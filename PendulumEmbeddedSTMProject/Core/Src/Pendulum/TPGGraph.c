/**
 * File generated with GEGELATI v1.3.1
 * On the 2024-03-18 17:37:15
 * With the CodeGen::TPGGenerationEngine.
 */

#include "TPGGraph.h"
#include "TPGprograms.h"
#include <limits.h>
#include <assert.h>
#include <float.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>

int bestProgram(double *results, int nb) {
	int bestProgram = 0;
	double bestScore = (isnan(results[0]))? -INFINITY : results[0];
	for (int i = 1; i < nb; i++) {
		double challengerScore = (isnan(results[i]))? -INFINITY : results[i];
		if (challengerScore >= bestScore) {
			bestProgram = i;
			bestScore = challengerScore;
		}
	}
	return bestProgram;
}

enum vertices {T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, A19, A20, A21, A22, A23, A24, A25, A26, A27, A28, A29, };

int inferenceTPG() {
	enum vertices currentVertex = T18;
	while(1) {
		switch (currentVertex) {
		case T0: {
			const enum vertices next[2] = { A19, A20,  };

			double T0Scores[2];

			T0Scores[0] = P0();
			T0Scores[1] = P1();

			int best = bestProgram(T0Scores, 2);
			currentVertex = next[best];
			break;
		}
		case T1: {
			const enum vertices next[4] = { A21, A22, A20, A23,  };

			double T1Scores[4];

			T1Scores[0] = P2();
			T1Scores[1] = P3();
			T1Scores[2] = P4();
			T1Scores[3] = P5();

			int best = bestProgram(T1Scores, 4);
			currentVertex = next[best];
			break;
		}
		case T2: {
			const enum vertices next[4] = { A22, A24, A25, A24,  };

			double T2Scores[4];

			T2Scores[0] = P6();
			T2Scores[1] = P7();
			T2Scores[2] = P8();
			T2Scores[3] = P7();

			int best = bestProgram(T2Scores, 4);
			currentVertex = next[best];
			break;
		}
		case T3: {
			const enum vertices next[4] = { A23, T0, A26, A22,  };

			double T3Scores[4];

			T3Scores[0] = P9();
			T3Scores[1] = P10();
			T3Scores[2] = P11();
			T3Scores[3] = P12();

			int best = bestProgram(T3Scores, 4);
			currentVertex = next[best];
			break;
		}
		case T4: {
			const enum vertices next[4] = { A26, T3, A24, A27,  };

			double T4Scores[4];

			T4Scores[0] = P11();
			T4Scores[1] = P13();
			T4Scores[2] = P14();
			T4Scores[3] = P15();

			int best = bestProgram(T4Scores, 4);
			currentVertex = next[best];
			break;
		}
		case T5: {
			const enum vertices next[5] = { A23, A28, A26, A29, A22,  };

			double T5Scores[5];

			T5Scores[0] = P16();
			T5Scores[1] = P17();
			T5Scores[2] = P18();
			T5Scores[3] = P19();
			T5Scores[4] = P12();

			int best = bestProgram(T5Scores, 5);
			currentVertex = next[best];
			break;
		}
		case T6: {
			const enum vertices next[3] = { T3, T5, T5,  };

			double T6Scores[3];

			T6Scores[0] = P20();
			T6Scores[1] = P21();
			T6Scores[2] = P22();

			int best = bestProgram(T6Scores, 3);
			currentVertex = next[best];
			break;
		}
		case T7: {
			const enum vertices next[5] = { T5, T5, T5, T5, T5,  };

			double T7Scores[5];

			T7Scores[0] = P23();
			T7Scores[1] = P24();
			T7Scores[2] = P25();
			T7Scores[3] = P26();
			T7Scores[4] = P27();

			int best = bestProgram(T7Scores, 5);
			currentVertex = next[best];
			break;
		}
		case T8: {
			const enum vertices next[4] = { A25, T7, T5, T5,  };

			double T8Scores[4];

			T8Scores[0] = P28();
			T8Scores[1] = P29();
			T8Scores[2] = P30();
			T8Scores[3] = P31();

			int best = bestProgram(T8Scores, 4);
			currentVertex = next[best];
			break;
		}
		case T9: {
			const enum vertices next[4] = { T5, T5, T5, T5,  };

			double T9Scores[4];

			T9Scores[0] = P32();
			T9Scores[1] = P33();
			T9Scores[2] = P34();
			T9Scores[3] = P35();

			int best = bestProgram(T9Scores, 4);
			currentVertex = next[best];
			break;
		}
		case T10: {
			const enum vertices next[5] = { T5, T1, T5, T5, T2,  };

			double T10Scores[5];

			T10Scores[0] = P36();
			T10Scores[1] = P37();
			T10Scores[2] = P38();
			T10Scores[3] = P39();
			T10Scores[4] = P40();

			int best = bestProgram(T10Scores, 5);
			currentVertex = next[best];
			break;
		}
		case T11: {
			const enum vertices next[5] = { T5, T5, T5, T5, T5,  };

			double T11Scores[5];

			T11Scores[0] = P41();
			T11Scores[1] = P42();
			T11Scores[2] = P43();
			T11Scores[3] = P44();
			T11Scores[4] = P45();

			int best = bestProgram(T11Scores, 5);
			currentVertex = next[best];
			break;
		}
		case T12: {
			const enum vertices next[4] = { T5, T11, T4, T5,  };

			double T12Scores[4];

			T12Scores[0] = P46();
			T12Scores[1] = P47();
			T12Scores[2] = P48();
			T12Scores[3] = P49();

			int best = bestProgram(T12Scores, 4);
			currentVertex = next[best];
			break;
		}
		case T13: {
			const enum vertices next[3] = { T9, T6, T5,  };

			double T13Scores[3];

			T13Scores[0] = P50();
			T13Scores[1] = P51();
			T13Scores[2] = P52();

			int best = bestProgram(T13Scores, 3);
			currentVertex = next[best];
			break;
		}
		case T14: {
			const enum vertices next[4] = { T13, T10, T12, T5,  };

			double T14Scores[4];

			T14Scores[0] = P53();
			T14Scores[1] = P54();
			T14Scores[2] = P55();
			T14Scores[3] = P56();

			int best = bestProgram(T14Scores, 4);
			currentVertex = next[best];
			break;
		}
		case T15: {
			const enum vertices next[3] = { T5, T14, T10,  };

			double T15Scores[3];

			T15Scores[0] = P57();
			T15Scores[1] = P58();
			T15Scores[2] = P59();

			int best = bestProgram(T15Scores, 3);
			currentVertex = next[best];
			break;
		}
		case T16: {
			const enum vertices next[4] = { T15, T14, T10, T15,  };

			double T16Scores[4];

			T16Scores[0] = P60();
			T16Scores[1] = P61();
			T16Scores[2] = P62();
			T16Scores[3] = P63();

			int best = bestProgram(T16Scores, 4);
			currentVertex = next[best];
			break;
		}
		case T17: {
			const enum vertices next[5] = { T15, T16, T15, T15, T15,  };

			double T17Scores[5];

			T17Scores[0] = P64();
			T17Scores[1] = P65();
			T17Scores[2] = P66();
			T17Scores[3] = P67();
			T17Scores[4] = P68();

			int best = bestProgram(T17Scores, 5);
			currentVertex = next[best];
			break;
		}
		case T18: {
			const enum vertices next[5] = { T17, T15, T8, T15, T15,  };

			double T18Scores[5];

			T18Scores[0] = P69();
			T18Scores[1] = P70();
			T18Scores[2] = P71();
			T18Scores[3] = P72();
			T18Scores[4] = P73();

			int best = bestProgram(T18Scores, 5);
			currentVertex = next[best];
			break;
		}
		case A19: {
			return 11;
			break;
		}
		case A20: {
			return 12;
			break;
		}
		case A21: {
			return 1;
			break;
		}
		case A22: {
			return 2;
			break;
		}
		case A23: {
			return 6;
			break;
		}
		case A24: {
			return 3;
			break;
		}
		case A25: {
			return 4;
			break;
		}
		case A26: {
			return 7;
			break;
		}
		case A27: {
			return 8;
			break;
		}
		case A28: {
			return 13;
			break;
		}
		case A29: {
			return 5;
			break;
		}
		}
	}
}
