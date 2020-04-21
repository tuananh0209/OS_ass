#include <stdio.h>
#include <string.h>

#include "findsubstr.h"
#include "readline.h"

int main (int argc , char **argv){
    char line[100] ="";
    char agr[100] = "";
  
    for (int i = 1 ; i < argc ; i++){
        if (i != 1) strcat(agr , " ");
        strcat(agr , argv[i]);
    }
    // printf("%s\n",agr);
    while (read_line(line) > 0){
        
        int chk = find_sub_string(line , agr);
        if (chk == 1) printf("%s\n", line);
    }
    // printf( "%s", argv[1]);
}