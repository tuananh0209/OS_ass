#include <stdio.h>

#include "findsubstr.h"
#include "readline.h"

int main (int argc , char **argv){
    char line[100];
    while (read_line(line) > 0){
        int chk = find_sub_string(line , argv);
        printf("%d \n", chk);
    }
    // printf( "%s", argv[1]);
}