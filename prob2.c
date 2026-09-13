#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define  SIZE 100

// *** Function Protoypes ***
char *newString(char *str, int size);
char showArray(char **strings);

int main(int argc, char *argv[]){
    char **strings = malloc((SIZE + 1) * sizeof(char *));
    char input[SIZE];
    char **nextString;
    char *inputChar;


    if (strings == NULL) {
        return 1;
    }

    nextString = strings;

    // Read input strings from stdin and replace the newline with a null terminator.
    while (nextString < strings + SIZE && fgets(input, sizeof(input), stdin) != NULL) {
        inputChar = input;
        while (*inputChar != '\0') {
            if (*inputChar == '\n') {
                *inputChar = '\0';
                break;
            }
            inputChar++;
        }

        // Use newString to allocate memory for the string and copy the input string into it.
        *nextString = newString(input, (int)strlen(input));

        // Check if malloc was successful. If it wasn't, use free to prevent memory leaks before exiting the program.
        if (*nextString == NULL) {
            char **allocatedString = strings;

            while (allocatedString < nextString) {
                free(*allocatedString);
                allocatedString++;
            }
            free(strings);
            return 1;
        }

        nextString++;
    }

    *nextString = NULL;
    showArray(strings);

    // Making sure to free the memory allocated for each string in the array before exiting the program to prevent memory leaks.
    nextString = strings;
    while (*nextString != NULL) {
        free(*nextString);
        nextString++;
    }

    // Almost forgot to free the memory allocated for strings variable since we allocated space on the heap for it this time.
    free(strings);
    return 0;
}

// Allocates memory for a string on the heap depending on the size of the input string. Returns a pointer to the new memory location.
// Checks if malloc was successful. If it wasn't, returns NULL.
char *newString(char *str, int size){
    char *copy = malloc((size + 1) * sizeof(char));

    if (copy != NULL) {
        strcpy(copy, str);
    }

    return copy;
}

// Uses pointer notation to iterate through the string array and prints each string. I wasn't sure what I needed to return so I just returned a null character.
// Prints until it reaches a NULL pointer in the array.
char showArray(char **strings){
    char **current = strings;

    while (*current != NULL) {
        printf("%s\n", *current);
        current++;
    }

    return '\0';
}
