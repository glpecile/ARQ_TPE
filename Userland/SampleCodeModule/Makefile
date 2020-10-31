include ../Makefile.inc

MODULE=0000-sampleCodeModule.bin
SOURCES=$(wildcard *.c)
SOURCES_ASM=$(wildcard libasm/*.asm)
SOURCES_LIBC=$(wildcard libc/*.c)
SOURCES_APPS=$(wildcard apps/*.c)

OBJECTS=$(SOURCES:.c=.o)
OBJECTS_ASM=$(SOURCES_ASM:.asm=.o)
OBJECTS_APPS=$(SOURCES_APPS:.c=.o)
OBJECTS_LIBC=$(SOURCES_LIBC:.c=.o)

all: $(MODULE)

$(MODULE): $(OBJECTS) $(OBJECTS_ASM) $(OBJECTS_APPS) $(OBJECTS_LIBC)
	$(LD) $(LDFLAGS) -T sampleCodeModule.ld -o ../$(MODULE) $^

%.o: %.c
	$(GCC) $(GCCFLAGS) -I./include -c $< -o $@

%.o : %.asm
	$(ASM) $(ASMFLAGS) $< -o $@

clean:
	rm -rf *.o libasm/*.o libc/*.o apps/*.o *.bin

.PHONY: all clean print
