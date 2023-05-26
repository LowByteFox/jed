#include <stdio.h>
#include <string.h>

#include "./buffer.c"

void printBuffer(Buffer b) {
    for (int i = 0; i < b.lineCount; i++) {
        int end = b.lines[i];
        if (end) {
            int start = b.lines[i - 1];
            char *str = strndup(b.buff + start, end - start - 1);
            printf("%s\n", str);
            free(str);
        }
    }
}

void printBufferWithLines(Buffer b) {
    char buff[12];
    sprintf(buff, "%d", b.lineCount);
    int width = strlen(buff);

    for (int i = 0; i < b.lineCount; i++) {
        int end = b.lines[i];
        if (end) {
            int start = b.lines[i - 1];
            char *str = strndup(b.buff + start, end - start - 1);
            printf("%*d |%s\n", width, i, str);
            free(str);
        }
    }
}

int printLine(Buffer b, int line) {
    if (b.lineCount < line) return 1;

    if (line <= 0) return 2;

    int start = b.lines[line - 1];
    int end = b.lines[line];
    char *str = strndup(b.buff + start, end - start - 1);
    printf("%s\n", str);
    free(str);

    return 0;
}

int main(int argc, char **argv) {
    Buffer b = loadFile(argv[1]);
    appendToBuffer(&b, argv[2]);
    printBufferWithLines(b);
    return 0;
}
