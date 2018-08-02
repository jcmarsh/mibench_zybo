/******************************************************************************
*
* Copyright (C) 2010 - 2015 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/

#include <xparameters.h>
#include <xil_cache_l.h>
#include <xgpio.h>
#include <xl2cc.h>
#include "platform_config.h"

void
init_platform()
{
  // Disable all caches so that settings can be updated
  Xil_L2CacheEnable();
  Xil_L1DCacheDisable();
  Xil_L1ICacheDisable();

  // Attempt to read some registers for some reason
  register u32 L2CCReg;

  L2CCReg = Xil_In32(XPS_L2CC_BASEADDR + XPS_L2CC_CNTRL_OFFSET);
  printf("XPS_L2CC_CNTRL: 0x%08lX\n", L2CCReg);

  // Disable L2
  L2CCReg = 0x00000000;
  Xil_Out32(XPS_L2CC_BASEADDR + XPS_L2CC_CNTRL_OFFSET, L2CCReg);
  // L2CCReg = Xil_In32(XPS_L2CC_BASEADDR + XPS_L2CC_CNTRL_OFFSET);
  // printf("XPS_L2CC_CNTRL: 0x%08lX\n", L2CCReg);

  L2CCReg = Xil_In32(XPS_L2CC_BASEADDR + XPS_L2CC_ID_OFFSET);
  printf("XPS_L2CC_ID: 0x%08lX\n", L2CCReg);

  L2CCReg = Xil_In32(XPS_L2CC_BASEADDR + XPS_L2CC_TYPE_OFFSET);
  printf("XPS_L2CC_TYPE: 0x%08lX\n", L2CCReg);

  L2CCReg = Xil_In32(XPS_L2CC_BASEADDR + XPS_L2CC_CNTRL_OFFSET);
  printf("XPS_L2CC_CNTRL: 0x%08lX\n", L2CCReg);

  L2CCReg = Xil_In32(XPS_L2CC_BASEADDR + XPS_L2CC_TAG_RAM_CNTRL_OFFSET);
  printf("XPS_L2CC_TAG_RAM_CNTRL: 0x%08lX\n", L2CCReg);

  L2CCReg = Xil_In32(XPS_L2CC_BASEADDR + XPS_L2CC_DATA_RAM_CNTRL_OFFSET);
  printf("XPS_L2CC_DATA_RAM_CNTRL: 0x%08lX\n", L2CCReg);

  L2CCReg = Xil_In32(XPS_L2CC_BASEADDR + 0x0F60);
  printf("XPS_L2CC_PREFETCH_CNTRL: 0x%08lX\n", L2CCReg);

  L2CCReg = Xil_In32(XPS_L2CC_BASEADDR + XPS_L2CC_AUX_CNTRL_OFFSET);
  printf("XPS_L2CC_AUX_CNTRL: 0x%08lX\n", L2CCReg);

  // Disable early BRESP
  L2CCReg = L2CCReg & (~(XPS_L2CC_AUX_IPFE_MASK | XPS_L2CC_AUX_EBRESPE_MASK));
  // Disable L2 prefetch for data and instructsion
  L2CCReg = L2CCReg & (~(XPS_L2CC_AUX_IPFE_MASK | XPS_L2CC_AUX_DPFE_MASK));
  // Set replacement policy to Round Robin
  L2CCReg = L2CCReg | XPS_L2CC_AUX_CRP_MASK;
  // Disable parity
  L2CCReg = L2CCReg & (~(XPS_L2CC_AUX_IPFE_MASK | XPS_L2CC_AUX_PE_MASK));
  // Write back out
  Xil_Out32(XPS_L2CC_BASEADDR + XPS_L2CC_AUX_CNTRL_OFFSET, L2CCReg);

  L2CCReg = Xil_In32(XPS_L2CC_BASEADDR + 0x0F60);
  printf("XPS_L2CC_PREFETCH_CNTRL: 0x%08lX\n", L2CCReg);
  // Disable double linefill on wrap
  L2CCReg = L2CCReg | 0x08000000U;
  Xil_Out32(XPS_L2CC_BASEADDR + 0x0F60, L2CCReg);

  L2CCReg = Xil_In32(XPS_L2CC_BASEADDR + 0x0F60);
  printf("XPS_L2CC_PREFETCH_CNTRL (Post-Update): 0x%08lX\n", L2CCReg);

  L2CCReg = Xil_In32(XPS_L2CC_BASEADDR + XPS_L2CC_AUX_CNTRL_OFFSET);
  printf("XPS_L2CC_AUX_CNTRL (Post-Update): 0x%08lX\n", L2CCReg);

  // Enable L2
  L2CCReg = 0x00000001;
  Xil_Out32(XPS_L2CC_BASEADDR + XPS_L2CC_CNTRL_OFFSET, L2CCReg);
  // L2CCReg = Xil_In32(XPS_L2CC_BASEADDR + XPS_L2CC_CNTRL_OFFSET);
  // printf("XPS_L2CC_CNTRL: 0x%08lX\n", L2CCReg);

  //Xil_L1DCacheEnable();
  //Xil_L1ICacheEnable();
  //Xil_L2CacheEnable();
  //print("Caches ALL ON\n");

  //Xil_L1DCacheEnable();
  //Xil_L1ICacheEnable();
  //Xil_L2CacheDisable();
  //print("L1D and L1I Caches ON\n");

  //Xil_L1DCacheEnable();
  //Xil_L1ICacheDisable();
  //Xil_L2CacheDisable();
  //print("Only L1D Cache\n");

  //  Xil_L2CacheEnable();
  print("Only L2 Cache\n");

  L2CCReg = Xil_In32(XPS_L2CC_BASEADDR + XPS_L2CC_AUX_CNTRL_OFFSET);
  printf("XPS_L2CC_AUX_CNTRL: 0x%08lX\n", L2CCReg);

  L2CCReg = Xil_In32(XPS_L2CC_BASEADDR + 0x0F60);
  printf("XPS_L2CC_PREFETCH_CNTRL: 0x%08lX\n", L2CCReg);

  //Xil_L2CacheDisable();
  //Xil_L1DCacheDisable();
  //Xil_L1ICacheDisable();
  //xil_printf("No Caches!\n");
}

void exit_platform() {
  register u32 L2CCReg;

  L2CCReg = Xil_In32(XPS_L2CC_BASEADDR + XPS_L2CC_ID_OFFSET);
  printf("XPS_L2CC_ID: 0x%08lX\n", L2CCReg);

  L2CCReg = Xil_In32(XPS_L2CC_BASEADDR + XPS_L2CC_TYPE_OFFSET);
  printf("XPS_L2CC_TYPE: 0x%08lX\n", L2CCReg);

  L2CCReg = Xil_In32(XPS_L2CC_BASEADDR + XPS_L2CC_CNTRL_OFFSET);
  printf("XPS_L2CC_CNTRL: 0x%08lX\n", L2CCReg);

  L2CCReg = Xil_In32(XPS_L2CC_BASEADDR + XPS_L2CC_TAG_RAM_CNTRL_OFFSET);
  printf("XPS_L2CC_TAG_RAM_CNTRL: 0x%08lX\n", L2CCReg);

  L2CCReg = Xil_In32(XPS_L2CC_BASEADDR + XPS_L2CC_DATA_RAM_CNTRL_OFFSET);
  printf("XPS_L2CC_DATA_RAM_CNTRL: 0x%08lX\n", L2CCReg);

  L2CCReg = Xil_In32(XPS_L2CC_BASEADDR + 0x0F60);
  printf("XPS_L2CC_PREFETCH_CNTRL: 0x%08lX\n", L2CCReg);

  L2CCReg = Xil_In32(XPS_L2CC_BASEADDR + XPS_L2CC_AUX_CNTRL_OFFSET);
  printf("XPS_L2CC_AUX_CNTRL: 0x%08lX\n", L2CCReg);
}
