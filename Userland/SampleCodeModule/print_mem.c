#include <libc.h>
#include <syscalls.h>

void print_mem(char * address){
    if (!is_valid_hex(address)) {
        char * error_message = "Invalid address. Address must be 64 bits long, written in valid hex.";
        write(2, error_message, strlen(error_message));
    }
    uint64_t * real_address = (uint64_t *) str_to_hex(address);

	uint8_t * to_print = (uint8_t *) real_address;
    for (int i=0; i < MEM_DUMP_LEN ; i++) {
		if (i > 0 && i % 4 == 0) {
			write(1, "\n", 1);
		}
		print_byte_from_mem(to_print);
		write(1, "   ", 3);
        to_print++;
    }
	write(1, "\n", 1);
}