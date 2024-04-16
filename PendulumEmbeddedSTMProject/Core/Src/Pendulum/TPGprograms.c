/**
 * File generated with GEGELATI v1.3.1
 * On the 2024-04-10 14:16:07
 * With the CodeGen::ProgramGenerationEngine.
 */

#include "TPGprograms.h"
#include "externHeader.h"
#include <stdint.h>
extern int* in1;

int P0(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	return reg[0];
}

int P1(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = in1[1];
		int op1 = reg[1];
		reg[2] = op0 - op1;
	}
	{
		int op0 = in1[0];
		int op1 = reg[7];
		reg[0] = op0 * op1;
	}
	{
		int op0 = in1[1];
		int op1 = reg[2];
		reg[6] = op0 - op1;
	}
	{
		int op0 = reg[6];
		int op1 = reg[0];
		reg[4] = f_div(op0, op1);
	}
	{
		int op0 = in1[0];
		int op1 = reg[4];
		reg[0] = f_div(op0, op1);
	}
	return reg[0];
}

int P2(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	return reg[0];
}

int P3(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	return reg[0];
}

int P4(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = in1[0];
		int op1 = in1[0];
		reg[0] = op0 * op1;
	}
	return reg[0];
}

int P5(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = in1[0];
		int op1 = in1[1];
		reg[0] = op0 + op1;
	}
	return reg[0];
}

int P6(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = reg[3];
		int op1 = in1[1];
		reg[5] = op0 + op1;
	}
	{
		int op0 = in1[1];
		int op1 = reg[5];
		reg[0] = op0 + op1;
	}
	return reg[0];
}

int P7(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = in1[1];
		int op1 = in1[0];
		reg[6] = op0 + op1;
	}
	{
		int op0 = reg[6];
		int op1 = in1[0];
		reg[0] = f_div(op0, op1);
	}
	return reg[0];
}

int P8(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = in1[1];
		int op1 = in1[0];
		reg[1] = op0 * op1;
	}
	{
		int op0 = reg[1];
		int op1 = in1[1];
		reg[0] = op0 + op1;
	}
	return reg[0];
}

int P9(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = in1[0];
		int op1 = in1[1];
		reg[4] = f_div(op0, op1);
	}
	{
		int op0 = in1[1];
		int op1 = reg[4];
		reg[4] = f_div(op0, op1);
	}
	{
		int op0 = reg[4];
		int op1 = in1[1];
		reg[0] = op0 * op1;
	}
	return reg[0];
}

int P10(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	return reg[0];
}

int P11(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
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

int P12(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	return reg[0];
}

int P13(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = reg[3];
		int op1 = in1[1];
		reg[0] = ((op0) < (op1)) ? (op1) : (op0);
	}
	return reg[0];
}

int P14(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
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

int P15(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = in1[0];
		int op1 = in1[0];
		reg[0] = ((op0) < (op1)) ? (op1) : (op0);
	}
	return reg[0];
}

int P16(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
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

int P17(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	return reg[0];
}

int P18(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = in1[1];
		int op1 = in1[1];
		reg[0] = f_div(op0, op1);
	}
	return reg[0];
}

int P19(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
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

int P20(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = in1[0];
		int op1 = in1[1];
		reg[2] = ((op0) < (op1)) ? (op1) : (op0);
	}
	{
		int op0 = reg[2];
		int op1 = in1[1];
		reg[0] = op0 + op1;
	}
	return reg[0];
}

int P21(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = in1[1];
		int op1 = reg[0];
		reg[5] = ((op0) < (op1)) ? (op1) : (op0);
	}
	{
		int op0 = in1[1];
		int op1 = reg[5];
		reg[0] = op0 + op1;
	}
	return reg[0];
}

int P22(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = in1[0];
		int op1 = in1[1];
		reg[1] = op0 - op1;
	}
	{
		int op0 = reg[1];
		int op1 = reg[5];
		reg[6] = op0 + op1;
	}
	{
		int op0 = reg[6];
		int op1 = in1[0];
		reg[0] = op0 + op1;
	}
	return reg[0];
}

int P23(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = in1[0];
		int op1 = in1[0];
		reg[3] = op0 + op1;
	}
	{
		int op0 = reg[3];
		int op1 = reg[3];
		reg[4] = op0 + op1;
	}
	{
		int op0 = in1[1];
		int op1 = reg[4];
		reg[0] = op0 + op1;
	}
	return reg[0];
}

int P24(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = in1[1];
		int op1 = reg[4];
		reg[0] = f_div(op0, op1);
	}
	{
		int op0 = in1[1];
		int op1 = reg[0];
		reg[1] = op0 - op1;
	}
	{
		int op0 = reg[4];
		int op1 = reg[0];
		reg[2] = ((op0) < (op1)) ? (op1) : (op0);
	}
	{
		int op0 = reg[1];
		int op1 = reg[2];
		reg[0] = op0 - op1;
	}
	return reg[0];
}

int P25(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = in1[0];
		int op1 = in1[0];
		reg[0] = op0 * op1;
	}
	return reg[0];
}

int P26(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = reg[3];
		int op1 = in1[0];
		reg[0] = op0 - op1;
	}
	return reg[0];
}

int P27(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = in1[1];
		int op1 = in1[1];
		reg[4] = f_div(op0, op1);
	}
	{
		int op0 = in1[0];
		int op1 = in1[0];
		reg[5] = op0 * op1;
	}
	{
		int op0 = reg[5];
		int op1 = reg[4];
		reg[0] = ((op0) < (op1)) ? (op1) : (op0);
	}
	return reg[0];
}

