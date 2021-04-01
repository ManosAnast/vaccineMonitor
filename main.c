# include "Interface.h"

int Level, BloomNum;

int main(int argc, char *argv[])
{
    if(argc < 5){
        printf("Input format ./vaccineMonitor -c citizenRecordsFile –b bloomSize \n");
        return 0;
    }

    char * File;
    printf("%ld\n\n", sizeof(Country));
    /*Convert the arguments that the user gave.*/
    for (int i = 1; i < argc; i++){
        if ( !strcmp(argv[i],"-c") ){
            File=argv[++i];
        }
        else if ( !strcmp(argv[i],"-b") ){
            BloomNum=atoi(argv[++i]);
        }
    }
    Start(File);
    return 0;
}