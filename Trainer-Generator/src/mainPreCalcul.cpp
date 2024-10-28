#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <gegelati.h>
#include <random>

#include "instructions.h"
#include "PendulumLearningEnvironment.h"    

#define DEFAULT_NB_ACTIONS 1000
#define DEFAULT_NB_SEEDS 100
// #define VERBOSE

// Function to write data from two arrays to a CSV file
void storeToCProgram(const std::string& filename, const double* angles, const double* velocities, 
    const unsigned int* seeds, const int* nbActionsToTerminal, size_t nbValues) {
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    // write Header
    file << "#ifndef SEEDS_H\n"
        << "#define SEEDS_H\n\n"

        << "#define NB_SEED " << nbValues << "\n\n"

        << "static const double angles[NB_SEED] = {";

    // write content of angles array
    size_t i;
    for (i = 0; i < nbValues-1; ++i) {
        file << angles[i] << ", "; 
    }
    file << angles[i] << "};\n"

        << "static const double velocities[NB_SEED] = {";

    // write content of velocities array
    for (i = 0; i < nbValues-1; ++i) {
        file << velocities[i] << ", "; 
    }
    file << velocities[i] << "};\n"

        << "static const unsigned int seeds[NB_SEED] = {";

    // write content of seeds array
    for (i = 0; i < nbValues-1; ++i) {
        file << seeds[i] << ", "; 
    }
    file << seeds[i] << "};\n"
        << "static const int nbActionsToTerminal[NB_SEED] = {";

    // write content of nbActionsToTerminal array
    for (i = 0; i < nbValues-1; ++i) {
        file << nbActionsToTerminal[i] << ", "; 
    }
    file << nbActionsToTerminal[i] << "};\n\n";

    // write Footer
    file << "#endif /* SEEDS_H */";

    file.close();
}

int main(int argc, char *argv[]) {


    std::cout << "\033[1;33m=====[ PreCalcul target ]=====\033[0m" << std::endl;

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
    int nbActions = DEFAULT_NB_ACTIONS;
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
    double angles[nbSeeds];
    double velocities[nbSeeds];

    // Generate nbSeeds seeds using the initial seed
    for (int i = 0; i < nbSeeds; ++i) {
        seeds[i] = rand(); // Generate a random seed
    }


    /* Settings */

    // Array to store the number of actions to compute before solving the 
    // Environment's challenge (Stabilizing a Pendulum, Scoring XXX points, ...)
    int nbActionsToTerminal[nbActions];

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

    /* TPG Inference */

    for(int j = 0; j < nbSeeds; j++){

        // set the inital pendulum conditions using the seed
        pendulumLE.reset(seeds[j], &angles[j], &velocities[j], Learn::LearningMode::TESTING);
        
        //std::cout << "\tInitial parameter {Angle : " << initalAngle <<", Velocity : " << initialVelocity << "}" << std::endl;

        bool wasTerminal = false;
        int i = 0;
        while(i < nbActions && !wasTerminal){

            auto trace = tee.executeFromRoot(*root);
            uint64_t action = ((const TPG::TPGAction*)trace.back())->getActionID();
            pendulumLE.doAction(action);

    #ifdef VERBOSE
            std::cout << "Action : " << i+1 << " { Angle = " << pendulumLE.getAngle() << ", Velocity : " << pendulumLE.getVelocity() << " }" << std::endl;
    #endif

            if(!wasTerminal && pendulumLE.isTerminal()){
                std::cout << "\tseed: " << seeds[j] << " - Pendulum reached terminal state at \033[1;36mstep " << i+1 << "\033[0m" << std::endl;
                wasTerminal = true;
                nbActionsToTerminal[j] = i; // save the number of actions computed for this seed of the problem
            }

            i++;
        }
        if (!pendulumLE.isTerminal()){
            std::cout << "\t\033[1;31mseed: " << seeds[j] << " - Pendulum did not reach terminal state.\033[0m" << std::endl;
            nbActionsToTerminal[j] = -1;
        }
    }

    // Write data to CSV file
    storeToCProgram("Results/seeds_nbActionsToTerminal.h", angles, velocities, seeds, nbActionsToTerminal, nbSeeds);

    std::cout << "Data written to Results/seeds_nbActionsToTerminal.csv successfully." << std::endl;

    std::cout << "End program" << std::endl;

    return 0;
}
