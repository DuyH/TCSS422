################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../cpu.c \
../dispatcher.c \
../isr.c \
../pcb.c \
../queue.c \
../scheduler.c 

OBJS += \
./cpu.o \
./dispatcher.o \
./isr.o \
./pcb.o \
./queue.o \
./scheduler.o 

C_DEPS += \
./cpu.d \
./dispatcher.d \
./isr.d \
./pcb.d \
./queue.d \
./scheduler.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


