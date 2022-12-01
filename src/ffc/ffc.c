// ffc - FastFfmpegConversion
// Threaded ffmpeg file conversion
// Written by NewDawn0 (Tom) 1.12.2022

// Libs
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

// Static Stuff 
#define HELP "ffc - A threade wrapper aroud the ffmpeg file conversions\nUSAGE: ffc -i <file> -o <outfile>"
char *cliArgs[2] = {"-i", "-o"};

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
    int inFileIndex = -1;
    int outFileIndex = -1;
    bool inFileFound = false;
    bool outFileFound = false;
    for (int ac = 0; ac < argc; ac++) {
        int inRes = in(cliArgs, 2, argv[ac]);
        if (inRes >= 0) {
            if (argv[ac+1] != NULL) {
                if (inRes == 0 && !inFileFound) {
                    inFileFound = true;
                    inFileIndex = ac+1;
                } else if (inRes == 1 && !outFileFound) {
                    outFileFound = true;
                    outFileIndex = ac+1;
                } else {
                    fprintf(stderr, "ERROR: Unexpected extra input file \"%s\"\n", argv[ac+1]);
                    return 1;
                }
            } else {
                fprintf(stderr, "ERROR: No input provided after option %s\n", cliArgs[inRes]);
                return 1;
            }
        }
    }
    if (inFileIndex == -1 && outFileIndex == -1) {
        printf("in: %d; out: %d", inFileIndex, outFileIndex);
        fprintf(stderr, "No input and output files provided");
        return 1;
    }
    if (!fileExists(argv[inFileIndex])) {
        fprintf(stderr, "ERROR: Input file \'%s\' does not exist\n", argv[inFileIndex]);
        return 1;
    }
    if (fileExists(argv[outFileIndex])) {
        fprintf(stderr, "ERROR: Output file \'%s\' already exists\n", argv[outFileIndex]);
        return 1;
    }
    // Check if files exist
    /* for (int i = 0; i < inFileVec.count; i++) { */
    /*     char *current = (char*)inFileVec.data[i]; */
    /*     if (!fileExists(current)) { */
    /*         fprintf(stderr, "ERROR: \'%s\' No such file or directory\n", current); */
    /*         return 1; */
    /*     } */
    /* } */
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

// Check if file exists
bool fileExists(char *fname) {
    if (access(fname, F_OK) == 0) {
        return true;
    }
    return false;
}
// Command
// fmpeg -i "input" -ss 164 -f segment -segment_time 120 -reset_timestamps 1 -map 0:0 -an output_video%d.MTS
