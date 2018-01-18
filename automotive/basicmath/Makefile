FILE1 = basicmath_small.c   rad2deg.c  cubic.c   isqrt.c
FILE2 = basicmath_large.c   rad2deg.c  cubic.c   isqrt.c
CFLAGS = -static -O3
INC = -I../../../jtag_eval/basic_bsp/ps7_cortexa9_0/include -I../../zybo_build_common
LIB = -L../../../jtag_eval/basic_bsp/ps7_cortexa9_0/lib

SPEC = -specs=../../zybo_build_common/Xilinx.spec

# From subdir.mk
LD_SRCS += ../../zybo_build_common/lscript.ld

C_SRCS += ../../zybo_build_common/platform.c \
basicmath_small.c   rad2deg.c  cubic.c   isqrt.c

OBJS += ../../zybo_build_common/platform.o \
basicmath_small.o   rad2deg.o  cubic.o   isqrt.o

C_DEPS += ../../zybo_build_common/platform.d \
basicmath_small.d   rad2deg.d  cubic.d   isqrt.d

# TODO: Need to link lgcc and lc?
USER_OBJS :=
LIBS := -Wl,-lm,--start-group,-lxil,-lgcc,-lc,--end-group

ELFSIZE += mi_basicmath.elf.size

all: mi_basicmath.elf secondary-outputs


%.o: %.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM v7 gcc compiler'
	arm-none-eabi-gcc $(CFLAGS) -c -fmessage-length=0 -MT"$@" -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard $(INC) -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

mi_basicmath.elf: $(OBJS) $(LD_SRCS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: ARM v7 gcc linker'
	arm-none-eabi-gcc -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -Wl,-build-id=none $(SPEC) -Wl,-T -Wl,$(LD_SRCS) $(LIB) -o "mi_basicmath.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

mi_basicmath.elf.size: mi_basicmath.elf
	@echo 'Invoking: ARM v7 Print Size'
	arm-none-eabi-size mi_basicmath.elf  |tee "mi_basicmath.elf.size"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	rm -rf $(EXECUTABLES) $(OBJS) $(S_UPPER_DEPS) $(C_DEPS) $(ELFSIZE) mi_basicmath.elf Xilinx.spec
	-@echo ' '

pre-build:
	-a9-linaro-pre-build-step
	-@echo ' '

secondary-outputs: $(ELFSIZE)

.PHONY: all clean dependents
.SECONDARY: main-build pre-build

#basicmath_small: ${FILE1} Makefile
#	gcc -static -O3 ${FILE1} -o basicmath_small -lm
