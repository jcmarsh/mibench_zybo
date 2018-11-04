FILE1 = qsort_small.c
FILE2 = qsort_large.c
CFLAGS = -Wall -O3

LIBS := -Wl,-lm,--start-group,-lgcc,-lc,--end-group

all: mi_qsort

mi_qsort: qsort_small.c
	gcc $(CFLAGS) qsort_small.c -o mi_qsort

clean:
	rm -rf mi_qsort

