/**************************************************************************************************
  Filename:       Dl698_Test.c
  Revised:        $Date: 2017-05-23 $
  Revision:       $Revision: V0.1 $
  Author:         lin.xiaoman

  Description:    .
**************************************************************************************************/
/*********************************************************************
 * INCLUDES
 */
#include <string.h>
#include "Dl698_Crc.h"
#include "Dl698_Memory.h"
#include "Dl698_Scom.h"
#include "Dl698_Globals.h"
#include "Dl698_UserData.h"
#define CHANNEL_NUM 1

sServerAddr_TypeDef gSa = {0};
#define SR_ADDR_LEN 0x06
#define SR_ADDR_LOG 0x00
#define SR_ADDR_TYPE DL698DL_SERVER_ADDR_TYPE_UNICAST
//u8 SrAddr = 0x1F;

sDl698AL_UserCfg_TypeDef gUserCfg[] =
{
    {1, 0x800, 0x200, 0x200, &gSa},  /*id 0, max apdu size, dl_rx_size,dl_tx_size, pSrAddr*/
    //{1, 0x100, 0x100, 0x100, &gSa},  /*id 1, max apdu size, dl_rx_size,dl_tx_size, pSrAddr*/
    //{1, 0x200, 0x200, 0x200, &gSa},  /*id 2, max apdu size, dl_rx_size,dl_tx_size, pSrAddr*/
    //{1, 0x300, 0x400, 0x300, &gSa}   /*id 3, max apdu size, dl_rx_size,dl_tx_size, pSrAddr*/
};

int main(void)
{
    u8 id = 0, i = 0;

    gSa.ubLen = SR_ADDR_LEN;
    gSa.ubLogic = SR_ADDR_LOG;
    gSa.ubAddrType = SR_ADDR_TYPE;
    gSa.pAddr = SrAddr;

    for (i = 0; i < 3; i++)
    {
        if (fnDl698_Serv_Init(CHANNEL_NUM, gUserCfg) == SUCCESS)
        {
            break;
        }
    }
    if (i == 3)
    {
        //init fail,reset
    }

    for (id = 0; id < CHANNEL_NUM; id++)
    {
        fnDl698_Init(id, id, 9600);
    }
    //testRecodeGetDI();

    while (1)
    {
        UART0_HANDLER();
        for (id = 0; id < CHANNEL_NUM; id++)
        {
            fnDl698_Process(id);
        }
    }
    //return 0;
}
