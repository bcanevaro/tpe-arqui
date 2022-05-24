#include <stdint.h>
#include <libc.h>
// returns 0 if str1 == str2; != 0 if str1 != str2
int strcmp(char * str1, char * str2){
    int i;
    for(i = 0; str1[i] && str2[i]; i++){
        if(str1[i] != str2[i]){
            return -1;
        }
        
    }
    if(str1[i] || str2[i]){
        return -1;
    }
    return 0;
}

int strlen(char * str){
    if(str == 0){
        return 0;
    }
    int i;
    for(i = 0; str[i] != 0; i++);
    return i;
}

int str_to_num (char * str) {
    int num = 0;
    for (int i = 0; str[i] != 0; i++) {
        if (str[i] < '0' || str[i] > '9' ) {
            return -1;
        }
        num *= 10;
        num += str[i] - '0';
    }
    return num;
}

uint64_t str_to_hex(char * str){
    int num = 0;
    for (int i = 2; str[i] != 0; i++) {
        num *= 16;
        if(str[i] == 'A' || str[i] == 'a'){
            num += 10;
        }else if(str[i] == 'B' || str[i] == 'b'){
            num += 11;
        }else if(str[i] == 'C' || str[i] == 'c'){
            num += 12;
        }else if(str[i] == 'D' || str[i] == 'd'){
            num += 13;
        }else if(str[i] == 'E' || str[i] == 'e'){
            num += 14;
        }else if(str[i] == 'F' || str[i] == 'f'){
            num += 15;
        }else{// if(str[i] >= '0' && str[i] <= '9'){
            num += str[i] - '0';
        }
    }
    return num;
}

int is_valid_hex(char * str){
    int i = 0;
    if(str[i++] != '0'){
        return 0;
    }
    if(str[i++] != 'x'){
        return 0;
    }
    for (; str[i] != 0; i++) {
        if( !(str[i] == 'A' || str[i] == 'a' || str[i] == 'B' || str[i] == 'b' || 
            str[i] == 'C' || str[i] == 'c' || str[i] == 'D' || str[i] == 'd'||
            str[i] == 'E' || str[i] == 'e' ||str[i] == 'F' || str[i] == 'f' ||
            (str[i] >= '0' && str[i] <= '9') ) ){
            return 0;
        }
    }
    return 1;
}

// Retorna longitud de cadena ó ERROR
int num_to_str(unsigned long long num, char * buffer, int bufferSize) {
    if (bufferSize <= 0) {
        return -1;
    }

    if (num == 0) {
        buffer[0] = '0';
        buffer[1] = '\0';
        return 1;
    }

    int isNeg = 0;
    if (num < 0) {
        buffer[0] = '-';
        num *= -1;
        isNeg = 1;
    }

    int digitCount = num_length(num);
    
    int startPos = digitCount + isNeg - 1;
    if (startPos + 1 > bufferSize) {
        return -1;
    }

    buffer[startPos+1] = '\0';
    for(int i = 0; i < digitCount; i++) {
        buffer[startPos - i] = num % 10 + '0';
        num /= 10;
    }
    return startPos + 1;
}

int num_length(unsigned long long num) {
    if (num < 0){
      num*=-1;
    }
    int length = 0;
    while (num > 0) {
        length++;
        num /= 10;
    }
    return length;
}

void sleep(int seconds) {
    int seconds_e = seconds_elapsed();
    for (int i = seconds_elapsed(); i < seconds_e + seconds; i = seconds_elapsed());
}

// Retrieved from naiveConsole.c
uint32_t uint_to_base(uint64_t value, char * buffer, uint32_t base)
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
