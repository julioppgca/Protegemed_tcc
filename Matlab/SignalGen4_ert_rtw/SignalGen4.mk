###########################################################################
## Makefile generated for Simulink model 'SignalGen4'. 
## 
## Makefile     : SignalGen4.mk
## Generated on : Thu Aug 31 20:19:09 2017
## MATLAB Coder version: 3.1 (R2016a)
## 
## Build Info:
## 
## Final product: $(RELATIVE_PATH_TO_ANCHOR)/SignalGen4.out
## Product type : executable
## Build type   : Top-Level Standalone Executable
## 
###########################################################################

###########################################################################
## MACROS
###########################################################################

# Macro Descriptions:
# PRODUCT_NAME            Name of the system to build
# MAKEFILE                Name of this makefile
# COMPUTER                Computer type. See the MATLAB "computer" command.

PRODUCT_NAME              = SignalGen4
MAKEFILE                  = SignalGen4.mk
COMPUTER                  = PCWIN64
MATLAB_ROOT               = C:/PROGRA~1/MATLAB/R2016a
MATLAB_BIN                = C:/PROGRA~1/MATLAB/R2016a/bin
MATLAB_ARCH_BIN           = C:/PROGRA~1/MATLAB/R2016a/bin/win64
MASTER_ANCHOR_DIR         = 
START_DIR                 = C:/Users/skelter_win/Protegemed_tcc/Matlab
ARCH                      = win64
SOLVER                    = 
SOLVER_OBJ                = 
CLASSIC_INTERFACE         = 0
TGT_FCN_LIB               = TI C28x
MODELREF_LINK_RSPFILE_NAME = SignalGen4_ref.rsp
RELATIVE_PATH_TO_ANCHOR   = ..

###########################################################################
## TOOLCHAIN SPECIFICATIONS
###########################################################################

# Toolchain Name:          Texas Instruments C2000 Code Generation Tools v6.0.0 | gmake (64-bit Windows)
# Supported Version(s):    
# ToolchainInfo Version:   R2016a
# Specification Revision:  1.0
# 

-include codertarget_assembly_flags.mk
-include ../codertarget_assembly_flags.mk


#-------------------------------------------
# Macros assumed to be defined elsewhere
#-------------------------------------------

# CCSV6INSTALLDIR
# CCSV6SCRIPTINGDIR
# TARGET_LOAD_CMD_ARGS
# TIF28XXXSYSSWDIR

#-----------
# MACROS
#-----------

TARGET_SCRIPTINGTOOLS_INSTALLDIR = $(CCSV6SCRIPTINGDIR)
TI_TOOLS                         = $(CCSV6INSTALLDIR)/bin
TI_INCLUDE                       = $(CCSV6INSTALLDIR)/include
TI_LIB                           = $(CCSV6INSTALLDIR)/lib
F28_HEADERS                      = $(TIF28XXXSYSSWDIR)/~SupportFiles/DSP280x_headers
CCOUTPUTFLAG                     = --output_file=
LDOUTPUTFLAG                     = --output_file=
EXE_FILE_EXT                     = $(PROGRAM_FILE_EXT)
DOWN_EXE_JS                      = $(MATLAB_ROOT)/toolbox/idelink/extensions/ticcs/ccsdemos/runProgram.js
CCS_CONFIG                       = $(TARGET_PKG_INSTALLDIR)/tic2000/CCS_Config/f28x_generic.ccxml
ASAP2_PERL_PATH                  = $(MATLAB_ROOT)/toolbox/target/extensions/processor/tic2000/asap2/asap2post.pl
SHELL                            = %SystemRoot%/system32/cmd.exe

TOOLCHAIN_SRCS = 
TOOLCHAIN_INCS = 
TOOLCHAIN_LIBS = 

#------------------------
# BUILD TOOL COMMANDS
#------------------------

# Assembler: C2000 Assembler
AS_PATH = $(TI_TOOLS)
AS = $(AS_PATH)/cl2000

# C Compiler: C2000 C Compiler
CC_PATH = $(TI_TOOLS)
CC = $(CC_PATH)/cl2000

# Linker: C2000 Linker
LD_PATH = $(TI_TOOLS)
LD = $(LD_PATH)/cl2000

# C++ Compiler: C2000 C++ Compiler
CPP_PATH = $(TI_TOOLS)
CPP = $(CPP_PATH)/cl2000

