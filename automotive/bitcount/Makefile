

FILE = bitcnt_1.c bitcnt_2.c bitcnt_3.c bitcnt_4.c bitcnts.c bitfiles.c bitstrng.c bstr_i.c
CFLAGS = -static -O3
INC = -I../../../jtag_eval/basic_bsp/ps7_cortexa9_0/include -I../../zybo_build_common
LIB = -L../../../jtag_eval/basic_bsp/ps7_cortexa9_0/lib

SPEC = -specs=../../zybo_build_common/Xilinx.spec

# From subdir.mk
LD_SRCS += ../../zybo_build_common/lscript.ld

C_SRCS += ../../zybo_build_common/platform.c \
bitcnt_1.c bitcnt_2.c bitcnt_3.c bitcnt_4.c bitcnts.c bitfiles.c bitstrng.c bstr_i.c

OBJS += ../../zybo_build_common/platform.o \
bitcnt_1.o bitcnt_2.o bitcnt_3.o bitcnt_4.o bitcnts.o bitfiles.o bitstrng.o bstr_i.o

C_DEPS += ../../zybo_build_common/platform.d \
bitcnt_1.d bitcnt_2.d bitcnt_3.d bitcnt_4.d bitcnts.d bitfiles.d bitstrng.d bstr_i.d

# TODO: Need to link lgcc and lc?
USER_OBJS :=
LIBS := -Wl,-lm,--start-group,-lxil,-lgcc,-lc,--end-group

all: mi_bitcount.elf


%.o: %.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM v7 gcc compiler'
	arm-none-eabi-gcc $(CFLAGS) -c -fmessage-length=0 -MT"$@" -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard $(INC) -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

mi_bitcount.elf: $(OBJS) $(LD_SRCS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: ARM v7 gcc linker'
	arm-none-eabi-gcc -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -Wl,-build-id=none $(SPEC) -Wl,-T -Wl,$(LD_SRCS) $(LIB) -o "mi_bitcount.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	rm -rf $(EXECUTABLES) $(OBJS) $(S_UPPER_DEPS) $(C_DEPS) mi_bitcount.elf Xilinx.spec
	-@echo ' '
