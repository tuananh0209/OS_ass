#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "findsubstr.h"

// int main(int argc, char **argv){
//     char a[] = "1234";
//     char b[] = "13";
//     printf("%d \n",find_sub_string(a , b));
// }

int find_sub_string(const char *str, const char *sub){
    char *search = strstr(str, sub);
    if (search == NULL){
        return -1;
    } else {
        return 1;
    }
}