# C++ Linker: C2000 C++ Linker
CPP_LD_PATH = $(TI_TOOLS)
CPP_LD = $(CPP_LD_PATH)/cl2000

# Archiver: C2000 Archiver
AR_PATH = $(TI_TOOLS)
AR = $(AR_PATH)/ar2000

# MEX Tool: MEX Tool
MEX_PATH = $(MATLAB_BIN)
MEX = $(MEX_PATH)/mex

# Download: Download
DOWNLOAD_PATH = $(TARGET_SCRIPTINGTOOLS_INSTALLDIR)/bin
DOWNLOAD = $(DOWNLOAD_PATH)/dss.bat

# Execute: Execute
EXECUTE = $(PRODUCT)

# Builder: GMAKE Utility
MAKE_PATH = %MATLAB%\bin\win64
MAKE = $(MAKE_PATH)/gmake


#-------------------------
# Directives/Utilities
#-------------------------

ASDEBUG             = -g
AS_OUTPUT_FLAG      = --output_file=
CDEBUG              = -g
C_OUTPUT_FLAG       = --output_file=
LDDEBUG             = -g
OUTPUT_FLAG         = --output_file=
CPPDEBUG            = -g
CPP_OUTPUT_FLAG     = --output_file=
CPPLDDEBUG          = -g
OUTPUT_FLAG         = --output_file=
ARDEBUG             =
STATICLIB_OUTPUT_FLAG =
MEX_DEBUG           = -g
RM                  = @del /F
ECHO                = @echo
MV                  = @move
RUN                 =

#--------------------------------------
# "Faster Runs" Build Configuration
#--------------------------------------

ARFLAGS              = -r
ASFLAGS              = -s \
                       -v28 \
                       -ml \
                       $(ASFLAGS_ADDITIONAL)
CFLAGS               = --compile_only \
                       --large_memory_model \
                       --cla_support=cla0 \
                       --silicon_version=28 \
                       --define="LARGE_MODEL" \
                       -i"$(F28_HEADERS)" \
                       -i"$(F28_HEADERS)/include" \
                       -i"$(TI_INCLUDE)" \
                       -O2
CPPFLAGS             =
CPP_LDFLAGS          =
CPP_SHAREDLIB_LDFLAGS  =
DOWNLOAD_FLAGS       = $(TARGET_LOAD_CMD_ARGS) $(PRODUCT)
EXECUTE_FLAGS        =
LDFLAGS              = -z -I$(TI_LIB) \
                       --stack_size=$(STACK_SIZE) --warn_sections \
                       --heap_size=$(HEAP_SIZE) \
                       --reread_libs --rom_model \
                       -m"$(PRODUCT_NAME).map"
MEX_CFLAGS           =
MEX_LDFLAGS          =
MAKE_FLAGS           = -B -f $(MAKEFILE)
SHAREDLIB_LDFLAGS    =

#--------------------
# File extensions
#--------------------

OBJ_EXT             = .obj
ASM_EXT             = .asm
AS_EXT              = .asm
CLA_EXT             = .cla
H_EXT               = .h
OBJ_EXT             = .obj
C_EXT               = .c
EXE_EXT             = .out
SHAREDLIB_EXT       =
HPP_EXT             = .hpp
OBJ_EXT             = .obj
CPP_EXT             = .cpp
EXE_EXT             =
SHAREDLIB_EXT       =
STATICLIB_EXT       = .lib
MEX_EXT             = .mexw64
MAKE_EXT            = .mk


###########################################################################
## OUTPUT INFO
###########################################################################

PRODUCT = $(RELATIVE_PATH_TO_ANCHOR)/SignalGen4.out
PRODUCT_TYPE = "executable"
BUILD_TYPE = "Top-Level Standalone Executable"

###########################################################################
## INCLUDE PATHS
###########################################################################

INCLUDES_BUILDINFO = -I$(MATLAB_ROOT)/simulink/include/sf_runtime -I$(START_DIR)/SignalGen4_ert_rtw -I$(START_DIR) -I$(MATLAB_ROOT)/extern/include -I$(MATLAB_ROOT)/simulink/include -I$(MATLAB_ROOT)/rtw/c/src -I$(MATLAB_ROOT)/rtw/c/src/ext_mode/common -I$(MATLAB_ROOT)/rtw/c/ert -IC:/MATLAB/SupportPackages/R2016a/toolbox/target/supportpackages/tic2000/src -I$(MATLAB_ROOT)/toolbox/target/extensions/processor/tic2000/include -I$(MATLAB_ROOT)/toolbox/rtw/targets/common/can/blocks/tlc_c -IC:/MATLAB/SupportPackages/R2016a/toolbox/target/supportpackages/tic2000/inc -IC:/ti/controlSUITE/device_support/f2806x/v141/F2806x_common/include -IC:/ti/controlSUITE/device_support/f2806x/v141/F2806x_headers/include -I$(MATLAB_ROOT)/toolbox/shared/can/src/scanutil

