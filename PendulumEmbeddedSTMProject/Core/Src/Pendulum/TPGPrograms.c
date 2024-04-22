/**
 * File generated with GEGELATI v1.3.1
 * On the 2024-04-19 16:32:58
 * With the CodeGen::ProgramGenerationEngine.
 */

#include "TPGPrograms.h"
#include "externHeader.h"
#include <stdint.h>
extern int* in1;

int P0(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int32_t cst[5] = {10, -1, -1, -8, -10};
	{
		int op0 = reg[5];
		int op1 = in1[1];
		reg[1] = op0 - op1;
	}
	{
		int op0 = in1[1];
		int op1 = reg[1];
		reg[0] = ((op0) < (op1)) ? (op1) : (op0);
	}
	return reg[0];
}

int P1(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int32_t cst[5] = {4, 9, -8, 10, 1};
	return reg[0];
}

int P2(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int32_t cst[5] = {-7, -6, -4, -8, -9};
	{
		int op0 = reg[0];
		int op1 = reg[2];
		reg[5] = op0 * op1;
	}
	{
		int op0 = reg[5];
		int op1 = in1[1];
		reg[0] = ((op0) < (op1)) ? (op1) : (op0);
	}
	return reg[0];
}

int P3(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int32_t cst[5] = {-2, 0, -7, -3, 5};
	{
		int op0 = in1[0];
		int op1 = in1[0];
		reg[0] = ((op0) < (op1)) ? (op1) : (op0);
	}
	return reg[0];
}

int P4(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int32_t cst[5] = {6, 2, 3, 4, 10};
	{
		int op0 = in1[1];
		int op1 = in1[1];
		reg[6] = f_div(op0, op1);
	}
	{
		int op0 = reg[6];
		int op1 = in1[1];
		reg[0] = op0 - op1;
	}
	return reg[0];
}

int P5(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int32_t cst[5] = {-9, -9, 7, -3, -4};
	{
		int op0 = in1[0];
		int op1 = in1[1];
		reg[0] = op0 - op1;
	}
	return reg[0];
}

int P6(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int32_t cst[5] = {10, -6, -7, 9, -3};
	{
		int op0 = in1[1];
		int op1 = in1[1];
		reg[4] = op0 * op1;
	}
	{
		int op0 = in1[1];
		int op1 = reg[4];
		reg[7] = ((op0) < (op1)) ? (op1) : (op0);
	}
	{
		int op0 = reg[7];
		int op1 = in1[1];
		reg[0] = op0 + op1;
	}
	return reg[0];
}

int P7(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int32_t cst[5] = {-9, -9, 7, -3, -3};
	{
		int op0 = reg[4];
		int op1 = reg[4];
		reg[6] = op0 + op1;
	}
	{
		int op0 = reg[6];
		int op1 = in1[1];
		reg[5] = f_div(op0, op1);
	}
	{
		int op0 = reg[5];
		int op1 = in1[0];
		reg[0] = ((op0) < (op1)) ? (op1) : (op0);
	}
	return reg[0];
}

int P8(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int32_t cst[5] = {10, 5, -7, 9, -3};
	{
		int op0 = in1[1];
		int op1 = in1[1];
		reg[4] = op0 * op1;
	}
	{
		int op0 = reg[4];
		int op1 = reg[4];
		reg[0] = ((op0) < (op1)) ? (op1) : (op0);
	}
	return reg[0];
}

int P9(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int32_t cst[5] = {-10, -9, -1, 9, 4};
	{
		int op0 = in1[1];
		int op1 = in1[1];
		reg[4] = ((op0) < (op1)) ? (op1) : (op0);
	}
	{
		int op0 = in1[0];
		int op1 = reg[4];
		reg[0] = ((op0) < (op1)) ? (op1) : (op0);
	}
	return reg[0];
}

int P10(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int32_t cst[5] = {-9, -4, -2, 9, -8};
	{
		int op0 = in1[1];
		int op1 = in1[1];
		reg[6] = op0 + op1;
	}
	{
		int op0 = in1[0];
		int op1 = reg[6];
		reg[0] = op0 - op1;
	}
	return reg[0];
}

