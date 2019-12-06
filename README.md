# IoT Nixie Tube Clock

This is the code running in the nixie tube clock I have built. It runs on a ESP8266 module that can arbitrarily control each nixie tube and exposes an API as well as a web-interface to control different functionalities of the clock.

## How to use 

Create a new file named `wifi_credentials.h` with the following content: 

```C++
#define SSID "my-ssid"
#define PASS "my-password"
```

where you replace `my-ssid` with the SSID of the Wifi network you want to use and `my-password` with the corresponding password.

To compile and upload the program onto the microcontroller run `make` or `make all`. You might need to adjust the `ARCH` and `PORT` variables in the `Makefile` and the `arduino` binary needs to be in your `PATH`.

If you modify the web UI in `steering.html`, run `python3 render.py` before compiling and uploading the sketch. this will render the html into the c++ code so that it can be served.