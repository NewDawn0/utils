// serde ffmpeg
// Parralelized ffmpeg action
// Written by NewDawn0 (Tom) 1.12.2022

// Libs
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

// Definitions
#define empty 100

// Static Messages
char HELP[] = "serde-ffmpeg - A threaded wrapper around ffmpeg\nUSAGE: serde-ffmpeg <your normal ffmpeg operatons>";
char *cliArgs[1] = {"-i"};


// Function declarations
void splitVideos(char *inFile);
int in(char **arr, int len, char *target);
bool fileExists(char *fname);

// Main
int main(int argc, char *argv[]) {
    // Parse arguments
    if (argc == 1) {
        printf("%s\n", HELP);
        return 1;
    }
    for (int ac = 0; ac < argc; ac++) {
        int inRes = in(cliArgs, 1, argv[ac]);
        if (inRes >= 0) {
            if (argv[ac+1] != NULL) {
                printf("fileindex[?] = %d\n", ac+1);
            } else {
                fprintf(stderr, "ERROR: No input provided after option %s\n", cliArgs[inRes]);
                return 1;
            }
        }
    }
    char inFile[] = "Hello world";
    // Check if file exists
    if (!fileExists(inFile)) {
        perror("ERROR");
        return 1;
    }
    splitVideos(inFile);
    return 0;
}

// Split Videos into multiple files
void splitVideos(char *inFile) {
    char *command;
    asprintf(&command, "Lol %s", inFile);
    printf("%s\n", command);
    free(command);
}

// Retrurn indes of allowed arguments
int in(char **arr, int len, char *target) {
    int i;
    for (i = 0; i < len; i++) {
        if (strncmp(arr[i], target, strlen(target)) == 0) {
            return i;
        }
    }
    return -1;
}

// Check if file exists
bool fileExists(char *fname) {
    if (access(fname, F_OK) == 0) {
        return true;
    }
    return false;
}
// Command
// fmpeg -i "input" -ss 164 -f segment -segment_time 120 -reset_timestamps 1 -map 0:0 -an output_video%d.MTS
