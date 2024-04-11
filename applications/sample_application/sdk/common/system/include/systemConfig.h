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

#define adiPrintf(...) HAL_UART_Transmit_IT(&huart1,(uint8_t *)u_buf,\
									  sprintf((char*)u_buf,__VA_ARGS__));

#ifdef __cplusplus
}
#endif

#endif /* __SYSTEMCONFIG_H */
