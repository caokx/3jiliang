/********************************************************************
Filename:       Dl698_UserData.c
Revised:        $Date: 2017-05-23 $
Revision:       $Revision: V0.1 $
Author:

Description:
**********************************************************************/
/*********************************************************************
* INCLUDES
*/
#include "Dl698_Type.h"
#include "Dl698_Memory.h"
#include "Dl698_AL.h"
#include "Dl698AL_def.h"
#include "Dl698AL_asn1.h"
#include "Dl698_UserData.h"
#include "Dl698_UserData_Encode645to698.h"
#include "Dl645B_Com.h"
#include "Dl698_EsamOp.h"

/*********************************************************************
* EXTERNAL VARIABLES
*/
/*********************************************************************
* EXTERNAL FUNCTIONS
*/

/*********************************************************************
* PUBLIC FUNCTIONS
*/

/*********************************************************************
* @fn      fnDl698_GetRcsdNum
*
* @brief
*
* @param
*
* @return
*/
u8 fnDl698_GetRcsdNum(u32 OAD)
{
    return 0;
}

/*********************************************************************
* @fn      fnDl698_GetNormalValue
*
* @brief
*
* @param
*
* @return
*/
u8 fnDl698_GetNormalValue(
    u32  OAD,           //OAD
    u16  classId,       //class id
    u16  oiindex,       //oi list index
    u16  retMaxLen,     //return result buffer max length�����ص����ݳ��ȱ���<= retMaxLen
    u8  *pRetBuf,       //return result buffer
    u16 *pRetLen,        //return result buffer length
    u8  *blockRsp       //rsp is blocking�������ص����ݳ���data length>max lengthʱ����BlockRsp��1��˵�����и���������Ҫ�´ζ�ȡ
)
{
    //       OAD_Analyse_TypeDef *pOadAys = (OAD_Analyse_TypeDef*)&OAD;
    u8 res = DATA_ACCESS_RESULT_UNAVA;
    u8 *uBuf, *pDataBuf;

    *blockRsp = false;

    fnWDT_Restart();

    //��̬������ʱbuf
    uBuf = (u8 *)fnDl698_Buffer_Alloc(TEMP_MAXSIZE);
    if (uBuf == NULL)
    {
        return DATA_ACCESS_AL_MEMALLOC_ERR;
    }
    Std_Memset(uBuf, 0, TEMP_MAXSIZE);

    retMaxLen -= 1;

    pDataBuf = pRetBuf + 1;//Ԥ��һ���ֽ�
    retMaxLen -= 1;

    res = fnGet_Normal(OAD, uBuf, pDataBuf, pRetLen, blockRsp);

    //���ش����װ����ԭ������
    if (res != DATA_ACCESS_RESULT_SUC)
    {
        *pRetLen = 2;
        *pRetBuf++ = 0;   //��װѡ��DAR[0]
        *pRetBuf++ = res; //��װDAR
    }
    //������ȷ��װ��������
    else
    {
        *pRetBuf = 1; //��װѡ��DATA[1]
        //Std_Memcpy( pRetBuf, p698DataBuf, (u8)pRetLen );
        *pRetLen += 1;
    }

    fnDl698_Buffer_Free(uBuf);//��Դ�ͷ�
    return res;
}

/*********************************************************************
* @fn      fnDl698_GetRecordValue
*
* @brief
*
* @param
*
* @return
*/
u8 fnDl698_GetRecordValue(
    u32  OAD,           //OAD
    u8  *pParBuf,       //paramter buffer ,�Ǽ�¼�͵�pParBufΪNULL����¼�͵�pParBufָ������RCD����Ϣ
    u16 *parLen,        //paramter buffer length ,�Ѵ�������ݳ���
    u16  retMaxLen,     //return result buffer max length�����ص����ݳ��ȱ���<= retMaxLen
    u8  *pRetBuf,       //return result buffer
    u16 *pRetLen,        //return result buffer length
    u8   blockReq,      //req is get-next��Э��ջ�յ�����GET-NEXT����
    u8  *blockRsp       //rsp is blocking�������ص����ݳ���data length>max lengthʱ����BlockRsp��1��˵�����и���������Ҫ�´ζ�ȡ
)
{
    OAD_Analyse_TypeDef *pOadAys = (OAD_Analyse_TypeDef*)&OAD;
    u8 res = DATA_ACCESS_RESULT_UNAVA;

    u8 *uBuf;

    *parLen = 0;
    *blockRsp = false;

    //��̬������ʱbuf
    uBuf = (u8 *)fnDl698_Buffer_Alloc(TEMP_GETREC_MAXSIZE);
    if (uBuf == NULL)
    {
        return DATA_ACCESS_AL_MEMALLOC_ERR;
    }
    Std_Memset(uBuf, 0, TEMP_GETREC_MAXSIZE);

    *parLen = fnDl698AL_GetData_Len(0, DTYPE_RSD, pParBuf);
    *parLen += fnDl698AL_GetData_Len(0, DTYPE_RCSD, (pParBuf + *parLen));

    switch (pOadAys->OIA1)
    {
        case OIA1_FREEZE:
            if (pOadAys->OIB2 == 2) //���Ӷ���
            {
                res = fnGet_FrzMinRecord(OAD, pParBuf, uBuf, pRetBuf, pRetLen, blockRsp);
            }
            else                    // dyf ����оֻ֧�ַ��Ӷ���
            {
                pRetBuf[0] = 0x00;                      // SeqOf����=0
                pRetBuf[1] = 0x00;                      // �������0������
                pRetBuf[2] = DATA_ACCESS_RESULT_UNDEF;  // DAR�ο����ǵļ���о�ظ�����δ����
                *pRetLen   = 3;
            }

            //else
            //  res = fnGet_FrzRecord(OAD, pParBuf, uBuf, pRetBuf, pRetLen, blockRsp , TRUE);

            break;

        default:
        {
            res = fnGet_EvtRecord(OAD, pParBuf, uBuf, pRetBuf, pRetLen, blockRsp, TRUE);
            break;
        }
    }
    /*
    if(res != DATA_ACCESS_RESULT_SUC)
    {
        *pRetLen = 3;
        *pRetBuf++ = 0;
        *pRetBuf++ = 0;   //��װѡ��DAR[0]
        *pRetBuf++ = res; //��װDAR
    }
    */
    fnDl698_Buffer_Free(uBuf);//��Դ�ͷ�
    return res;
}

/*********************************************************************
* @fn      fnDl698_GetValue
*
* @brief
*
* @param
*
* @return
*/
u8 fnDl698_GetValue(
    u32  OAD,           //OAD
    u16  classId,       //class id
    u16  oiindex,       //oi list index
    u8  *pParBuf,       //paramter buffer ,�Ǽ�¼�͵�pParBufΪNULL����¼�͵�pParBufָ������RCD����Ϣ
    u16 *parLen,        //paramter buffer length ,�Ѵ�������ݳ���
    u16  retMaxLen,     //return result buffer max length�����ص����ݳ��ȱ���<= retMaxLen
    u8  *pRetBuf,       //return result buffer
    u16 *retLen,        //return result buffer length
    u8   blockReq,      //req is get-next��Э��ջ�յ�����GET-NEXT����
    u8  *blockRsp       //rsp is blocking�������ص����ݳ���data length>max lengthʱ����BlockRsp��1��˵�����и���������Ҫ�´ζ�ȡ
)
{
    u8 res = DATA_ACCESS_RESULT_SUC;

    #ifdef DL698_GETBLOCK
    if (retMaxLen < 2)
    {
        //���ȺϷ����жϣ������Ϸ�ֱ�������Ƭ
        *blockRsp = true;
        return DATA_ACCESS_RESULT_SUC;
    }
    else
    #endif
    {
        if (pParBuf == NULL)
        {
            //normal��
            *parLen = 0;
            res = fnDl698_GetNormalValue(OAD, classId, oiindex, retMaxLen, pRetBuf, retLen, blockRsp);
        }
        else
        {
            //record��
            res = fnDl698_GetRecordValue(OAD, pParBuf, parLen, retMaxLen, pRetBuf, retLen, blockReq, blockRsp);
        }
    }
    return res;
}

