#! /bin/zsh
sudo apt-get install -qq libusb-1.0-0-dev
sudo apt install -qq gcc-arm-none-eabi
git clone https://github.com/texane/stlink stlink
cd stlink
git checkout 625f4cd
make release
cd build/Release; sudo make install
#sudo cp build/Release/bin/st-* /usr/local/bin
#sudo cp --remove-destination build/Release/lib/libstlink.so* /usr/lib/
cd ../../etc/udev/rules.d
sudo cp 49-stlinkv* /etc/udev/rules.d/
sudo udevadm control --reload
cat command_line.txt >> ~/.zshrc
