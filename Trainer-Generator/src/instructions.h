/**
* \file instruction.cpp
* \author Karol Desnos
* \license CeCILL-C
* 
* The purpose of this file is to provide a utility function
* filling a given Instructions::Set with instruction.
* The objective of this file is to specify the instructions
* used in all pendulum related project in a single place.
*/

#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include <gegelati.h>
#include "approximateComputingTools.h"

/**
* Fill the given instruction set.
*/
void fillInstructionSet(Instructions::Set& set);

/**
* Delete the dynamically allocated instructions.
*/
void deleteInstructions(Instructions::Set& set);

#endif