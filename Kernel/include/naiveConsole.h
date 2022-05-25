#ifndef NAIVE_CONSOLE_H
#define NAIVE_CONSOLE_H

#include <stdint.h>

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

void ncPrintColorfulChar(int fd, char c, color foreground, color background);
void ncPrintColorful(int fd, char * str, color foreground, color background);
void ncPrintColorfulDec(int fd, uint64_t value, color foreground, color background);
void ncPrintColorfulHex(int fd, uint64_t value , color foreground, color background);
void ncPrintColorfulBin(int fd, uint64_t value, color foreground, color background);
void ncPrintColorfulBase(int fd, uint64_t value, uint32_t base, color foreground, color background);
void ncColorfulNewline(int fd, color background);

void printRegisterFormat(uint64_t reg);

void ncPrint(int fd, const char * string);
void ncPrintChar(int fd, char character);
void ncNewline(int fd);
void ncPrintDec(int fd, uint64_t value);
void ncPrintHex(int fd, uint64_t value);
void ncPrintBin(int fd, uint64_t value);
void ncPrintBase(int fd, uint64_t value, uint32_t base);
void ncClear();
void ncBackspace();

void ncStarSplitScreen();

#endif