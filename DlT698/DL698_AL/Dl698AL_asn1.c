
#include "Dl698_Type.h"
#include "Dl698AL_def.h"
#include "DL698_Globals.h"
#include "Dl698_AL.h"
#include "Dl698AL_Get.h"
#include "Dl698AL_Set.h"
#include "Dl698AL_Act.h"
#include "Dl698_DL.h"
#include "Dl698AL_asn1.h"
//�������е����ݽ��б��룬��֧�ֵ��������ͼ������г����ĺ궨�弰˵����ʹ��BER���뷽ʽ
//���������������bufferָ�򻺴��е��ֽ��������ظ���������Ӧ����
//BITSTRING���͵�data_len��BITλ��λ���������������ֽڳ��ȡ�
//BITSTRING���͵�������Чλ�����һ���ֽڵĵ�λ��

//��IC������������
extern u8 gDl698_DataTypList_IC01[];
extern u8 gDl698_HDRDataTypList_IC01[];
extern u8 gDl698_DataTypList_IC02[];
extern u8 gDl698_DataTypList_IC03[];
extern u8 gDl698_DataTypList_IC04[];
extern u8 gDl698_DataTypList_IC05[];
extern u8 gDl698_DataTypList_IC06[];

//����ĺ���ʵ���ǿ��õģ������Ǽ򻯺�İ汾��ֱ���ж�data_len�Ĵ�С
u8 fnDL698AL_asn1_set_ObjCnt(u16 data_len, u8* buffer)
{
    //���length����127����Ҫ���0x80+XX������XX��ʾlengthռ�õ��ֽ�
    //���length����127����ô��Ҫʹ�ö���ֽڱ�ʾlength����һ���ֽ�0x80 | fffffff
    //����fffffff��7bit��ʾ����lengthռ�õ��ֽ���������������length�Ͳ���Ҫ�ٿ��Ǳ���
    //bitλ��
    //data_len > 0xFF  ��ôlength������Ҫ�����ֽڣ����ϵ�һ��������ֽڣ�����Ҫ�����ֽ�
    //0xFF >= data_len > 0x7F ��ôlength������Ҫһ���ֽڣ�   ����Ҫ�����ֽ�
    // data_len <= 0xFF�� ����Ҫ������ֽڣ�����Ҫһ���ֽڡ�
    u8 op_len = 0;

    if (data_len > 0xFF)
    {
        //0x82
        if (buffer != NULL)
        {
            *buffer++ = 0x82;
            *buffer++ = (data_len >> 8) & 0xFF;
            *buffer++ =  data_len     & 0xFF;
        }
        op_len = 3;
    }
    else if (data_len > 0x7F)
    {
        //0x81
        if (buffer != NULL)
        {
            *buffer++ = 0x81;
            *buffer++ =  data_len     & 0xFF;
        }
        op_len = 2;
    }
    else
    {
        //�������
        if (buffer != NULL)
        {
            *buffer++ = data_len & 0xFF;
        }
        op_len = 1;
    }

    return op_len;
}

u16 fnDL698AL_asn1_get_ObjCnt(u16* data_len, u8* buffer)
{
    u16 op_len = 1;
    u16 cnt = *buffer++ & 0xFF;
    if (cnt > 0x80)
    {
        s32 tmp = cnt;
        s32 pos;
        cnt = 0;
        for (pos = tmp - 0x81; pos > -1; --pos)
        {
            cnt += (*buffer++ & 0xFF) << (8 * pos);
            ++op_len;
        }
    }

    *data_len = cnt;

    return op_len;
}

