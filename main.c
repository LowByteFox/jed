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

int main(int argc, char **argv) {
    Buffer *b = loadFile(argv[1]);
    return 0;
}