/*********************************************************************
* @fn      fnDl698_ReportValue
*
* @brief
*
* @param
*
* @return
*/
void fnDl698_ReportValue(
    u8  *pParBuf,      //parameter buffer
    u8  *pOADNum        //
)
{
    u32 tempOAD;
    u8 i, j, Num;

    Num = *pOADNum;

    while (Num--)
    {
        tempOAD = Std_Msb32DataGet(pParBuf);
        tempOAD &= 0xFFFFFF00;

        pParBuf += 4;

        if (tempOAD == 0x33200200)
        {
            EvtRptData.ReportCnt = 0;
            Std_Memset((u8 *)&EvtRptData.ListZB_A, 0x00, sizeof(sReportList_TypeDef));
            fnFile_Write(FileId_EvtReport, FileItemInfoOffAddr_EvtReport_OADNumZB_A, (u8 *)&EvtRptData.ListZB_A, sizeof(sReportList_TypeDef));
        }
        else if (tempOAD == 0x20150200)
        {
            EvtRptData.ReportCnt = 0;
            EvtRptData.Status.RptStuZB = 0x00;
            EvtRptData.Status.RptStuZBBack = 0x00;
            fnFile_Write(FileId_EvtReport, FileItemInfoOffAddr_EvtReport_RptStatusZB, (u8 *)&EvtRptData.Status.RptStuZB, 8);
        }
        else
        {
            for (i = 0; i < EvtRptData.ListZB_A.OADNum; i++)
            {
                if (EvtRptData.ListZB_A.OAD[i] == tempOAD)
                {
                    EvtRptData.ReportCnt = 0;

                    j = EvtRptData.ListZB_A.OADNum - i;

                    if (j > 1)
                    {
                        Std_Memcpy((u8 *)&EvtRptData.ListZB_A.OAD[i], (u8 *)&EvtRptData.ListZB_A.OAD[i + 1], 4 * (j - 1));
                        EvtRptData.ListZB_A.OAD[i + j - 1] = 0;  //
                    }
                    else
                    {
                        EvtRptData.ListZB_A.OAD[i] = 0;
                    }

                    EvtRptData.ListZB_A.OADNum--;

                    fnFile_Write(FileId_EvtReport, FileItemInfoOffAddr_EvtReport_OADNumZB_A, &EvtRptData.ListZB_A, sizeof(sReportList_TypeDef));

                    break;
                }
            }
        }
    }
}

/*********************************************************************
* @fn      fnDl698_SetValue
*
* @brief
*
* @param
*
* @return
*/
u8 fnDl698_SetValue(
    u32  OAD,          //oad
    u16  classId,      //class id
    u8  *pParBuf,      //parameter buffer
    u16 *parLen        //parameter length ���Ѵ���Ĳ������ݳ���
)
{
    u8 res = DATA_ACCESS_RESULT_UNAVA;
    u8 *pDataBuf;

    //��̬������ʱbuf
    pDataBuf = (u8 *)fnDl698_Buffer_Alloc(TEMP_MAXSIZE);
    if (pDataBuf == NULL)
    {
        return DATA_ACCESS_AL_MEMALLOC_ERR;
    }
    Std_Memset(pDataBuf, 0, TEMP_MAXSIZE);

    res = fnSet_Normal(OAD, pParBuf, pDataBuf, parLen);

    fnDl698_Buffer_Free(pDataBuf); //��Դ�ͷ�

    return res;
}

/*********************************************************************
* @fn      fnDl698_ActMeth
*
* @brief
*
* @param
*
* @return
*/
u8 fnDl698_ActMeth(
    u32  OMD,        //OMD
    u16  classId,    //class id
    u8  *pParBuf,    //parameter buffer
    u16 *parLen,     //parameter length ���Ѵ���Ĳ������ݳ���
    u16  retMaxLen,  //return result buffer max length
    u8  *pRetBuf,    //return result buffer
    u16 *retLen      //return result buffer length
)
{
    u8 res = DATA_ACCESS_RESULT_UNAVA;
    u8 *pDataBuf;

    //��̬������ʱbuf
    pDataBuf = (u8 *)fnDl698_Buffer_Alloc(TEMP_MAXSIZE);
    if (pDataBuf == NULL)
    {
        return DATA_ACCESS_AL_MEMALLOC_ERR;
    }
    Std_Memset(pDataBuf, 0, TEMP_MAXSIZE);

    res = fnAct_Normal(OMD, pParBuf, parLen, pRetBuf, retLen, pDataBuf);

    fnDl698_Buffer_Free(pDataBuf); //��Դ�ͷ�

    return res;
}

/*********************************************************************
* @fn      fnDl698_SafetyCertiHandle
*
* @brief   ��ȫ��֤����������ESAM����, ���������ݷ��͸�ESAM���ܵ�ESAM�Ļظ�
*
* @param   req_type  �������ͣ�ֻ��OMDΪ0��req_typeΪ�������ӻ��߶Ͽ����ӣ�������
*          OMD
*          pParBuf   ������buf
*          pRetBuf   ESAM���ص�buf
*          retLen    ESAM���ص�buf����
*
* @return
*/
u8 fnDl698_SafetyCertiHandle(
    u8   req_type,   //��������
    u32  OMD,        //OMD
    u8  *pParBuf,    //parameter buffer
    u8  *pRetBuf,    //return result buffer
    u16 *retLen      //return result buffer length
)
{
    u8 result = 0;
    u8 fun_type = 0;   //��������
    u8 act_type = 0;   //��������

    switch (OMD)
    {
        case 0xF0010300:
        {
            break;
        }

        case 0xF0010600:
        {
            fun_type = *pParBuf++;
            if (fun_type == DTYPE_INT8)  //��������Ϊinteger,int8һ���ֽ�
            {
                act_type = *pParBuf++;     //�������ͣ���Ϊ��������ֵ���˷�
                if (act_type == 0x00)     //����
                {
                }
                else if (act_type == 0x01)     //��ֵ
                {
                }
            }
            break;
        }

        case 0xF0010700:
        {
            break;
        }

        case 0xF0010900:
        {
            break;
        }

        case 0xF0010A00:
        {
            break;
        }

        case 0x00000000:
        {
            if (req_type == DL698AL_APDU_TAG_CONREQ)   //��������
            {
            }
            else if (req_type == DL698AL_APDU_TAG_RLSREQ)  //�޲�������ʱ�Ĳ���pParBuf������,�˴���Ҫ��֪ͨESAM���ӶϿ�
            {
            }
            break;
        }

        default:
            break;
    }
    return result;
}

u8 fnDl698_GetFlwRptFlag(u8 chan)
{
    return 1;
}