INCLUDES = $(INCLUDES_BUILDINFO)

###########################################################################
## DEFINES
###########################################################################

DEFINES_ = -DMODEL=SignalGen4 -DNUMST=2 -DNCSTATES=0 -DHAVESTDIO -DONESTEPFCN=1 -DTERMFCN=1 -DMAT_FILE=0 -DMULTI_INSTANCE_CODE=0 -DINTEGER_CODE=0 -DMT=1 -DCLASSIC_INTERFACE=0 -DALLOCATIONFCN=0 -DTID01EQ=0 -D__MW_TARGET_USE_HARDWARE_RESOURCES_H__ -DRT -DSTACK_SIZE=512
DEFINES_BUILD_ARGS = -DONESTEPFCN=1 -DTERMFCN=1 -DMAT_FILE=0 -DMULTI_INSTANCE_CODE=0 -DINTEGER_CODE=0 -DMT=1 -DCLASSIC_INTERFACE=0 -DALLOCATIONFCN=0
DEFINES_IMPLIED = -DTID01EQ=0
DEFINES_SKIPFORSIL = -DRT -DSTACK_SIZE=512
DEFINES_STANDARD = -DMODEL=SignalGen4 -DNUMST=2 -DNCSTATES=0 -DHAVESTDIO

DEFINES = $(DEFINES_) $(DEFINES_BUILD_ARGS) $(DEFINES_IMPLIED) $(DEFINES_SKIPFORSIL) $(DEFINES_STANDARD)

###########################################################################
## SOURCE FILES
###########################################################################

SRCS = $(START_DIR)/SignalGen4_ert_rtw/MW_c28xx_board.c $(START_DIR)/SignalGen4_ert_rtw/MW_c28xx_csl.c $(START_DIR)/SignalGen4_ert_rtw/MW_c28xx_pwm.c $(START_DIR)/SignalGen4_ert_rtw/SignalGen4.c $(START_DIR)/SignalGen4_ert_rtw/SignalGen4_data.c C:/MATLAB/SupportPackages/R2016a/toolbox/target/supportpackages/tic2000/src/c2806xBoard_Realtime_Support.c C:/ti/controlSUITE/device_support/f2806x/v141/F2806x_common/source/F2806x_CpuTimers.c C:/ti/controlSUITE/device_support/f2806x/v141/F2806x_common/source/F2806x_DefaultIsr.c C:/ti/controlSUITE/device_support/f2806x/v141/F2806x_headers/source/F2806x_GlobalVariableDefs.c C:/ti/controlSUITE/device_support/f2806x/v141/F2806x_common/source/F2806x_PieCtrl.c C:/ti/controlSUITE/device_support/f2806x/v141/F2806x_common/source/F2806x_PieVect.c C:/ti/controlSUITE/device_support/f2806x/v141/F2806x_common/source/F2806x_SysCtrl.c C:/ti/controlSUITE/device_support/f2806x/v141/F2806x_common/source/F2806x_usDelay.asm C:/ti/controlSUITE/device_support/f2806x/v141/F2806x_common/source/F2806x_CodeStartBranch.asm C:/ti/controlSUITE/device_support/f2806x/v141/F2806x_common/source/F2806x_Dma.c C:/ti/controlSUITE/device_support/f2806x/v141/F2806x_common/source/F2806x_Adc.c C:/MATLAB/SupportPackages/R2016a/toolbox/target/supportpackages/tic2000/src/c2806xSchedulerTimer0.c

MAIN_SRC = $(START_DIR)/SignalGen4_ert_rtw/ert_main.c

ALL_SRCS = $(SRCS) $(MAIN_SRC)

###########################################################################
## OBJECTS
###########################################################################

