################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
XINT/XInt.obj: ../XINT/XInt.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.2/bin/cl2000" -v28 -ml -mt --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.2/include" --include_path="C:/Users/Lynkzhang/workspace_v6_1/MPU6050/include" -g --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="XINT/XInt.pp" --obj_directory="XINT" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


