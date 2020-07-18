##########################################################################################################################
# File automatically-generated by tool: [projectgenerator] version: [3.7.1] date: [Sun Jun 28 10:50:54 AST 2020] 
##########################################################################################################################

# ------------------------------------------------
# Generic Makefile (based on gcc)
#
# ChangeLog :
#	2017-02-10 - Several enhancements + project update mode
#   2015-07-22 - first version
# ------------------------------------------------

######################################
# target
######################################
TARGET = cranesupervisor


######################################
# building variables
######################################
# debug build?
DEBUG = 1
# optimization
ifeq ($(DEBUG), 1)
	OPT = -O0
  	BUILD_TYPE = Debug
else
	OPT = -Og
	BUILD_TYPE = Release
endif


#######################################
# paths
#######################################
# Build path
EXTENSIONS_DIR = $(shell pwd)
TOPFOLDER = $(EXTENSIONS_DIR)/../..
UROS_DIR = $(TOPFOLDER)/firmware/mcu_ws
BUILD_DIR = $(EXTENSIONS_DIR)/build
UROS_APP_FOLDER = $(EXTENSIONS_DIR)/apps/supervisor
######################################
# source
######################################
# C sources
C_SOURCES =  \
Src/main.c \
Src/stm32f4xx_it.c \
Src/stm32f4xx_hal_msp.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim_ex.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_uart.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc_ex.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ex.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ramfunc.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma_ex.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr_ex.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_exti.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pcd.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pcd_ex.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_usb.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_i2c.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_i2c_ex.c \
Src/system_stm32f4xx.c \
Src/freertos.c \
Src/stm32f4xx_hal_timebase_tim.c \
Middlewares/Third_Party/FreeRTOS/Source/croutine.c \
Middlewares/Third_Party/FreeRTOS/Source/event_groups.c \
Middlewares/Third_Party/FreeRTOS/Source/list.c \
Middlewares/Third_Party/FreeRTOS/Source/queue.c \
Middlewares/Third_Party/FreeRTOS/Source/stream_buffer.c \
Middlewares/Third_Party/FreeRTOS/Source/tasks.c \
Middlewares/Third_Party/FreeRTOS/Source/timers.c \
Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/heap_4.c \
Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.c \
Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os2.c \
lib/FreeRTOS-Plus-POSIX/source/FreeRTOS_POSIX_utils.c \
lib/FreeRTOS-Plus-POSIX/source/FreeRTOS_POSIX_clock.c \
lib/FreeRTOS-Plus-POSIX/source/FreeRTOS_POSIX_sched.c \
lib/FreeRTOS-Plus-POSIX/source/FreeRTOS_POSIX_unistd.c \
lib/FreeRTOS-Plus-POSIX/source/FreeRTOS_POSIX_pthread.c \
Src/custom_memory_manager.c \
Src/libatomic.c \
Src/allocators.c \
Src/FreeRTOS-openocd.c \
# Src/Apps/ros_interface.c \

CPP_SOURCES = \
$(UROS_APP_FOLDER)/app_starter.cpp \
$(UROS_APP_FOLDER)/actuator_manager.cpp \
$(UROS_APP_FOLDER)/actuators/ODrive/ODriveInterface.cpp \
$(UROS_APP_FOLDER)/ros_manager.cpp \
Src/Device/UART.cpp \
Src/cpp_allocators.cpp
#TODO: replace wildcard for all Src then exclude, example:
# $(wildcard Device/*.c) $(wildcard Device/*.cpp) \
# $(wildcard Apps/*.c) $(wildcard Apps/*.cpp) \
# $(wildcard Sensors/*.c) $(wildcard Sensors/*.cpp) \
# $(wildcard $(UROS_APP_FOLDER)/*.c) $(wildcard $(UROS_APP_FOLDER)/*.cpp) \
# C_SOURCES := $(wildcard src/*.cpp)
# C_SOURCES := $(filter-out src/bar.cpp, $(SRC_FILES))

# Removing heap4 manager while being polite with STM32CubeMX
TMPVAR := $(C_SOURCES)
C_SOURCES := $(filter-out Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/heap_4.c, $(TMPVAR))


# ASM sources
ASM_SOURCES =  \
startup_stm32f446xx.s


#######################################
# binaries
#######################################

# The gcc compiler bin path can be either defined in make command via GCC_PATH variable (> make GCC_PATH=xxx)
# either it can be added to the PATH environment variable.
CROSS_COMPILE_NAME_PREFIX=arm-none-eabi-
CROSS_COMPILE = $(TOPFOLDER)/toolchain/bin/$(CROSS_COMPILE_NAME_PREFIX)

