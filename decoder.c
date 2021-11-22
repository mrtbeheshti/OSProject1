#include "consts.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>


int main()
{
    //---- read input from parent-decoder pipe ---//
    mkfifo(parent_decoder, 0666);
    char parent_inp[MAX_STRING_LENGTH * MAX_LINES / 2];
    int p2d = open(parent_decoder, O_RDONLY);
    read(p2d, parent_inp, MAX_STRING_LENGTH * MAX_LINES / 2);
    close(p2d);

    //---- find the main string ----//
    for (int i = 0; parent_inp[i];i++){
        if (parent_inp[i]-3>='a')
            parent_inp[i] -= 3;
        else
            parent_inp[i] += 23;
    }
}