################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.2

ORDERED_OBJS += \
"./main.obj" \
"./source/DSP2802x_Adc.obj" \
"./source/DSP2802x_CSMPasswords.obj" \
"./source/DSP2802x_CodeStartBranch.obj" \
"./source/DSP2802x_CpuTimers.obj" \
"./source/DSP2802x_DefaultIsr.obj" \
"./source/DSP2802x_EPwm.obj" \
"./source/DSP2802x_GlobalVariableDefs.obj" \
"./source/DSP2802x_I2C.obj" \
"./source/DSP2802x_MemCopy.obj" \
"./source/DSP2802x_PieCtrl.obj" \
"./source/DSP2802x_PieVect.obj" \
"./source/DSP2802x_Sci.obj" \
"./source/DSP2802x_SysCtrl.obj" \
"./source/DSP2802x_usDelay.obj" \
"./ePWM/epwm.obj" \
"./XINT/XInt.obj" \
"./UART/uart.obj" \
"./Timer/timer.obj" \
"./MPU6050/motion.obj" \
"./MPU6050/mpu6050.obj" \
"./I2C/i2c.obj" \
"./ADC/Adc.obj" \
"../DSP2802x_Headers_nonBIOS.cmd" \
"../F28027.cmd" \
$(GEN_CMDS__FLAG) \
-l"libc.a" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include source/subdir_vars.mk
-include ePWM/subdir_vars.mk
-include XINT/subdir_vars.mk
-include UART/subdir_vars.mk
-include Timer/subdir_vars.mk
-include MPU6050/subdir_vars.mk
-include I2C/subdir_vars.mk
-include ADC/subdir_vars.mk
-include subdir_rules.mk
-include source/subdir_rules.mk
-include ePWM/subdir_rules.mk
-include XINT/subdir_rules.mk
-include UART/subdir_rules.mk
-include Timer/subdir_rules.mk
-include MPU6050/subdir_rules.mk
-include I2C/subdir_rules.mk
-include ADC/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
MPU6050.out \

EXE_OUTPUTS__QUOTED += \
"MPU6050.out" \

BIN_OUTPUTS += \
MPU6050.hex \

BIN_OUTPUTS__QUOTED += \
"MPU6050.hex" \


# All Target
all: MPU6050.out

# Tool invocations
MPU6050.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: C2000 Linker'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.2/bin/cl2000" -v28 -ml -mt -g --diag_warning=225 --display_error_number --diag_wrap=off -z -m"MPU6050.map" --stack_size=0x300 --warn_sections -i"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.2/lib" -i"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.2/include" --reread_libs --display_error_number --diag_wrap=off --xml_link_info="MPU6050_linkInfo.xml" --rom_model -o "MPU6050.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

MPU6050.hex: $(EXE_OUTPUTS)
	@echo 'Invoking: C2000 Hex Utility'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.2/bin/hex2000"  -o "MPU6050.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)$(BIN_OUTPUTS__QUOTED)
	-$(RM) "main.pp" "source\DSP2802x_Adc.pp" "source\DSP2802x_CpuTimers.pp" "source\DSP2802x_DefaultIsr.pp" "source\DSP2802x_EPwm.pp" "source\DSP2802x_GlobalVariableDefs.pp" "source\DSP2802x_I2C.pp" "source\DSP2802x_MemCopy.pp" "source\DSP2802x_PieCtrl.pp" "source\DSP2802x_PieVect.pp" "source\DSP2802x_Sci.pp" "source\DSP2802x_SysCtrl.pp" "ePWM\epwm.pp" "XINT\XInt.pp" "UART\uart.pp" "Timer\timer.pp" "MPU6050\motion.pp" "MPU6050\mpu6050.pp" "I2C\i2c.pp" "ADC\Adc.pp" 
	-$(RM) "main.obj" "source\DSP2802x_Adc.obj" "source\DSP2802x_CSMPasswords.obj" "source\DSP2802x_CodeStartBranch.obj" "source\DSP2802x_CpuTimers.obj" "source\DSP2802x_DefaultIsr.obj" "source\DSP2802x_EPwm.obj" "source\DSP2802x_GlobalVariableDefs.obj" "source\DSP2802x_I2C.obj" "source\DSP2802x_MemCopy.obj" "source\DSP2802x_PieCtrl.obj" "source\DSP2802x_PieVect.obj" "source\DSP2802x_Sci.obj" "source\DSP2802x_SysCtrl.obj" "source\DSP2802x_usDelay.obj" "ePWM\epwm.obj" "XINT\XInt.obj" "UART\uart.obj" "Timer\timer.obj" "MPU6050\motion.obj" "MPU6050\mpu6050.obj" "I2C\i2c.obj" "ADC\Adc.obj" 
	-$(RM) "source\DSP2802x_CSMPasswords.pp" "source\DSP2802x_CodeStartBranch.pp" "source\DSP2802x_usDelay.pp" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

