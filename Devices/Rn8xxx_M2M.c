
#define  _DRIVE_M2M_GLOBALS
#include <CoreSupport.h>
#include <Rn8xxx_Common.h>
#include <Rn8xxx_M2M.h>

/*********************************************************************************************************
** Function name:          Rn8xxx_M2M_Move
** Descriptions:             M2M ���ݰ���
** input parameters:      M2M_ModePara:����ģʽ����
**                  SAddr:Դ���ݵ�ַ
**                  DAddr:Ŀ�����ݵ�ַ
**                  ILen:Դ���ݳ���
** output parameters:   NONE
** Returned value:      SUCCESEE  or ERROR
*********************************************************************************************************/
ErrorStatus Rn8xxx_M2M_Move(uM2M_ModePara_TypeDef M2M_ModePara, u32 SAddr, u32 DAddr, u16 ILen)
{
    M2M->CTL = 0;       //ֹͣ��һ�ΰ���;
    M2M->MODE = M2M_ModePara.gMode;
    //M2M->DUMMY    = M2M_ModePara.Mode_DUMMY;
    M2M->SADDR = (SAddr & 0x0001FFFF);  //����Դ��ַ
    M2M->DADDR = (DAddr & 0x0001FFFF); //Ŀ���ַ

    M2M->ILEN = ILen;  //len
    M2M->CTL = 1;   //��������

    if (fnRegState_Detect((u32)(&M2M->IF), 0, 1, M2M_TimeOut) == ERROR)
    {
        return (ERROR);    //�ȴ�ת�����
    }

    M2M->IF = 0x01;  //clear If

    return SUCCESS;
}

//------------------------------------------------------------------------------
