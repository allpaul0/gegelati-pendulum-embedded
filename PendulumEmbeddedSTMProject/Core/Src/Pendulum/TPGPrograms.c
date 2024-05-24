/**
 * File generated with GEGELATI v1.3.1
 * On the 2024-04-30 11:04:22
 * With the CodeGen::ProgramGenerationEngine.
 */

#include "TPGPrograms.h"
#include "externHeader.h"
#include <stdint.h>
extern double* in1;

double P0(){
	double reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int32_t cst[5] = {10, -1, -1, -8, -10};
	{
		double op0 = reg[5];
		double op1 = in1[1];
		reg[1] = op0 - op1;
	}
	{
		double op0 = in1[1];
		double op1 = reg[1];
		reg[0] = ((op0) < (op1)) ? (op1) : (op0);
	}
	return reg[0];
}

double P1(){
	double reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int32_t cst[5] = {4, 9, -8, 10, 1};
	return reg[0];
}

double P2(){
	double reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int32_t cst[5] = {-7, -6, -4, -8, -9};
	{
		double op0 = reg[0];
		double op1 = reg[2];
		reg[5] = op0 * op1;
	}
	{
		double op0 = reg[5];
		double op1 = in1[1];
		reg[0] = ((op0) < (op1)) ? (op1) : (op0);
	}
	return reg[0];
}

double P3(){
	double reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int32_t cst[5] = {-2, 0, -7, -3, 5};
	{
		double op0 = in1[0];
		double op1 = in1[0];
		reg[0] = ((op0) < (op1)) ? (op1) : (op0);
	}
	return reg[0];
}

double P4(){
	double reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int32_t cst[5] = {6, 2, 3, 4, 10};
	{
		double op0 = in1[1];
		double op1 = in1[1];
		reg[6] = f_div(op0, op1);
	}
	{
		double op0 = reg[6];
		double op1 = in1[1];
		reg[0] = op0 - op1;
	}
	return reg[0];
}

double P5(){
	double reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int32_t cst[5] = {-9, -9, 7, -3, -4};
	{
		double op0 = in1[0];
		double op1 = in1[1];
		reg[0] = op0 - op1;
	}
	return reg[0];
}

double P6(){
	double reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int32_t cst[5] = {10, -6, -7, 9, -3};
	{
		double op0 = in1[1];
		double op1 = in1[1];
		reg[4] = op0 * op1;
	}
	{
		double op0 = in1[1];
		double op1 = reg[4];
		reg[7] = ((op0) < (op1)) ? (op1) : (op0);
	}
	{
		double op0 = reg[7];
		double op1 = in1[1];
		reg[0] = op0 + op1;
	}
	return reg[0];
}

double P7(){
	double reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int32_t cst[5] = {-9, -9, 7, -3, -3};
	{
		double op0 = reg[4];
		double op1 = reg[4];
		reg[6] = op0 + op1;
	}
	{
		double op0 = reg[6];
		double op1 = in1[1];
		reg[5] = f_div(op0, op1);
	}
	{
		double op0 = reg[5];
		double op1 = in1[0];
		reg[0] = ((op0) < (op1)) ? (op1) : (op0);
	}
	return reg[0];
}

double P8(){
	double reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int32_t cst[5] = {10, 5, -7, 9, -3};
	{
		double op0 = in1[1];
		double op1 = in1[1];
		reg[4] = op0 * op1;
	}
	{
		double op0 = reg[4];
		double op1 = reg[4];
		reg[0] = ((op0) < (op1)) ? (op1) : (op0);
	}
	return reg[0];
}

double P9(){
	double reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int32_t cst[5] = {-10, -9, -1, 9, 4};
	{
		double op0 = in1[1];
		double op1 = in1[1];
		reg[4] = ((op0) < (op1)) ? (op1) : (op0);
	}
	{
		double op0 = in1[0];
		double op1 = reg[4];
		reg[0] = ((op0) < (op1)) ? (op1) : (op0);
	}
	return reg[0];
}

