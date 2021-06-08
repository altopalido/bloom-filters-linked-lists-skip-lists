#include <string.h>

#include "mytok.h"

char * getFirst(char * str) {
    return strtok(str, " ");
}

char * getNext() {
    return strtok(NULL, " ");
}

char * getRest() {
    return strtok(NULL, "");
}

char * getFirst1(char * str) {
    return strtok(str, "-");
}

char * getNext1() {
    return strtok(NULL, "-");
}