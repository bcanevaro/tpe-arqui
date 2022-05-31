#include <keyboard.h>
#include <scheduler.h>
#include <naiveConsole.h>
#include <signal.h>

static int shift = 0;
static int caps_lock = 0;
static uint8_t lower_array[] = {
      0,   27, '1', '2', '3', '4', '5', '6', '7', '8', '9',  '0', '-', '=',
   	  8,'\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p',  '[', ']',
   	'\n',   0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',
      0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/',    0, '*',
      0,  ' ',   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,    0,   0,
      0,    0,   0,   0, '-',   0,   0,   0, '+',   0,   0,   0,    0,   0,
      0,    0,   0,   0,   0,   0
};
static uint8_t upper_array[] = {
      0,   27, '!', '@', '#', '$', '%', '^', '&', '*', '(',  ')', '_', '+',
   	  8,'\t', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',  '{', '}',
   	'\n',   0, 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '\"', '`',
      0, '|', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?',    0, '*',
      0,  ' ',   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,    0,   0,
      0,    0,   0,   0, '-',   0,   0,   0, '+',   0,   0,   0,    0,   0,
      0,    0,   0,   0,   0,   0
};
static uint8_t caps_lock_array[] = {
      0,   27, '1', '2', '3', '4', '5', '6', '7', '8', '9',  '0', '-', '=',
   	  8,'\t', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',  '[', ']',
   	'\n',   0, 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ';', '\'', '`',
      0, '\\', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', ',', '.', '/',    0, '*',
      0,  ' ',   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,    0,   0,
      0,    0,   0,   0, '-',   0,   0,   0, '+',   0,   0,   0,    0,   0,
      0,    0,   0,   0,   0,   0
};

char buffer[256];
int actualDim = 0;

char * get_buffer(){
    return buffer;
}

int get_dim(){
    return actualDim;
}

void update_dim(int dim){
    actualDim = dim;
}

void keyboard_handler() {
	uint8_t scancode = read_port(0x60);
    if (scancode >= 128) {
        if (scancode == 170 || scancode == 182) {
            shift = 0;
        }
        return;
    } else if (scancode == 42 || scancode == 54) {
        shift = 1;
    } else if (scancode == 58) {
        caps_lock = !caps_lock;
    } else if (scancode == 1) { //ESC -> salir de pantalla dividida
        if (get_in_split_screen()) {
            ncStopSplitScreen();
            stop_split_screen();
        }
    } else if (scancode == 59) { //F1 -> termino proceso pantalla entera
        // if (!get_in_split_screen()) {
        //     kill_process(3);
        // }
    } else if (scancode == 60) { //F2 -> suspendo/reanudo proceso pantalla entera

    } else if (scancode == 61) { //F3 -> termino proceso pantalla izquierda

    } else if (scancode == 62) { //F4 -> suspendo/reanudo proceso pantalla izquierda

    } else if (scancode == 63) { //F5 -> termino proceso pantalla derecha

    } else if (scancode == 64) { //F6 -> suspendo/reanudo proceso pantalla derecha

    } else {
        if (lower_array[scancode] != 0) {
            char letter;
            if (shift) {
                letter = upper_array[scancode];
            } else if(caps_lock) {
                letter = caps_lock_array[scancode];
            } else {
                letter = lower_array[scancode];
            }
            if (actualDim < 256) {
                buffer[actualDim++] = letter;
            }
        }
    }
}
