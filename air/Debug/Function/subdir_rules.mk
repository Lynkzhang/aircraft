################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
Function/function.obj: ../Function/function.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"D:/Program Files (x86)/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.4/bin/cl2000" -v28 -ml -mt --include_path="D:/Program Files (x86)/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.4/include" --include_path="S:/Users/szy/workspace_v6_0/MPU6050/include" -g --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="Function/function.pp" --obj_directory="Function" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


