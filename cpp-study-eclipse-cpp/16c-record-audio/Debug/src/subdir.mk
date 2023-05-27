################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/16c-record-audio.c \
../src/ZJF_Audio_Ctrl.c \
../src/ZJF_Audio_Record.c 

C_DEPS += \
./src/16c-record-audio.d \
./src/ZJF_Audio_Ctrl.d \
./src/ZJF_Audio_Record.d 

OBJS += \
./src/16c-record-audio.o \
./src/ZJF_Audio_Ctrl.o \
./src/ZJF_Audio_Record.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/16c-record-audio.d ./src/16c-record-audio.o ./src/ZJF_Audio_Ctrl.d ./src/ZJF_Audio_Ctrl.o ./src/ZJF_Audio_Record.d ./src/ZJF_Audio_Record.o

.PHONY: clean-src

