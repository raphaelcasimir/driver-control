# Driver-Control

Small driver control sketch w/ serial interface, for 2 VNH-type drivers (most common ones with PWM input and 2 direction pins). Pins in #define...
**After uploading the code, type "help" in the command line for a command list**.

*Default baud rate: 115200* .

You will need the [SerialCommand](https://github.com/kroimon/Arduino-SerialCommand) library for it to work.
Download it and select "Add .zip library" in the sketch menu to install it.

![zip-library-install](https://www.arduino.cc/en/uploads/Guide/ImportLibraryFromZIPFile.png)

A good serial monitor is **cutecom** (`sudo apt install cutecom`).

On Ubuntu do this to access serial ports if you have issues:
```bash
sudo adduser $USER dialout
```