int P11(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int32_t cst[5] = {1, -5, 3, 8, 0};
	{
		int op0 = reg[6];
		int op1 = in1[0];
		reg[3] = op0 + op1;
	}
	{
		int op0 = reg[3];
		int op1 = in1[1];
		reg[5] = op0 - op1;
	}
	{
		int op0 = reg[5];
		int op1 = reg[5];
		reg[0] = op0 * op1;
	}
	return reg[0];
}

int P12(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int32_t cst[5] = {4, 4, -8, -4, -9};
	{
		int op0 = in1[1];
		int op1 = in1[1];
		reg[0] = op0 * op1;
	}
	return reg[0];
}

int P13(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int32_t cst[5] = {3, 1, -8, -2, -2};
	{
		int op0 = in1[0];
		int op1 = in1[0];
		reg[1] = op0 + op1;
	}
	{
		int op0 = in1[1];
		int op1 = in1[1];
		reg[6] = op0 - op1;
	}
	{
		int op0 = in1[1];
		int op1 = reg[6];
		reg[2] = ((op0) < (op1)) ? (op1) : (op0);
	}
	{
		int op0 = reg[1];
		int op1 = in1[0];
		reg[4] = ((op0) < (op1)) ? (op1) : (op0);
	}
	{
		int op0 = reg[2];
		int op1 = reg[4];
		reg[0] = op0 * op1;
	}
	return reg[0];
}

int P14(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int32_t cst[5] = {-7, 6, -8, 8, -7};
	{
		int op0 = in1[0];
		int op1 = in1[0];
		reg[0] = ((op0) < (op1)) ? (op1) : (op0);
	}
	{
		int op0 = in1[0];
		int op1 = reg[0];
		reg[2] = op0 + op1;
	}
	{
		int op0 = reg[2];
		int op1 = in1[1];
		reg[7] = op0 + op1;
	}
	{
		int op0 = in1[1];
		int op1 = in1[0];
		reg[3] = ((op0) < (op1)) ? (op1) : (op0);
	}
	{
		int op0 = in1[0];
		int op1 = reg[3];
		reg[3] = ((op0) < (op1)) ? (op1) : (op0);
	}
	{
		int op0 = reg[3];
		int op1 = reg[7];
		reg[0] = op0 * op1;
	}
	return reg[0];
}

int P15(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int32_t cst[5] = {-6, 0, 6, -4, 1};
	{
		int op0 = in1[1];
		int op1 = in1[1];
		reg[3] = ((op0) < (op1)) ? (op1) : (op0);
	}
	{
		int op0 = reg[3];
		int op1 = reg[5];
		reg[3] = ((op0) < (op1)) ? (op1) : (op0);
	}
	{
		int op0 = reg[3];
		int op1 = in1[0];
		reg[0] = ((op0) < (op1)) ? (op1) : (op0);
	}
	return reg[0];
}

int P16(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int32_t cst[5] = {5, 1, -7, 1, -3};
	{
		int op0 = in1[1];
		int op1 = reg[6];
		reg[1] = op0 * op1;
	}
	{
		int op0 = in1[1];
		int op1 = reg[3];
		reg[0] = ((op0) < (op1)) ? (op1) : (op0);
	}
	{
		int op0 = reg[0];
		int op1 = reg[1];
		reg[1] = op0 + op1;
	}
	{
		int op0 = in1[0];
		int op1 = in1[0];
		reg[4] = op0 + op1;
	}
	{
		int op0 = reg[1];
		int op1 = in1[0];
		reg[3] = ((op0) < (op1)) ? (op1) : (op0);
	}
	{
		int op0 = in1[0];
		int op1 = in1[0];
		reg[7] = ((op0) < (op1)) ? (op1) : (op0);
	}
	{
		int op0 = reg[3];
		int op1 = reg[4];
		reg[2] = op0 * op1;
	}
	{
		int op0 = reg[7];
		int op1 = reg[3];
		reg[6] = op0 + op1;
	}
	{
		int op0 = reg[2];
		int op1 = reg[6];
		reg[0] = op0 * op1;
	}
	return reg[0];
}

