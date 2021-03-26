# Installation

The script `setup.zsh` installs

- `gcc-arm-none-eabi`
- `libusb-1.0-0-dev` used to communicate with the stlink
- https://github.com/texane/stlink implements CLI to control the ST-Link

Once the script has been run you can check if the installation was successful by connecting the ST-Link with the
STM32F1, then type,

```
st-info --probe
```

and the output should be like that,

```
Found 1 stlink programmers
 serial: 353f6f064d53373451131743
openocd: "\x35\x3f\x6f\x06\x4d\x53\x37\x34\x51\x13\x17\x43"
  flash: 65536 (pagesize: 1024)
   sram: 20480
 chipid: 0x0410
  descr: F1 Medium-density device
```