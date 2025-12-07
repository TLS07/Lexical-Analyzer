#include "main.h"
int error_flag;

int main(int argc,char *argv[])
{
    // to check .c file is passed or not
    if(argc<2)
    {
        printf("ERROR:Pass the .c file to read\n");
        printf("INFO: Format ./aout filename.c\n");
        return 0;
    }

    char filename[20];
    strcpy(filename,argv[1]);
    if(!strstr(filename,".c"))
    {
        printf("ERROR: Pass the .c format file\n");
        return 0;
    }

    //opening the file and performing lexiacal anlyze
    FILE* fptr=fopen(filename,"r");
    if(fptr)
    {
        printf("%s file opened successfully\n",filename);
    }
    else{
        printf("failed to open %s file\n",filename);
        printf("Try again \n");
        return 0;
    }

    lexical_analyze(fptr);
    fclose(fptr);

}

