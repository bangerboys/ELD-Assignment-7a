CFLAGS = -mmcu=atmega328p -Os	
CC = avr-gcc
name = aslicode
objcp = avr-objcopy
ohex = -O ihex
dude = avrdude
carduino = -c arduino
patemega = -p atmega328p
root = -P /dev/ttyUSB0
lol = -b57600
rem = rm
mp3file = faltu

all: $(name).hex

compile: $(name).hex $(name).c
	$(CC) $(CFLAGS) -o $(name).elf $(name).c
	
$(name).hex: $(name).elf
	$(objcp) $(ohex) $(name).elf $(name).hex

$(name).elf: $(name).c
	$(CC) $(CFLAGS) -o $(name).elf $(name).c

clean:
	$(rem) -rf *.o *.hex *.elf

program: all
	$(dude) $(carduino) $(patemega) $(root) $(lol) -U flash:w:$(name).hex

cmd1: $(mp3file).mp3
	mplayer -ao pcm mp3file.mp3

cmd2: audiodump.wav
	sox -v 1.32 audiodump.wav -c 1 -r 80000 -u -1 audiodump-8000.wav

cmd3: audiodump-8000.wav
	./wav2c audiodump-8000.wav sounddata.h sounddata