int P28(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = in1[1];
		int op1 = in1[1];
		reg[0] = ((op0) < (op1)) ? (op1) : (op0);
	}
	return reg[0];
}

int P29(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = in1[0];
		int op1 = in1[0];
		reg[5] = op0 + op1;
	}
	{
		int op0 = in1[0];
		int op1 = reg[5];
		reg[0] = ((op0) < (op1)) ? (op1) : (op0);
	}
	return reg[0];
}

int P30(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = in1[0];
		int op1 = in1[0];
		reg[0] = f_div(op0, op1);
	}
	return reg[0];
}

int P31(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = reg[0];
		int op1 = reg[2];
		reg[5] = op0 * op1;
	}
	{
		int op0 = reg[3];
		int op1 = in1[0];
		reg[7] = f_div(op0, op1);
	}
	{
		int op0 = reg[7];
		int op1 = in1[1];
		reg[6] = op0 - op1;
	}
	{
		int op0 = in1[0];
		int op1 = reg[5];
		reg[3] = op0 + op1;
	}
	{
		int op0 = reg[3];
		int op1 = reg[4];
		reg[2] = ((op0) < (op1)) ? (op1) : (op0);
	}
	{
		int op0 = reg[2];
		int op1 = reg[6];
		reg[0] = op0 + op1;
	}
	return reg[0];
}

int P32(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = in1[0];
		int op1 = in1[1];
		reg[0] = op0 - op1;
	}
	return reg[0];
}

int P33(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = in1[1];
		int op1 = in1[0];
		reg[0] = f_div(op0, op1);
	}
	return reg[0];
}

int P34(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = in1[1];
		int op1 = reg[2];
		reg[7] = ((op0) < (op1)) ? (op1) : (op0);
	}
	{
		int op0 = reg[7];
		int op1 = in1[1];
		reg[0] = op0 + op1;
	}
	return reg[0];
}

int P35(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
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

int P36(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
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

int P37(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
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

int P38(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = in1[0];
		int op1 = in1[1];
		reg[4] = op0 + op1;
	}
	{
		int op0 = reg[4];
		int op1 = reg[6];
		reg[6] = op0 - op1;
	}
	{
		int op0 = reg[6];
		int op1 = in1[1];
		reg[7] = ((op0) < (op1)) ? (op1) : (op0);
	}
	{
		int op0 = in1[0];
		int op1 = reg[7];
		reg[0] = f_div(op0, op1);
	}
	return reg[0];
}

int P39(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
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

int P40(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = in1[0];
		int op1 = in1[1];
		reg[0] = f_div(op0, op1);
	}
	return reg[0];
}

int P41(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = in1[1];
		int op1 = in1[1];
		reg[4] = op0 + op1;
	}
	{
		int op0 = in1[0];
		int op1 = reg[4];
		reg[5] = f_div(op0, op1);
	}
	{
		int op0 = reg[5];
		int op1 = in1[0];
		reg[0] = op0 + op1;
	}
	return reg[0];
}

int P42(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = in1[0];
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

int P43(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
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

int P44(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = reg[6];
		int op1 = reg[0];
		reg[0] = ((op0) < (op1)) ? (op1) : (op0);
	}
	{
		int op0 = reg[7];
		int op1 = reg[7];
		reg[4] = op0 + op1;
	}
	{
		int op0 = in1[1];
		int op1 = in1[0];
		reg[6] = op0 + op1;
	}
	{
		int op0 = reg[6];
		int op1 = in1[0];
		reg[7] = ((op0) < (op1)) ? (op1) : (op0);
	}
	{
		int op0 = reg[1];
		int op1 = reg[4];
		reg[3] = op0 * op1;
	}
	{
		int op0 = reg[0];
		int op1 = reg[3];
		reg[2] = op0 * op1;
	}
	{
		int op0 = reg[7];
		int op1 = reg[2];
		reg[0] = op0 - op1;
	}
	return reg[0];
}

int P45(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
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

int P46(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = in1[1];
		int op1 = in1[0];
		reg[0] = op0 * op1;
	}
	return reg[0];
}

int P47(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = in1[0];
		int op1 = reg[2];
		reg[2] = op0 + op1;
	}
	{
		int op0 = in1[0];
		int op1 = reg[2];
		reg[0] = op0 + op1;
	}
	return reg[0];
}

int P48(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = reg[7];
		int op1 = in1[1];
		reg[6] = op0 - op1;
	}
	{
		int op0 = reg[6];
		int op1 = in1[0];
		reg[0] = ((op0) < (op1)) ? (op1) : (op0);
	}
	return reg[0];
}

int P49(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = in1[1];
		int op1 = reg[0];
		reg[0] = f_div(op0, op1);
	}
	{
		int op0 = in1[1];
		int op1 = reg[0];
		reg[1] = op0 - op1;
	}
	{
		int op0 = reg[4];
		int op1 = reg[0];
		reg[2] = ((op0) < (op1)) ? (op1) : (op0);
	}
	{
		int op0 = reg[1];
		int op1 = reg[2];
		reg[0] = op0 - op1;
	}
	return reg[0];
}

