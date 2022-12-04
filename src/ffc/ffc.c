// ffc - FastFfmpegConversion
// Threaded ffmpeg file conversion
// Written by NewDawn0 (Tom) 1.12.2022

// Libs
#include <ftw.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/stat.h>

// Static Stuff 
#define HELP "ffc - A threade wrapper aroud the ffmpeg file conversions\nUSAGE: ffc -i <file> -o <outfile>"
char *cliArgs[2] = {"-i", "-o"};

// Function declarations
void splitVideos(char *inFile);
int in(char **arr, int len, char *target);
bool fileExists(char *fname);
int rmrf(char *path);
char getExt(char *inFile);

// Main
int main(int argc, char *argv[]) {
    //// Parse arguments ////
    // check if no arguments were provided
    if (argc == 1) {
        printf("%s\n", HELP);
        return 1;
    }
    // check all arguments
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
    // check if input and output files were provided
    if (inFileIndex == -1 && outFileIndex == -1) {
        printf("in: %d; out: %d", inFileIndex, outFileIndex);
        fprintf(stderr, "No input and output files provided");
        return 1;
    }
    // check if file exist
    if (!fileExists(argv[inFileIndex])) {
        fprintf(stderr, "ERROR: Input file \'%s\' does not exist\n", argv[inFileIndex]);
        return 1;
    }
    if (fileExists(argv[outFileIndex])) {
        fprintf(stderr, "ERROR: Output file \'%s\' already exists\n", argv[outFileIndex]);
        return 1;
    } 
    splitVideos(argv[inFileIndex]);
    return 0;
}

// Split file into multiple files
void splitVideos(char *inFile) {
    // set strings
    char *dir;
    char *command;
    char ext[strlen(getExt(inFile)) + 1];
    strcpy(ext, getExt(inFile));
        /* char ext[strlen(strrchr(inFile, '.') + 1) + 1]; */
        /* strcpy(ext, strrchr(inFile, '.') + 1); */
    asprintf(&dir, ".%s.tmp-ffc", inFile);
    asprintf(&command, "ffmpeg -i %s -ss 164 -f segment -segment_time 120 -reset_timestamps -map 0:0 -an %s out%d.%s", inFile, ext);
    printf("%s", command);
    // create temporary dir
    if (mkdir(dir, 0700) == -1) {
        fprintf(stderr, "ERROR: Failed to create temporary directory \'%s\'\n", dir);
        exit(1);
    }
    if (rmrf(dir) != 0) {
        fprintf(stderr, "ERROR: Failed to remove temporary directory \'%s\'\n", dir);
        exit(1);
    }
    // remove temporary dir
    free(command);
    free(dir);
}

// Return indes of allowed arguments
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
// remove files
int _unlink(const char *fpath, const struct stat *sb, int typeflag, struct FTW *ftwbuf) {
    int rv = remove(fpath);
    if (rv) {
        perror(fpath);
    }
    return rv;
};
int rmrf(char *path) {
    return nftw(path, _unlink, 64, FTW_DEPTH | FTW_PHYS);
}
// get file extension
char getExt(char *inFile) {
    if (!strchr(inFile, '.')) {
        perror("Could not get extension");
        return false;
    } else {
        char ext[strlen(strrchr(inFile, '.') + 1) + 1];
        strcpy(ext, strrchr(inFile, '.') + 1);
        return ext;
    }
    char iex[] = "";
    return iex;
}
// Command
// fmpeg -i "input" -ss 164 -f segment -segment_time 120 -reset_timestamps 1 -map 0:0 -an output_video%d.MTS
