# dash-rpi
Command line interface and update tools for SM Dashboard controller

## Setup

Enable I2C communication first:
```bash
sudo raspi-config
```
A good article about I2C on Raspberry Pi can be found [here](https://www.raspberrypi-spy.co.uk/2014/11/enabling-the-i2c-interface-on-the-raspberry-pi/).

If you use Ubuntu, you need to install `raspi-config` first:
```bash
sudo apt update
sudo apt install raspi-config
```

Make sure you have all the tools you need:
```bash
sudo apt update
sudo apt-get install git build-essential
```

## Usage

Install the command:
```bash
cd
git clone https://github.com/SequentMicrosystems/dash-rpi.git
cd dash-rpi/
sudo make install
```

Now you can access all the functions of the [Eight 24-Bit Analog Inputs DAQ](https://sequentmicrosystems.com/products/eight-24bit-analog-inputs-daq-8-layer-stackable-hat-for-raspberry-pi) through the command "24b8vin". Use -h option for help:
```bash
dash -h
```

If you clone the repository, any updates can be made with the following commands:
```bash
cd ~/dash-rpi/  
git pull
sudo make install
```
