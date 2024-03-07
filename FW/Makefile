
build:
	sjasmplus main.asm --syntax=F --inc

flash:
	PCProg.exe COM9 out.bin

clean:
	rm -f *.bin
	#rm -f user.l

.PHONY: all build clean