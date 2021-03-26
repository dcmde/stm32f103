# STM32F103 Template

## About

Template to program and conveniently debug the STM32F103 mcu.

The template example

- blinks the on board led of the blue pill (pin PC13)
- uses the Serial Wire Debug Output (SWO) on PB3
- integrates FreeRTOS by default

## Installation

The installation procedure is explained in the `script` folder.

## Compiling and flashing

Start by creating a bin folder,

```
mkdir bin
cd bin
```

Run the following commands,

```
cmake ..
make
```

[Warning] For some unknown reason you have to do these commands twice when you compile for the first time.

Then you can flash the code,

```
make flash
```

You can use CLion as well. Once CLion is running go : File -> Import Project -> Import existing project.

Also configure the compiler : File -> Settings -> Build,Execution,Deployment -> Toolchain -> C Compiler

Here change to : /usr/bin/arm-none-eabi-gcc

If you are bored with the endless loop warning, go into : Settings -> Editor -> Inspections -> C/C++ -> Data flow
analysis -> Endless loop

The result should be:

```
Flashing ./build/template.bin
st-flash 1.5.1-31-g625f4cd
2019-08-03T17:07:51 INFO usb.c: -- exit_dfu_mode
2019-08-03T17:07:51 INFO common.c: Loading device parameters....
2019-08-03T17:07:51 INFO common.c: Device connected is: F1 Medium-density device, id 0x20036410
2019-08-03T17:07:51 INFO common.c: SRAM size: 0x5000 bytes (20 KiB), Flash: 0x20000 bytes (128 KiB) in pages of 1024 bytes
2019-08-03T17:07:51 INFO common.c: Attempting to write 2356 (0x934) bytes to stm32 address: 134217728 (0x8000000)
Flash page at addr: 0x08000800 erased
2019-08-03T17:07:51 INFO common.c: Finished erasing 3 pages of 1024 (0x400) bytes
2019-08-03T17:07:51 INFO common.c: Starting Flash write for VL/F0/F3/F1_XL core id
2019-08-03T17:07:51 INFO flash_loader.c: Successfully loaded flash loader in sram
  3/3 pages written
2019-08-03T17:07:51 INFO common.c: Starting verification of write complete
2019-08-03T17:07:51 INFO common.c: Flash written and verified! jolly good!
```

## Debugging

Sometimes I face problems when I don't use the -O0 flag for the compiler.

In the stm32f103-template folder.

```
$ stm-debug
```

Result should be:

```
./cmake-build-debug/template.elf
Open On-Chip Debugger 0.10.0
Licensed under GNU GPL v2
For bug reports, read
	http://openocd.org/doc/doxygen/bugs.html
Info : auto-selecting first available session transport "hla_swd". To override use 'transport select <transport>'.
Info : The selected transport took over low-level target control. The results might differ compared to plain JTAG/SWD
adapter speed: 1000 kHz
adapter_nsrst_delay: 100
none separate
Info : Unable to match requested speed 1000 kHz, using 950 kHz
Info : Unable to match requested speed 1000 kHz, using 950 kHz
Info : clock speed 950 kHz
Info : STLINK v2 JTAG v28 API v2 SWIM v7 VID 0x0483 PID 0x3748
Info : using stlink api v2
Info : Target voltage: 3.200523
Info : stm32f1x.cpu: hardware has 6 breakpoints, 4 watchpoints
GNU gdb (Ubuntu 8.1-0ubuntu3) 8.1.0.20180409-git
Copyright (C) 2018 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.  Type "show copying"
and "show warranty" for details.
This GDB was configured as "x86_64-linux-gnu".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<http://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
<http://www.gnu.org/software/gdb/documentation/>.
For help, type "help".
Type "apropos word" to search for commands related to "word"...
Reading symbols from ./cmake-build-debug/template.elf...done.
>>> 
```

Then use the arrow key up three times to select the command:

```
>>> target remote localhost:3333
```

Useful [link](http://openocd.org/doc/html/GDB-and-OpenOCD.html) for openocd.

## Log

Before doing that you need to connect the PB3 pin to the swo of the stlink.

If you have [this](https://www.waveshare.com/st-link-v2-stm8.htm) stlink no problems otherwise you have to do
this [hack](https://lujji.github.io/blog/stlink-clone-trace/).

The clock speed should be at 72MHz. In case you don't use this speed you have to change the flag in the stm-log function
with

```
tpiu config internal $LOG_NAME uart off 72000000 2000000
```

The clock you are using instead of 72000000 and maybe the 2000000.

Use the function in the stm32f103-template folder.

```
$ stm-log 
```

The output should look like that :

```
Start OpenOCD redirect log to : ./log/08:03:2019-17:30:03- 
Open On-Chip Debugger 0.10.0
Licensed under GNU GPL v2
For bug reports, read
	http://openocd.org/doc/doxygen/bugs.html
Info : auto-selecting first available session transport "hla_swd". To override use 'transport select <transport>'.
Info : The selected transport took over low-level target control. The results might differ compared to plain JTAG/SWD
adapter speed: 1000 kHz
adapter_nsrst_delay: 100
none separate
Info : Unable to match requested speed 1000 kHz, using 950 kHz
Info : Unable to match requested speed 1000 kHz, using 950 kHz
Info : clock speed 950 kHz
Info : STLINK v2 JTAG v28 API v2 SWIM v7 VID 0x0483 PID 0x3748
Info : using stlink api v2
Info : Target voltage: 3.200523
Info : stm32f1x.cpu: hardware has 6 breakpoints, 4 watchpoints
Start the trace using SWO on file : ./log/08:03:2019-17:30:03-
Start
Running... 0
Running... 1
Running... 2
```

You may have to reset manually the mcu. The log is saved in the log file that is created in the stm32f103-template
folder.

In order to see the log you can use [swo-tracer](https://github.com/ehkom/swo-tracer). You can add a name to the log in
addition of the timestamp. Example :

```
$ stm-log log_name
```

## Useful link

- swo tracer https://ehko.fr/index.php?post/2017/09/SWD-Trace-avec-un-STM32
- openocd http://openocd.org/doc/html/GDB-and-OpenOCD.html
- swo hack on stlink https://lujji.github.io/blog/stlink-clone-trace/

## Enjoy!
