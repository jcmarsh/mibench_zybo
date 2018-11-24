/*
** Test_Audio
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "adpcm.h"
#include "input_small.h"
#ifndef NATIVE
#include <platform.h>
#include <xil_cache_l.h>
#endif

struct adpcm_state coder_state;

// From input_small: ___data_small_pcm_len = 1368864; <- Max
#define IN_BYTES 32768 // 65536 // 1368864

// ___data_small_pcm_len is the number of bytes in the array
// Output should be 1/4 the bytes
char adpcmdata[IN_BYTES / 4];

main() {
#ifndef NATIVE
  init_platform();
  Xil_L2CacheFlush();
#endif
  asm("drseus_start_tag:");

  // In length is the number of 16 bit shorts (so byte count / 2)
  adpcm_coder(___data_small_pcm, adpcmdata, IN_BYTES / 2, &coder_state);

  asm("drseus_end_tag:");
#ifndef NATIVE
  Xil_L2CacheFlush();
#endif

  if (fwrite(adpcmdata,IN_BYTES / 4,1,stdout) != 1) {
    printf("Can't write audio.\n");
    exit(0);
  }

  printf("Encoded %d bytes.\n", IN_BYTES);

  printf("safeword ");

#ifndef NATIVE
  exit_platform();
#endif

  exit(0);
}
