#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

const int MAX_STRING_LENGTH = 100;
const int MAX_LINES = 20;

int isSeparator(char str[][MAX_STRING_LENGTH])
{
    return 1;
}
int main()
{
    FILE *input_file;
    char *text_parts;
    char inputText[MAX_LINES][MAX_STRING_LENGTH];
    int lines;

    char *parent_decoder = "parent_decoder.unp";
    char *parent_finder = "parent_finder.unp";
    char *parent_placer = "parent_placer.unp";
    char *decoder_finder = "decoder_finder.unp";
    char *finder_placer = "finder_placer.unp";

    char *decoder_args[] = {"./decoder", NULL};
    char *finder_args[] = {"./finder", NULL};
    char *placer_args[] = {"./placer", NULL};

    //---- read input file ----//
    input_file = fopen("./codedText.txt", "r");
    if (!input_file)
    {
        printf("can't find input file");
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
        int part = 0;
        for (int i=0;i<=lines;i++)
        {
            //---- making pipes ----//

            //---- parent - decoder pipe ----//
            mkfifo(parent_decoder, 0666);
            if (isSeparator(inputText))
                part++;
            else
            {
                switch (part)
                {
                case 0:

                case 1:
                    break;
                case 2:
                    break;
                }
            }
        }
    }
}