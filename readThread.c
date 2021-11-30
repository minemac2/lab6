#include "readThread.h"
#include "queueE.h"

void* readFromFile(char* filename, struct Queue *q,sem_t *mutex,sem_t *empty,sem_t *full){
    
    //Opens file
    FILE * in = fopen(filename,"r");

    //stores the letters as a word is being read
    char str[100];
    str[0]='\0';

    //holds characters as they are read from file
    int c;


    //loops through the file character by character
    

    while((c=fgetc(in)) != EOF)
    {
        //if the current char is a space or newline it is the end of a word
        if(c== ' ' || c == '\n' || c == ','){
            if(str[0]=='\0'){
                continue;
            }
            
                //critical section start
                //wait
                //printf("FileName: %s\n", filename);
                sem_wait(full);
                sem_wait(mutex);
                enQueue(q,strdup(&str),strdup(filename));
                sem_post(mutex);
                sem_post(empty);
                //post
                //crit section end

                //clear str
                str[0]='\0';


        }
        else{

            //add character to str
            strcat(&str,&c);

        }
    }
    
    
    

    sem_wait(full);
    sem_wait(mutex);
    enQueue(q,strdup(&str),strdup(filename));
    sem_post(mutex);
    sem_post(empty);

    
    fclose(in);


    return (void*) 0;
}