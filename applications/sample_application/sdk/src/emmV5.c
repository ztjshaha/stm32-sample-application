#include "../include/emmV5.h"

sdkErr_t emmV5EnControl(stepmotor_device_t *device,stepmotor_status_t state, bool snF)
{
  uint8_t buffer[16] = {0};
  device->status = state;
  device->snF = snF;
  buffer[0] =  smEnControl;
  buffer[1] =  0xAB;
  buffer[2] =  device->status;
  buffer[3] =  device->snF;
  buffer[4] =  0x6B;

  if( can_send_msg(device->device_id,buffer,5) != SDK_OK)
  {
	return SDK_ERR;
  }

  return SDK_OK;
}

sdkErr_t emmV5ModifyCtrlMode(stepmotor_device_t *device, bool snF, uint8_t ctrl_mode)
{
  uint8_t buffer[16] = {0};

  device->snF = snF;
  device->ctrl_mode = ctrl_mode;
  buffer[0] =  smChangeCtrlMode;
  buffer[1] =  0x69;
  buffer[2] =  device->snF;
  buffer[3] =  device->ctrl_mode;
  buffer[4] =  0x6B;

  if( can_send_msg(device->device_id,buffer,5) != SDK_OK)
  {
	  return SDK_ERR;
  }
  return SDK_OK;
}

sdkErr_t emmV5readMotorTargetPosition(stepmotor_device_t *device)
{
	uint8_t buffer[16] = {0};

	buffer[0] = smReadSetTargetPos;
	buffer[1] = 0x6B;
	if( can_send_msg(device->device_id,buffer,2) != SDK_OK)
	{
		return SDK_ERR;
	}

	return SDK_OK;
}

sdkErr_t emmV5readMotorSpeed(stepmotor_device_t *device)
{
	uint8_t buffer[16] = {0};

	buffer[0] = smReadCurSpeed;
	buffer[1] = 0x6B;
	if( can_send_msg(device->device_id,buffer,2) != SDK_OK)
	{
		return SDK_ERR;
	}

	return SDK_OK;
}

sdkErr_t emmV5ResetCurPosToZero(stepmotor_device_t *device)
{
    uint8_t buffer[16] = {0x00};

    buffer[0] =  smClearCurPosRot;
    buffer[1] =  0x6D;
    buffer[2] =  0x6B;

	if( can_send_msg(device->device_id,buffer,3) != SDK_OK)
	{
		return SDK_ERR;
	}

	return SDK_OK;
}

sdkErr_t emmV5ClearStallPro(stepmotor_device_t *device)
{
    uint8_t buffer[16] = {0x00};

    buffer[0] =  smClearStallProtect;
    buffer[1] =  0x52;
    buffer[2] =  0x6B;

	if( can_send_msg(device->device_id,buffer,3) != SDK_OK)
	{
		return SDK_ERR;
	}

	return SDK_OK;
}

sdkErr_t emmV5VelControl(stepmotor_device_t *device, uint8_t dir, uint16_t vel, uint8_t acc, bool snF)
{
    uint8_t buffer[16] = {0x00};

    device->dir = dir;
    device->speed = vel;
    device->acceleration = acc;
    device->snF = snF;

    buffer[0] =  smSpeedModeControl;
    buffer[1] =  device->dir;
    buffer[2] =  (uint8_t)(device->speed >> 8);
    buffer[3] =  (uint8_t)(device->speed >> 0);
    buffer[4] =  device->acceleration;
    buffer[5] =  device->snF;
    buffer[6] =  0x6B;

	if( can_send_msg(device->device_id,buffer,7) != SDK_OK)
	{
		return SDK_ERR;
	}
	return SDK_OK;
}

sdkErr_t emmV5PosControl(stepmotor_device_t *device,uint8_t dir, uint16_t vel, uint8_t acc, uint32_t clk, bool raF, bool snF)
{
  device->dir = dir;
  device->speed = vel;
  device->acceleration = acc;
  device->pluse = clk;
  device->raF = raF;
  device->snF = snF;
  uint8_t buffer0[8] = {0x00};
  uint8_t buffer1[8] = {0x00};
  buffer0[0]  =  0xFD;                      // 功能码
  buffer0[1]  =  device->dir;                       // 方向
  buffer0[2]  =  (uint8_t)(device->speed >> 8);       // 速度(RPM)高8位字节
  buffer0[3]  =  (uint8_t)(device->speed >> 0);       // 速度(RPM)低8位字节
  buffer0[4]  =  device->acceleration;                       // 加速度，注意：0是直接启动
  buffer0[5]  =  (uint8_t)(device->pluse >> 24);      // 脉冲数(bit24 - bit31)
  buffer0[6]  =  (uint8_t)(device->pluse >> 16);      // 脉冲数(bit16 - bit23)
  buffer0[7] =  (uint8_t)(device->pluse >> 8);       // 脉冲数(bit8  - bit15)

  buffer1[0]  =  0xFD;                      // 功能码
  buffer1[1] =  (uint8_t)(device->pluse >> 0);       // 脉冲数(bit0  - bit7 )
  buffer1[2] =  device->raF;                       // 相位/绝对标志，false为相对运动，true为绝对值运动
  buffer1[3] =  device->snF;                       // 多机同步运动标志，false为不启用，true为启用
  buffer1[4] =  0x6B;                      // 校验字节
  if( can_send_msg(device->device_id,buffer0,8) != SDK_OK)
  {
      return SDK_ERR;
  }
  if( can_send_msg(device->device_id + 1,buffer1,5) != SDK_OK)
  {
      return SDK_ERR;
  }
  return SDK_OK;
}