double P10(){
	double reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int32_t cst[5] = {-9, -4, -2, 9, -8};
	{
		double op0 = in1[1];
		double op1 = in1[1];
		reg[6] = op0 + op1;
	}
	{
		double op0 = in1[0];
		double op1 = reg[6];
		reg[0] = op0 - op1;
	}
	return reg[0];
}

double P11(){
	double reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int32_t cst[5] = {1, -5, 3, 8, 0};
	{
		double op0 = reg[6];
		double op1 = in1[0];
		reg[3] = op0 + op1;
	}
	{
		double op0 = reg[3];
		double op1 = in1[1];
		reg[5] = op0 - op1;
	}
	{
		double op0 = reg[5];
		double op1 = reg[5];
		reg[0] = op0 * op1;
	}
	return reg[0];
}

double P12(){
	double reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int32_t cst[5] = {4, 4, -8, -4, -9};
	{
		double op0 = in1[1];
		double op1 = in1[1];
		reg[0] = op0 * op1;
	}
	return reg[0];
}

double P13(){
	double reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int32_t cst[5] = {3, 1, -8, -2, -2};
	{
		double op0 = in1[0];
		double op1 = in1[0];
		reg[1] = op0 + op1;
	}
	{
		double op0 = in1[1];
		double op1 = in1[1];
		reg[6] = op0 - op1;
	}
	{
		double op0 = in1[1];
		double op1 = reg[6];
		reg[2] = ((op0) < (op1)) ? (op1) : (op0);
	}
	{
		double op0 = reg[1];
		double op1 = in1[0];
		reg[4] = ((op0) < (op1)) ? (op1) : (op0);
	}
	{
		double op0 = reg[2];
		double op1 = reg[4];
		reg[0] = op0 * op1;
	}
	return reg[0];
}

double P14(){
	double reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int32_t cst[5] = {-7, 6, -8, 8, -7};
	{
		double op0 = in1[0];
		double op1 = in1[0];
		reg[0] = ((op0) < (op1)) ? (op1) : (op0);
	}
	{
		double op0 = in1[0];
		double op1 = reg[0];
		reg[2] = op0 + op1;
	}
	{
		double op0 = reg[2];
		double op1 = in1[1];
		reg[7] = op0 + op1;
	}
	{
		double op0 = in1[1];
		double op1 = in1[0];
		reg[3] = ((op0) < (op1)) ? (op1) : (op0);
	}
	{
		double op0 = in1[0];
		double op1 = reg[3];
		reg[3] = ((op0) < (op1)) ? (op1) : (op0);
	}
	{
		double op0 = reg[3];
		double op1 = reg[7];
		reg[0] = op0 * op1;
	}
	return reg[0];
}

double P15(){
	double reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int32_t cst[5] = {-6, 0, 6, -4, 1};
	{
		double op0 = in1[1];
		double op1 = in1[1];
		reg[3] = ((op0) < (op1)) ? (op1) : (op0);
	}
	{
		double op0 = reg[3];
		double op1 = reg[5];
		reg[3] = ((op0) < (op1)) ? (op1) : (op0);
	}
	{
		double op0 = reg[3];
		double op1 = in1[0];
		reg[0] = ((op0) < (op1)) ? (op1) : (op0);
	}
	return reg[0];
}

double P16(){
	double reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int32_t cst[5] = {5, 1, -7, 1, -3};
	{
		double op0 = in1[1];
		double op1 = reg[6];
		reg[1] = op0 * op1;
	}
	{
		double op0 = in1[1];
		double op1 = reg[3];
		reg[0] = ((op0) < (op1)) ? (op1) : (op0);
	}
	{
		double op0 = reg[0];
		double op1 = reg[1];
		reg[1] = op0 + op1;
	}
	{
		double op0 = in1[0];
		double op1 = in1[0];
		reg[4] = op0 + op1;
	}
	{
		double op0 = reg[1];
		double op1 = in1[0];
		reg[3] = ((op0) < (op1)) ? (op1) : (op0);
	}
	{
		double op0 = in1[0];
		double op1 = in1[0];
		reg[7] = ((op0) < (op1)) ? (op1) : (op0);
	}
	{
		double op0 = reg[3];
		double op1 = reg[4];
		reg[2] = op0 * op1;
	}
	{
		double op0 = reg[7];
		double op1 = reg[3];
		reg[6] = op0 + op1;
	}
	{
		double op0 = reg[2];
		double op1 = reg[6];
		reg[0] = op0 * op1;
	}
	return reg[0];
}

