#!/usr/bin/bash

# Generate the CodeGen files for all pendulum TPG that are in subfolders of the TPG directory.
# This script uses the Generator C++ target of the Trainer-Generator directory.

# function to check return of previous command
checkExitStatus() {
    code=$?
    if [[ $code -ne 0 ]]
    then
        printf "\033[1;91mERROR\033[0m --- Something wrong hapenned, last exit code is $code, exiting script\n"
        exit 1
    fi
}

# check whether the specified dir is matching criterias. The dir exists and contains the required files.
# The exact criterias are specified under TPG/README.md
checkValidDirectory(){
    local d=$1

    [ $# -ne 0 ] && [ -d "$d" ] && 
        ! [ -f "$d/CodeGen/TPGGraph.c" ] && ! [ -f "$d/CodeGen/TPGGraph.h" ] && 
        ! [ -f "$d/CodeGen/TPGprograms.c" ] && ! [ -f "$d/CodeGen/TPGprograms.h" ] &&
        [ -f "$d/CodeGen/pendulumLE.cpp" ] && [ -f "$d/CodeGen/pendulumLE.h" ] && 
        [ -f "$d/CodeGen/instructions.cpp" ] && [ -f "$d/CodeGen/instructions.h" ] && 
        [ -f "$d/CodeGen/params.json" ] && [ -f "$d/CodeGen/out_best.dot" ] 

    return  # Last evaluated logical expression stored its "result code" in $?, which is returned by return
}


SCRIPT_DIR=$(cd $(dirname "${BASH_SOURCE[0]}") && pwd) # get the absolute path of the calling script
cd $SCRIPT_DIR/../TPG     # TPG/

# CMake configuration
rm -r ../Trainer-Generator/bin
mkdir ../Trainer-Generator/bin
cmake -S ../Trainer-Generator -B ../Trainer-Generator/bin
checkExitStatus

dirs=$(ls)
for d in $dirs
do

    if (checkValidDirectory $d)
    then
        printf "\033[1;36mGenerating CodeGen for $d\n\033[0m"

        # Using Generator target of the Trainer-Genertor C++ project

        # Copying files
        cp $d/CodeGen/instructions.cpp ../Trainer-Generator/src/
        checkExitStatus

        cp $d/CodeGen/instructions.h ../Trainer-Generator/src/
        checkExitStatus

        cp $d/CodeGen/pendulumLE.cpp ../Trainer-Generator/src/
        checkExitStatus

        cp $d/CodeGen/pendulumLE.h ../Trainer-Generator/src/
        checkExitStatus

        # Building target
        cmake --build ../Trainer-Generator/bin --target Generator
        checkExitStatus
        echo

        # Do code generation
        ../Trainer-Generator/bin/Release/Generator $d/CodeGen/out_best.dot
        checkExitStatus
        echo

        printf "\033[1;36mSuccessful code generation for $d\n\033[0m"
    elif [ -d $d ]
    then
        printf "\033[1;36mSkip $d (not all required files or TPG already generated)\n\033[0m"
    fi

done