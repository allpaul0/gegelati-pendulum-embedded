#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <gegelati.h>

#include "instructions.h"
#include "PendulumLearningEnvironment.h"

#define DEFAULT_NB_ACTIONS 1000
// #define VERBOSE

int main(int argc, char *argv[]) {


    std::cout << "\033[1;33m=====[ Execution statistics target ]=====\033[0m" << std::endl;

#if TYPE_INT == 1
    std::cout << "\tTYPE_INT=1, COEFF_DYNAMIC_OPPENING:" << COEFF_DYNAMIC_OPPENING << std::endl;
#else
    std::cout << "\tTYPE_DOUBLE, COEFF_DYNAMIC_OPPENING:" << COEFF_DYNAMIC_OPPENING << std::endl;
#endif

    /*
     * This program need 3 to 4 arguments :
     * - argv[1] : path to the .dot file of the TPG to be used, if relative path, starts from call pwd
     * - argv[2] : initial angle
     * - argv[3] : initial velocity
     * - argv[4] : number of inferences to do (default in 1000)
     *
     * The executionStats.json file is generated in the same directory as the .dot file.
     */


    /* Checking arguments */

    if(argc < 4){
        std::cerr << "Missing arguments, this program needs (in order) : the path to the .dot file, the initial angle"
                     "and the initial velocity." << std::endl;
        exit(1);
    }
    
    double initalAngle;
    double initialVelocity;
    std::filesystem::path dotPath(argv[1]);
    int nbActions = DEFAULT_NB_ACTIONS;

    try{
        initalAngle = std::stod(argv[2]);
        initialVelocity = std::stod(argv[3]);
    }
    catch (const std::invalid_argument& e){
        std::cerr << "Initial angle or velocity is not a double" << std::endl;
        exit(1);
    }

    if(argc == 5){
        try {
            nbActions = std::stoi(argv[4]);
        }
        catch (const std::invalid_argument& e){
            std::cerr << "Invalid given number of action, use default value (" << DEFAULT_NB_ACTIONS << ")" << std::endl;
        }
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
    pendulumLE.reset(initalAngle, initialVelocity);

    // Load graph from dot file
    Environment env(set, pendulumLE.getDataSources(), params.nbRegisters, params.nbProgramConstant);
    TPG::TPGGraph tpgGraph(env, std::make_unique<TPG::TPGFactoryInstrumented>());
    File::TPGGraphDotImporter tpgGraphDotImporter(dotPath.c_str(), env, tpgGraph);
    tpgGraphDotImporter.importGraph();

    // Prepare for inference
    TPG::TPGExecutionEngineInstrumented tee(env);
    const TPG::TPGVertex* root(tpgGraph.getRootVertices().back());

    /* TPG Inference */

    std::cout << "\tInitial parameter {Angle : " << initalAngle <<", Velocity : " << initialVelocity << "}" << std::endl;

    bool wasTerminal = false;
    for(int i = 0; i < nbActions; i++){

        auto trace = tee.executeFromRoot(*root);
        uint64_t action = ((const TPG::TPGAction*)trace.back())->getActionID();
        pendulumLE.doAction(action);

#ifdef VERBOSE
        std::cout << "Action : " << i+1 << " { Angle = " << pendulumLE.getAngle() << ", Velocity : " << pendulumLE.getVelocity() << " }" << std::endl;
#endif

        if(!wasTerminal && pendulumLE.isTerminal()){
            std::cout << "\tPendulum reached terminal state at \033[1;36mstep " << i+1 << "\033[0m" << std::endl;
            wasTerminal = true;
        }

    }
    if (!pendulumLE.isTerminal()){
        std::cout << "\t\033[1;31mPendulum did not reach terminal state\033[0m" << std::endl;
    }

    /* Execution statistics extraction and export */

    //std::cout << "Exporting execution statistics" << std::endl;

    TPG::ExecutionStats executionStats;
    executionStats.analyzeExecution(tee, &tpgGraph);
    executionStats.writeStatsToJson((dotPath.parent_path().string() + "/executionStats.json").c_str());
    //placed in CodeGen, latter moved to the current inference_timestamp dir

    //std::cout << "End program" << std::endl;

    return 0;
}