ifdef GCC_PATH
CC = $(GCC_PATH)/$(CROSS_COMPILE_NAME_PREFIX)gcc
CPP = $(GCC_PATH)/$(CROSS_COMPILE_NAME_PREFIX)g++
AS = $(GCC_PATH)/$(CROSS_COMPILE_NAME_PREFIX)gcc -x assembler-with-cpp
CP = $(GCC_PATH)/$(CROSS_COMPILE_NAME_PREFIX)objcopy
SZ = $(GCC_PATH)/$(CROSS_COMPILE_NAME_PREFIX)size
else
CC = $(CROSS_COMPILE)gcc
CPP = $(CROSS_COMPILE)g++
AS = $(CROSS_COMPILE)gcc -x assembler-with-cpp
CP = $(CROSS_COMPILE)objcopy
SZ = $(CROSS_COMPILE)size
endif
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S
 
#######################################
# CFLAGS
#######################################
# cpu
CPU = -mcpu=cortex-m4

# fpu
FPU = -mfpu=fpv4-sp-d16

# float-abi
FLOAT-ABI = -mfloat-abi=hard

# mcu
MCU = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)

# macros for gcc
# AS defines
AS_DEFS = 

# C defines
C_DEFS =  \
-DUSE_HAL_DRIVER \
-DSTM32F446xx \
-D_TIMEVAL_DEFINED


# AS includes
AS_INCLUDES = \
-IInc

# C includes
C_INCLUDES =  \
-IInc \
-IDrivers/STM32F4xx_HAL_Driver/Inc \
-IDrivers/STM32F4xx_HAL_Driver/Inc/Legacy \
-IDrivers/CMSIS/Device/ST/STM32F4xx/Include \
-IDrivers/CMSIS/Include \
-IMiddlewares/Third_Party/FreeRTOS/Source/include \
-IMiddlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F \
-IMiddlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 \
-Ilib/FreeRTOS-Plus-POSIX/include \
-Ilib/FreeRTOS-Plus-POSIX/include/portable/empty_portable \
-Ilib/FreeRTOS-Plus-POSIX/include/portable \
-Ilib/include \
-Ilib/include/private \
-Ilib/include/FreeRTOS_POSIX \
-Ilib/MachineRX/machinerfx/include \
-I$(UROS_APP_FOLDER)

MICROROS_INCLUDES += $(shell find $(UROS_DIR)/install -name 'include' | sed -E "s/(.*)/-I\1/")
MICROROS_INCLUDES += -I$(EXTENSIONS_DIR)/lib/include
MICROROS_INCLUDES += -I$(EXTENSIONS_DIR)/lib/include/FreeRTOS_POSIX
MICROROS_INCLUDES += -I$(EXTENSIONS_DIR)/lib/include/private
MICROROS_INCLUDES += -I$(EXTENSIONS_DIR)/lib/FreeRTOS-Plus-POSIX/include
MICROROS_INCLUDES += -I$(EXTENSIONS_DIR)/lib/FreeRTOS-Plus-POSIX/include/portable
C_INCLUDES += $(MICROROS_INCLUDES)

COLCON_INCLUDES += $(EXTENSIONS_DIR)/lib//FreeRTOS-Plus-POSIX/include 
COLCON_INCLUDES += $(EXTENSIONS_DIR)/lib//include 
COLCON_INCLUDES += $(EXTENSIONS_DIR)/lib//include/private 
COLCON_INCLUDES += $(EXTENSIONS_DIR)/lib//include/FreeRTOS_POSIX 
COLCON_INCLUDES += $(EXTENSIONS_DIR)/lib//include/FreeRTOS_POSIX/sys
COLCON_INCLUDES += $(EXTENSIONS_DIR)/Inc
COLCON_INCLUDES += $(EXTENSIONS_DIR)/Drivers/STM32F4xx_HAL_Driver/Inc
COLCON_INCLUDES += $(EXTENSIONS_DIR)/Drivers/CMSIS/Device/ST/STM32F4xx/Include
COLCON_INCLUDES += $(EXTENSIONS_DIR)/Drivers/CMSIS/Include
COLCON_INCLUDES_STR := $(foreach x,$(COLCON_INCLUDES),$(x)\n)

