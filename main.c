#include <stdio.h>
#include <string.h>

#include "c11exponent.h"
#include "c13Lucas.h"
#include "c14square.h"

void handleInput(char type);

int main() {
    setbuf(stdout, NULL);

    char type[10];
    printf("Welcome to use this system!\n");
    while (1) {
        printf("Please input what you want to do:\n");
        printf("A、 C.1.1 Exponential operation in finite field\n");
        printf("B、 C.1.3 Lucas\n");
        printf("C、 C.1.4 method1 via q≡3 (mod 4)\n");
        printf("D、 C.1.4 method2 via q≡5 (mod 8)\n");
        printf("E、 C.1.4 method3 via Lucas\n");
        scanf("%s", type);
        if (strlen(type) > 1) { // invalid input found
            continue;
        } else if (strcmp(type, "Q") == 0) // quit
            break;
        else {
            handleInput(type[0]);
        }
    }
    printf("Bye");
    return 0;
}


void handleInput(char type) {
    switch (type) {
        case 'A':
            handleC11();
            break;
        case 'B':
            handleC13();
            break;
        case 'C':
            handleC14(1);
            break;
        case 'D':
            handleC14(2);
            break;
        case 'E':
            handleC14(3);
            break;
        default:
            printf("please input A~E.");
    }
}
