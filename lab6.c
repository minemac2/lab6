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



void* copyText(char* filename){
    

    printf("test1");
    //Opens file
    FILE * in = fopen(filename,"r");

    //stores the letters as a word is being read
    char* str="";
    //temp stand in for the buffer-stores words once they have been read
    char* words="";
    //holds characters as they are read from file
    char c;
    printf("test2");

    //loops through the file character by character
    while((c = fgetc(in)) != EOF)
    {
        printf("test3");
        //if the currect char is a space or newline it is the end of a word
        if(c== ' ' || c == '\n'){
            printf("test4");
            //add newline to str
            strcat(str,(char*)"\n");
            //add str to words-should be buffer eventually
            strcat(words,str);
            //reset str to be blank for next word
            str="";
        }
        else{
            printf("test5");
            //add current char to str
            strcat(str,(char*)c);
        }
    }
    
    printf("%s",words);

    

    fclose(in);

    return (void*) 0;
}



int main(int argc, char *argv[]){
    DIR *d;
    struct dirent *e;
    d = opendir(argv[1]);
    int i = 0;

    //pthread_t threads[100];
    while ((e = readdir(d)) != NULL) {

        if (e->d_type != DT_REG)
            continue;



        printf("%s\n", (char*)e->d_name);

        char* filename = strdup(e->d_name);
        //pthread_create(&threads[i], NULL, copyText, filename);
        printf("test");
        copyText(filename);
        i++;
    }




    return 0;
}

