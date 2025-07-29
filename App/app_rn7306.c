/* �������������ļ����ο������ȴ��봦��
*/

#include <App.h>

static double err;
static double pgain;
static double e;
static unsigned long gain;

PARAMETER_STRUCT parameter; // ����

//BCDתhex
UINT32 bcdtohex(unsigned char *input, unsigned char size)
{
    long_union y;
    unsigned long z = 0;
    unsigned long m = 1;
    unsigned char n, k;
    k = size;
    y.long_type = 0;

    while (k--)
    {
        z = (*input) & 0x0f;
        y.long_type += (z * m);
        m *= 10;
        n = (*input) & 0xf0;
        n = (n >> 4) | (n << 4);
        z = n;
        y.long_type += (z * m);
        m *= 10;
        input++;
    }

    return y.long_type;
}

//�������
double math_error(unsigned char *buf)
{
    unsigned char fu;

    if (buf[2] & 0x80)
    {
        fu = 1;
    }
    else
    {
        fu = 0;
    }

    buf[2] &= 0x7f;
    gain = bcdtohex(&buf[0], 3);    //xx.xxxx %
    err = (double)gain;
    err /= 1000000;

    if (fu)
    {
        err = 0 - err;
    }

    return err;
}

//GAINת�ǲ����
double phs_gain_to_err(UINT32 gain)
{
    UINT8 flag = 0;
    gain &= 0xffff;

    if (gain >= 32768)
    {
        gain = 65536 - gain;
        flag = 1;
    }

    pgain = (double)gain / 32768;

    if (flag)
    {
        pgain = 0 - pgain;
    }

    pgain = (0 - pgain) * 1.7320508075689;
    return pgain;
}

//�ǲ����תGAIN
UINT32 phs_err_to_gain(double err)
{
    err = (0 - err) / (1.7320508075689);
    err *= 32768;

    if (err < 0)
    {
        err += 65536;
    }

    return (UINT32)err;
}

// дʹ��
VOID rn7306_write_enable()
{
    sDataComm_TypeDef      EmuCommbuf;

    EmuCommbuf.ucTemp8 = RN8302_WREN_EN; // дʹ��λ
    fnRN8302_Write(RN8302_WREN, EmuCommbuf.ucTempBuf, 1);
    //fnRN8302_Write(RN8302_WREN2, EmuCommbuf.ucTempBuf, 1);
}

// д����
VOID rn7306_write_disable()
{
    sDataComm_TypeDef      EmuCommbuf;

    //д����
    EmuCommbuf.ucTemp8 = RN8302_WREN_DIS; // дʹ��λ
    fnRN8302_Write(RN8302_WREN, EmuCommbuf.ucTempBuf, 1);
}

//����0.5L�¹�����λ���ǲ����
void rn7306_cail_fine_phs_error_xiebo(UINT8 *buf, UINT8 interval)
{
    UINT32 addr;
    UINT8 phase;
    double err_buf;
    unsigned long tmp_u32 = 0;

    //if (meter_data.rn8302_hard.cail_load != 0xaa)
    {
        //return;
    }

    //����RN8302�İ汾��
    //meter_data.spi_cm.int_type = DeviceID;
    //SPIRead();

    //if (meter_data.spi_data.long_type != 0x830200)
    {
        //return;
    }

    #if 0
    if (interval == 0) //�Ͷ�
    {
        db_write_ee(offsetof(METER_EE_STRUCT, run_ee.xiebo_err[0]), &buf[0], 3);
    }
    else  //�߶�
    {
        db_write_ee(offsetof(METER_EE_STRUCT, run_ee.xiebo_err[1]), &buf[0], 3);
    }
    #endif

    //дʹ��
    rn7306_write_enable();
    err_buf = math_error(&buf[0]);

    for (phase = 0; phase < 3; phase++)
    {
        err = err_buf;

        //�ж�Ӧ��������Ĵ�����������
        // ����MeasureRms.PubData.I[i]���ж��ڵ͡��С�������
        if (interval == 0)  //(meter_data.rn8302_hard.current_range1 == 0)   // dyf�зֶ�
        {
            if (phase == 0)
            {
                //addr = RN8302_PA_PHSL;
                addr = RN8302_PA_PHSM;
            }
            else if (phase == 1)
            {
                //addr = RN8302_PB_PHSL;
                addr = RN8302_PB_PHSM;
            }
            else
            {
                //addr = RN8302_PC_PHSL;
                addr = RN8302_PC_PHSM;
            }
        }
        else
        {
            if (phase == 0)
            {
                addr = RN8302_PA_PHSH;
            }
            else if (phase == 1)
            {
                addr = RN8302_PB_PHSH;
            }
            else
            {
                addr = RN8302_PC_PHSH;
            }
        }

        //�ǲ�
        fnRN8302_Read(addr, (u8 *)&tmp_u32, 3);
        gain = tmp_u32;
        e = phs_gain_to_err(gain);
        err = e + err + (e * err);
        gain = phs_err_to_gain(err);
        tmp_u32 = gain;                           //����ԭ��ֵ
        tmp_u32 &= 0xffff;                        //���θ�λ

        if (interval == 0) //�Ͷ�
        {
            fnFile_Write(FileId_FirmPara, FileItemInfoOffAddr_Xiebo_Value + phase * 4, (u8 *)&tmp_u32, 4);
        }
        else  //�߶�
        {
            fnFile_Write(FileId_FirmPara, FileItemInfoOffAddr_Xiebo_Value + 12 + phase * 4, (u8 *)&tmp_u32, 4);
        }
    }
}