OBJS = MW_c28xx_board.obj MW_c28xx_csl.obj MW_c28xx_pwm.obj SignalGen4.obj SignalGen4_data.obj c2806xBoard_Realtime_Support.obj F2806x_CpuTimers.obj F2806x_DefaultIsr.obj F2806x_GlobalVariableDefs.obj F2806x_PieCtrl.obj F2806x_PieVect.obj F2806x_SysCtrl.obj F2806x_usDelay.obj F2806x_CodeStartBranch.obj F2806x_Dma.obj F2806x_Adc.obj c2806xSchedulerTimer0.obj

MAIN_OBJ = ert_main.obj

ALL_OBJS = $(OBJS) $(MAIN_OBJ)

###########################################################################
## PREBUILT OBJECT FILES
###########################################################################

PREBUILT_OBJS = 

###########################################################################
## LIBRARIES
###########################################################################

LIBS = C:/MATLAB/SupportPackages/R2016a/toolbox/target/supportpackages/tic2000/src/c28069M.cmd C:/MATLAB/SupportPackages/R2016a/toolbox/target/supportpackages/tic2000/rtlib/IQmath_fpu32.lib $(MATLAB_ROOT)/toolbox/idelink/extensions/ticcs/c2000/c2806xPeripherals.cmd

###########################################################################
## SYSTEM LIBRARIES
###########################################################################

SYSTEM_LIBS = 

###########################################################################
## ADDITIONAL TOOLCHAIN FLAGS
###########################################################################

#---------------
# C Compiler
#---------------

CFLAGS_SKIPFORSIL = -v28 -ml --float_support=fpu32
CFLAGS_BASIC = $(DEFINES) $(INCLUDES)

CFLAGS += $(CFLAGS_SKIPFORSIL) $(CFLAGS_BASIC)

#-----------------
# C++ Compiler
#-----------------

CPPFLAGS_SKIPFORSIL = -v28 -ml --float_support=fpu32
CPPFLAGS_BASIC = $(DEFINES) $(INCLUDES)

CPPFLAGS += $(CPPFLAGS_SKIPFORSIL) $(CPPFLAGS_BASIC)

#---------------
# C++ Linker
#---------------

CPP_LDFLAGS_SKIPFORSIL = -l"rts2800_fpu32.lib" --define BOOT_FROM_FLASH=1

CPP_LDFLAGS += $(CPP_LDFLAGS_SKIPFORSIL)

#------------------------------
# C++ Shared Library Linker
#------------------------------

CPP_SHAREDLIB_LDFLAGS_SKIPFORSIL = -l"rts2800_fpu32.lib" --define BOOT_FROM_FLASH=1

CPP_SHAREDLIB_LDFLAGS += $(CPP_SHAREDLIB_LDFLAGS_SKIPFORSIL)

#-----------
# Linker
#-----------

LDFLAGS_SKIPFORSIL = -l"rts2800_fpu32.lib" --define BOOT_FROM_FLASH=1

LDFLAGS += $(LDFLAGS_SKIPFORSIL)

#--------------------------
# Shared Library Linker
#--------------------------

SHAREDLIB_LDFLAGS_SKIPFORSIL = -l"rts2800_fpu32.lib" --define BOOT_FROM_FLASH=1

SHAREDLIB_LDFLAGS += $(SHAREDLIB_LDFLAGS_SKIPFORSIL)

###########################################################################
## PHONY TARGETS
###########################################################################

.PHONY : all build buildobj clean info prebuild download execute


all : build
	@echo "### Successfully generated all binary outputs."


build : prebuild $(PRODUCT)


buildobj : prebuild $(OBJS) $(PREBUILT_OBJS) $(LIBS)
	@echo "### Successfully generated all binary outputs."


prebuild : 


download : build
	@echo "### Invoking postbuild tool "Download" ..."
	$(DOWNLOAD) $(DOWNLOAD_FLAGS)
	@echo "### Done invoking postbuild tool."


execute : download
	@echo "### Invoking postbuild tool "Execute" ..."
	$(EXECUTE) $(EXECUTE_FLAGS)
	@echo "### Done invoking postbuild tool."


###########################################################################
## FINAL TARGET
###########################################################################

#-------------------------------------------
# Create a standalone executable            
#-------------------------------------------

$(PRODUCT) : $(OBJS) $(PREBUILT_OBJS) $(LIBS) $(MAIN_OBJ)
	@echo "### Creating standalone executable "$(PRODUCT)" ..."
	$(LD) $(LDFLAGS) --output_file=$(PRODUCT) $(OBJS) $(MAIN_OBJ) $(LIBS) $(SYSTEM_LIBS) $(TOOLCHAIN_LIBS)
	@echo "### Created: $(PRODUCT)"