int P50(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = in1[0];
		int op1 = in1[1];
		reg[6] = ((op0) < (op1)) ? (op1) : (op0);
	}
	{
		int op0 = reg[6];
		int op1 = in1[1];
		reg[0] = op0 * op1;
	}
	return reg[0];
}

int P51(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = reg[0];
		int op1 = reg[6];
		reg[7] = op0 * op1;
	}
	{
		int op0 = in1[1];
		int op1 = in1[0];
		reg[3] = op0 * op1;
	}
	{
		int op0 = in1[1];
		int op1 = reg[0];
		reg[1] = ((op0) < (op1)) ? (op1) : (op0);
	}
	{
		int op0 = in1[0];
		int op1 = reg[3];
		reg[5] = op0 - op1;
	}
	{
		int op0 = reg[7];
		int op1 = reg[1];
		reg[6] = op0 - op1;
	}
	{
		int op0 = reg[5];
		int op1 = reg[6];
		reg[0] = op0 - op1;
	}
	return reg[0];
}

int P52(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = in1[0];
		int op1 = in1[0];
		reg[1] = op0 * op1;
	}
	{
		int op0 = in1[1];
		int op1 = reg[1];
		reg[0] = op0 - op1;
	}
	return reg[0];
}

int P53(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = in1[1];
		int op1 = reg[3];
		reg[6] = op0 - op1;
	}
	{
		int op0 = reg[6];
		int op1 = in1[1];
		reg[3] = f_div(op0, op1);
	}
	{
		int op0 = reg[3];
		int op1 = in1[0];
		reg[6] = op0 - op1;
	}
	{
		int op0 = in1[0];
		int op1 = reg[6];
		reg[0] = op0 * op1;
	}
	return reg[0];
}

int P54(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = in1[1];
		int op1 = in1[1];
		reg[0] = op0 + op1;
	}
	return reg[0];
}

int P55(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = reg[4];
		int op1 = in1[1];
		reg[6] = f_div(op0, op1);
	}
	{
		int op0 = reg[6];
		int op1 = in1[1];
		reg[1] = f_div(op0, op1);
	}
	{
		int op0 = reg[1];
		int op1 = in1[1];
		reg[5] = op0 - op1;
	}
	{
		int op0 = in1[0];
		int op1 = reg[5];
		reg[6] = op0 + op1;
	}
	{
		int op0 = reg[6];
		int op1 = in1[0];
		reg[0] = op0 * op1;
	}
	return reg[0];
}

int P56(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = reg[6];
		int op1 = in1[1];
		reg[0] = op0 - op1;
	}
	{
		int op0 = reg[0];
		int op1 = reg[6];
		reg[0] = op0 + op1;
	}
	return reg[0];
}

int P57(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
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

int P58(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = in1[0];
		int op1 = in1[1];
		reg[5] = ((op0) < (op1)) ? (op1) : (op0);
	}
	{
		int op0 = reg[5];
		int op1 = reg[5];
		reg[0] = op0 * op1;
	}
	return reg[0];
}

int P59(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = in1[1];
		int op1 = in1[0];
		reg[3] = op0 + op1;
	}
	{
		int op0 = in1[0];
		int op1 = reg[3];
		reg[0] = ((op0) < (op1)) ? (op1) : (op0);
	}
	return reg[0];
}

int P60(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = in1[0];
		int op1 = in1[0];
		reg[4] = op0 + op1;
	}
	{
		int op0 = in1[1];
		int op1 = reg[4];
		reg[0] = ((op0) < (op1)) ? (op1) : (op0);
	}
	return reg[0];
}

int P61(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = in1[0];
		int op1 = in1[1];
		reg[5] = op0 * op1;
	}
	{
		int op0 = in1[1];
		int op1 = reg[5];
		reg[0] = op0 * op1;
	}
	return reg[0];
}

int P62(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
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

int P63(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = in1[1];
		int op1 = in1[1];
		reg[0] = op0 * op1;
	}
	return reg[0];
}

int P64(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
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

int P65(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = in1[1];
		int op1 = in1[1];
		reg[0] = f_div(op0, op1);
	}
	{
		int op0 = in1[1];
		int op1 = reg[6];
		reg[6] = ((op0) < (op1)) ? (op1) : (op0);
	}
	{
		int op0 = reg[0];
		int op1 = reg[6];
		reg[0] = ((op0) < (op1)) ? (op1) : (op0);
	}
	return reg[0];
}

int P66(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = in1[1];
		int op1 = in1[0];
		reg[1] = f_div(op0, op1);
	}
	{
		int op0 = in1[0];
		int op1 = reg[1];
		reg[0] = op0 - op1;
	}
	return reg[0];
}

int P67(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = reg[6];
		int op1 = in1[0];
		reg[0] = op0 - op1;
	}
	return reg[0];
}

int P68(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
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

int P69(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = in1[0];
		int op1 = in1[1];
		reg[4] = op0 + op1;
	}
	{
		int op0 = in1[0];
		int op1 = reg[2];
		reg[2] = op0 + op1;
	}
	{
		int op0 = reg[4];
		int op1 = reg[2];
		reg[0] = ((op0) < (op1)) ? (op1) : (op0);
	}
	return reg[0];
}

int P70(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = reg[6];
		int op1 = in1[0];
		reg[0] = op0 - op1;
	}
	return reg[0];
}

