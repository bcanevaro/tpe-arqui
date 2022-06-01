#include <libc.h>
#include <syscalls.h>

#define MAX_MEMORY_ADDRESS 0xFFFFFFFF8

void print_mem(unsigned int fd, char * address){
    if (!is_valid_hex(address)) {
        char * error_message = "Invalid address. Address must be 64 bits long, written in valid hex.\n";
        write(fd + 1, error_message, strlen(error_message));
        return;
    }
    uint64_t * real_address = (uint64_t *) str_to_hex(address);
    if ((uint64_t) real_address > MAX_MEMORY_ADDRESS) {
        char * error_message = "Invalid address. Address must be lower than 0xFFFFFFFF8\n";
        write(fd + 1, error_message, strlen(error_message));
        return;
    }
	uint8_t * to_print = (uint8_t *) real_address;
    int memory_overflow = 0;
    for (int i=0; !memory_overflow && i < MEM_DUMP_LEN ; i++) {
        if ((uint64_t) to_print > MAX_MEMORY_ADDRESS) {
            memory_overflow = 1;
        } else {
            if (i > 0 && i % 4 == 0) {
                write(fd, "\n", 1);
            }
            print_byte_from_mem(fd, to_print);
            write(fd, "   ", 3);
            to_print++;
        }
    }
	write(fd, "\n", 1);
    if (memory_overflow) {
        char * error_message = "Stopped printing. Next address not mapped.\n";
        write(fd + 1, error_message, strlen(error_message));
    }
}