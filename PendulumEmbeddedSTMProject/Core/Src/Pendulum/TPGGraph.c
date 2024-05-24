/**
 * File generated with GEGELATI v1.3.1
 * On the 2024-04-30 11:04:22
 * With the CodeGen::TPGGenerationEngine.
 */

#include "TPGGraph.h"
#include "TPGPrograms.h"
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

enum vertices {T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, A14, A15, A16, A17, A18, A19, };

int inferenceTPG() {
	enum vertices currentVertex = T13;
	while(1) {
		switch (currentVertex) {
		case T0: {
			const enum vertices next[2] = { A14, A15,  };

			double T0Scores[2];

			T0Scores[0] = P0();
			T0Scores[1] = P1();

			int best = bestProgram(T0Scores, 2);
			currentVertex = next[best];
			break;
		}
		case T1: {
			const enum vertices next[3] = { A16, A17, A14,  };

			double T1Scores[3];

			T1Scores[0] = P2();
			T1Scores[1] = P3();
			T1Scores[2] = P4();

			int best = bestProgram(T1Scores, 3);
			currentVertex = next[best];
			break;
		}
		case T2: {
			const enum vertices next[3] = { A16, T1, A15,  };

			double T2Scores[3];

			T2Scores[0] = P5();
			T2Scores[1] = P6();
			T2Scores[2] = P7();

			int best = bestProgram(T2Scores, 3);
			currentVertex = next[best];
			break;
		}
		case T3: {
			const enum vertices next[3] = { T1, A18, T0,  };

			double T3Scores[3];

			T3Scores[0] = P8();
			T3Scores[1] = P9();
			T3Scores[2] = P10();

			int best = bestProgram(T3Scores, 3);
			currentVertex = next[best];
			break;
		}
		case T4: {
			const enum vertices next[3] = { T2, T2, T1,  };

			double T4Scores[3];

			T4Scores[0] = P11();
			T4Scores[1] = P12();
			T4Scores[2] = P13();

			int best = bestProgram(T4Scores, 3);
			currentVertex = next[best];
			break;
		}
		case T5: {
			const enum vertices next[2] = { T3, T2,  };

			double T5Scores[2];

			T5Scores[0] = P14();
			T5Scores[1] = P15();

			int best = bestProgram(T5Scores, 2);
			currentVertex = next[best];
			break;
		}
		case T6: {
			const enum vertices next[3] = { T4, T3, T2,  };

			double T6Scores[3];

			T6Scores[0] = P16();
			T6Scores[1] = P17();
			T6Scores[2] = P18();

			int best = bestProgram(T6Scores, 3);
			currentVertex = next[best];
			break;
		}
		case T7: {
			const enum vertices next[5] = { T5, T4, T2, T2, T2,  };

			double T7Scores[5];

			T7Scores[0] = P19();
			T7Scores[1] = P20();
			T7Scores[2] = P21();
			T7Scores[3] = P22();
			T7Scores[4] = P23();

			int best = bestProgram(T7Scores, 5);
			currentVertex = next[best];
			break;
		}
		case T8: {
			const enum vertices next[3] = { T7, T1, T6,  };

			double T8Scores[3];

			T8Scores[0] = P24();
			T8Scores[1] = P25();
			T8Scores[2] = P26();

			int best = bestProgram(T8Scores, 3);
			currentVertex = next[best];
			break;
		}
		case T9: {
			const enum vertices next[2] = { T6, T8,  };

			double T9Scores[2];

			T9Scores[0] = P27();
			T9Scores[1] = P28();

			int best = bestProgram(T9Scores, 2);
			currentVertex = next[best];
			break;
		}
		case T10: {
			const enum vertices next[3] = { T9, T1, A19,  };

			double T10Scores[3];

			T10Scores[0] = P29();
			T10Scores[1] = P30();
			T10Scores[2] = P31();

			int best = bestProgram(T10Scores, 3);
			currentVertex = next[best];
			break;
		}
		case T11: {
			const enum vertices next[3] = { T10, T4, T10,  };

			double T11Scores[3];

			T11Scores[0] = P32();
			T11Scores[1] = P33();
			T11Scores[2] = P34();

			int best = bestProgram(T11Scores, 3);
			currentVertex = next[best];
			break;
		}
		case T12: {
			const enum vertices next[3] = { T11, T10, T10,  };

			double T12Scores[3];

			T12Scores[0] = P35();
			T12Scores[1] = P36();
			T12Scores[2] = P37();

			int best = bestProgram(T12Scores, 3);
			currentVertex = next[best];
			break;
		}
		case T13: {
			const enum vertices next[3] = { T10, T2, T12,  };

			double T13Scores[3];

			T13Scores[0] = P38();
			T13Scores[1] = P39();
			T13Scores[2] = P40();

			int best = bestProgram(T13Scores, 3);
			currentVertex = next[best];
			break;
		}
		case A14: {
			return 5;
			break;
		}
		case A15: {
			return 2;
			break;
		}
		case A16: {
			return 7;
			break;
		}
		case A17: {
			return 8;
			break;
		}
		case A18: {
			return 0;
			break;
		}
		case A19: {
			return 13;
			break;
		}
		}
	}
}