int P71(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = in1[0];
		int op1 = reg[7];
		reg[4] = op0 + op1;
	}
	{
		int op0 = in1[0];
		int op1 = in1[0];
		reg[2] = op0 + op1;
	}
	{
		int op0 = reg[4];
		int op1 = reg[2];
		reg[0] = op0 + op1;
	}
	return reg[0];
}

int P72(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = in1[0];
		int op1 = in1[0];
		reg[5] = op0 * op1;
	}
	{
		int op0 = reg[5];
		int op1 = in1[0];
		reg[6] = op0 + op1;
	}
	{
		int op0 = reg[6];
		int op1 = in1[0];
		reg[0] = op0 + op1;
	}
	return reg[0];
}

int P73(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = in1[0];
		int op1 = in1[0];
		reg[5] = ((op0) < (op1)) ? (op1) : (op0);
	}
	{
		int op0 = reg[5];
		int op1 = reg[5];
		reg[0] = op0 * op1;
	}
	return reg[0];
}

int P74(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = reg[6];
		int op1 = in1[1];
		reg[4] = op0 - op1;
	}
	{
		int op0 = reg[4];
		int op1 = reg[1];
		reg[0] = op0 - op1;
	}
	return reg[0];
}

int P75(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = in1[0];
		int op1 = in1[1];
		reg[0] = op0 * op1;
	}
	return reg[0];
}

int P76(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = reg[0];
		int op1 = reg[2];
		reg[5] = op0 * op1;
	}
	{
		int op0 = reg[5];
		int op1 = in1[1];
		reg[6] = op0 - op1;
	}
	{
		int op0 = in1[0];
		int op1 = reg[5];
		reg[3] = op0 + op1;
	}
	{
		int op0 = reg[3];
		int op1 = reg[4];
		reg[2] = ((op0) < (op1)) ? (op1) : (op0);
	}
	{
		int op0 = reg[2];
		int op1 = reg[6];
		reg[0] = op0 + op1;
	}
	return reg[0];
}

int P77(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = reg[2];
		int op1 = in1[1];
		reg[5] = op0 + op1;
	}
	{
		int op0 = reg[4];
		int op1 = reg[5];
		reg[0] = op0 - op1;
	}
	return reg[0];
}

int P78(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = in1[0];
		int op1 = in1[1];
		reg[6] = ((op0) < (op1)) ? (op1) : (op0);
	}
	{
		int op0 = reg[6];
		int op1 = reg[6];
		reg[5] = op0 * op1;
	}
	{
		int op0 = in1[1];
		int op1 = reg[5];
		reg[3] = op0 + op1;
	}
	{
		int op0 = reg[0];
		int op1 = in1[0];
		reg[0] = ((op0) < (op1)) ? (op1) : (op0);
	}
	{
		int op0 = in1[1];
		int op1 = reg[0];
		reg[4] = op0 * op1;
	}
	{
		int op0 = reg[3];
		int op1 = reg[4];
		reg[0] = op0 - op1;
	}
	return reg[0];
}

int P79(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = in1[1];
		int op1 = in1[1];
		reg[0] = op0 + op1;
	}
	return reg[0];
}

int P80(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = in1[0];
		int op1 = in1[1];
		reg[1] = op0 - op1;
	}
	{
		int op0 = reg[1];
		int op1 = in1[0];
		reg[0] = f_div(op0, op1);
	}
	return reg[0];
}

int P81(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = in1[0];
		int op1 = in1[0];
		reg[7] = op0 * op1;
	}
	{
		int op0 = in1[1];
		int op1 = in1[1];
		reg[6] = op0 + op1;
	}
	{
		int op0 = reg[7];
		int op1 = reg[6];
		reg[6] = op0 + op1;
	}
	{
		int op0 = reg[6];
		int op1 = in1[1];
		reg[0] = op0 + op1;
	}
	return reg[0];
}

int P82(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = reg[4];
		int op1 = reg[1];
		reg[0] = op0 - op1;
	}
	{
		int op0 = reg[0];
		int op1 = in1[1];
		reg[0] = op0 - op1;
	}
	return reg[0];
}

int P83(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
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

int P84(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = in1[0];
		int op1 = in1[1];
		reg[0] = ((op0) < (op1)) ? (op1) : (op0);
	}
	return reg[0];
}

int P85(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = in1[0];
		int op1 = in1[1];
		reg[0] = f_div(op0, op1);
	}
	{
		int op0 = reg[0];
		int op1 = in1[0];
		reg[0] = op0 - op1;
	}
	return reg[0];
}

int P86(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = in1[0];
		int op1 = in1[0];
		reg[0] = f_div(op0, op1);
	}
	{
		int op0 = reg[0];
		int op1 = in1[0];
		reg[5] = op0 - op1;
	}
	{
		int op0 = in1[1];
		int op1 = reg[5];
		reg[0] = op0 - op1;
	}
	return reg[0];
}

int P87(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = in1[0];
		int op1 = in1[1];
		reg[3] = f_div(op0, op1);
	}
	{
		int op0 = reg[3];
		int op1 = reg[3];
		reg[0] = ((op0) < (op1)) ? (op1) : (op0);
	}
	return reg[0];
}

int P88(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = in1[0];
		int op1 = in1[0];
		reg[7] = ((op0) < (op1)) ? (op1) : (op0);
	}
	{
		int op0 = reg[7];
		int op1 = in1[0];
		reg[2] = f_div(op0, op1);
	}
	{
		int op0 = reg[7];
		int op1 = reg[2];
		reg[4] = op0 - op1;
	}
	{
		int op0 = in1[1];
		int op1 = reg[4];
		reg[0] = op0 * op1;
	}
	return reg[0];
}

