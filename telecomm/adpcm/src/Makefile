CFLAGS = -Wall -static -O3
INC = -I../../../../jtag_eval/basic_bsp/ps7_cortexa9_0/include -I../../../zybo_build_common
LIB = -L../../../../jtag_eval/basic_bsp/ps7_cortexa9_0/lib

SPEC = -specs=../../../zybo_build_common/Xilinx.spec

# From subdir.mk
LD_SRCS += ../../../zybo_build_common/lscript.ld

C_SRCS += ../../../zybo_build_common/platform.c \
adpcm.c \
test_audio.c

OBJS += ../../../zybo_build_common/platform.o \
adpcm.o \
test_audio.o

C_DEPS += ../../../zybo_build_common/platform.d \
adpcm.d \
test_audio.d

# From objects.mk
USER_OBJS :=
LIBS := -Wl,-lm,--start-group,-lxil,-lgcc,-lc,--end-group

# All Target
all: input_small.h mi_adpcm.elf

input_small.h: ../data/small.pcm
	xxd -i ../data/small.pcm > input_small.h

native: input_small.h test_audio.c adpcm.c adpcm.h
	gcc $(CFLAGS) -g -o test_audio test_audio.c adpcm.c -DNATIVE

%.o: %.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM v7 gcc compiler'
	arm-none-eabi-gcc $(CFLAGS) -c -fmessage-length=0 -MT"$@" -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard $(INC) -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

mi_adpcm.elf: $(OBJS) $(LD_SRCS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: ARM v7 gcc linker'
	arm-none-eabi-gcc -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -Wl,-build-id=none $(SPEC) -Wl,-T -Wl,$(LD_SRCS) $(LIB) -o "mi_adpcm.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	mv mi_adpcm.elf ../

# Other Targets
clean:
	rm -rf $(EXECUTABLES) $(OBJS) $(S_UPPER_DEPS) $(C_DEPS) mi_adpcm.elf Xilinx.spec input_small.h test_audio
	-@echo ' '
