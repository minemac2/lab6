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
#include <glob.h>


void* copyText(char* filename){
    
    int in = 0;
    
    in = open(filename,O_RDONLY);

    

    close(in);

    return (void*) 0;
}

int main(int argc, char *argv[]){
    DIR *d;
    struct dirent *e;
    d = opendir(argv[1]);

    while ((e = readdir(d)) != NULL) {

        if (e->d_type != DT_REG)
            continue;

        if(strrchr(e->d_name,"."))
            continue;

        printf("%s", (char*)e->d_name);
        
    }


return 0;
}