int P89(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = in1[0];
		int op1 = in1[1];
		reg[3] = op0 - op1;
	}
	{
		int op0 = in1[1];
		int op1 = reg[3];
		reg[0] = op0 - op1;
	}
	return reg[0];
}

int P90(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = in1[0];
		int op1 = in1[0];
		reg[2] = ((op0) < (op1)) ? (op1) : (op0);
	}
	{
		int op0 = in1[1];
		int op1 = in1[1];
		reg[5] = op0 + op1;
	}
	{
		int op0 = reg[5];
		int op1 = reg[2];
		reg[0] = op0 - op1;
	}
	return reg[0];
}

int P91(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = in1[1];
		int op1 = in1[0];
		reg[0] = op0 * op1;
	}
	return reg[0];
}

int P92(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = in1[0];
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

int P93(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = in1[1];
		int op1 = in1[1];
		reg[2] = op0 + op1;
	}
	{
		int op0 = reg[2];
		int op1 = in1[1];
		reg[1] = f_div(op0, op1);
	}
	{
		int op0 = reg[2];
		int op1 = in1[1];
		reg[7] = op0 - op1;
	}
	{
		int op0 = reg[7];
		int op1 = reg[1];
		reg[7] = ((op0) < (op1)) ? (op1) : (op0);
	}
	{
		int op0 = reg[7];
		int op1 = in1[0];
		reg[0] = ((op0) < (op1)) ? (op1) : (op0);
	}
	return reg[0];
}

int P94(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = in1[1];
		int op1 = in1[0];
		reg[7] = op0 * op1;
	}
	{
		int op0 = in1[0];
		int op1 = reg[7];
		reg[6] = op0 - op1;
	}
	{
		int op0 = in1[1];
		int op1 = reg[6];
		reg[0] = op0 - op1;
	}
	return reg[0];
}

int P95(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = reg[3];
		int op1 = reg[3];
		reg[6] = op0 - op1;
	}
	{
		int op0 = in1[1];
		int op1 = in1[1];
		reg[5] = op0 * op1;
	}
	{
		int op0 = in1[0];
		int op1 = reg[5];
		reg[4] = op0 - op1;
	}
	{
		int op0 = reg[4];
		int op1 = reg[6];
		reg[0] = op0 - op1;
	}
	return reg[0];
}

int P96(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = in1[1];
		int op1 = in1[1];
		reg[6] = ((op0) < (op1)) ? (op1) : (op0);
	}
	{
		int op0 = reg[6];
		int op1 = in1[1];
		reg[1] = op0 * op1;
	}
	{
		int op0 = reg[4];
		int op1 = reg[1];
		reg[0] = op0 - op1;
	}
	return reg[0];
}

int P97(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = in1[0];
		int op1 = in1[0];
		reg[0] = op0 + op1;
	}
	{
		int op0 = reg[0];
		int op1 = in1[1];
		reg[0] = op0 - op1;
	}
	return reg[0];
}

int P98(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = in1[1];
		int op1 = in1[1];
		reg[5] = op0 * op1;
	}
	{
		int op0 = reg[5];
		int op1 = in1[0];
		reg[0] = op0 + op1;
	}
	return reg[0];
}

int P99(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = reg[3];
		int op1 = in1[1];
		reg[0] = f_div(op0, op1);
	}
	{
		int op0 = reg[1];
		int op1 = in1[0];
		reg[4] = op0 + op1;
	}
	{
		int op0 = in1[1];
		int op1 = reg[0];
		reg[0] = op0 - op1;
	}
	{
		int op0 = reg[4];
		int op1 = in1[0];
		reg[2] = op0 + op1;
	}
	{
		int op0 = reg[0];
		int op1 = in1[0];
		reg[7] = op0 + op1;
	}
	{
		int op0 = reg[7];
		int op1 = reg[2];
		reg[5] = ((op0) < (op1)) ? (op1) : (op0);
	}
	{
		int op0 = reg[5];
		int op1 = in1[0];
		reg[4] = f_div(op0, op1);
	}
	{
		int op0 = reg[2];
		int op1 = reg[4];
		reg[0] = op0 + op1;
	}
	return reg[0];
}

int P100(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = in1[1];
		int op1 = in1[0];
		reg[4] = ((op0) < (op1)) ? (op1) : (op0);
	}
	{
		int op0 = in1[1];
		int op1 = reg[4];
		reg[0] = op0 - op1;
	}
	return reg[0];
}

int P101(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = in1[1];
		int op1 = in1[0];
		reg[0] = op0 - op1;
	}
	{
		int op0 = reg[0];
		int op1 = in1[0];
		reg[6] = op0 * op1;
	}
	{
		int op0 = in1[1];
		int op1 = reg[6];
		reg[0] = op0 - op1;
	}
	return reg[0];
}

int P102(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = in1[0];
		int op1 = in1[0];
		reg[7] = op0 + op1;
	}
	{
		int op0 = reg[7];
		int op1 = in1[0];
		reg[3] = op0 * op1;
	}
	{
		int op0 = in1[0];
		int op1 = reg[3];
		reg[7] = op0 * op1;
	}
	{
		int op0 = reg[7];
		int op1 = reg[2];
		reg[4] = op0 + op1;
	}
	{
		int op0 = in1[0];
		int op1 = reg[4];
		reg[0] = ((op0) < (op1)) ? (op1) : (op0);
	}
	return reg[0];
}

