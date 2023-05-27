################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../eclipse-cpp-opencv-4.1.1-demo-01.cpp 

O_SRCS += \
../eclipse-cpp-opencv-4.1.1-demo-01.o 

CPP_DEPS += \
./eclipse-cpp-opencv-4.1.1-demo-01.d 

OBJS += \
./eclipse-cpp-opencv-4.1.1-demo-01.o 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"D:\dev_program\opencv-4.1.1\build\include" -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean--2e-

clean--2e-:
	-$(RM) ./eclipse-cpp-opencv-4.1.1-demo-01.d ./eclipse-cpp-opencv-4.1.1-demo-01.o

.PHONY: clean--2e-