###########################################################################
## INTERMEDIATE TARGETS
###########################################################################

#---------------------
# SOURCE-TO-OBJECT
#---------------------

%.obj : %.cla
	$(CC) $(CFLAGS) --output_file="$@" "$<"


%.obj : %.c
	$(CC) $(CFLAGS) --output_file="$@" "$<"


%.obj : %.asm
	$(AS) $(ASFLAGS) --output_file="$@" "$<"


%.obj : %.cpp
	$(CPP) $(CPPFLAGS) --output_file="$@" "$<"


%.obj : $(RELATIVE_PATH_TO_ANCHOR)/%.cla
	$(CC) $(CFLAGS) --output_file="$@" "$<"


%.obj : $(RELATIVE_PATH_TO_ANCHOR)/%.c
	$(CC) $(CFLAGS) --output_file="$@" "$<"


%.obj : $(RELATIVE_PATH_TO_ANCHOR)/%.asm
	$(AS) $(ASFLAGS) --output_file="$@" "$<"


%.obj : $(RELATIVE_PATH_TO_ANCHOR)/%.cpp
	$(CPP) $(CPPFLAGS) --output_file="$@" "$<"


%.obj : $(START_DIR)/SignalGen4_ert_rtw/%.cla
	$(CC) $(CFLAGS) --output_file="$@" "$<"


%.obj : $(START_DIR)/SignalGen4_ert_rtw/%.c
	$(CC) $(CFLAGS) --output_file="$@" "$<"


%.obj : $(START_DIR)/SignalGen4_ert_rtw/%.asm
	$(AS) $(ASFLAGS) --output_file="$@" "$<"


%.obj : $(START_DIR)/SignalGen4_ert_rtw/%.cpp
	$(CPP) $(CPPFLAGS) --output_file="$@" "$<"


%.obj : $(START_DIR)/%.cla
	$(CC) $(CFLAGS) --output_file="$@" "$<"


%.obj : $(START_DIR)/%.c
	$(CC) $(CFLAGS) --output_file="$@" "$<"


%.obj : $(START_DIR)/%.asm
	$(AS) $(ASFLAGS) --output_file="$@" "$<"


%.obj : $(START_DIR)/%.cpp
	$(CPP) $(CPPFLAGS) --output_file="$@" "$<"


%.obj : $(MATLAB_ROOT)/rtw/c/src/%.cla
	$(CC) $(CFLAGS) --output_file="$@" "$<"


%.obj : $(MATLAB_ROOT)/rtw/c/src/%.c
	$(CC) $(CFLAGS) --output_file="$@" "$<"


%.obj : $(MATLAB_ROOT)/rtw/c/src/%.asm
	$(AS) $(ASFLAGS) --output_file="$@" "$<"


%.obj : $(MATLAB_ROOT)/rtw/c/src/%.cpp
	$(CPP) $(CPPFLAGS) --output_file="$@" "$<"


%.obj : $(MATLAB_ROOT)/simulink/src/%.cla
	$(CC) $(CFLAGS) --output_file="$@" "$<"


%.obj : $(MATLAB_ROOT)/simulink/src/%.c
	$(CC) $(CFLAGS) --output_file="$@" "$<"


%.obj : $(MATLAB_ROOT)/simulink/src/%.asm
	$(AS) $(ASFLAGS) --output_file="$@" "$<"


%.obj : $(MATLAB_ROOT)/simulink/src/%.cpp
	$(CPP) $(CPPFLAGS) --output_file="$@" "$<"


c2806xBoard_Realtime_Support.obj : C:/MATLAB/SupportPackages/R2016a/toolbox/target/supportpackages/tic2000/src/c2806xBoard_Realtime_Support.c
	$(CC) $(CFLAGS) --output_file="$@" "$<"


F2806x_CpuTimers.obj : C:/ti/controlSUITE/device_support/f2806x/v141/F2806x_common/source/F2806x_CpuTimers.c
	$(CC) $(CFLAGS) --output_file="$@" "$<"


F2806x_DefaultIsr.obj : C:/ti/controlSUITE/device_support/f2806x/v141/F2806x_common/source/F2806x_DefaultIsr.c
	$(CC) $(CFLAGS) --output_file="$@" "$<"


