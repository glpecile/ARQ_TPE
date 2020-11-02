#include <chess.h>

void startGame(int mode){
    if(mode == 0)
        print("new game");
    if(mode == 1)
        print("continue");
    putChar('\n');
}