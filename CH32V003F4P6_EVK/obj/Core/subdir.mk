################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/core_riscv.c 

OBJS += \
./Core/core_riscv.o 

C_DEPS += \
./Core/core_riscv.d 


# Each subdirectory must supply rules for building sources it contributes
Core/%.o: ../Core/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv-none-embed-gcc -march=rv32ec -mabi=ilp32e -msmall-data-limit=0 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"/home/jeanfrancois/mrs_community-workspace/git/orion_nunki_evk/CH32V003F4P6_EVK/Debug" -I"/home/jeanfrancois/mrs_community-workspace/git/orion_nunki_evk/CH32V003F4P6_EVK/Core" -I"/home/jeanfrancois/mrs_community-workspace/git/orion_nunki_evk/CH32V003F4P6_EVK/User" -I"/home/jeanfrancois/mrs_community-workspace/git/orion_nunki_evk/CH32V003F4P6_EVK/Peripheral/inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


