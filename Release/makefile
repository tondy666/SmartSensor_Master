################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include myUART/subdir.mk
-include mySPI/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
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
LSS += \
SmartSensor_Master.lss \

FLASH_IMAGE += \
SmartSensor_Master.hex \

EEPROM_IMAGE += \
SmartSensor_Master.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: SmartSensor_Master.elf secondary-outputs

# Tool invocations
SmartSensor_Master.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,SmartSensor_Master.map -mmcu=atmega2560 -o "SmartSensor_Master.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

SmartSensor_Master.lss: SmartSensor_Master.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S SmartSensor_Master.elf  >"SmartSensor_Master.lss"
	@echo 'Finished building: $@'
	@echo ' '

SmartSensor_Master.hex: SmartSensor_Master.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex SmartSensor_Master.elf  "SmartSensor_Master.hex"
	@echo 'Finished building: $@'
	@echo ' '

SmartSensor_Master.eep: SmartSensor_Master.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex SmartSensor_Master.elf  "SmartSensor_Master.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: SmartSensor_Master.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=berkeley -t SmartSensor_Master.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) SmartSensor_Master.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
