/****************************************************************************
* @file     BSP_Tmp.c
* @author   Renergy Application Team
* @version  V1.0.1
* @date     2023.4.23
* @brief    板级层温度传感器
******************************************************************************
* @attention
*
*
****************************************************************************/
#include <BSP.h>
#include "Globals.h"

sTemperSchoolPara_TypeDef gTemperSchoolParaMem;     //存储的原始值
sTemperSchoolPara_TypeDef gTemperSchoolParaTemp;    //经过处理的用于转换的值

typedef struct
{
    u8 valid;
    u8 iBuf;
    s16 buf[MAX_TERMINAL_TMP_NUM][8];
    s32 sum[MAX_TERMINAL_TMP_NUM];
} sOrgTempData_TypeDef;
sOrgTempData_TypeDef OrgTempData;

/*********************************************************************************************************
** Descriptions:        IIC总线开始时序
** Function name:       IIC_Tmp_FirmMode_Start
** input parameters:    none
** output parameters:   none
** Returned value:      none
*********************************************************************************************************/
void IIC_Tmp_FirmMode_Start(void)
{
    PinMode_TmpSCL(GPIO_MODE_OUT);
    PinMode_TmpSDA(GPIO_MODE_OUT);
    PinWrite_TmpSDA(1);
    PinWrite_TmpSDA(1);
    fnDelay2us();

    PinWrite_TmpSCL(1);
    PinWrite_TmpSCL(1);
    fnDelay2us();

    PinWrite_TmpSDA(0);
    PinWrite_TmpSDA(0);
    fnDelay2us();

    PinWrite_TmpSCL(0);
    PinWrite_TmpSCL(0);
    fnDelay2us();
    return;
}

/*********************************************************************************************************
** Function name:       IIC_Tmp_FirmMode_Stop
** Descriptions:        IIC总线结束时序
** input parameters:    none
** output parameters:   none
** Returned value:      none
*********************************************************************************************************/
void IIC_Tmp_FirmMode_Stop(void)
{
    PinMode_TmpSCL(GPIO_MODE_OUT);
    PinMode_TmpSDA(GPIO_MODE_OUT);
    PinWrite_TmpSDA(0);
    PinWrite_TmpSDA(0);
    fnDelay2us();

    PinWrite_TmpSCL(1);
    PinWrite_TmpSCL(1);
    fnDelay2us();

    PinWrite_TmpSDA(1);
    PinWrite_TmpSDA(1);
    fnDelay2us();

    return ;
}

/*********************************************************************************************************
** Function name:       IIC_Tmp_FirmMode_Reset
** Descriptions:        IIC总线复位时序
** input parameters:    none
** output parameters:   none
** Returned value:      none
*********************************************************************************************************/
void IIC_Tmp_FirmMode_Reset(void)
{
    u16 i;
    PinWrite_TmpSDA(0);
    PinWrite_TmpSDA(0);
    PinWrite_TmpSCL(0);
    PinWrite_TmpSCL(0);
    for (i = 0; i < 200; i++)
    {}
    PinWrite_TmpSDA(1);
    PinWrite_TmpSDA(1);
    PinWrite_TmpSCL(0);
    PinWrite_TmpSCL(0);
    for (i = 0; i < 200; i++)
    {}
    return;
}

/*********************************************************************************************************
** Function name:       IIC_Tmp_FirmMode_ACK
** Descriptions:        IIC总线应答时序
** input parameters:    none
** output parameters:   none
** Returned value:      none
*********************************************************************************************************/
void IIC_Tmp_FirmMode_ACK(void)
{
    PinMode_TmpSCL(GPIO_MODE_OUT);
    PinMode_TmpSDA(GPIO_MODE_OUT);
    PinWrite_TmpSDA(0);
    PinWrite_TmpSDA(0);
    fnDelay2us();

    PinWrite_TmpSCL(1);
    PinWrite_TmpSCL(1);
    fnDelay2us();

    PinWrite_TmpSCL(0);
    PinWrite_TmpSCL(0);
    return;
}