void fnDl698_FlwRptValue(
    u16  retMaxLen,     //return result buffer max length�����ص����ݳ��ȱ���<= retMaxLen
    u8  *pRetBuf,       //return result buffer
    u16 *retLen         //return result buffer length
)
{
    u8 num = 0 ;
    u8 FollowOAD[5] = {0x33, 0x20, 0x02, 0x01, 0x01};    //�����ϱ��̶�OAD  0x33200101��������̶�1��
    u8 statusOAD[5] = {0x20, 0x15, 0x02, 0x00, 0x01};
    u16 len;
    u32 rptOAD, status;

    if (EvtRptData.Para.FollowAllow == TRUE)
    {
        if (Secret.Chan == SCOM_PORT_ZBCOM)
        {
            if (EvtRptData.RecOADZB) //�����ϱ���Ϣ
            {
                num++;
                rptOAD = EvtRptData.RecOADZB;
            }
            else
            {
                rptOAD = 0x00;
            }

            if ((EvtRptData.Para.RptStatusAllow == 1) && (EvtRptData.Status.RptStuZB))
            {
                num++;
                status = EvtRptData.Status.RptStuZB;
            }
            else
            {
                status = 0x00;
            }
        }
        else if (Secret.Chan == SCOM_PORT_RS485A)
        {
            if (EvtRptData.RecOAD485) //�����ϱ���Ϣ
            {
                num++;
                rptOAD = EvtRptData.RecOAD485;
            }
            else
            {
                rptOAD = 0x00;
            }

            if ((EvtRptData.Para.RptStatusAllow == 1) && (EvtRptData.Status.RptStu485))
            {
                num++;
                status = EvtRptData.Status.RptStu485;
            }
            else
            {
                status = 0x00;
            }
        }
        else if (Secret.Chan == SCOM_PORT_RS485B)
        {
            if (EvtRptData.RecOAD4852) //�����ϱ���Ϣ
            {
                num++;
                rptOAD = EvtRptData.RecOAD4852;
            }
            else
            {
                rptOAD = 0x00;
            }

            if ((EvtRptData.Para.RptStatusAllow == 1) && (EvtRptData.Status.RptStu4852))
            {
                num++;
                status = EvtRptData.Status.RptStu4852;
            }
            else
            {
                status = 0x00;
            }
        }
        else
        {
            *retLen = 0;
            return;
        }
    }
    else
    {
        *retLen = 0;
        return;
    }

    if (num)
    {
        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, retLen, &num, NULL, DTYPE_ARRAY);
        if (rptOAD)
        {
            Std_Memcpy(pRetBuf, (u8 *)&FollowOAD[0], 5);
            *retLen += 5;
            pRetBuf += 5;
            pRetBuf += fnDl698_asn1_build_Type(pRetBuf, retLen, (u8 *)&rptOAD, NULL, DTYPE_OAD);
        }

        if (status)
        {
            Std_Memcpy(pRetBuf, (u8 *)&statusOAD[0], 5);
            *retLen += 5;
            pRetBuf += 5;
            len = 4;
            pRetBuf += fnDl698_asn1_build_Type(pRetBuf, retLen, (u8 *)&status, &len, DTYPE_BITSTRING);
        }
    }
    else
    {
        *retLen = 0;
    }
}

VOID fnDl698AL_EvtNotify(u8 chan, u16 event_value)
{
    switch (event_value)
    {
        case (DL698DL_EVENT_CONNECT):
        {
            break;
        }
        case (DL698DL_EVENT_BREAK):
        {
            break;
        }
        case (DL698DL_EVENT_FAIL):
        {
            break;
        }
        case (DL698DL_EVENT_RECONNECT):
        {
            break;
        }
        case (DL698DL_EVENT_DUMMYBREAK):
        {
            break;
        }
        case (DL698DL_EVENT_OCTTIMEOUT):
        {
            break;
        }
        case (DL698DL_EVENT_INACTTIMEOUT):
        {
            break;
        }

        case (DL698AL_EVENT_CONNECT):
        {
            break;
        }
        case (DL698AL_EVENT_BREAK):
        {
            break;
        }
        case (DL698AL_EVENT_CONNECTFAIL):
        {
            break;
        }
        case (DL698AL_EVENT_RELEASEFAIL):
        {
            break;
        }
        case (DL698AL_EVENT_RECONNECT):
        {
            break;
        }
        case (DL698AL_EVENT_RELEASE):
        {
            break;
        }
        case (DL698AL_EVENT_DUMMYDIS):
        {
            break;
        }
        default:
        {
            break;
        }
    }
    return;
}

typedef struct
{
    u16 oi;
    u16 sec;
} sDl698AL_SecPar_TypeDef;

typedef struct
{
    u16 oi;
    u16 sec;
    u16 mask;   //MASKΪF��ʾΪ������ͨ��
} sDl698AL_SecParWld_TypeDef;

//4byte
//get set act agent
sDl698AL_SecPar_TypeDef gDl698AL_SecPar_List[] =
{
    {0x202C, 0x8004},
    {0x2015, 0x8180},
    {0x4000, 0x8184},
    {0x4001, 0x8104},
    {0x4002, 0x8404},
    {0x4003, 0x8400},
    {0x400A, 0x8100},
    {0x400B, 0x8100},
    {0x401C, 0x8100},
    {0x401D, 0x8100},
    {0x401E, 0x8100},
    {0x4018, 0x8000},
    {0x4019, 0x8500},
    {0x401A, 0x8000},
    {0x401B, 0x8500},
    {0x4111, 0x8104},
    {0x40EE, 0x8800},
    {0x5000, 0x8140},
    {0xF000, 0x8110},
    {0xF001, 0x8220},
    {0xF002, 0x8880},
    {0xF100, 0x8414},
    {0xF101, 0x8124},
};

sDl698AL_SecParWld_TypeDef gDl698AL_SecParWld_List[] =
{
    {0x0000, 0x8004, 0x0FFF},
    {0x1000, 0x8000, 0x0FFF},
    {0x2000, 0x8080, 0x0FFF},
    {0x3000, 0x8110, 0x0FFF},
    {0x4000, 0x8110, 0x0FFF},
    {0x5000, 0x8110, 0x00FF},
    {0x6000, 0x8887, 0x00FF},
    {0x7000, 0x8085, 0x00FF},
    {0x8000, 0x8110, 0x00FF},
    {0xF200, 0x8887, 0x00FF},
    {0xFF00, 0x8887, 0x00FF},
};

/*********************************************************************
* @fn      fnRaed_DefaultSecPar
*
* @brief   ��ȡOI��Ĭ�ϰ�ȫģʽ����
*
* @param   oi
*
* @return  ����OI��Ĭ�ϰ�ȫģʽ������ʧ�ܷ���0xFFFF��ԭ��ΪĬ�ϰ�ȫģʽ�����б���δ�ҵ���oi
*/
u16 fnRaed_DefaultSecPar(u16 oi)
{
    u8 i;

    //1. ��û��ͨ����б�gDl698AL_SecPar_List�в��ң�
    for (i = 0; i < sizeof(gDl698AL_SecPar_List) / sizeof(gDl698AL_SecPar_List[0]); i++)
    {
        if (gDl698AL_SecPar_List[i].oi == oi)
        {
            return gDl698AL_SecPar_List[i].sec;
        }
    }

    //2. ��1�����û�ҵ���������ͨ����б�gDl698AL_SecParWld_List�в���
    for (i = 0; i < sizeof(gDl698AL_SecParWld_List) / sizeof(gDl698AL_SecParWld_List[0]); i++)
    {
        if ((gDl698AL_SecParWld_List[i].oi & (~gDl698AL_SecParWld_List[i].mask) & 0xFFFF) == (oi & (~gDl698AL_SecParWld_List[i].mask) & 0xFFFF))
        {
            return gDl698AL_SecParWld_List[i].sec;
        }
    }

    return 0xFFFF;
}

/*********************************************************************
* @fn      fnRead_FormulationSecPar
*
* @brief   ��ȡOI����ʽ��ȫģʽ����
*
* @param   oi
*
* @return  ����OI��Ĭ�ϰ�ȫģʽ������ʧ�ܷ���0xFFFF��ԭ��ΪĬ�ϰ�ȫģʽ�����б���δ�ҵ���oi
*/
u16 fnRead_FormulationSecPar(u16 oi)
{
    sSafeModePara_TypeDef   safe_mode;
    u8 i;

    fnFile_Read(FileId_SecretPara, FileItemInfoOffAddr_SecretPara_SafeModePara, (u8 *)&safe_mode, FileItemInfoLen_SecretPara_SafeModePara);

    for (i = 0; i < safe_mode.OI_Cnt; i++)
    {
        if (safe_mode.SafeModeTable[i].OI == oi)
        {
            return safe_mode.SafeModeTable[i].Mode;
        }
    }

    return 0xFFFF;
}

/*********************************************************************
* @fn      fnRead_SecurtyStatus
*
* @brief   �жϰ�ȫģʽ���ؼ����״̬
*
* @param   secflag=1 ��ȫģʽ������     secflag=0 ��ȫģʽ��δ����
*          PrgEnable = 1 ����ʹ��     PrgEnable=0 ���̽�ֹ
* @return  true = ��ȫģʽ��δ����||����ʹ��
*/
u8 fnRead_SecurtyStatus(void)
{
    u8 secflag;

    fnFile_Read(FileId_SecretPara, FileItemInfoOffAddr_SecretPara_SafeModeFlag, (u8 *)&secflag, FileItemInfoLen_SecretPara_SafeModeFlag);

    if ((secflag == 0) || (Bkgrd.PubData.MtSta.MtSta3.StaBit.PrgEnable))
    {
        return true;
    }
    else
    {
        return false;
    }
}

