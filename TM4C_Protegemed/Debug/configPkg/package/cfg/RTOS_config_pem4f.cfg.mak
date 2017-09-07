# invoke SourceDir generated makefile for RTOS_config.pem4f
RTOS_config.pem4f: .libraries,RTOS_config.pem4f
.libraries,RTOS_config.pem4f: package/cfg/RTOS_config_pem4f.xdl
	$(MAKE) -f C:\Users\skelter_win\Protegemed_tcc\TM4C_Protegemed/src/makefile.libs

clean::
	$(MAKE) -f C:\Users\skelter_win\Protegemed_tcc\TM4C_Protegemed/src/makefile.libs clean

