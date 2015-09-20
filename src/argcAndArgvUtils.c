#include <stdlib.h> //malloc

#include "argcAndArgvUtils.h"

const int LINE_MAX = 256;

int isBlankSpace(char c) {
    return ((c == ' ') ||
            (c == '\n') ||
            (c == '\t'));
}

int setArgc(char line[LINE_MAX + 1]) {
    int index = 0;
    int argc = 0;
    while(line[index] != '\0') {
        // Increment argc if there is a space between inputs
        if(isBlankSpace(line[index]) &&
           (index > 0) &&
           !isBlankSpace(line[index-1])) {
            argc++;
        }
        
        // Increment argc if this is the last input
        if(!isBlankSpace(line[index]) &&
           (line[index+1] == '\0')) {
            argc++;
        }

        index++;
    }
    return argc;
}

// Allocate memory for each input argument provided
void allocateMemForArgv(int argc, char *argv[], 
                        char line[LINE_MAX + 1]) {
    int index = 0;
    int i = 0;
    int stringLen = 0;

    while(line[index] != '\0') {
        stringLen++;
        if(isBlankSpace(line[index]) &&
           (index > 0) &&
           !isBlankSpace(line[index-1])) {
            argv[i] = (char *)(malloc((stringLen)*sizeof(char *)));
            i++;
            stringLen = 0;
        }
        
        // If this is the last input
        if(!isBlankSpace(line[index]) &&
           (line[index+1] == '\0')) {
            argv[i] = (char *)(malloc((stringLen)*sizeof(char *)));
            i++;
            stringLen = 0;
        }
        index++;
    }
}

void populateArgvWithStrings(char *argv[], 
                             char line[LINE_MAX + 1]) {
    int index = 0, stringLen = 0, numArg = 0;

    // Populate argv with the arguments
    while(line[index] != '\0') {
        
        if(!isBlankSpace(line[index])) {
            argv[numArg][stringLen] = line[index];
            stringLen++;
        }

        if(isBlankSpace(line[index]) &&
           (index > 0) &&
           !isBlankSpace(line[index-1])) {
            argv[numArg][stringLen+1] = '\0';
            numArg++;
            stringLen = 0;
        }
        
        // If it is the last input
        if(!isBlankSpace(line[index]) &&
           (line[index+1] == '\0')) {
            argv[numArg][stringLen+1] = '\0';
            numArg++;
            stringLen = 0;
        }
        index++;
    }
}

void deallocateArgv(int argc, char ***argv) {
  int i = 0;
  for(i = argc-1; i >= 0; i--) {
    free((*argv)[i]);
  }
  free(*argv);
  (*argv) = NULL;
}
