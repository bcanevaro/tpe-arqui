#include <stdint.h>
#include <libc.h>
#include <syscalls.h>

#define REGITER_COUNT 16
#define REGISTER_NAME_LEN 4
static char * register_names[] = {"RAX=", "RBX=", "RCX=", "RDX=", "RBP=", "RDI=", "RSI=", "RSP=",
                                  " R8=", " R9=", "R10=", "R11=", "R12=", "R13=", "R14=", "R15="};

void print_regs(uint64_t registers[]) {
    char buffer[17];
    for (int i = 0; i < REGITER_COUNT; i++) {
        write(1, register_names[i], REGISTER_NAME_LEN);

        int digits = uint_to_base(registers[i], buffer, 16);
        for (int j = 0; j < 16 - digits; j++) {
            write(1, "0", 1);
        }
        write(1, buffer, digits);
        write(1, "\n", 1);
    }
    return;
}