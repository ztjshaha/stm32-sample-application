#ifndef __SYSTEMCONFIG_H
#define __SYSTEMCONFIG_H

#ifdef __cplusplus
extern "C" {
#endif
#include "main.h"
#include <stdlib.h>
#include "stdbool.h"
#include "stdio.h"

extern UART_HandleTypeDef huart1;
extern uint8_t u_buf[256];

#define printf(...) HAL_UART_Transmit(&huart1,(uint8_t *)u_buf,\
									  sprintf((char*)u_buf,__VA_ARGS__), 0xffff);

/**
 *  \brief Enum of possible Errors Detected by HAL layer to be communicated
 *         to ADI APIs.
 */
typedef enum {
	SDK_OK = 0,        /*!< SDK function successful. No error Detected */
	SDK_CAN_FAIL,      /*!< SDK CAN operation failure. CAN controller Down */
	SDK_WAIT_TIMEOUT,  /*!< SDK function Timeout */
	SDK_GEN_SW,        /*!< SDK function failed due to general invalid  HAL data*/
	SDK_WARNING,       /*!< SDK function warning that non critical error was detected*/
	SDK_ERR
} sdkErr_t;

typedef struct stepmotor_status {
	uint8_t SM_EN;
	uint8_t SM_READY;
	uint8_t SM_STALL;
	uint8_t SM_STALLPRO;
	uint8_t SM_ERROR;
} stepmotor_status_t;

typedef struct driverConfigParams{
	uint8_t lenthBytes;
	uint8_t ConfigParamNum;
	uint8_t motorMode;
	uint8_t PulCtrl;
	uint8_t CommMode;
	uint8_t En;
	uint8_t Dir;
	uint8_t resolution;
	uint8_t resolutionCal;
	uint8_t autoLcdDisable;
	uint16_t oLoopCur;
	uint16_t cLStallMaxCur;
	uint16_t cLMaxVlotage;
	uint8_t uartBand;
	uint8_t canBand;
	uint16_t device_id; // Device ID
	uint8_t CommChecksum;
	uint8_t ctrlInstructionResp;
	uint8_t StallPro;
	uint16_t StallProSpeedThread;
	uint16_t StallProCurThread;
	uint16_t StallProTimeThread;
	uint16_t arrived;
} driverConfigParams_t;

typedef struct stepmotor_device {
  driverConfigParams_t driver;
  uint16_t device_id;
  int32_t position;       // current position
  uint16_t target_position; // target position
  uint16_t acceleration;
  uint32_t pluse;
  uint8_t raF;
  uint8_t snF;
  int16_t speed;           // speed
  stepmotor_status_t status; // Statue: 0 - free, 1 - running，2 - error
  uint8_t dir;				// dir: 0 - clockwise, 1 - counterclockwise
  uint8_t ctrl_mode;
  float angle;
} stepmotor_device_t;

#ifdef __cplusplus
}
#endif

#endif /* __SYSTEMCONFIG_H */
