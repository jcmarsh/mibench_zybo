FILE = susan.c
CFLAGS = -static -DSASR -c -O3 -DSTUPID_COMPILER -DNeedFunctionPrototypes=1
INC = -I../../../jtag_eval/basic_bsp/ps7_cortexa9_0/include -I../../zybo_build_common -Iinc
LIB = -L../../../jtag_eval/basic_bsp/ps7_cortexa9_0/lib

SPEC = -specs=../../zybo_build_common/Xilinx.spec

# From subdir.mk
LD_SRCS += ../../zybo_build_common/lscript.ld

LIBS := -Wl,-lm,--start-group,-lxil,-lgcc,-lc,--end-group

SRC = ./src

GSM_OBJECTS =	$(SRC)/add.o		\
		$(SRC)/code.o		\
		$(SRC)/debug.o		\
		$(SRC)/decode.o		\
		$(SRC)/long_term.o	\
		$(SRC)/lpc.o		\
		$(SRC)/preprocess.o	\
		$(SRC)/rpe.o		\
		$(SRC)/gsm_destroy.o	\
		$(SRC)/gsm_decode.o	\
		$(SRC)/gsm_encode.o	\
		$(SRC)/gsm_explode.o	\
		$(SRC)/gsm_implode.o	\
		$(SRC)/gsm_create.o	\
		$(SRC)/gsm_print.o	\
		$(SRC)/gsm_option.o	\
		$(SRC)/short_term.o	\
		$(SRC)/table.o

TOAST_OBJECTS =	../../zybo_build_common/platform.o \
		$(SRC)/toast.o 		\
		$(SRC)/toast_lin.o	\
		$(SRC)/toast_ulaw.o	\
		$(SRC)/toast_alaw.o	\
		$(SRC)/toast_audio.o


all: input_small.h mi_gsm.elf #libgsm.a mi_gsm.elf

input_small.h: ./data/small.au
	xxd -i ./data/small.au > input_small.h

%.o: %.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM v7 gcc compiler'
	arm-none-eabi-gcc $(CFLAGS) -c -fmessage-length=0 -MT"$@" -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard $(INC) -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

#libgsm.a: $(GSM_OBJECTS)
#	arm-none-eabi-ar cr libgsm.a $(GSM_OBJECTS)
#	@echo 'built libgsm.a'

mi_gsm.elf: $(TOAST_OBJECTS) $(GSM_OBJECTS) $(LD_SRCS) # $(LIBGSM) $(LD_SRCS)
	@echo 'Building target: $@'
	@echo 'Invoking: ARM v7 gcc linker'
	arm-none-eabi-gcc -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -Wl,-build-id=none $(SPEC) -Wl,-T -Wl,$(LD_SRCS) $(LIB) -o "mi_gsm.elf" $(TOAST_OBJECTS) $(GSM_OBJECTS) $(LIBS) # libgsm.a
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	rm -rf $(EXECUTABLES) $(TOAST_OBJECTS) $(GSM_OBJECTS) ./src/*.d mi_gsm.elf Xilinx.spec input_small.h
	-@echo ' '

pre-build:
	-a9-linaro-pre-build-step
	-@echo ' '
