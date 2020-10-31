#define ZERO_EXCEPTION_ID 0
#define INVALID_OPCODE_EXCEPTION_ID 6
#include <exceptions.h>

static void zero_division();
static void invalid_opcode();

void exceptionDispatcher(int exception) {
	 switch (exception)
	 {
	 case ZERO_EXCEPTION_ID:
		 zero_division();
		 break;
	 case INVALID_OPCODE_EXCEPTION_ID:
	 	invalid_opcode();
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