int P17(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int32_t cst[5] = {2, 6, 0, 8, -7};
	{
		int op0 = in1[0];
		int op1 = in1[0];
		reg[0] = ((op0) < (op1)) ? (op1) : (op0);
	}
	{
		int op0 = in1[0];
		int op1 = reg[0];
		reg[2] = op0 + op1;
	}
	{
		int op0 = reg[2];
		int op1 = reg[3];
		reg[7] = op0 + op1;
	}
	{
		int op0 = in1[1];
		int op1 = in1[0];
		reg[3] = ((op0) < (op1)) ? (op1) : (op0);
	}
	{
		int op0 = reg[3];
		int op1 = reg[7];
		reg[0] = op0 * op1;
	}
	return reg[0];
}

int P18(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int32_t cst[5] = {10, 0, 10, 4, -10};
	{
		int op0 = in1[1];
		int op1 = in1[0];
		reg[0] = ((op0) < (op1)) ? (op1) : (op0);
	}
	return reg[0];
}

int P19(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int32_t cst[5] = {7, 3, 5, 7, 4};
	{
		int op0 = in1[1];
		int op1 = in1[1];
		reg[7] = op0 * op1;
	}
	{
		int op0 = reg[7];
		int op1 = reg[7];
		reg[0] = op0 * op1;
	}
	return reg[0];
}

int P20(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int32_t cst[5] = {5, 1, 10, 1, -3};
	{
		int op0 = reg[3];
		int op1 = reg[6];
		reg[0] = f_div(op0, op1);
	}
	{
		int op0 = in1[1];
		int op1 = reg[6];
		reg[1] = op0 * op1;
	}
	{
		int op0 = reg[0];
		int op1 = reg[1];
		reg[1] = op0 + op1;
	}
	{
		int op0 = in1[0];
		int op1 = in1[0];
		reg[4] = op0 + op1;
	}
	{
		int op0 = reg[1];
		int op1 = in1[0];
		reg[3] = ((op0) < (op1)) ? (op1) : (op0);
	}
	{
		int op0 = in1[0];
		int op1 = in1[0];
		reg[7] = ((op0) < (op1)) ? (op1) : (op0);
	}
	{
		int op0 = reg[3];
		int op1 = reg[4];
		reg[2] = op0 * op1;
	}
	{
		int op0 = reg[7];
		int op1 = reg[3];
		reg[6] = op0 + op1;
	}
	{
		int op0 = reg[2];
		int op1 = reg[6];
		reg[0] = op0 * op1;
	}
	return reg[0];
}

int P21(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int32_t cst[5] = {-10, -3, -5, 2, 4};
	{
		int op0 = reg[6];
		int op1 = in1[0];
		reg[0] = op0 - op1;
	}
	return reg[0];
}

int P22(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int32_t cst[5] = {-7, 0, -3, 10, -7};
	{
		int op0 = in1[0];
		int op1 = in1[1];
		reg[6] = op0 * op1;
	}
	{
		int op0 = reg[6];
		int op1 = in1[0];
		reg[4] = op0 + op1;
	}
	{
		int op0 = in1[0];
		int op1 = reg[4];
		reg[0] = op0 + op1;
	}
	return reg[0];
}

int P23(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int32_t cst[5] = {-10, -5, 8, -8, -5};
	{
		int op0 = in1[0];
		int op1 = in1[1];
		reg[5] = op0 + op1;
	}
	{
		int op0 = reg[5];
		int op1 = in1[1];
		reg[0] = f_div(op0, op1);
	}
	return reg[0];
}

