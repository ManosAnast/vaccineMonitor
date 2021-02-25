# include "Interface.h"

int Level;

unsigned int Log(unsigned int n) 
{ 
    return (n > 1) ? 1 + Log(n / 2) : 0; 
} 

int main(int argc, char *argv[])
{
    // if(argc < 5){
    //     printf("Input format ./vaccineMonitor -c citizenRecordsFile –b bloomSize \n");
    //     return 0;
    // }

    // FILE * fp; 
    int ch,Size=0,Bloom;
    // char * File;

    // LinkedList lst;

    // /*Convert the arguments that the user gave.*/
    // for (int i = 1; i < argc; i++){
    //     if ( !strcmp(argv[i],"-c") ){
    //         File=atoi(argv[++i]);
    //     }
    //     else if ( !strcmp(argv[i],"-b") ){
    //         Bloom=atoi(argv[++i]);
    //     }
    // }

    // // calculate the number of entrenches that we get from the file in order to take the size that we need for the hash table
    // fp=fopen(File , "r");   
    // while(1) { 

    //     ch = getc(fp);
    //     if( feof(fp) ) { 
    //         break ;
    //     }
    //     if(ch == '\n'){  //Finds how many students are added.
    //         Size+=1;
    //     }
    // }
    // fclose(fp);

    //Level is log of the number of entries
    Size=10;
    Level=Log(Size); 
    SkipList * slist=SLInit(0);

    HTCreate(Size);

    // HTInsert(7, "Testopoulos", "Greece", 27, "SARS-COV2", true);
    // HTInsert(1, "Testopoulos", "Greece", 21, "SARS-COV2", true);
    // HTInsert(3, "Testopoulos", "Greece", 23, "SARS-COV2", true);
    // HTInsert(2, "Testopoulos", "Greece", 22, "SARS-COV2", true);
    // HTInsert(5, "Testopoulos", "Greece", 25, "SARS-COV2", true);
    // HTInsert(4, "Testopoulos", "Greece", 24, "SARS-COV2", true);
    // HTInsert(6, "Testopoulos", "Greece", 26, "SARS-COV2", true);

    FILE * fp=fopen("testfile.txt", "r");
    Insert(fp);

    LinkedList * List=slist->Header;
    LLInsert(List, 7, 0);
    LLInsert(List, 1, 0);
    LLInsert(List, 3, 0);
    LLInsert(List, 2, 0);
    LLInsert(List, 5, 0);
    LLInsert(List, 4, 0);
    LLInsert(List, 6, 0);
    SLInsert(slist);

    
    return 0;
}