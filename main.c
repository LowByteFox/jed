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

int main(int argc, char **argv) {
    Buffer b = loadFile(argv[1]);
    printBufferWithLines(b);
    return 0;
}
