#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    int fd1;
    char * inputText[1000];
    char * parent_decoder = "parent_decoder.unp";
    char * parent_finder = "parent_finder.unp";
    char * parent_placer = "parent_placer.unp";
    char * decoder_finder = "decoder_finder.unp";
    char * finder_placer = "finder_placer.unp";

    char * decoder_args[]={"./decoder",NULL};
    char * finder_args[]={"./finder",NULL};
    char * placer_args[]={"./placer",NULL};

    //---- fork decoder proccess ----
    pid_t decoder_id=fork();
    if(decoder_id<0){
        perror("failure fork() for decoding");
        exit(EXIT_FAILURE);
    }
    else if(decoder_id==0)
        execvp(decoder_args[0],decoder_args);

    //---- fork finder proccess ----
    pid_t finder_id=fork();
    if(finder_id<0){
        perror("failure fork() for finding");
        exit(EXIT_FAILURE);
    }
    else if(finder_id==0)
        execvp(finder_args[0],finder_args);

    //---- fork placer proccess ----
    pid_t placer_id=fork();
    if(placer_id<0){
        perror("failure fork() for placing");
        exit(EXIT_FAILURE);
    }
    else if(placer_id==0)
        execvp(placer_args[0],placer_args);
}