################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccs1230/ccs/tools/compiler/gcc-arm-none-eabi-9-2019-q4-major

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./main.o" \
"./startup_msp432p401r_gcc.o" \
"./system_msp432p401r.o" \
"./driverlib/adc14.o" \
"./driverlib/aes256.o" \
"./driverlib/comp_e.o" \
"./driverlib/cpu.o" \
"./driverlib/crc32.o" \
"./driverlib/cs.o" \
"./driverlib/dma.o" \
"./driverlib/flash.o" \
"./driverlib/fpu.o" \
"./driverlib/gpio.o" \
"./driverlib/i2c.o" \
"./driverlib/interrupt.o" \
"./driverlib/mpu.o" \
"./driverlib/pcm.o" \
"./driverlib/pmap.o" \
"./driverlib/pss.o" \
"./driverlib/ref_a.o" \
"./driverlib/reset.o" \
"./driverlib/rtc_c.o" \
"./driverlib/spi.o" \
"./driverlib/sysctl.o" \
"./driverlib/systick.o" \
"./driverlib/timer32.o" \
"./driverlib/timer_a.o" \
"./driverlib/uart.o" \
"./driverlib/wdt_a.o" \
"./portable8439/chacha-portable/chacha-portable.o" \
-Wl,-T"../msp432p401r.lds" \
$(GEN_CMDS__FLAG) \
-Wl,--start-group \
-lgcc \
-lnosys \
-lc \
-Wl,--end-group \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include driverlib/subdir_vars.mk
-include portable8439/chacha-portable/subdir_vars.mk
-include subdir_rules.mk
-include driverlib/subdir_rules.mk
-include portable8439/chacha-portable/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
CS6024_HW3_CHACHA20.out \

EXE_OUTPUTS__QUOTED += \
"CS6024_HW3_CHACHA20.out" \


# All Target
all: $(OBJS) $(LDS_SRCS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "CS6024_HW3_CHACHA20.out"

# Tool invocations
CS6024_HW3_CHACHA20.out: $(OBJS) $(LDS_SRCS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: GNU Linker'
	"C:/ti/ccs1230/ccs/tools/compiler/gcc-arm-none-eabi-9-2019-q4-major/bin/arm-none-eabi-gcc-9.2.1.exe" -mfpu=fpv4-sp-d16 -D__MSP432P401R__ -Dgcc -O0 -g -gdwarf-3 -gstrict-dwarf -Wall -march=armv7e-m -mthumb -mfloat-abi=soft -Wl,-Map,"CS6024_HW3_CHACHA20.map" -mthumb -g -gstrict-dwarf -Wall -o"CS6024_HW3_CHACHA20.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)
	-$(RM) "main.o" "startup_msp432p401r_gcc.o" "system_msp432p401r.o" "driverlib\adc14.o" "driverlib\aes256.o" "driverlib\comp_e.o" "driverlib\cpu.o" "driverlib\crc32.o" "driverlib\cs.o" "driverlib\dma.o" "driverlib\flash.o" "driverlib\fpu.o" "driverlib\gpio.o" "driverlib\i2c.o" "driverlib\interrupt.o" "driverlib\mpu.o" "driverlib\pcm.o" "driverlib\pmap.o" "driverlib\pss.o" "driverlib\ref_a.o" "driverlib\reset.o" "driverlib\rtc_c.o" "driverlib\spi.o" "driverlib\sysctl.o" "driverlib\systick.o" "driverlib\timer32.o" "driverlib\timer_a.o" "driverlib\uart.o" "driverlib\wdt_a.o" "portable8439\chacha-portable\chacha-portable.o" 
	-$(RM) "main.d" "startup_msp432p401r_gcc.d" "system_msp432p401r.d" "driverlib\adc14.d" "driverlib\aes256.d" "driverlib\comp_e.d" "driverlib\cpu.d" "driverlib\crc32.d" "driverlib\cs.d" "driverlib\dma.d" "driverlib\flash.d" "driverlib\fpu.d" "driverlib\gpio.d" "driverlib\i2c.d" "driverlib\interrupt.d" "driverlib\mpu.d" "driverlib\pcm.d" "driverlib\pmap.d" "driverlib\pss.d" "driverlib\ref_a.d" "driverlib\reset.d" "driverlib\rtc_c.d" "driverlib\spi.d" "driverlib\sysctl.d" "driverlib\systick.d" "driverlib\timer32.d" "driverlib\timer_a.d" "driverlib\uart.d" "driverlib\wdt_a.d" "portable8439\chacha-portable\chacha-portable.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

