#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

#include "comm.h"
#include "data.h"
#include "wdt.h"

const CliCmdType CMD_WDT_RELOAD = {
	"wdtr",
	1,
	&doWdtReload,
	"  wdtr             Reload the watchdog timer and enable the watchdog if is disabled.\n",
	"  Usage:           "PROGRAM_NAME" wdtr\n",
	"  Example:         "PROGRAM_NAME" wdtr; Reload the watchdog timer on Board #0 with the period \n"
};
int doWdtReload(int argc, char *argv[]) {
	(void)argv;

	if(argc != 2) {
		return ARG_CNT_ERR;
	}
	int dev = doBoardInit(0);
	if(dev < 0) {
		return ERROR;
	}
	uint8_t buf[1] = { WDT_RESET_SIGNATURE };
	if (OK != i2cMem8Write(dev, I2C_MEM_WDT_RESET_ADD, buf, 1)) {
		printf("Fail to write watchdog reset key!\n");
		return ERROR;
	}
	return OK;
}

const CliCmdType CMD_WDT_GET_PERIOD = {
	"wdtprd",
	1,
	&doWdtGetPeriod,
	"  wdtprd           Get the watchdog period in seconds, reload command must\n"
	"                   be issue in this interval to prevent Raspberry Pi power off.\n",
	"  Usage:           "PROGRAM_NAME" wdtprd \n",
	"  Example:         "PROGRAM_NAME" wdtprd; Get the watchdog timer period\n"
};
int doWdtGetPeriod(int argc, char *argv[]) {
	(void)argv;
	if(argc != 2) {
		return ARG_CNT_ERR;
	}
	int dev = doBoardInit(0);
	if (dev <= 0) {
		return ERROR;
	}
	uint8_t buf[2];
	if (OK != i2cMem8Read(dev, I2C_MEM_WDT_INTERVAL_GET_ADD, buf, 2)) {
		printf("Fail to read watchdog period!\n");
		return ERROR;
	}
	uint16_t period;
	memcpy(&period, buf, 2);
	printf("%d\n", (int)period);
	return OK;
}

const CliCmdType CMD_WDT_SET_PERIOD = {
	"wdtpwr",
	1,
	&doWdtSetPeriod,
	"  wdtpwr           Set the watchdog period in seconds, reload command must\n"
	"                   be issue in this interval to prevent Raspberry Pi power off.\n",
	"  Usage:           "PROGRAM_NAME" wdtpwr <val> \n",
	"  Example:         "PROGRAM_NAME" wdtpwr 10; Set the watchdog timer period at 10 seconds \n"
};
int doWdtSetPeriod(int argc, char *argv[]) {
	if(argc != 3) {
		return ARG_CNT_ERR;
	}
	int dev = doBoardInit(0);
	if(dev < 0) {
		return ERROR;
	}
	uint16_t period;
	period = (uint16_t)atoi(argv[2]);
	if(0 == period) {
		printf("Invalid period!\n");
		return ERROR;
	}
	uint8_t buff[2];
	memcpy(buff, &period, 2);
	if(OK != i2cMem8Write(dev, I2C_MEM_WDT_INTERVAL_SET_ADD, buff, 2)) {
		printf("Fail to write watchdog period!\n");
		return ERROR;
	}
	return OK;
}

const CliCmdType CMD_WDT_SET_INIT_PERIOD = {
	"wdtipwr",
	1,
	&doWdtSetInitPeriod,
	"  wdtipwr          Set the watchdog initial period in seconds. This period\n"
	"                   is loaded after power cycle, giving Raspberry time to boot.\n",
	"  Usage:           "PROGRAM_NAME" wdtipwr <val> \n",
	"  Example:         "PROGRAM_NAME" wdtipwr 10; Set the watchdog timer initial period at 10 seconds \n"
};
int doWdtSetInitPeriod(int argc, char *argv[]) {
	if(argc != 3) {
		return ARG_CNT_ERR;
	}
	int dev = doBoardInit(0);
	if (dev < 0) {
		return ERROR;
	}
	uint16_t period = atoi(argv[2]);
	if(0 == period) {
		printf("Invalid period!\n");
		return ERROR;
	}
	uint8_t buf[2];
	memcpy(buf, &period, 2);
	if(OK != i2cMem8Write(dev, I2C_MEM_WDT_INIT_INTERVAL_SET_ADD, buf, 2)) {
		printf("Fail to write watchdog period!\n");
		return ERROR;
	}
	return OK;
}

