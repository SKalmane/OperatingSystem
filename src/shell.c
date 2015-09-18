#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/time.h>

const int LINE_MAX = 256;

enum {
    CMD_DATE,
    CMD_ECHO,
    CMD_EXIT,
    CMD_HELP,
    NUM_COMMANDS
} Commands;

int cmd_date(int argc, char *argv[]);
int cmd_echo(int argc, char *argv[]);
int cmd_exit(int argc, char *argv[]);
int cmd_help(int argc, char *argv[]);

struct commandEntry {
    char *name;
    int (*functionp)(int argc, char *argv[]);
} commands[] = {{"date", cmd_date},
                {"echo", cmd_echo},
                {"exit", cmd_exit},
                {"help", cmd_help}};

int isBlankSpace(char c) {
    return ((c == ' ') ||
            (c == '\n') ||
            (c == '\t'));
}

int createArgc(char line[LINE_MAX + 1]) {
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


int processLine(char line[LINE_MAX + 1]) {
    int i = 0;
    int argc = 0;
    char **argv;
    int numCommand;

    argc = createArgc(line);

    // Allocate the entire argv array
    argv = (char **)(malloc(argc*sizeof(char *)));

    allocateMemForArgv(argc, argv, line);
    
    populateArgvWithStrings(argv, line);

    /* fprintf(stdout, "Number of arguments is: %d\n", argc); */

    /* for(i = 0; i < argc; i++) { */
    /*     fprintf(stdout, "Argument number %d is: %s\n", i, argv[i]); */
    /* } */

    while(numCommand < NUM_COMMANDS) {
        if(!strcmp(argv[0], commands[numCommand].name)) {
            return commands[numCommand].functionp(argc, argv);
        }
        numCommand++;
    }
    
   if (!strncmp(line, "ls", LINE_MAX)) {
       fprintf(stdout, "your files here\n");

   } else {
       fprintf(stdout, "%s\n", line);
   }
   return 0;
}

int main(int argc, char *argv[]) {
   char line[LINE_MAX + 1];
   int c, index;

   // Print the prompt
   fprintf(stdout, "%s", "$ ");

   index = 0;
   c = fgetc(stdin);
   while (c > 0 && c != '\n' && index < LINE_MAX) {
      line[index++] = c;
      c = fgetc(stdin);
   }
   line[index] = '\0';

   if (ferror(stdin)) {
      fprintf(stderr, "error while reading line: %s\n", strerror(errno));
      return 1;

   } else {
      processLine(line);
      return 0;
   }
}

int cmd_date(int argc, char *argv[]) {
    /* int time = gettimeofday(); */
    return 0;
}

int cmd_echo(int argc, char *argv[]) {
    /* int time = gettimeofday(); */
    fprintf(stdout, "The command is echo\n");
    return 0;
}

int cmd_exit(int argc, char *argv[]) {
    /* int time = gettimeofday(); */
    return 0;
}

int cmd_help(int argc, char *argv[]) {
    /* int time = gettimeofday(); */
    return 0;
}
