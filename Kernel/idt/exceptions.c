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

void printError(char *message)
{
	sWrite(message, strlen(message), RED);
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
}

// Función idéntica en funcionamiento a printreg.
void printreg(uint64_t *reg)
{
	char buffer[20];
	for (int i = 0; i < REG_SIZE; i++)
	{
		print(regs_to_print[i]);
		uintToBase(reg[i], buffer, 16);
		print(buffer);
		putchar('\n', WHITE);
	}
	// Resta imprimir el rsp.
	print(regs_to_print[REG_SIZE-1]);
	uintToBase(reg[15 + 3], buffer, 16);
	print(buffer);
}

void zero_division()
{
	printError("ERROR DIVISION POR CERO.\n");
}

void invalid_opcode()
{
	printError("ERROR CODIGO DE OPERACION INVALIDO.\n");
}
