FILE1 = qsort_small.c
FILE2 = qsort_large.c
CFLAGS = -Wall -O3

LIBS := -Wl,-lm,--start-group,-lgcc,-lc,--end-group

all: mi_qsort

mi_qsort: qsort_small.c
	gcc $(CFLAGS) qsort_small.c -o mi_qsort

clean:
	rm -rf mi_qsort

cache:
	valgrind --tool=cachegrind -v --I1=32768,4,32 --D1=524288,8,32 --LL=524288,8,32 ./mi_qsort
	# valgrind --tool=cachegrind -v --I1=32768,4,64 --D1=32768,4,64 --LL=524288,8,64 ./mi_qsort