F2806x_GlobalVariableDefs.obj : C:/ti/controlSUITE/device_support/f2806x/v141/F2806x_headers/source/F2806x_GlobalVariableDefs.c
	$(CC) $(CFLAGS) --output_file="$@" "$<"


F2806x_PieCtrl.obj : C:/ti/controlSUITE/device_support/f2806x/v141/F2806x_common/source/F2806x_PieCtrl.c
	$(CC) $(CFLAGS) --output_file="$@" "$<"


F2806x_PieVect.obj : C:/ti/controlSUITE/device_support/f2806x/v141/F2806x_common/source/F2806x_PieVect.c
	$(CC) $(CFLAGS) --output_file="$@" "$<"


F2806x_SysCtrl.obj : C:/ti/controlSUITE/device_support/f2806x/v141/F2806x_common/source/F2806x_SysCtrl.c
	$(CC) $(CFLAGS) --output_file="$@" "$<"


F2806x_usDelay.obj : C:/ti/controlSUITE/device_support/f2806x/v141/F2806x_common/source/F2806x_usDelay.asm
	$(AS) $(ASFLAGS) --output_file="$@" "$<"


F2806x_CodeStartBranch.obj : C:/ti/controlSUITE/device_support/f2806x/v141/F2806x_common/source/F2806x_CodeStartBranch.asm
	$(AS) $(ASFLAGS) --output_file="$@" "$<"


F2806x_Dma.obj : C:/ti/controlSUITE/device_support/f2806x/v141/F2806x_common/source/F2806x_Dma.c
	$(CC) $(CFLAGS) --output_file="$@" "$<"


F2806x_Adc.obj : C:/ti/controlSUITE/device_support/f2806x/v141/F2806x_common/source/F2806x_Adc.c
	$(CC) $(CFLAGS) --output_file="$@" "$<"


c2806xSchedulerTimer0.obj : C:/MATLAB/SupportPackages/R2016a/toolbox/target/supportpackages/tic2000/src/c2806xSchedulerTimer0.c
	$(CC) $(CFLAGS) --output_file="$@" "$<"


###########################################################################
## DEPENDENCIES
###########################################################################

$(ALL_OBJS) : $(MAKEFILE) rtw_proj.tmw


###########################################################################
## MISCELLANEOUS TARGETS
###########################################################################

info : 
	@echo "### PRODUCT = $(PRODUCT)"
	@echo "### PRODUCT_TYPE = $(PRODUCT_TYPE)"
	@echo "### BUILD_TYPE = $(BUILD_TYPE)"
	@echo "### INCLUDES = $(INCLUDES)"
	@echo "### DEFINES = $(DEFINES)"
	@echo "### ALL_SRCS = $(ALL_SRCS)"
	@echo "### ALL_OBJS = $(ALL_OBJS)"
	@echo "### LIBS = $(LIBS)"
	@echo "### MODELREF_LIBS = $(MODELREF_LIBS)"
	@echo "### SYSTEM_LIBS = $(SYSTEM_LIBS)"
	@echo "### TOOLCHAIN_LIBS = $(TOOLCHAIN_LIBS)"
	@echo "### ASFLAGS = $(ASFLAGS)"
	@echo "### CFLAGS = $(CFLAGS)"
	@echo "### LDFLAGS = $(LDFLAGS)"
	@echo "### SHAREDLIB_LDFLAGS = $(SHAREDLIB_LDFLAGS)"
	@echo "### CPPFLAGS = $(CPPFLAGS)"
	@echo "### CPP_LDFLAGS = $(CPP_LDFLAGS)"
	@echo "### CPP_SHAREDLIB_LDFLAGS = $(CPP_SHAREDLIB_LDFLAGS)"
	@echo "### ARFLAGS = $(ARFLAGS)"
	@echo "### MEX_CFLAGS = $(MEX_CFLAGS)"
	@echo "### MEX_LDFLAGS = $(MEX_LDFLAGS)"
	@echo "### DOWNLOAD_FLAGS = $(DOWNLOAD_FLAGS)"
	@echo "### EXECUTE_FLAGS = $(EXECUTE_FLAGS)"
	@echo "### MAKE_FLAGS = $(MAKE_FLAGS)"


clean : 
	$(ECHO) "### Deleting all derived files..."
	$(RM) $(subst /,\,$(PRODUCT))
	$(RM) $(subst /,\,$(ALL_OBJS))
	$(RM) *Object
	$(ECHO) "### Deleted all derived files."


