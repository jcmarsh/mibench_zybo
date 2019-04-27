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

#include <stdio.h>
#include <xparameters.h>
#include <xil_cache_l.h>
#include <xgpio.h>
#include <xl2cc.h>
#include "platform_config.h"

// xil_cache.c has some private functions...
#ifdef __GNUC__
static inline void Xil_L2CacheSync(void)
#else
static void Xil_L2CacheSync(void)
#endif
{
#ifdef CONFIG_PL310_ERRATA_753970
	Xil_Out32(XPS_L2CC_BASEADDR + XPS_L2CC_DUMMY_CACHE_SYNC_OFFSET, 0x0U);
#else
	Xil_Out32(XPS_L2CC_BASEADDR + XPS_L2CC_CACHE_SYNC_OFFSET, 0x0U);
#endif
}

// Mostly copied from Xil_L2CacheEnable
void my_L2CacheEnable(void) {
  register u32 L2CCReg;

  L2CCReg = Xil_In32(XPS_L2CC_BASEADDR + XPS_L2CC_CNTRL_OFFSET);

  /* only enable if L2CC is currently disabled */
  if ((L2CCReg & 0x01U) == 0U) {
    printf("Version 0... ");
    /* set up the way size and latencies */
    L2CCReg = Xil_In32(XPS_L2CC_BASEADDR +
                       XPS_L2CC_AUX_CNTRL_OFFSET);
    L2CCReg &= XPS_L2CC_AUX_REG_ZERO_MASK; // 0xFFF1FFFFU
    L2CCReg |= XPS_L2CC_AUX_REG_DEFAULT_MASK; // 0x72360000U
    //L2CCReg &= 0x42360000; //0x03160000U;
    Xil_Out32(XPS_L2CC_BASEADDR + XPS_L2CC_AUX_CNTRL_OFFSET,
              L2CCReg);
    Xil_Out32(XPS_L2CC_BASEADDR + XPS_L2CC_TAG_RAM_CNTRL_OFFSET,
              XPS_L2CC_TAG_RAM_DEFAULT_MASK);
    Xil_Out32(XPS_L2CC_BASEADDR + XPS_L2CC_DATA_RAM_CNTRL_OFFSET,
              XPS_L2CC_DATA_RAM_DEFAULT_MASK);

    //// Set prefetch behavior (off)
    //L2CCReg = Xil_In32(XPS_L2CC_BASEADDR + 0x0F60);
    //// Disable double linefill on wrap, prefetching off
    //L2CCReg = 0x08000000U;
    //Xil_Out32(XPS_L2CC_BASEADDR + 0x0F60, L2CCReg);

    /* Clear the pending interrupts */
    L2CCReg = Xil_In32(XPS_L2CC_BASEADDR +
                       XPS_L2CC_ISR_OFFSET);
    Xil_Out32(XPS_L2CC_BASEADDR + XPS_L2CC_IAR_OFFSET, L2CCReg);

    Xil_L2CacheInvalidate();
    /* Enable the L2CC */
    L2CCReg = Xil_In32(XPS_L2CC_BASEADDR +
                       XPS_L2CC_CNTRL_OFFSET);
    Xil_Out32(XPS_L2CC_BASEADDR + XPS_L2CC_CNTRL_OFFSET,
              (L2CCReg | (0x01U)));

    Xil_L2CacheSync();
    /* synchronize the processor */
    dsb();
    printf("Done\n");
  } else {
    printf("Error: tried to enable already enabled cache\n");
  }
}

void
init_platform()
{
  // Attempt to read some registers for some reason
  register u32 L2CCReg;

  // Disable all caches (to muck with settings)
  Xil_L2CacheDisable();
  Xil_L1DCacheDisable();
  Xil_L1ICacheDisable();

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

  my_L2CacheEnable();
  print("Only L2 Cache\n");

  L2CCReg = Xil_In32(XPS_L2CC_BASEADDR + XPS_L2CC_AUX_CNTRL_OFFSET);
  printf("XPS_L2CC_AUX_CNTRL: 0x%08lX\n", L2CCReg);

  L2CCReg = Xil_In32(XPS_L2CC_BASEADDR + 0x0F60);
  printf("XPS_L2CC_PREFETCH_CNTRL: 0x%08lX\n", L2CCReg);

  L2CCReg = Xil_In32(XPS_L2CC_BASEADDR + XPS_L2CC_DEBUG_CTRL_OFFSET);
  printf("XPS_L2CC_DEBUG_CTRL_OFFSET: 0x%08lX\n", L2CCReg);
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
