#include <naiveConsole.h>

static uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base);

static char buffer[64] = { '0' };
static uint8_t * const video = (uint8_t*)0xB8000;
static uint8_t * currentVideo = (uint8_t*)0xB8000;
static const uint32_t width = 80;
static const uint32_t height = 25;

void ncPrint(const char * string)
{
	int i;

	for (i = 0; string[i] != 0; i++)
		ncPrintChar(string[i]);
}

void ncPrintChar(char character)
{
	ncPrintColorfulChar(character, L_GRAY, BLACK);
}

void ncNewline()
{
	do
	{
		ncPrintChar(' ');
	}
	while((uint64_t)(currentVideo - video) % (width * 2) != 0);
}

void ncBackspace() {
	currentVideo -= 2;
	*currentVideo = ' ';
	*(currentVideo + 1) = 0x07;
}

void ncPrintDec(uint64_t value)
{
	ncPrintBase(value, 10);
}

void ncPrintHex(uint64_t value)
{
	ncPrintBase(value, 16);
}

void ncPrintBin(uint64_t value)
{
	ncPrintBase(value, 2);
}

void ncPrintBase(uint64_t value, uint32_t base)
{
    uintToBase(value, buffer, base);
    ncPrint(buffer);
}

void ncClear()
{
	int i;

	for (i = 0; i < height * width; i++) {
		video[i * 2] = ' ';
		video[i * 2 + 1] = ( 0x00 | BLACK ) << 4 | L_GRAY;
	}
	currentVideo = video;
}

static uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base)
{
	char *p = buffer;
	char *p1, *p2;
	uint32_t digits = 0;

	//Calculate characters for each digit
	do
	{
		uint32_t remainder = value % base;
		*p++ = (remainder < 10) ? remainder + '0' : remainder + 'A' - 10;
		digits++;
	}
	while (value /= base);

	// Terminate string in buffer.
	*p = 0;

	//Reverse string in buffer.
	p1 = buffer;
	p2 = p - 1;
	while (p1 < p2)
	{
		char tmp = *p1;
		*p1 = *p2;
		*p2 = tmp;
		p1++;
		p2--;
	}

	return digits;
}

void prueba() {

}

void scroll() {
	uint8_t * currentVideoAux = video + width * 2;
	for (int i = 0; currentVideoAux <= currentVideo; currentVideoAux++, i++) {
		video[i] = *currentVideoAux;
	}
	prueba();
	currentVideo = currentVideo - width * 2;
	uint8_t * currentVideoAux2 = currentVideo;
	for (int i = 0; currentVideoAux2 <= currentVideoAux; currentVideoAux2 += 2, i += 2) {
		currentVideo[i] = ' ';
		currentVideo[i + 1] = ( 0x00 | BLACK ) << 4 | L_GRAY;
	}
}
 
void ncPrintColorfulChar(char c, color foreground, color background) {
	if ((uint32_t)currentVideo == (uint32_t)video + width * height * 2 - 2) {
		scroll();
	}
	*currentVideo = c;
	*(currentVideo + 1) = ( 0x00 | background ) << 4 | foreground;
	currentVideo += 2;
}

void ncPrintColorful(char * str, color foreground, color background) {
	for (int i = 0; str[i] != 0; i++) {
		ncPrintColorfulChar(str[i], foreground, background);
	}
}

void ncPrintColorfulDec(uint64_t value, color foreground, color background) {
	ncPrintColorfulBase(value, 10, foreground, background);
}

void ncPrintColorfulHex(uint64_t value , color foreground, color background) {
	ncPrintColorfulBase(value, 16, foreground, background);
}

void ncPrintColorfulBin(uint64_t value, color foreground, color background) {
	ncPrintColorfulBase(value, 2, foreground, background);
}

void ncPrintColorfulBase(uint64_t value, uint32_t base, color foreground, color background) {
    uintToBase(value, buffer, base);
    ncPrintColorful(buffer, foreground, background);
}

void ncColorfulNewline(color background) {
	do
	{
		ncPrintColorfulChar(' ', BLACK, background);
	}
	while((uint64_t)(currentVideo - video) % (width * 2) != 0);
}

void printRegisterFormat(uint64_t reg){
    uint64_t aux = reg;
    uint64_t zeroes =  16;
    
    while (aux) {
        aux = aux >> 4;
    	zeroes--;
    }

    for(int i = 0; i < zeroes; i++){
       ncPrintColorfulChar('0', RED, WHITE);
    }
  
    if (reg) {
       ncPrintColorfulHex(reg, RED, WHITE);
    }
}