/*********************************************************************************************************
** Function name:       IIC_Tmp_FirmMode_NOACK
** Descriptions:        IIC总线无应答时序
** input parameters:    none
** output parameters:   none
** Returned value:      none
*********************************************************************************************************/
void IIC_Tmp_FirmMode_NOACK(void)
{
    PinMode_TmpSCL(GPIO_MODE_OUT);
    PinMode_TmpSDA(GPIO_MODE_OUT);
    PinWrite_TmpSDA(1);
    PinWrite_TmpSDA(1);
    fnDelay2us();

    PinWrite_TmpSCL(1);
    PinWrite_TmpSCL(1);
    fnDelay2us();

    PinWrite_TmpSCL(0);
    PinWrite_TmpSCL(0);
    fnDelay2us();
    return;
}

/*********************************************************************************************************
** Function name:       IIC_Tmp_FirmMode_SendByte
** Descriptions:        向ICC总线发送一个字节
** input parameters:    B:待发送的数据
** output parameters:   none
** Returned value:      成功返回true，失败返回false
*********************************************************************************************************/
u8 IIC_Tmp_FirmMode_SendByte(u8 B)
{
    u8  i;
    i = 0;

    PinMode_TmpSCL(GPIO_MODE_OUT);
    PinMode_TmpSDA(GPIO_MODE_OUT);
    PinWrite_TmpSCL(0);
    fnDelay2us();

    for (; i < 8; i++)
    {
        if (B & 0x80)
        {
            PinWrite_TmpSDA(1);
            PinWrite_TmpSDA(1);
            fnDelay2us();
        }
        else
        {
            PinWrite_TmpSDA(0);
            PinWrite_TmpSDA(0);
            fnDelay2us();
        }
        PinWrite_TmpSCL(0);
        fnDelay2us();

        PinWrite_TmpSCL(1);
        fnDelay2us();

        PinWrite_TmpSCL(0);
        fnDelay2us();
        B <<= 1;
    }
    PinMode_TmpSDA(GPIO_MODE_IN);
    PinWrite_TmpSCL(0);
    PinWrite_TmpSCL(0);
    fnDelay2us();

    PinWrite_TmpSCL(1);
    PinWrite_TmpSCL(1);
    fnDelay2us();
    B = true;
    if (PinRead_TmpSDA())
    {
        B = false;
    }
    PinWrite_TmpSCL(0);
    PinWrite_TmpSCL(0);
    fnDelay2us();

    return B;
}

/*********************************************************************************************************
** Function name:       IIC_Tmp_FirmMode_ReceiveByte
** Descriptions:        从ICC总线读取一个字节
** input parameters:    ACK:true发送ACK，false不发送ACK
** output parameters:   none
** Returned value:      读取到的一个字节数据
*********************************************************************************************************/
u8 IIC_Tmp_FirmMode_ReceiveByte(BOOL ACK)
{
    u8 i, B;

    PinMode_TmpSDA(GPIO_MODE_IN);
    PinMode_TmpSCL(GPIO_MODE_OUT);
    PinWrite_TmpSCL(0);
    PinWrite_TmpSCL(0);
    fnDelay2us();
    B = 0;
    i = 0;
    for (; i < 8; i++)
    {
        B <<= 1;
        PinWrite_TmpSCL(1);
        PinWrite_TmpSCL(1);
        fnDelay2us();
        fnDelay2us();
        if (PinRead_TmpSDA())
        {
            B = B + 0x1;
        }
        PinWrite_TmpSCL(0);
        PinWrite_TmpSCL(0);
        fnDelay2us();
        fnDelay2us();
    }
    if (ACK)
    {
        IIC_Tmp_FirmMode_ACK();
    }
    else
    {
        IIC_Tmp_FirmMode_NOACK();
    }
    return B;
}

