#include "analog.h"
#include "u10in.h"

bool badU10InCh(int ch) {
	if(!(MIN_CH_NO <= ch && ch <= V_IN_CH_NO)) {
		printf("0-20V input channel out of range![%d..%d]\n", MIN_CH_NO, V_IN_CH_NO);
		return true;
	}
	return false;
}

bool badODCh(int ch) {
	if(!(MIN_CH_NO <= ch && ch <= OD_CH_NO)) {
		printf("Open drain output channel out of range![%d..%d]\n", MIN_CH_NO, OD_CH_NO);
		return true;
	}
	return false;
}

const CliCmdType CMD_U10_IN_READ = {/*{{{*/
	"uinrd",
	1,
	&doU10InRead,
	"  uinrd            Read 0-20V input voltage value(V)\n",
	"  Usage:           "PROGRAM_NAME" uinrd <channel>\n",
	"  Example:         "PROGRAM_NAME" uinrd 2 #Read voltage on 0-20V input channel #2\n",
};
int doU10InRead(int argc, char *argv[]) {
	if(argc != 3) {
		return ARG_CNT_ERR;
	}
	int dev = doBoardInit(0);
	if(dev < 0) {
		return ERR;
	}
	int ch = atoi(argv[2]);
	if(badU10InCh(ch)) {
		return ARG_RANGE_ERR;
	}
	float val = 0;
	if(OK != val16Get(dev, I2C_MEM_VIN_START, ch, VOLT_TO_MILIVOLT, &val)) {
		return ERR;
	}
	printf("%0.3f\n", val);
	return OK;
}/*}}}*/


const CliCmdType CMD_BL_WR = {/*{{{*/
	"blwr",
	1,
	&dobacklightWr,
	"  blwr            Write backlight value\n",
	"  Usage:           "PROGRAM_NAME" blwr <value>\n",
	"  Example:         "PROGRAM_NAME" blwr 50 #Set backlight to 50%\n",
};
int dobacklightWr(int argc, char *argv[]) {
	if(argc != 3) {
		return ARG_CNT_ERR;
	}
	int dev = doBoardInit(0);
	if(dev < 0) {
		return ERR;
	}
	float val = atof(argv[2]);
	if( (val < 0) || (val > 100) ) {
		printf("Backlight value out of range![0..100]\n");
		return ARG_RANGE_ERR;
	}
	
	if(OK != val16Set(dev, I2C_MEM_BACKLIGHT_PWM, 1, 10, val)) {
		return ERR;
	}
	
	return OK;
}

const CliCmdType CMD_OD_OUT_WRITE = {/*{{{*/
	"odwr",
	1,
	&doODWrite,
	"  odwr            Write Open_drain output PWM value(0-100%)\n",
	"  Usage:           "PROGRAM_NAME" odwr <ch> <value>\n",
	"  Example:         "PROGRAM_NAME" odwr 1 50 #Set Open_drain output #1 PWM to 50%\n",
};
int doODWrite(int argc, char *argv[]) {
	if(argc != 4) {
		return ARG_CNT_ERR;
	}
	int dev = doBoardInit(0);
	if(dev < 0) {
		return ERR;
	}
	int ch = atoi(argv[2]);
	float val = atof(argv[3]);
	if(badODCh(ch)) {
		return ARG_RANGE_ERR;
	}
	if( (val < 0) || (val > 100) ) {
		printf("Open_drain output PWM value out of range![0..100]\n");
		return ARG_RANGE_ERR;
	}
	if(OK != val16Set(dev, I2C_MEM_OD_PWM_START, ch, 10, val)) {
		return ERR;
	}
	return OK;
}/*}}}*/


// const CliCmdType CMD_U10_IN_CAL = {/*{{{*/
// 	"uincal",
// 	2,
// 	&doU10InCal,
// 	"  uincal           Calibrate 0-20V input channel, the calibration must be done in 2 points\n",
// 	"  Usage 1:         "PROGRAM_NAME" <id> uincal <channel> <value(V)>\n"
// 	"  Usage 2:         "PROGRAM_NAME" <id> uincal <channel> reset\n",
// 	"  Example:         "PROGRAM_NAME" 0 uincal 1 0.5; Calibrate the 0-20V input channel #1 on board #0 at 0.5V\n"
// };
// int doU10InCal(int argc, char *argv[]) {
// 	if(argc != 5) {
// 		return ARG_CNT_ERR;
// 	}
// 	int ch = atoi(argv[3]);
// 	if(badU10InCh(ch)) {
// 		return ARG_RANGE_ERR;
// 	}
// 	int dev = doBoardInit(atoi(argv[1]));
// 	if(dev < 0) {
// 		return ERR;
// 	}
// 	if(strcasecmp(argv[4], "reset") == 0) {
// 		if(OK != calibReset(dev, CALIB_CH_V_IN1 + (ch - 1))) {
// 			return ERR;
// 		}
// 		return OK;
// 	}
// 	float value = atof(argv[4]);
// 	if(OK != calibSet(dev, CALIB_CH_V_IN1 + (ch - 1), value)) {
// 		return ERR;
// 	}
// 	return OK;
// }/*}}}*/

// vi: fdm=marker