/*********************************************************************
* @fn      fnDl698AL_Check_TimeTag
*
* @brief
*
* @param
*
* @return  ����ʱ���ǩ��ƫ�Ƶ�ַ�����û��ʱ���ǩ���򷵻�0xFFFF
*/
u16 fnDl698AL_Check_TimeTag(u8 chan)
{
    u8* pBuf = gDl698AL_Server.pAlChan[chan].apdu_rx_buf.data;
    //    u8* pData = NULL;
    u8 tag = *pBuf++;
    u8 tag2 = *pBuf++;
    u16 offset = 0xFFFF;
    u16 ret = 0xFFFF;
    u8  seqnum = 0;
    u8 i;
    //u8 vert0;
    //-------debug------
    //  u8 temp[50];
    //  u16 len;

    switch (tag)
    {
        case (DL698AL_APDU_TAG_CONREQ):
        {
            pBuf += 37;             //ָ���ߵ���֤���Ʊ�ʶ�ֽ�
            tag2 = *pBuf++;
            if (tag2 == NullSecurity)
            {
                offset = DL698AL_TIMETAG_CONREQ_NOSECU;   //��������
            }
            else if (tag2 == PasswordSecurity)
            {
                offset = DL698AL_TIMETAG_CONREQ_PWDSECU + (*pBuf);   //һ������
            }
            else if (tag2 == SymmetrySecurity)
            {
                offset = DL698AL_TIMETAG_CONREQ_SYMMSECU;   //�Գ�����
            }
            break;
        }
        case (DL698AL_APDU_TAG_RLSREQ):
        {
            offset = DL698AL_TIMETAG_CONRLS;
            break;
        }
        case (DL698AL_APDU_TAG_GETREQ):
        {
            switch (tag2)
            {
                case (DL698AL_GETTYPE_NORMAL):
                {
                    offset = DL698AL_TIMETAG_GETNORM;
                    break;
                }
                case (DL698AL_GETTYPE_NORMALLIST):
                {
                    pBuf++;  //PIID
                    offset = 3;
                    seqnum = *pBuf++;
                    offset++;    //add by wj
                    offset += seqnum * 4;
                    break;
                }
                case (DL698AL_GETTYPE_RECORD):
                {
                    pBuf++;  //PIID
                    offset = 3;//PIID
                    pBuf += 4; //OAD
                    offset += 4; //OAD
                    //RSD
                    ret = fnDl698AL_GetData_Len(0, DTYPE_RSD, pBuf);
                    if (ret != 0xFFFF)
                    {
                        offset += ret;
                        pBuf += ret;   //modified by wj
                    }
                    //RCSD
                    ret = fnDl698AL_GetData_Len(0, DTYPE_RCSD, pBuf);
                    if (ret != 0xFFFF)
                    {
                        offset += ret;
                        pBuf += ret;
                    }
                    break;
                }
                case (DL698AL_GETTYPE_RECORDLIST):
                {
                    pBuf++;  //PIID
                    offset = 3;
                    seqnum = *pBuf++;
                    offset++;    //add by wj
                    for (i = 0; i < seqnum; i++)
                    {
                        pBuf += 4;     //OAD
                        offset += 4;   //OAD
                        //RSD
                        ret = fnDl698AL_GetData_Len(0, DTYPE_RSD, pBuf);
                        if (ret != 0xFFFF)
                        {
                            offset += ret;
                            pBuf += ret;   //modified by wj
                        }
                        //RCSD
                        ret = fnDl698AL_GetData_Len(0, DTYPE_RCSD, pBuf);
                        if (ret != 0xFFFF)
                        {
                            offset += ret;
                            pBuf += ret;
                        }
                    }
                    break;
                }
                case (DL698AL_GETTYPE_NEXT):
                {
                    offset = DL698AL_TIMETAG_GETNXT;
                    break;
                }
                #ifdef DL698_GST_TEST
                case (DL698AL_GETDI_TEST):
                {
                    offset = DL698AL_TIMETAG_GETNORM;
                    break;
                }

                case (DL698AL_GETRECORDDI_TEST):
                {
                    pBuf++;  //PIID
                    offset = DL698AL_TIMETAG_GETRECORDDI;
                    break;
                }
                #endif
                default:
                    break;  //do nothing
            }
            break;
        }
        case (DL698AL_APDU_TAG_SETREQ):
        {
            //-------debug------
            //  u8 temp[50];
            /*
                temp[0] = gDl698AL_Server.pAlChan[chan].apdu_rx_buf.right;
                temp[1] = DL698AL_APDU_TAG_SETREQ;
                temp[2] = tag2;
                if(gDl698AL_Server.pAlChan[chan].apdu_rx_buf.right > 50)
                    len = 50;
                else
                    len = (u16)gDl698AL_Server.pAlChan[chan].apdu_rx_buf.right;
                Std_Memcpy(&temp[3] , pBuf , len);
                fnFile_Write(12 , 12, &temp[0] , (u32)(len));
            */
            switch (tag2)
            {
                case (DL698AL_SETTYPE_NORMAL):
                {
                    pBuf += 5;  //data type
                    offset = 7;
                    ret = fnDl698AL_GetData_Len(1, 0, pBuf);
                    if ((ret != 0) && (ret != 0xFFFF))
                    {
                        offset += ret;
                        pBuf += ret;
                    }
                    break;
                }
                case (DL698AL_SETTYPE_NORMALLIST):
                {
                    pBuf++;  //data type
                    offset = 3;
                    seqnum = *pBuf++;
                    offset++;    //add by wj
                    for (i = 0; i < seqnum; i++)
                    {
                        pBuf += 4;
                        offset += 4;
                        ret = fnDl698AL_GetData_Len(1, 0, pBuf);
                        if ((ret != 0) && (ret != 0xFFFF))
                        {
                            offset += ret;
                            pBuf += ret; //add by wj
                        }
                        else
                        {
                            return 0xFFFF;
                        }
                    }
                    break;
                }
                case (DL698AL_SETTHENGETNORMALLIST):
                {
                    pBuf++;  //piid
                    offset = 3;
                    seqnum = *pBuf++;
                    offset++;    //add by wj
                    for (i = 0; i < seqnum; i++)
                    {
                        //set
                        pBuf += 4;  //OAD
                        offset += 4;
                        ret = fnDl698AL_GetData_Len(1, 0, pBuf);
                        if ((ret != 0) && (ret != 0xFFFF))
                        {
                            offset += ret;
                            pBuf += ret; //add by wj
                        }
                        else
                        {
                            return 0xFFFF;
                        }
                        //get
                        pBuf += 5;  // 4(OAD)+1(Delay)
                        offset += 5;
                    }
                    break;
                }
                default:
                    break;
            }
            break;
        }
        case (DL698AL_APDU_TAG_ACTREQ): //����ACT��SET��Ӧ������װ����һ��
        {
            /*
            temp[0] = gDl698AL_Server.pAlChan[chan].apdu_rx_buf.right;
            temp[1] = DL698AL_APDU_TAG_ACTREQ;
            temp[2] = tag2;
            if(gDl698AL_Server.pAlChan[chan].apdu_rx_buf.right > 50)
                len = 50;
            else
                len = (u16)gDl698AL_Server.pAlChan[chan].apdu_rx_buf.right;
            Std_Memcpy(&temp[3] , pBuf , len);
            fnFile_Write(12 , 12, &temp[0] , (u32)(len));
            */
            switch (tag2)
            {
                case (DL698AL_ACTTYPE_NORMAL):
                {
                    pBuf += 5;  //data type
                    offset = 7;
                    ret = fnDl698AL_GetData_Len(1, 0, pBuf);
                    if (ret != 0)
                    {
                        offset += ret;
                        pBuf += ret;
                    }
                    break;
                }
                case (DL698AL_ACTTYPE_NORMALLIST):
                {
                    pBuf++;  //data type
                    offset = 3;
                    seqnum = *pBuf++;
                    offset++;    //add by wj
                    for (i = 0; i < seqnum; i++)
                    {
                        pBuf += 4;
                        offset += 4;
                        ret = fnDl698AL_GetData_Len(1, 0, pBuf);
                        if (ret != 0)
                        {
                            offset += ret;
                            pBuf += ret; //add by wj
                        }
                        else
                        {
                            return 0xFFFF;
                        }
                    }
                    break;
                }
                case (DL698AL_ACTTHENGETNORMALLIST):
                {
                    pBuf++;  //data type
                    offset = 3;
                    seqnum = *pBuf++;
                    offset++;    //add by wj
                    for (i = 0; i < seqnum; i++)
                    {
                        //set
                        pBuf += 4;
                        offset += 4;
                        ret = fnDl698AL_GetData_Len(1, 0, pBuf);
                        if (ret != 0)
                        {
                            offset += ret;
                            pBuf += ret;
                        }
                        else
                        {
                            return 0xFFFF;
                        }
                        //get
                        pBuf += 5;
                        offset += 5;
                    }
                    break;
                }
                default:
                    break;
            }
            break;
        }
        case (DL698AL_APDU_TAG_RPTRSP):
        {
            pBuf++;       //piid
            offset = 3;
            seqnum = *pBuf++;
            offset++;    //add by wj
            offset += seqnum * 4;
            break;
        }
        default:
            break;  //do nothing
    }

    if (offset != 0xFFFF)
    {
        if (offset >= gDl698AL_Server.pAlChan[chan].apdu_rx_buf.right - gDl698AL_Server.pAlChan[chan].apdu_rx_buf.left)
        {
            //offset����Խ��
            offset = 0xFFFF;
        }
        else
        {
            pBuf = gDl698AL_Server.pAlChan[chan].apdu_rx_buf.data;
            pBuf += offset;
            //---------ʱ���ǩ�����ж�---------------
            if (*pBuf == 0) //��ʱ���ǩ
            {
                if ((offset + 1) <  gDl698AL_Server.pAlChan[chan].apdu_rx_buf.right - gDl698AL_Server.pAlChan[chan].apdu_rx_buf.left)
                {
                    offset = 0xFFFF;
                }
            }
            else if (*pBuf == 1) //��ʱ���ǩ
            {
                if ((offset + 11) <  gDl698AL_Server.pAlChan[chan].apdu_rx_buf.right - gDl698AL_Server.pAlChan[chan].apdu_rx_buf.left)
                {
                    offset = 0xFFFF;
                }
            }
            else
            {
                offset = 0xFFFF;
            }
        }
    }

    return offset;
}