// ����ֱ��ż��г���������ܵ�У����Ƿ�һ��
s8 check_rn7306_checksum(u32 ic_checksum)
{
    u32 sum = 0;
    s8 i = 0;

    for (i = 0; i < nPhs; i++)
    {
        sum += MeasureFirmPara.P_PHS[i];
        sum += MeasureFirmPara.Q_PHS[i];
    }
    for (i = 0; i < 6; i++)
    {
        sum += MeasureFirmPara.P_PHSMH[i];
        sum += MeasureFirmPara.Q_PHSMH[i];
    }
    if (((~ic_checksum - parameter.xiebo_new_regsum) & 0xFFFFFF) == ((~MeasureFirmPara.ChkSum1 - sum) & 0xFFFFFF))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

//���RN7306�Ĵ��������ݣ��Ƿ��RAM��һ��
INT8 check_rn7306_reg(void)
{
    long_union check_data;  //, compare_data;
    long_union spi_data;
    UINT8 j; // i
    UINT32 sum;
    UINT32 quanbo_i[3], jibo_i[3], err_i[3];
    UINT32 quanbo_p[3], jibo_p[3], err_p[3];
    UINT32 xiebo_mid_current;

    //20180117 ���üĴ���WMSW�ϵ縴λ��ֵΪ0x03�������0x03����ô����װ�ؼĴ���
    //meter_data.spi_cm.int_type = WMSW;
    //SPIRead();

    //if (meter_data.spi_data.long_type == 0x03)
    {
        //return -1;
    }

    fnRN8302_Read(RN8302_DeviceID, (u8 *)spi_data.char_type, 3) ;

    //дʹ��
    rn7306_write_enable();
    //�˶����Ĵ��� ���ݵ�ѹ������ͬ�ļĴ���
    sum = 0;

    //ֱ��ż��г���������ش�ʱ������ȫ�����������������ȫ������������������
    if (parameter.xiebo_flag != 0x5A)
    {
        j = 0;
        while (j < 3)
        {
            fnRN8302_Read(RN8302_IA + j, (u8 *)&MeasureRegTmp.Irms[j], 4) ;
            quanbo_i[j] = (u32)(100 * (float)MeasureRegTmp.Irms[j] / (MeasureFirmPara.KIArms) + 0.5);

            //if (quanbo_i[j] <= meter_data.rn8302_hard.zero_current)
            {
                //quanbo_i[j] = 0;
            }

            fnRN8302_Read(RN8302_FIA + j, (u8 *)&MeasureRegTmp.FIrms[j], 4);
            jibo_i[j] = (u32)(100 * (float)MeasureRegTmp.FIrms[j] / (MeasureFirmPara.KIArms) + 0.5);

            //if (jibo_i[j] <= meter_data.rn8302_hard.zero_current)
            {
                //jibo_i[j] = 0;
            }

            if (jibo_i[j] != 0)
            {
                if (quanbo_i[j] > jibo_i[j])
                {
                    err_i[j] = (quanbo_i[j] - jibo_i[j]) * 100 / jibo_i[j];
                }
                else
                {
                    err_i[j] = 0;
                }
            }
            else
            {
                err_i[j] = 0;
            }

            MeasureRegTmp.Pw[j] = 0 ;
            fnRN8302_Read(RN8302_PA + j, (u8 *)&MeasureRegTmp.Pw[j], 4);
            quanbo_p[j] = (s32)(1000 * (float)(MeasureRegTmp.Pw[j]) / (((s32)MeasureFirmPara.KPrms))); //�����Pa Pb Pc������Qa Qb Qc��

            //if (quanbo_p[j] <= meter_data.rn8302_hard.zero_moment_power)
            {
                //quanbo_p[j] = 0;
            }

            MeasureRegTmp.FPw[j] = 0 ;
            fnRN8302_Read(RN8302_FPA + j, (u8 *)&MeasureRegTmp.FPw[j], 4);
            jibo_p[j] = (s32)(1000 * (float)(MeasureRegTmp.Pw[j]) / (((s32)MeasureFirmPara.KPrms))); //�����Pa Pb Pc������Qa Qb Qc��

            //if (jibo_p[j] <= meter_data.rn8302_hard.zero_moment_power)
            {
                //jibo_p[j] = 0;
            }

            if (jibo_p[j] != 0)
            {
                if (quanbo_p[j] > jibo_p[j])
                {
                    err_p[j] = (quanbo_p[j] - jibo_p[j]) * 100 / jibo_p[j];
                }
                else
                {
                    err_p[j] = (jibo_p[j] - quanbo_p[j]) * 100 / jibo_p[j];
                }
            }
            else
            {
                err_p[j] = 1;
            }

            j++;
        }
    }

    j = 0;
    while (j < 3)
    {
        if (parameter.xiebo_flag != 0x5A)  //ֱ��ż��г���������ش�
        {
            //ȫ��������������������5%-15%֮�� ���� ȫ������������������С��1% ���� ����������0.35-0.6�����0.85�����ù�����λ�����в���
            if ((err_i[0] > 4) && (err_i[1] > 4) && (err_i[2] > 4) && (err_i[0] < 16) && (err_i[1] < 16) && (err_i[2] < 16)
                && (err_p[0] < 1) && (err_p[1] < 1) && (err_p[2] < 1))
                //if (1) // dyf test
            {
                fnFile_Read(FileId_FirmPara, FileItemInfoOffAddr_Xiebo_Mid_Current, (u8 *)&xiebo_mid_current, 4);

                if (MeasureRms.PubData.I[j] < xiebo_mid_current * 10) //�Ͷ�
                {
                    fnFile_Read(FileId_FirmPara, FileItemInfoOffAddr_Xiebo_Value + j * 4, (u8 *)check_data.char_type, 4);
                }
                else  //�߶�
                {
                    fnFile_Read(FileId_FirmPara, FileItemInfoOffAddr_Xiebo_Value + 12 + j * 4, (u8 *)check_data.char_type, 4);
                }

                fnRN8302_Read(RN8302_PA_PHSL + j, (u8 *)spi_data.char_type, 2);
                if ((spi_data.long_type & 0xFFFF) != check_data.long_type)
                {
                    fnRN8302_Write(RN8302_PA_PHSL + j, (u8 *)check_data.char_type, 2);
                    fnRN8302_Read(RN8302_PA_PHSL + j, (u8 *)spi_data.char_type, 2); // �Լ��
                }

                sum += check_data.long_type & 0xFFFF;

                fnRN8302_Read(RN8302_PA_PHSM + j * 2, (u8 *)spi_data.char_type, 3);
                if ((spi_data.long_type & 0xFFFFFF) != check_data.long_type)
                {
                    fnRN8302_Write(RN8302_PA_PHSM + j * 2, (u8 *)check_data.char_type, 3);
                }

                sum += check_data.long_type & 0xFFFFFF;

                fnRN8302_Read(RN8302_PA_PHSH + j * 2, (u8 *)spi_data.char_type, 3);
                if ((spi_data.long_type & 0xFFFFFF) != check_data.long_type)
                {
                    fnRN8302_Write(RN8302_PA_PHSH + j * 2, (u8 *)check_data.char_type, 3);
                }

                sum += check_data.long_type & 0xFFFFFF;

                fnRN8302_Read(RN8302_QA_PHSL + j, (u8 *)spi_data.char_type, 2);
                if ((spi_data.long_type & 0xFFFF) != check_data.long_type)
                {
                    fnRN8302_Write(RN8302_QA_PHSL + j, (u8 *)check_data.char_type, 2);
                }

                sum += check_data.long_type & 0xFFFF;

                fnRN8302_Read(RN8302_QA_PHSM + j * 2, (u8 *)spi_data.char_type, 3);
                if ((spi_data.long_type & 0xFFFFFF) != check_data.long_type)
                {
                    fnRN8302_Write(RN8302_QA_PHSM + j * 2, (u8 *)check_data.char_type, 3);
                }

                sum += check_data.long_type & 0xFFFFFF;

                fnRN8302_Read(RN8302_QA_PHSH + j * 2, (u8 *)spi_data.char_type, 3);
                if ((spi_data.long_type & 0xFFFFFF) != check_data.long_type)
                {
                    fnRN8302_Write(RN8302_QA_PHSH + j * 2, (u8 *)check_data.char_type, 3);
                }

                sum += check_data.long_type & 0xFFFFFF;

                fnRN8302_Read(RN8302_FPA_PHS + j, (u8 *)spi_data.char_type, 2);
                if ((spi_data.long_type & 0xFFFF) != check_data.long_type)
                {
                    fnRN8302_Write(RN8302_FPA_PHS + j, (u8 *)check_data.char_type, 2);
                }

                sum += check_data.long_type & 0xFFFF;

                fnRN8302_Read(RN8302_FQA_PHS + j, (u8 *)spi_data.char_type, 2);
                if ((spi_data.long_type & 0xFFFF) != check_data.long_type)
                {
                    fnRN8302_Write(RN8302_FQA_PHS + j, (u8 *)check_data.char_type, 2);
                }

                sum += check_data.long_type & 0xFFFF;

                parameter.xiebo_new_regsum = sum;   // ���²��������ۼ�У���
            }
            else
            {
                fnRN8302_Read(RN8302_PA_PHSL + j, (u8 *)spi_data.char_type, 2);
                if ((spi_data.long_type & 0xFFFF) != MeasureFirmPara.P_PHS[j])
                {
                    fnRN8302_Write(RN8302_PA_PHSL + j, (u8 *)&MeasureFirmPara.P_PHS[j], 2);
                }
                fnRN8302_Read(RN8302_QA_PHSL + j, (u8 *)spi_data.char_type, 2);
                if ((spi_data.long_type & 0xFFFF) != MeasureFirmPara.Q_PHS[j])
                {
                    fnRN8302_Write(RN8302_QA_PHSL + j, (u8 *)&MeasureFirmPara.Q_PHS[j], 2);
                }
                fnRN8302_Read(RN8302_PA_PHSM + j * 2, (u8 *)spi_data.char_type, 3);
                if ((spi_data.long_type & 0xFFFFFF) != MeasureFirmPara.P_PHSMH[j * 2])
                {
                    fnRN8302_Write(RN8302_PA_PHSM + j * 2, (u8 *)&MeasureFirmPara.P_PHSMH[j * 2], 3);
                }
                fnRN8302_Read(RN8302_QA_PHSM + j * 2, (u8 *)spi_data.char_type, 3);
                if ((spi_data.long_type & 0xFFFFFF) != MeasureFirmPara.Q_PHSMH[j * 2])
                {
                    fnRN8302_Write(RN8302_QA_PHSM + j * 2, (u8 *)&MeasureFirmPara.Q_PHSMH[j * 2], 3);
                }
                fnRN8302_Read(RN8302_PA_PHSH + j * 2, (u8 *)spi_data.char_type, 3);
                if ((spi_data.long_type & 0xFFFFFF) != MeasureFirmPara.P_PHSMH[j * 2 + 1])
                {
                    fnRN8302_Write(RN8302_PA_PHSH + j * 2, (u8 *)&MeasureFirmPara.P_PHSMH[j * 2 + 1], 3);
                }
                fnRN8302_Read(RN8302_QA_PHSH + j * 2, (u8 *)spi_data.char_type, 3);
                if ((spi_data.long_type & 0xFFFFFF) != MeasureFirmPara.Q_PHSMH[j * 2 + 1])
                {
                    fnRN8302_Write(RN8302_QA_PHSH + j * 2, (u8 *)&MeasureFirmPara.Q_PHSMH[j * 2 + 1], 3);
                }

                // ����������д0����Ϊ������0��д����ֵ��Ӱ��У���
                fnRN8302_Read(RN8302_FPA_PHS + j, (u8 *)spi_data.char_type, 2);
                //if ((spi_data.long_type & 0xFFFF) != MeasureFirmPara.P_PHSMH[j * 2])
                check_data.long_type = 0x00;
                if ((spi_data.long_type & 0xFFFF) != check_data.long_type)
                {
                    //fnRN8302_Write(RN8302_FPA_PHS + j, (u8 *)&MeasureFirmPara.P_PHSMH[j * 2], 2);
                    fnRN8302_Write(RN8302_FPA_PHS + j, (u8 *)&check_data.long_type, 2);
                }
                fnRN8302_Read(RN8302_FQA_PHS + j, (u8 *)spi_data.char_type, 2);
                check_data.long_type = 0x00;
                if ((spi_data.long_type & 0xFFFF) != check_data.long_type)
                    //if ((spi_data.long_type & 0xFFFF) != MeasureFirmPara.Q_PHSMH[j * 2])
                {
                    //fnRN8302_Write(RN8302_FQA_PHS + j, (u8 *)&MeasureFirmPara.Q_PHSMH[j * 2], 2);
                    fnRN8302_Write(RN8302_FQA_PHS + j, (u8 *)&check_data.long_type, 2);
                }

                parameter.xiebo_new_regsum = 0;
            }
        }
        else
        {
            fnRN8302_Read(RN8302_PA_PHSL + j, (u8 *)spi_data.char_type, 2);
            if ((spi_data.long_type & 0xFFFF) != MeasureFirmPara.P_PHS[j])
            {
                fnRN8302_Write(RN8302_PA_PHSL + j, (u8 *)&MeasureFirmPara.P_PHS[j], 2);
            }
            fnRN8302_Read(RN8302_QA_PHSL + j, (u8 *)spi_data.char_type, 2);
            if ((spi_data.long_type & 0xFFFF) != MeasureFirmPara.Q_PHS[j])
            {
                fnRN8302_Write(RN8302_QA_PHSL + j, (u8 *)&MeasureFirmPara.Q_PHS[j], 2);
            }
            fnRN8302_Read(RN8302_PA_PHSM + j * 2, (u8 *)spi_data.char_type, 3);
            if ((spi_data.long_type & 0xFFFFFF) != MeasureFirmPara.P_PHSMH[j * 2])
            {
                fnRN8302_Write(RN8302_PA_PHSM + j * 2, (u8 *)&MeasureFirmPara.P_PHSMH[j * 2], 3);
            }
            fnRN8302_Read(RN8302_QA_PHSM + j * 2, (u8 *)spi_data.char_type, 3);
            if ((spi_data.long_type & 0xFFFFFF) != MeasureFirmPara.Q_PHSMH[j * 2])
            {
                fnRN8302_Write(RN8302_QA_PHSM + j * 2, (u8 *)&MeasureFirmPara.Q_PHSMH[j * 2], 3);
            }
            fnRN8302_Read(RN8302_PA_PHSH + j * 2, (u8 *)spi_data.char_type, 3);
            if ((spi_data.long_type & 0xFFFFFF) != MeasureFirmPara.P_PHSMH[j * 2 + 1])
            {
                fnRN8302_Write(RN8302_PA_PHSH + j * 2, (u8 *)&MeasureFirmPara.P_PHSMH[j * 2 + 1], 3);
            }
            fnRN8302_Read(RN8302_QA_PHSH + j * 2, (u8 *)spi_data.char_type, 3);
            if ((spi_data.long_type & 0xFFFFFF) != MeasureFirmPara.Q_PHSMH[j * 2 + 1])
            {
                fnRN8302_Write(RN8302_QA_PHSH + j * 2, (u8 *)&MeasureFirmPara.Q_PHSMH[j * 2 + 1], 3);
            }

            // ����������д0����Ϊ������0��д����ֵ��Ӱ��У���
            fnRN8302_Read(RN8302_FPA_PHS + j, (u8 *)spi_data.char_type, 2);
            //if ((spi_data.long_type & 0xFFFF) != MeasureFirmPara.P_PHSMH[j * 2])
            check_data.long_type = 0x00;
            if ((spi_data.long_type & 0xFFFF) != check_data.long_type)
            {
                //fnRN8302_Write(RN8302_FPA_PHS + j, (u8 *)&MeasureFirmPara.P_PHSMH[j * 2], 2);
                fnRN8302_Write(RN8302_FPA_PHS + j, (u8 *)&check_data.long_type, 2);
            }
            fnRN8302_Read(RN8302_FQA_PHS + j, (u8 *)spi_data.char_type, 2);
            check_data.long_type = 0x00;
            if ((spi_data.long_type & 0xFFFF) != check_data.long_type)
                //if ((spi_data.long_type & 0xFFFF) != MeasureFirmPara.Q_PHSMH[j * 2])
            {
                //fnRN8302_Write(RN8302_FQA_PHS + j, (u8 *)&MeasureFirmPara.Q_PHSMH[j * 2], 2);
                fnRN8302_Write(RN8302_FQA_PHS + j, (u8 *)&check_data.long_type, 2);
            }

            parameter.xiebo_new_regsum = 0;
        }

        j++;
    }

    //if (meter_data.rn8302_hard.cail_load != 0xaa)
    {
        //д����
        //rn7306_write_disable();
    }

    return 0;
}
