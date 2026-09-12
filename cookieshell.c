#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int main() {

    printf("\e[2J\e[H");

    bool running = true;

    while (running) {
        char MainInput[256]; // allocates 256 bytes to MainInput 
        char Pointer[] = ">"; // pointer, deafault is ">"
        char PreCursor[] = "main"; // the array of chars printed before the pointer, default is "main"
        char User[] = "user"; // the user
        char UserSeperator = '@'; // the symbol between the username and the PreCursor when printed in the main promt, default is "@"

        printf("\e[38;2;130;200;200m%s\e[38;2;150;255;150m%c\e[38;2;0;150;150m%s\e[0m%s", User, UserSeperator, PreCursor, Pointer); // 130;200;200 . 150;255;255 . 0;150;150 . 255;255;255
	fgets(MainInput, sizeof(MainInput), stdin);
        
        if (strcmp(MainInput, "exit\n") == 0) {
	    running = false;
        }
        if (strcmp(MainInput, "clear\n") == 0) {
            printf("\e[2J\e[H");
        }
    }
    return 0;
} 

