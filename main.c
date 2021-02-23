# include "skiplist.h"

int Level;

unsigned int Log(unsigned int n) 
{ 
    return (n > 1) ? 1 + Log(n / 2) : 0; 
} 

int main(int argc, char *argv[])
{
    if(argc < 5){
        printf("Input format ./vaccineMonitor -c citizenRecordsFile –b bloomSize \n");
        return 0;
    }

    FILE * fp; 
    int ch,Size=0,Bloom;
    char * File;

    LinkedList lst;

    /*Convert the arguments that the user gave.*/
    for (int i = 1; i < argc; i++){
        if ( !strcmp(argv[i],"-c") ){
            File=atoi(argv[++i]);
        }
        else if ( !strcmp(argv[i],"-b") ){
            Bloom=atoi(argv[++i]);
        }
    }

    // calculate the number of entrenches that we get from the file in order to take the size that we need for the hash table
    fp=fopen(File , "r");   
    while(1) { 

        ch = getc(fp);
        if( feof(fp) ) { 
            break ;
        }
        if(ch == '\n'){  //Finds how many students are added.
            Size+=1;
        }
    }
    fclose(fp);

    //Level is log of the number of entries
    Level=Log(Size); 

    return 0;
}