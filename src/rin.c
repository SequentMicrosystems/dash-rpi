#include "analog.h"
#include "rin.h"

bool badRInCh(int ch) {
	if(!(MIN_CH_NO <= ch && ch <= R_IN_CH_NO)) {
		printf("Res input channel out of range![%d..%d]\n", MIN_CH_NO, R_IN_CH_NO);
		return true;
	}
	return false;
}

const CliCmdType CMD_R_IN_READ = {/*{{{*/
	"rinrd",
	1,
	&doRInRead,
	"  rinrd            Read thermistor input resistance value(ohms)\n",
	"  Usage:           "PROGRAM_NAME" rinrd <channel>\n",
	"  Example:         "PROGRAM_NAME" rinrd 2 #Read resistance on thermistor input channel #2\n",
};
int doRInRead(int argc, char *argv[]) {
	if(argc != 3) {
		return ARG_CNT_ERR;
	}
	
	int dev = doBoardInit(0);
	if(dev < 0) {
		return ERR;
	}
	int ch = atoi(argv[2]);
	if(badRInCh(ch)) {
		return ARG_RANGE_ERR;
	}
	float val = 0;
	if(OK != val16Get(dev, I2C_MEM_RIN_START, ch, 1, &val)) {
		return ERR;
	}
	printf("%0.0f\n", val);
	return OK;
}/*}}}*/

// const CliCmdType CMD_R1K_IN_CAL = {/*{{{*/
// 	"1kincal",
// 	2,
// 	&doR1KInCal,
// 	"  1kincal           Calibrate 1k thermistor input channel, the calibration must be done in 2 points\n",
// 	"  Usage 1:         "PROGRAM_NAME" <id> 1kincal <channel> <value(ohms)>\n"
// 	"  Usage 2:         "PROGRAM_NAME" <id> 1kincal <channel> reset\n",
// 	"  Example:         "PROGRAM_NAME" 0 1kincal 1 10; Calibrate the 1k thermistor input channel #1 on board #0 at 10 ohms\n"
// };
// int doR1KInCal(int argc, char *argv[]) {
// 	if(argc != 5) {
// 		return ARG_CNT_ERR;
// 	}
// 	int ch = atoi(argv[3]);
// 	if(badRInCh(ch)) {
// 		return ARG_RANGE_ERR;
// 	}
// 	int dev = doBoardInit(atoi(argv[1]));
// 	if(dev < 0) {
// 		return ERR;
// 	}
// 	if(strcasecmp(argv[4], "reset") == 0) {
// 		if(OK != calibReset(dev, CALIB_CH_1K_IN1 + (ch - 1))) {
// 			return ERR;
// 		}
// 		return OK;
// 	}
// 	float value = atof(argv[4]);
// 	if(OK != calibSet(dev, CALIB_CH_1K_IN1 + (ch - 1), value)) {
// 		return ERR;
// 	}
// 	return OK;
// }


