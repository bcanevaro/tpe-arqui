#include <naiveConsole.h>

#define STDOUT 1
#define STDERR 2
#define LEFTOUT 3
#define LEFTERR 4
#define RIGHTOUT 5
#define RIGHTERR 6

static uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base);

static char buffer[64] = { '0' };
static uint8_t * const video = (uint8_t*)0xB8000;
static uint8_t * currentVideo = (uint8_t*)0xB8000;
static const uint32_t width = 80;
static const uint32_t height = 25;

static const uint32_t semi_width = 39;
static uint8_t * const left = (uint8_t*)0xB8000;
static uint8_t * const right = (uint8_t*)0xB8052;
static uint8_t * currentLeft = (uint8_t*)0xB8000;
static int leftIndex = 0;
static int leftVerticalIndex = 0;
static int rightVerticalIndex = 0;
static int rightIndex = 0;
static uint8_t * currentRight = (uint8_t*)0xB8052;

static uint8_t * ncGetPosition(int x, int y) {
	return video + width * 2 * x + y * 2;
}

void ncStarSplitScreen() {
	for (int i = 0; i < height; i++) {
		uint8_t * ad = ncGetPosition(i, semi_width);
		*(ad) = '|';
		*(ad+1) = ( 0x00 | BLACK ) << 4 | YELLOW;
		ad = ncGetPosition(i, semi_width + 1);
		*(ad) = '|';
		*(ad+1) = ( 0x00 | BLACK ) << 4 | YELLOW;
	}
	currentVideo = video;
}

void ncPrint(int fd, const char * string)
{
	int i;

	for (i = 0; string[i] != 0; i++)
		ncPrintChar(fd, string[i]);
}

void ncPrintChar(int fd, char character)
{
	ncPrintColorfulChar(fd, character, L_GRAY, BLACK);
}

void ncNewline(int fd)
{
	ncColorfulNewline(fd, BLACK);
}

void ncBackspace() {
	currentVideo -= 2;
	*currentVideo = ' ';
	*(currentVideo + 1) = 0x07;
}

void ncPrintDec(int fd, uint64_t value)
{
	ncPrintBase(fd, value, 10);
}

void ncPrintHex(int fd, uint64_t value)
{
	ncPrintBase(fd, value, 16);
}

void ncPrintBin(int fd, uint64_t value)
{
	ncPrintBase(fd, value, 2);
}

void ncPrintBase(int fd, uint64_t value, uint32_t base)
{
    uintToBase(value, buffer, base);
    ncPrint(fd, buffer);
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

void scrollCompleteScreen() {
	uint8_t * currentVideoAux = video + width * 2;
	for (int i = 0; currentVideoAux <= currentVideo; currentVideoAux++, i++) {
		video[i] = *currentVideoAux;
	}
	currentVideo = currentVideo - width * 2;
	uint8_t * currentVideoAux2 = currentVideo;
	for (int i = 0; currentVideoAux2 <= currentVideoAux; currentVideoAux2 += 2, i += 2) {
		currentVideo[i] = ' ';
		currentVideo[i + 1] = ( 0x00 | BLACK ) << 4 | L_GRAY;
	}
}

void scrollLeft() {
	uint8_t * currentVideoAux = video + width * 2;
	for (int i = 0; currentVideoAux <= currentLeft; currentVideoAux++, i++) {
		if (i % (width * 2) == semi_width * 2) {
			currentVideoAux += 82;
			i += 82;
		}
		video[i] = *currentVideoAux;
	}
	currentLeft = currentLeft - semi_width * 2;
	uint8_t * currentVideoAux2 = currentLeft;
	for (int i = 0; currentVideoAux2 <= currentVideoAux; currentVideoAux2 += 2, i += 2) {
		currentLeft[i] = ' ';
		currentLeft[i + 1] = ( 0x00 | BLACK ) << 4 | L_GRAY;
	}
}
 
void ncPrintColorfulChar(int fd, char c, color foreground, color background) {
	if ((fd == 1 || fd == 2) && (uint32_t)currentVideo == (uint32_t)video + width * height * 2 - 2) {
		scrollCompleteScreen();
	} else if ((fd == 3 || fd == 4) && leftVerticalIndex == height - 1 && leftIndex == semi_width) {
		scrollLeft();
		leftVerticalIndex--;
		leftIndex = 0;
	} else if ((fd == 5 || fd == 6) && rightVerticalIndex == height - 1 && rightIndex == semi_width) {
		// scrollRight();	
		rightVerticalIndex--;
	}
	if (fd == 1) {
		*currentVideo = c;
		*(currentVideo + 1) = ( 0x00 | background ) << 4 | foreground;
		currentVideo += 2;
	} else if (fd == 3) {
		if (leftIndex == semi_width) {
			currentLeft += 82;
			leftIndex = 0;
			leftVerticalIndex++;
		}
		*currentLeft = c;
		*(currentLeft + 1) = ( 0x00 | background ) << 4 | foreground;
		currentLeft += 2;
		leftIndex++;
	} else if (fd == 5) {
		if (rightIndex == semi_width) {
			currentRight += 82;
			rightIndex = 0;
			rightVerticalIndex++;
		}
		*currentRight = c;
		*(currentRight + 1) = ( 0x00 | background ) << 4 | foreground;
		currentRight += 2;
		rightIndex++;
	}
	
}

void ncPrintColorful(int fd, char * str, color foreground, color background) {
	for (int i = 0; str[i] != 0; i++) {
		ncPrintColorfulChar(fd, str[i], foreground, background);
	}
}

void ncPrintColorfulDec(int fd, uint64_t value, color foreground, color background) {
	ncPrintColorfulBase(fd, value, 10, foreground, background);
}

void ncPrintColorfulHex(int fd, uint64_t value , color foreground, color background) {
	ncPrintColorfulBase(fd, value, 16, foreground, background);
}

void ncPrintColorfulBin(int fd, uint64_t value, color foreground, color background) {
	ncPrintColorfulBase(fd, value, 2, foreground, background);
}

void ncPrintColorfulBase(int fd, uint64_t value, uint32_t base, color foreground, color background) {
    uintToBase(value, buffer, base);
    ncPrintColorful(fd, buffer, foreground, background);
}

void ncColorfulNewline(int fd, color background) {
	int condition;
	do
	{ 
		ncPrintColorfulChar(fd, ' ', BLACK, background);
		if (fd == 1 || fd == 2) {
			condition = (uint64_t) (currentVideo - video) % (width * 2) != 0;
		} else if (fd == 3 || fd == 4) {
			condition = leftIndex < semi_width;
		} else if (fd == 5 || fd == 6) {
			condition = rightIndex < semi_width;
		}
	} while (condition);
}

// CAMBIAR ESTO
void printRegisterFormat(uint64_t reg){
    uint64_t aux = reg;
    uint64_t zeroes =  16;
    
    while (aux) {
        aux = aux >> 4;
    	zeroes--;
    }

    for(int i = 0; i < zeroes; i++){
       ncPrintColorfulChar(1, '0', RED, WHITE);
    }
  
    if (reg) {
       ncPrintColorfulHex(1, reg, RED, WHITE);
    }
}