double P17(){
	double reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int32_t cst[5] = {2, 6, 0, 8, -7};
	{
		double op0 = in1[0];
		double op1 = in1[0];
		reg[0] = ((op0) < (op1)) ? (op1) : (op0);
	}
	{
		double op0 = in1[0];
		double op1 = reg[0];
		reg[2] = op0 + op1;
	}
	{
		double op0 = reg[2];
		double op1 = reg[3];
		reg[7] = op0 + op1;
	}
	{
		double op0 = in1[1];
		double op1 = in1[0];
		reg[3] = ((op0) < (op1)) ? (op1) : (op0);
	}
	{
		double op0 = reg[3];
		double op1 = reg[7];
		reg[0] = op0 * op1;
	}
	return reg[0];
}

double P18(){
	double reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int32_t cst[5] = {10, 0, 10, 4, -10};
	{
		double op0 = in1[1];
		double op1 = in1[0];
		reg[0] = ((op0) < (op1)) ? (op1) : (op0);
	}
	return reg[0];
}

double P19(){
	double reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int32_t cst[5] = {7, 3, 5, 7, 4};
	{
		double op0 = in1[1];
		double op1 = in1[1];
		reg[7] = op0 * op1;
	}
	{
		double op0 = reg[7];
		double op1 = reg[7];
		reg[0] = op0 * op1;
	}
	return reg[0];
}

double P20(){
	double reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int32_t cst[5] = {5, 1, 10, 1, -3};
	{
		double op0 = reg[3];
		double op1 = reg[6];
		reg[0] = f_div(op0, op1);
	}
	{
		double op0 = in1[1];
		double op1 = reg[6];
		reg[1] = op0 * op1;
	}
	{
		double op0 = reg[0];
		double op1 = reg[1];
		reg[1] = op0 + op1;
	}
	{
		double op0 = in1[0];
		double op1 = in1[0];
		reg[4] = op0 + op1;
	}
	{
		double op0 = reg[1];
		double op1 = in1[0];
		reg[3] = ((op0) < (op1)) ? (op1) : (op0);
	}
	{
		double op0 = in1[0];
		double op1 = in1[0];
		reg[7] = ((op0) < (op1)) ? (op1) : (op0);
	}
	{
		double op0 = reg[3];
		double op1 = reg[4];
		reg[2] = op0 * op1;
	}
	{
		double op0 = reg[7];
		double op1 = reg[3];
		reg[6] = op0 + op1;
	}
	{
		double op0 = reg[2];
		double op1 = reg[6];
		reg[0] = op0 * op1;
	}
	return reg[0];
}

double P21(){
	double reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int32_t cst[5] = {-10, -3, -5, 2, 4};
	{
		double op0 = reg[6];
		double op1 = in1[0];
		reg[0] = op0 - op1;
	}
	return reg[0];
}

double P22(){
	double reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int32_t cst[5] = {-7, 0, -3, 10, -7};
	{
		double op0 = in1[0];
		double op1 = in1[1];
		reg[6] = op0 * op1;
	}
	{
		double op0 = reg[6];
		double op1 = in1[0];
		reg[4] = op0 + op1;
	}
	{
		double op0 = in1[0];
		double op1 = reg[4];
		reg[0] = op0 + op1;
	}
	return reg[0];
}

double P23(){
	double reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int32_t cst[5] = {-10, -5, 8, -8, -5};
	{
		double op0 = in1[0];
		double op1 = in1[1];
		reg[5] = op0 + op1;
	}
	{
		double op0 = reg[5];
		double op1 = in1[1];
		reg[0] = f_div(op0, op1);
	}
	return reg[0];
}

