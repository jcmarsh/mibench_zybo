CFLAGS = -Wall -O3
INC = -I../../../jtag_eval/basic_bsp/ps7_cortexa9_0/include -I../../zybo_build_common
LIB = -L../../../jtag_eval/basic_bsp/ps7_cortexa9_0/lib

SPEC = -specs=../../zybo_build_common/Xilinx.spec

# From subdir.mk
LD_SRCS += ../../zybo_build_common/lscript.ld

C_SRCS += ../../zybo_build_common/platform.c \
dijkstra_small.c

OBJS += ../../zybo_build_common/platform.o \
dijkstra_small.o

C_DEPS += ../../zybo_build_common/platform.d \
dijkstra_small.d

USER_OBJS :=
LIBS := -Wl,-lm,--start-group,-lxil,-lgcc,-lc,--end-group

all: input_file mi_dijkstra.elf

input_file: input.dat to_array.py
	python3 to_array.py input.dat > input_data.h

%.o: %.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM v7 gcc compiler'
	arm-none-eabi-gcc $(CFLAGS) -c -fmessage-length=0 -MT"$@" -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard $(INC) -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

mi_dijkstra.elf: $(OBJS) $(LD_SRCS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: ARM v7 gcc linker'
	arm-none-eabi-gcc -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -Wl,-build-id=none $(SPEC) -Wl,-T -Wl,$(LD_SRCS) $(LIB) -o "mi_dijkstra.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	rm -rf $(EXECUTABLES) $(OBJS) $(S_UPPER_DEPS) $(C_DEPS) mi_dijkstra.elf Xilinx.spec input_data.h
	-@echo ' '

pre-build:
	-a9-linaro-pre-build-step
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: main-build pre-build
