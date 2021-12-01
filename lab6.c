#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <pthread.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <string.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <stdbool.h>
#include "sortThread.h"
#include <semaphore.h>

pthread_mutex_t readMutex;
pthread_mutex_t writeMutex;
pthread_mutex_t sortMutex;


struct Queue *queue1;
struct Queue *queue2;
int maxBufferSize;
int maxSortThreads;


void* readFromFile(void* filename){

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
                pthread_mutex_lock(&readMutex);
                if(maxBufferSize > getCount(queue1))
                {
                    enQueue(queue1,strdup(&str),strdup(filename));
                    pthread_mutex_unlock(&readMutex);
                }
                else
                {
                    pthread_t threads[maxSortThreads];
                    for (size_t i = 0; i < maxSortThreads; i++)
                    {
                        pthread_create(&threads[i], NULL, sortThread, NULL);
                    }

                    for (size_t k = 0; k < maxSortThreads; k++)
                    {
                        pthread_join(threads[k], NULL);
                    }

                    enQueue(queue1,strdup(&str),strdup(filename));
                    pthread_mutex_unlock(&readMutex);
                }

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
    
    
    
    //add final word to queue
    pthread_mutex_lock(&readMutex);
    enQueue(queue1,strdup(&str),strdup(filename));
    pthread_mutex_unlock(&readMutex);
    
    fclose(in);


    return (void*) 0;
}



int main(int argc, char *argv[]){
    DIR *d;
    int files = 0;
    maxSortThreads = atoi(argv[3]);

    char *directory=(char*)malloc(sizeof(argv[1])+3);
    directory[0]='\0';
    strcat(directory,"./");
    strcat(directory,argv[1]);

    char *directoryForFilename=(char*)malloc(sizeof(argv[1])+1);
    strcat(directoryForFilename,argv[1]);
    strcat(directoryForFilename,"/");

    maxBufferSize = atoi(argv[2]);

    d = opendir(directory);

    struct dirent *fileCounter;
    struct dirent *iterator;
    
    int counter = 0;

    //init queue1 and queue2
    queue1=createQueue();
    queue2=createQueue();

    pthread_mutex_init( &readMutex, NULL);
    pthread_mutex_init( &writeMutex, NULL);
    pthread_mutex_init( &sortMutex, NULL);

    while( (fileCounter=readdir(d)) )
    {
        if (fileCounter->d_type == DT_REG)
        {
            files++;
        }
    };

    //Init file read threads
    pthread_t fileThreads[files];

    rewinddir(d);
    
    
    while ((iterator = readdir(d)) != NULL) {

        if (iterator->d_type != DT_REG)
            continue;


        char * filename = (char*) malloc((strlen(directoryForFilename) + strlen((char*)iterator->d_name) + 1)*sizeof(char));
        strcpy(filename,directoryForFilename);
        strcat(filename,iterator->d_name);

        pthread_create(&fileThreads[counter], NULL, readFromFile, (void *)filename);


        
        counter++;
    }

    for (size_t j = 0; j < counter; j++)
    {
        pthread_join(fileThreads[j], NULL);
    }

    //spinning up threads until the read queue is depleted
    while(getCount(queue1) != 0)
    {
        pthread_t threads[maxSortThreads];
        for (size_t i = 0; i < maxSortThreads; i++)
        {
            pthread_create(&threads[i], NULL, sortThread, NULL);
        }

        for (size_t k = 0; k < maxSortThreads; k++)
        {
            pthread_join(threads[k], NULL);
        }
    }



    FILE *fp;
    fp = fopen(argv[4], "w+");
    struct node* n = queue2->front;
    while (n != NULL) {
        fprintf(fp, "%s\t\t%s\n", n->word, n->dir);
        n = n->next;
    }    
    fclose(fp);

    free(directory);




    return 0;
}

