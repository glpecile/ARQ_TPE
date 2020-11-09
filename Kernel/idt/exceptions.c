/**
 * exceptions.c: Archivo aportado por la cátedra. 
 * Modificado para el manejo de excepciones pedidas. 
*/
#define ZERO_EXCEPTION_ID 0
#define INVALID_OPCODE_EXCEPTION_ID 6
#include <exceptions.h>

static char *regs_to_print[REG_SIZE] = {
	"R15: 0x", "R14: 0x", "R13: ", "R12: 0x", "R11: 0x", "R10: 0x", "R9: 0x",
	"R8: 0x", "RSI: 0x", "RDI: 0x", "RBP: 0x", "RDX: 0x", "RCX: 0x", "RBX: 0x",
	"RAX: 0x", "IP: 0x", "RSP: 0x"};
static void zero_division();
static void invalid_opcode();
void printreg(uint64_t *reg);
void returnToSnapshot(uint64_t *stackframe);
/**
 * Variables para el guardado del estado inicial del stack pointer y la posición del sampleCodeModuleAdress
 * para luego recuperar ese estado al realizar una interrupción.
 */
static uint64_t snapshotIP,
	snapshotSP;

void printError(char *message)
{
	sWrite(message, strlen(message), RED);
}

void initialStateSnapshot(uint64_t IP, uint64_t SP)
{
	snapshotIP = IP;
	snapshotSP = SP;
}

void exceptionDispatcher(int exception, uint64_t *stackframe)
{
	switch (exception)
	{
	case ZERO_EXCEPTION_ID:
		zero_division();
		break;
	case INVALID_OPCODE_EXCEPTION_ID:
		invalid_opcode();
		break;
	default:
		break;
	}
	printreg(stackframe);
	returnToSnapshot(stackframe);
}

void returnToSnapshot(uint64_t *stackframe)
{
	stackframe[REG_SIZE - 2] = snapshotIP; // RIP
	stackframe[REG_SIZE + 1] = snapshotSP; // RSP
}

// Función idéntica en funcionamiento a printreg.
void printreg(uint64_t *reg)
{
	char toPrint[30];
	for (int i = 0; i < REG_SIZE; i++)
	{
		print(regs_to_print[i]);
		uintToBase(reg[i], toPrint, 16);
		print(toPrint);
		putchar('\n', WHITE);
	}
	// Resta imprimir el RSP.
	print(regs_to_print[REG_SIZE - 1]);
	uintToBase(reg[REG_SIZE + 1], toPrint, 16); // Caso especial CS y flags.
	print(toPrint);
	putchar('\n', WHITE);
	printError("RESTARTING SHELL...\n");
}

void zero_division()
{
	printError("ERROR DIVISION BY ZERO EXCEPTION.\n");
}

void invalid_opcode()
{
	printError("ERROR INVALID OPERATION CODE EXCEPTION.\n");
}