int P103(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = in1[0];
		int op1 = in1[1];
		reg[5] = f_div(op0, op1);
	}
	{
		int op0 = in1[0];
		int op1 = in1[0];
		reg[4] = ((op0) < (op1)) ? (op1) : (op0);
	}
	{
		int op0 = reg[1];
		int op1 = reg[4];
		reg[3] = op0 - op1;
	}
	{
		int op0 = reg[5];
		int op1 = reg[3];
		reg[4] = op0 * op1;
	}
	{
		int op0 = in1[1];
		int op1 = in1[1];
		reg[2] = f_div(op0, op1);
	}
	{
		int op0 = reg[2];
		int op1 = reg[4];
		reg[0] = ((op0) < (op1)) ? (op1) : (op0);
	}
	return reg[0];
}

int P104(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = in1[0];
		int op1 = in1[1];
		reg[5] = op0 * op1;
	}
	{
		int op0 = reg[5];
		int op1 = in1[1];
		reg[0] = op0 * op1;
	}
	return reg[0];
}

int P105(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = in1[1];
		int op1 = in1[1];
		reg[0] = op0 * op1;
	}
	{
		int op0 = in1[1];
		int op1 = in1[0];
		reg[7] = op0 * op1;
	}
	{
		int op0 = in1[1];
		int op1 = reg[0];
		reg[3] = ((op0) < (op1)) ? (op1) : (op0);
	}
	{
		int op0 = reg[3];
		int op1 = in1[1];
		reg[0] = op0 - op1;
	}
	{
		int op0 = reg[7];
		int op1 = reg[0];
		reg[5] = op0 + op1;
	}
	{
		int op0 = reg[5];
		int op1 = in1[1];
		reg[0] = op0 * op1;
	}
	return reg[0];
}

int P106(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = reg[5];
		int op1 = in1[1];
		reg[0] = op0 - op1;
	}
	return reg[0];
}

int P107(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = in1[1];
		int op1 = reg[0];
		reg[2] = op0 - op1;
	}
	{
		int op0 = reg[2];
		int op1 = in1[0];
		reg[7] = op0 - op1;
	}
	{
		int op0 = in1[1];
		int op1 = reg[7];
		reg[5] = op0 - op1;
	}
	{
		int op0 = in1[1];
		int op1 = reg[5];
		reg[0] = op0 - op1;
	}
	return reg[0];
}

int P108(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
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

int P109(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
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

int P110(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = in1[1];
		int op1 = reg[6];
		reg[2] = ((op0) < (op1)) ? (op1) : (op0);
	}
	{
		int op0 = in1[0];
		int op1 = reg[2];
		reg[0] = op0 - op1;
	}
	return reg[0];
}

int P111(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = in1[0];
		int op1 = in1[0];
		reg[2] = op0 + op1;
	}
	{
		int op0 = in1[1];
		int op1 = in1[1];
		reg[3] = f_div(op0, op1);
	}
	{
		int op0 = in1[0];
		int op1 = reg[3];
		reg[3] = ((op0) < (op1)) ? (op1) : (op0);
	}
	{
		int op0 = reg[2];
		int op1 = reg[3];
		reg[7] = op0 + op1;
	}
	{
		int op0 = reg[3];
		int op1 = reg[7];
		reg[0] = op0 * op1;
	}
	return reg[0];
}

int P112(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = in1[0];
		int op1 = in1[0];
		reg[7] = op0 + op1;
	}
	{
		int op0 = in1[0];
		int op1 = reg[3];
		reg[1] = ((op0) < (op1)) ? (op1) : (op0);
	}
	{
		int op0 = reg[1];
		int op1 = in1[1];
		reg[2] = op0 * op1;
	}
	{
		int op0 = reg[2];
		int op1 = reg[7];
		reg[4] = op0 + op1;
	}
	{
		int op0 = in1[1];
		int op1 = reg[4];
		reg[0] = op0 * op1;
	}
	return reg[0];
}

int P113(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
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

int P114(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = in1[0];
		int op1 = in1[1];
		reg[3] = op0 - op1;
	}
	{
		int op0 = reg[3];
		int op1 = reg[3];
		reg[0] = op0 * op1;
	}
	return reg[0];
}

int P115(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = in1[0];
		int op1 = in1[1];
		reg[0] = op0 * op1;
	}
	return reg[0];
}

int P116(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = reg[4];
		int op1 = in1[0];
		reg[0] = ((op0) < (op1)) ? (op1) : (op0);
	}
	{
		int op0 = reg[0];
		int op1 = reg[7];
		reg[4] = op0 - op1;
	}
	{
		int op0 = reg[4];
		int op1 = reg[0];
		reg[6] = f_div(op0, op1);
	}
	{
		int op0 = in1[0];
		int op1 = reg[6];
		reg[3] = op0 + op1;
	}
	{
		int op0 = in1[1];
		int op1 = reg[3];
		reg[0] = op0 * op1;
	}
	return reg[0];
}

int P117(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
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

int P118(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = in1[1];
		int op1 = in1[0];
		reg[0] = ((op0) < (op1)) ? (op1) : (op0);
	}
	return reg[0];
}

