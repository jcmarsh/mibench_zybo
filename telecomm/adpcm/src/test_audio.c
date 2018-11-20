/*
** Test_Audio
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "adpcm.h"
#include "input_small.h"

struct adpcm_state coder_state;

// From input_small: ___data_small_pcm_len = 1368864; <- Max
#define IN_BYTES 1368864

// ___data_small_pcm_len is the number of bytes in the array
// Output should be 1/4 the bytes
char adpcmdata[IN_BYTES / 4];

main() {
  //init_platform();

  printf("Doing some encoding I guess\n");

  //    Xil_L2CacheFlush();
  //asm("drseus_start_tag:");

  // In length is the number of 16 bit shorts (so byte count / 2)
  adpcm_coder(___data_small_pcm, adpcmdata, IN_BYTES / 2, &coder_state);

  //    asm("drseus_end_tag:");
  //Xil_L2CacheFlush();

  if (fwrite(adpcmdata,IN_BYTES / 4,1,stdout) != 1) {
    printf("Can't write audio.\n");
    exit(0);
  }

  printf("It's been coded.\n");

  printf("safeword ");
  //    exit_platform();

  exit(0);
}
