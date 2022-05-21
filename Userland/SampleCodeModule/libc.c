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

int str_to_num(char * str){
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
// 0x 0X
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