# compile gcc flags
ASFLAGS = $(MCU) $(AS_DEFS) $(AS_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

CFLAGS = $(MCU) $(C_DEFS) $(C_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

ifeq ($(DEBUG), 1)
CFLAGS += -g -gdwarf-2 
endif

# Generate dependency information
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"

ARCHCPUFLAGS = $(MCU) $(C_DEFS) $(OPT) -Wall -fdata-sections -ffunction-sections

#######################################
# LDFLAGS
#######################################
# link script
LDSCRIPT = STM32F446ZETx_FLASH.ld

# libraries
LIBS = -lc -lm -lnosys -lstdc++ 

LIBDIR = 
LDFLAGS = $(MCU) -specs=nano.specs -T$(LDSCRIPT) $(LIBDIR) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections,--undefined=uxTopUsedPriority

# default action: build all
all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin

#######################################
# build micro-ROS
#######################################

arm_toolchain: $(EXTENSIONS_DIR)/arm_toolchain.cmake.in
	rm -f $(EXTENSIONS_DIR)/arm_toolchain.cmake; \
	cat $(EXTENSIONS_DIR)/arm_toolchain.cmake.in | \
		sed "s/@CROSS_COMPILE@/$(subst /,\/,$(CROSS_COMPILE))/g" | \
		sed "s/@FREERTOS_TOPDIR@/$(subst /,\/,$(TOPFOLDER))/g" | \
		sed "s/@ARCH_CPU_FLAGS@/\"$(ARCHCPUFLAGS)\"/g" | \
		sed "s/@ARCH_OPT_FLAGS@/\"$(ARCHOPTIMIZATION)\"/g" | \
		sed "s/@INCLUDES@/$(subst /,\/,$(COLCON_INCLUDES_STR))/g" \
		> $(EXTENSIONS_DIR)/arm_toolchain.cmake

colcon_compile: arm_toolchain
	cd $(UROS_DIR); \
	colcon build \
		--packages-ignore-regex=.*_cpp \
		--metas $(UROS_DIR)/colcon.meta $(UROS_APP_FOLDER)/app-colcon.meta \
		--cmake-args \
		-DCMAKE_POSITION_INDEPENDENT_CODE=OFF \
		-DTHIRDPARTY=ON \
		-DBUILD_SHARED_LIBS=OFF \
		-DBUILD_TESTING=OFF \
		-DCMAKE_BUILD_TYPE=$(BUILD_TYPE) \
		-DCMAKE_TOOLCHAIN_FILE=$(EXTENSIONS_DIR)/arm_toolchain.cmake \
		-DCMAKE_VERBOSE_MAKEFILE=ON; \

libmicroros: colcon_compile
	mkdir -p $(UROS_DIR)/libmicroros; cd $(UROS_DIR)/libmicroros; \
	for file in $$(find $(UROS_DIR)/install/ -name '*.a'); do \
		folder=$$(echo $$file | sed -E "s/(.+)\/(.+).a/\2/"); \
		mkdir -p $$folder; cd $$folder; ar x $$file; \
		for f in *; do \
			mv $$f ../$$folder-$$f; \
		done; \
		cd ..; rm -rf $$folder; \
	done ; \
	ar rc libmicroros.a *.obj; mkdir -p $(BUILD_DIR); cp libmicroros.a $(BUILD_DIR); ranlib $(BUILD_DIR)/libmicroros.a; \
	cd ..; rm -rf libmicroros;

colcon_compile_app:
	cd $(UROS_DIR); \
	colcon build \
		--packages-select cranesupervisor \
		--packages-ignore-regex=.*_cpp \
		--metas $(UROS_DIR)/colcon.meta $(UROS_APP_FOLDER)/app-colcon.meta \
		--cmake-args \
		-DCMAKE_POSITION_INDEPENDENT_CODE=OFF \
		-DTHIRDPARTY=ON \
		-DBUILD_SHARED_LIBS=ON \
		-DBUILD_TESTING=OFF \
		-DCMAKE_BUILD_TYPE=$(BUILD_TYPE) \
		-DCMAKE_TOOLCHAIN_FILE=$(EXTENSIONS_DIR)/arm_toolchain.cmake \
		-DCMAKE_VERBOSE_MAKEFILE=ON;

libmicroros_app: colcon_compile_app
	mkdir -p $(UROS_DIR)/libmicroros; cd $(UROS_DIR)/libmicroros; \
	for file in $$(find $(UROS_DIR)/install/ -name '*.a'); do \
		folder=$$(echo $$file | sed -E "s/(.+)\/(.+).a/\2/"); \
		mkdir -p $$folder; cd $$folder; ar x $$file; \
		for f in *; do \
			mv $$f ../$$folder-$$f; \
		done; \
		cd ..; rm -rf $$folder; \
	done ; \
	ar rc libmicroros.a *.obj; mkdir -p $(BUILD_DIR); cp libmicroros.a $(BUILD_DIR); ranlib $(BUILD_DIR)/libmicroros.a; \
	cd ..; rm -rf libmicroros;


#######################################
# build the application
#######################################
# list of objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(CPP_SOURCES:.cpp=.o)))
vpath %.cpp $(sort $(dir $(CPP_SOURCES)))

OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
OBJECTS += $(BUILD_DIR)/libmicroros.a

vpath %.c $(sort $(dir $(C_SOURCES)))
# list of ASM program objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))
vpath %.s $(sort $(dir $(ASM_SOURCES)))

# make rule cpp
$(BUILD_DIR)/%.o: %.cpp Makefile | $(BUILD_DIR) 
	$(CPP) -c $(CFLAGS) -std=c++14 -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.cpp=.lst)) $< -o $@  

# make rule c
$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR) 
	$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

# make rule asm
$(BUILD_DIR)/%.o: %.s Makefile | $(BUILD_DIR)
	$(AS) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) Makefile
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	$(SZ) $@

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(HEX) $< $@
	
$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(BIN) $< $@	
	
$(BUILD_DIR):
	mkdir $@		

#######################################
# clean up
#######################################
clean:
	-rm -fR $(BUILD_DIR);
  
#######################################
# dependencies
#######################################
-include $(wildcard $(BUILD_DIR)/*.d)

# *** EOF ***
