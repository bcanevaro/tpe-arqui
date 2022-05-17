include ../Makefile.inc

MODULE=0000-sampleCodeModule.bin
SOURCES=$(wildcard [^_]*.c)
MODULEELF=0000-sampleCodeModule.elf

all: $(MODULE)

$(MODULE): $(SOURCES)
	$(GCC) $(GCCFLAGS) -T sampleCodeModule.ld _loader.c $(SOURCES) -o ../$(MODULE)
	$(GCC) $(GCCFLAGS) -T sampleCodeModule.ld -Wl,--oformat=elf64-x86-64 _loader.c $(SOURCES) -o ../$(MODULEELF)
clean:
	rm -rf *.o

.PHONY: all clean print
