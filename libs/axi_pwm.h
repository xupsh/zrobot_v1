#ifndef AXI_PWM_H
#define AXI_PWM_H

#include "xil_io.h"

#define AXI_PWM_BASEADDR 0x43C000000
//period
#define REG0_OFFSET 0x00 
#define REG1_OFFSET 0x04
#define REG2_OFFSET 0x08
#define REG3_OFFSET 0x0C
//direction
#define REG4_OFFSET 0x10
#define REG5_OFFSET 0x14
#define REG6_OFFSET 0x18
#define REG7_OFFSET 0x1C

/**************************** Type Definitions *****************************/
/**
   *
   * Write a value to a AXI_PWM register. A 32 bit write is performed.
   * If the component is implemented in a smaller width, only the least
   * significant data is written.
   *
   * @param   BaseAddress is the base address of the AXI_PWMdevice.
   * @param   RegOffset is the register offset from the base to write to.
   * @param   Data is the data written to the register.
   *
   * @return  None.
   *
   * @note
   * C-style signature:
   * 	void AXI_PWM_mWriteReg(Xuint32 BaseAddress, unsigned
   * 	RegOffset, Xuint32 Data)
   *
 */
#define AXI_PWM_mWriteReg(BaseAddress, RegOffset, Data) \
	  	Xil_Out32((BaseAddress) + (RegOffset), (uint32_t)(Data))

/**
  *
  * Read a value from a AXI_PWM register. A 32 bit read is performed.
  * If the component is implemented in a smaller width, only the least
  * significant data is read from the register. The most significant data
  * will be read as 0.
  *
  * @param   BaseAddress is the base address of the AXI_PWM device.
  * @param   RegOffset is the register offset from the base to write to.
  *
  * @return  Data is the data from the register.
  *
  * @note
  * C-style signature:
  * 	Xuint32 AXI_PWM_mReadReg(Xuint32 BaseAddress, unsigned
  * 	RegOffset
  *
 */
#define AXI_PWM_mReadReg(BaseAddress, RegOffset) \
	    Xil_In32((BaseAddress) + (RegOffset))

#endif // AXI_PWM_H

