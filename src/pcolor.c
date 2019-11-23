/**
Filename: pcolor.c (implementation of pcolor.h)
Description: Print character with some color in terminal
Prepared by: Asisten IF2110
Created at: 17/10/2019
**/

#include <stdio.h>
#include <string.h>
#include "pcolor.h"

void print_red(char *c)
{
    printf("%s%s", RED, c);
    printf("%s", NORMAL);
}

void print_green(char *c)
{
    printf("%s%s", GREEN, c);
    printf("%s", NORMAL);
}

void print_yellow(char *c)
{
    printf("%s%s", YELLOW, c);
    printf("%s", NORMAL);
}

void print_blue(char *c)
{
    printf("%s%s", BLUE, c);
    printf("%s", NORMAL);
}

void print_magenta(char *c)
{
    printf("%s%s", MAGENTA, c);
    printf("%s", NORMAL);
}

void print_cyan(char *c)
{
    printf("%s%s", MAGENTA, c);
    printf("%s", NORMAL);
}
