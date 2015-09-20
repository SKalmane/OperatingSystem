
extern const int LINE_MAX;

int setArgc(char line[LINE_MAX + 1]);

// Allocate memory for each input argument provided
void allocateMemForArgv(int argc, char *argv[], 
                        char line[LINE_MAX + 1]);

void populateArgvWithStrings(char *argv[], 
                             char line[LINE_MAX + 1]);

void deallocateArgv(int argc, char ***argv);
