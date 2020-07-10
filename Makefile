
all: build upload

dhtt.esp32.esp32.ttgo-lora32-v1.bin: dhtt.ino
	arduino-cli compile --fqbn esp32:esp32:ttgo-lora32-v1

build: dhtt.esp32.esp32.ttgo-lora32-v1.bin

upload: build
	arduino-cli upload -p /dev/ttyUSB0 --fqbn esp32:esp32:ttgo-lora32-v1

clean:
	rm *.bin *.elf