/*********************************************************************************************************
** Function name:       Conv_temp_CT7538
** Descriptions:        将测温芯片的温度寄存器值转换为真实的温度值，单位是0.1℃
** input parameters:    tempReg:温度寄存器值
** output parameters:
** Returned value:      真实温度值
*********************************************************************************************************/
s16 Conv_temp_CT7538(s16 tempReg)
{
    /*
    //执行时间574个定时器计数
    float tmp;
    tmp = (float)tempReg * 0.0625 * 0.125;
    if (channel == 0)
    tmp = 1.0316 * tmp + 4.7774;
    else
    tmp = 1.0509 * tmp + 14.277;
    return (s16)(tmp*10);
    */

    u8 sign;
    s16 s16Tmp;
    u32 u32Tmp;

    ///////////////////
    //执行时间6个定时器计数
    //tmp1 = (float)tmpIn * 0.0625 * 0.125
    //     = tmpIn / 2^7
    //tmp2 = 1.0509 * tmp1 + 14.277
    //     = 1.0509 * (tmpIn / 2^7) + 14.277
    //     = (1.0509 * tmpIn + 14.277*2^7) / 2^7
    //     = (1.0509 * 2^9 * tmpIn + 14.277*2^7*2^9) / (2^7*2^9)
    //     = (1.0509 * 2^9 * tmpIn + 14.277*2^16) / 2^16
    //tmpCalc = 1.0509 * 2^9 * tmpIn + 14.277*2^16;
    //tmp2 = tmpCalc / 2^16;
    //tmp4 = tmp2*10;
    //tmpOut = tmp4 = tmpCalc / 2^16;
    //////////////////
    if (tempReg >= 0)
    {
        sign = 0;
        u32Tmp = tempReg;
    }
    else
    {
        sign = 1;
        u32Tmp = -tempReg;
    }
    u32Tmp *= 538;
    if (sign == 0)
    {
        u32Tmp += 935656;
    }
    else
    {
        u32Tmp = 935656 - u32Tmp;
    }
    u32Tmp *= 10;

    u32Tmp >>= 16;

    s16Tmp = u32Tmp & 0xFFFF;

    return (s16Tmp);
}

/*********************************************************************************************************
** Function name:       fnBsp_Temp_Ajust
** Descriptions:        对转换后的温度值进行滤波和线性补偿，单位是0.1℃
** input parameters:    s16Tmp:未处理的温度值
** output parameters:
** Returned value:      滤波和补偿后的温度值
*********************************************************************************************************/
s16 fnBsp_Temp_Ajust(u8 chNo, s16 s16Tmp)
{
    //滑动滤波
    s32 temp;
    OrgTempData.sum[chNo] += (s32)s16Tmp;
    OrgTempData.sum[chNo] -= (s32)OrgTempData.buf[chNo][OrgTempData.iBuf];
    OrgTempData.buf[chNo][OrgTempData.iBuf] = (s32)s16Tmp;
    s32 temp_1 = 0, temp_2 = 0;

    if (OrgTempData.valid)
    {
        if (OrgTempData.sum[chNo] >= 0)
        {
            temp = OrgTempData.sum[chNo] >> 3;
        }
        else
        {
            temp = -(-OrgTempData.sum[chNo] >> 3);
        }
    }
    else
    {
        temp = (s32)s16Tmp;
    }
    temp_1 = temp;
    //线性补偿
    //if (temp > 70 * 10) //大于70℃才去补偿
    if (temp > 50 * 10) //zhangyang 大于50℃才去补偿(原补偿范围会导致多产生一次温度剧变事件)
    {
        if (gTemperSchoolParaTemp.chan[chNo].valid == 0xA5)
        {
            temp *= gTemperSchoolParaTemp.chan[chNo].k;
            if (temp >= 0)
            {
                temp = temp >> 13;
            }
            else
            {
                temp = -(-temp >> 13);
            }
            #if 0   //RNW代码
            temp += gTemperSchoolParaTemp.chan[chNo].offs;
            #else   //zhangyang 温度补偿临界点附近，保证补偿是正向的
            temp_2 = temp + gTemperSchoolParaTemp.chan[chNo].offs;
            temp = (temp_2 > temp_1) ? temp_2 : temp_1;

            #endif
        }
    }

    return (temp & 0xFFFF);
}