const CliCmdType CMD_WDT_GET_INIT_PERIOD = {
	"wdtiprd",
	1,
	&doWdtGetInitPeriod,
	"  wdtiprd          Get the watchdog initial period in seconds.\n"
	"                   This period is loaded after power cycle, giving Raspberry time to boot\n",
	"  Usage:           "PROGRAM_NAME" wdtiprd \n",
	"  Example:         "PROGRAM_NAME" wdtiprd; Get the watchdog timer initial period\n"
};
int doWdtGetInitPeriod(int argc, char *argv[]) {
	(void)argv;
	if(argc != 2) {
		return ARG_CNT_ERR;
	}
	int dev = doBoardInit(0);
	if(dev < 0) {
		return ERROR;
	}
	uint8_t buf[2];
	if(OK != i2cMem8Read(dev, I2C_MEM_WDT_INIT_INTERVAL_GET_ADD, buf, 2)) {
		printf("Fail to read watchdog period!\n");
		return ERROR;
	}
	uint16_t period;
	memcpy(&period, buf, 2);
	printf("%d\n", (int)period);
	return OK;
}

const CliCmdType CMD_WDT_GET_OFF_PERIOD = {
	"wdtoprd",
	1,
	&doWdtGetOffPeriod,
	"  wdtoprd          Get the watchdog off period in seconds (max 48 days).\n"
	"                   This is the time that watchdog mantain Raspberry turned off \n",
	"  Usage:           "PROGRAM_NAME" wdtoprd \n",
	"  Example:         "PROGRAM_NAME" wdtoprd; Get the watchdog off period\n"
};
int doWdtGetOffPeriod(int argc, char *argv[])
{
	(void)argv;
	if(argc != 2) {
		return ARG_CNT_ERR;
	}
	int dev = doBoardInit(0);
	if (dev < 0) {
		return ERROR;
	}
	uint8_t buf[4];
	if (OK != i2cMem8Read(dev, I2C_MEM_WDT_POWER_OFF_INTERVAL_GET_ADD, buf, 4)) {
		printf("Fail to read watchdog period!\n");
		return ERROR;
	}
	uint32_t period;
	memcpy(&period, buf, 4);
	printf("%d\n", (int)period);

	return OK;
}

const CliCmdType CMD_WDT_SET_OFF_PERIOD = {
	"wdtopwr",
	1,
	&doWdtSetOffPeriod,
	"  wdtopwr          Set the watchdog off period in seconds (max 48 days).\n"
	"                   This is the time that watchdog mantain Raspberry turned off \n",
	"  Usage:           "PROGRAM_NAME" wdtopwr <val> \n",
	"  Example:         "PROGRAM_NAME" wdtopwr 10; Set the watchdog off interval at 10 seconds \n"
};
int doWdtSetOffPeriod(int argc, char *argv[]) {
	if(argc != 3) {
		return ARG_CNT_ERR;
	}
	int dev = doBoardInit(0);
	if (dev < 0) {
		return ERROR;
	}
	uint32_t period = (uint32_t)atoi(argv[2]);
	if ( (0 == period) || (period > 1 << 20 /* TODO: USE WDT_MAX_OFF_INTERVAL_S */)) {
		printf("Invalid period!\n");
		return ARG_RANGE_ERROR;
	}
	uint8_t buf[4];
	memcpy(buf, &period, 4);
	if (OK != i2cMem8Write(dev, I2C_MEM_WDT_POWER_OFF_INTERVAL_SET_ADD, buf, 4)) {
		printf("Fail to write watchdog period!\n");
		return ERROR;
	}
	return OK;
}