double P24(){
	double reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int32_t cst[5] = {-7, -8, -8, -8, 1};
	{
		double op0 = in1[0];
		double op1 = reg[6];
		reg[2] = op0 - op1;
	}
	{
		double op0 = in1[1];
		double op1 = reg[2];
		reg[7] = op0 - op1;
	}
	{
		double op0 = reg[7];
		double op1 = reg[7];
		reg[2] = f_div(op0, op1);
	}
	{
		double op0 = reg[7];
		double op1 = reg[2];
		reg[5] = op0 - op1;
	}
	{
		double op0 = reg[5];
		double op1 = in1[1];
		reg[0] = op0 * op1;
	}
	return reg[0];
}

double P25(){
	double reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int32_t cst[5] = {-1, 10, -3, -2, 9};
	{
		double op0 = in1[1];
		double op1 = in1[1];
		reg[4] = op0 + op1;
	}
	{
		double op0 = reg[4];
		double op1 = in1[1];
		reg[0] = op0 + op1;
	}
	return reg[0];
}

double P26(){
	double reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int32_t cst[5] = {-5, -3, -7, -2, 10};
	{
		double op0 = in1[0];
		double op1 = in1[0];
		reg[0] = op0 + op1;
	}
	return reg[0];
}

double P27(){
	double reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int32_t cst[5] = {8, 0, 4, 4, -10};
	{
		double op0 = reg[5];
		double op1 = in1[0];
		reg[2] = op0 + op1;
	}
	{
		double op0 = in1[0];
		double op1 = reg[2];
		reg[7] = op0 * op1;
	}
	{
		double op0 = reg[7];
		double op1 = in1[1];
		reg[0] = op0 - op1;
	}
	return reg[0];
}

double P28(){
	double reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int32_t cst[5] = {6, 8, 0, 5, 4};
	{
		double op0 = in1[0];
		double op1 = in1[0];
		reg[7] = op0 * op1;
	}
	{
		double op0 = reg[7];
		double op1 = in1[1];
		reg[6] = ((op0) < (op1)) ? (op1) : (op0);
	}
	{
		double op0 = reg[6];
		double op1 = in1[0];
		reg[0] = op0 + op1;
	}
	return reg[0];
}

double P29(){
	double reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int32_t cst[5] = {8, 9, -7, 10, -9};
	{
		double op0 = reg[6];
		double op1 = in1[0];
		reg[0] = op0 + op1;
	}
	{
		double op0 = in1[0];
		double op1 = reg[0];
		reg[1] = op0 + op1;
	}
	{
		double op0 = in1[0];
		double op1 = in1[0];
		reg[3] = op0 + op1;
	}
	{
		double op0 = reg[3];
		double op1 = reg[1];
		reg[0] = op0 * op1;
	}
	return reg[0];
}

double P30(){
	double reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int32_t cst[5] = {-1, 1, 9, -2, 10};
	{
		double op0 = in1[0];
		double op1 = in1[1];
		reg[1] = op0 + op1;
	}
	{
		double op0 = reg[1];
		double op1 = in1[0];
		reg[4] = ((op0) < (op1)) ? (op1) : (op0);
	}
	{
		double op0 = in1[1];
		double op1 = reg[4];
		reg[0] = op0 * op1;
	}
	return reg[0];
}

double P31(){
	double reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int32_t cst[5] = {-2, -6, 2, -4, -7};
	{
		double op0 = in1[0];
		double op1 = reg[2];
		reg[6] = f_div(op0, op1);
	}
	{
		double op0 = in1[1];
		double op1 = in1[0];
		reg[1] = f_div(op0, op1);
	}
	{
		double op0 = in1[1];
		double op1 = in1[1];
		reg[2] = f_div(op0, op1);
	}
	{
		double op0 = reg[2];
		double op1 = reg[1];
		reg[0] = op0 - op1;
	}
	{
		double op0 = reg[6];
		double op1 = reg[0];
		reg[0] = op0 - op1;
	}
	return reg[0];
}

