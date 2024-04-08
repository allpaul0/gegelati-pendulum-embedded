#include <iostream>
#include <fstream>
#include <ctime>
#include <gegelati.h>

#include "PendulumLearningEnvironment.h"
#include "instructions.h"

int main() {
    std::cout << "\033[1;33m=====[ Trainer target ]=====\033[0m" << std::endl;

    std::cout << "Environment initialisation" << std::endl;

    /* Settings */

    // Instruction set
    Instructions::Set instructionSet;
    fillInstructionSet(instructionSet);
    // Learning parameters
    Learn::LearningParameters params;
    File::ParametersParser::loadParametersFromJson(PROJECT_ROOT_PATH "/params.json", params);

    /* Trainings objects */

    // Learning environment
    PendulumLearningEnvironment pendulumLE({ 0.05, 0.1, 0.2, 0.4, 0.6, 0.8, 1.0 });
    // Learning agent
    size_t seed = 0; // = time(nullptr);
    const TPG::TPGFactory& TPGInstrumentedFactory = TPG::TPGInstrumentedFactory();
    Learn::ParallelLearningAgent la(pendulumLE, instructionSet, params, TPGInstrumentedFactory);

    std::shared_ptr<TPG::TPGGraph> tpg1 = la.getTPGGraph();

    //Learn::ParallelLearningAgent la(pendulumLE, instructionSet, params);
    la.init(seed);

    /* Training message*/
    std::cout << "Starting training for " << params.nbGenerations << " generations" << std::endl;
    
    /* Log and output setup */

    // Log
    std::ofstream trainLogFile(RESULT_EXPORT_PATH "/train.log");
    Log::LABasicLogger trainLog(la, trainLogFile);
    Log::LABasicLogger consoleLog(la);
    // Create an exporter for graphs
    File::TPGGraphDotExporter dotExporter(RESULT_DOTFILE_PATH "/out_0000.dot", *la.getTPGGraph());
    // Logging best policy stat.
    std::ofstream stats;
    stats.open(RESULT_EXPORT_PATH "/bestPolicyStats.md");
    Log::LAPolicyStatsLogger policyStatsLogger(la, stats);
    // Export parameters before starting training.
    // These may differ from imported parameters because of LE or machine specific
	// settings such as thread count of number of actions.
    File::ParametersParser::writeParametersToJson(RESULT_EXPORT_PATH "/exported_params.json", params);

    /* Training */

    for (uint64_t i = 0; i < params.nbGenerations; i++){
        // Setting dot exporter for generation graph
        char buff[100];
        sprintf(buff, RESULT_EXPORT_PATH "/dotfiles/out_%04ld.dot", i);
        dotExporter.setNewFilePath(buff);
        dotExporter.print();

        la.trainOneGeneration(i);
    }

    std::cout << "End training, generating data on best policy" << std::endl;

    // Clean unused vertices and teams (clean Hitchhickers)
    std::shared_ptr<TPG::TPGGraph> tpg = la.getTPGGraph();

    //check if the factory is of type TPGInstrumentedFactory
    /*
    auto tpgFactory = tpg->getFactory();
    if (typeid(tpgFactory) == typeid(TPG::TPGFactory)) {
        std::cout << "TPG::TPGFactory" << std::endl;

    }else if(typeid(tpgFactory) == typeid(TPG::TPGInstrumentedFactory)){
        std::cout << "TPG::TPGInstrumentedFactory" << std::endl;
        
    }else {
        std::cout << "else" << std::endl;
    }
    */

    TPG::TPGInstrumentedFactory().clearUnusedTPGGraphElements(*tpg);

    // Keep only the best root
    la.keepBestPolicy();

    // Clean introns from the TPG
    tpg->clearProgramIntrons();

    // Print the resulting TPG
    dotExporter.setNewFilePath(RESULT_EXPORT_PATH "/out_best.dot");
    dotExporter.print();

    // Export topology stats on the winning root
    TPG::PolicyStats ps;
    ps.setEnvironment(la.getTPGGraph()->getEnvironment());
    ps.analyzePolicy(la.getBestRoot().first);
    std::ofstream bestStats;
    bestStats.open(RESULT_EXPORT_PATH "/out_best_stats.md");
    bestStats << ps;
    bestStats.close();
    stats.close();

    // Cleanup instruction set
	deleteInstructions(instructionSet);

    trainLogFile.close();

    std::cout << "End program" << std::endl;

    return 0;
}
