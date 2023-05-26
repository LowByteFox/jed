#ifndef BUFFER_C
#define BUFFER_C

#include <inttypes.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *text;
    struct Node *next;
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

Buffer *loadFile(char *name) {
    FILE *f = fopen(name, "r");
    Buffer *buf = malloc(sizeof(Buffer));
    Buffer *orig = buf;

    buf->next = NULL;
    buf->text = NULL;

    char tmp;
    char *buff = malloc(1);
    int len = 1;

    while ((tmp = fgetc(f)) != EOF) {
        if (tmp != '\n') {
            buff[len - 1] = tmp;
            len++;
            buff = realloc(buff, len);
        } else {
            buf->text = buff;
            len = 1;
            buff = malloc(1);
            Buffer *next = malloc(sizeof(Buffer));
            buf->next = next;
            buf = buf->next;
        }
    }

    buf->next = NULL;
    buf->text = NULL;
    fclose(f);
    return orig;
}

void appendBufferToFile(Buffer *b, char *name) {
    Buffer *copy = b;
    FILE *o = fopen(name, "a");

    while(copy->next) {
        fprintf(o, "%s\n", copy->text);
        copy = copy->next;
    }

    fclose(o);
}

#endif

