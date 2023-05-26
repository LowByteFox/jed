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

int wipeLine(Buffer *b, int line) {
    if (b->lineCount < line) return 1;
    if (line <= 0) return 2;
    Buffer *copy = b;
    for (int i = 1; i < line; i++) copy = copy->next;
    copy->text = malloc(0);
    copy->text[0] = 0;
    return 0;
}

// 1 - found, 0 - not found
int findAndReplace(Buffer *b, char *target, char *replacement) {
    Buffer *copy = b;
    while (copy->next) {
        char *base = strstr(copy->text, target);
        if (base) {
            char *first = strndup(copy->text, base - copy->text); // getting length
            first = realloc(first, strlen(copy->text) + 1 +
                    (strlen(replacement) - strlen(target)));
            memcpy(first + (base - copy->text), replacement, strlen(replacement));
            char *end = strdup(copy->text + (base - copy->text + strlen(target)));
            memcpy(first + (base - copy->text + strlen(replacement)),
                    end, strlen(end));
            first[strlen(first)] = 0;
            free(copy->text);
            free(end);
            copy->text = first;
            return 1;
        }
        copy = copy->next;
    }
    return 0;
}

// 0 - found
int findAndReplaceLine(Buffer *b, int line, char *target, char *replacement) {
    if (b->lineCount < line) return 1;
    if (line <= 0) return 2;
    Buffer *copy = b;

    for (int i = 1; i < line; i++) {
        copy = copy->next;
    }
 
    char *base = strstr(copy->text, target);
    if (base) {
        char *first = strndup(copy->text, base - copy->text); // getting length
        first = realloc(first, strlen(copy->text) + 1 +
                (strlen(replacement) - strlen(target)));
        memcpy(first + (base - copy->text), replacement, strlen(replacement));
        char *end = strdup(copy->text + (base - copy->text + strlen(target)));
        memcpy(first + (base - copy->text + strlen(replacement)),
                end, strlen(end));
        first[strlen(first)] = 0;
        free(copy->text);
        free(end);
        copy->text = first;
        return 1;
    }

    return 3;
}

void findAndReplaceGlobal(Buffer *b, char *target, char *replacement) {
    Buffer *copy = b;
    while (copy->next) {
        char *base = strstr(copy->text, target);
        while (base) {
            char *first = strndup(copy->text, base - copy->text); // getting length
            first = realloc(first, strlen(copy->text) + 1 +
                    (strlen(replacement) - strlen(target)));
            memcpy(first + (base - copy->text), replacement, strlen(replacement));
            char *end = strdup(copy->text + (base - copy->text + strlen(target)));
            memcpy(first + (base - copy->text + strlen(replacement)),
                    end, strlen(end));
            first[strlen(first)] = 0;
            free(copy->text);
            free(end);
            copy->text = first;
            base = strstr(copy->text, target);
        }
        copy = copy->next;
    }
}

void appendMode(Buffer *b) {
    Buffer *copy = b;
    Buffer *end = giveMeLast(b);
    int stop = 0;
    int iter = 0;

    while (!stop) {
        char *in = readline();
        if (strlen(in) == 1 && in[0] == '.') {
            stop = 1;
            break;
        }

        if (strlen(in) == 2 && !strncmp(in, "\\.", 2)) {
            in = realloc(in, strlen(in));
            in[0] = '.';
            in[1] = 0;
        } else {
            if (!strncmp(in, "\\\\.", 3)) {
                memcpy(in, "\\.", 2);
                memcpy(in + 2, in + 3, strlen(in) - 3);
                in[strlen(in)-1] = 0;
            } else if (!strncmp(in, "\\.", 2)) {
                in[0] = '.';
                memcpy(in + 1, in + 2, strlen(in) - 2);
                in[strlen(in)-1] = 0;
            }
        }

        if (!iter) {
            end->text = realloc(end->text, strlen(end->text) + strlen(in) + 1);
            memcpy(end->text + strlen(end->text), in, strlen(in));
            end->text[strlen(end->text)] = 0;
            Buffer *new = malloc(sizeof(Buffer));
            new->text = NULL;
            new->next = NULL;
            end->next = new;
            end = end->next;
            iter++;
        } else {
            end->text = in;
            Buffer *new = malloc(sizeof(Buffer));
            new->text = NULL;
            new->next = NULL;
            end->next = new;
            end = end->next;
        }
    }
}

int main(int argc, char **argv) {
    Buffer *b = loadFile(argv[1]);
    appendMode(b);
    printBufferWithLines(b);
    return 0;
}
