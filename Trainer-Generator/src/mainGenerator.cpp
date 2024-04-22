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

#define NBACTIONS 18000

int main(int argc, char *argv[]) {

    std::cout << "\033[1;33m=====[ Instrumentation target ]=====\033[0m" << std::endl;

    /*
     * This program needs 1 argument :
     * - argv[1] : path to the .dot file of the TPG to be used, if relative path, starts from call pwd
     */

    /* Checking arguments */

    if(argc < 2){
        std::cerr << "Missing arguments, this program needs : the path to the .dot file." << std::endl;
        exit(1);
    }

#if TYPE_INT == 1
    std::cout << "\tTYPE_INT=1, COEFF_DYNAMIC_OPPENING:" << COEFF_DYNAMIC_OPPENING << std::endl;
#else
    std::cout << "\tTYPE_DOUBLE, COEFF_DYNAMIC_OPPENING:" << COEFF_DYNAMIC_OPPENING << std::endl;
#endif

    std::filesystem::path dotPath(argv[1]);

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
    double initalAngle = -3.14159;
    double initialVelocity = 0.380002;

    // Load graph from dot file
    Environment env(set, pendulumLE.getDataSources(), params.nbRegisters, params.nbProgramConstant);
    TPG::TPGGraph tpgGraph(env, std::make_unique<TPG::TPGFactoryInstrumented>());
    File::TPGGraphDotImporter tpgGraphDotImporter(dotPath.c_str(), env, tpgGraph);
    tpgGraphDotImporter.importGraph();

    // Prepare for inference
    const TPG::TPGVertex* root(tpgGraph.getRootVertices().back());
    TPG::TPGExecutionEngineInstrumented tee(env);
    
    
    /* Play the game once to identify useful edges & vertices (TPG Inference) */

    // output stream for tracabillity of the inference actions
    std::ofstream ofs (RESULT_EXPORT_PATH "/tpg_inference_actions_orig.txt", std::ofstream::out);

    // reset Learning Environment, counter
    pendulumLE.reset(initalAngle, initialVelocity);
    int idActionsOrig = 0;
    
    std::cout << "Inference of original TPG" << std::endl;
    while(idActionsOrig < NBACTIONS && !pendulumLE.isTerminal()){
    	auto actionID = ((TPG::TPGAction*)(tee.executeFromRoot(*root).back()))->getActionID();
        pendulumLE.doAction(actionID);
        ofs << idActionsOrig << " " << actionID << std::endl;
        idActionsOrig++;
    }
    auto scoreOrig = pendulumLE.getScore();
    std::cout << "Total score: " << scoreOrig << " in "  << idActionsOrig << " actions." << std::endl;
    ofs.close();


    // Clear Hitchhickers (the unused vertices & teams)
    ((const TPG::TPGFactoryInstrumented&)tpgGraph.getFactory()).clearUnusedTPGGraphElements(tpgGraph);


    /* Replay the game to make sure results are unchanged after deleting parts of the TPG (TPG Inference) */
    
    // output stream for tracabillity of the inference actions
    std::ofstream ofs2 (RESULT_EXPORT_PATH "/tpg_cleaned_inference_actions.txt", std::ofstream::out);
    
    // reset Learning Environment, counter
    pendulumLE.reset(initalAngle, initialVelocity);
    int idActionsPruned = 0;
    
    std::cout << "Inference of cleaned TPG code" << std::endl;
    while(idActionsPruned < 18000 && !pendulumLE.isTerminal()){
    	auto actionID = ((TPG::TPGAction*)(tee.executeFromRoot(* root).back()))->getActionID();
        pendulumLE.doAction(actionID);
        ofs2 << idActionsPruned << " " << actionID << std::endl;
        idActionsPruned++;
    }
    auto scorePruned = pendulumLE.getScore();
    std::cout << "Total score: " << scorePruned << " in "  << idActionsPruned << " actions." << std::endl;
    ofs.close();

    if(scorePruned != scoreOrig || idActionsPruned != idActionsOrig){
        std::cout << "Determinism was lost during graph cleaning." << std::endl;
        exit(1);
    }

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
