#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./buffer.c"

void printBuffer(Buffer *b) {
    Buffer *copy = b;
    while (copy->next) {
        printf("%s\n", copy->text);
        copy = copy->next;
    }
}

void printBufferWithLines(Buffer *b) {
    Buffer *copy = b;

    char buff[12];
    sprintf(buff, "%d", b->lineCount);
    int width = strlen(buff);

    int i = 1;
    while (copy->next) {
        printf("%*d |%s\n", width, i, copy->text);
        copy = copy->next;
        i++;
    }
}

int printLine(Buffer *b, int line) {
    if (b->lineCount < line) return 1;

    if (line <= 0) return 2;

    Buffer *copy = b;

    for (int i = 1; i < line; i++) {
        copy = copy->next;
    }

    printf("%s\n", copy->text);
    return 0;
}

Buffer *removeLine(Buffer *b, int line) {
    if (b->lineCount < line) return b;
    if (line <= 0) return b;
    b->lineCount--;
    if (line == 1) return b->next;

    Buffer *copy = b;
    Buffer *prev = b;

    for (int i = 1; i < line; i++) {
        copy = copy->next;
        if (prev->next != copy) {
            prev = prev->next;
        }
    }

    prev->next = copy->next;

    return b;
}

Buffer *insertBefore(Buffer *b, int line) {
    if (b->lineCount < line) return b;
    if (line <= 0) return b;
    b->lineCount++;

    Buffer *new = malloc(sizeof(Buffer));
    new->text = malloc(1);
    new->text[0] = 0;

    if (line == 1) {
        new->lineCount = b->lineCount;
        new->next = b;
        return new;
    }

    Buffer *copy = b;
    Buffer *prev = b;
    for (int i = 1; i < line; i++) {
        copy = copy->next;
        if (prev->next != copy) {
            prev = prev->next;
        }
    }

    prev->next = new;
    new->next = copy;

    return b;
}

Buffer *insertAfter(Buffer *b, int line) {
    if (b->lineCount < line) return b;
    if (line <= 0) return b;
    b->lineCount++;

    Buffer *new = malloc(sizeof(Buffer));
    new->text = "";

    if (line == 1) {
        new->next = b->next;
        b->next = new;
        return b;
    }

    Buffer *copy = b;
    for (int i = 1; i < line; i++) {
        copy = copy->next;
    }

    new->next = copy->next;
    copy->next = new;

    return b;
}

int main(int argc, char **argv) {
    Buffer *b = loadFile(argv[1]);
    printBufferWithLines(b);
    return 0;
}
