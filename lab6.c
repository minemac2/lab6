#include "q.h"
#include <stdio.h>
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

void* copyText(void* arg){

    char *filename = ((char*)arg);


    int in = 0;

    in = open(filename, O_RDONLY);



    close(in);

    free(filename);
    
    return (void *) 0;
}

int main(char *argv[]){

    DIR *d;
    struct dirent *e;
    d = opendir(argv[0]);
    double total;
    double total2=0;
    int i = 0;

    pthread_t threads[100];
    
    while ((e = readdir(d)) != NULL) {

        
        if (e->d_type != DT_REG)
            continue;

        if(strcmp(e->d_name,"*.txt"))
            continue;

        char *filename = strdup(e->d_name);

        printf("%s\n", filename);
        
        //clock_gettime(CLOCK_REALTIME, &start[i]);
        pthread_create(&threads[i], NULL, copyText, filename);
      
        i++;
    	
	
    }

    /*for (int j = 0; j < i; j++) {
     
        pthread_join(threads[j], NULL);
   	clock_gettime(CLOCK_REALTIME, &end[j]);
   	total = (end[j].tv_sec - start[j].tv_sec);
   	total += (end[j].tv_nsec - start[j].tv_nsec) / 1000000000.0;
   	printf("Time for thread %d: %f\n", j, total);
   	
    }*/

    return 0;

}
