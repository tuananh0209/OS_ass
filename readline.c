#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "readline.h"

// int main(int argc , char **argv){
//     char a[100] = "";
//     int i = 0;
//     while(i <4){
//     printf(" \n %d \n",read_line(a));
//     i++;
//     }
//     return 0;
// }

int read_line(char *str){
    int p = 0;
    int i = 0;
    char ch[100] = "";
    do {
        p = fgetc(stdin);
        char a[1] = {(char)p};
        if (p != '\n') {
            strncat(str , a , 1);
            strncat(ch, a, 1);
        }
       i++;
    }while (p != EOF && p != '\n');
    // printf("%s \n", str);
    // printf("%s \n", ch);
    if (p == EOF ) return -1;
    else {
        return i - 1;
    }
}