/*********************************************************************
* @fn      fnDl698AL_GetData_Len
*
* @brief   ��ȡ���ݳ���(�����ͣ�ֻ��һ������)
*
* @param   pBuf          ������buf
*          dattyp_exist  ָʾ������buf��ͷ���Ƿ�����������ͣ����ϵ�����ص����ݳ���
*                        0Ϊ���������ͣ�1Ϊ�����ݳ���
*          datatype      ָ��һ���������ͣ�����dattyp_existΪ0ʱ�Ż�鿴datatype���Ҵ�
*                        datatypeһ���ֽڲ����뷵�س�����
*
* @return  ���ػ�ȡ�������ݳ���
*/

//���ݲ��������ͺͳ��Ȼ�ȡASN.1 BER��װ�ĳ���
//���type�ǹ̶����ȵ�type�������len������
//���type�ǿɱ䳤�ȵ�type����ʹ��len������Ϊ�������ݵĳ��ȡ�
u16 fnDl698AL_GetSimpleData_Len(u8 dattyp_exist, u8 datatype, u8* pBuf)
{
    u16 encap_size = 0;
    //    u16 offset = 0xFFFF;
    u16 ret = 0xFFFF;
    u8  seqnum = 0;
    //    u8  selpar = 0;
    u32  k;
    //    u8  j = 0;
    u8  choice = 0;       //ѡ����

    if (dattyp_exist)  //bufͷ�а�����������
    {
        u8  val_type = *pBuf++;
        u16 val_len  = *pBuf++;
        switch (val_type)
        {
            case (DTYPE_NONE):
            {
                encap_size = 1;
                break;
            }
            case (DTYPE_BOOLEAN) :
            case (DTYPE_ENUM):
            case (DTYPE_INT8):
            case (DTYPE_UINT8):
            {
                encap_size = 2;
                break;
            }
            case (DTYPE_INT16):
            case (DTYPE_UINT16):
            {
                encap_size = 3;
                break;
            }
            case (DTYPE_INT32):
            case (DTYPE_UINT32):
            case (DTYPE_FLOAT32): //��������������һ�����ĸ��ֽ�����д��
            {
                encap_size = 5;
                break;
            }
            case (DTYPE_INT64):
            case (DTYPE_UINT64):
            case (DTYPE_FLOAT64): //��������������һ���Ѱ˸��ֽ�����д��
            {
                encap_size = 9;
                break;
            }

            case (DTYPE_DATETIME): //DL698AL_DATA_TYPE_DATETIME
            {
                encap_size = 11;
                break;
            }

            case (DTYPE_DATETIME_S): //DL698AL_DATA_TYPE_DATETIME_S
            {
                encap_size = 8;
                break;
            }

            case (DTYPE_DATE): //DL698AL_DATA_TYPE_DATE
            {
                encap_size = 6;
                break;
            }

            case (DTYPE_TIME):  //DL698AL_DATA_TYPE_TIME
            {
                encap_size = 4;
                break;
            }

            case (DTYPE_BITSTRING) :
            {
                //�ݲ�֧�֣�ò��Ҳ�ò���֧�֣��Ǿͱ�����
                //BIT STRING ��BER��������� �� T L V ,L��ʾV���ֽ�������V�������ǰ��Ҫ����һ��octet����ʾ���һ���ֽ�����bit������û���õ�bit����
                //�����0����1���û�������
                encap_size = 2 + val_len / 8;  //encap_size = 2 + val_len;  modified by wj
                break;
            }
            case (DTYPE_STRING) :
            case (DTYPE_OCT_STR):
            {
                //ASCII���ַ���
                //encap_size = 2 + val_len;
                pBuf--;
                encap_size = fnDL698AL_asn1_get_ObjCnt(&val_len, pBuf);
                encap_size += val_len + 1;
                break;
            }
            case (DTYPE_OI) :
            {
                encap_size = 3;
                break;
            }
            case (DTYPE_OAD) :
            {
                encap_size = 5; // 4;   //1+4,modified by wj
                break;
            }
            case (DTYPE_ROAD) :
            {
                encap_size = 5; // 4;   //1+4,modified by wj
                pBuf += 3;             //add by wj
                seqnum = *pBuf++;
                encap_size += 1;       //seqnum
                encap_size += seqnum * 4;
                break;
            }
            case (DTYPE_OMD) :
            {
                encap_size = 5;  // 4;   //1+4, modified by wj
                break;
            }
            case (DTYPE_TI) :
            {
                encap_size = 4; // 5;   // 1+3, modified by wj 1+3
                break;
            }
            case (DTYPE_TSA) :
            {
                encap_size = 2 + val_len;
                break;
            }
            case (DTYPE_MAC) :
            {
                //encap_size = 2 + val_len;
                encap_size = 1 + val_len;
                break;
            }
            case (DTYPE_RN) :
            {
                encap_size = 2 + val_len;
                break;
            }
            case (DTYPE_SCAUNIT) :
            {
                encap_size = 3;  //5; //1+4+1, modified by wj
                break;
            }
            case (DTYPE_CSD) :
            {
                pBuf--;     //ָ��CSD��������֮���һ���ֽ�
                choice = *pBuf++;
                encap_size = 2;   //csd type + choice
                if (choice == 0)   //OAD
                {
                    encap_size += 4;
                }
                else if (choice == 1)   //ROAD
                {
                    encap_size += 4; // 4;   //modified by wj
                    pBuf += 4;             //add by wj
                    seqnum = *pBuf++;
                    encap_size += 1;       //seqnum
                    encap_size += seqnum * 4;
                }
                break;
            }
            case (DTYPE_MS) :
            {
                break;
            }
            case (DTYPE_SID) :
            {
                encap_size += 5;     // 4, U32, modified by wj
                pBuf += 3;
                ret = *pBuf++;
                encap_size += ret + 1;     //�������ݳ���
                break;
            }
            case (DTYPE_SID_MAC) :
            {
                encap_size = 5;     // SID_MAC type
                pBuf += 3;
                //�õ�SID�򳤶�
                ret = *pBuf++;
                encap_size += ret + 1;     //�������ݳ���

                pBuf += ret;        //ָ��ָ��MAC��

                //�õ�MAC�򳤶�
                ret =  *pBuf++;
                pBuf += ret;        //ָ��ָ��MAC��
                encap_size += ret + 1;
                break;
            }

            case (DTYPE_RCSD) :
            {
                encap_size = 1;     // RCSD type
                pBuf++;
                seqnum = *pBuf++;   //num of CSD
                encap_size++;       //num of CSD
                //�õ�CSD�򳤶�
                for (k = 0; k < seqnum; k++)
                {
                    choice = *pBuf++;
                    encap_size += 1;   //csd type + choice
                    if (choice == 0)   //OAD
                    {
                        encap_size += 4;
                    }
                    else if (choice == 1)   //ROAD
                    {
                        encap_size += 4; // 4;   //modified by wj
                        pBuf += 4;             //add by wj
                        seqnum = *pBuf++;
                        encap_size += 1;       //seqnum
                        encap_size += seqnum * 4;
                    }
                }
                break;
            }
            case (DTYPE_COMDCB) :
            {
                encap_size = 6;
                break;
            }
            default :
            {
                //��֧�ֵ�����
                break;
            }
        }
    }
    else      //buf�в������������ͣ���ʱ�迿ָ���������������������ݳ���,��Ҫ����Record
    {
        u16 val_len  = *pBuf++;
        switch (datatype)
        {
            case (DTYPE_BOOLEAN) :
            case (DTYPE_ENUM):
            case (DTYPE_INT8):
            case (DTYPE_UINT8):
            {
                encap_size = 1;
                break;
            }
            case (DTYPE_INT16):
            case (DTYPE_UINT16):
            {
                encap_size = 2;
                break;
            }
            case (DTYPE_INT32):
            case (DTYPE_UINT32):
            case (DTYPE_FLOAT32): //��������������һ�����ĸ��ֽ�����д��
            {
                encap_size = 4;
                break;
            }
            case (DTYPE_INT64):
            case (DTYPE_UINT64):
            case (DTYPE_FLOAT64): //��������������һ���Ѱ˸��ֽ�����д��
            {
                encap_size = 8;
                break;
            }
            case (DTYPE_DATETIME): //DL698AL_DATA_TYPE_DATETIME
            {
                encap_size = 10;
                break;
            }

            case (DTYPE_DATETIME_S): //DL698AL_DATA_TYPE_DATETIME_S
            {
                encap_size = 7;
                break;
            }

            case (DTYPE_DATE): //DL698AL_DATA_TYPE_DATE
            {
                encap_size = 5;
                break;
            }

            case (DTYPE_TIME):  //DL698AL_DATA_TYPE_TIME
            {
                encap_size = 3;
                break;
            }
            case (DTYPE_BITSTRING) :
            {
                //�ݲ�֧�֣�ò��Ҳ�ò���֧�֣��Ǿͱ�����
                //BIT STRING ��BER��������� �� T L V ,L��ʾV���ֽ�������V�������ǰ��Ҫ����һ��octet����ʾ���һ���ֽ�����bit������û���õ�bit����
                //�����0����1���û�������
                encap_size = 1 + val_len / 8;
                break;
            }
            case (DTYPE_STRING) :
            case (DTYPE_OCT_STR):
            {
                //ASCII���ַ���
                //encap_size = 1 + val_len;
                pBuf--;
                encap_size = fnDL698AL_asn1_get_ObjCnt(&val_len, pBuf);
                encap_size += val_len;
                break;
            }
            case (DTYPE_OI) :
            {
                encap_size = 2;
                break;
            }
            case (DTYPE_OAD) :
            {
                encap_size = 4;   // 1+4,modified by wj
                break;
            }
            case (DTYPE_ROAD) :
            {
                encap_size = 4;   // 1+4,modified by wj
                pBuf += 3;             //add by wj
                seqnum = *pBuf++;
                encap_size += seqnum * 4;
                break;
            }
            case (DTYPE_OMD) :
            {
                encap_size = 4;   //modified by wj
                break;
            }
            case (DTYPE_TI) :
            {
                encap_size = 3;   //modified by wj 1+3
                break;
            }
            case (DTYPE_TSA) :
            {
                encap_size = 1 + val_len;
                break;
            }
            case (DTYPE_MAC) :
            {
                encap_size = 1 + val_len;
                break;
            }
            case (DTYPE_RN) :
            {
                encap_size = 1 + val_len;
                break;
            }
            case (DTYPE_REGION) :
            {
                break;
            }
            case (DTYPE_SCAUNIT) :
            {
                encap_size = 2; // 4+1, modified by wj
                break;
            }
            case (DTYPE_CSD) :
            {
                pBuf--;     //ָ��CSD��������֮���һ���ֽ�
                choice = *pBuf++;
                encap_size = 1;   //csd type + choice
                if (choice == 0)   //OAD
                {
                    encap_size += 4;
                }
                else if (choice == 1)   //ROAD
                {
                    encap_size += 4; // 4;   //modified by wj
                    pBuf += 4;             //add by wj
                    seqnum = *pBuf++;
                    encap_size += 1;       //seqnum
                    encap_size += seqnum * 4;
                }
                break;
            }
            case (DTYPE_MS) :
            {
                break;
            }

            case (DTYPE_COMDCB) :
            {
                encap_size = 5;
                break;
            }
            default :
            {
                //��֧�ֵ�����
                break;
            }
        }
    }

    return encap_size;
}

