#include <syscalls.h>
#include <libc.h>

void help(unsigned int fd){
    char welcome_message[] = "--- CFL (Canevaro Flores Llanos) Kernel ---\n";
    char programs_message[] = "Available programs:\n";
    char divide_by_zero_message[] = "   divide_by_zero: verify Divide by Zero exception funtionality.\n";
    char invalid_opcode_message[] = "   invalid_opcode: verify Invalid Opcode exception funtionality.\n";
    char inforeg_message[] = "   inforeg: print registers values. To capture these values press F10 at any time.\n";
    char finonacci_message[] = "   fibonacci: obtain the numbers returned by the Fibonacci series.\n";
    char primes_message[] = "   primes: obtain all the prime numbers starting from 1.\n";
    char datetime_message[] = "   datetime: deploy the system datetime (GMT-3).\n";
    char clear_message[] = "   clear: clear the screen.\n";
    char printmem_message[] = "   print mem 0xADDRESS: deploy a 32 bytes long memory dump from the address specified as an argument.\n";
    write(fd, welcome_message, strlen(welcome_message));
    write(fd, programs_message, strlen(programs_message));
    write(fd, divide_by_zero_message, strlen(divide_by_zero_message));
    write(fd, invalid_opcode_message, strlen(invalid_opcode_message));
    write(fd, inforeg_message, strlen(inforeg_message));
    write(fd, finonacci_message, strlen(finonacci_message));
    write(fd, primes_message, strlen(primes_message));
    write(fd, datetime_message, strlen(datetime_message));
    write(fd, clear_message, strlen(clear_message));
    write(fd, printmem_message, strlen(printmem_message));
    return;
}