cmake_minimum_required(VERSION 3.16)

set(PROJECT_NAME Trainer_Generator)
project(${PROJECT_NAME})

# Build type is released if not specified via command line
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()


set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Link with pthread
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
#add libmath during non visual studio builds
set(CMAKE_EXTRA_LIB m)


#OPTION(TYPE_INT "int data type used for TPG inference" ON) # Disabled by default
if (DEFINED TYPE_INT)
    set(ADDITIONAL_C_FLAGS "${ADDITIONAL_C_FLAGS} -DTYPE_INT=${TYPE_INT}")
    message("ADDITIONAL_C_FLAGS: ${ADDITIONAL_C_FLAGS}")
endif()


# Debug or release
if(CMAKE_BUILD_TYPE MATCHES "Debug")
    MESSAGE("Generate Debug project")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Debug)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${ADDITIONAL_C_FLAGS} -g -pg -Wall")
elseif(CMAKE_BUILD_TYPE MATCHES "Release")
    MESSAGE("Generate Release project")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Release)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${ADDITIONAL_C_FLAGS} -Wall")
elseif(CMAKE_BUILD_TYPE MATCHES "Profiling")
MESSAGE("Generate Profiling project")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Profiling)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${ADDITIONAL_C_FLAGS} -g -O2 -shared-libgcc -Wall")
endif()

# === GEGELATI ===
find_package(GEGELATI)


# === Executable target ===
add_definitions( 
        -DPROJECT_ROOT_PATH="${CMAKE_CURRENT_SOURCE_DIR}"
        -DRESULT_EXPORT_PATH="./Results"
        -DRESULT_DOTFILE_PATH="./Results/dotfiles"
)
file(MAKE_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Results)
file(GLOB_RECURSE
        files
        ./src/instructions.*
        ./src/PendulumLearningEnvironment.*
        ./src/approximateComputingTools.h
        ./params.json
)

include_directories(${GEGELATI_INCLUDE_DIRS})

set(TRAINER_TARGET Trainer)
add_executable(${TRAINER_TARGET} src/mainTrainer.cpp ${files})
target_link_libraries(${TRAINER_TARGET} ${GEGELATI_LIBRARIES})
add_custom_command(
    TARGET ${TRAINER_TARGET} PRE_BUILD 
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Results/dotfiles)

set(GENERATOR_TARGET Generator)
add_executable(${GENERATOR_TARGET} src/mainGenerator.cpp ${files})
target_link_libraries(${GENERATOR_TARGET} ${GEGELATI_LIBRARIES})
add_custom_command(
    TARGET ${GENERATOR_TARGET} PRE_BUILD 
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Results/src)

set(PRECALCUL_TARGET PreCalcul)
add_executable(${PRECALCUL_TARGET} src/mainPreCalcul.cpp ${files})
target_link_libraries(${PRECALCUL_TARGET} ${GEGELATI_LIBRARIES})

set(EXECUTION_STATS_TARGET ExecutionStats)
add_executable(${EXECUTION_STATS_TARGET} src/mainExecutionStats.cpp ${files})
target_link_libraries(${EXECUTION_STATS_TARGET} ${GEGELATI_LIBRARIES})

set(EXECUTION_INFOS_TARGET ExecutionInfos)
add_executable(${EXECUTION_INFOS_TARGET} src/mainExecutionInfos.cpp ${files})
target_link_libraries(${EXECUTION_INFOS_TARGET} ${GEGELATI_LIBRARIES})

set(VALIDATION_TARGET Validation)
add_executable(${VALIDATION_TARGET} src/mainValidation.cpp ${files})
target_link_libraries(${VALIDATION_TARGET} ${GEGELATI_LIBRARIES})

set(SEEDS_GRAPH_TRAVERSAL_TARGET SeedsGraphTraversal)
add_executable(${SEEDS_GRAPH_TRAVERSAL_TARGET} src/mainSeedsGraphTraversal.cpp ${files})
target_link_libraries(${SEEDS_GRAPH_TRAVERSAL_TARGET} ${GEGELATI_LIBRARIES})


# Test variables
message("Project configuration :")
message("Build type : ${CMAKE_BUILD_TYPE}")
message("Source directory : ${CMAKE_CURRENT_SOURCE_DIR}")
message("Binary directory : ${CMAKE_BINARY_DIR}")
