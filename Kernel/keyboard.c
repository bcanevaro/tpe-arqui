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

#define INFOREG_REGISTER_COUNT 16
uint64_t inforeg_registers[INFOREG_REGISTER_COUNT];
char saved_inforeg_registers = 0;

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
        if (!get_in_unique_screen() && get_in_split_screen()) {
            ncStopSplitScreen();
            stop_split_screen();
        }
    } else if (scancode == 59) { //F1 -> termino proceso pantalla entera
        if (!get_in_split_screen() && get_in_unique_screen()) {
            kill_unique_process();
        }
    } else if (scancode == 60) { //F2 -> suspendo/reanudo proceso pantalla entera
        if (!get_in_split_screen() && get_in_unique_screen()) {
            suspend_unique_process();
        }
    } else if (scancode == 61) { //F3 -> suspendo/reanudo proceso pantalla izquierda
        if (!get_in_unique_screen() && get_in_split_screen()) {
            suspend_left_split_screen();
        }
    } else if (scancode == 62) { //F4 -> suspendo/reanudo proceso pantalla derecha
        if (!get_in_unique_screen() && get_in_split_screen()) {
            suspend_right_split_screen();
        }
    } else if (scancode == 68) { //F10 -> guardo registros para inforeg
        uint64_t * r = get_registers_for_inforeg();
        // Los tengo que copiar a otro vector porque el array que está en ASM se actualiza todo el tiempo
        for (int i = 0; i < INFOREG_REGISTER_COUNT; i++) {
            inforeg_registers[i] = r[i];
        }
        saved_inforeg_registers = 1;
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

uint64_t * get_inforeg_registers() {
    return inforeg_registers;
}

char get_saved_inforeg_registers() {
    return saved_inforeg_registers;
}
