#
# Makefile for adpcm and test programs
# -------------------

#####################################################################
# Added by C. Lee.
#
# On Sun machines, gcc need to be informed whether the machines have
# integer multipliers by specifying this option: -mv8.
#
# Also, on Sun machines, in order to use the SPIXTOOLS and SHADE,
# uncomment this option: -static.
#
CC = gcc
LFLAGS = -mv8
LFLAGS = $(LFLAGS) -static
#
# End of addition
######################################################################
CFLAGS = -static -O3

# May need this on a sun:
# CFLAGS=-O -I/usr/demo/SOUND

all: adpcm.o rawcaudio rawdaudio timing
	cp rawcaudio rawdaudio timing ../bin/.

adpcm.o: adpcm.h

rawcaudio: rawcaudio.o adpcm.o
	$(CC) $(CFLAGS) rawcaudio.o adpcm.o -o rawcaudio

rawdaudio: rawdaudio.o adpcm.o
	$(CC) $(CFLAGS) rawdaudio.o adpcm.o -o rawdaudio

timing: timing.o adpcm.o
	$(CC) $(CFLAGS) timing.o adpcm.o -o timing

# Added by C. Lee
clean:
	rm -f *.o ; rm rawcaudio rawdaudio timing ; rm -f ../bin/* ../output*
