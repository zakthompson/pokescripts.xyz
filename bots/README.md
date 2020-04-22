# Pokemon Scripts for Arduino

## Introduction
Since the Nintendo Switch now supports USB controllers, some enterprising individuals reverse-engineered the Pokken Tournament Pro Pad firmware for use on microcontrollers. This repository is a collection of scripts which execute input loops on the controller that allow for automating repetitive tasks in Pokemon Sword & Shield, such as hosting raids and hatching eggs.

## Instructions
* You will need to have `avr-gcc` installed on your system
* In the `makefile`, change the `TARGET` to the script you'd like to build
* Ensure that the `MCU` is set the the appropriate chipset for your microcontroller (for example, `atmega16u2` for an Arduino UNO R3)
* Run `make`
* Flash the resulting `.hex` file to your microcontroller

The instructions for putting your microcontroller in DFU mode and flashing firmware differ depending on your hardware. If you are on a Mac and have `dfu-programmer` installed, you can use the `make flash` command to flash the `TARGET` hex to your board.

## Scripts
* **DaySkipper**: Auto day-skipper for skips up to 22280 days
* **DaySkipper_Unlimited**: DaySkipper but with no limit
* **Auto3DaySkipper**: Auto roll den to the 3rd day, SR and repeats
* **AutoLoto**: Infinite loto reward grinding
* **AutoFossil**: Shiny Fossil grinding
* **AutoHost**: Auto hosting raids, with optional fixed/random link code
* **TurboA**: A button masher (for digging duo)
* **WattFarmer**: Fast watt collector
* **BerryFarmer**: Fast berry farmer
* **BoxRelease**: Release all pokemon in PC boxes
* **EggCollector**: Automatically collect eggs
* **EggHatcher**: Batch hatch eggs
* **FriendDeleteAdd**: Quickly remove as many friends as you'd like, and optionally add more

Each of these have instructions written in the README in their folder. Several also have configuration options that you will need to set in the `Config.h` file in their folder.

## Pre-Compiled Hexes
In the build folder, you will find precompiled hexes for the scripts that don't require variables to be changed.  These include:
* Auto3DaySkipper_US
* AutoLoto_US
* AutoHost (No Link Code)
* AutoHostWithFriendAccept (No Link Code)
* AutoHostReroll (No Link Code)
* AutoHostRerollWithFriendAccept (No Link Code)
* TurboA
* BerryFarmer_US
* WattFarmer_US

**Note that these builds are for `atmega16u2` boards such as the Arduino UNO R3. They will not work if your board has a different chipset!**

## Contributing
Feel free to submit a pull-request with a clear explanation of what improvement you are adding. I will review it as quickly as I can.

## Credits
These scripts originate from various people, and have been tweaked, modified and optimized along the way. As more contribute, I'll try and keep this list up-to-date.

* [progmem](https://github.com/progmem)
* [shinyquagsire](https://github.com/shinyquagsire23)
* [bertrandom](https://github.com/bertrandom)
* [hoskinsw](https://github.com/hoskinsw)
* [brianuuuSonic](https://www.youtube.com/channel/UCHV0EP9TifKSo7RERIbY1QA)
* [plus](https://www.youtube.com/channel/UCHV0EP9TifKSo7RERIbY1QA)
* [Pedro](https://www.youtube.com/channel/UCHV0EP9TifKSo7RERIbY1QA)
