#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
char HELP[] = "vm-man - A simple QEMU vm managing tool written in c\nUsage:\n\tvm-man install <iso image>\n\tvm-man help\n\tvm-man list\n\tvm-man <list item>";
char *opts[4] = {"start", "install", "help", "list"};
enum Mode{Start, Install, Help, List};
enum Mode mode = 2;
int defSize = 20;
int defRam = 4096;

// function init
int in(char **arr, int len, char *target);
void doStuff();
// main
int main(int argc, char *argv[]) {
    if (argc == 1) {
        fprintf(stderr, "%s\n", HELP);
        exit(1);
    } else {
        int inIndex = in(opts, 4, argv[1]);
        if (inIndex == -1) {
            fprintf(stderr, "Error invalid argument\nRun 'vm-man help' for more info");
            exit(1);
        } else {
            mode = inIndex;
        }
    }
    doStuff(argc, argv);
    return 0;
}
void doStuff(int argc, char *argv[]) {
    char *command = NULL;
    if (mode == Help) {
        printf("%s\n", HELP);
    } else if (mode == Install) {
        asprintf(&command, "qemu-img create -f qcow2 %s %dG", command, defSize);
        system("echo Heloo");
        command = NULL;
    }
    free(command); 
}
int in(char **arr, int len, char *target) {
    int i;
    for (i = 0; i < len; i++) {
        if (strncmp(arr[i], target, strlen(target)) == 0) {
            return i;
        }
    }
    return -1;
}
