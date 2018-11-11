#include "snipmath.h"
#include <stdio.h>
#include <math.h>
#include <platform.h>
#include <xgpio.h>
#include <xil_cache_l.h>
#include "xuartps.h"

/* The printf's may be removed to isolate just the math calculations */

#define CUBIC_NUM (4 + (10 * 2))
int cubic_index = 0;
int cubic_solutions[CUBIC_NUM] = {0};
double cubic_x[CUBIC_NUM * 3] = {0.0};

#define SQRT_NUM (1001 + 1)
struct int_sqrt sqrt_solutions[SQRT_NUM] = {0};

#define ANG_NUM (360 + 360)
double ang_result[ANG_NUM] = {0.0};
int ang_index = 0;

int single_run(void)
{
  double  a1 = 1.0, b1 = -10.5, c1 = 32.0, d1 = -30.0;
  double  a2 = 1.0, b2 = -4.5, c2 = 17.0, d2 = -30.0;
  double  a3 = 1.0, b3 = -3.5, c3 = 22.0, d3 = -31.0;
  double  a4 = 1.0, b4 = -13.7, c4 = 1.0, d4 = -35.0;
  double  x[3];
  double X;
  int     solutions;
  int i;
  unsigned long l = 0x3fed0169L;
  struct int_sqrt q;
  long n = 0;

  /* solve soem cubic functions */
  //printf("********* CUBIC FUNCTIONS ***********\n");
  /* should get 3 solutions: 2, 6 & 2.5   */
  SolveCubic(a1, b1, c1, d1, &(cubic_solutions[cubic_index]), &(cubic_x[cubic_index * 3]));
  cubic_index++;
  //printf("Solutions:");
  //for(i=0;i<solutions;i++)
  //printf(" %f",x[i]);
  //printf("\n");
  /* should get 1 solution: 2.5           */
  SolveCubic(a2, b2, c2, d2, &(cubic_solutions[cubic_index]), &(cubic_x[cubic_index * 3]));
  cubic_index++;
  //printf("Solutions:");
  //for(i=0;i<solutions;i++)
  //printf(" %f",x[i]);
  //printf("\n");
  SolveCubic(a3, b3, c3, d3, &(cubic_solutions[cubic_index]), &(cubic_x[cubic_index * 3]));
  cubic_index++;
  //printf("Solutions:");
  //for(i=0;i<solutions;i++)
  //printf(" %f",x[i]);
  //printf("\n");
  SolveCubic(a4, b4, c4, d4, &(cubic_solutions[cubic_index]), &(cubic_x[cubic_index * 3]));
  cubic_index++;
  //printf("Solutions:");
  //for(i=0;i<solutions;i++)
  //printf(" %f",x[i]);
  //printf("\n");
  /* Now solve some random equations */
  //for(a1=1;a1<10;a1++) {
  a1 = 1;
  //for(b1=10;b1>0;b1--) {
  b1 = 10;
  //for(c1=5;c1<15;c1+=0.5) {
  for(c1=5;c1<6;c1+=0.5) {
    for(d1=-1;d1>-11;d1--) {
      SolveCubic(a1, b1, c1, d1, &(cubic_solutions[cubic_index]), &(cubic_x[cubic_index * 3]));
      cubic_index++;
	  //printf("Solutions:");
	  //for(i=0;i<solutions;i++)
          //printf(" %f",x[i]);
	  //printf("\n");
    }
  }
  //  }
  //  }
  
  //printf("********* INTEGER SQR ROOTS ***********\n");
  /* perform some integer square roots */
  for (i = 0; i < 1001; ++i) {
    usqrt(i, &(sqrt_solutions[i]));
    // remainder differs on some machines
    // printf("sqrt(%3d) = %2d, remainder = %2d\n",
    //printf("sqrt(%3d) = %2d\n",
    //	     i, q.sqrt);
  }
  usqrt(l, &(sqrt_solutions[SQRT_NUM - 1]));
  //printf("\nsqrt(%lX) = %X, remainder = %X\n", l, q.sqrt, q.frac);
  //printf("\nsqrt(%lX) = %X\n", l, q.sqrt);


  //printf("********* ANGLE CONVERSION ***********\n");
  /* convert some rads to degrees */
  for (X = 0.0; X <= 360.0; X += 1.0)
    ang_result[ang_index++] = deg2rad(X);
  //    printf("%3.0f degrees = %.12f radians\n", X, deg2rad(X));
  //puts("");
  for (X = 0.0; X <= (2 * PI + 1e-6); X += (PI / 180))
    ang_result[ang_index++] = rad2deg(X);
    //printf("%.12f radians = %3.0f degrees\n", X, rad2deg(X));
  
  
  return 0;
}

int main(void) {
  init_platform();

  printf("Starting basicmath small\n");

  //single_run();
  //single_run();
  //single_run();

  Xil_L2CacheFlush();
  asm("drseus_start_tag:");
  single_run();
  asm("drseus_end_tag:");
  Xil_L2CacheFlush();

  printf("Total: %d\n", cubic_index);

  for (int i = 0; i < cubic_index; i++) {
    printf("Solutions:");
    for(int j = 0; j < cubic_solutions[i]; j++) {
      printf("\t%d: %f\n", cubic_solutions[i], cubic_x[(i * 3) + j]);
    }
    printf("\n");
  }

  for (int i = 0; i < SQRT_NUM; i++) {
    printf("sqrt(%d) = %f, remainder = %f\n", i, sqrt_solutions[i].sqrt, sqrt_solutions[i].frac);
  }

  for (int i = 0; i < ANG_NUM; i++) {
    printf("Angle solution %d: %f\n", i, ang_result[i]);
  }

  exit_platform();
  printf("safeword ");
}
