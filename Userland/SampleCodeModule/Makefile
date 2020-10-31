include ../Makefile.inc

MODULE=0000-sampleCodeModule.bin
SOURCES=$(wildcard [^_]*.c)
SOURCES_ASM=$(wildcard libasm/*.asm)
SOURCES_APPS=$(wildcard apps/*.c)
SOURCES_LIBC=$(wildcard libc/*.c)

OBJECTS_ASM=$(SOURCES_ASM:.asm=.o)
OBJECTS_APPS=$(SOURCES_APPS:.c=.o)
OBJECTS_LIBC=$(SOURCES_LIBC:.c=.o)

all: $(MODULE)

$(MODULE): $(SOURCES) $(OBJECTS_ASM) $(OBJECTS_APPS) $(OBJECTS_LIBC)
	$(GCC) $(GCCFLAGS) -T sampleCodeModule.ld _loader.c $(SOURCES) $(OBJECTS_ASM) $(OBJECTS_APPS) $(OBJECTS_LIBC) -o ../$(MODULE)

%.o: %.c
	$(GCC) $(GCCFLAGS) -I./include -I./apps -I./libc -c $< -o $@

%.o : %.asm
	$(ASM) $(ASMFLAGS) $< -o $@

clean:
	rm -rf *.o asm/*.o apps/*.o libc/*.o

.PHONY: all clean print
