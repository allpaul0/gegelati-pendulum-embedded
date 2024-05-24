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
#define DISPLAY_VALIDATION 1

int main(int argc, char *argv[]) {
    

    std::cout << "\033[1;33m=====[ Validation ]=====\033[0m" << std::endl;

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
    //int nbActions = DEFAULT_NB_ACTIONS;
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
    Instructions::Set instructionSet;
    fillInstructionSet(instructionSet);

    // Load parameters
    Learn::LearningParameters params;
    File::ParametersParser::loadParametersFromJson(PROJECT_ROOT_PATH "/params.json", params);


    /* Setup Pendulum environment and import graph */

    // Setup environment
    PendulumLearningEnvironment pendulumLE({ 0.05, 0.1, 0.2, 0.4, 0.6, 0.8, 1.0 });

    // Load graph from dot file
    Environment env(instructionSet, pendulumLE.getDataSources(), params.nbRegisters, params.nbProgramConstant);
    std::shared_ptr<TPG::TPGGraph> tpgGraph = std::make_shared<TPG::TPGGraph>(env, std::make_unique<TPG::TPGFactory>());
    File::TPGGraphDotImporter tpgGraphDotImporter(dotPath.c_str(), env, *tpgGraph);
    tpgGraphDotImporter.importGraph();
    
    Learn::ParallelLearningAgent la(pendulumLE, instructionSet, params, tpgGraph);

    /* Log and output setup */

    // Log 
    std::ofstream validationLogFile(RESULT_EXPORT_PATH "/validation.log");
    Log::LABasicLogger outputFileLog(la, validationLogFile);
#ifdef DISPLAY_VALIDATION
    Log::LABasicLogger consoleLog(la);
#endif 
    
    double total_result_accuracy = 0; 

    /***** Play the game once to identify useful edges & vertices (TPG Inference) *****/

    for(int i=0; i<nbSeeds; i++){
        
        // reset Learning Environment, counter
        pendulumLE.reset(seeds[i]);

        auto resultsOrig = la.evaluateAllRoots(i, Learn::LearningMode::VALIDATION);

        auto val = resultsOrig.begin()->first->getResult();
        if(val > 0 ){
            total_result_accuracy ++;
        }

#ifdef DISPLAY_VALIDATION        
        consoleLog.logAfterValidate(resultsOrig);
        std::cout << std::endl;
#endif
        outputFileLog.logAfterValidate(resultsOrig);
        outputFileLog << std::endl;
    }

    total_result_accuracy = (total_result_accuracy * 100) / nbSeeds;

    std::cout << "Accuracy: " << int(total_result_accuracy) << "%" << std::endl;
    outputFileLog << "Accuracy: " << int(total_result_accuracy) << "%" << std::endl;

    std::cout << "End program" << std::endl;

    return 0;
}