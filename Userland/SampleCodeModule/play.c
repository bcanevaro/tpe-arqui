#include <syscalls.h>
#include <libc.h>

void getPlayersMoves(char key1,char key2){
    movePlayer(1,key1);
    movePlayer(2,key2);
}

movePlayer(int player,char key){
    sys_move(player,key);
}