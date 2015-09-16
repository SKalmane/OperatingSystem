#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/time.h>

const int LINE_MAX = 256;

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

void process_line(char line[LINE_MAX + 1]) {
   if (!strncmp(line, "ls", LINE_MAX)) {
       fprintf(stdout, "your files here\n");

   } else {
       fprintf(stdout, "%s\n", line);
   }
}

int main(int argc, char *argv[]) {
   char line[LINE_MAX + 1];
   int c, index;

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
      process_line(line);
      return 0;
   }
}

int cmd_date(int argc, char *argv[]) {
    int time = gettimeofday();
    
    
}
