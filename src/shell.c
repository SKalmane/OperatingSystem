#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/time.h>
#include <assert.h>

// Local includes
#include "dateUtils.h"
#include "argcAndArgvUtils.h"

enum {
    CMD_DATE,
    CMD_ECHO,
    CMD_EXIT,
    CMD_HELP,
    NUM_COMMANDS
} Commands;

enum {
  NO_ERROR,
  ERROR_READING_LINE,
  INCORRECT_NUM_ARGUMENTS,
  NO_ARGUMENTS_SPECIFIED,
  COMMAND_NOT_FOUND
} ErrorCodes;

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

/* Function: compareStrings ==================
 * Returns 1 if the two input strings are 
 * equal and of the same length. Returns 0
 * otherwise.
 */
int compareStrings(char *str1, char *str2) {
  int equal = 1;
  int i = 0;
  while(str1[i] != '\0' && str2[i] != '\0') {
    if(str1[i] != str2[i]) {
      equal = 0;
      break;
    }
    i++;
  }

  if((str1[i] == '\0' && str2[i] != '\0') ||
     (str1[i] != '\0' && str2[i] == '\0')) {
    equal = 0;
  }  
  return equal;
}

int processLine(char line[LINE_MAX + 1]) {
    int i = 0;
    int argc = 0;
    char **argv;
    int numCommand = 0;
    int status = 0;
    
    argc = setArgc(line);

    // Allocate the entire argv array
    argv = (char **)(malloc(argc*sizeof(char *)));

    allocateMemForArgv(argc, argv, line);
    
    populateArgvWithStrings(argv, line);

    while(numCommand < NUM_COMMANDS) {
        if(compareStrings(argv[0], commands[numCommand].name)) {
            status = commands[numCommand].functionp(argc, argv);
	    break;
        }
        numCommand++;
    }

    if(numCommand == NUM_COMMANDS) {
      // Command not found
      status = COMMAND_NOT_FOUND;
    }
    
    deallocateArgv(argc, &argv);

    return status;
}

void handleError(int status) {
  switch (status) {
  case NO_ERROR:
    assert("handleError should not be called when there's no error to be thrown! \n");
    break;
  case ERROR_READING_LINE:
    fprintf(stderr, "error while reading line: %s\n", strerror(status));
    break;
  case INCORRECT_NUM_ARGUMENTS:
    fprintf(stderr, "Error code %d: Incorrect number of arguments specified\n", status);
    break;
  case NO_ARGUMENTS_SPECIFIED:
    fprintf(stderr, "Error code %d: No arguments specified when arguments were expected\n", status);
    break;
  case COMMAND_NOT_FOUND:
    fprintf(stderr, "Error code %d: Command not found. Type help to show supported commands\n", status);
    break;
  default:
    fprintf(stderr, "%s\n", strerror(status));
    break;
  };
}

int getAndProcessInput() {
  char line[LINE_MAX + 1];
  int c = 0, index = 0;
  int status = 0;
  
  // Print the prompt
  fprintf(stdout, "%s", "$ ");
  c = fgetc(stdin);
  while (c > 0 && c != '\n' && index < LINE_MAX) {
    line[index++] = c;
    c = fgetc(stdin);
  }
  line[index] = '\0';
  
  if (ferror(stdin)) {
    status = ERROR_READING_LINE;    
  } else {
    status = processLine(line);
  }

  if(status != NO_ERROR) {
    handleError(status);
  }
  
  getAndProcessInput();
}

int main(int argc, char *argv[]) {
  int status = NO_ERROR;
   status = getAndProcessInput();
   return status;
}

int cmd_date(int argc, char *argv[]) {
  struct timeval tv;
  struct timezone tz;
  int status = 0;
  long int seconds = 0, minutes = 0, hours = 0,
    days = 0, months = 0, years = 0;
  char *monthName = NULL;
  int *t;

  if(argc > 1) {
    return INCORRECT_NUM_ARGUMENTS;
  }
  
  status = gettimeofday(&tv, &tz);
  
  if(status == -1) {
    return status;
  }
  
  seconds = (long) (tv.tv_sec);
  minutes = (long) (seconds/60);
  hours   = (long) (minutes/60);
  days    = (long) (hours/24);
  hours   = hours % 24;
  minutes = minutes % 60;
  seconds = seconds % 60;

  years = getYearFromDays(&days);
  
  monthName = getMonthFromDays(&days, years);

  fprintf(stdout, "%s %-2ld, %4ld %2ld:%-2ld:%-2ld.%-6ld\n",
	  monthName, days, years, hours, minutes, seconds,
	  tv.tv_usec);
  return 0;
}

int cmd_echo(int argc, char *argv[]) {
  int i = 0;
  // Print out all the arguments except the
  // last one
  for(i = 1; i < argc-1; i++) {
    fprintf(stdout, "%s ", argv[i]);
  }
  // Print the last argument.
  if(argc > 1) {
    fprintf(stdout, "%s\n", argv[argc-1]);
  }
  return 0;
}

int cmd_exit(int argc, char *argv[]) {
  int status = 0;
  if(argc > 1) {
    return INCORRECT_NUM_ARGUMENTS;
  }
  exit(status);
  return 0;
}

int cmd_help(int argc, char *argv[]) {
  if(argc > 1) {
    return INCORRECT_NUM_ARGUMENTS;
  }
  
  fprintf(stdout, "The commands accepted by the shell are: \n \
\tdate: Return the present date and time. \n \
\techo: Display a line of text. \n \
\texit: Exit the shell. \n \
\thelp: Show a brief desciption of the commands accepted by the shell.\n");
    return 0;
}
