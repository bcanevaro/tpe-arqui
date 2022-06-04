#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#include <stdint.h>

char * get_buffer();
int get_dim();
void update_dim(int dim);
void keyboard_handler();

uint64_t * get_inforeg_registers();
char get_saved_inforeg_registers();

#endif