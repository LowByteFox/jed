#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./buffer.c"


int main(int argc, char **argv) {
    Buffer *b = loadFile(argv[1]);
    insertBufferToFile(b, argv[2]);
    return 0;
}
