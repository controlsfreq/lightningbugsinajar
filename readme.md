# Readme #

The Lightning Bugs in a Jar (LBJ) application is used to control up to 8 LEDs and flash them randomly as if they were lightning bugs.

## Toolchain ##

* [WinAVR](http://sourceforge.net/projects/winavr/files/) - Compiler, linker, archiver, etc.
* [AvrDude](http://www.nongnu.org/avrdude/) - Programmer interface application.
* [LibUSB](http://sourceforge.net/projects/libusb-win32/) - USB driver for AvrDude which allows it to interface with the AVRISP mkII. Running `bin/inf-wizard.exe` will create a driver for a connected AVRISP mkII and install it.
* [Cygwin](https://www.cygwin.com) - Provides Make and a build environment.