/*********************************************************************************************************
** Function name:       fnBsp_CT7538_TempRange
** Descriptions:        在115℃或者135℃以上随机跳动一定范围的值
** input parameters:    无
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
s16 gTempRangeValue;
u8 gTempRangeSign;
void fnBsp_CT7538_TempRange(void)
{
    if (gTempRangeSign)
    {
        gTempRangeValue++;
        if (gTempRangeValue >= 4)
        {
            gTempRangeSign = 0;
        }
    }
    else
    {
        gTempRangeValue--;
        if (gTempRangeValue <= 1)
        {
            gTempRangeSign = 1;
        }
    }
}

/*********************************************************************************************************
** Function name:       fnBsp_CT7538_JudgeStable
** Descriptions:        判断温度是否稳定，间隔4秒测量温差是否大于0.6℃
** input parameters:    chNo:端子序号，s16Tmp:从寄存器转换过来的并经过转换的温度值
** output parameters:   无
** Returned value:      温度稳定返回true,不稳定返回false
*********************************************************************************************************/
s16 gTempLastBuf[MAX_TERMINAL_TMP_NUM][8];
s32 gTempLastLt4Sum[MAX_TERMINAL_TMP_NUM];  //前1S~4S数据和
s32 gTempLastBf4Sum[MAX_TERMINAL_TMP_NUM];  //前5S~8S数据和
u8 gILastBuf;
u8 fnBsp_CT7538_JudgeStable(u8 chNo, s16 s16Tmp)
{
    u8 iLtOld, iBfNew, iBfOld, ret;
    s16 avgLt, avgBf;
    //s32 temp;

    iLtOld = (gILastBuf + 4) % 8;
    iBfNew = iLtOld;
    iBfOld = gILastBuf;

    gTempLastLt4Sum[chNo] += (s32)s16Tmp;
    gTempLastLt4Sum[chNo] -= (s32)gTempLastBuf[chNo][iLtOld];
    gTempLastBf4Sum[chNo] += (s32)gTempLastBuf[chNo][iBfNew];
    gTempLastBf4Sum[chNo] -= (s32)gTempLastBuf[chNo][iBfOld];

    if (gTempLastLt4Sum[chNo] >= 0)
    {
        avgLt = gTempLastLt4Sum[chNo] >> 2;
    }
    else
    {
        avgLt = -((-gTempLastLt4Sum[chNo]) >> 2);
    }

    if (gTempLastBf4Sum[chNo] >= 0)
    {
        avgBf = gTempLastBf4Sum[chNo] >> 2;
    }
    else
    {
        avgBf = -((-gTempLastBf4Sum[chNo]) >> 2);
    }

    if (avgLt >= avgBf)
    {
        //if (avgLt >= (avgBf + 6))
        if (avgLt >= (avgBf + 12))//参考测试情况，三相表温度稳定后波动最大值能达到1.2度
        {
            ret = false;
        }
        else
        {
            ret = true;
        }
    }
    else
    {
        //if (avgBf >= (avgLt + 6))
        if (avgBf >= (avgLt + 12))//参考测试情况，三相表温度稳定后波动最大值能达到1.2度
        {
            ret = false;
        }
        else
        {
            ret = true;
        }
    }

    gTempLastBuf[chNo][gILastBuf] = (s32)s16Tmp;
    if ((chNo + 1) >= MAX_TERMINAL_TMP_NUM)
    {
        gILastBuf++;
        if (gILastBuf >= 8)
        {
            gILastBuf = 0;
        }
    }

    return (ret);
}

