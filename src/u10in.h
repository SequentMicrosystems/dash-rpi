#ifndef U5IN_H_
#define U5IN_H_

#include "cli.h"

extern const CliCmdType CMD_U10_IN_READ;
extern const CliCmdType CMD_BL_WR;
extern const CliCmdType CMD_OD_OUT_WRITE;
extern const CliCmdType CMD_VCC_READ;
// extern const CliCmdType CMD_U10_IN_CAL;


int doU10InRead(int argc, char *argv[]);
int dobacklightWr(int argc, char *argv[]);
int doODWrite(int argc, char *argv[]);
int doVccRead(int argc, char *argv[]);
// int doU10InCal(int argc, char *argv[]);

#endif /* U5IN_H_ */