const CliCmdType CMD_WDT_GET_RESET_COUNT = {
	"wdtrcrd",
	1,
	&doWdtGetResetCount,
	"  wdtrcrd          Get the watchdog numbers of performed repowers.\n",
	"  Usage:           "PROGRAM_NAME" wdtrcrd \n",
	"  Example:         "PROGRAM_NAME" wdtrcrd; Get the watchdog reset count\n"
};
int doWdtGetResetCount(int argc, char *argv[]) {
	(void)argv;
	if(argc != 2) {
		return ARG_CNT_ERR;
	}
	int dev = doBoardInit(0);
	if (dev < 0) {
		return ERROR;
	}
	uint8_t buf[2];
	if (OK != i2cMem8Read(dev, I2C_MEM_WDT_RESET_COUNT_ADD, buf, 2))
	{
		printf("Fail to read watchdog reset count!\n");
		return ERROR;
	}
	uint16_t period;
	memcpy(&period, buf, 2);
	printf("%d\n", (int)period);
	return OK;
}

const CliCmdType CMD_WDT_CLR_RESET_COUNT = {
	"wdtrcclr",
	1,
	&doWdtClearResetCount,
	"  wdtrcclr         Clear the reset count.\n",
	"  Usage:           "PROGRAM_NAME" wdtrcclr\n",
	"  Example:         "PROGRAM_NAME" wdtrcclr -> Clear the watchdog resets count\n"
};
int doWdtClearResetCount(int argc, char *argv[]) {
	(void)argv;
	if(argc != 2) {
		return ARG_CNT_ERR;
	}
	int dev = doBoardInit(0);
	if (dev <= 0) {
		return ERROR;
	}
	uint8_t buf[1] = { WDT_RESET_COUNT_SIGNATURE };
	if (OK != i2cMem8Write(dev, I2C_MEM_WDT_CLEAR_RESET_COUNT_ADD, buf, 1))
	{
		printf("Fail to clear the reset count!\n");
		return ERROR;
	}
	return OK;
}


const CliCmdType CMD_PWR_SET_CTRL_CH = {
	"pchwr",
	1,
	&doPwrSetCtrlCh,
	"  pchwr          Set the power control channel.\n",
	"  Usage:           "PROGRAM_NAME" pchwr <val>\n",
	"  Example:         "PROGRAM_NAME" pchwr 1; Set the power control channel to 1\n"
};
int doPwrSetCtrlCh(int argc, char *argv[]) {
	if(argc != 3) {
		return ARG_CNT_ERR;
	}
	int dev = doBoardInit(0);
	if (dev < 0) {
		return ERROR;
	}
	int ch = atoi(argv[2]);
	if ( (ch < 0) || (ch > 16) ) {
		printf("Invalid power control channel! Only 0 to 16 are valid. 0 means turn off.\n");
		return ARG_RANGE_ERROR;
	}
	uint8_t buf[1] = { (uint8_t)ch };
	if (OK != i2cMem8Write(dev, I2C_MEM_DIN_POWER_CTRL_CH_ADD, buf, 1)) {
		printf("Fail to write power control channel!\n");
		return ERROR;
	}
	return OK;
}

const CliCmdType CMD_PWR_GET_CTRL_CH = {
	"pchrd",
	1,
	&doPwrGetCtrlCh,
	"  pchrd          Get the power control channel.\n",
	"  Usage:           "PROGRAM_NAME" pchrd\n",
	"  Example:         "PROGRAM_NAME" pchrd; Get the power control channel\n"
};

