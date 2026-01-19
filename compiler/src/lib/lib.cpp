//
// Created by abhilekh on 5/10/24.
//
#include "lib.h"
#include <cstdio>
#include <cstdlib>
#include <cstdarg>
#include <cstring>

extern "C" DECLSPEC void println(char* str, ...){
    char* outputStr;
    va_list argp;
    va_start(argp, str);
    outputStr = (char*) malloc(strlen(str) + 2);
    strcpy(outputStr, str);
    strcat(outputStr, "\n");
    std::vprintf(outputStr, argp);
    va_end(argp);
    free(outputStr);
 }
extern "C" DECLSPEC void print(char* str, ...){
    char* outputStr;
    va_list argp;
    va_start(argp, str);
    outputStr = (char*) malloc(strlen(str) + 2);
    strcpy(outputStr, str);
    std::vprintf(outputStr, argp);
    va_end(argp);
    free(outputStr);
}
extern "C" DECLSPEC void input_ints(int count, ...){
    va_list ap;
    va_start(ap, count);

    for(int i = 0 ; i < count ; ++i){
      int *p = va_arg(ap, int*);
      scanf("%d", p);
    }
    va_end(ap);
}
