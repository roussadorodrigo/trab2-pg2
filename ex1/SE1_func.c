#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "SE1_func.h"


char *splitField(char *str) {
    for (int i = 0; str[i] != '\n' && str[i] != '\0'; i++) {
        if (str[i] == ';') {
            str[i] = '\0';
            return &str[i + 1];
        }
    }
    return NULL;
}



void separatorUnify(char str[]) {
    int i = 0, space_before = 0, j = 0;

    while (isspace(str[i])) {
        i++;
    }

    while (str[i] != '\0') {
        if (isspace(str[i])) {
            if (!space_before) {
                str[j++] = ' ';
                space_before = 1;
            }
        } else {
            str[j++] = str[i];
            space_before = 0;
        }
        i++;
    }

    if (j > 0 && str[j - 1] == ' ') {
        j--;
    }
    str[j] = '\0';
}
