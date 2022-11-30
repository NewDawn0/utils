// serde ffmpeg
// Parralelized ffmpeg action
// Written by NewDawn0 (Tom) 30.11.2022

// Libs
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

// Static Messages
char HELP[] = "serde-ffmpeg\nA threaded wrapper around ffmpeg\nUSAGE: serde-ffmpeg <your normal ffmpeg operatons>";

// Main
int main(int argc, char *argv[]) {
    if (argc == 0) {
        printf("%s", HELP);
        return 1;
    }
    return 0;
}
