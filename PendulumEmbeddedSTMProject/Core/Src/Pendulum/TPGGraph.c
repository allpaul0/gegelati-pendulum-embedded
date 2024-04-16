/**
 * File generated with GEGELATI v1.3.1
 * On the 2024-04-10 14:16:07
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

int bestProgram(int *results, int nb) {
	int bestProgram = 0;
	//int bestScore = (isnan(results[0]))? -INFINITY : results[0];
	int bestScore = results[0];
	for (int i = 1; i < nb; i++) {
		//int challengerScore = (isnan(results[i]))? -INFINITY : results[i];
		int challengerScore = results[i];
		if (challengerScore >= bestScore) {
			bestProgram = i;
			bestScore = challengerScore;
		}
	}
	return bestProgram;
}

enum vertices {T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45, T46, T47, A48, A49, A50, A51, A52, A53, A54, A55, A56, A57, A58, };

int inferenceTPG() {
	enum vertices currentVertex = T47;
	while(1) {
		switch (currentVertex) {
		case T0: {
			const enum vertices next[2] = { A48, A49,  };

			int T0Scores[2];

			T0Scores[0] = P0();
			T0Scores[1] = P1();

			int best = bestProgram(T0Scores, 2);
			currentVertex = next[best];
			break;
		}
		case T1: {
			const enum vertices next[3] = { A50, A51, A52,  };

			int T1Scores[3];

			T1Scores[0] = P2();
			T1Scores[1] = P3();
			T1Scores[2] = P4();

			int best = bestProgram(T1Scores, 3);
			currentVertex = next[best];
			break;
		}
		case T2: {
			const enum vertices next[4] = { A49, A53, A52, A54,  };

			int T2Scores[4];

			T2Scores[0] = P5();
			T2Scores[1] = P6();
			T2Scores[2] = P7();
			T2Scores[3] = P8();

			int best = bestProgram(T2Scores, 4);
			currentVertex = next[best];
			break;
		}
		case T3: {
			const enum vertices next[5] = { A55, A56, A53, A52, A56,  };

			int T3Scores[5];

			T3Scores[0] = P9();
			T3Scores[1] = P10();
			T3Scores[2] = P11();
			T3Scores[3] = P12();
			T3Scores[4] = P10();

			int best = bestProgram(T3Scores, 5);
			currentVertex = next[best];
			break;
		}
		case T4: {
			const enum vertices next[4] = { A50, A52, A57, A53,  };

			int T4Scores[4];

			T4Scores[0] = P13();
			T4Scores[1] = P14();
			T4Scores[2] = P15();
			T4Scores[3] = P16();

			int best = bestProgram(T4Scores, 4);
			currentVertex = next[best];
			break;
		}
		case T5: {
			const enum vertices next[4] = { A57, A52, A53, T4,  };

			int T5Scores[4];

			T5Scores[0] = P17();
			T5Scores[1] = P12();
			T5Scores[2] = P18();
			T5Scores[3] = P19();

			int best = bestProgram(T5Scores, 4);
			currentVertex = next[best];
			break;
		}
		case T6: {
			const enum vertices next[5] = { A55, A58, A56, T1, A55,  };

			int T6Scores[5];

			T6Scores[0] = P20();
			T6Scores[1] = P21();
			T6Scores[2] = P22();
			T6Scores[3] = P23();
			T6Scores[4] = P24();

			int best = bestProgram(T6Scores, 5);
			currentVertex = next[best];
			break;
		}
		case T7: {
			const enum vertices next[5] = { T2, A58, A58, A57, T5,  };

			int T7Scores[5];

			T7Scores[0] = P25();
			T7Scores[1] = P26();
			T7Scores[2] = P26();
			T7Scores[3] = P17();
			T7Scores[4] = P27();

			int best = bestProgram(T7Scores, 5);
			currentVertex = next[best];
			break;
		}
		case T8: {
			const enum vertices next[3] = { A57, T4, A58,  };

			int T8Scores[3];

			T8Scores[0] = P28();
			T8Scores[1] = P19();
			T8Scores[2] = P29();

			int best = bestProgram(T8Scores, 3);
			currentVertex = next[best];
			break;
		}
		case T9: {
			const enum vertices next[4] = { A53, A52, A55, T4,  };

			int T9Scores[4];

			T9Scores[0] = P30();
			T9Scores[1] = P31();
			T9Scores[2] = P24();
			T9Scores[3] = P19();

			int best = bestProgram(T9Scores, 4);
			currentVertex = next[best];
			break;
		}
		case T10: {
			const enum vertices next[5] = { T6, T4, T4, T4, A56,  };

			int T10Scores[5];

			T10Scores[0] = P32();
			T10Scores[1] = P33();
			T10Scores[2] = P19();
			T10Scores[3] = P34();
			T10Scores[4] = P35();

			int best = bestProgram(T10Scores, 5);
			currentVertex = next[best];
			break;
		}
		case T11: {
			const enum vertices next[5] = { T4, A54, A56, T3, A50,  };

			int T11Scores[5];

			T11Scores[0] = P36();
			T11Scores[1] = P37();
			T11Scores[2] = P38();
			T11Scores[3] = P39();
			T11Scores[4] = P40();

			int best = bestProgram(T11Scores, 5);
			currentVertex = next[best];
			break;
		}
		case T12: {
			const enum vertices next[3] = { A52, T10, T4,  };

			int T12Scores[3];

			T12Scores[0] = P41();
			T12Scores[1] = P42();
			T12Scores[2] = P36();

			int best = bestProgram(T12Scores, 3);
			currentVertex = next[best];
			break;
		}
		case T13: {
			const enum vertices next[3] = { T10, T4, T4,  };

			int T13Scores[3];

			T13Scores[0] = P42();
			T13Scores[1] = P43();
			T13Scores[2] = P19();

			int best = bestProgram(T13Scores, 3);
			currentVertex = next[best];
			break;
		}
		case T14: {
			const enum vertices next[4] = { A58, A50, T4, T4,  };

			int T14Scores[4];

			T14Scores[0] = P44();
			T14Scores[1] = P13();
			T14Scores[2] = P45();
			T14Scores[3] = P46();

			int best = bestProgram(T14Scores, 4);
			currentVertex = next[best];
			break;
		}
		case T15: {
			const enum vertices next[5] = { T10, A53, A55, T10, T9,  };

			int T15Scores[5];

			T15Scores[0] = P47();
			T15Scores[1] = P48();
			T15Scores[2] = P49();
			T15Scores[3] = P50();
			T15Scores[4] = P51();

			int best = bestProgram(T15Scores, 5);
			currentVertex = next[best];
			break;
		}
		case T16: {
			const enum vertices next[3] = { T10, T10, A57,  };

			int T16Scores[3];

			T16Scores[0] = P42();
			T16Scores[1] = P52();
			T16Scores[2] = P53();

			int best = bestProgram(T16Scores, 3);
			currentVertex = next[best];
			break;
		}
		case T17: {
			const enum vertices next[5] = { T10, T10, A50, T4, A52,  };

			int T17Scores[5];

			T17Scores[0] = P54();
			T17Scores[1] = P55();
			T17Scores[2] = P13();
			T17Scores[3] = P19();
			T17Scores[4] = P56();

			int best = bestProgram(T17Scores, 5);
			currentVertex = next[best];
			break;
		}
		case T18: {
			const enum vertices next[5] = { T4, T10, T10, A57, T4,  };

			int T18Scores[5];

			T18Scores[0] = P57();
			T18Scores[1] = P58();
			T18Scores[2] = P59();
			T18Scores[3] = P60();
			T18Scores[4] = P61();

			int best = bestProgram(T18Scores, 5);
			currentVertex = next[best];
			break;
		}
		case T19: {
			const enum vertices next[4] = { T10, T10, A52, T4,  };

			int T19Scores[4];

			T19Scores[0] = P62();
			T19Scores[1] = P63();
			T19Scores[2] = P12();
			T19Scores[3] = P64();

			int best = bestProgram(T19Scores, 4);
			currentVertex = next[best];
			break;
		}
		case T20: {
			const enum vertices next[5] = { T16, T12, A57, T10, T4,  };

			int T20Scores[5];

			T20Scores[0] = P65();
			T20Scores[1] = P66();
			T20Scores[2] = P67();
			T20Scores[3] = P68();
			T20Scores[4] = P69();

			int best = bestProgram(T20Scores, 5);
			currentVertex = next[best];
			break;
		}
		case T21: {
			const enum vertices next[5] = { T10, T10, T10, T10, T13,  };

			int T21Scores[5];

			T21Scores[0] = P70();
			T21Scores[1] = P71();
			T21Scores[2] = P72();
			T21Scores[3] = P73();
			T21Scores[4] = P74();

			int best = bestProgram(T21Scores, 5);
			currentVertex = next[best];
			break;
		}
		case T22: {
			const enum vertices next[4] = { T15, A52, T10, T17,  };

			int T22Scores[4];

			T22Scores[0] = P75();
			T22Scores[1] = P76();
			T22Scores[2] = P77();
			T22Scores[3] = P78();

			int best = bestProgram(T22Scores, 4);
			currentVertex = next[best];
			break;
		}
		case T23: {
			const enum vertices next[5] = { T10, A56, T10, T10, T10,  };

			int T23Scores[5];

			T23Scores[0] = P79();
			T23Scores[1] = P80();
			T23Scores[2] = P81();
			T23Scores[3] = P82();
			T23Scores[4] = P83();

			int best = bestProgram(T23Scores, 5);
			currentVertex = next[best];
			break;
		}
		case T24: {
			const enum vertices next[4] = { T12, T10, T10, T22,  };

			int T24Scores[4];

			T24Scores[0] = P84();
			T24Scores[1] = P85();
			T24Scores[2] = P86();
			T24Scores[3] = P87();

			int best = bestProgram(T24Scores, 4);
			currentVertex = next[best];
			break;
		}
		case T25: {
			const enum vertices next[4] = { T4, T10, T24, T23,  };

			int T25Scores[4];

			T25Scores[0] = P88();
			T25Scores[1] = P89();
			T25Scores[2] = P90();
			T25Scores[3] = P91();

			int best = bestProgram(T25Scores, 4);
			currentVertex = next[best];
			break;
		}
		case T26: {
			const enum vertices next[5] = { T10, T10, T25, T10, T10,  };

			int T26Scores[5];

			T26Scores[0] = P92();
			T26Scores[1] = P93();
			T26Scores[2] = P94();
			T26Scores[3] = P95();
			T26Scores[4] = P62();

			int best = bestProgram(T26Scores, 5);
			currentVertex = next[best];
			break;
		}
		case T27: {
			const enum vertices next[3] = { T18, T10, T10,  };

			int T27Scores[3];

			T27Scores[0] = P96();
			T27Scores[1] = P97();
			T27Scores[2] = P98();

			int best = bestProgram(T27Scores, 3);
			currentVertex = next[best];
			break;
		}
		case T28: {
			const enum vertices next[5] = { T12, T18, T11, A52, T10,  };

			int T28Scores[5];

			T28Scores[0] = P99();
			T28Scores[1] = P100();
			T28Scores[2] = P101();
			T28Scores[3] = P14();
			T28Scores[4] = P102();

			int best = bestProgram(T28Scores, 5);
			currentVertex = next[best];
			break;
		}
		case T29: {
			const enum vertices next[5] = { T26, T14, T10, T10, T8,  };

			int T29Scores[5];

			T29Scores[0] = P103();
			T29Scores[1] = P104();
			T29Scores[2] = P105();
			T29Scores[3] = P106();
			T29Scores[4] = P107();

			int best = bestProgram(T29Scores, 5);
			currentVertex = next[best];
			break;
		}
		case T30: {
			const enum vertices next[3] = { T11, T10, T10,  };

			int T30Scores[3];

			T30Scores[0] = P108();
			T30Scores[1] = P109();
			T30Scores[2] = P110();

			int best = bestProgram(T30Scores, 3);
			currentVertex = next[best];
			break;
		}
		case T31: {
			const enum vertices next[5] = { T11, T10, T19, T10, T29,  };

			int T31Scores[5];

			T31Scores[0] = P111();
			T31Scores[1] = P112();
			T31Scores[2] = P113();
			T31Scores[3] = P114();
			T31Scores[4] = P115();

			int best = bestProgram(T31Scores, 5);
			currentVertex = next[best];
			break;
		}
		case T32: {
			const enum vertices next[4] = { T10, T19, T11, T10,  };

			int T32Scores[4];

			T32Scores[0] = P116();
			T32Scores[1] = P113();
			T32Scores[2] = P117();
			T32Scores[3] = P118();

			int best = bestProgram(T32Scores, 4);
			currentVertex = next[best];
			break;
		}
		case T33: {
			const enum vertices next[3] = { T30, T30, T27,  };

			int T33Scores[3];

			T33Scores[0] = P119();
			T33Scores[1] = P120();
			T33Scores[2] = P121();

			int best = bestProgram(T33Scores, 3);
			currentVertex = next[best];
			break;
		}
		case T34: {
			const enum vertices next[5] = { T30, T19, T10, T20, T10,  };

			int T34Scores[5];

			T34Scores[0] = P122();
			T34Scores[1] = P123();
			T34Scores[2] = P70();
			T34Scores[3] = P124();
			T34Scores[4] = P125();

			int best = bestProgram(T34Scores, 5);
			currentVertex = next[best];
			break;
		}
		case T35: {
			const enum vertices next[5] = { T11, T19, T5, T10, T19,  };

			int T35Scores[5];

			T35Scores[0] = P126();
			T35Scores[1] = P113();
			T35Scores[2] = P127();
			T35Scores[3] = P79();
			T35Scores[4] = P128();

			int best = bestProgram(T35Scores, 5);
			currentVertex = next[best];
			break;
		}
		case T36: {
			const enum vertices next[5] = { T32, T10, T30, T19, T30,  };

			int T36Scores[5];

			T36Scores[0] = P129();
			T36Scores[1] = P130();
			T36Scores[2] = P131();
			T36Scores[3] = P113();
			T36Scores[4] = P132();

			int best = bestProgram(T36Scores, 5);
			currentVertex = next[best];
			break;
		}
		case T37: {
			const enum vertices next[3] = { T21, T35, T7,  };

			int T37Scores[3];

			T37Scores[0] = P133();
			T37Scores[1] = P134();
			T37Scores[2] = P135();

			int best = bestProgram(T37Scores, 3);
			currentVertex = next[best];
			break;
		}
		case T38: {
			const enum vertices next[4] = { T36, T4, T19, T37,  };

			int T38Scores[4];

			T38Scores[0] = P136();
			T38Scores[1] = P36();
			T38Scores[2] = P113();
			T38Scores[3] = P137();

			int best = bestProgram(T38Scores, 4);
			currentVertex = next[best];
			break;
		}
		case T39: {
			const enum vertices next[5] = { T33, T31, T19, T28, T11,  };

			int T39Scores[5];

			T39Scores[0] = P138();
			T39Scores[1] = P139();
			T39Scores[2] = P113();
			T39Scores[3] = P140();
			T39Scores[4] = P141();

			int best = bestProgram(T39Scores, 5);
			currentVertex = next[best];
			break;
		}
		case T40: {
			const enum vertices next[5] = { T11, T11, T18, T38, T32,  };

			int T40Scores[5];

			T40Scores[0] = P142();
			T40Scores[1] = P143();
			T40Scores[2] = P100();
			T40Scores[3] = P144();
			T40Scores[4] = P145();

			int best = bestProgram(T40Scores, 5);
			currentVertex = next[best];
			break;
		}
		case T41: {
			const enum vertices next[3] = { T40, T32, T11,  };

			int T41Scores[3];

			T41Scores[0] = P146();
			T41Scores[1] = P147();
			T41Scores[2] = P148();

			int best = bestProgram(T41Scores, 3);
			currentVertex = next[best];
			break;
		}
		case T42: {
			const enum vertices next[4] = { T34, T9, T19, T32,  };

			int T42Scores[4];

			T42Scores[0] = P149();
			T42Scores[1] = P150();
			T42Scores[2] = P151();
			T42Scores[3] = P145();

			int best = bestProgram(T42Scores, 4);
			currentVertex = next[best];
			break;
		}
		case T43: {
			const enum vertices next[5] = { T39, T32, T32, T41, T42,  };

			int T43Scores[5];

			T43Scores[0] = P152();
			T43Scores[1] = P153();
			T43Scores[2] = P154();
			T43Scores[3] = P155();
			T43Scores[4] = P156();

			int best = bestProgram(T43Scores, 5);
			currentVertex = next[best];
			break;
		}
		case T44: {
			const enum vertices next[5] = { T32, T43, A55, T4, T0,  };

			int T44Scores[5];

			T44Scores[0] = P157();
			T44Scores[1] = P158();
			T44Scores[2] = P159();
			T44Scores[3] = P43();
			T44Scores[4] = P160();

			int best = bestProgram(T44Scores, 5);
			currentVertex = next[best];
			break;
		}
		case T45: {
			const enum vertices next[3] = { T44, T19, T44,  };

			int T45Scores[3];

			T45Scores[0] = P161();
			T45Scores[1] = P162();
			T45Scores[2] = P163();

			int best = bestProgram(T45Scores, 3);
			currentVertex = next[best];
			break;
		}
		case T46: {
			const enum vertices next[3] = { T45, T44, T44,  };

			int T46Scores[3];

			T46Scores[0] = P164();
			T46Scores[1] = P165();
			T46Scores[2] = P166();

			int best = bestProgram(T46Scores, 3);
			currentVertex = next[best];
			break;
		}
		case T47: {
			const enum vertices next[3] = { T44, T10, T46,  };

			int T47Scores[3];

			T47Scores[0] = P167();
			T47Scores[1] = P168();
			T47Scores[2] = P169();

			int best = bestProgram(T47Scores, 3);
			currentVertex = next[best];
			break;
		}
		case A48: {
			return 12;
			break;
		}
		case A49: {
			return 13;
			break;
		}
		case A50: {
			return 4;
			break;
		}
		case A51: {
			return 9;
			break;
		}
		case A52: {
			return 7;
			break;
		}
		case A53: {
			return 5;
			break;
		}
		case A54: {
			return 0;
			break;
		}
		case A55: {
			return 3;
			break;
		}
		case A56: {
			return 2;
			break;
		}
		case A57: {
			return 8;
			break;
		}
		case A58: {
			return 6;
			break;
		}
		}
	}
}
