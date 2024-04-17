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

typedef enum {
	ONELOOP   = 0,
	ONELOOPDIR    = 1,
	MULLOOPNOLIMIT   = 2,
	MULLOOPLIMIT  = 3
}ZeroMode_t;

//define emmV5 Function mask
#define smEnControl 		0xF3 //verify
#define smSpeedModeControl 	0xF6 //ready
#define smPositionModeControl 	0xFD //ready
#define smStopNowControl 		0xFE
#define smSyncMotion 			0xFF

#define smOneLoopZeroPos 		0x93
#define smZeroPos 				0x9A
#define smForceDisableReturnZeo 0x9C
#define smReadReturnZeroParam 	0x22
#define smChangeReturnZeroParam 0x4C
#define smReadReturnZeroFlag 	0x3B

#define smTrigeEncoderCal 		0x06
#define smClearCurPosRot 		0x0A
#define smClearStallProtect 	0x0E
#define smFactoryReset 			0x0F

#define smReadFWHWVersion 		0x1F
#define smReadResPhaseHenrys 	0x20
#define smReadPosLoopPIDParam 	0x21
#define smReadBusVoltage 		0x24
#define smReadPhaseCurrent 		0x27
#define smReadPostCalEncoderValue 	0x31
#define smReadInPluse 				0x32
#define smReadTargetPos 			0x33
#define smReadSetTargetPos 			0x34
#define smReadCurSpeed 				0x35 //ready
#define smReadCurPos 				0x36 //ready
#define smReadPosErr 				0x37
#define smReadStatusFlag 			0x3A //ready
#define smReadDriverConfigParams 	0x42
#define smReadSysStatusParams 		0x43

#define smChangeResolution 			0x84
#define smChangeIdAddress 			0xAE
#define smChangeCtrlMode 			0x46
#define smChangeOpenModeCurrent 	0x44
#define smChangeDriverConfigParams 	0x48
#define smChangePosLoopPIDParams 	0x4A
#define smChangeComModeSpeed 		0x4F

sdkErr_t emmV5EnControl(stepmotor_device_t *device, bool state, bool snF); //verify
sdkErr_t emmV5ModifyCtrlMode(stepmotor_device_t *device, bool snF, uint8_t ctrl_mode);
sdkErr_t emmV5PosControl(stepmotor_device_t *device,uint8_t dir, uint16_t vel, uint8_t acc, uint32_t clk, bool raF, bool snF); //verify
sdkErr_t emmV5readMotorTargetPosition(stepmotor_device_t *device);
sdkErr_t emmV5readMotorSpeed(stepmotor_device_t *device);
sdkErr_t emmV5ResetCurPosToZero(stepmotor_device_t *device);
sdkErr_t emmV5ClearStallPro(stepmotor_device_t *device);
sdkErr_t emmV5VelControl(stepmotor_device_t *device, uint8_t dir, uint16_t vel, uint8_t acc, bool snF);//verify
sdkErr_t emmV5ReadSysParams(stepmotor_device_t *device, SysParams_t s);//verify part
sdkErr_t emmV5StopNow(stepmotor_device_t *device, bool snF);
sdkErr_t emmV5Synchronousmotion(stepmotor_device_t *device);
sdkErr_t emmV5OriginModifyParams(stepmotor_device_t *device, bool svF, uint8_t o_mode, uint8_t o_dir, uint16_t o_vel, uint32_t o_tm, uint16_t sl_vel, uint16_t sl_ma, uint16_t sl_ms, bool potF);
sdkErr_t emmV5OriginTriggerReturn(stepmotor_device_t *device, ZeroMode_t o_mode, bool snF);
sdkErr_t emmV5OriginInterrupt(stepmotor_device_t *device);

#ifdef __cplusplus
}
#endif

#endif /* __EMMV5_H__ */
