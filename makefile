#
#             LUFA Library
#     Copyright (C) Dean Camera, 2014.
#
#  dean [at] fourwalledcubicle [dot] com
#           www.lufa-lib.org
#
# --------------------------------------
#         LUFA Project Makefile.
# --------------------------------------

# MCU Types:
# at90usb1286 for Teensy 2.0++
# atmega16u2 for Arduino UNO R3
# atmega32u4 for Arduino Micro/Teensy 2.0

# TARGET Types:
# DaySkipper: Auto day skipper for skips up to 22280 days
# DaySkipper_Unlimited: DaySkipper but with no limit
# Auto3DaySkipper: Auto roll den to the 3rd day, SR and repeats
# AutoLoto: Infinite loto reward grinding
# AutoFossil: Shiny Fossil grinding
# AutoHost: Auto hosting raids, with optional fixed/random link code
# TurboA: A button masher (for digging duo)
# WattFarmer: Fast watt collector
# BerryFarmer: Fast berry farmer
# BoxRelease: Release all pokemon in PC boxes
# EggCollector: Automatically collect eggs
# EggHatcher: Batch hatch eggs
# FriendDeleteAdd: Quickly remove as many friends as you'd like, and optionally add more

MCU          = atmega16u2
ARCH         = AVR8
F_CPU        = 16000000
F_USB        = $(F_CPU)
OPTIMIZATION = s
TARGET       = AutoHost
SRC          = $(TARGET)/$(TARGET).c ./Config/Descriptors.c $(LUFA_SRC_USB)
LUFA_PATH    = ./LUFA
CC_FLAGS     = -DUSE_LUFA_CONFIG_HEADER -IConfig/
LD_FLAGS     =

# Default target
all:

# Include LUFA build script makefiles
include $(LUFA_PATH)/Build/lufa_core.mk
include $(LUFA_PATH)/Build/lufa_sources.mk
include $(LUFA_PATH)/Build/lufa_build.mk
include $(LUFA_PATH)/Build/lufa_cppcheck.mk
include $(LUFA_PATH)/Build/lufa_doxygen.mk
include $(LUFA_PATH)/Build/lufa_dfu.mk
include $(LUFA_PATH)/Build/lufa_hid.mk
include $(LUFA_PATH)/Build/lufa_avrdude.mk
include $(LUFA_PATH)/Build/lufa_atprogram.mk

.PHONY: flash
flash:
	sudo dfu-programmer $(MCU) erase || true
	sudo dfu-programmer $(MCU) flash $(TARGET).hex
	sudo dfu-programmer $(MCU) reset
