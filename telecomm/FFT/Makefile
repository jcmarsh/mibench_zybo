OBJ = main.o fftmisc.o  fourierf.o
FILE = main.c fftmisc.c  fourierf.c
CFLAGS = -static -O3
INC = -I../../../jtag_eval/basic_bsp/ps7_cortexa9_0/include
LIB = -L../../../jtag_eval/basic_bsp/ps7_cortexa9_0/lib

SPEC = -specs=../../zybo_build_common/Xilinx.spec

# From subdir.mk
LD_SRCS += ../../zybo_build_common/lscript.ld

C_SRCS += ../../zybo_build_common/platform.c \
fftmisc.c \
fourierf.c \
main.c

OBJS += ../../zybo_build_common/platform.o \
fftmisc.o \
fourierf.o \
main.o

C_DEPS += ../../zybo_build_common/platform.d \
fftmisc.d \
fourierf.d \
main.d

# From objects.mk
USER_OBJS :=
LIBS := -Wl,-lm,--start-group,-lxil,-lgcc,-lc,--end-group


ELFSIZE += fft.elf.size

# All Target
all: pre-build main-build

# Main-build Target
main-build: fft.elf secondary-outputs


%.o: %.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM v7 gcc compiler'
	arm-none-eabi-gcc -Wall -O0 -g3 -c -fmessage-length=0 -MT"$@" -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard $(INC) -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

fft.elf: $(OBJS) $(LD_SRCS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: ARM v7 gcc linker'
	arm-none-eabi-gcc -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -Wl,-build-id=none $(SPEC) -Wl,-T -Wl,$(LD_SRCS) $(LIB) -o "mi_fft.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

fft.elf.size: fft.elf
	@echo 'Invoking: ARM v7 Print Size'
	arm-none-eabi-size fft.elf  |tee "fft.elf.size"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	rm -rf $(EXECUTABLES) $(OBJS) $(S_UPPER_DEPS) $(C_DEPS) $(ELFSIZE) mi_fft.elf Xilinx.spec
	-@echo ' '

pre-build:
	-a9-linaro-pre-build-step
	-@echo ' '

secondary-outputs: $(ELFSIZE)

.PHONY: all clean dependents
.SECONDARY: main-build pre-build