double P32(){
	double reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int32_t cst[5] = {1, -6, 9, -8, 0};
	{
		double op0 = in1[0];
		double op1 = in1[0];
		reg[2] = op0 * op1;
	}
	{
		double op0 = in1[1];
		double op1 = reg[5];
		reg[1] = op0 * op1;
	}
	{
		double op0 = reg[2];
		double op1 = reg[1];
		reg[3] = ((op0) < (op1)) ? (op1) : (op0);
	}
	{
		double op0 = in1[0];
		double op1 = reg[3];
		reg[2] = op0 * op1;
	}
	{
		double op0 = reg[2];
		double op1 = in1[0];
		reg[5] = ((op0) < (op1)) ? (op1) : (op0);
	}
	{
		double op0 = reg[5];
		double op1 = in1[1];
		reg[0] = op0 - op1;
	}
	return reg[0];
}

double P33(){
	double reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int32_t cst[5] = {-8, -2, -4, -5, -2};
	{
		double op0 = in1[1];
		double op1 = in1[0];
		reg[0] = op0 - op1;
	}
	{
		double op0 = reg[0];
		double op1 = in1[0];
		reg[3] = op0 - op1;
	}
	{
		double op0 = reg[3];
		double op1 = in1[0];
		reg[4] = f_div(op0, op1);
	}
	{
		double op0 = in1[0];
		double op1 = reg[4];
		reg[0] = op0 * op1;
	}
	return reg[0];
}

double P34(){
	double reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int32_t cst[5] = {6, -8, 5, -7, 7};
	{
		double op0 = in1[0];
		double op1 = in1[1];
		reg[5] = op0 * op1;
	}
	{
		double op0 = reg[5];
		double op1 = in1[1];
		reg[3] = op0 * op1;
	}
	{
		double op0 = in1[1];
		double op1 = reg[3];
		reg[0] = op0 * op1;
	}
	return reg[0];
}

double P35(){
	double reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int32_t cst[5] = {7, -7, 10, 9, -10};
	{
		double op0 = in1[1];
		double op1 = in1[0];
		reg[5] = op0 - op1;
	}
	{
		double op0 = reg[5];
		double op1 = reg[5];
		reg[3] = op0 + op1;
	}
	{
		double op0 = reg[3];
		double op1 = in1[1];
		reg[5] = op0 * op1;
	}
	{
		double op0 = in1[1];
		double op1 = reg[5];
		reg[0] = ((op0) < (op1)) ? (op1) : (op0);
	}
	return reg[0];
}

double P36(){
	double reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int32_t cst[5] = {10, -2, -1, 2, -7};
	{
		double op0 = reg[3];
		double op1 = in1[1];
		reg[0] = ((op0) < (op1)) ? (op1) : (op0);
	}
	{
		double op0 = in1[1];
		double op1 = in1[0];
		reg[7] = op0 - op1;
	}
	{
		double op0 = reg[7];
		double op1 = reg[0];
		reg[0] = op0 + op1;
	}
	return reg[0];
}

double P37(){
	double reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int32_t cst[5] = {7, -4, -6, 9, -7};
	{
		double op0 = in1[0];
		double op1 = in1[0];
		reg[0] = f_div(op0, op1);
	}
	return reg[0];
}

double P38(){
	double reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int32_t cst[5] = {1, 10, -1, -10, -3};
	{
		double op0 = in1[1];
		double op1 = in1[1];
		reg[0] = f_div(op0, op1);
	}
	return reg[0];
}

double P39(){
	double reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int32_t cst[5] = {-9, -10, 0, -5, 4};
	{
		double op0 = in1[0];
		double op1 = in1[1];
		reg[2] = op0 + op1;
	}
	{
		double op0 = reg[4];
		double op1 = in1[0];
		reg[4] = op0 - op1;
	}
	{
		double op0 = reg[4];
		double op1 = reg[2];
		reg[0] = f_div(op0, op1);
	}
	return reg[0];
}

double P40(){
	double reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int32_t cst[5] = {-9, 7, -3, 9, 10};
	{
		double op0 = in1[0];
		double op1 = in1[0];
		reg[5] = op0 * op1;
	}
	{
		double op0 = in1[0];
		double op1 = reg[5];
		reg[2] = op0 * op1;
	}
	{
		double op0 = in1[1];
		double op1 = reg[2];
		reg[0] = op0 - op1;
	}
	return reg[0];
}
