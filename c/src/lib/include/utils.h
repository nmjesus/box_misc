#ifndef UTILS_H
#define UTILS_H
#endif

#ifndef bool
    typedef int bool;
    #define TRUE  1
    #define FALSE 0
#endif

bool str_cmp(char *str1, char *str2);
void error(char *msg); 
