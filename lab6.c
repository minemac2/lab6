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
#include "q1e.h"
#include "q2e.h"




pthread_cond_t queueOneEmpty, queueOneFill, queueTwoEmpty, queueTwoFill;
pthread_mutex_t queueOneMutex, queueTwoMutex;



void* copyText(char* filename){
    
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
            
                pthread_mutex_lock(&queueOneMutex);
                while ((queueOneIsFull())) {
                    pthread_cond_wait(&queueOneEmpty, &queueOneMutex); 
                };
                
                //printf("FileName: %s\n", filename);
                queueOneEnqueue(strdup(&str),strdup(filename));
                pthread_cond_signal(&queueOneFill);
                pthread_mutex_unlock(&queueOneMutex);
                
                //clear str
                str[0]='\0';


        }
        else{

            //add character to str
            strcat(&str,&c);

        }
    }
    
    
    
    pthread_mutex_lock(&queueOneMutex);
    while (queueOneIsFull()){
        pthread_cond_wait(&queueOneEmpty, &queueOneMutex);    
    };
    queueOneEnqueue(strdup(&str),strdup(filename));
    pthread_cond_signal(&queueOneFill);
    pthread_mutex_unlock(&queueOneMutex);
    
    fclose(in);


    return (void*) 0;
}

void preSort(){

    pthread_mutex_lock(&queueOneMutex); 
    while (queueOneIsEmpty())
        pthread_cond_wait(&queueOneFill, &queueOneMutex);
    
    char* word;
    char* dir;
    queueOneDequeue(word,dir);

    pthread_cond_signal(&queueOneEmpty);
    pthread_mutex_unlock(&queueOneMutex);



    free(word);
    free(dir);
}

void finalSort(){

}


int main(int argc, char *argv[]){
    DIR *d;
    struct dirent *e;

    char *directory=(char*)malloc(sizeof(argv[1])+3);
    directory[0]='\0';
    strcat(directory,"./");
    strcat(directory,argv[1]);

    d = opendir(directory);
    
    int i = 0;

    queueOneSetup(10000);

    //pthread_t threads[100];
    while ((e = readdir(d)) != NULL) {

        if (e->d_type != DT_REG)
            continue;



        //printf("%s\n", (char*)e->d_name);

        //create filename (for now just set the array size to 1000)
        char filename[1000];
        filename[0]='\0';
        //add filepath to filename and filename
        strcat(&filename,argv[1]);
        strcat(&filename,"/");
        strcat(&filename,e->d_name);


        //print filename
        //printf("%s\n",&filename);



        //pthread_create(&threads[i], NULL, copyText, filename);
        //run copy text
        copyText(filename);
        
        i++;
    }

    //queueOnePrint();
    queueOneClose();
    free(directory);




    return 0;
}

