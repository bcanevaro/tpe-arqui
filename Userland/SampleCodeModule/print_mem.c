#include <libc.h>

static uint32_t uint_to_base(uint64_t value, char * buffer, uint32_t base);

void print_mem(char * address){   
    if(strlen(address) != 18 || !is_valid_hex(address)){
        char * error_message = "Invalid address. Address must be 64 bits long.";
        write(2, error_message, strlen(error_message));
    }
    uint64_t * real_address = (uint64_t *) str_to_hex(address);

	uint8_t * to_print = (uint8_t *) real_address;
    for (int i=0; i < MEM_DUMP_LEN ; i++) {
		if (i > 0 && i % 4 == 0) {
			write(1, "\n", 1);
		}
		char buff[16];
		write(1, "0x", 2);
		uint32_t digits = uint_to_base((uint64_t) to_print, buff, BASE_HEX);
        write(1, buff, digits);
		write(1, "=", 1);
        digits = uint_to_base(*to_print, buff, BASE_HEX);
		if (digits == 1) {
        	write(1, "0", 1);
		}
        write(1, buff, digits);
		write(1, "   ", 3);
        to_print++;
    }
	write(1, "\n", 1);
}

// Retrieved from naiveConsole.c
static uint32_t uint_to_base(uint64_t value, char * buffer, uint32_t base){
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