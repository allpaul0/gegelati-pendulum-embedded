#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <gegelati.h>

#include "instructions.h"
#include "PendulumLearningEnvironment.h"

#define DEFAULT_NB_SEEDS 100

// #define VERBOSE

int main(int argc, char *argv[]) {

    std::cout << "\033[1;33m=====[ Execution informations target ]=====\033[0m" << std::endl;

#if TYPE_INT == 1
    std::cout << "\tTYPE_INT=1, COEFF_DYNAMIC_OPPENING:" << COEFF_DYNAMIC_OPPENING << std::endl;
#else
    std::cout << "\tTYPE_DOUBLE, COEFF_DYNAMIC_OPPENING:" << COEFF_DYNAMIC_OPPENING << std::endl;
#endif

    /*
     * This program needs 2 arguments :
     * - argv[1] : path to the .dot file of the TPG to be used, if relative path, starts from call pwd
     * - argv[2] : seed
     */


    /* Checking arguments */

    if(argc < 3){
        std::cerr << "Missing arguments, this program needs (in order) : the path to the .dot file, a seed." << std::endl;
        exit(1);
    }

    std::filesystem::path dotPath(argv[1]);
    unsigned int initial_seed;
    int nbSeeds = DEFAULT_NB_SEEDS;

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
    TPG::TPGExecutionEngineInstrumented tee(env);
    const TPG::TPGVertex* root(tpgGraph.getRootVertices().back());

    /* Prepare to Execution informations extraction and export */
    TPG::ExecutionInfos executionInfos;

    //Annotate the graph for better understanding of the execution
    executionInfos.assignIdentifiers((const TPG::TPGTeamInstrumented*)root);
    //executionInfos.assignIdentifiers(root);

    /* TPG Inference */

    for(int j = 0; j < nbSeeds; j++){

        // std::cout << "\t Seed: " << seeds[j] 

        // set the inital pendulum conditions using the seed
        pendulumLE.reset(seeds[j], Learn::LearningMode::TESTING);
       
        // execute one action, trace it, and move to the next seed.        
        tee.executeFromRoot(*root);

        executionInfos.analyzeExecution(tee, tpgGraph, seeds[j]);
    }
       
    executionInfos.writeInfosToJson((dotPath.parent_path().string() + "/../training/executionInfos.json").c_str());

    std::cout << "End program" << std::endl;

    return 0;
}