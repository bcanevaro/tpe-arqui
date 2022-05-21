
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