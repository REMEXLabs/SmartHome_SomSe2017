[![build status](https://gitlab.mi.hdm-stuttgart.de/health-hub/health-hub/badges/master/build.svg)](https://gitlab.mi.hdm-stuttgart.de/health-hub/health-hub/commits/master)

# Health Hub
An Arduino based device to scan and monitor various health parameters by simply placing the hand on the device.

## Arduino Libraries
The following third party Arduino libraries are used in this project:

* [OneWire](http://playground.arduino.cc/Learning/OneWire)
* [Arduino-Temperature-Control-Library](https://github.com/milesburton/Arduino-Temperature-Control-Library)
* [Fingerprint_Scanner-TTL](https://github.com/AndreasFliehr/Fingerprint_Scanner-TTL)
* [PulseSensorBPM](https://github.com/ninaschaaf/PulseSensorBPM)
* [Adafruit_NeoPixel] (https://github.com/td042/Adafruit_NeoPixel)

## Execution

To run this project locally the above mentioned libraries need to be initialized first. Therefore run `git submodule init` and `git submodule update` in that order.

For build and deployment this project uses the [Arduino-Makefile](https://github.com/sudar/Arduino-Makefile) by Sudar Muthu. For detailed instructions on how to use this makefile, please reference his Github repository.
To compile the source code run `make`, and to compile *and* upload run `make upload`.