int P24(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int32_t cst[5] = {-7, -8, -8, -8, 1};
	{
		int op0 = in1[0];
		int op1 = reg[6];
		reg[2] = op0 - op1;
	}
	{
		int op0 = in1[1];
		int op1 = reg[2];
		reg[7] = op0 - op1;
	}
	{
		int op0 = reg[7];
		int op1 = reg[7];
		reg[2] = f_div(op0, op1);
	}
	{
		int op0 = reg[7];
		int op1 = reg[2];
		reg[5] = op0 - op1;
	}
	{
		int op0 = reg[5];
		int op1 = in1[1];
		reg[0] = op0 * op1;
	}
	return reg[0];
}

int P25(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int32_t cst[5] = {-1, 10, -3, -2, 9};
	{
		int op0 = in1[1];
		int op1 = in1[1];
		reg[4] = op0 + op1;
	}
	{
		int op0 = reg[4];
		int op1 = in1[1];
		reg[0] = op0 + op1;
	}
	return reg[0];
}

int P26(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int32_t cst[5] = {-5, -3, -7, -2, 10};
	{
		int op0 = in1[0];
		int op1 = in1[0];
		reg[0] = op0 + op1;
	}
	return reg[0];
}

int P27(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int32_t cst[5] = {8, 0, 4, 4, -10};
	{
		int op0 = reg[5];
		int op1 = in1[0];
		reg[2] = op0 + op1;
	}
	{
		int op0 = in1[0];
		int op1 = reg[2];
		reg[7] = op0 * op1;
	}
	{
		int op0 = reg[7];
		int op1 = in1[1];
		reg[0] = op0 - op1;
	}
	return reg[0];
}

int P28(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int32_t cst[5] = {6, 8, 0, 5, 4};
	{
		int op0 = in1[0];
		int op1 = in1[0];
		reg[7] = op0 * op1;
	}
	{
		int op0 = reg[7];
		int op1 = in1[1];
		reg[6] = ((op0) < (op1)) ? (op1) : (op0);
	}
	{
		int op0 = reg[6];
		int op1 = in1[0];
		reg[0] = op0 + op1;
	}
	return reg[0];
}

int P29(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int32_t cst[5] = {8, 9, -7, 10, -9};
	{
		int op0 = reg[6];
		int op1 = in1[0];
		reg[0] = op0 + op1;
	}
	{
		int op0 = in1[0];
		int op1 = reg[0];
		reg[1] = op0 + op1;
	}
	{
		int op0 = in1[0];
		int op1 = in1[0];
		reg[3] = op0 + op1;
	}
	{
		int op0 = reg[3];
		int op1 = reg[1];
		reg[0] = op0 * op1;
	}
	return reg[0];
}

int P30(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int32_t cst[5] = {-1, 1, 9, -2, 10};
	{
		int op0 = in1[0];
		int op1 = in1[1];
		reg[1] = op0 + op1;
	}
	{
		int op0 = reg[1];
		int op1 = in1[0];
		reg[4] = ((op0) < (op1)) ? (op1) : (op0);
	}
	{
		int op0 = in1[1];
		int op1 = reg[4];
		reg[0] = op0 * op1;
	}
	return reg[0];
}

int P31(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int32_t cst[5] = {-2, -6, 2, -4, -7};
	{
		int op0 = in1[0];
		int op1 = reg[2];
		reg[6] = f_div(op0, op1);
	}
	{
		int op0 = in1[1];
		int op1 = in1[0];
		reg[1] = f_div(op0, op1);
	}
	{
		int op0 = in1[1];
		int op1 = in1[1];
		reg[2] = f_div(op0, op1);
	}
	{
		int op0 = reg[2];
		int op1 = reg[1];
		reg[0] = op0 - op1;
	}
	{
		int op0 = reg[6];
		int op1 = reg[0];
		reg[0] = op0 - op1;
	}
	return reg[0];
}

