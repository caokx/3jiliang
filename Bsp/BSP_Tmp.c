/****************************************************************************
* @file     BSP_Tmp.c
* @author   Renergy Application Team
* @version  V1.0.1
* @date     2023.4.23
* @brief    �弶���¶ȴ�����
******************************************************************************
* @attention
*
*
****************************************************************************/
#include <BSP.h>
#include "Globals.h"

sTemperSchoolPara_TypeDef gTemperSchoolParaMem;     //�洢��ԭʼֵ
sTemperSchoolPara_TypeDef gTemperSchoolParaTemp;    //�������������ת����ֵ

typedef struct
{
    u8 valid;
    u8 iBuf;
    s16 buf[MAX_TERMINAL_TMP_NUM][8];
    s32 sum[MAX_TERMINAL_TMP_NUM];
} sOrgTempData_TypeDef;
sOrgTempData_TypeDef OrgTempData;

/*********************************************************************************************************
** Descriptions:        IIC���߿�ʼʱ��
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
** Descriptions:        IIC���߽���ʱ��
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
** Descriptions:        IIC���߸�λʱ��
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
** Descriptions:        IIC����Ӧ��ʱ��
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
** Descriptions:        IIC������Ӧ��ʱ��
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
** Descriptions:        ��ICC���߷���һ���ֽ�
** input parameters:    B:�����͵�����
** output parameters:   none
** Returned value:      �ɹ�����true��ʧ�ܷ���false
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
** Descriptions:        ��ICC���߶�ȡһ���ֽ�
** input parameters:    ACK:true����ACK��false������ACK
** output parameters:   none
** Returned value:      ��ȡ����һ���ֽ�����
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
** Descriptions:        ������оƬ���¶ȼĴ���ֵת��Ϊ��ʵ���¶�ֵ����λ��0.1��
** input parameters:    tempReg:�¶ȼĴ���ֵ
** output parameters:
** Returned value:      ��ʵ�¶�ֵ
*********************************************************************************************************/
s16 Conv_temp_CT7538(s16 tempReg)
{
    /*
    //ִ��ʱ��574����ʱ������
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
    //ִ��ʱ��6����ʱ������
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
** Descriptions:        ��ת������¶�ֵ�����˲������Բ�������λ��0.1��
** input parameters:    s16Tmp:δ������¶�ֵ
** output parameters:
** Returned value:      �˲��Ͳ�������¶�ֵ
*********************************************************************************************************/
s16 fnBsp_Temp_Ajust(u8 chNo, s16 s16Tmp)
{
    //�����˲�
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
    //���Բ���
    //if (temp > 70 * 10) //����70���ȥ����
    if (temp > 50 * 10) //zhangyang ����50���ȥ����(ԭ������Χ�ᵼ�¶����һ���¶Ⱦ���¼�)
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
            #if 0   //RNW����
            temp += gTemperSchoolParaTemp.chan[chNo].offs;
            #else   //zhangyang �¶Ȳ����ٽ�㸽������֤�����������
            temp_2 = temp + gTemperSchoolParaTemp.chan[chNo].offs;
            temp = (temp_2 > temp_1) ? temp_2 : temp_1;

            #endif
        }
    }

    return (temp & 0xFFFF);
}

/*********************************************************************************************************
** Function name:       fnBsp_CT7538_TempRange
** Descriptions:        ��115�����135�������������һ����Χ��ֵ
** input parameters:    ��
** output parameters:   ��
** Returned value:      ��
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
** Descriptions:        �ж��¶��Ƿ��ȶ������4������²��Ƿ����0.6��
** input parameters:    chNo:������ţ�s16Tmp:�ӼĴ���ת�������Ĳ�����ת�����¶�ֵ
** output parameters:   ��
** Returned value:      �¶��ȶ�����true,���ȶ�����false
*********************************************************************************************************/
s16 gTempLastBuf[MAX_TERMINAL_TMP_NUM][8];
s32 gTempLastLt4Sum[MAX_TERMINAL_TMP_NUM];  //ǰ1S~4S���ݺ�
s32 gTempLastBf4Sum[MAX_TERMINAL_TMP_NUM];  //ǰ5S~8S���ݺ�
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
        if (avgLt >= (avgBf + 12))//�ο����������������¶��ȶ��󲨶����ֵ�ܴﵽ1.2��
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
        if (avgBf >= (avgLt + 12))//�ο����������������¶��ȶ��󲨶����ֵ�ܴﵽ1.2��
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
** Descriptions:        ��ȡ����оƬ���¶ȼĴ���ֵ��ת��Ϊ��ʵ���¶�ֵ����λ��0.1��
** input parameters:    chNum:��ȡ����ͨ������
** output parameters:   pTempData:ʵ���¶�ֵָ���ַ
** Returned value:      ������ȷ����true,�������󷵻�false
//ִ��ʱ��1925����ʱ������
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

            //����¶��ȶ���������ֵ������115���135�渽��
            if (fnBsp_CT7538_JudgeStable(i, gTempData[i]) == true)
            {
                // dyf �ǳ���ģʽ�£������������������ģʽ�£������������������ȡԭʼ���д�¶Ȳ���ֵ
                if (Bkgrd.PubData.MtSta.MtSta3.StaBit.PrgEnable != 1) //�ǳ���
                {
                    #if 1    // zhangyang �޸�

                    if (gTempData[i] < (1150 + 75) && gTempData[i] >= (1150 - 120))
                    {
                        gTempData[i] = (gTempData[i] - 1150) * 0.1 + 1150; //(x-115)*0.1+115
                    }
                    else if (gTempData[i] <= (1350 + 90) && gTempData[i] >= (1350 - 120))
                    {
                        gTempData[i] = (gTempData[i] - 1350) * 0.1 + 1350; //(x-135)*0.1+135
                    }

                    #endif

                    #if 0   /* RNW���� */

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
** Descriptions:        ��ȡ����оƬ��IO�ڳ�ʼ�����Լ�����оƬ��ʼ��
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
