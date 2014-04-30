#include <stdio.h>
#include "platform.h"
#include "AXI_PWM.h"
#include "xparameters.h"
#include "xgpio.h"
#include "sleep.h"

#define AXI_PWM_BASEADDR  XPAR_AXI_PWM_0_S_AXI_BASEADDR
int main()
{
    init_platform();
    AXI_PWM_mWriteReg(AXI_PWM_BASEADDR, AXI_PWM_S_AXI_SLV_REG0_OFFSET, 0x80000000 + 8000);
    sleep(1);
    AXI_PWM_mWriteReg(AXI_PWM_BASEADDR, AXI_PWM_S_AXI_SLV_REG1_OFFSET, 0x80000000 + 8000);
    sleep(1);
    AXI_PWM_mWriteReg(AXI_PWM_BASEADDR, AXI_PWM_S_AXI_SLV_REG2_OFFSET, 0x80000000 + 8000);
    sleep(1);
    AXI_PWM_mWriteReg(AXI_PWM_BASEADDR, AXI_PWM_S_AXI_SLV_REG3_OFFSET, 0x80000000 + 8000);
    sleep(1);
    print("Hello World\n\r");
    return 0;
}