u8 fnReadStatus_PrgEnable(void)
{
    if (Bkgrd.PubData.MtSta.MtSta3.StaBit.PrgEnable)
    {
        return true;
    }
    else
    {
        return false;
    }
}

u8 fnRead_tIRDly(void)
{
    if (Secret.CA == TERMINAL)
    {
        return false;
    }
    else if (Secret.tIRDly == 0) //������֤��Ч
    {
        return false;
    }
    else
    {
        return true;
    }
}

u8 fnChkStatus_tLinkDly(void)
{
    u8 i;

    if (Secret.CA == TERMINAL)
    {
        for (i = 0; i < SCOM_PORT_MAX; i++) //�ն�
        {
            if (Secret.Terminal.tLinkDly[i])
            {
                return true;
            }
        }
    }
    else
    {
        for (i = 0; i < SCOM_PORT_MAX; i++) //��վ
        {
            if (Secret.Master.tLinkDly[i])
            {
                return true;
            }
        }
    }

    return false;
}

/*********************************************************************
* @fn      fnChk_TermBinCoreAuthStatus
*
* @brief   �ж��ն������֤��˫о��֤״̬
*
* @param  chan--��ǰͨ��
*
* @return  true = �����֤��Ч,false = �����֤ʧЧ
*/
u8 fnChk_TermBinCoreAuthStatus(u8 chan)
{
    u8 ret;

    ret = false;

    if (chan == SCOM_PORT_SPI)
    {
        if (Bkgrd.PubData.MtSysSta.SysStaBit.BothCoreValid)
        {
            ret = true;
        }
    }
    else
    {
        if (Secret.CA == TERMINAL && Secret.tTerminalDly != 0)
        {
            ret = true;
        }
    }

    return (ret);
}

/*********************************************************************
* @fn      fnChk_AuthOnStatus
*
* @brief   �ж������֤Ȩ��
*
* @param  �����֤����:0=����/����+RN �������������֤;1=���Ķ�ȡ��Ҫ�����֤
*
* @return  true =
*/
u8 fnChk_AuthOnStatus(void)
{
    //u8 authon;

    if (Secret.Chan != SCOM_PORT_SPI)
    {
        //fnFile_Read(FileId_SecretPara , FileItemInfoOffAddr_SecretPara_AuthOn , (u8 *)&authon , 1);

        if (Secret.NeedIdentityAuth)   //1=���Ķ�ȡ��Ҫ�����֤
        {
            if (Secret.CA == TERMINAL)
            {
                if (Secret.tTerminalDly == 0)
                {
                    return false;
                }
            }
            else
            {
                if (fnChkStatus_tLinkDly() == false)
                {
                    return false;
                }
            }
        }
    }

    //0=����/����+RN �������������֤
    return true;
}

//*****************************************************************************************************
// ��������u8 fnReadMeter_Esam( u8*  uBuf, u8  *pRetBuf, u16 *pRetLen,)
// ���룺   RxBuf:��������
//          RxLen:����
// ���أ�   SUCCESS or ERROR
// ������   ��ESAM���
//******************************************************************************************************
u8 fnReadMeter_Esam(u8*  uBuf)
{
    ErrorStatus err;
    u8 TxBuf[5] = {0, 0, 0x07, 0, 0x06};

    fnEsamOp_RxTxCommhead(0x80, 0x2C, 0x00, 0x01, 0x00, 0x05);

    err = fnEsamOp_CardTxRxFrame(ESAM, 5, (u8 *)uBuf, &TxBuf[0]);
    if (err == ERROR)
    {
        return ERROR;
    }

    return SUCCESS;
}

//*****************************************************************************************************
// ��������void fnUpdateMeterNo( void )
// ���룺
//
// ���أ�  TRUE:��ŷ����ı�      FALSE:���δ�����ı�
// ������   ����E2���
//******************************************************************************************************
u8 fnUpdateMeterNo(void)
{
    u8 temp[6];

    fnFile_Read(FileId_HighPara, FileItemInfoOffAddr_HighPara_MeterNo, &temp[0], 0x06);

    if (fnReadMeter_Esam(&ICEsamComm.Ic_Comm_RxBuf[4]) == SUCCESS)
    {
        Std_MemRvsSelf(&ICEsamComm.Ic_Comm_RxBuf[4], 6);
        if (fnDFCompData(&ICEsamComm.Ic_Comm_RxBuf[4], &temp[0], 6) != 0)
        {
            fnFile_Write(FileId_HighPara, FileItemInfoOffAddr_HighPara_MeterNo, &ICEsamComm.Ic_Comm_RxBuf[4], 0x06);
            return TRUE;
        }
    }
    return FALSE;
}

//*****************************************************************************************************
// ��������u8 fnReadAuthOn_Esam( u8*  uBuf )
// ���룺
//
// ���أ�   SUCCESS or ERROR
// ������   ��ESAM�������֤Ȩ��
//******************************************************************************************************
u8 fnReadAuthOn_Esam(u8*  uBuf)
{
    ErrorStatus err;

    fnEsamOp_RxTxCommhead(0x80, 0x36, 0x00, 0x08, 0x00, 0x00);

    err = fnEsamOp_CardTxRxFrame(ESAM, 0x00, (u8 *)uBuf, 0);
    if (err == ERROR)
    {
        return ERROR;
    }

    return SUCCESS;
}

//*****************************************************************************************************
// ��������void fnUpdateAuthOn( void )
// ���룺
//
// ���أ�
// ������   ���������֤Ȩ��
//******************************************************************************************************
u8 fnUpdateAuthOn(void)
{
    u8 temp;

    fnFile_Read(FileId_SecretPara, FileItemInfoOffAddr_SecretPara_AuthOn, &temp, 0x01);

    if (fnReadAuthOn_Esam(&ICEsamComm.Ic_Comm_RxBuf[4]) == SUCCESS)
    {
        if (ICEsamComm.Ic_Comm_RxBuf[4] != temp)
        {
            fnFile_Write(FileId_SecretPara, FileItemInfoOffAddr_SecretPara_AuthOn, &ICEsamComm.Ic_Comm_RxBuf[4], 0x01);
            return TRUE;
        }
    }
    return FALSE;
}

//*****************************************************************************************************
// ��������u8 fnReadMeter_Esam( u8*  uBuf, u8  *pRetBuf, u16 *pRetLen,)
// ���룺   RxBuf:��������
//          RxLen:����
// ���أ�
// ������   ��ESAM��Կ�汾��
//******************************************************************************************************
u8 fnReadPswVer_Esam(u8*  uBuf)
{
    ErrorStatus err;

    fnEsamOp_RxTxCommhead(0x80, 0x36, 0x00, 0x04, 0x00, 0x00);

    err = fnEsamOp_CardTxRxFrame(ESAM, 0x00, (u8 *)uBuf, 0);
    if (err == ERROR)
    {
        return ERROR;
    }

    return SUCCESS;
}

