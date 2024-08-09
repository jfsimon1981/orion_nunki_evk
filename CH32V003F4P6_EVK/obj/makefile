################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include User/subdir.mk
-include Startup/subdir.mk
-include Peripheral/src/subdir.mk
-include Debug/subdir.mk
-include Core/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
CH32V003F4P6_EVK.hex \

SECONDARY_LIST += \
CH32V003F4P6_EVK.lst \

SECONDARY_SIZE += \
CH32V003F4P6_EVK.siz \


# All Target
all: CH32V003F4P6_EVK.elf secondary-outputs

# Tool invocations
CH32V003F4P6_EVK.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU RISC-V Cross C Linker'
	riscv-none-embed-gcc -march=rv32ec -mabi=ilp32e -msmall-data-limit=0 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -T "/home/jeanfrancois/mrs_community-workspace/git/orion_nunki_evk/CH32V003F4P6_EVK/Ld/Link.ld" -nostartfiles -Xlinker --gc-sections -Wl,-Map,"CH32V003F4P6_EVK.map" --specs=nano.specs --specs=nosys.specs -o "CH32V003F4P6_EVK.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

CH32V003F4P6_EVK.hex: CH32V003F4P6_EVK.elf
	@echo 'Invoking: GNU RISC-V Cross Create Flash Image'
	riscv-none-embed-objcopy -O ihex "CH32V003F4P6_EVK.elf"  "CH32V003F4P6_EVK.hex"
	@echo 'Finished building: $@'
	@echo ' '

CH32V003F4P6_EVK.lst: CH32V003F4P6_EVK.elf
	@echo 'Invoking: GNU RISC-V Cross Create Listing'
	riscv-none-embed-objdump --all-headers --demangle --disassemble "CH32V003F4P6_EVK.elf" > "CH32V003F4P6_EVK.lst"
	@echo 'Finished building: $@'
	@echo ' '

CH32V003F4P6_EVK.siz: CH32V003F4P6_EVK.elf
	@echo 'Invoking: GNU RISC-V Cross Print Size'
	riscv-none-embed-size --format=berkeley "CH32V003F4P6_EVK.elf"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_UPPER_DEPS)$(C_DEPS) CH32V003F4P6_EVK.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets
