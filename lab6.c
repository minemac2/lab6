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
#include "queueE.h"
#include "readThreadE.h"
#include "readThread.h"
#include "sortThread.h"
#include <semaphore.h>

sem_t queueOneEmptySem;
sem_t queueOneFullSem;
sem_t queueOneMutexSem;





//producer
// sem_wait(&full);
// sem_wait(&mutex);
// put(i);
// sem_post(&mutex);
// sem_post(&empty);

//consumer
// sem_wait(&empty);
// sem_wait(&mutex);
// int tmp = get();
// sem_post(&mutex);
// sem_post(&full);



int main(int argc, char *argv[]){
    DIR *d;
    struct dirent *e;

    char *directory=(char*)malloc(sizeof(argv[1])+3);
    directory[0]='\0';
    strcat(directory,"./");
    strcat(directory,argv[1]);

    d = opendir(directory);
    

    //init semaphores
    sem_init(&queueOneMutexSem, 0, 1);
    sem_init(&queueOneEmptySem, 0, 0); //want the write threads to wait until queue is filled or files are done
    sem_init(&queueOneFullSem,0,argv[2]);

    //init queue1 and queue2
    struct Queue* queue1=createQueue();
    struct Queue* queue2=createQueue();

    int fileCount=0;
    while((e=readdir(d)) !=NULL){

        if (e->d_type != DT_REG)
            fileCount++;
    }
    d = opendir(directory);

    pthread_t readThreads[fileCount];
    int i=0;
    while ((e = readdir(d)) != NULL) {

        if (e->d_type != DT_REG)
            continue;


        //create filename (for now just set the array size to 1000)
        char filename[1000];
        filename[0]='\0';
        //add filepath to filename and filename
        strcat(&filename,argv[1]);
        strcat(&filename,"/");
        strcat(&filename,e->d_name);

        void* args[5];
        args[0]=filename;
        args[1]=queue1;
        args[2]=&queueOneMutexSem;
        args[3]=&queueOneEmptySem;
        args[4]=&queueOneFullSem;
        for(int i=0;i<5;i++){
            printf("%s, ",args[i]);
        }
        printf("\n");
        pthread_create(&readThreads[i],NULL,readFromFile,&args);
        //readFromFile(filename, queue1,&queueOneMutexSem,&queueOneEmptySem,&queueOneFullSem);


        
        i++;
    }
    printf("%d",fileCount);
    for(int j=0;j<fileCount+1;j++){
        pthread_join(readThreads[j],NULL);
        printf("Joined thread: %d\n",j);
    }




    free(directory);
    free(queue1);
    free(queue2);




    return 0;
}