int P119(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = in1[1];
		int op1 = in1[1];
		reg[7] = op0 * op1;
	}
	{
		int op0 = reg[7];
		int op1 = in1[1];
		reg[0] = op0 - op1;
	}
	return reg[0];
}

int P120(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
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
		int op1 = reg[7];
		reg[0] = op0 * op1;
	}
	return reg[0];
}

int P121(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = in1[0];
		int op1 = in1[0];
		reg[0] = op0 * op1;
	}
	return reg[0];
}

int P122(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
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

int P123(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
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

int P124(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
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

int P125(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
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

int P126(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = in1[0];
		int op1 = in1[0];
		reg[0] = ((op0) < (op1)) ? (op1) : (op0);
	}
	{
		int op0 = in1[1];
		int op1 = reg[7];
		reg[3] = f_div(op0, op1);
	}
	{
		int op0 = reg[0];
		int op1 = reg[6];
		reg[2] = op0 + op1;
	}
	{
		int op0 = in1[0];
		int op1 = reg[3];
		reg[3] = ((op0) < (op1)) ? (op1) : (op0);
	}
	{
		int op0 = reg[2];
		int op1 = reg[3];
		reg[7] = op0 + op1;
	}
	{
		int op0 = reg[3];
		int op1 = reg[7];
		reg[0] = op0 * op1;
	}
	return reg[0];
}

int P127(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = reg[4];
		int op1 = reg[4];
		reg[1] = op0 * op1;
	}
	{
		int op0 = reg[1];
		int op1 = in1[1];
		reg[0] = op0 - op1;
	}
	{
		int op0 = in1[0];
		int op1 = reg[0];
		reg[0] = f_div(op0, op1);
	}
	return reg[0];
}

int P128(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = in1[1];
		int op1 = in1[1];
		reg[1] = op0 + op1;
	}
	{
		int op0 = reg[1];
		int op1 = in1[1];
		reg[0] = f_div(op0, op1);
	}
	return reg[0];
}

int P129(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = in1[0];
		int op1 = in1[0];
		reg[1] = op0 + op1;
	}
	{
		int op0 = in1[1];
		int op1 = reg[2];
		reg[7] = op0 + op1;
	}
	{
		int op0 = reg[1];
		int op1 = reg[7];
		reg[3] = f_div(op0, op1);
	}
	{
		int op0 = reg[3];
		int op1 = reg[7];
		reg[1] = op0 - op1;
	}
	{
		int op0 = in1[0];
		int op1 = reg[1];
		reg[0] = op0 * op1;
	}
	return reg[0];
}

int P130(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = reg[0];
		int op1 = in1[0];
		reg[2] = ((op0) < (op1)) ? (op1) : (op0);
	}
	{
		int op0 = in1[0];
		int op1 = in1[0];
		reg[7] = op0 + op1;
	}
	{
		int op0 = reg[2];
		int op1 = reg[7];
		reg[4] = op0 + op1;
	}
	{
		int op0 = in1[1];
		int op1 = reg[4];
		reg[0] = op0 * op1;
	}
	return reg[0];
}

int P131(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = in1[1];
		int op1 = in1[1];
		reg[7] = op0 * op1;
	}
	{
		int op0 = in1[0];
		int op1 = reg[7];
		reg[0] = ((op0) < (op1)) ? (op1) : (op0);
	}
	return reg[0];
}

int P132(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = in1[0];
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

int P133(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = reg[5];
		int op1 = in1[0];
		reg[2] = op0 - op1;
	}
	{
		int op0 = in1[1];
		int op1 = in1[1];
		reg[1] = op0 + op1;
	}
	{
		int op0 = reg[2];
		int op1 = in1[0];
		reg[6] = ((op0) < (op1)) ? (op1) : (op0);
	}
	{
		int op0 = reg[6];
		int op1 = in1[1];
		reg[0] = ((op0) < (op1)) ? (op1) : (op0);
	}
	{
		int op0 = reg[1];
		int op1 = reg[0];
		reg[0] = ((op0) < (op1)) ? (op1) : (op0);
	}
	return reg[0];
}

int P134(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
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
		reg[3] = op0 - op1;
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

int P135(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = reg[5];
		int op1 = in1[0];
		reg[4] = op0 - op1;
	}
	{
		int op0 = in1[0];
		int op1 = reg[4];
		reg[0] = f_div(op0, op1);
	}
	return reg[0];
}

int P136(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = in1[1];
		int op1 = reg[4];
		reg[4] = op0 + op1;
	}
	{
		int op0 = reg[4];
		int op1 = in1[0];
		reg[5] = op0 + op1;
	}
	{
		int op0 = reg[5];
		int op1 = reg[3];
		reg[0] = op0 - op1;
	}
	return reg[0];
}

int P137(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = in1[1];
		int op1 = in1[0];
		reg[0] = op0 - op1;
	}
	{
		int op0 = in1[1];
		int op1 = reg[0];
		reg[2] = ((op0) < (op1)) ? (op1) : (op0);
	}
	{
		int op0 = in1[0];
		int op1 = reg[2];
		reg[0] = op0 - op1;
	}
	return reg[0];
}

int P138(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = in1[1];
		int op1 = reg[4];
		reg[7] = op0 + op1;
	}
	{
		int op0 = in1[1];
		int op1 = reg[7];
		reg[0] = f_div(op0, op1);
	}
	return reg[0];
}

int P139(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = reg[5];
		int op1 = in1[0];
		reg[0] = op0 - op1;
	}
	return reg[0];
}