//*****************************************************************************************************
// ��������void fnUpdatePswSta( void )
// ���룺
//
// ���أ�  TRUE:��Կ״̬�����ı�      FALSE:��Կ״̬δ�����仯
// ������   ����RAM��E2 ��Կ��Ϣ״̬����־λ
//******************************************************************************************************
u8 fnUpdatePswSta(void)
{
    //  u32 Temp;
    u8   Buf[FileItemInfoLen_CipherKeyPara_CipherKeyFlag];

    fnFile_Read(FileId_ParaCipherKey, FileItemInfoOffAddr_CipherKeyPara_CipherKeyFlag, &Buf[0], FileItemInfoLen_CipherKeyPara_CipherKeyFlag);

    if (fnReadPswVer_Esam(&ICEsamComm.Ic_Comm_RxBuf[4]) == SUCCESS)
    {
        if (fnDFCompData(&ICEsamComm.Ic_Comm_RxBuf[4], &Buf[0], FileItemInfoLen_CipherKeyPara_CipherKeyFlag) != 0)
        {
            fnFile_Write(FileId_ParaCipherKey, FileItemInfoOffAddr_CipherKeyPara_CipherKeyFlag, &ICEsamComm.Ic_Comm_RxBuf[4], FileItemInfoLen_CipherKeyPara_CipherKeyFlag);

            #if 0   /* dyf �ϵ����״̬ʱ���ܲ�ִ�е��˴� */

            if (fnJudge_Zero(&ICEsamComm.Ic_Comm_RxBuf[4], FileItemInfoLen_CipherKeyPara_CipherKeyFlag) == FALSE)
            {
                Bkgrd.PubData.CipherKeyFlag = 1;
                Bkgrd.PubData.MtSysSta.SysStaBit.KeySta = 1;
            }
            else
            {
                Bkgrd.PubData.CipherKeyFlag = 0;
                Bkgrd.PubData.MtSysSta.SysStaBit.KeySta = 0;
            }

            //Bkgrd.PubData.UpRunFileFlag = 0x5a;

            return TRUE;
            #endif
        }

        // dyf ������Կ���º��ϵ�ͬ������ESAM״̬�����ã���Ų��if {} ����
        if (fnJudge_Zero(&ICEsamComm.Ic_Comm_RxBuf[4], FileItemInfoLen_CipherKeyPara_CipherKeyFlag) == FALSE)
        {
            Bkgrd.PubData.CipherKeyFlag = 1;
            Bkgrd.PubData.MtSysSta.SysStaBit.KeySta = 1;
        }
        else
        {
            Bkgrd.PubData.CipherKeyFlag = 0;
            Bkgrd.PubData.MtSysSta.SysStaBit.KeySta = 0;
        }

        return TRUE;
    }
    else
    {
        if (fnJudge_Zero(&Buf[0], FileItemInfoLen_CipherKeyPara_CipherKeyFlag) == FALSE)
        {
            Bkgrd.PubData.CipherKeyFlag = 1;
            Bkgrd.PubData.MtSysSta.SysStaBit.KeySta = 1;
        }
        else
        {
            Bkgrd.PubData.CipherKeyFlag = 0;
            Bkgrd.PubData.MtSysSta.SysStaBit.KeySta = 0;
        }
    }

    return FALSE;
}

//*****************************************************************************************************
// ��������u8 fnReadDlyTime_Esam( u8*  uBuf )
// ���룺   RxBuf:��������
//          RxLen:����
// ���أ�
// ������  ��ȡESAM�Ựʣ��ʱ��
//******************************************************************************************************
u8 fnReadDlyTime_Esam(u32*  DlyTime, u8 CA, u8 Type)
{
    ErrorStatus err;
    u8  temp[20];

    if (CA & 0xF0) //��վ
    {
        fnEsamOp_RxTxCommhead(0x80, 0x36, 0x00, 0x05, 0x00, 0x00);
    }
    else   //�ն�
    {
        fnEsamOp_RxTxCommhead(0x80, 0x36, 0x00, 0x14, 0x00, 0x00);
    }

    err = fnEsamOp_CardTxRxFrame(ESAM, 0x00, (u8 *)&temp[0], NULL);     //�Ự����(4byte) + �Ựʣ��ʱ��(4byte)
    if (err == ERROR)
    {
        return ERROR;
    }

    if (Type) //����
    {
        *DlyTime = Std_Msb32DataGet(&temp[0]);  //min
        *DlyTime *= 60;  //sec
    }
    else   //ʣ��ʱ��
    {
        *DlyTime = Std_Msb32DataGet(&temp[4]);  //min
        *DlyTime *= 60;  //sec
    }
    return SUCCESS;
}

//*****************************************************************************************************
// �������� fnWrite_Broatcast_SafetyType
// ���룺
//
// ���أ�
// ������
//******************************************************************************************************
void fnWrite_Broatcast_SafetyType(u8  Type)
{
    Bkgrd.PubData.Broatcase_SfType = Type;
}

//*****************************************************************************************************
// ��������u8 fnRead_Broatcast_SafetyType
// ���룺
//
// ���أ�
// ������
//******************************************************************************************************
u8 fnRead_Broatcast_SafetyType(void)
{
    return Bkgrd.PubData.Broatcase_SfType;
}

//*****************************************************************************************************
// ��������u8 fnGetCurrTime
// ���룺
//
// ���أ�
// ������
//******************************************************************************************************
void fnGetCurrTime(sDate_time_s_TypeDef * ptime)
{
    Std_Memcpy((u8 *)&ptime->second, (u8 *)&SysDatetimes.second, sizeof(sDate_time_s_TypeDef));
}

/*********************************************************************************************************
** Function name:
** Descriptions:
** input parameters:
** output parameters:
** Returned value:
*********************************************************************************************************/
void fnConnDataInit(u8 Chan, u8 CA)
{
    Secret.Chan = Chan;

    if ((CA & 0xF0) == TERMINAL) //�ն�
    {
        Secret.CA = TERMINAL;
        if (Secret.Terminal.tLinkDly[Chan])
        {
            Secret.Terminal.tLinkDly[Chan] = Secret.Terminal.tLink[Chan];
        }
    }
    else
    {
        Secret.CA = MASTER;
        if (Secret.Master.tLinkDly[Chan])
        {
            Secret.Master.tLinkDly[Chan] = Secret.Master.tLink[Chan];
        }
    }
}

/*********************************************************************
* @fn      fnConnDataDefault
*
* @brief   Ӧ������ͨ�����ݻָ���Ĭ��ֵ
*
* @param   chan ͨ��
*
* @return  �Ƿ������ӳɹ����ɹ�����0, ʧ�ܷ��ط�0
*/
sLinkSize_TypeDef LinkSizeDefault[] =
{
    {1, DL698AL_APTU_MAXSIZE_485A, DL698AL_DL_SIZE_TX_485A, DL698AL_DL_SIZE_RX_485A},  /* channel 0 for 485A */
    {1, DL698AL_APTU_MAXSIZE_SPI,   DL698AL_DL_SIZE_TX_SPI, DL698AL_DL_SIZE_RX_SPI},  /* channel 1 for IR */
    {1, DL698AL_APTU_MAXSIZE_PLC,  DL698AL_DL_SIZE_TX_PLC,  DL698AL_DL_SIZE_RX_PLC},  /* channel 2 for ZBCOM */
    {1, DL698AL_APTU_MAXSIZE_485B, DL698AL_DL_SIZE_TX_485B, DL698AL_DL_SIZE_RX_485B}     /* channel 3 for 485B */
};

u8 fnConnSizeDefault(u8 chan, u8 CA)
{
    sCommSize_TypeDef temp;
    u8 offset, len;

    len = sizeof(sCommSize_TypeDef);
    Std_Memcpy((u8 *)&temp, (u8 *)&LinkSizeDefault[chan], len);
    offset = chan * len;

    if ((CA & 0xF0) == TERMINAL) //�ն�
    {
        fnFile_Write(FileId_InterTmp, FileItemInfoOffAddr_InterTmp_TLinkSize + offset, (u8 *)&temp, len);
    }
    else
    {
        fnFile_Write(FileId_InterTmp, FileItemInfoOffAddr_InterTmp_MLinkSize + offset, (u8 *)&temp, len);
    }

    return SUCCESS;
}

extern sDl698AL_UserCfg_TypeDef gUserCfg[];