int doPwrGetCtrlCh(int argc, char *argv[]) {
	(void)argv;
	if(argc != 2) {
		return ARG_CNT_ERR;
	}
	int dev = doBoardInit(0);
	if (dev < 0) {
		return ERROR;
	}
	uint8_t buf[1];
	if (OK != i2cMem8Read(dev, I2C_MEM_DIN_POWER_CTRL_CH_ADD, buf, 1)) {
		printf("Fail to read power control channel!\n");
		return ERROR;
	}
	if (buf[0] == 0) {
		printf("Power control disabled\n");
	} else {	
	printf("%d\n", (int)buf[0]);
	}
	return OK;
}

const CliCmdType CMD_PWR_SET_OFF_DELAY = {
	"podwr",
	1,
	&doPwrSetOffDelay,
	"  podwr          Set the power off delay in seconds.\n",
	"  Usage:           "PROGRAM_NAME" podwr <val>\n",
	"  Example:         "PROGRAM_NAME" podwr 10; Set the power off delay at 10 seconds\n"
};
int doPwrSetOffDelay(int argc, char *argv[]) {
	if(argc != 3) {
		return ARG_CNT_ERR;
	}
	int dev = doBoardInit(0);
	if (dev < 0) {
		return ERROR;
	}
	uint16_t delay = atoi(argv[2]);
	if(delay < 5 || delay > 300) {
		printf("Invalid power off delay! Only 5 to 300 seconds are valid.\n");
		return ARG_RANGE_ERROR;
	}
	uint8_t buf[2];
	memcpy(buf, &delay, 2);
	if (OK != i2cMem8Write(dev, I2C_MEM_POWER_OFF_DELAY_S_ADD, buf, 2)) {
		printf("Fail to write power off delay!\n");
		return ERROR;
	}
	return OK;
}

const CliCmdType CMD_PWR_GET_OFF_DELAY = {
	"podrd",
	1,
	&doPwrGetOffDelay,
	"  podrd          Get the power off delay in seconds.\n",
	"  Usage:           "PROGRAM_NAME" podrd\n",
	"  Example:         "PROGRAM_NAME" podrd; Get the power off delay \n"
};
int doPwrGetOffDelay(int argc, char *argv[]) {
	(void)argv;
	if(argc != 2) {
		return ARG_CNT_ERR;
	}
	int dev = doBoardInit(0);
	if (dev < 0) {
		return ERROR;
	}
	uint8_t buf[2];
	if (OK != i2cMem8Read(dev, I2C_MEM_POWER_OFF_DELAY_S_ADD, buf, 2)) {
		printf("Fail to read power off delay!\n");
		return ERROR;
	}
	uint16_t delay;
	memcpy(&delay, buf, 2);
	printf("%d\n", (int)delay);
	return OK;
}

const CliCmdType CMD_PWR_GET_PRESENT = {
	"pwrprd",
	1,
	&doPwrGetPresent,
	"  pwrprd          Get the power control status.\n",
	"  Usage:           "PROGRAM_NAME" pwrprd\n",
	"  Example:         "PROGRAM_NAME" pwrprd; Get the power control status\n"
};
int doPwrGetPresent(int argc, char *argv[]) {
	(void)argv;
	if(argc != 2) {
		return ARG_CNT_ERR;
	}
	int dev = doBoardInit(0);
	if (dev < 0) {
		return ERROR;
	}
	uint8_t buf[1];
	if (OK != i2cMem8Read(dev, I2C_MEM_POWER_PRESENT, buf, 1)) {
		printf("Fail to read power present status!\n");
		return ERROR;
	}
	printf("%d\n", (int)buf[0]);
	return OK;
}

const CliCmdType CMD_PWR_ON_DEBOUNCE_SET = {
	"pdonwr",
	1,
	&doPwrOnDebounceSet,
	"  pdonwr          Set the power on debounce time in milliseconds.\n",
	"  Usage:           "PROGRAM_NAME" pdonwr <val>\n",
	"  Example:         "PROGRAM_NAME" pdonwr 100; Set the power on debounce time at 100 ms\n"
};