/*********************************************************************
* @fn      fnDl698AL_GetArrayData_Len
*
* @brief   ��ȡ���ݳ���(���ݼ��ṹ�����ͣ����֧��3��,����3�㷵��APDU�޷�����)
*
* @param   pBuf          ������buf
*          dattyp_exist  ָʾ������buf��ͷ���Ƿ�����������ͣ����ϵ�����ص����ݳ���
*                        0Ϊ���������ͣ�1Ϊ�����ݳ���
*          datatype      ָ��һ���������ͣ�����dattyp_existΪ0ʱ�Ż�鿴datatype���Ҵ�
*                        datatypeһ���ֽڲ����뷵�س�����
*
* @return  ���ػ�ȡ�������ݳ���
*/

//���ݲ��������ͺͳ��Ȼ�ȡASN.1 BER��װ�ĳ���
//���type�ǹ̶����ȵ�type�������len������
//���type�ǿɱ䳤�ȵ�type����ʹ��len������Ϊ�������ݵĳ��ȡ�
u16 fnDl698AL_GetArrayData_Len(u8 dattyp_exist, u8 datatype, u8* pBuf)
{
    u8  val_type1 ;
    u16 val_len1, val_len2, val_len3, encap_size = 0, ret;
    u8  i = 0, j, k;

    val_type1 = *pBuf;
    if ((val_type1 == DTYPE_ARRAY) || (val_type1 == DTYPE_STRUCTURE))
    {
        pBuf++;
        val_len1  = *pBuf++;
        encap_size = 2;
        for (i = 0; i < val_len1; i++)    //val_lenΪarray����Ԫ����Ŀ
        {
            if ((*pBuf == DTYPE_ARRAY) || (*pBuf == DTYPE_STRUCTURE))
            {
                pBuf++;
                val_len2 = *pBuf++;
                encap_size += 2;

                for (j = 0; j < val_len2; j++)
                {
                    if (*pBuf == DTYPE_STRUCTURE)
                    {
                        pBuf++;
                        val_len3 = *pBuf++;
                        encap_size += 2;
                        for (k = 0; k < val_len3; k++)
                        {
                            ret = fnDl698AL_GetSimpleData_Len(1, 0, pBuf);
                            encap_size += ret;
                            pBuf += ret;
                        }
                    }
                    else
                    {
                        ret = fnDl698AL_GetSimpleData_Len(1, 0, pBuf);
                        encap_size += ret;
                        pBuf += ret;
                    }
                }
            }
            else
            {
                ret = fnDl698AL_GetSimpleData_Len(1, 0, pBuf);
                encap_size += ret;
                pBuf += ret;
            }
        }
    }
    return encap_size;
}

