CROSS_COMPILE ?= arm-none-eabi-
CC := $(CROSS_COMPILE)gcc
AS := $(CROSS_COMPILE)as
CORTEX_M3 := -mcpu=cortex-m3
CORTEX_M4 := -mcpu=cortex-m4
CFLAGS = -fno-common -ffreestanding -O0 -std=gnu99 \
	 	 -gdwarf-2 -g3 -Wall -Werror \
	 	 -mthumb
QEMU := /Users/mizuho/buzz/qbuild/arm-softmmu/qemu-system-arm

#devices vendor
STM32 := STM32

#Naming your devices
STM32F103_X6_DEVICE := STM32F103x6

#Device using Cortex-M4 CPU.Otherwise, treated as Cortex-M3(in uni_def)
target_using_CM4_list :=

#For those devices that does not need CMSIS
target_NOT_using_CMSIS_list :=

#Universal Devices Defintion
include rules.mk

#Create corresponding device variable
$(eval $(call eval_all_variable,$(STM32F103_X6_DEVICE)))


define build_command
	mkdir -p $($(1)_RELEASE_DIR)
	$(CC) $(CFLAGS) $($(1)_CPU) -Wl,-T$($(1)_TARGET_ld) -nostartfiles \
		  $(addprefix -I,$($(1)_INC_DIR)) \
		  $(CORE_SOURCE) $($(1)_DEPENDENT_SOURCE) -o $($(1)_TARGET_elf)
	$(CROSS_COMPILE)objcopy -Obinary $($(1)_TARGET_elf) $($(1)_TARGET_bin)
	$(CROSS_COMPILE)objdump -S $($(1)_TARGET_elf) > $($(1)_TARGET_dump)
endef

define eval_build_command
$($(1)_TARGET):
	$(call build_command,$(1))
endef

#Create corresponding build command to the device
$(eval $(call eval_build_command,$(STM32F103_X6_DEVICE)))

#default target
PLAT ?= $(STM32F103_X6_DEVICE)

.PHONY:all target clean

all:  $($(STM32F103_X6_DEVICE)_TARGET) $($(STM32F103_X6_DEVICE)_TARGET)

target:
	$(call build_command,$(PLAT))

run:
	@$(QEMU) -M ? | grep stm32-f103c8 >/dev/null || exit
	@echo "Press Ctrl-A and then X to exit QEMU"
	@echo
	$(QEMU) -M stm32-f103c8 -nographic -kernel ./release/STM32F103x6/STM32F103x6.bin
	rm -f DAC_OUT_PUT*.txt

qemu: $($(STM32P103_DEVICE)_TARGET)
	@$(QEMU) -M ? | grep stm32-f103c8 >/dev/null || exit
	@echo "Press Ctrl-A and then X to exit QEMU"
	@echo
	$(QEMU) -M stm32-f103c8 -nographic -kernel $($(STM32P103_DEVICE)_TARGET_bin)

clean:
	rm -rf $(RELEASE_DIR)

