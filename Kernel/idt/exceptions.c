#define ZERO_EXCEPTION_ID 0
#define INVALID_OPCODE_EXCEPTION_ID 6
#include <exceptions.h>

static char *regs[REG_SIZE] = {
	"RAX: ", "RBX: ", "RCX: ", "RDX: ", "RBP: ", "RDI: ", "RSI: ",
	"R8: ", "R9: ", "R10: ", "R11: ", "R12: ", "R13: ", "R14: ", "R15: "};
static void zero_division();
static void invalid_opcode();

void exceptionDispatcher(int exception)
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
}

void zero_division() {
	// TODO Handler para manejar excepcíon.
}

void invalid_opcode() {
	// TODO

}
