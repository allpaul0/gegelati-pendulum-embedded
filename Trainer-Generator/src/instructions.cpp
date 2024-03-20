/**
* \file instruction.cpp
* \author Karol Desnos
* \license CeCILL-C
*/

#define _USE_MATH_DEFINES  To get M_PI
#include <math.h>
#include "instructions.h"
#include "approximateComputingTools.h"

void fillInstructionSet(Instructions::Set& set) {
	auto minus = [](double a, double b) -> double { return double(int(a) - int(b)); };
	auto add = [](double a, double b) -> double { return double(int(a) + int(b)); };
	auto mult = [](double a, double b) -> double { return double(int(a) * int(b)); };
	auto div = [](double a, double b) -> double { return double(f_div(int(a), int(b))); };
	auto max = [](double a, double b) -> double { return double(std::max(int(a), int(b))); };
	auto pow2 = [](double a) -> double { return double(f_pow2(int(a))); };
	auto log2 = [](double a) -> double { return double(f_log2(int(a))); };

	set.add(*(new Instructions::LambdaInstruction<double, double>(minus, "$0 = $1 - $2;")));
	set.add(*(new Instructions::LambdaInstruction<double, double>(add, "$0 = $1 + $2;")));
	set.add(*(new Instructions::LambdaInstruction<double, double>(mult, "$0 = $1 * $2;")));
	set.add(*(new Instructions::LambdaInstruction<double, double>(div, "$0 = f_div($1, $2);")));
	set.add(*(new Instructions::LambdaInstruction<double, double>(max, "$0 = (($1) < ($2)) ? ($2) : ($1);")));
	set.add(*(new Instructions::LambdaInstruction<double>(pow2 , "$0 = f_pow2($1);")));
	set.add(*(new Instructions::LambdaInstruction<double>(log2, "$0 = f_log2($1);")));
}

void deleteInstructions(Instructions::Set& set)
{
	for (unsigned int i = 0; i < set.getNbInstructions(); i++) {
		delete (&set.getInstruction(i));
	}
}