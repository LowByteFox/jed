#ifndef BUFFER_C
#define BUFFER_C

#include <stdio.h>
#include <stdlib.h>

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

void addCharacter(Buffer *b, char character) {
    b->buff[b->buffSize - 1] = character;
    b->buff = realloc(b->buff, b->buffSize + 1);
    b->buffSize++;
    b->buff[b->buffSize - 1] = 0;

    if (character == '\n') {
        b->lineCount++;
        b->lines = realloc(b->lines, b->lineCount * sizeof(int));
        b->lines[b->lineCount - 1] = b->buffSize - 1;
    }
}

Buffer loadFile(char *filename) {
    Buffer out = newBuffer();
    *out.lines = 0;
    FILE *f = fopen(filename, "r");
    char tmp;

    while ((tmp = fgetc(f) ) != EOF) {
        addCharacter(&out, tmp);
    }

    return out;
}

#endif

