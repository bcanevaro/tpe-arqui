#include <syscalls.h>
#include <libc.h>

#define DOWN    0
#define UP      1
#define LEFT    2
#define RIGHT   3

typedef int color;

#define BLACK 0x0
#define BLUE 0x1
#define GREEN 0x2
#define CYAN 0x3
#define RED 0x4
#define MAGENTA 0x5
#define BROWN 0x6
#define L_GRAY 0x7
#define GRAY 0x8
#define L_BLUE 0x9
#define L_GREEN 0xA
#define L_CYAN 0xB
#define L_RED 0xC
#define L_MAGENTA 0xD
#define YELLOW 0xE
#define WHITE 0xF

static uint8_t * currentPlayer1Pos = (uint8_t*)0xB8000+1960; // cambiarlo
static uint8_t * currentPlayer2Pos = (uint8_t*)0xB8000+2040; //cambiarlo
static uint32_t playersPaintedPixels[80 * 25] = {0};//Array que nos sirve para guardar el recorrido de los jugadores
static const uint32_t width = 80;
static const uint32_t height = 25;
//80 * 12 = 960
//960 * 2 = 1920
//20 * 2 = 40
//1920 + 40 = 1960 -> primera pos player1
//1920 + 120 = 2040 -> primera pos player2

void play(unsigned int fd){
    int ret = 0;
    char letter[1] = {0};
    clear_screen();
    while(1){
        ret = read(1, letter, 1);
        if(ret > 0){
            drawMovement(letter[0],1);
            drawMovement(letter[0],2);
            ret = 0;
        }    
    }
}

void drawMovement(char c, int player){
	if(player==1){
        color background = RED;
        color foreground = RED;
		playersPaintedPixels[((uint32_t)currentPlayer1Pos - 0xB8000)/2] = 1;
		if(c=='d' || c=='D'){
            move(1,RIGHT,currentPlayer1Pos,foreground,background);
		}
		else if(c=='a' || c=='A'){
            move(1,LEFT,currentPlayer1Pos,foreground,background);
		}
		else if(c=='w' || c=='W'){
            move(1,UP,currentPlayer1Pos,foreground,background);
		}
		else if(c=='s' || c=='S'){
			move(1,DOWN,currentPlayer1Pos,foreground,background);
		}
	}
	else{
        color background = BLUE;
        color foreground = BLUE;
		playersPaintedPixels[((uint32_t)currentPlayer2Pos - 0xB8000)/2] = 1;
		if(c=='l' || c=='L'){
			move(1,RIGHT,currentPlayer2Pos,foreground,background);
		}
		else if(c=='j' || c=='J'){
			move(1,LEFT,currentPlayer2Pos,foreground,background);
		}
		else if(c=='i' || c=='I'){
			move(1,UP,currentPlayer2Pos,foreground,background);
		}
		else if(c=='k' || c=='K'){
			move(1,DOWN,currentPlayer2Pos,foreground,background);
		}
	}
}