int doPwrOnDebounceSet(int argc, char *argv[]) {
	if(argc != 3) {
		return ARG_CNT_ERR;
	}
	int dev = doBoardInit(0);
	if (dev < 0) {
		return ERROR;
	}
	uint16_t debounce = atoi(argv[2]);
	if(debounce < 100 || debounce > 500) {
		printf("Invalid power on debounce time! Only 100 to 500 ms are valid.\n");
		return ARG_RANGE_ERROR;
	}
	uint8_t buf[2];
	memcpy(buf, &debounce, 2);
	if (OK != i2cMem8Write(dev, I2C_MEM_DIN_DEBOUNCE_ON_MS_ADD, buf, 2)) {
		printf("Fail to write power on debounce time!\n");
		return ERROR;
	}
	return OK;
}

const CliCmdType CMD_PWR_ON_DEBOUNCE_GET = {
	"pdonrd",
	1,
	&doPwrOnDebounceGet,
	"  pdonrd          Get the power on debounce time in milliseconds.\n",
	"  Usage:           "PROGRAM_NAME" pdonrd\n",
	"  Example:         "PROGRAM_NAME" pdonrd; Get the power on debounce time\n"
};
int doPwrOnDebounceGet(int argc, char *argv[]) {
	(void)argv;
	if(argc != 2) {
		return ARG_CNT_ERR;
	}
	int dev = doBoardInit(0);
	if (dev < 0) {
		return ERROR;
	}
	uint8_t buf[2];
	if (OK != i2cMem8Read(dev, I2C_MEM_DIN_DEBOUNCE_ON_MS_ADD, buf, 2)) {
		printf("Fail to read power on debounce time!\n");
		return ERROR;
	}
	uint16_t debounce;
	memcpy(&debounce, buf, 2);
	printf("%d\n", (int)debounce);
	return OK;
}

const CliCmdType CMD_PWR_OFF_DEBOUNCE_SET = {
	"pdoffwr",
	1,
	&doPwrOffDebounceSet,
	"  pdoffwr          Set the power off debounce time in milliseconds.\n",
	"  Usage:           "PROGRAM_NAME" pdoffwr <val>\n",
	"  Example:         "PROGRAM_NAME" pdoffwr 500; Set the power off debounce time at 500 ms\n"
};

int doPwrOffDebounceSet(int argc, char *argv[]) {
	if(argc != 3) {
		return ARG_CNT_ERR;
	}
	int dev = doBoardInit(0);
	if (dev < 0) {
		return ERROR;
	}
	uint16_t debounce = atoi(argv[2]);
	if(debounce < 500 || debounce > 2000) {
		printf("Invalid power off debounce time! Only 500 to 2000 ms are valid.\n");
		return ARG_RANGE_ERROR;
	}
	uint8_t buf[2];
	memcpy(buf, &debounce, 2);
	if (OK != i2cMem8Write(dev, I2C_MEM_DIN_DEBOUNCE_OFF_MS_ADD, buf, 2)) {
		printf("Fail to write power off debounce time!\n");
		return ERROR;
	}
	return OK;
}

const CliCmdType CMD_PWR_OFF_DEBOUNCE_GET = {
	"pdoffrd",
	1,
	&doPwrOffDebounceGet,
	"  pdoffrd          Get the power off debounce time in milliseconds.\n",
	"  Usage:           "PROGRAM_NAME" pdoffrd\n",
	"  Example:         "PROGRAM_NAME" pdoffrd; Get the power off debounce time	\n"
};
int doPwrOffDebounceGet(int argc, char *argv[]) {
	(void)argv;
	if(argc != 2) {
		return ARG_CNT_ERR;
	}
	int dev = doBoardInit(0);
	if (dev < 0) {
		return ERROR;
	}
	uint8_t buf[2];
	if (OK != i2cMem8Read(dev, I2C_MEM_DIN_DEBOUNCE_OFF_MS_ADD, buf, 2)) {
		printf("Fail to read power off debounce time!\n");
		return ERROR;
	}
	uint16_t debounce;
	memcpy(&debounce, buf, 2);
	printf("%d\n", (int)debounce);
	return OK;
}



// vi:fdm=marker
