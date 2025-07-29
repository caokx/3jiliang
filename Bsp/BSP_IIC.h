
#ifndef  _BSP_IIC_H
#define  _BSP_IIC_H
//---------------------------------------------------
//----------------------------
//---------------------------------------------------
extern void IIC_FirmMode_Start(void);
extern void IIC_FirmMode_Stop(void);
extern void IIC_FirmMode_Reset(void);
extern u8 IIC_FirmMode_SendByte(u8 B);
extern u8 IIC_FirmMode_ReceiveByte(BOOL ACK);
extern void fnDelay2us(void);
//---------------------------------------------------
#endif  //_IIC_H
//---------------------------------------------------
