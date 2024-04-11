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
									  sprintf((char*)u_buf,__VA_ARGS__), 0xFFFF);

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

#ifdef __cplusplus
}
#endif

#endif /* __SYSTEMCONFIG_H */
