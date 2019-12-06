#ARCH = arduino:avr:uno
ARCH = esp8266:esp8266:nodemcuv2

PORT = /dev/ttyUSB0

all:
	arduino --upload --board $(ARCH) --port $(PORT) main.ino

port_enabled:
	chmod o+rw $(PORT)

.PHONY: all port_enabled