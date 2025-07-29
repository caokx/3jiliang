/****************************************************************************
* @file
* @author   Renergy Application Team
* @version  V1.0.0
* @date     2021.06.10
* @brief
******************************************************************************
* @attention
*
*
****************************************************************************/

/* Includes ------------------------------------------------------------------*/

#include <CoreSupport.h>
#include <Rn8xxx_Common.h>

/* Private define ------------------------------------------------------------*/

/* Private enum -------------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private data ---------------------------------------------------------*/

/* Exported data ----------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/* Exported functions ----------------------------------------------------------*/
// dyf 29M 5000: 4.78ms
void SystemDelayUs(uint32_t i)
{
    if (((SYSCTL->OSC_CTRL1 >> 6) & 0x3) != 0x3) //¸ßÆµÄ£Ê½
    {
        for (; i > 0; i--)
        {
            __NOP();
            __NOP();
            __NOP();
            __NOP();
            __NOP();
            __NOP();
            __NOP();
            __NOP();
        }
    }
    else
    {
        for (; i > 0; i--)
        {
            __NOP();
            __NOP();
            __NOP(); // dyf add
            __NOP();
            __NOP();
            __NOP();
            __NOP();
            __NOP();
            __NOP();
            __NOP();
            __NOP();
            __NOP();
            __NOP();
            __NOP();
            __NOP();
            __NOP();
            __NOP();
        }
    }
}

/*********************************************************************************************************
** Function name:       fnState_Detect
** Descriptions:        wait while the position of value in addr is not the same as sign
** input parameters:    addr:the address which need to be detected;
                                                position:the position of the value needed to be detected sign: the valid state£»timeout:timeout time us
** output parameters:   None
** Returned value:      true:valid state  false: state is invalid befor the function return
*********************************************************************************************************/
uint8_t fnRegState_Detect(uint32_t reg_addr, uint32_t position, uint32_t sign, uint32_t timeout)
{
    uint32_t i = 0, val = 0;

    val = (1 << position);

    if (timeout == 0)
    {
        return 0;
    }
    for (i = 0 ; i < timeout ; i++)
    {
        if (((sign == 1) && ((*(uint32_t *)reg_addr & val) == val)) ||   //return while value is 1
            ((sign == 0) && ((*(uint32_t *)reg_addr & val) != val)))      //return while value is 0
        {
            return 1;
        }
        SystemDelayUs(1);
    }
    return 0;
}

/****************************   (C) COPYRIGHT Renergy   ****************************/
/****************************       END OF FILE     ********************************/
