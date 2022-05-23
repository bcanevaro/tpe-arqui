#include <syscalls.h>
#include <libc.h>

int stop_help = 0;

void help(){
    char welcome_message[] = "CFL (Canevaro Flores Llanos) Kernel, version 1.0.\n";
    char programs_message[] = "Available programs:\n";
    char divide_by_zero_message[] = "Divide by zero: type 'divide_by_zero' to verify Divide by Zero exception's funtionality.\n";
    char invalid_opcode_message[] = "Invalid Opcode: type 'invalid_opcode' to verify Invalid Opcode exception's funtionality.\n";
    char inforeg_message[] = "Inforeg: type 'inforeg' to print registers' current values.\n";
    char finonacci_message[] = "Fibonacci: type 'fibonacci' to obtain the numbers returned by the Fibonacci sequence.\n";
    char primes_message[] = "Primes: type 'primes' to obtain all the prime numbers from 1.\n";
    char datetime_message[] = "Datetime: type 'datetime' to deploy the system datetime.\n";
    char clear_message[] = "Clear: type 'clear' to clear the screen\n";
    char printmem_message[] = "Print Memory: type 'print mem 0xADDRESS' to deploy a 32bytes long memory dump from the address specified as an argument.\n";
    write(1, welcome_message, strlen(welcome_message));
    write(1, programs_message, strlen(programs_message));
    write(1, divide_by_zero_message, strlen(divide_by_zero_message));
    write(1, invalid_opcode_message, strlen(invalid_opcode_message));
    write(1, inforeg_message, strlen(inforeg_message));
    write(1, finonacci_message, strlen(finonacci_message));
    write(1, primes_message, strlen(primes_message));
    write(1, datetime_message, strlen(datetime_message));
    write(1, clear_message, strlen(clear_message));
    write(1, printmem_message, strlen(printmem_message));
    return;
}