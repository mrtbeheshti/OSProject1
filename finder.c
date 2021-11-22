
#include "consts.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

int main()
{
    printf("Starting finding proccess!\n");
    //---- read input from parent-finder pipe ---//
    mkfifo(parent_finder, 0666);
    char parent_inp[MAX_STRING_LENGTH * MAX_LINES / 2];
    int p2f = open(parent_finder, O_RDONLY);
    read(p2f, parent_inp, MAX_STRING_LENGTH * MAX_LINES / 2);
    close(p2f);
    
}