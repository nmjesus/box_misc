#include "include/utils.h"
#include <stdlib.h>

bool str_cmp(char *str1, char *str2) {
    while(*str1 != '\0' && *str2 != '\0') {
        if(*str1++ != *str2++) {
            return FALSE;
        }
    }
    return TRUE;
}

void error(char *msg) {
    perror(msg);
    exit(0);
}
