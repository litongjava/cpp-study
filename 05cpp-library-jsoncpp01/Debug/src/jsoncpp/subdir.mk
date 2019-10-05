################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/jsoncpp/jsoncpp_study_01.cpp 

OBJS += \
./src/jsoncpp/jsoncpp_study_01.o 

CPP_DEPS += \
./src/jsoncpp/jsoncpp_study_01.d 


# Each subdirectory must supply rules for building sources it contributes
src/jsoncpp/%.o: ../src/jsoncpp/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -I"D:\dev_workspace\c\c_study\cpp-library-jsoncpp01\src\include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


