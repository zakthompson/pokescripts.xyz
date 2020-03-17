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
# DaySkipper_US: Auto day skipper for US date arrangement (mm/dd/yyyy hh:mm:AM)
# DaySkipper_EU: Auto day skipper for EU date arrangement (dd/mm/yyyy hh:mm)
# DaySkipper_JP: Auto day skipper for JP date arrangement (yyyy/mm/dd hh:mm) **FASTEST**
# DaySkipper_US_NoLimit: DaySkipper_US but without 22280 days limit
# DaySkipper_EU_NoLimit: DaySkipper_EU but without 22280 days limit
# DaySkipper_JP_NoLimit: DaySkipper_JP but without 22280 days limit **FASTEST**
# Auto3DaySkipper: Auto roll den to the 4th day, SR and repeats
# AutoLoto: Infinite loto reward grinding
# AutoFossil: Shiny Fossil grinding
# AutoHost: Auto hosting raids, with optional fixed/random link code, using game restart to exit
# AutoHostAirplane: Auto hosting raids using airplane mode method to exit
# TurboA: A button masher (for digging duo)
# WattFarmer: Fast watt collector
# BerryFarmer: Fast berry farmer
# BoxRelease: Release all pokemon in PC boxes
# Hatcher: Automatically collect and hatch eggs

MCU          = atmega16u2
ARCH         = AVR8
F_CPU        = 16000000
F_USB        = $(F_CPU)
OPTIMIZATION = s
TARGET       = CHANGE_ME
SRC          = $(TARGET).c Descriptors.c $(LUFA_SRC_USB)
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
