#include <syscalls.h>
#include <libc.h>
#include <help.h>
#include <divide_by_zero.h>
#include <invalid_opcode.h>
#include <inforeg.h>
#include <fibonacci.h>
#include <primes.h>
#include <datetime.h>
#include <clear.h>
#include <print_mem.h>

#define PRINT_MEM_POS 8
#define COMMS_LEN 9
#define MAX_ADDRESS_LEN 16
#define BUFFER_LEN 256
static char print_memory[] = "printmem ";
static char * commands[]={"help", "divide_by_zero", "invalid_opcode", "inforeg",  
                            "fibonacci", "primes", "datetime", "clear"};

typedef void (*Command)(unsigned int);
static Command commands_functions[] = {&help, &divide_by_zero, &invalid_opcode, &inforeg,  
                                        &fibonacci, &primes, &datetime, &clear};

void terminal();
void error();
int print_mem_validation(char * buffer);
int pipe_validation(char * buffer, int * func1, int * func2, char * address_1, char * address_2);
int command_validation(char * command, char * address);

void terminal() {
    flush_buffer();
    int pipe = 0;
    write(1, "$> ", 3);
    char letter[1] = {0};
    char buffer[BUFFER_LEN];
    int ret = 0;
    int i = 0;
    while(letter[0] != '\n'){
        ret = read(1, letter, 1);
        if(ret > 0){
            if(letter[0] == '\b'){
                if(i > 0){
                    write(1, letter, 1); 
                    i--;
                }
            } else if (letter[0] == '\t') {
            } else {
                write(1, letter, 1); 
                if(letter[0] == '|'){
                    pipe++;
                }
                buffer[i++] = letter[0];
            }
            ret = 0;
        }
    }
    buffer[i-1] = 0;
    if(buffer[0] == 0){ // Caso cuando tocamos enter
        return; 
    }
    if(pipe == 1){
        int func1, func2;
        char address_1[MAX_ADDRESS_LEN+1];
        char address_2[MAX_ADDRESS_LEN+1];
        if(pipe_validation(buffer, &func1, &func2, address_1, address_2)){
            start_split_screen();
            if(func1 != PRINT_MEM_POS && func2 != PRINT_MEM_POS){
                arguments arguments_left = {
                .integer = 3,
                .string = -1
                };
                arguments arguments_right = {
                    .integer = 5,
                    .string = -1
                };
                load_process(commands_functions[func1], &arguments_left);
                load_process(commands_functions[func2], &arguments_right);
                hibernate_process(2);
            }else if(func1 == PRINT_MEM_POS && func2 != PRINT_MEM_POS){
                arguments arguments_left = {3, address_1};
                arguments arguments_right = {
                    .integer = 5,
                    .string = -1
                };
                load_process(&print_mem, &arguments_left);
                load_process(commands_functions[func2], &arguments_right);
                hibernate_process(2);
            }else if(func1 != PRINT_MEM_POS && func2 == PRINT_MEM_POS){
                arguments arguments_left = {
                .integer = 3,
                .string = -1
                };
                arguments arguments_right = {5, address_2};
                load_process(commands_functions[func1], &arguments_left);
                load_process(&print_mem, &arguments_right);
                hibernate_process(2);
            }else{
                arguments arguments_left = {3, address_1};
                arguments arguments_right = {5, address_2};
                load_process(&print_mem, &arguments_left);
                load_process(&print_mem, &arguments_right);
                hibernate_process(2);
            }
        }else{
            error();
        }
    }else if(pipe == 0){
        int found = 0;
        for(int i = 0; !found && i < COMMS_LEN - 1; i++){
            if(strcmp(buffer, commands[i]) == 0){
                start_unique_screen();
                arguments function_arguments = {1, -1};
                load_process(commands_functions[i], &function_arguments);
                hibernate_process(2);
                found = 1;
            }
        }
        if(!found){
            if(print_mem_validation(buffer)){
                char mem_address[19];
                int print_mem_len = strlen(print_memory);
                int i = COMMS_LEN;
                int j;
                for(j = 0; buffer[i] != 0; i++, j++){
                    mem_address[j] = buffer[i];
                }
                mem_address[j] = 0;
                start_unique_screen();
                arguments function_arguments = {1, mem_address};
                load_process(&print_mem, &function_arguments);
                hibernate_process(2);
            }else{
                error();
            }
        }
    }else{
        error();
    }
}

void error(){
    char error_message[] = "Invalid command. Type \"help\" for the command list.\n";
    write(2, error_message, strlen(error_message));
}

int pipe_validation(char * buffer, int * func1, int * func2, char * address_1, char * address_2){
    char str1[BUFFER_LEN];
    char str2[BUFFER_LEN];
    int i = 0;
    int j = 0;
    int k = 0;
    while(buffer[i] != '|'){
        str1[j++] = buffer[i++];
    }
    if(str1[j-1] != ' ' && buffer[i+1] != ' '){
        return 0;
    }
    i += 2;
    while(buffer[i]){
        str2[k++] = buffer[i++];
    }
    str1[j-1] = 0;
    str2[k] = 0;
    *func1 = command_validation(str1, address_1);
    *func2 = command_validation(str2, address_2);
    // Si alguno de los dos no es un comando valido entonces debo retornar cero.
    if(*func1 == -1 || *func2 == -1){
        return 0;
    }
    return 1;
}

// Me devuelve la posicion del vector de punteros a funcion del 0 al 7
// si me devuelve 8 entonces es print_mem. Sino devuelve el -1;
int command_validation(char * command, char * address) {
    int found = -1;
    int i;
    for(i = 0; found == -1 && i < COMMS_LEN - 1; i++){
        if(strcmp(command, commands[i]) == 0){
            found = i;
        }
    }
    if(found == -1 && print_mem_validation(command)){
        found = PRINT_MEM_POS;
        int print_mem_len = strlen(print_memory);
        int i = print_mem_len;
        int j;
        for(j = 0; command[i] != 0; i++, j++){
            address[j] = command[i];
        }
        address[j] = 0;
    }
    return found;
}

// Printmem command verification
int print_mem_validation(char * buffer){
    int is_print_mem = 1;
    int i;
    int print_mem_len = strlen(print_memory);
    for(i = 0; buffer[i] != 0 && is_print_mem && i < print_mem_len; i++){
        if(buffer[i] != print_memory[i]){
            is_print_mem = 0;
        }
    }
    if(i < print_mem_len || buffer[i] != '0' || buffer[i+1] != 'x'){
        is_print_mem = 0;
    }
    if(!is_print_mem){
        return is_print_mem;
    }
    i += 2;
    int address_digits = 0;
    while(buffer[i]){
        address_digits++;
        i++;
    }
    if(address_digits == 0 || address_digits > MAX_ADDRESS_LEN){
        is_print_mem = 0;
    }
    return is_print_mem;
}