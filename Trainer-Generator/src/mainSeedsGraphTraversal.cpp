#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <gegelati.h>
#include <random>
#include <vector>

#include "instructions.h"
#include "PendulumLearningEnvironment.h"

// number of seeds to try before stopping the search for new graph traversals
#define DEFAULT_NB_SEEDS 1e5 // 2000
// #define VERBOSE

/// @brief stores the elements required at the start
/// of a graph traversal measurement.
/// The storing of traceTeamIds, which represents the
/// path of the graph traversal is stored for indicative
/// purpose.
struct graphTraversalInitializer
{
    /// initial values
    double angle;
    double velocity;
    uint32_t seed;
    /// identifiers for each traversed Team
    std::list<int> traceTeamIds;
};

/// @brief specify if the seeds are randomized in the output header file
/// allows to distribute the computation and be less dependent to the heating
/// of the chip.
enum RandomizeOption
{
    DisableRandomize = 0,
    EnableRandomize = 1
};

/// @brief Function to write data from two arrays to a CSV file
void storeToCProgram(
    const std::string &filename,
    const std::map<std::list<int>, std::vector<graphTraversalInitializer>> mapGTI,
    bool randomize);

int main(int argc, char *argv[])
{

    std::cout << "\033[1;33m=====[ Generate Seeds for Graph Traversal target ]=====\033[0m" << std::endl;

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

    if (argc < 3)
    {
        std::cerr << "Missing arguments, this program needs (in order) : the path to the .dot file, a seed." << std::endl;
        exit(1);
    }

    std::filesystem::path dotPath(argv[1]);
    unsigned int initial_seed;
    int nbSeeds = DEFAULT_NB_SEEDS;

    try
    {
        initial_seed = (unsigned int)std::stoi(argv[2]);
    }
    catch (const std::invalid_argument &e)
    {
        std::cerr << "seed is not an int" << std::endl;
        exit(1);
    }

    // Set the seed for the RNG
    srand(initial_seed);

    /* Settings */

    // Instruction set
    Instructions::Set set;
    fillInstructionSet(set);

    // Load parameters
    Learn::LearningParameters params;
    File::ParametersParser::loadParametersFromJson(PROJECT_ROOT_PATH "/params.json", params);

    /* Setup Pendulum environment and import graph */

    // Setup environment
    PendulumLearningEnvironment pendulumLE({0.05, 0.1, 0.2, 0.4, 0.6, 0.8, 1.0});

    // Load graph from dot file
    Environment env(set, pendulumLE.getDataSources(), params.nbRegisters, params.nbProgramConstant);
    TPG::TPGGraph tpgGraph(env, std::make_unique<TPG::TPGFactoryInstrumented>());
    File::TPGGraphDotImporter tpgGraphDotImporter(dotPath.c_str(), env, tpgGraph);
    tpgGraphDotImporter.importGraph();

    // Prepare for inference, retrieve exec engine and root
    TPG::TPGExecutionEngineInstrumented tee(env);
    const TPG::TPGVertex *root(tpgGraph.getRootVertices().back());

    // Prepare for Execution informations extraction and export
    TPG::ExecutionInfos executionInfos;

    // Annotate the graph to understand the progress of the execution
    executionInfos.assignIdentifiers((const TPG::TPGTeamInstrumented *)root);

    // We don't know the size of the following struct at compile time
    // since we want 10 occurences of each graph traversals and we don't
    // know how many graph traversal there can be for a given TPG a priori
    // Graph traversal = combinations of Team traversed before reaching action

    std::map<std::list<int>, std::vector<graphTraversalInitializer>> mapGTI;

    /* TPG Inference */
    int continue_search = 0;
    int total_nb_seeds = 0;

    do
    {
        for (int j = 0; j < nbSeeds; j++)
        {
            // generate the seed, find associated angle and velocity
            uint32_t seed = rand();
            double angle;
            double velocity;

            // set the inital pendulum conditions using the seed, sets angle and velocity
            pendulumLE.reset(seed, &angle, &velocity, Learn::LearningMode::TESTING);

            // execute one action, trace it, and move to the next seed.
            tee.executeFromRoot(*root);

            // retrieve graph traversal informations from TPG and tee
            executionInfos.analyzeExecution(tee, tpgGraph, seed, angle, velocity);
        }

        // ended a serie of search through nbSeeds

        // retrieve vecInfTraceInfos
        std::vector<TPG::InferenceTraceInfos> vecInferenceTraceInfos = executionInfos.getVecInferenceTraceInfos();

        for (TPG::InferenceTraceInfos infTraceInfos : vecInferenceTraceInfos)
        {
            // the key is the graph traversal of the inferenceTraceInfos object under inspection
            // graph Traversals  = list<int> traceTeamIds

            // if the key doesnt exist in the map, insert it with its value
            if (!mapGTI.count(infTraceInfos.traceTeamIds))
            {
                // create the value (gTI) gTI = mean to init the TPG to do the graphTraversal
                graphTraversalInitializer gTI;
                gTI.seed = infTraceInfos.seed;
                gTI.traceTeamIds = infTraceInfos.traceTeamIds;
                gTI.angle = infTraceInfos.angle;
                gTI.velocity = infTraceInfos.velocity;
                std::vector<graphTraversalInitializer> vecgTI = {gTI};
                // insert key (graphTraversal), value (gTI)
                mapGTI.insert({infTraceInfos.traceTeamIds, vecgTI});
            }

            // else if the key is already present but we have less than 10 values and the seed is not already in the map,
            // insert the value
            else
            {
                if (mapGTI[infTraceInfos.traceTeamIds].size() < 10)
                {

                    // iterate over the vector mapGTI[infTraceInfos.traceTeamIds] to make sure the seed
                    // we want to add is not already present
                    int collision = 0;
                    for (graphTraversalInitializer gti : mapGTI[infTraceInfos.traceTeamIds])
                    {
                        if (infTraceInfos.seed == gti.seed)
                        {
                            collision++;
                        }
                    }
                    if (!collision)
                    {
                        // create the value (gTI) gTI = mean to init the TPG to do the graphTraversal
                        graphTraversalInitializer gTI;
                        gTI.seed = infTraceInfos.seed;
                        gTI.traceTeamIds = infTraceInfos.traceTeamIds;
                        gTI.angle = infTraceInfos.angle;
                        gTI.velocity = infTraceInfos.velocity;
                        // insert key (graphTraversal), value (gTI)
                        mapGTI[infTraceInfos.traceTeamIds].push_back(gTI);
                    }
                    else
                    {
                        std::cerr << "collision" << std::endl;
                    }
                }
            }

            // else discard key, value pair
        }

        // Do we have a balanced map, X values for each graph traversal
        int balanced = 1;
        for (std::map<std::list<int>, std::vector<graphTraversalInitializer>>::iterator it = mapGTI.begin(); it != mapGTI.end(); it++)
        {
            const std::vector<graphTraversalInitializer> &gti = it->second;
            if (gti.size() < 10)
            {
                balanced = 0;
            }
        }

        // if not balanced -> continue_serach
        continue_search = !balanced;
        total_nb_seeds += nbSeeds;

        // clear vecInferenceTraceInfos
        executionInfos.clear();

    } while (continue_search);

    std::cout << "total seeds searched: " << total_nb_seeds << std::endl;
    std::cout << "graph traversal: " << mapGTI.size() << std::endl;
    for (std::map<std::list<int>, std::vector<graphTraversalInitializer>>::iterator it = mapGTI.begin(); it != mapGTI.end(); it++)
    {
        const std::list<int> &teams = it->first;
        const std::vector<graphTraversalInitializer> &gti = it->second;

        std::cout << "[";
        for (int t : teams)
        {
            std::cout << "T" << t << ", ";
        }
        std::cout << "]" << std::endl;
        std::cout << gti.size() << "\n";
    }

    // Write data to CSV file
    storeToCProgram("Results/seeds_nbActionsToTerminal.h", mapGTI, EnableRandomize);

    // Empty the vec of InferenceTraceInfos from executionInfos which has current TPG execution context in it
    //executionsInfos.clear();

    // Re-fill it with the values from the map we are keeping
    //executionInfos.set();

    executionInfos.writeTPGtoJson((dotPath.parent_path().string() + "/../training/tpgInfos.json").c_str());

    executionInfos.writeInfosToJson((dotPath.parent_path().string() + "/../training/executionInfos.json").c_str());

    std::cout << "End program" << std::endl;

    return 0;
}