int P140(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = reg[5];
		int op1 = in1[1];
		reg[1] = op0 + op1;
	}
	{
		int op0 = reg[5];
		int op1 = reg[1];
		reg[0] = op0 - op1;
	}
	return reg[0];
}

int P141(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = in1[0];
		int op1 = reg[4];
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

int P142(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = in1[1];
		int op1 = in1[0];
		reg[3] = ((op0) < (op1)) ? (op1) : (op0);
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
		int op1 = reg[7];
		reg[0] = op0 * op1;
	}
	return reg[0];
}

int P143(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = in1[0];
		int op1 = in1[1];
		reg[6] = op0 - op1;
	}
	{
		int op0 = reg[7];
		int op1 = reg[6];
		reg[7] = op0 - op1;
	}
	{
		int op0 = reg[7];
		int op1 = in1[1];
		reg[0] = op0 + op1;
	}
	return reg[0];
}

int P144(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = in1[0];
		int op1 = in1[1];
		reg[4] = op0 + op1;
	}
	{
		int op0 = in1[1];
		int op1 = reg[5];
		reg[5] = op0 * op1;
	}
	{
		int op0 = reg[4];
		int op1 = reg[5];
		reg[3] = op0 * op1;
	}
	{
		int op0 = reg[3];
		int op1 = in1[0];
		reg[1] = op0 - op1;
	}
	{
		int op0 = in1[1];
		int op1 = reg[1];
		reg[0] = op0 * op1;
	}
	return reg[0];
}

int P145(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = in1[0];
		int op1 = in1[0];
		reg[0] = op0 + op1;
	}
	return reg[0];
}

int P146(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = in1[0];
		int op1 = in1[1];
		reg[6] = f_div(op0, op1);
	}
	{
		int op0 = reg[6];
		int op1 = in1[0];
		reg[0] = ((op0) < (op1)) ? (op1) : (op0);
	}
	return reg[0];
}

int P147(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = reg[5];
		int op1 = in1[0];
		reg[2] = op0 + op1;
	}
	{
		int op0 = reg[2];
		int op1 = in1[1];
		reg[7] = f_div(op0, op1);
	}
	{
		int op0 = reg[7];
		int op1 = in1[1];
		reg[0] = op0 - op1;
	}
	return reg[0];
}

int P148(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = in1[1];
		int op1 = in1[0];
		reg[0] = op0 - op1;
	}
	return reg[0];
}

int P149(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
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

int P150(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
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

int P151(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = in1[1];
		int op1 = reg[5];
		reg[3] = op0 - op1;
	}
	{
		int op0 = reg[3];
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

int P152(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = in1[1];
		int op1 = in1[0];
		reg[0] = op0 - op1;
	}
	return reg[0];
}

int P153(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
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

int P154(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = reg[5];
		int op1 = in1[0];
		reg[5] = ((op0) < (op1)) ? (op1) : (op0);
	}
	{
		int op0 = reg[4];
		int op1 = reg[5];
		reg[0] = op0 - op1;
	}
	return reg[0];
}

int P155(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = reg[5];
		int op1 = reg[5];
		reg[4] = ((op0) < (op1)) ? (op1) : (op0);
	}
	{
		int op0 = in1[0];
		int op1 = in1[0];
		reg[3] = f_div(op0, op1);
	}
	{
		int op0 = reg[4];
		int op1 = in1[0];
		reg[5] = ((op0) < (op1)) ? (op1) : (op0);
	}
	{
		int op0 = reg[5];
		int op1 = reg[3];
		reg[0] = op0 - op1;
	}
	return reg[0];
}

int P156(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
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

int P157(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = in1[1];
		int op1 = in1[1];
		reg[7] = op0 * op1;
	}
	{
		int op0 = in1[1];
		int op1 = reg[7];
		reg[0] = op0 - op1;
	}
	return reg[0];
}

int P158(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
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

int P159(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = in1[0];
		int op1 = reg[1];
		reg[6] = op0 * op1;
	}
	{
		int op0 = in1[1];
		int op1 = reg[5];
		reg[0] = op0 * op1;
	}
	{
		int op0 = reg[0];
		int op1 = reg[6];
		reg[0] = ((op0) < (op1)) ? (op1) : (op0);
	}
	{
		int op0 = reg[7];
		int op1 = reg[4];
		reg[4] = ((op0) < (op1)) ? (op1) : (op0);
	}
	{
		int op0 = in1[1];
		int op1 = in1[1];
		reg[3] = op0 + op1;
	}
	{
		int op0 = reg[3];
		int op1 = reg[4];
		reg[4] = op0 + op1;
	}
	{
		int op0 = reg[0];
		int op1 = in1[0];
		reg[2] = f_div(op0, op1);
	}
	{
		int op0 = reg[4];
		int op1 = reg[2];
		reg[0] = op0 + op1;
	}
	return reg[0];
}

int P160(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
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

int P161(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
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

int P162(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
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

int P163(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
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

int P164(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
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

int P165(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
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

int P166(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = in1[0];
		int op1 = in1[0];
		reg[0] = f_div(op0, op1);
	}
	return reg[0];
}

int P167(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	{
		int op0 = in1[1];
		int op1 = in1[1];
		reg[0] = f_div(op0, op1);
	}
	return reg[0];
}

int P168(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
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

int P169(){
	int reg[8] = {0, 0, 0, 0, 0, 0, 0, 0};
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
