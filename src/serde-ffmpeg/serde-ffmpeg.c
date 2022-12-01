// serde ffmpeg
// Parralelized ffmpeg action
// Written by NewDawn0 (Tom) 1.12.2022

// Libs
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Static Messages
char HELP[] = "serde-ffmpeg - A threaded wrapper around ffmpeg\nUSAGE: serde-ffmpeg <your normal ffmpeg operatons>";
char *cliArgs[2] = {"-i", "-a"};

// Function declarations
void splitVideos(char *inFile);
int in(char **arr, int len, char *target);

// Main
int main(int argc, char *argv[]) {
    // Parse arguments
    if (argc == 1) {
        printf("%s\n", HELP);
        return 1;
    }
    for (int ac = 0; ac < argc; ac++) {
        int inRes = in(cliArgs, 2, argv[ac]);
        if (inRes >= 0) {
            printf("Argument %s found at index %d\n", argv[ac], ac);
            if (argv[ac+1] != NULL) {
                printf("Next Argument %s found at index %d\n", argv[ac+1], ac+1);
            } else {
                char *errmsg;
                asprintf(&errmsg, "ERROR :: No input provided after option %s", cliArgs[inRes]);
                perror(errmsg);
                free(errmsg);
                return 1;
            }
        }
    }
    char inFile[] = "Hello world";
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
// Command
// fmpeg -i "input" -ss 164 -f segment -segment_time 120 -reset_timestamps 1 -map 0:0 -an output_video%d.MTS
