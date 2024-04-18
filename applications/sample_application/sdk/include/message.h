#ifndef __MESSAGE_H__
#define __MESSAGE_H__

#ifdef __cplusplus
extern "C" {
#endif
#include "main.h"
#include "stdbool.h"
typedef struct {
	CAN_RxHeaderTypeDef CAN_RxMsg;
	CAN_TxHeaderTypeDef CAN_TxMsg;
	bool rxFrameFlag;
}CAN_t;


extern CAN_HandleTypeDef hcan;
extern CAN_t can;
extern uint8_t RxData[256];
extern stepmotor_device_t motor0;

uint8_t can_send_msg(uint32_t id, uint8_t *msg, uint8_t len);

#ifdef __cplusplus
}
#endif

#endif /* __MESSAGE_H__ */
