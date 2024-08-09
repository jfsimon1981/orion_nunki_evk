################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User/ch32v00x_it.c \
../User/main.c \
../User/ol_init.c \
../User/ol_lib.c \
../User/system_ch32v00x.c 

OBJS += \
./User/ch32v00x_it.o \
./User/main.o \
./User/ol_init.o \
./User/ol_lib.o \
./User/system_ch32v00x.o 

C_DEPS += \
./User/ch32v00x_it.d \
./User/main.d \
./User/ol_init.d \
./User/ol_lib.d \
./User/system_ch32v00x.d 


# Each subdirectory must supply rules for building sources it contributes
User/%.o: ../User/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv-none-embed-gcc -march=rv32ec -mabi=ilp32e -msmall-data-limit=0 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"/home/jeanfrancois/mrs_community-workspace/git/orion_nunki_evk/CH32V003F4P6_EVK/Debug" -I"/home/jeanfrancois/mrs_community-workspace/git/orion_nunki_evk/CH32V003F4P6_EVK/Core" -I"/home/jeanfrancois/mrs_community-workspace/git/orion_nunki_evk/CH32V003F4P6_EVK/User" -I"/home/jeanfrancois/mrs_community-workspace/git/orion_nunki_evk/CH32V003F4P6_EVK/Peripheral/inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


