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

#define COMMS_LEN 9
#define MAX_ADDRESS_LEN 18
static char print_memory[] = "printmem ";
static char * commands[]={"help", "divide_by_zero", "invalid_opcode", "inforeg",  
                            "fibonacci", "primes", "datetime", "clear"};

typedef void (*Command)(unsigned int);
static Command commands_functions[] = {&help, &divide_by_zero, &invalid_opcode, &inforeg,  
                                        &fibonacci, &primes, &datetime, &clear};

void terminal();
void error();

// Falta el ctrl + c
void terminal(){
    /*
        1.1 Tenemos que printear esto "$> "
        1.2 El usuario no debe poder borrar el prompt
        2.1 Lectura de comandos. Detectar los siguientes comandos:
            divide_by_zero
            invalid_opcode
            help
            inforeg
            fibonacci
            primesPRINT_MEMme: imprime dia y hora del sistema
            clear
            * | *
        2.2 Con el enter 
    */
    int pipe = 0;
    write(1, "$> ", 3);
    char letter[1] = {0};
    char buffer[256];
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
        arguments arguments_left = {
            .integer = 3,
            .string = -1
        };
        arguments arguments_right = {
            .integer = 5,
            .string = -1
        };
        start_split_screen();
        load_process(&fibonacci, &arguments_left);
        load_process(&fibonacci, &arguments_right);
        hibernate_process(1);
    }else if(pipe == 0){
        int found = 0;
        for(int i = 0; !found && i < COMMS_LEN - 1; i++){
            if(strcmp(buffer, commands[i]) == 0){
                arguments function_arguments = {1, -1};
                load_process(commands_functions[i], &function_arguments);
                hibernate_process(1);
                found = 1;
            }
        }
        // Esto es para print_mem.
        if(!found){ // Si no es ninguno de los comandos guardados en el vector command_functions
            int is_print_mem = 1;
            int i;
            char mem_address[19];
            int print_mem_len = strlen(print_memory);
            for(i = 0; buffer[i] !=0 && is_print_mem && i < print_mem_len; i++){
                if(buffer[i] != print_memory[i]){
                    is_print_mem = 0;
                }
            }
            if(is_print_mem){
                int j;
                for(j = 0; buffer[i] != 0 && i < MAX_ADDRESS_LEN + print_mem_len; i++, j++){
                    mem_address[j] = buffer[i];
                }
                mem_address[j] = 0;
                arguments function_arguments = {1, mem_address};
                load_process(&print_mem, &function_arguments);
                hibernate_process(1);
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