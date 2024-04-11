#include "../include/message.h"

CAN_t can = {0};
uint8_t RxData[256];

uint8_t can_send_msg(uint32_t id, uint8_t *msg, uint8_t len)
{
	uint32_t TxMailbox = CAN_TX_MAILBOX0;
	can.CAN_TxMsg.StdId = id;
	can.CAN_TxMsg.ExtId = id;
	can.CAN_TxMsg.IDE = CAN_ID_EXT;
	can.CAN_TxMsg.RTR = CAN_RTR_DATA;
	can.CAN_TxMsg.DLC = len;
	if( HAL_CAN_AddTxMessage(&hcan, &can.CAN_TxMsg,msg, &TxMailbox) != HAL_OK)
	{
		return 1;
	}
	while(HAL_CAN_GetTxMailboxesFreeLevel(&hcan) != 3)
	{
		return 0;
	}
	return 0;
}

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
	uint32_t i = 0;
	if(HAL_CAN_GetRxMessage(hcan,CAN_RX_FIFO0, &can.CAN_RxMsg,RxData)==HAL_OK)
	  {
		can.rxFrameFlag=true;
		printf("GetRxMessage, CANID:0x%0lX,DLC:%lu,Data:",can.CAN_RxMsg.ExtId, can.CAN_RxMsg.DLC);
		for(i = 0;i < can.CAN_RxMsg.DLC; i++)
		{
		    printf("%02x ", RxData[i]);
		}
		printf("\n");
		HAL_CAN_ActivateNotification(hcan, CAN_IT_RX_FIFO0_MSG_PENDING);
	  }
}
