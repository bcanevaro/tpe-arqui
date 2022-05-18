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

void ncPrintColorfulChar(char c, color foreground, color background);
void ncPrintColorful(char * str, color foreground, color background);
void ncPrintColorfulDec(uint64_t value, color foreground, color background);
void ncPrintColorfulHex(uint64_t value , color foreground, color background);
void ncPrintColorfulBin(uint64_t value, color foreground, color background);
void ncPrintColorfulBase(uint64_t value, uint32_t base, color foreground, color background);

void ncPrint(const char * string);
void ncPrintChar(char character);
void ncNewline();
void ncPrintDec(uint64_t value);
void ncPrintHex(uint64_t value);
void ncPrintBin(uint64_t value);
void ncPrintBase(uint64_t value, uint32_t base);
void ncClear();

#endif