/*********************************************************************
* @fn      fnDl698AL_GetData_Len
*
* @brief   ��ȡ�����������ݳ���  (������������)
*
* @param   pBuf          ������buf
*          dattyp_exist  ָʾ������buf��ͷ���Ƿ�����������ͣ����ϵ�����ص����ݳ���
*                        0Ϊ���������ͣ�1Ϊ�����ݳ���
*          datatype      ָ��һ���������ͣ�����dattyp_existΪ0ʱ�Ż�鿴datatype���Ҵ�
*                        datatypeһ���ֽڲ����뷵�س�����
*
* @return  ���ػ�ȡ�������ݳ���
*/

//���ݲ��������ͺͳ��Ȼ�ȡASN.1 BER��װ�ĳ���
//���type�ǹ̶����ȵ�type�������len������
//���type�ǿɱ䳤�ȵ�type����ʹ��len������Ϊ�������ݵĳ��ȡ�
u16 fnDl698AL_GetData_Len(u8 dattyp_exist, u8 datatype, u8* pBuf)
{
    u16 encap_size = 0;
    //    u16 offset = 0xFFFF;
    u16 ret = 0xFFFF;
    u8  seqnum = 0;
    u8  selpar = 0;
    u32 i ;
    //    u8  j = 0 , k ,ii;

    u8  val_type ;
    //  u16 val_len , val_len2 , val_len3 ;

    //  u8  choice = 0;       //ѡ����

    if (dattyp_exist)  //bufͷ�а�����������
    {
        val_type = *pBuf;
        switch (val_type)
        {
            case (DTYPE_RSD) :
            {
                // selpar = *pBuf++;    //���ָ��ָ������?����
                pBuf++;
                selpar = *pBuf++;
                switch (selpar)
                {
                    case (0):
                    {
                        //NULL
                        encap_size = 2;  //type + selector + data
                        break;
                    }
                    case (1):
                    {
                        //Selector1
                        encap_size = 2 + 4; //�ǲ���1+1+4ѽ
                        pBuf += 4;

                        ret = fnDl698AL_GetArrayData_Len(1, 0, pBuf);
                        if (ret == 0)
                        {
                            ret = fnDl698AL_GetSimpleData_Len(1, 0, pBuf);
                        }

                        encap_size += ret;
                        break;
                    }
                    case (2):
                    {
                        //Selector2
                        encap_size = 2 + 4; // 1+1+4
                        pBuf += 4;

                        //��ʼֵData
                        ret = fnDl698AL_GetArrayData_Len(1, 0, pBuf);
                        if (ret == 0)
                        {
                            ret = fnDl698AL_GetSimpleData_Len(1, 0, pBuf);
                        }
                        encap_size += ret;

                        //����ֵData
                        pBuf += ret;   //add by wj
                        ret = fnDl698AL_GetArrayData_Len(1, 0, pBuf);
                        if (ret == 0)
                        {
                            ret = fnDl698AL_GetSimpleData_Len(1, 0, pBuf);
                        }
                        encap_size += ret;

                        //���ݼ��Data
                        pBuf += ret;  //add by wj
                        ret = fnDl698AL_GetArrayData_Len(1, 0, pBuf);
                        if (ret == 0)
                        {
                            ret = fnDl698AL_GetSimpleData_Len(1, 0, pBuf);
                        }
                        encap_size += ret;
                        break;
                    }
                    case (3):
                    {
                        //Selector3
                        seqnum = *pBuf++;
                        encap_size = 3;   //type + selector + seqnum

                        for (i = 0; i < seqnum; i++)
                        {
                            pBuf += 4;
                            encap_size += 4;   //OAD
                            //��ʼֵ
                            ret = fnDl698AL_GetArrayData_Len(1, 0, pBuf);
                            if (ret == 0)
                            {
                                ret = fnDl698AL_GetSimpleData_Len(1, 0, pBuf);
                            }
                            encap_size += ret;
                            //����ֵ
                            pBuf += ret;  //add by wj
                            ret = fnDl698AL_GetArrayData_Len(1, 0, pBuf);
                            if (ret == 0)
                            {
                                ret = fnDl698AL_GetSimpleData_Len(1, 0, pBuf);
                            }
                            encap_size += ret;
                            //���ݼ��
                            pBuf += ret;  //add by wj
                            ret = fnDl698AL_GetArrayData_Len(1, 0, pBuf);
                            if (ret == 0)
                            {
                                ret = fnDl698AL_GetSimpleData_Len(1, 0, pBuf);
                            }
                            encap_size += ret;
                        }
                        break;
                    }

                    case (9):
                    {
                        //Selector9
                        encap_size = 3; //+2;
                        break;
                    }
                    default:
                        break;
                }
                break;
            }
            default :
            {
                ret = fnDl698AL_GetArrayData_Len(1, 0, pBuf);
                if (ret == 0)
                {
                    ret = fnDl698AL_GetSimpleData_Len(1, 0, pBuf);
                }
                encap_size += ret;
                break;
            }
        }
    }
    else      //buf�в������������ͣ���ʱ�迿ָ���������������������ݳ���,��Ҫ����Record
    {
        switch (datatype)
        {
            case (DTYPE_RSD) :
            {
                selpar = *pBuf++;
                switch (selpar)
                {
                    case (0):
                    {
                        //NULL
                        encap_size = 1;  //selector + data
                        break;
                    }
                    case (1):
                    {
                        //Selector1
                        encap_size = 1 + 4; //�ǲ���1+4ѽ
                        pBuf += 4;
                        ret = fnDl698AL_GetArrayData_Len(1, 0, pBuf);
                        if (ret == 0)
                        {
                            ret = fnDl698AL_GetSimpleData_Len(1, 0, pBuf);
                        }
                        encap_size += ret;
                        break;
                    }
                    case (2):
                    {
                        //Selector2
                        encap_size = 1 + 4; // 1+4
                        pBuf += 4;
                        //��ʼֵData
                        ret = fnDl698AL_GetArrayData_Len(1, 0, pBuf);
                        if (ret == 0)
                        {
                            ret = fnDl698AL_GetSimpleData_Len(1, 0, pBuf);
                        }
                        encap_size += ret;
                        //����ֵData
                        pBuf += ret;   //add by wj
                        ret = fnDl698AL_GetArrayData_Len(1, 0, pBuf);
                        if (ret == 0)
                        {
                            ret = fnDl698AL_GetSimpleData_Len(1, 0, pBuf);
                        }
                        encap_size += ret;
                        //���ݼ��Data
                        pBuf += ret;  //add by wj
                        ret = fnDl698AL_GetArrayData_Len(1, 0, pBuf);
                        if (ret == 0)
                        {
                            ret = fnDl698AL_GetSimpleData_Len(1, 0, pBuf);
                        }
                        encap_size += ret;
                        break;
                    }
                    case (3):
                    {
                        //Selector3
                        seqnum = *pBuf++;
                        encap_size = 2;   //selector + seqnum

                        for (i = 0; i < seqnum; i++)
                        {
                            pBuf += 4;
                            encap_size += 4;   //OAD
                            //��ʼֵ
                            ret = fnDl698AL_GetArrayData_Len(1, 0, pBuf);
                            if (ret == 0)
                            {
                                ret = fnDl698AL_GetSimpleData_Len(1, 0, pBuf);
                            }
                            encap_size += ret;
                            //����ֵ
                            pBuf += ret;  //add by wj
                            ret = fnDl698AL_GetArrayData_Len(1, 0, pBuf);
                            if (ret == 0)
                            {
                                ret = fnDl698AL_GetSimpleData_Len(1, 0, pBuf);
                            }
                            encap_size += ret;
                            //���ݼ��
                            pBuf += ret;  //add by wj
                            ret = fnDl698AL_GetArrayData_Len(1, 0, pBuf);
                            if (ret == 0)
                            {
                                ret = fnDl698AL_GetSimpleData_Len(1, 0, pBuf);
                            }
                            encap_size += ret;
                        }
                        break;
                    }

                    case (9):
                    {
                        //Selector9
                        encap_size = 2;
                        break;
                    }

                    default:
                        break;
                }
                break;
            }
            case (DTYPE_SID) :
            {
                encap_size += 4;     // 4, U32
                pBuf += 4;
                ret = fnDl698AL_GetSimpleData_Len(0, DTYPE_OCT_STR, pBuf);
                encap_size += ret;     //�������ݳ���
                break;
            }
            case (DTYPE_SID_MAC) :
            {
                encap_size = 0;     // No SID_MAC type

                //�õ�SID�򳤶�
                ret = fnDl698AL_GetSimpleData_Len(0, DTYPE_SID, pBuf);
                pBuf += ret;        //ָ��ָ��MAC��
                encap_size += ret;
                //�õ�MAC�򳤶�
                ret = fnDl698AL_GetSimpleData_Len(0, DTYPE_SID, pBuf);
                pBuf += ret;        //ָ��ָ��MAC��
                encap_size += ret;
                break;
            }
            case (DTYPE_RCSD) :
            {
                encap_size = 0;     // No RCSD type

                seqnum = *pBuf++;   //num of CSD
                encap_size++;       //num of CSD
                //�õ�CSD�򳤶�
                for (i = 0; i < seqnum; i++)
                {
                    ret = fnDl698AL_GetSimpleData_Len(0, DTYPE_CSD, pBuf);
                    encap_size += ret;       //ÿ�μ���һ��CSD�ĳ���
                    pBuf += ret;
                }
                break;
            }
            default:
                break;
        }
    }

    return encap_size;
}