u8 fnReadConnSize(sCommSize_TypeDef *LinkSize, u8 chan, u8 CA)
{
    u8 offset, len;

    len = sizeof(sCommSize_TypeDef);
    offset = chan * len;

    if ((CA & 0xF0) == TERMINAL) //�ն�
    {
        fnFile_Read(FileId_InterTmp, FileItemInfoOffAddr_InterTmp_TLinkSize + offset, (u8 *)LinkSize, len);
    }
    else
    {
        fnFile_Read(FileId_InterTmp, FileItemInfoOffAddr_InterTmp_MLinkSize + offset, (u8 *)LinkSize, len);
    }

    if ((LinkSize->apdu_window_size_rx == 0) || (LinkSize->apdu_window_size_rx > 1))
    {
        LinkSize->apdu_window_size_rx = 1;
    }

    /*
    if( (LinkSize->apdu_size == 0)||(LinkSize->apdu_size > 2048) )
        LinkSize->apdu_size = 2048;

    if( (LinkSize->dl_size_rx== 0)||(LinkSize->dl_size_rx> 2048) )//512
        LinkSize->dl_size_rx= 2048;

    if( (LinkSize->dl_size_tx== 0)||(LinkSize->dl_size_tx> 2048) )//512
        LinkSize->dl_size_tx= 2048;
    */

    if ((LinkSize->apdu_size == 0) || (LinkSize->apdu_size > gUserCfg[chan].apdu_size)) //2048
    {
        LinkSize->apdu_size = gUserCfg[chan].apdu_size;
    }

    if ((LinkSize->dl_size_rx == 0) || (LinkSize->dl_size_rx > gUserCfg[chan].dl_size_rx)) //512
    {
        LinkSize->dl_size_rx = gUserCfg[chan].dl_size_rx;
    }

    if ((LinkSize->dl_size_tx == 0) || (LinkSize->dl_size_tx > gUserCfg[chan].dl_size_tx)) //512
    {
        LinkSize->dl_size_tx = gUserCfg[chan].dl_size_tx;
    }

    return SUCCESS;
}

u8 fnWriteConnSize(sCommSize_TypeDef *LinkSize, u8 chan, u8 CA)
{
    u8 offset, len;

    len = sizeof(sCommSize_TypeDef);
    offset = chan * len;

    if ((CA & 0xF0) == TERMINAL) //�ն�
    {
        fnFile_Write(FileId_InterTmp, FileItemInfoOffAddr_InterTmp_TLinkSize + offset, (u8 *)LinkSize, len);
    }
    else
    {
        fnFile_Write(FileId_InterTmp, FileItemInfoOffAddr_InterTmp_MLinkSize + offset, (u8 *)LinkSize, len);
    }

    return SUCCESS;
}

/*********************************************************************
* @fn      fnFind_FrzMinSpecPos
*
* @brief   ���ҷ��Ӷ���ָ��
*
* @param  Line: ���Ӷ������߱��;type: �Ƚϵ�����ʼʱ������ʱ��
*              TimeDest:ָ��ʱ��;tempFrzMin:���Ӷ�������ͷ��Ϣ
*
* @return    �ҵ���������ָ��(�ڼ������:1~FFFE)��=0����0xFFFF ʱ��ʾ�Ҳ�����Чָ��
*/
u32  fnFind_FrzMinSpecPos(u8 Line, u8 type, sDate_time_s_TypeDef  *TimeDest,  sFrzMinHead_TypeDef  *tempFrzMin)
{
    u32  OffAddr, tempu32 ;
    u32  Startcnt, Endcnt, Midcnt, find = 0;
    sDate_time_s_TypeDef timesrc1, timesrc2;
    s8 ret ;
    u8 temp8;

    Startcnt = (tempFrzMin->RecHead.FrzAddrEnd - tempFrzMin->RecHead.FrzAddrStart);

    if (Startcnt >= tempFrzMin->LinePara.Depth)
    {
        Startcnt = tempFrzMin->LinePara.Depth;
    }

    Endcnt = 1;

    tempu32 = tempFrzMin->RecHead.FrzAddrStart % tempFrzMin->LinePara.Depth;

    OffAddr = FileItemInfo_FrzRecord[FileItemInfoNum_Frz_MinFrz].OffAddr + (u32)tempFrzMin->LinePara.LineOffAdder ;
    OffAddr += tempu32 * (u32)tempFrzMin->LinePara.RecLen + (u32)Frz_StdRecList.Clist[1].OffPos;

    fnFile_Read(FileId_FrzRecord,  OffAddr, (u8 *)&timesrc1, sizeof(sDate_time_s_TypeDef));

    Std_Memcpy((u8 *)&timesrc2, (u8 *)&tempFrzMin->RecHead.FrzTime, sizeof(sDate_time_s_TypeDef));   //��ȡ�����¼ʱ��

    if (type == GETPOS_START)
    {
        if (TimeDest->second)  //���Ӷ�����������ֲ���
        {
            TimeDest->second = 0;
            TimeDest->minute ++;
            if (TimeDest->minute > 59)
            {
                TimeDest->minute = 0;
            }
        }

        temp8 = TimeDest->minute % tempFrzMin->LinePara.Cycle;
        if (temp8)
        {
            fnMinAdd(TimeDest, (tempFrzMin->LinePara.Cycle - temp8));   //
        }

        if (fnDFCompData((u8 *)TimeDest, (u8 *)&timesrc1, sizeof(sDate_time_s_TypeDef)) != 1) //����ʱ��С�ڵ��������¼ʱ��
        {
            return Startcnt;
        }
        if (fnDFCompData((u8 *)TimeDest, (u8 *)&timesrc2, sizeof(sDate_time_s_TypeDef)) == 1) //����ʱ����������¼ʱ��
        {
            return 0xFFFFFFFF;
        }
    }

    if (type == GETPOS_END)
    {
        if (fnDFCompData((u8 *)TimeDest, (u8 *)&timesrc1, sizeof(sDate_time_s_TypeDef)) != 1) //����ʱ��С�ڵ��������¼ʱ��
        {
            return 0xFFFFFFFF;
        }
        if (fnDFCompData((u8 *)TimeDest, (u8 *)&timesrc2, sizeof(sDate_time_s_TypeDef)) == 1) //����ʱ����������¼ʱ��
        {
            return (Endcnt - 1);
        }
    }
    //-----------����ʱ���������¼ʱ��������¼ʱ��֮��--------------------
    do
    {
        Midcnt = (Startcnt + Endcnt) / 2;

        tempu32 = (tempFrzMin->RecHead.FrzAddrEnd % tempFrzMin->LinePara.Depth);
        tempu32 = (tempFrzMin->LinePara.Depth + tempu32 - (u32)Midcnt) % tempFrzMin->LinePara.Depth;

        OffAddr = FileItemInfo_FrzRecord[FileItemInfoNum_Frz_MinFrz].OffAddr + (u32)tempFrzMin->LinePara.LineOffAdder ;
        OffAddr += tempu32 * (u32)tempFrzMin->LinePara.RecLen + Frz_StdRecList.Clist[1].OffPos;

        fnFile_Read(FileId_FrzRecord,  OffAddr, (u8 *)&timesrc1, sizeof(sDate_time_s_TypeDef));
        fnWDT_Restart();    // dyf add

        if (type == GETPOS_START)
        {
            ret = fnDFCompData((u8 *)TimeDest, (u8 *)&timesrc1, sizeof(sDate_time_s_TypeDef));
            if (ret == 1) //����ʱ����ڼ�¼��ʱ��
            {
                Startcnt = Midcnt - 1;
            }
            else if (ret == 0)
            {
                find = Midcnt;
                break;
            }
            else
            {
                Endcnt = Midcnt + 1;
            }
        }

        if (type == GETPOS_END)
        {
            ret = fnDFCompData((u8 *)TimeDest, (u8 *)&timesrc1, sizeof(sDate_time_s_TypeDef));
            if (ret == 1) //����ʱ����ڼ�¼��ʱ��
            {
                Startcnt = Midcnt - 1;
            }
            else if (ret == 0)
            {
                find = Midcnt;
                break;
            }
            else
            {
                Endcnt = Midcnt + 1;
            }
        }
    } while ((Endcnt <= Startcnt) && (find == 0));

    if (find == 0) //���ַ����Ҳ���ʱ�����ȵĵ�
    {
        if (ret == 1)
        {
            find = Midcnt - 1;
        }
        else
        {
            find = Midcnt;
        }
    }

    return find;
}

