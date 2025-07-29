#ifndef _APP_RN7306_H
#define _APP_RN7306_H

//参数
typedef struct _PARAMETER_STRUCT
{
    UINT8   xiebo_flag;                                 // 直流偶次谐波误差补偿开关 0x5A-关闭，其它-打开
    UINT32  xiebo_err[2];                               // 需补偿误差值,0-当前电流小于谐波补偿中心点电流时误差值，其它-在当前电流大于等于谐波补偿中心点电流时误差值
    UINT32  xiebo_value[2][3];                          // 直流偶次谐波补偿后寄存器值,0-用于在当前电流小于谐波补偿中心点电流时补偿，其它-用于在当前电流大于等于谐波补偿中心点电流时补偿
    UINT32  xiebo_mid_current;                          // 谐波补偿中心点电流 xxx.xxx
    UINT32  xiebo_new_regsum;                           // 补偿参数新累加和
    //UINT8                                       halfimax_phs_flag;                           // 1/2 Imax角差补偿开关 0x5A-打开，其它-关闭
    //UINT8                                       start_power_flag;                            // 启动误差补偿开关 0x5A-打开，其它-关闭
} PARAMETER_STRUCT;

//联合结构类型
typedef union _long_union
{
    UINT8                                       char_type[4];
    UINT32                                      long_type;
} long_union;

extern PARAMETER_STRUCT parameter; // 参数

s8 check_rn7306_checksum(u32 ic_checksum);
extern INT8 check_rn7306_reg(void);

#endif // end _APP_RN7306_H
