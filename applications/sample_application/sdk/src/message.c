#include "../include/message.h"

CAN_t can = {0};
uint8_t RxData[256];

sdkErr_t can_send_msg(uint32_t id, uint8_t *msg, uint8_t len)
{
	uint32_t TxMailbox = CAN_TX_MAILBOX0;
	can.CAN_TxMsg.StdId = id;
	can.CAN_TxMsg.ExtId = id;
	can.CAN_TxMsg.IDE = CAN_ID_EXT;
	can.CAN_TxMsg.RTR = CAN_RTR_DATA;
	can.CAN_TxMsg.DLC = len;
	if( HAL_CAN_AddTxMessage(&hcan, &can.CAN_TxMsg,msg, &TxMailbox) != HAL_OK)
	{
		return SDK_CAN_FAIL;
	}
	while(HAL_CAN_GetTxMailboxesFreeLevel(&hcan) != 3)
	{
		return SDK_OK;
	}
	return SDK_OK;
}

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
//	uint32_t i = 0;
	if(HAL_CAN_GetRxMessage(hcan,CAN_RX_FIFO0, &can.CAN_RxMsg,RxData)==HAL_OK)
	  {
		if(can.CAN_RxMsg.ExtId ==  motor0.device_id){
			switch(RxData[0]){
			case 00:{
				printf("error Instruction!\n");
			}
			case smReadCurSpeed:{
				if(RxData[1] == 1)
				{
					motor0.speed = -((RxData[2] << 8) + RxData[3]);
				}else
					motor0.speed = (RxData[2] << 8) + RxData[3];
				break;
			}
			case smReadCurPos:{
				if(RxData[1] == 1)
				{
					motor0.position = -((RxData[2] << 24) + (RxData[3] << 16)+ (RxData[4] << 8) + (RxData[5] << 0));
				}else
					motor0.position = (RxData[2] << 24) + (RxData[3] << 16)+ (RxData[4] << 8) + (RxData[5] << 0);
				motor0.angle = (float)(motor0.position * 360) / 65536;
				break;
			}
			case smReadStatusFlag:{
				motor0.status.SM_EN = RxData[1] & 0x01;
				motor0.status.SM_READY = RxData[1] & 0x02;
				motor0.status.SM_STALL = RxData[1] & 0x04;
				motor0.status.SM_STALLPRO = RxData[1] & 0x08;
				break;
			}
			default:
			        printf("Invalid function mask\n");
			}
		}else
			printf("Fail no motor!\n");
	  }
		can.rxFrameFlag = true;
//
//		printf("GetRxMessage, CANID:0x%0lX,DLC:%lu,Data:",can.CAN_RxMsg.ExtId, can.CAN_RxMsg.DLC);
//		for(i = 0;i < can.CAN_RxMsg.DLC; i++)
//		{
//		    printf("%02x ", RxData[i]);
//		}
//		printf("\n");
		HAL_CAN_ActivateNotification(hcan, CAN_IT_RX_FIFO0_MSG_PENDING);
}

