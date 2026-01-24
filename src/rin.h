#ifndef RIN_H_
#define RIN_H_

#include "cli.h"

extern const CliCmdType CMD_R_IN_READ;

// extern const CliCmdType CMD_R1K_IN_CAL;

extern const CliCmdType CMD_R10K_IN_READ;

extern const CliCmdType CMD_R10K_IN_CAL;

int doRInRead(int argc, char *argv[]);

// int doR1KInCal(int argc, char *argv[]);


#endif /* RIN_H_ */
