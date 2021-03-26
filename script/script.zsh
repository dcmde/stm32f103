#! /bin/zsh
# Get the .bin file in the build folder.
BIN_FILE=$(find ./build -iname '*.bin')
# Display info.
echo "\e[32mFlashing $BIN_FILE\e[37m"
# Kill any instance of openocd running.
pkill openocd
# Falsh to the MCU.
sudo st-flash write $BIN_FILE 0x8000000


