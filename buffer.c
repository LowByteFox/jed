#ifndef BUFFER_C
#define BUFFER_C

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char* string;
typedef struct {
    string buff;
    unsigned long buffSize;
    int *lines;
    int lineCount;
} Buffer;

char *readline() {
    char *buff = malloc(1);
    int len = 1;
    char tmp;

    while((tmp = fgetc(stdin)) && tmp != '\n') {
        buff[len - 1] = tmp;
        len++;
        buff = realloc(buff, len);
    }
    buff[len - 1] = 0;

    return buff;
}

string newString() {
    return malloc(1);
}

Buffer newBuffer() {
    return (Buffer) { .buff = newString(), .buffSize = 1, .lines = malloc(sizeof(int)), .lineCount = 1 };
}

#endif

