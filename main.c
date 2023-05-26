#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./buffer.c"


int main(int argc, char **argv) {
    Buffer *b = loadFile(argv[1]);
    appendBufferToFile(b, argv[1]);
    return 0;
}