/*
u8 fnDl698_asn1_build_datatime_s(u8 *pDst,u8 year,u8 month,u8 day,u8 hour,u8 minute,u8 sec)
{
    u16 hex_year;
    u8 len;
    if(year == 0xFF)
    {
        hex_year = 0xFFFF;
    }
    else
    {
        hex_year = year + 0x07D0;
    }

    UINT8_TO_STREAM(pDst, DTYPE_DATETIME_S);
    UINT16_TO_STREAM(pDst, hex_year);
    UINT8_TO_STREAM(pDst, month);
    UINT8_TO_STREAM(pDst, day);
    UINT8_TO_STREAM(pDst, hour);
    UINT8_TO_STREAM(pDst, minute);
    UINT8_TO_STREAM(pDst, sec);
    len = 0x08;
    return len;
}

u8 fnDl698_asn1_build_date(u8 *pDst,u16 year,u8 month,u8 day,u8 week)
{
    u16 hex_year;
    u8 len;

    if(year==0xFFFF)
      hex_year = 0xFFFF;
    else
    hex_year = year + 0x07D0;

    UINT8_TO_STREAM(pDst, DTYPE_DATE);
    UINT16_TO_STREAM(pDst, year);
    UINT8_TO_STREAM(pDst, month);
    UINT8_TO_STREAM(pDst, day);
    UINT8_TO_STREAM(pDst, week);
    len = 6;
    return len;
}

u8 fnDl698_asn1_build_octstring(u8 *pDst,u8 *pSrc,u8 srclen)
{
    u8 len, i;
    UINT8_TO_STREAM(pDst, DTYPE_OCT_STR);
    UINT8_TO_STREAM(pDst, srclen);
    for(i = 0;i<srclen;i++ )
    {
        UINT8_TO_STREAM(pDst, *pSrc++);
    }
    len = srclen + 2;
    return len;
}

u8 fnDl698_asn1_build_visiblestring(u8 *pDst,u8 *pSrc,u8 srclen)
{
    u8 len, i;
    UINT8_TO_STREAM(pDst, DTYPE_STRING);
    UINT8_TO_STREAM(pDst, srclen);
    for(i = 0;i<srclen;i++ )
    {
        UINT8_TO_STREAM(pDst, *pSrc++);
    }
    len = srclen + 2;
    return len;
}
*/
u8 fnDl698_asn1_build_bitstring(u8 *pDst, u8 *pSrc, u8 srclen)
{
    u8 len, i;
    UINT8_TO_STREAM(pDst, DTYPE_BITSTRING);
    UINT8_TO_STREAM(pDst, srclen * 8);
    for (i = 0; i < srclen; i++)
    {
        UINT8_TO_STREAM(pDst, *pSrc++);
    }
    len = srclen + 2;
    return len;
    /*
        //BIT STRING ��BER��������� �� T L V ,L��ʾV���ֽ�������V�������ǰ��Ҫ����һ��octet����ʾ���һ���ֽ�����bit������û���õ�bit����
        //�����0����1���û�������
        u32 temp;
        u8  len;
        u16 bitstring_byte = (srclen>>3) + ((srclen&0x7) ? 1 : 0);
        UINT8_TO_STREAM(pDst, DL698AL_DATA_TYPE_BITSTRING);
        *pDst++ = bitstring_byte+1;             //length
        *pDst++ =(srclen&0x7) ? (8 - (srclen&0x7)) : 0;         //���һ���ֽ�δʹ�õ�bit��
        for(temp=0;temp<bitstring_byte;temp++)
        {
            *pDst++ =*pSrc++;
        }
        len = bitstring_byte + 3;
        return len;
        */
}

