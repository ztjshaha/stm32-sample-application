#ifndef __EMMV5_H__
#define __EMMV5_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "message.h"
typedef enum {
	S_VER   = 0,
	S_RL    = 1,
	S_PID   = 2,
	S_VBUS  = 3,
	S_CPHA  = 5,
	S_ENCL  = 7,
	S_TPOS  = 8,
	S_VEL   = 9,
	S_CPOS  = 10,
	S_PERR  = 11,
	S_FLAG  = 13,
	S_Conf  = 14,
	S_State = 15,
	S_ORG   = 16,
}SysParams_t;

int emmV5readMotorTargetPosition(uint32_t addr);
int emmV5readMotorSpeed(uint32_t addr);
int emmV5ResetCurPosToZero(uint32_t addr);
int emmV5ResetClogPro(uint32_t addr);
int emmV5VelControl(uint32_t addr, uint8_t dir, uint16_t vel, uint8_t acc, bool snF);
int emmV5PosControl(uint32_t addr, uint8_t dir, uint16_t vel, uint8_t acc, uint32_t clk, bool raF, bool snF);

int emmV5ReadSysParams(uint32_t addr, SysParams_t s);
int emmV5StopNow(uint32_t addr, bool snF);
#ifdef __cplusplus
}
#endif

#endif /* __EMMV5_H__ */
