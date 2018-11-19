
FILE = crc_32.c
CFLAGS = -static -Wall -O3
INC = -I../../../jtag_eval/basic_bsp/ps7_cortexa9_0/include -I../../zybo_build_common
LIB = -L../../../jtag_eval/basic_bsp/ps7_cortexa9_0/lib

SPEC = -specs=../../zybo_build_common/Xilinx.spec

# From subdir.mk
LD_SRCS += ../../zybo_build_common/lscript.ld

C_SRCS += ../../zybo_build_common/platform.c \
crc_32.c

OBJS += ../../zybo_build_common/platform.o \
crc_32.o

C_DEPS += ../../zybo_build_common/platform.d \
crc_32.d

USER_OBJS :=
LIBS := -Wl,-lm,--start-group,-lxil,-lgcc,-lc,--end-group

all: input_small.h mi_crc.elf

native: Makefile crc_32.c input_small.h
	gcc -o crc -static -g crc_32.c -DNATIVE

input_small.h: small.pcm
	xxd -i small.pcm > input_small.h

%.o: %.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM v7 gcc compiler'
	arm-none-eabi-gcc $(CFLAGS) -c -fmessage-length=0 -MT"$@" -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard $(INC) -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

mi_crc.elf: $(OBJS) $(LD_SRCS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: ARM v7 gcc linker'
	arm-none-eabi-gcc -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -Wl,-build-id=none $(SPEC) -Wl,-T -Wl,$(LD_SRCS) $(LIB) -o "mi_crc.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	rm -rf $(EXECUTABLES) $(OBJS) $(S_UPPER_DEPS) $(C_DEPS) $(ELFSIZE) mi_crc.elf crc Xilinx.spec input_small.h
	-@echo ' '
