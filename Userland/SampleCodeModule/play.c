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

#define WIDTH 80
#define HEIGHT 25
static uint8_t * currentPlayer1Pos = (uint8_t*)0xB8000+1960; // cambiarlo
static uint8_t * currentPlayer2Pos = (uint8_t*)0xB8000+2040; //cambiarlo
static uint32_t playersPaintedPixels[HEIGHT * WIDTH] = {0};//Array que nos sirve para guardar el recorrido de los jugadores



int drawMovement(char c, int player);
//int checkCollision();
/**
 *         0 if no player crashed
 *         1 if Colision was caused by player 1
 *         2 if Colision was caused by player 2
 *         3 if both crashed
 */

uint32_t crash = 0;
//80 * 12 = 960
//960 * 2 = 1920
//20 * 2 = 40
//1920 + 40 = 1960 -> primera pos player1
//1920 + 120 = 2040 -> primera pos player2

void play(unsigned int fd){
    int ret = 0;
    char letter[1] = {0};
    char lastLetter1 = 's';
    char lastLetter2 = 'k';
    clear_screen();



    while(1){
        ret = read(1, letter, 1);
        if(ret <= 0 ){
            drawMovement(lastLetter1,1);
            drawMovement(lastLetter2,2);
        }
        if(ret > 0){
            if( letter[0]=='w' || letter[0]=='a' || letter[0]=='s' || letter[0]=='d'){
                drawMovement(letter[0],1);
                drawMovement(lastLetter2,2);
                lastLetter1 = letter[0];
            }
            else if( letter[0]=='j' || letter[0]=='k' || letter[0]=='l' || letter[0]=='i'){
                drawMovement(letter[0],2);
                drawMovement(lastLetter1,1);
                lastLetter2 = letter[0];
            }
            ret = 0;


            if(crash==1){
                break;
            }
        }
        sleepMiliseconds(65);
    }
}

int drawMovement(char c, int player){
	if(player==1){
        color background = RED;
        color foreground = RED;
		if(c=='d' || c=='D'){
            currentPlayer1Pos += 2;
            move(1,RIGHT,currentPlayer1Pos,foreground,background);
		}
		else if(c=='a' || c=='A'){
            currentPlayer1Pos -= 2;
            move(1,LEFT,currentPlayer1Pos,foreground,background);
		}
		else if(c=='w' || c=='W'){
            currentPlayer1Pos -= 2 * WIDTH;
            move(1,UP,currentPlayer1Pos,foreground,background);
		}
		else if(c=='s' || c=='S'){
            currentPlayer1Pos += 2 * WIDTH;
			move(1,DOWN,currentPlayer1Pos,foreground,background);
		}
        //checkCollision();
        playersPaintedPixels[((uint32_t)currentPlayer1Pos - 0xB8000)/2] = 1;

	}
	else{
        color background = BLUE;
        color foreground = BLUE;
		playersPaintedPixels[((uint32_t)currentPlayer2Pos - 0xB8000)/2] = 1;
		if(c=='l' || c=='L'){
            currentPlayer2Pos += 2;
			move(1,RIGHT,currentPlayer2Pos,foreground,background);
		}
		else if(c=='j' || c=='J'){
            currentPlayer2Pos -= 2;
			move(1,LEFT,currentPlayer2Pos,foreground,background);
		}
		else if(c=='i' || c=='I'){
            currentPlayer2Pos -= 2 * WIDTH;
			move(1,UP,currentPlayer2Pos,foreground,background);
		}
		else if(c=='k' || c=='K'){
            currentPlayer2Pos += 2 * WIDTH;
			move(1,DOWN,currentPlayer2Pos,foreground,background);
		}
	}
}
/*
cleanPlayersPaintedPixels(){
    for( int i=0 ; i<=(HEIGHT*WIDTH) ; i++ ){
        playersPaintedPixels[i]=0;
    }
}

int checkCollision(){
    if(playersPaintedPixels[((uint32_t)currentPlayer1Pos - 0xB8000)/2]==1){
        crash = 1;
    }
    if(playersPaintedPixels[((uint32_t)currentPlayer2Pos - 0xB8000)/2]==1){
        crash += 2;
    }
    if(crash!=0){
        cleanPlayersPaintedPixels();
    }
}*/