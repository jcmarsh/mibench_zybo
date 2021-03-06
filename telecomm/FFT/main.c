#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <platform.h>
#include <unistd.h>
#include "xuartps.h"

#include <xil_cache_l.h>

void run_fft(unsigned MAXWAVES, unsigned MAXSIZE) {
	unsigned i,j;
	float *RealIn;
	float *ImagIn;
	float *RealOut;
	float *ImagOut;
	float *coeff;
	float *amp;
	int invfft=0;

 srand(1);

 RealIn=(float*)malloc(sizeof(float)*MAXSIZE);
 ImagIn=(float*)malloc(sizeof(float)*MAXSIZE);
 RealOut=(float*)malloc(sizeof(float)*MAXSIZE);
 ImagOut=(float*)malloc(sizeof(float)*MAXSIZE);
 coeff=(float*)malloc(sizeof(float)*MAXWAVES);
 amp=(float*)malloc(sizeof(float)*MAXWAVES);

 /* Makes MAXWAVES waves of random amplitude and period */
	for(i=0;i<MAXWAVES;i++) 
	{
		coeff[i] = rand()%1000;
		amp[i] = rand()%1000;
	}
 for(i=0;i<MAXSIZE;i++) 
 {
   /*   RealIn[i]=rand();*/
	 RealIn[i]=0;
	 for(j=0;j<MAXWAVES;j++) 
	 {
		 /* randomly select sin or cos */
		 if (rand()%2)
		 {
		 		RealIn[i]+=coeff[j]*cos(amp[j]*i);
			}
		 else
		 {
		 	RealIn[i]+=coeff[j]*sin(amp[j]*i);
		 }
  	 ImagIn[i]=0;
	 }
 }

 /* regular*/
 fft_float (MAXSIZE,invfft,RealIn,ImagIn,RealOut,ImagOut);

 printf("RealOut:\n");
 for (i=0;i<(MAXSIZE / 4);i++)
   // MAXSIZE better be a multiple of 4! (likely a power of 2, so should be fine)
   printf("%f\t%f\t%f\t%f\n", RealOut[i], RealOut[i + 1], RealOut[i + 2], RealOut[i + 3]);
 printf("\n");

 printf("ImagOut:\n");
 for (i=0;i<(MAXSIZE / 4);i++)
   printf("%f\t%f\t%f\t%f\n", ImagOut[i], ImagOut[i + 1], ImagOut[i + 2], ImagOut[i + 3]);
 printf("\n");

 free(RealIn);
 free(ImagIn);
 free(RealOut);
 free(ImagOut);
 free(coeff);
 free(amp);

}

void run_fft_tagged(unsigned MAXWAVES, unsigned MAXSIZE) {
	unsigned i,j;
	float *RealIn;
	float *ImagIn;
	float *RealOut;
	float *ImagOut;
	float *coeff;
	float *amp;
	int invfft=0;

 srand(1);

 RealIn=(float*)malloc(sizeof(float)*MAXSIZE);
 ImagIn=(float*)malloc(sizeof(float)*MAXSIZE);
 RealOut=(float*)malloc(sizeof(float)*MAXSIZE);
 ImagOut=(float*)malloc(sizeof(float)*MAXSIZE);
 coeff=(float*)malloc(sizeof(float)*MAXWAVES);
 amp=(float*)malloc(sizeof(float)*MAXWAVES);

 /* Makes MAXWAVES waves of random amplitude and period */
	for(i=0;i<MAXWAVES;i++) 
	{
		coeff[i] = rand()%1000;
		amp[i] = rand()%1000;
	}
 for(i=0;i<MAXSIZE;i++) 
 {
   /*   RealIn[i]=rand();*/
	 RealIn[i]=0;
	 for(j=0;j<MAXWAVES;j++) 
	 {
		 /* randomly select sin or cos */
		 if (rand()%2)
		 {
		 		RealIn[i]+=coeff[j]*cos(amp[j]*i);
			}
		 else
		 {
		 	RealIn[i]+=coeff[j]*sin(amp[j]*i);
		 }
  	 ImagIn[i]=0;
	 }
 }

 Xil_L2CacheFlush();

 asm("drseus_start_tag:");
 /* regular*/
 fft_float (MAXSIZE,invfft,RealIn,ImagIn,RealOut,ImagOut);
 asm("drseus_end_tag:");

 Xil_L2CacheFlush();

 printf("RealOut:\n");
 for (i=0;i<(MAXSIZE / 4);i++)
   // MAXSIZE better be a multiple of 4! (likely a power of 2, so should be fine)
   printf("%f\t%f\t%f\t%f\n", RealOut[i], RealOut[i + 1], RealOut[i + 2], RealOut[i + 3]);
 printf("\n");

 printf("ImagOut:\n");
 for (i=0;i<(MAXSIZE /4);i++)
   printf("%f\t%f\t%f\t%f\n", ImagOut[i], ImagOut[i + 1], ImagOut[i + 2], ImagOut[i + 3]);
 printf("\n");

 free(RealIn);
 free(ImagIn);
 free(RealOut);
 free(ImagOut);
 free(coeff);
 free(amp);

}


int main(int argc, char *argv[]) {
	unsigned MAXSIZE;
	unsigned MAXWAVES;

	/* Disable command line args to run on Zybo
	if (argc<3)
	{
		printf("Usage: fft <waves> <length> -i\n");
		printf("-i performs an inverse fft\n");
		printf("make <waves> random sinusoids");
		printf("<length> is the number of samples\n");
		exit(-1);
	}
	else if (argc==4)
		invfft = !strncmp(argv[3],"-i",2);
	*/

	MAXSIZE= 4096; // atoi(argv[2]);
	MAXWAVES= 4; //atoi(argv[1]);

        // MAXSIZE= 2048; // atoi(argv[2]);
        // MAXWAVES= 4; //atoi(argv[1]);

        // MAXSIZE=512;
        // MAXWAVES=4;

	// MAXSIZE= 64; // atoi(argv[2]);
	// MAXWAVES= 2; //atoi(argv[1]);

        init_platform();

	printf("Starting FFT with %d %d\n", MAXWAVES, MAXSIZE);

	// Run if cache warmup desired
	//run_fft(MAXWAVES, MAXSIZE);

	run_fft_tagged(MAXWAVES, MAXSIZE);

        exit_platform();

        printf("\nsafeword ");

	exit(0);
}
