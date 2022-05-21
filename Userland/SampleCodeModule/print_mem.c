#include <libc.h>

static uint32_t uint_to_base(uint64_t value, char * buffer, uint32_t base);

void print_mem(char * address){   
    if(strlen(address) != 18 || !is_valid_hex(address)){
        char * error_message = "Invalid address. Address must be 64 bits long.";
        write(2, error_message, strlen(error_message));
    }
    uint64_t * real_address = (uint64_t *) str_to_hex(address);
    
    for(int i = 0; i < MEM_DUMP_LEN; i += 8){
        char buffer[2];
        uint32_t digits = uint_to_base(real_address[i], buffer, BASE_HEX);
        write(1, buffer, digits);
    }
}
// Le pasas un algo y le decis que eque base esta y en buffer te devuelve un string de eso
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