int P32(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int32_t cst[5] = {1, -6, 9, -8, 0};
	{
		int op0 = in1[0];
		int op1 = in1[0];
		reg[2] = op0 * op1;
	}
	{
		int op0 = in1[1];
		int op1 = reg[5];
		reg[1] = op0 * op1;
	}
	{
		int op0 = reg[2];
		int op1 = reg[1];
		reg[3] = ((op0) < (op1)) ? (op1) : (op0);
	}
	{
		int op0 = in1[0];
		int op1 = reg[3];
		reg[2] = op0 * op1;
	}
	{
		int op0 = reg[2];
		int op1 = in1[0];
		reg[5] = ((op0) < (op1)) ? (op1) : (op0);
	}
	{
		int op0 = reg[5];
		int op1 = in1[1];
		reg[0] = op0 - op1;
	}
	return reg[0];
}

int P33(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int32_t cst[5] = {-8, -2, -4, -5, -2};
	{
		int op0 = in1[1];
		int op1 = in1[0];
		reg[0] = op0 - op1;
	}
	{
		int op0 = reg[0];
		int op1 = in1[0];
		reg[3] = op0 - op1;
	}
	{
		int op0 = reg[3];
		int op1 = in1[0];
		reg[4] = f_div(op0, op1);
	}
	{
		int op0 = in1[0];
		int op1 = reg[4];
		reg[0] = op0 * op1;
	}
	return reg[0];
}

int P34(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int32_t cst[5] = {6, -8, 5, -7, 7};
	{
		int op0 = in1[0];
		int op1 = in1[1];
		reg[5] = op0 * op1;
	}
	{
		int op0 = reg[5];
		int op1 = in1[1];
		reg[3] = op0 * op1;
	}
	{
		int op0 = in1[1];
		int op1 = reg[3];
		reg[0] = op0 * op1;
	}
	return reg[0];
}

int P35(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int32_t cst[5] = {7, -7, 10, 9, -10};
	{
		int op0 = in1[1];
		int op1 = in1[0];
		reg[5] = op0 - op1;
	}
	{
		int op0 = reg[5];
		int op1 = reg[5];
		reg[3] = op0 + op1;
	}
	{
		int op0 = reg[3];
		int op1 = in1[1];
		reg[5] = op0 * op1;
	}
	{
		int op0 = in1[1];
		int op1 = reg[5];
		reg[0] = ((op0) < (op1)) ? (op1) : (op0);
	}
	return reg[0];
}

int P36(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int32_t cst[5] = {10, -2, -1, 2, -7};
	{
		int op0 = reg[3];
		int op1 = in1[1];
		reg[0] = ((op0) < (op1)) ? (op1) : (op0);
	}
	{
		int op0 = in1[1];
		int op1 = in1[0];
		reg[7] = op0 - op1;
	}
	{
		int op0 = reg[7];
		int op1 = reg[0];
		reg[0] = op0 + op1;
	}
	return reg[0];
}

int P37(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int32_t cst[5] = {7, -4, -6, 9, -7};
	{
		int op0 = in1[0];
		int op1 = in1[0];
		reg[0] = f_div(op0, op1);
	}
	return reg[0];
}

int P38(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int32_t cst[5] = {1, 10, -1, -10, -3};
	{
		int op0 = in1[1];
		int op1 = in1[1];
		reg[0] = f_div(op0, op1);
	}
	return reg[0];
}

int P39(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int32_t cst[5] = {-9, -10, 0, -5, 4};
	{
		int op0 = in1[0];
		int op1 = in1[1];
		reg[2] = op0 + op1;
	}
	{
		int op0 = reg[4];
		int op1 = in1[0];
		reg[4] = op0 - op1;
	}
	{
		int op0 = reg[4];
		int op1 = reg[2];
		reg[0] = f_div(op0, op1);
	}
	return reg[0];
}

int P40(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int32_t cst[5] = {-9, 7, -3, 9, 10};
	{
		int op0 = in1[0];
		int op1 = in1[0];
		reg[5] = op0 * op1;
	}
	{
		int op0 = in1[0];
		int op1 = reg[5];
		reg[2] = op0 * op1;
	}
	{
		int op0 = in1[1];
		int op1 = reg[2];
		reg[0] = op0 - op1;
	}
	return reg[0];
}
