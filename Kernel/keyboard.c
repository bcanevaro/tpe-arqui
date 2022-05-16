#include <keyboard.h>
#include <naiveConsole.h>

static int shift = 0;
static int caps_lock = 0;
static uint8_t lower[] = {
      0,   27, '1', '2', '3', '4', '5', '6', '7', '8', '9',  '0', '-', '=',
   	'\b','\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p',  '[', ']',
   	'\n',   0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',
      0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/',    0, '*',
      0,  ' ',   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,    0,   0,
      0,    0,   0,   0, '-',   0,   0,   0, '+',   0,   0,   0,    0,   0,
      0,    0,   0,   0,   0,   0
};
static uint8_t upper[] = {
      0,   27, '!', '@', '#', '$', '%', '^', '&', '*', '(',  ')', '_', '+',
   	'\b','\t', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',  '{', '}',
   	'\n',   0, 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '\"', '`',
      0, '|', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?',    0, '*',
      0,  ' ',   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,    0,   0,
      0,    0,   0,   0, '-',   0,   0,   0, '+',   0,   0,   0,    0,   0,
      0,    0,   0,   0,   0,   0
};
static uint8_t caps_lock_array[] = {
      0,   27, '1', '2', '3', '4', '5', '6', '7', '8', '9',  '0', '-', '=',
   	'\b','\t', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',  '[', ']',
   	'\n',   0, 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ';', '\'', '`',
      0, '\\', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', ',', '.', '/',    0, '*',
      0,  ' ',   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,    0,   0,
      0,    0,   0,   0, '-',   0,   0,   0, '+',   0,   0,   0,    0,   0,
      0,    0,   0,   0,   0,   0
};
// Maneja el RTC.
void keyboard_handler() {
	uint8_t scancode = read_port(0x60);
    if(scancode >= 128){
        if(scancode == 170 || scancode == 182){
            shift = 0;
        }
        return;
    }else if(scancode == 42 || scancode == 54){
        shift = 1;
    }else if(scancode == 58){
        caps_lock = !caps_lock;
    }else{
        if(shift){
            ncPrintChar(upper[scancode]);
        }else if(caps_lock){
            ncPrintChar(caps_lock_array[scancode]);
        }else{
            ncPrintChar(lower[scancode]);
        }
    }
}
