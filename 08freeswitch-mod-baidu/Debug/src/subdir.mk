################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/freeswitch-mod-baidu.cpp \
../src/mod_baidu_tts.cpp 

OBJS += \
./src/freeswitch-mod-baidu.o \
./src/mod_baidu_tts.o 

CPP_DEPS += \
./src/freeswitch-mod-baidu.d \
./src/mod_baidu_tts.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -I"D:\dev_workspace\c\c_study\cpp-ai-baidu-tts\src\include" -I"D:\dev_c_lib\linux\include\freeswitch" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