void storeToCProgram(
    const std::string &filename,
    const std::map<std::list<int>, std::vector<graphTraversalInitializer>> mapGTI,
    bool randomize)
{

    std::ofstream file(filename);

    if (!file.is_open())
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    // Collect all data into vectors
    std::vector<double> angles;
    std::vector<double> velocities;
    std::vector<unsigned int> seeds;
    std::vector<unsigned int> ids_graph_traversals;

    // C++17 structured binding, mutiples vars initialized from tuple
    // used to unpack the key-value pair in the map
    int id_GT = 0;
    for (const auto &[_, vecGTI] : mapGTI)
    {
        for (auto const &gti : vecGTI)
        {
            angles.push_back(gti.angle);
            velocities.push_back(gti.velocity);
            seeds.push_back(gti.seed);
            ids_graph_traversals.push_back(id_GT);
        }
        id_GT++;
    }

    // Determine number of values
    size_t nbValues = angles.size();

    // If randomize is true, shuffle the indices
    std::vector<size_t> indices(nbValues);
    // Fill with 0, 1, ..., nbValues-1
    std::iota(indices.begin(), indices.end(), 0);

    if (randomize)
    {
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(indices.begin(), indices.end(), g);
    }

    // write Header
    file << "#ifndef SEEDS_H\n"
         << "#define SEEDS_H\n\n"
         << "#define NB_SEED " << nbValues << "\n\n";

    // Helper lambda to write an array
    auto writeArray = [&file](const std::string &name, const auto &data, const std::vector<size_t> &indices)
    {
        using DataType = typename std::decay<decltype(data[0])>::type;
        file << "static const "
             << (std::is_same_v<DataType, double> ? "double" : "unsigned int")
             << " " << name << "[NB_SEED] = {";
        for (size_t i = 0; i < indices.size(); i++)
        {
            if (i > 0)
                file << ", ";
            file << data[indices[i]];
        }
        file << "};\n";
    };

    // Write arrays
    writeArray("angles", angles, indices);
    writeArray("velocities", velocities, indices);
    writeArray("seeds", seeds, indices);
    writeArray("ids_graph_traversals", ids_graph_traversals, indices);

    file << "\n";

    // write Footer
    file << "#endif /* SEEDS_H */";

    file.close();

    if (randomize)
    {
        std::cout << "Data order was randomized." << std::endl;
    }
    std::cout << "Data written to " << filename << " successfully." << std::endl;
}
