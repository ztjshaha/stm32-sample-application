#include "../include/emmV5.h"

int emmV5readMotorTargetPosition(uint32_t addr)
{
	uint8_t buffer[2] = {0x34,0x6B};
	if( can_send_msg(addr,buffer,2) != HAL_OK)
	{
		return HAL_ERROR;
	}

	return HAL_OK;
}

int emmV5readMotorSpeed(uint32_t addr)
{
	uint8_t buffer[2] = {0x35,0x6B};
	can_send_msg(addr,buffer,2);
	return 0;

}

int emmV5ResetCurPosToZero(uint32_t addr)
{
    uint8_t buffer[16] = {0x00};

    buffer[0] =  0x0A;
    buffer[1] =  0x6D;
    buffer[2] =  0x6B;

	can_send_msg(addr,buffer,3);
	return 0;
}

int emmV5ResetClogPro(uint32_t addr)
{
    uint8_t buffer[16] = {0x00};

    buffer[0] =  0x0E;
    buffer[1] =  0x52;
    buffer[2] =  0x6B;

	can_send_msg(addr,buffer,3);
	return 0;
}

int emmV5VelControl(uint32_t addr, uint8_t dir, uint16_t vel, uint8_t acc, bool snF)
{
    uint8_t buffer[16] = {0x00};
    uint8_t check=0;
    buffer[0] =  0xF6;
    buffer[1] =  dir;
    buffer[2] =  (uint8_t)(vel >> 8);
    buffer[3] =  (uint8_t)(vel >> 0);
    buffer[4] =  acc;
    buffer[5] =  snF;
    buffer[6] =  0x6B;

	if( can_send_msg(addr,buffer,7) != HAL_OK)
	{
		return HAL_ERROR;
	}

	while(can.rxFrameFlag == false);
	for(int i = 0;i < can.CAN_RxMsg.DLC; i++)
	{
	     if((RxData[0] == 0xF7)||(RxData[1] == 0x02)||(RxData[2] == 0x6b))
	    	 check = 1;
	     else
	    	 check = 0;
	}
	can.rxFrameFlag = false;
	if(check == 0)
		return HAL_ERROR;
	else
	return HAL_OK;
}
int emmV5PosControl(uint32_t addr, uint8_t dir, uint16_t vel, uint8_t acc, uint32_t clk, bool raF, bool snF)
{
  uint8_t buffer0[8] = {0x00};
  uint8_t buffer1[8] = {0x00};

  buffer0[0]  =  0xFD;                      // 功能码
  buffer0[1]  =  dir;                       // 方向
  buffer0[2]  =  (uint8_t)(vel >> 8);       // 速度(RPM)高8位字节
  buffer0[3]  =  (uint8_t)(vel >> 0);       // 速度(RPM)低8位字节
  buffer0[4]  =  acc;                       // 加速度，注意：0是直接启动
  buffer0[5]  =  (uint8_t)(clk >> 24);      // 脉冲数(bit24 - bit31)
  buffer0[6]  =  (uint8_t)(clk >> 16);      // 脉冲数(bit16 - bit23)
  buffer0[7] =  (uint8_t)(clk >> 8);       // 脉冲数(bit8  - bit15)

  buffer1[0]  =  0xFD;                      // 功能码
  buffer1[1] =  (uint8_t)(clk >> 0);       // 脉冲数(bit0  - bit7 )
  buffer1[2] =  raF;                       // 相位/绝对标志，false为相对运动，true为绝对值运动
  buffer1[3] =  snF;                       // 多机同步运动标志，false为不启用，true为启用
  buffer1[4] =  0x6B;                      // 校验字节

  if( can_send_msg(addr,buffer0,8) != HAL_OK)
  {
      return HAL_ERROR;
  }
  if( can_send_msg(addr+1,buffer1,5) != HAL_OK)
  {
      return HAL_ERROR;
  }
  return HAL_OK;
}

int emmV5ReadSysParams(uint32_t addr, SysParams_t s)
{
  uint8_t i = 0;
  uint8_t buffer[16] = {0x00};


  switch(s)
  {
    case S_VER  : buffer[i] = 0x1F; ++i; break;
    case S_RL   : buffer[i] = 0x20; ++i; break;
    case S_PID  : buffer[i] = 0x21; ++i; break;
    case S_VBUS : buffer[i] = 0x24; ++i; break;
    case S_CPHA : buffer[i] = 0x27; ++i; break;
    case S_ENCL : buffer[i] = 0x31; ++i; break;
    case S_TPOS : buffer[i] = 0x33; ++i; break;
    case S_VEL  : buffer[i] = 0x35; ++i; break;
    case S_CPOS : buffer[i] = 0x36; ++i; break;
    case S_PERR : buffer[i] = 0x37; ++i; break;
    case S_FLAG : buffer[i] = 0x3A; ++i; break;
    case S_ORG  : buffer[i] = 0x3B; ++i; break;
    case S_Conf : buffer[i] = 0x42; ++i; buffer[i] = 0x6C; ++i; break;
    case S_State: buffer[i] = 0x43; ++i; buffer[i] = 0x7A; ++i; break;
    default: break;
  }

  buffer[i] = 0x6B; ++i;

	can_send_msg(addr,buffer,i);
	return 0;
}

int emmV5StopNow(uint32_t addr, bool snF)
{
    uint8_t buffer[16] = {0x00};

    buffer[0] =  0xFE;
    buffer[1] =  0x98;
    buffer[2] =  snF;
    buffer[3] =  0x6B;

	can_send_msg(addr,buffer,4);
	return 0;
}
