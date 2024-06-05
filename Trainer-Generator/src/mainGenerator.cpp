#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <gegelati.h>

#include "instructions.h"
#include "PendulumLearningEnvironment.h"

// Import trained TPG from dot
// Give TPGFactoryInstrumented
// Evaluate
// clearHicthhickers()
// Export dot file

#define DEFAULT_NB_ACTIONS 1000
#define DEFAULT_NB_SEEDS 100

int main(int argc, char *argv[]) {
    

    std::cout << "\033[1;33m=====[ Code Generation ]=====\033[0m" << std::endl;

#if TYPE_INT == 1
    std::cout << "\tTYPE_INT=1, COEFF_DYNAMIC_OPPENING:" << COEFF_DYNAMIC_OPPENING << std::endl;
#else
    std::cout << "\tTYPE_DOUBLE, COEFF_DYNAMIC_OPPENING:" << COEFF_DYNAMIC_OPPENING << std::endl;
#endif

    /*
     * This program needs 1 argument :
     * - argv[1] : path to the .dot file of the TPG to be used, if relative path, starts from call pwd
     */

    /* Checking arguments */

    if(argc < 3){
        std::cerr << "Missing arguments, this program needs (in order) : the path to the .dot file, a seed." << std::endl;
        exit(1);
    }

    std::filesystem::path dotPath(argv[1]);
    unsigned int initial_seed;
    int nbActions = DEFAULT_NB_ACTIONS;
    int nbSeeds = DEFAULT_NB_SEEDS;

    std::cout << "nbSeeds: " << nbSeeds << std::endl;

    try{
        initial_seed = (unsigned int) std::stoi(argv[2]);
    }
    catch (const std::invalid_argument& e){
        std::cerr << "seed is not an int" << std::endl;
        exit(1);
    }

    
    /* Generate an array of seeds */
    
    // Set the seed for the RNG
    srand(initial_seed);

    // Array to store the nbSeeds generated seeds
    unsigned int seeds[nbSeeds];

    // Generate nbSeeds seeds using the initial seed
    for (int i = 0; i < nbSeeds; ++i) {
        seeds[i] = rand(); // Generate a random seed
    }


    /* Settings */

    // Instruction set
    Instructions::Set set;
    fillInstructionSet(set);

    // Load parameters
    Learn::LearningParameters params;
    File::ParametersParser::loadParametersFromJson(PROJECT_ROOT_PATH "/params.json", params);


    /* Setup Pendulum environment and import graph */

    // Setup environment
    PendulumLearningEnvironment pendulumLE({ 0.05, 0.1, 0.2, 0.4, 0.6, 0.8, 1.0 });

    // Load graph from dot file
    Environment env(set, pendulumLE.getDataSources(), params.nbRegisters, params.nbProgramConstant);
    TPG::TPGGraph tpgGraph(env, std::make_unique<TPG::TPGFactoryInstrumented>());
    File::TPGGraphDotImporter tpgGraphDotImporter(dotPath.c_str(), env, tpgGraph);
    tpgGraphDotImporter.importGraph();

    // Prepare for inference
    const TPG::TPGVertex* root(tpgGraph.getRootVertices().back());
    TPG::TPGExecutionEngineInstrumented tee(env);
    
    int scorePruned[nbSeeds], scoreOrig[nbSeeds], idActionsPruned[nbSeeds], idActionsOrig[nbSeeds];


    /***** Play the game once to identify useful edges & vertices (TPG Inference) *****/

    // output stream for tracabillity of the inference actions
    std::ofstream ofs (RESULT_EXPORT_PATH "/tpg_inference_actions_orig.txt", std::ofstream::out);
    int sum = 0;

    for(int i=0; i<nbSeeds; i++){
        // reset Learning Environment, counter
        pendulumLE.reset(seeds[i]);
        idActionsOrig[i] = 0;
        
        //std::cout << "Inference of original TPG" << std::endl;
        
        while(idActionsOrig[i] < nbActions && !pendulumLE.isTerminal()){
            auto actionID = ((TPG::TPGAction*)(tee.executeFromRoot(*root).back()))->getActionID();
            pendulumLE.doAction(actionID);
            ofs << idActionsOrig[i] << " " << actionID << std::endl;
            idActionsOrig[i]++;
        }
        scoreOrig[i] = pendulumLE.getScore();
        if(scoreOrig[i]>0){
            sum++;
        }
        //std::cout << "Total score: " << scoreOrig[i] << " in "  << idActionsOrig[i] << " actions." << std::endl;
    }
    
    ofs.close();


    // Clear Hitchhickers (the unused vertices & teams)
    ((const TPG::TPGFactoryInstrumented&)tpgGraph.getFactory()).clearUnusedTPGGraphElements(tpgGraph);
    
    // Clear the trace history from all previous inference trace.
    // Execution Stats uses this trace to generate statistics of inference.
    tee.clearInferenceTraceHistory();

    
    /***** Replay the game to make sure results are unchanged after deleting parts of the TPG (TPG Inference) *****/
    
    // output stream for tracabillity of the inference actions
    std::ofstream ofs2 (RESULT_EXPORT_PATH "/tpg_cleaned_inference_actions.txt", std::ofstream::out);

    for(int i=0; i<nbSeeds; i++){
        // reset Learning Environment, counter
        pendulumLE.reset(seeds[i]);
        idActionsPruned[i] = 0;
        
        //std::cout << "Inference of cleaned TPG code" << std::endl;
        while(idActionsPruned[i] < nbActions && !pendulumLE.isTerminal()){
            auto actionID = ((TPG::TPGAction*)(tee.executeFromRoot(* root).back()))->getActionID();
            pendulumLE.doAction(actionID);
            ofs2 << idActionsPruned[i] << " " << actionID << std::endl;
            idActionsPruned[i]++;
        }
        scorePruned[i] = pendulumLE.getScore();
        //std::cout << "Total score: " << scorePruned[i] << " in "  << idActionsPruned[i] << " actions." << std::endl;
    }

    ofs.close();

    for(int i=0; i<nbSeeds; i++){
        if(scorePruned[i] != scoreOrig[i] || idActionsPruned[i] != idActionsOrig[i]){
            std::cout << "Seed: " << i << ", determinism was lost during graph cleaning." << std::endl;
            exit(1);
        }
    }
    

    double percentCorrectPred = ((double) sum/(double) nbSeeds)*100;
    std::cout << "percentCorrectPred: " << percentCorrectPred << std::endl; 

    // Get stats on graph to get the required stack size
    std::cout << "Analyze graph." << std::endl;
    TPG::PolicyStats ps;
    ps.setEnvironment(env);
    ps.analyzePolicy(tpgGraph.getRootVertices().front());


    // Generate bestPolicyStats
    char bestPolicyStatsPath[150];
    std::ofstream bestStats;
    sprintf(bestPolicyStatsPath, "%s/best_root_pruned_stats.md", RESULT_EXPORT_PATH);
    bestStats.open(bestPolicyStatsPath);
    bestStats << ps;
    bestStats.close();

    // Execution statistics extraction and export
    TPG::ExecutionStats executionStats;
    executionStats.analyzeExecution(tee, &tpgGraph);
    executionStats.writeStatsToJson((dotPath.parent_path().string() + "/executionStats.json").c_str());


    // Code Generation
    std::cout << "Printing C code." << std::endl;
	CodeGen::TPGGenerationEngineFactory factory(CodeGen::TPGGenerationEngineFactory::switchMode);
    std::unique_ptr<CodeGen::TPGGenerationEngine> tpgGenerationEngine = factory.create("TPG", tpgGraph, RESULT_EXPORT_PATH "/src/");
    tpgGenerationEngine->generateTPGGraph();


    // Generate out best dot file
    std::cout << "Printing cleaned dot file." << std::endl;

    // Create an exporter for graphs
    File::TPGGraphDotExporter dotExporter(RESULT_EXPORT_PATH "/best_root_pruned.dot", tpgGraph);
    dotExporter.print();

    std::cout << "End program" << std::endl;

    return 0;
}