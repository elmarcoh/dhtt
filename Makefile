
all: build upload

dhtt.esp32.esp32.ttgo-lora32-v1.bin: dhtt.ino
	arduino-cli compile --fqbn esp32:esp32:ttgo-lora32-v1

build: dhtt.esp32.esp32.ttgo-lora32-v1.bin

upload: build
	arduino-cli upload -p /dev/ttyUSB0 --fqbn esp32:esp32:ttgo-lora32-v1

clean:
	rm *.bin *.elf

tags:
	rm -f tags tags.cpp tags.ino &&\
	ctags -f tags.cpp --languages=c++ -R --sort=yes $$HOME/Arduino/**/*.cpp &&\
	ctags -f tags.ino --langmap=c++:.ino --sort=yes $$HOME/Arduino/**/*.ino &&\
	cat tags.cpp tags.ino | sort > tags &&\
	rm tags.cpp tags.ino