sdkErr_t emmV5ReadSysParams(stepmotor_device_t *device, SysParams_t s)
{
  uint8_t i = 0;
  uint8_t buffer[16] = {0x00};

  switch(s)
  {
    case S_VER  : buffer[i] = smReadFWHWVersion; ++i; break;
    case S_RL   : buffer[i] = smReadResPhaseHenrys; ++i; break;
    case S_PID  : buffer[i] = smReadPosLoopPIDParam; ++i; break;
    case S_VBUS : buffer[i] = smReadBusVoltage; ++i; break;
    case S_CPHA : buffer[i] = smReadPhaseCurrent; ++i; break;
    case S_ENCL : buffer[i] = smReadPostCalEncoderValue; ++i; break;
    case S_TPOS : buffer[i] = smReadTargetPos; ++i; break;
    case S_VEL  : buffer[i] = smReadCurSpeed; ++i; break;
    case S_CPOS : buffer[i] = smReadCurPos; ++i; break;
    case S_PERR : buffer[i] = smReadPosErr; ++i; break;
    case S_FLAG : buffer[i] = smReadStatusFlag; ++i; break;
    case S_ORG  : buffer[i] = smReadReturnZeroFlag; ++i; break;
    case S_Conf : buffer[i] = smReadDriverConfigParams; ++i; buffer[i] = 0x6C; ++i; break;
    case S_State: buffer[i] = smReadSysStatusParams; ++i; buffer[i] = 0x7A; ++i; break;
    default: break;
  }

  buffer[i] = 0x6B; ++i;

  if( can_send_msg(device->device_id,buffer,i) != SDK_OK)
  {
	  return SDK_ERR;
  }
  return SDK_OK;
}

sdkErr_t emmV5StopNow(stepmotor_device_t *device, bool snF)
{
    uint8_t buffer[16] = {0x00};
    device->snF = snF;
    buffer[0] =  smStopNowControl;
    buffer[1] =  0x98;
    buffer[2] =  device->snF;
    buffer[3] =  0x6B;

    if( can_send_msg(device->device_id,buffer,4) != SDK_OK)
    {
  	  return SDK_ERR;
    }
    return SDK_OK;
}
sdkErr_t emmV5Synchronousmotion(stepmotor_device_t *device)
{
  uint8_t buffer[16] = {0};

  buffer[0] =  smSyncMotion;
  buffer[1] =  0x66;
  buffer[2] =  0x6B;

  if( can_send_msg(device->device_id,buffer,3) != SDK_OK)
  {
	  return SDK_ERR;
  }
  return SDK_OK;
}

sdkErr_t emmV5OriginSetO(stepmotor_device_t *device, bool svF)
{
  uint8_t buffer[16] = {0};

  buffer[0] =  smOneLoopZeroPos;
  buffer[1] =  0x88;
  buffer[2] =  svF;
  buffer[3] =  0x6B;

  if( can_send_msg(device->device_id,buffer,4) != SDK_OK)
  {
	  return SDK_ERR;
  }
  return SDK_OK;
}

sdkErr_t emmV5OriginModifyParams(stepmotor_device_t *device, bool svF, uint8_t o_mode, uint8_t o_dir, uint16_t o_vel, uint32_t o_tm, uint16_t sl_vel, uint16_t sl_ma, uint16_t sl_ms, bool potF)
{
  uint8_t buffer[32] = {0};


  buffer[0] =  smChangeReturnZeroParam;
  buffer[1] =  0xAE;
  buffer[2] =  svF;
  buffer[3] =  o_mode;
  buffer[4] =  o_dir;
  buffer[5]  =  (uint8_t)(o_vel >> 8);
  buffer[6]  =  (uint8_t)(o_vel >> 0);
  buffer[7]  =  (uint8_t)(o_tm >> 24);
  if( can_send_msg(device->device_id,buffer,8) != SDK_OK)
  {
	  return SDK_ERR;
  }

  buffer[1]  =  (uint8_t)(o_tm >> 16);
  buffer[2] =  (uint8_t)(o_tm >> 8);
  buffer[3] =  (uint8_t)(o_tm >> 0);
  buffer[4] =  (uint8_t)(sl_vel >> 8);
  buffer[5] =  (uint8_t)(sl_vel >> 0);
  buffer[6] =  (uint8_t)(sl_ma >> 8);
  buffer[7] =  (uint8_t)(sl_ma >> 0);
  if( can_send_msg(device->device_id + 1,buffer,8) != SDK_OK)
  {
	  return SDK_ERR;
  }

  buffer[1] =  (uint8_t)(sl_ms >> 8);
  buffer[2] =  (uint8_t)(sl_ms >> 0);
  buffer[3] =  potF;
  buffer[4] =  0x6B;
  if( can_send_msg(device->device_id + 2,buffer,4) != SDK_OK)
  {
	  return SDK_ERR;
  }
  return SDK_OK;
}

sdkErr_t emmV5OriginTriggerReturn(stepmotor_device_t *device, ZeroMode_t o_mode, bool snF)
{
  uint8_t buffer[16] = {0};

  device->snF = snF;
  buffer[0] =  smZeroPos;
  buffer[1] =  o_mode;
  buffer[2] =  snF;
  buffer[3] =  0x6B;

  if( can_send_msg(device->device_id,buffer,4) != SDK_OK)
  {
	  return SDK_ERR;
  }
  return SDK_OK;
}

sdkErr_t emmV5OriginInterrupt(stepmotor_device_t *device)
{
  uint8_t buffer[16] = {0};

  buffer[0] =  smForceDisableReturnZeo;
  buffer[1] =  0x48;
  buffer[2] =  0x6B;

  if( can_send_msg(device->device_id,buffer,3) != SDK_OK)
  {
	  return SDK_ERR;
  }
  return SDK_OK;
}
