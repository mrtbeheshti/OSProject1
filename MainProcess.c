#include "consts.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

int isSeparator(char str[])
{
    if (!strcmp("###\n", str))
        return 1;
    return 0;
}
int main()
{
    FILE *input_file;
    char *text_parts;
    char inputText[MAX_LINES][MAX_STRING_LENGTH];
    int lines;

    int p2d, p2f, p2p;

    const char *decoder_args[] = {"./decoder", NULL};
    const char *finder_args[] = {"./finder", NULL};
    const char *placer_args[] = {"./placer", NULL};

    //---- read input file ----//
    input_file = fopen("./codedText.txt", "r");
    if (!input_file)
    {
        perror("can't find input file");
        exit(EXIT_FAILURE);
    }
    for (lines = 0; !feof(input_file); lines++)
    {
        fgets(inputText[lines], MAX_STRING_LENGTH, input_file);
    }
    //---- fork decoder proccess ----//
    pid_t decoder_id = fork();
    if (decoder_id < 0)
    {
        perror("failure fork() for decoding");
        exit(EXIT_FAILURE);
    }
    else if (decoder_id == 0)
        execvp(decoder_args[0], decoder_args);

    //---- fork finder proccess ----//
    pid_t finder_id = fork();
    if (finder_id < 0)
    {
        perror("failure fork() for finding");
        exit(EXIT_FAILURE);
    }
    else if (finder_id == 0)
        execvp(finder_args[0], finder_args);

    //---- fork placer proccess ----//
    pid_t placer_id = fork();
    if (placer_id < 0)
    {
        perror("failure fork() for placing");
        exit(EXIT_FAILURE);
    }
    else if (placer_id == 0)
        execvp(placer_args[0], placer_args);
    //---- main process ----//
    if (decoder_id && finder_id && placer_id)
    {

        //---- make pipes ----//
        mkfifo(parent_decoder, 0666);
        mkfifo(parent_finder, 0666);
        mkfifo(parent_placer, 0666);

        //------------------------//
        //---- write in pipes ----//
        //------------------------//

        int i;
        char buffer[MAX_STRING_LENGTH * MAX_LINES / 2];

        //---- write in parent-decoder pipe ----//
        buffer[0] = '\0';
        for (i = 0; !isSeparator(inputText[i]); i++)
        {
            inputText[i][strlen(inputText[i]) - 1] = '\0';
            strcat(buffer, inputText[i]);
        }
        inputText[i][strlen(inputText[i]) - 1] = '\0';
        p2d = open(parent_decoder, O_WRONLY);
        write(p2d, buffer, strlen(buffer) + 1);
        close(p2d);

        //---- write in parent-finder pipe ----//
        buffer[0] = '\0';
        for (i++; !isSeparator(inputText[i]); i++)
        {
            p2f = open(parent_finder, O_WRONLY);
            write(p2f, inputText[i], strlen(inputText[i]) + 1);
            close(p2f);
        }

        //---- write in parent-placer pipe ----//
        for (i++; i <= lines; i++)
        {
            p2p = open(parent_placer, O_WRONLY);
            write(p2p, inputText[i], strlen(inputText[i]) + 1);
            close(p2p);
        }
    }
}