/*
u8 fnDl698_asn1_build_structure(u8 *pDst,u8 data)
{
    u8 len;
   UINT8_TO_STREAM(pDst, DTYPE_STRUCTURE);
   UINT8_TO_STREAM(pDst, data);

    len = 2;
    return len;
}

u8 fnDl698_asn1_build_array(u8 *pDst,u8 data)
{
    u8 len;
   UINT8_TO_STREAM(pDst, DTYPE_ARRAY);
   UINT8_TO_STREAM(pDst, data);

    len = 2;
    return len;
}
*/
/*********************************************************************************************************
** Function name:    fnDl698_asn1_build_Type
** Descriptions:    �����ݷ�װ�ɶ�Ӧ��ʽ
** input parameters: src,Դ����, srclen, Դ���ݳ���;type,��������
** output parameters:   pDst, Ŀ������; Dstlen,Ŀ�������ۼӳ���
** Returned value: LenOffset,ָ��ƫ�Ƴ���
*********************************************************************************************************/
//------------���������������ͼ��������ɶ�Ӧ��ʽ--------------
u16 fnDl698_asn1_build_Type(u8 *pDst, u16 *Dstlen, u8 *pSrc, u16 *srclen, u8 type)
{
    u16 Len = 0, i ;

    switch (type)
    {
        case DTYPE_NONE:
            UINT8_TO_STREAM(pDst, DTYPE_NONE);
            Len = 0;
            break;

        case DTYPE_ARRAY:
        case DTYPE_STRUCTURE:
            UINT8_TO_STREAM(pDst, type);
            Len = 1;
            Std_Memcpy(pDst, pSrc, Len);
            break;

        case DTYPE_BOOLEAN:
        case DTYPE_ENUM:
        case DTYPE_REGION:
        case DTYPE_INT8:
        case DTYPE_UINT8:
            UINT8_TO_STREAM(pDst, type);
            Len = 1;
            Std_Memcpy(pDst, pSrc, Len);
            break;

        case DTYPE_INT16:
        case DTYPE_UINT16:
            UINT8_TO_STREAM(pDst, type);
            Len = 2;
            Std_MemRvs(pDst, pSrc, Len);
            break;

        case DTYPE_INT32:
        case DTYPE_UINT32:
            UINT8_TO_STREAM(pDst, type);
            Len = 4;
            Std_MemRvs(pDst, pSrc, Len);
            break;

        case DTYPE_INT64:
        case DTYPE_UINT64:
            UINT8_TO_STREAM(pDst, type);
            Len = 8;
            Std_MemRvs(pDst, pSrc, Len);
            break;

        case DTYPE_OCT_STR:
            UINT8_TO_STREAM(pDst, DTYPE_OCT_STR);
            if (*srclen < 128)
            {
                UINT8_TO_STREAM(pDst, *srclen);
            }
            else if (*srclen < 256)
            {
                UINT8_TO_STREAM(pDst, 0x81);
                UINT8_TO_STREAM(pDst, *srclen & 0xFF);
                Len += 1;
            }
            else
            {
                UINT8_TO_STREAM(pDst, 0x82);
                UINT8_TO_STREAM(pDst, *srclen >> 8);
                UINT8_TO_STREAM(pDst, *srclen & 0xFF);
                Len += 2;
            }

            Std_MemRvs(pDst, pSrc, *srclen);
            Len += *srclen + 1;
            break;

        case DTYPE_BITSTRING:
            UINT8_TO_STREAM(pDst, DTYPE_BITSTRING);
            u16 bitlen;
            bitlen = *srclen * 8;
            Len = 0;
            if (bitlen < 128)
            {
                UINT8_TO_STREAM(pDst, bitlen);
            }
            else if (bitlen < 256)
            {
                UINT8_TO_STREAM(pDst, 0x81);
                UINT8_TO_STREAM(pDst, bitlen);
                Len += 1;
            }
            else
            {
                UINT8_TO_STREAM(pDst, 0x82);
                UINT8_TO_STREAM(pDst, bitlen >> 8);
                UINT8_TO_STREAM(pDst, bitlen & 0xFF);
                Len += 2;
            }
            Std_Memcpy(pDst, pSrc, *srclen);

            for (i = 0; i < *srclen; i++)
            {
                Std_BitRvsSelf(pDst + i, pDst + i);
            }

            Len += *srclen + 1;
            break;

        case DTYPE_STRING:
            UINT8_TO_STREAM(pDst, DTYPE_STRING);
            if (*srclen < 128)
            {
                UINT8_TO_STREAM(pDst, *srclen);
            }
            else if (*srclen < 256)
            {
                UINT8_TO_STREAM(pDst, 0x81);
                UINT8_TO_STREAM(pDst, *srclen & 0xFF);
                Len += 1;
            }
            else
            {
                UINT8_TO_STREAM(pDst, 0x82);
                UINT8_TO_STREAM(pDst, *srclen >> 8);
                UINT8_TO_STREAM(pDst, *srclen & 0xFF);
                Len += 2;
            }

            for (i = 0; i < *srclen; i++)
            {
                UINT8_TO_STREAM(pDst, *pSrc++);
            }
            Len += *srclen + 1;
            break;

        case DTYPE_DATE:
            UINT8_TO_STREAM(pDst, DTYPE_DATE);
            Len = 5;
            Std_MemRvs(pDst, pSrc, Len);
            break;

        case DTYPE_DATETIME_S:
            UINT8_TO_STREAM(pDst, DTYPE_DATETIME_S);
            Len = 7;
            Std_MemRvs(pDst, pSrc, Len);
            break;

        case DTYPE_OI:
            UINT8_TO_STREAM(pDst, DTYPE_OI);
            Len = 2;
            Std_MemRvs(pDst, pSrc, Len);
            break;

        case DTYPE_OMD:
        case DTYPE_OAD:
            UINT8_TO_STREAM(pDst, type);
            Len = 4;
            Std_MemRvs(pDst, pSrc, Len);
            break;

        case DTYPE_RN:
            UINT8_TO_STREAM(pDst, DTYPE_RN);
            if (*srclen < 128)
            {
                UINT8_TO_STREAM(pDst, *srclen);
            }
            else if (*srclen < 256)
            {
                UINT8_TO_STREAM(pDst, 0x81);
                UINT8_TO_STREAM(pDst, *srclen & 0xFF);
                Len += 1;
            }
            else
            {
                UINT8_TO_STREAM(pDst, 0x82);
                UINT8_TO_STREAM(pDst, *srclen >> 8);
                UINT8_TO_STREAM(pDst, *srclen & 0xFF);
                Len += 2;
            }

            Std_Memcpy(pDst, pSrc, *srclen);
            Len += *srclen + 1;
            break;
        case DTYPE_CSD:
            UINT8_TO_STREAM(pDst, DTYPE_CSD);
            u8 temp;
            temp = *pSrc++;
            UINT8_TO_STREAM(pDst, temp);
            Len += 1 ;
            if (temp) //ROAD
            {
                Std_MemRvs(pDst, pSrc, 4);  //��OAD
                pDst += 4;
                pSrc += 4;
                Len += 4 ;

                temp = *pSrc++;  // OAD ����
                UINT8_TO_STREAM(pDst, temp);
                Len += 1 ;
                for (i = 0; i < temp; i++)
                {
                    Std_MemRvs(pDst, pSrc, 4);  //��OAD
                    pDst += 4;
                    pSrc += 4;
                    Len += 4 ;
                }
            }
            else
            {
                Std_MemRvs(pDst, pSrc, 4);
                Len += 4 ;
            }
            break;

        case DTYPE_COMDCB:
            UINT8_TO_STREAM(pDst, DTYPE_COMDCB);
            Len = 5;
            Std_Memcpy(pDst, pSrc, Len);
            break;

        default:
            Len = 0;
            break;
    }

    *Dstlen += Len + 1;

    return (Len + 1);
}

