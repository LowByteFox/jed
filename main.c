#include <stdio.h>
#include <string.h>

#include "./buffer.c"

int main(int argc, char **argv) {
    Buffer b = loadFile(argv[1]);
    for (int i = 0; i < b.lineCount; i++) {
        int end = b.lines[i];
        if (end) {
            int start = b.lines[i - 1];
            char *str = strndup(b.buff + start, end - start - 1);
            printf("%s\n", str);
            free(str);
        }
    }
    return 0;
}
