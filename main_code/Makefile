
# Put your stlink folder here so make burn will work.
STLINK=~/stlink/build/Release

# Put your STM32F4 library code directory here
STM_COMMON=../STM32F4xx_DSP_StdPeriph_Lib_V1.8.0

# Put your source files here (or *.c, etc)
SRCS=main.c system_stm32f4xx.c $(STM_COMMON)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_gpio.c $(STM_COMMON)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rcc.c

# Binaries will be generated with this name (.elf, .bin, .hex, etc)
PROJ_NAME=fairly_tale


# Normally you shouldn't need to change anything below this line!
#######################################################################################

CC=arm-none-eabi-gcc
OBJCOPY=arm-none-eabi-objcopy

CFLAGS  = -g -O2 -Wall -Tstm32_flash.ld 
CFLAGS += -mlittle-endian -mthumb -mcpu=cortex-m4 -mthumb-interwork -DUSE_STDPERIPH_DRIVER
CFLAGS += -mfloat-abi=hard -mfpu=fpv4-sp-d16
CFLAGS += -I.

# Include files from STM libraries
CFLAGS += -I$(STM_COMMON)/Utilities/STM32F4-Discovery
CFLAGS += -I$(STM_COMMON)/Libraries/CMSIS/Include -I$(STM_COMMON)/Libraries/CMSIS/Device/ST/STM32F4xx/Include
CFLAGS += -I$(STM_COMMON)/Libraries/STM32F4xx_StdPeriph_Driver/inc

# add startup file to build
SRCS += $(STM_COMMON)//Libraries/CMSIS/Device/ST/STM32F4xx/Source/Templates/TrueSTUDIO/startup_stm32f40xx.s 
OBJS = $(SRCS:.c=.o)


.PHONY: proj

all: proj

proj: $(PROJ_NAME).elf

$(PROJ_NAME).elf: $(SRCS)
	$(CC) $(CFLAGS) $^ -o $@ 
	$(OBJCOPY) -O binary $(PROJ_NAME).elf $(PROJ_NAME).bin

clean:
	rm -f *.o $(PROJ_NAME).elf $(PROJ_NAME).hex $(PROJ_NAME).bin

# Flash the STM32F4
burn: proj
	$(STLINK)/st-flash write $(PROJ_NAME).bin 0x8000000
