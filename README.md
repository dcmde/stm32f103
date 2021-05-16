# STM32F103 MicroSd

## About

In order to save data from the mcu it is very convenient to use a micro SD card adapter.

In my code I use the filesystem module available [here](http://elm-chan.org/fsw/ff/00index_e.html).

One of the most important thing to do when using this code is to take care of calling the `disk_timerproc()` every 10ms.
In my example I use a timer to do so.