/*********************************************************************
* @fn      fnFind_FrzSpecPos
*
* @brief   ���ҳ����Ӷ�����Ķ���ָ��
*
* @param  Item: �������߱��;type: �Ƚϵ�����ʼʱ������ʱ��
*              TimeDest:ָ��ʱ��;tempFrzMin:���Ӷ�������ͷ��Ϣ
*
* @return    �ҵ���������ָ��(�ڼ������:1~FFFE)��=0����0xFFFF ʱ��ʾ�Ҳ�����Чָ��
*/
u16  fnFind_FrzSpecPos(u8 Item, u8 type, sDate_time_s_TypeDef  *TimeDest,  sFrzCtxList_TypeDef  *List)
{
    u32  OffAddr, tempu32 ;
    u16  Startcnt, Endcnt, Midcnt, find = 0, recordlen;
    sDate_time_s_TypeDef timesrc1, timesrc2;
    s8 ret ;
    sFrzRcdHead_TypeDef  tempFrzRcdHead;
    u8 temp[3];

    //---------��ȡ��ǰ��¼����---------------
    fnFile_Read(FileId_FrzRcdHead, FileItemInfo_FrzRcdHead[Item].OffAddr, (u8 *)&tempFrzRcdHead, sizeof(sFrzRcdHead_TypeDef));

    fnFile_Read(FileId_FrzCtxlist, FileItemInfo_FrzCtxlist[Item].OffAddr, &temp[0], 3);

    recordlen = Std_Lsb16DataGet(&temp[1]);

    Startcnt = (u16)(tempFrzRcdHead.FrzAddrEnd - tempFrzRcdHead.FrzAddrStart);

    if (Startcnt >= List->Depth)
    {
        Startcnt = List->Depth;
    }

    Endcnt = 1;
    tempu32 = tempFrzRcdHead.FrzAddrStart % List->Depth;

    OffAddr = FileItemInfo_FrzRecord[Item].OffAddr;
    OffAddr += tempu32 * (u32)recordlen + Frz_StdRecList.Clist[1].OffPos;

    fnFile_Read(FileId_FrzRecord,  OffAddr, (u8 *)&timesrc1, sizeof(sDate_time_s_TypeDef));

    Std_Memcpy((u8 *)&timesrc2, (u8 *)&tempFrzRcdHead.FrzTime, sizeof(sDate_time_s_TypeDef));   //��ȡ�����¼ʱ��

    if (type == GETPOS_START)
    {
        if (fnDFCompData((u8 *)TimeDest, (u8 *)&timesrc1, sizeof(sDate_time_s_TypeDef)) != 1) //����ʱ��С�ڵ��������¼ʱ��
        {
            return  Startcnt;
        }
        if (fnDFCompData((u8 *)TimeDest, (u8 *)&timesrc2, sizeof(sDate_time_s_TypeDef)) == 1) //����ʱ����������¼ʱ��
        {
            return 0xFFFF;
        }
    }

    if (type == GETPOS_END)
    {
        if (fnDFCompData((u8 *)TimeDest, (u8 *)&timesrc1, sizeof(sDate_time_s_TypeDef)) != 1) //����ʱ��С�ڵ��������¼ʱ��
        {
            return 0xFFFF;
        }
        if (fnDFCompData((u8 *)TimeDest, (u8 *)&timesrc2, sizeof(sDate_time_s_TypeDef)) == 1) //����ʱ����������¼ʱ��
        {
            return (Endcnt - 1);
        }
    }

    do
    {
        Midcnt = (Startcnt + Endcnt) / 2;

        tempu32 = (tempFrzRcdHead.FrzAddrEnd % List->Depth);
        tempu32 = (List->Depth + tempu32 - (u32)Midcnt) % List->Depth;

        OffAddr = FileItemInfo_FrzRecord[Item].OffAddr;
        OffAddr += tempu32 * (u32)recordlen + Frz_StdRecList.Clist[1].OffPos;

        fnFile_Read(FileId_FrzRecord,  OffAddr, (u8 *)&timesrc1, sizeof(sDate_time_s_TypeDef));

        if (type == GETPOS_START)
        {
            ret = fnDFCompData((u8 *)TimeDest, (u8 *)&timesrc1, sizeof(sDate_time_s_TypeDef));
            if (ret == 1) //����ʱ����ڼ�¼��ʱ��
            {
                Startcnt = Midcnt - 1;
            }
            else if (ret == 0)
            {
                find = Midcnt;
                break;
            }
            else
            {
                Endcnt = Midcnt + 1;
            }
        }

        if (type == GETPOS_END)
        {
            ret = fnDFCompData((u8 *)TimeDest, (u8 *)&timesrc1, sizeof(sDate_time_s_TypeDef));
            if (ret == 1) //����ʱ����ڼ�¼��ʱ��
            {
                Startcnt = Midcnt - 1;
            }
            else if (ret == 0)
            {
                find = Midcnt;
                break;
            }
            else
            {
                Endcnt = Midcnt + 1;
            }
        }
    } while ((Endcnt <= Startcnt) && (find == 0));

    if (find == 0) //���ַ����Ҳ���ʱ�����ȵĵ�
    {
        if (ret == 1)  //����ʱ����ڼ�¼��ʱ��
        {
            find = Midcnt - 1;
        }
        else
        {
            find = Midcnt;
        }
    }

    return find;
}

/*********************************************************************
* @fn      CheckTPeriodValid
*
* @brief  ʱ�α�Ϸ����жϣ���������ʱ�������15min
*
* @param
*
*
* @return
*/
u8 CheckTPeriodValid(u8 *Buf, u8 tpnum)
{
    return SUCCESS;
}

void  fnCommStatus(u8 id)
{
    if (id == SCOM_PORT_RS485A)
    {
        Bkgrd.PubData.CommStatus |= F_Comm1Event;
    }
    if (id == SCOM_PORT_RS485B)
    {
        Bkgrd.PubData.CommStatus |= F_Comm2Event;
    }
    if (id == SCOM_PORT_IR)
    {
        Bkgrd.PubData.CommStatus |= F_Comm3Event;
    }
    if (id == SCOM_PORT_ZBCOM)
    {
        Bkgrd.PubData.CommStatus |= F_Comm4Event;
    }
}

//-------�����ϱ�-----------------------
/*********************************************************************************************************
** Function name:   fnReport_EvtData
** Descriptions:    �����ϱ�
** input parameters:
** output parameters:   pRetBuf:��ȡ��������.   pRetLen:��ȡ��������Ӧ�𳤶�
** Returned value:��ȡ�ɹ���ʧ�ܽ��
*********************************************************************************************************/
const u8 AtiveOAD[5] = {0x33, 0x20, 0x02, 0x00, 0x01};     //�����ϱ��̶�OAD    0x33200101��������̶�1��
const u8 statusOAD[5] = {0x20, 0x15, 0x02, 0x00, 0x01};
const u8 PdMethod[3] = {0x09, 0x01, 0x00};
const u8 PownDnOAD[5] = {0x01, 0x30, 0x11, 0x02, 0x01};