/*********************************************************************************************************
** Function name:    fnForm_build_Type
** Descriptions:    �����ݰ���ָ����type��װ,֧�ָ������ͷ�װ
** input parameters: src,Դ����(������), srclen, Դ���ݳ���;type,��������(������)
** output parameters:   pDst, Ŀ������; Dstlen,Ŀ�������ۼӳ���
** Returned value: LenOffset,ָ��ƫ�Ƴ���
*********************************************************************************************************/
//------------���������������ͼ��������ɶ�Ӧ��ʽ---��֧��С�ڵ���3�㸴�ӽṹ���ͷ�װ-----------
u16 fnForm_build_Type(u8 *pDst, u16 *Dstlen, u8 *pSrc, u16 *srclen, u8 *pType)
{
    u8  i = 0, j = 0, temp_type1 = 0xFF, temp_type2 = 0xFF, num1 = 1, num2 = 1;
    u16  LenOffset = 0, len = 0 ;

    if ((*pType == DTYPE_ARRAY) || (*pType == DTYPE_STRUCTURE))
    {
        temp_type1 = *pType++;
        num1 = *pType++;

        if ((*pType == DTYPE_ARRAY) || (*pType == DTYPE_STRUCTURE))
        {
            temp_type2 = *pType++;
            num2 = *pType++;
        }
    }

    if ((temp_type1 == DTYPE_ARRAY) || (temp_type1 == DTYPE_STRUCTURE))
    {
        UINT8_TO_STREAM(pDst, temp_type1);
        UINT8_TO_STREAM(pDst, num1);     //array,structure ����
        LenOffset += 2;

        for (i = 0; i < num1; i++)
        {
            if ((temp_type2 == DTYPE_ARRAY) || (temp_type2 == DTYPE_STRUCTURE))
            {
                UINT8_TO_STREAM(pDst, temp_type2);
                UINT8_TO_STREAM(pDst, num2);     //array,structure ����
                LenOffset += 2;
                for (j = 0; j < num2; j++)
                {
                    len = fnDl698_asn1_build_Type(pDst, NULL, pSrc, srclen, *(pType + j));
                    if (len)
                    {
                        LenOffset += len;
                        pDst += len;

                        if ((*(pType + j) == DTYPE_BITSTRING) || (*(pType + j) == DTYPE_STRING))
                        {
                            pSrc += *srclen;
                        }
                        else
                        {
                            pSrc += (len - 1);    //ָ��ƫ��
                        }
                    }
                }
            }
            else
            {
                len = fnDl698_asn1_build_Type(pDst, NULL, pSrc, srclen, *(pType + i));
                if (len)
                {
                    LenOffset += len;
                    pDst += len;

                    if ((*(pType + i) == DTYPE_BITSTRING) || (*(pType + i) == DTYPE_STRING))
                    {
                        pSrc += *srclen;
                    }
                    else
                    {
                        pSrc += (len - 1);    //ָ��ƫ��
                    }
                }
            }
        }
    }
    else
    {
        len = fnDl698_asn1_build_Type(pDst, NULL, pSrc, srclen, *pType);
        if (len)
        {
            LenOffset += len;
            pDst += len;
            if ((*pType == DTYPE_BITSTRING) || (*pType == DTYPE_STRING))
            {
                pSrc += *srclen;
            }
            else
            {
                pSrc += (len - 1);    //ָ��ƫ��
            }
        }
    }

    *Dstlen += LenOffset;

    return LenOffset;
}
