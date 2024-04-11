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

sdkErr_t emmV5EnControl(uint8_t addr, bool state, bool snF);
sdkErr_t emmV5ModifyCtrlMode(uint8_t addr, bool svF, uint8_t ctrl_mode);
sdkErr_t emmV5PosControl(uint32_t addr, uint8_t dir, uint16_t vel, uint8_t acc, uint32_t clk, bool raF, bool snF);
sdkErr_t emmV5readMotorTargetPosition(uint32_t addr);
sdkErr_t emmV5readMotorSpeed(uint32_t addr);
sdkErr_t emmV5ResetCurPosToZero(uint32_t addr);
sdkErr_t emmV5ResetClogPro(uint32_t addr);
sdkErr_t emmV5VelControl(uint32_t addr, uint8_t dir, uint16_t vel, uint8_t acc, bool snF);
sdkErr_t emmV5PosControl(uint32_t addr, uint8_t dir, uint16_t vel, uint8_t acc, uint32_t clk, bool raF, bool snF);
sdkErr_t emmV5ReadSysParams(uint32_t addr, SysParams_t s);
sdkErr_t emmV5StopNow(uint32_t addr, bool snF);
sdkErr_t emmV5Synchronousmotion(uint8_t addr);
sdkErr_t emmV5OriginModifyParams(uint8_t addr, bool svF, uint8_t o_mode, uint8_t o_dir, uint16_t o_vel, uint32_t o_tm, uint16_t sl_vel, uint16_t sl_ma, uint16_t sl_ms, bool potF);
sdkErr_t emmV5OriginTriggerReturn(uint8_t addr, uint8_t o_mode, bool snF);
sdkErr_t emmV5OriginInterrupt(uint8_t addr);

#ifdef __cplusplus
}
#endif

#endif /* __EMMV5_H__ */