u8 fnReport_EvtData(u8 *pRetBuf, u16 *pRetLen, u8 type,  u8  *blockRsp)
{
    u8 i, j, Num = 0, Offset, len ;
    u16 recordlen, len16 = 0;
    u8 temp[5] ;
    u32 OAD1;

    u8 *uBuf;
    sContextList_TypeDef    tmplist1;

    u8  *BufList, *pRecordBuf;

    if (type == RPTEVT_POWNDOWN)
    {
        uBuf = (u8 *)fnDl698_Buffer_Alloc(256);
        if (uBuf == NULL)
        {
            return DATA_ACCESS_AL_MEMALLOC_ERR;
        }
        Std_Memset(uBuf, 0, 256);

        BufList = (u8 *)fnDl698_Buffer_Alloc(512);
        if (BufList == NULL)
        {
            fnDl698_Buffer_Free(uBuf);
            return DATA_ACCESS_AL_MEMALLOC_ERR;
        }
        Std_Memset(BufList, 0, 512);

        pRecordBuf = (u8 *)fnDl698_Buffer_Alloc(256);
        if (pRecordBuf == NULL)
        {
            fnDl698_Buffer_Free(uBuf);
            fnDl698_Buffer_Free(BufList);
            return DATA_ACCESS_AL_MEMALLOC_ERR;
        }
        Std_Memset(pRecordBuf, 0, 256);

        Std_Memcpy(pRetBuf, (u8 *)&PownDnOAD[0], 5);
        *pRetLen += 5;
        pRetBuf += 5;

        //-------��ȡ�����������Ա�-----------
        //???
        //          fnFile_Read( FileId_EvtCtxlist,
        //                              FileItemInfoOffAddr_EvtCtxlist_PowDn,
        //                              BufList ,
        //                              FileItemInfoLen_EvtCtxlist_Prg  );
        fnFile_Read(FileId_EvtCtxlist,
                    FileItemInfoOffAddr_EvtCtxlist_PowDn,
                    BufList,
                    FileItemInfoLen_EvtCtxlist_PowDn);

        for (i = 0; i < EvtC7_StdRecList.num; i++) //--5�б�׼�¼���Ԫ----
        {
            Std_MemRvs(uBuf + i * 5 + 1, (u8 *)&EvtC7_StdRecList.Clist[i].OAD, 4);
        }

        Num = (*BufList++) + EvtC7_StdRecList.num; //���ϱ�׼�¼���¼��Ԫ 5��

        Std_Memcpy((u8 *)&recordlen, BufList, 2);

        BufList += 2;  //ƫ��1byte OADNum + 2byte recordLen

        for (i = EvtC7_StdRecList.num; i < Num; i++)
        {
            Offset = sizeof(sContextList_TypeDef) * (i - EvtC7_StdRecList.num);
            Std_Memcpy((u8 *)&tmplist1, BufList + Offset, sizeof(sContextList_TypeDef));
            Std_MemRvs(uBuf + i * 5 + 1, (u8 *)&tmplist1.OAD, 4);
        }

        *pRetBuf++ = Num;
        len = Num * 5;
        Std_Memcpy(pRetBuf, uBuf, len);
        pRetBuf += len;
        *pRetLen += len + 1;

        *pRetBuf++ = 1;   // ---1���¼���¼
        *pRetBuf++ = 1;
        *pRetLen += 2;

        fnFile_Read(FileId_EvtReport, FileItemInfoOffAddr_EvtReport_PowerDnEvtRcd, pRecordBuf, recordlen);

        for (j = 0; j < Num; j++)
        {
            if (j < EvtC7_StdRecList.num) //--��׼�¼���Ԫ----
            {
                Std_Memcpy((u8 *)&tmplist1, (u8 *)&EvtC7_StdRecList.Clist[j], sizeof(sContextList_TypeDef));
                if (tmplist1.OAD == 0x20200200) //�¼�����ʱ����NULL
                {
                    temp[0] = NULL;
                }
                else
                {
                    temp[0] = EvtStdRcdList_DataType[j];
                }
            }
            else
            {
                Offset = sizeof(sContextList_TypeDef) * (j - EvtC7_StdRecList.num);
                Std_Memcpy((u8 *)&tmplist1, BufList + Offset, sizeof(sContextList_TypeDef));
                fnGet_OADDataType(tmplist1.OAD, &temp[0]);
            }

            Std_Memcpy(uBuf, pRecordBuf + tmplist1.OffPos, tmplist1.len);
            len16 = (u16)tmplist1.len;
            pRetBuf += fnForm_build_Type(pRetBuf, pRetLen, uBuf, &len16, &temp[0]);
        }

        fnDl698_Buffer_Free(uBuf);//��Դ�ͷ�
        fnDl698_Buffer_Free(BufList);//��Դ�ͷ�
        fnDl698_Buffer_Free(pRecordBuf);//��Դ�ͷ�
    }
    else if (type == RPTEVT_POWNUP)
    {
        //��̬������ʱbuf
        uBuf = (u8 *)fnDl698_Buffer_Alloc(TEMP_GETREC_MAXSIZE);
        if (uBuf == NULL)
        {
            return DATA_ACCESS_AL_MEMALLOC_ERR;
        }
        Std_Memset(uBuf, 0, TEMP_GETREC_MAXSIZE);

        //--------��װ��ʹ�÷���9��ȡ�ϼ��μ�¼---------------
        Std_Memcpy(&temp[0], (u8 *)&PdMethod[0], 3);

        *blockRsp = FALSE;
        //          OAD1 = 0x30110200;
        OAD1 = 0x30500200;
        Std_Memcpy(pRetBuf, (u8 *)&PownDnOAD[0], 5);
        *pRetLen += 5;
        pRetBuf += 5;

        fnGet_EvtRecord(OAD1, &temp[0], uBuf, pRetBuf, pRetLen, blockRsp, FALSE);

        fnDl698_Buffer_Free(uBuf);//��Դ�ͷ�
    }
    else
    {
        if (EvtRptData.ListZB_A.OADNum)
        {
            Num++;
        }

        if ((EvtRptData.Para.RptStatusAllow == 0) && (EvtRptData.Status.RptStuZB))
        {
            Num++;
        }

        *pRetBuf++ = Num;
        *pRetLen += 1;

        if (EvtRptData.ListZB_A.OADNum)
        {
            Std_Memcpy(pRetBuf, (u8 *)&AtiveOAD[0], 5);
            *pRetLen += 5;
            pRetBuf += 5;

            pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &EvtRptData.ListZB_A.OADNum, NULL, DTYPE_ARRAY);

            for (i = EvtRptData.ListZB_A.OADNum ; i > 0 ; i--)
            {
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&EvtRptData.ListZB_A.OAD[i - 1], NULL, DTYPE_OAD);
            }
        }

        if ((EvtRptData.Para.RptStatusAllow == 0) && (EvtRptData.Status.RptStuZB))
        {
            Std_Memcpy(pRetBuf, (u8 *)&statusOAD[0], 5);
            *pRetLen += 5;
            pRetBuf += 5;
            len16 = 4;
            pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&EvtRptData.Status.RptStuZB, &len16, DTYPE_BITSTRING);
        }
    }

    EvtRptData.ReportCnt--;  //�ɹ���װ�������ݣ�������1

    if (type == RPTEVT_POWNDOWN)
    {
        EvtRptData.tReportDely = 0;
    }
    else
    {
        EvtRptData.tReportDely = 10;    //��һ֡���10��
    }

    return SUCCESS;
}

/*********************************************************************************************************
** Function name:   fnCheck_ReportCnt
** Descriptions:    �����ϱ�������ȡ
** input parameters:
** output parameters:
** Returned value:�����ϱ�����
*********************************************************************************************************/
u8 fnCheck_ReportCnt(void)
{
    if (EvtRptData.Para.AtiveAllow != TRUE) //�����ϱ�����δ����
    {
        EvtRptData.ReportCnt = 0;
        EvtRptData.tReportDely = 0;
    }

    if ((EvtRptData.ReportCnt) && (EvtRptData.tReportDely == 0))
    {
        return EvtRptData.ReportCnt;
    }
    else
    {
        return 0;    //�����ϱ�����Ϊ0�����ϱ����ʱ�䲻��10��ʱ������0
    }
}

/*********************************************************************************************************
** Function name:   fnCheck_ReportCnt
** Descriptions:    �����ϱ�������ȡ
** input parameters:
** output parameters:
** Returned value:�����ϱ�����
*********************************************************************************************************/
u8 fnCheck_RptType(void)
{
    return EvtRptData.RptType;
}

/*********************************************************************************************************
** Function name:   fnCheck_nMacErr
** Descriptions:
** input parameters:
** output parameters:
** Returned value:
*********************************************************************************************************/
u8 fnCheck_nMacErr(void)
{
    if (Secret.nMacErr >= MAX_MACERR)
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}

void  fnGet_ConnServer(u8 *Data)
{
    u8 buf[FileItemInfoLen_ASCIIPara_ServerVer];

    fnFile_Read(FileId_ParaASCII, FileItemInfoOffAddr_ASCIIPara_ServerVer, &buf[0], FileItemInfoLen_ASCIIPara_ServerVer);

    if (fnJudge_Value(&buf[0], 0xFF, FileItemInfoLen_ASCIIPara_ServerVer))
    {
        fnFile_Write(FileId_ParaASCII, FileItemInfoOffAddr_ASCIIPara_ServerVer, (u8 *)&ASCIIParaDefault + FileItemInfoOffAddr_ASCIIPara_ServerVer, FileItemInfoLen_ASCIIPara_ServerVer);
        Std_Memcpy(&buf[0], (u8 *)&ASCIIParaDefault + FileItemInfoOffAddr_ASCIIPara_ServerVer, FileItemInfoLen_ASCIIPara_ServerVer);
    }

    Std_Memcpy(Data, &buf[0], FileItemInfoLen_ASCIIPara_ServerVer);
}
