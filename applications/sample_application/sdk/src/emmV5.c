#include "../include/emmV5.h"

sdkErr_t emmV5EnControl(uint8_t addr, bool state, bool snF)
{
  uint8_t buffer[16] = {0};

  buffer[0] =  0xF3;
  buffer[1] =  0xAB;
  buffer[2] =  (uint8_t)state;
  buffer[3] =  snF;
  buffer[4] =  0x6B;

	if( can_send_msg(addr,buffer,5) != SDK_OK)
	{
		return SDK_ERR;
	}

	return SDK_OK;
}

sdkErr_t emmV5ModifyCtrlMode(uint8_t addr, bool svF, uint8_t ctrl_mode)
{
  uint8_t buffer[16] = {0};

  buffer[0] =  0x46;
  buffer[1] =  0x69;
  buffer[2] =  svF;
  buffer[3] =  ctrl_mode;
  buffer[4] =  0x6B;

  if( can_send_msg(addr,buffer,5) != SDK_OK)
  {
	  return SDK_ERR;
  }
  return SDK_OK;
}

sdkErr_t emmV5readMotorTargetPosition(uint32_t addr)
{
	uint8_t buffer[2] = {0x34,0x6B};
	if( can_send_msg(addr,buffer,2) != SDK_OK)
	{
		return SDK_ERR;
	}

	return SDK_OK;
}

sdkErr_t emmV5readMotorSpeed(uint32_t addr)
{
	uint8_t buffer[2] = {0x35,0x6B};
	if( can_send_msg(addr,buffer,2) != SDK_OK)
	{
		return SDK_ERR;
	}

	return SDK_OK;
}

sdkErr_t emmV5ResetCurPosToZero(uint32_t addr)
{
    uint8_t buffer[16] = {0x00};

    buffer[0] =  0x0A;
    buffer[1] =  0x6D;
    buffer[2] =  0x6B;

	if( can_send_msg(addr,buffer,3) != SDK_OK)
	{
		return SDK_ERR;
	}

	return SDK_OK;
}

sdkErr_t emmV5ResetClogPro(uint32_t addr)
{
    uint8_t buffer[16] = {0x00};

    buffer[0] =  0x0E;
    buffer[1] =  0x52;
    buffer[2] =  0x6B;

	if( can_send_msg(addr,buffer,3) != SDK_OK)
	{
		return SDK_ERR;
	}

	return SDK_OK;
}

sdkErr_t emmV5VelControl(uint32_t addr, uint8_t dir, uint16_t vel, uint8_t acc, bool snF)
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

	if( can_send_msg(addr,buffer,7) != SDK_OK)
	{
		return SDK_ERR;
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
		return SDK_ERR;
	else
	return SDK_OK;
}
sdkErr_t emmV5PosControl(uint32_t addr, uint8_t dir, uint16_t vel, uint8_t acc, uint32_t clk, bool raF, bool snF)
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

  if( can_send_msg(addr,buffer0,8) != SDK_OK)
  {
      return SDK_ERR;
  }
  if( can_send_msg(addr+1,buffer1,5) != SDK_OK)
  {
      return SDK_ERR;
  }
  return SDK_OK;
}

sdkErr_t emmV5ReadSysParams(uint32_t addr, SysParams_t s)
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

  if( can_send_msg(addr,buffer,i) != SDK_OK)
  {
	  return SDK_ERR;
  }
  return SDK_OK;
}

sdkErr_t emmV5StopNow(uint32_t addr, bool snF)
{
    uint8_t buffer[16] = {0x00};

    buffer[0] =  0xFE;
    buffer[1] =  0x98;
    buffer[2] =  snF;
    buffer[3] =  0x6B;

    if( can_send_msg(addr,buffer,4) != SDK_OK)
    {
  	  return SDK_ERR;
    }
    return SDK_OK;
}
sdkErr_t emmV5Synchronousmotion(uint8_t addr)
{
  uint8_t buffer[16] = {0};

  buffer[0] =  0xFF;
  buffer[1] =  0x66;
  buffer[2] =  0x6B;

  if( can_send_msg(addr,buffer,3) != SDK_OK)
  {
	  return SDK_ERR;
  }
  return SDK_OK;
}

sdkErr_t emmV5OriginSetO(uint8_t addr, bool svF)
{
  uint8_t buffer[16] = {0};

  buffer[0] =  0x93;
  buffer[1] =  0x88;
  buffer[2] =  svF;
  buffer[3] =  0x6B;

  if( can_send_msg(addr,buffer,4) != SDK_OK)
  {
	  return SDK_ERR;
  }
  return SDK_OK;
}

sdkErr_t emmV5OriginModifyParams(uint8_t addr, bool svF, uint8_t o_mode, uint8_t o_dir, uint16_t o_vel, uint32_t o_tm, uint16_t sl_vel, uint16_t sl_ma, uint16_t sl_ms, bool potF)
{
  uint8_t buffer[32] = {0};


  buffer[0] =  0x4C;
  buffer[1] =  0xAE;
  buffer[2] =  svF;
  buffer[3] =  o_mode;
  buffer[4] =  o_dir;
  buffer[5]  =  (uint8_t)(o_vel >> 8);
  buffer[6]  =  (uint8_t)(o_vel >> 0);
  buffer[7]  =  (uint8_t)(o_tm >> 24);
  if( can_send_msg(addr,buffer,8) != SDK_OK)
  {
	  return SDK_ERR;
  }

  buffer[0]  =  (uint8_t)(o_tm >> 16);
  buffer[1] =  (uint8_t)(o_tm >> 8);
  buffer[2] =  (uint8_t)(o_tm >> 0);
  buffer[3] =  (uint8_t)(sl_vel >> 8);
  buffer[4] =  (uint8_t)(sl_vel >> 0);
  buffer[5] =  (uint8_t)(sl_ma >> 8);
  buffer[6] =  (uint8_t)(sl_ma >> 0);
  buffer[7] =  (uint8_t)(sl_ms >> 8);
  if( can_send_msg(addr + 1,buffer,8) != SDK_OK)
  {
	  return SDK_ERR;
  }

  buffer[0] =  (uint8_t)(sl_ms >> 0);
  buffer[1] =  potF;
  buffer[2] =  0x6B;
  if( can_send_msg(addr + 2,buffer,3) != SDK_OK)
  {
	  return SDK_ERR;
  }
  return SDK_OK;
}

sdkErr_t emmV5OriginTriggerReturn(uint8_t addr, uint8_t o_mode, bool snF)
{
  uint8_t buffer[16] = {0};

  buffer[0] =  0x9A;
  buffer[1] =  o_mode;
  buffer[2] =  snF;
  buffer[3] =  0x6B;

  if( can_send_msg(addr,buffer,4) != SDK_OK)
  {
	  return SDK_ERR;
  }
  return SDK_OK;
}

sdkErr_t emmV5OriginInterrupt(uint8_t addr)
{
  uint8_t buffer[16] = {0};

  buffer[0] =  0x9C;
  buffer[1] =  0x48;
  buffer[2] =  0x6B;

  if( can_send_msg(addr,buffer,3) != SDK_OK)
  {
	  return SDK_ERR;
  }
  return SDK_OK;
}