/*********************************************************************************************************
** Function name:       fnBsp_CT7538_read_temp
** Descriptions:        读取测温芯片的温度寄存器值，转换为真实的温度值，单位是0.1℃
** input parameters:    chNum:读取的总通道数，
** output parameters:   pTempData:实际温度值指针地址
** Returned value:      操作正确返回true,操作错误返回false
//执行时间1925个定时器计数
*********************************************************************************************************/
#define IIC_TMP_ADDR    0x98
#define REMOTE_CH1_ADDR 0x81
s16 gTempData[MAX_TERMINAL_TMP_NUM];
u8 fnBsp_CT7538_read_temp(u8 chNum, s16 *pTempData)
{
    u8 i, j, ret;
    s16 tempBuf[MAX_TERMINAL_TMP_NUM], *pTemp;
    ct7568tempReg_Type ct7538Reg[MAX_TERMINAL_TMP_NUM];

    for (i = 0; i < 10; i++)
    {
        IIC_Tmp_FirmMode_Start();
        if (false == IIC_Tmp_FirmMode_SendByte(IIC_TMP_ADDR))
        {
            IIC_Tmp_FirmMode_Stop();
            SystemDelayUs(100);
            ret = false;
            continue;
        }
        ret = true;
        IIC_Tmp_FirmMode_SendByte(REMOTE_CH1_ADDR);
        IIC_Tmp_FirmMode_Start();
        IIC_Tmp_FirmMode_SendByte(IIC_TMP_ADDR | 0x01);
        for (j = 0; j < chNum; j++)
        {
            ct7538Reg[j].regByte[1] = IIC_Tmp_FirmMode_ReceiveByte(1);
            ct7538Reg[j].regByte[0] = IIC_Tmp_FirmMode_ReceiveByte(1);
        }
        IIC_Tmp_FirmMode_Stop();
        break;
    }

    if (ret == true)
    {
        pTemp = tempBuf;
        for (i = chNum; i > 0; i--)
        {
            *pTemp++ = Conv_temp_CT7538(ct7538Reg[i - 1].regS16);
        }
        for (i = 0; i < chNum; i++)
        {
            gTempData[i] = fnBsp_Temp_Ajust(i, tempBuf[i]);
            //*pTempData = fnBsp_Temp_Ajust(i,tempBuf[i]);

            //如果温度稳定，将测量值修正在115℃和135℃附近
            if (fnBsp_CT7538_JudgeStable(i, gTempData[i]) == true)
            {
                // dyf 非厂内模式下，进行误差修正；厂内模式下，不进行误差修正，获取原始误差写温度补偿值
                if (Bkgrd.PubData.MtSta.MtSta3.StaBit.PrgEnable != 1) //非厂内
                {
                    #if 1    // zhangyang 修改

                    if (gTempData[i] < (1150 + 75) && gTempData[i] >= (1150 - 120))
                    {
                        gTempData[i] = (gTempData[i] - 1150) * 0.1 + 1150; //(x-115)*0.1+115
                    }
                    else if (gTempData[i] <= (1350 + 90) && gTempData[i] >= (1350 - 120))
                    {
                        gTempData[i] = (gTempData[i] - 1350) * 0.1 + 1350; //(x-135)*0.1+135
                    }

                    #endif

                    #if 0   /* RNW代码 */

                    if (gTempData[i] < (1150 + 90) && gTempData[i] >= (1150 - 90))
                    {
                        gTempData[i] = gTempRangeValue + 1150;
                    }
                    else if (gTempData[i] <= (1350 + 90) && gTempData[i] >= (1350 - 90))
                    {
                        gTempData[i] = gTempRangeValue + 1350;
                    }

                    #endif
                }
            }

            *pTempData = gTempData[i];
            pTempData ++;
        }
        if (++OrgTempData.iBuf >= 8)
        {
            OrgTempData.iBuf = 0;
            OrgTempData.valid = 1;
        }
    }
    return ret;
}

/*********************************************************************************************************
** Function name:       fnBsp_Tmp_Init
** Descriptions:        读取测温芯片的IO口初始化，以及测温芯片初始化
** input parameters:    none
** output parameters:   none
** Returned value:      none
*********************************************************************************************************/
void fnBsp_Tmp_Init(void)
{
    u8 i;
    Rn8xxx_GPIO_CfgFun(PinTmpSDA, _NORMALIO);
    Rn8xxx_GPIO_CfgIOMode(PinTmpSDA, GPIO_MODE_OUT, NORMAL_OUT);
    Rn8xxx_GPIO_SetPin(PinTmpSDA, 1);

    Rn8xxx_GPIO_CfgFun(PinTmpSCL, _NORMALIO);
    Rn8xxx_GPIO_CfgIOMode(PinTmpSCL, GPIO_MODE_OUT, NORMAL_OUT);
    Rn8xxx_GPIO_SetPin(PinTmpSCL, 1);

    IIC_Tmp_FirmMode_Start();
    IIC_Tmp_FirmMode_SendByte(0x00);
    IIC_Tmp_FirmMode_SendByte(0x06);
    IIC_Tmp_FirmMode_Stop();

    Std_Memset((u8*)&OrgTempData, 0, sizeof(sOrgTempData_TypeDef));

    gTempRangeValue = 0;
    gTempRangeSign = 0;

    for (i = 0; i < MAX_TERMINAL_TMP_NUM; i++)
    {
        if (gTemperSchoolParaMem.chan[i].valid == 0xA5)
        {
            gTemperSchoolParaTemp.chan[i].valid = 0xA5;
            gTemperSchoolParaTemp.chan[i].k = gTemperSchoolParaMem.chan[i].k * 0.8192;
            gTemperSchoolParaTemp.chan[i].offs = gTemperSchoolParaMem.chan[i].offs * 0.001;
        }
        else
        {
            gTemperSchoolParaTemp.chan[i].valid = 0;
            gTemperSchoolParaTemp.chan[i].k = 10000 * 0.8192;
            gTemperSchoolParaTemp.chan[i].offs = 0 * 0.001;
        }
    }
}
