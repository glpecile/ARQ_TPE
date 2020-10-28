/**
 *  Limpiamos un poco lo previamente establecido.
 */
#include <stdint.h>
#include <string.h>
#include <lib.h>
#include <moduleLoader.h>
#include <idtLoader.h>
#include <naiveConsole.h>
#include <rtcDriver.h>
#include <keyboardDriver.h>
#include <videoDriver.h>

#define WHITE 0xFFFFFF
#define BLACK 0x0

extern uint8_t text;
extern uint8_t rodata;
extern uint8_t data;
extern uint8_t bss;
extern uint8_t endOfKernelBinary;
extern uint8_t endOfKernel;

static const uint64_t PageSize = 0x1000;

static void *const sampleCodeModuleAddress = (void *)0x400000;
static void *const sampleDataModuleAddress = (void *)0x500000;

typedef int (*EntryPoint)();

void clearBSS(void *bssAddress, uint64_t bssSize)
{
	memset(bssAddress, 0, bssSize);
}

void *getStackBase()
{
	return (void *)((uint64_t)&endOfKernel + PageSize * 8 //The size of the stack itself, 32KiB
					- sizeof(uint64_t)					  //Begin at the top of the stack
	);
}

void *initializeKernelBinary()
{
	void *moduleAddresses[] = {
		sampleCodeModuleAddress,
		sampleDataModuleAddress};

	loadModules(&endOfKernelBinary, moduleAddresses);

	clearBSS(&bss, &endOfKernel - &bss);

	return getStackBase();
}

int main()
{
	load_idt();
	((EntryPoint)sampleCodeModuleAddress)();
	/*
	drawChar(10, 10, 'F', 1, WHITE, BLACK);
	// day of the week
	char *day_of_the_week[2];
	uintToBase(getTime(DAY_OF_THE_WEEK), day_of_the_week, 10);
	drawChar(10, 30, day_of_the_week[0], 1, WHITE, BLACK);
	drawChar(10, 30, day_of_the_week[1], 1, WHITE, BLACK);
	//hours
	drawChar(14, 60, getTime(HOURS), 1, WHITE, BLACK);
	// minutes
	drawChar(16, 90, getTime(MINUTES), 1, WHITE, BLACK);
	// seconds
	drawChar(18, 120, getTime(SECONDS), 1, WHITE, BLACK);
	*/
	// test de driver de teclado.

	keyboard_handler();

	while (1)
		;
	return 0;
}
