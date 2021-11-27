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
    
    //Opens file
    FILE * in = fopen(filename,"r");

    //stores the letters as a word is being read
    char str[100];
    str[0]='\0';
    //temp stand in for the buffer-stores words once they have been read
    char words[10000];
    words[0]='\0';
    //holds characters as they are read from file
    int c;


    //loops through the file character by character

    while((c=fgetc(in)) != EOF)
    {
        //if the currect char is a space or newline it is the end of a word
        if(c== ' ' || c == '\n'){
           
            //copy str and newline into words and clear str
            strcat(&words,&str);
            strcat(&words,"\n");
            str[0]='\0';


        }
        else{

            //add character to str
            strcat(&str,&c);

        }
    }

    //copy last word to words
    strcat(&words,&str);
    strcat(&words,"\n");
    
    printf("%s",&words);

    

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



        //printf("%s\n", (char*)e->d_name);

        //create filename (for now just set the array size to 1000)
        char filename[1000];
        filename[0]='\0';
        //add filepath to filename and filename
        strcat(&filename,argv[1]);
        strcat(&filename,"/");
        strcat(&filename,e->d_name);


        //print filename
        printf("%s\n",&filename);



        //pthread_create(&threads[i], NULL, copyText, filename);
        //run copy text
        copyText(filename);
        i++;
    }




    return 0;
}

