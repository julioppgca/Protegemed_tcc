################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
build-918998481:
	@$(MAKE) -Onone -f subdir_rules.mk build-918998481-inproc

build-918998481-inproc: ../RTOS_config.cfg
	@echo 'Building file: $<'
	@echo 'Invoking: XDCtools'
	"C:/ti/xdctools_3_32_00_06_core/xs" --xdcpath= xdc.tools.configuro -o configPkg -t ti.targets.arm.elf.M4F -p ti.platforms.tiva:TM4C1294NCPDT -r release -c "C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.3.LTS" --compileOptions "-mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -O2 --opt_for_speed=5 --include_path=\"C:/ti/tirtos_tivac_2_16_00_08/products/ndk_2_25_00_09/packages/ti/ndk/inc/bsd\" --include_path=\"C:/Users/skelter_win/Protegemed_tcc/TM4C_Protegemed\" --include_path=\"C:/ti/tirtos_tivac_2_16_00_08/products/TivaWare_C_Series-2.1.1.71b\" --include_path=\"C:/ti/tirtos_tivac_2_16_00_08/products/bios_6_45_01_29/packages/ti/sysbios/posix\" --include_path=\"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.3.LTS/include\" --include_path=\"C:/ti/CMSIS-SP-00300-r4p5-00rel0/CMSIS/Include\" --define=ccs --define=ccs=\"ccs\" --define=PART_TM4C1294NCPDT --define=TIVAWARE --define=NET_NDK --define=ARM_MATH_CM4 --define=__FPU_PRESENT=1 -g --gcc --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi  " "$<"
	@echo 'Finished building: $<'
	@echo ' '

configPkg/linker.cmd: build-918998481 ../RTOS_config.cfg
configPkg/compiler.opt: build-918998481
configPkg/: build-918998481

ptgm_main.obj: ../ptgm_main.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.3.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -O2 --opt_for_speed=5 --include_path="C:/ti/tirtos_tivac_2_16_00_08/products/ndk_2_25_00_09/packages/ti/ndk/inc/bsd" --include_path="C:/Users/skelter_win/Protegemed_tcc/TM4C_Protegemed" --include_path="C:/ti/tirtos_tivac_2_16_00_08/products/TivaWare_C_Series-2.1.1.71b" --include_path="C:/ti/tirtos_tivac_2_16_00_08/products/bios_6_45_01_29/packages/ti/sysbios/posix" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.3.LTS/include" --include_path="C:/ti/CMSIS-SP-00300-r4p5-00rel0/CMSIS/Include" --define=ccs --define=ccs="ccs" --define=PART_TM4C1294NCPDT --define=TIVAWARE --define=NET_NDK --define=ARM_MATH_CM4 --define=__FPU_PRESENT=1 -g --gcc --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --preproc_with_compile --preproc_dependency="ptgm_main.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


