# include "skiplist.h"

unsigned int Log(unsigned int n) 
{ 
    return (n > 1) ? 1 + Log(n / 2) : 0; 
} 

void Nothing()
{
    return;
}

void Insert(FILE * fp)
{
    int ch,Size=0,Bloom;
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

    LinkedList * List=slist->Header;


    char *str;
    str=(char *)calloc(150,sizeof(char));
    
    char **Array;
    Array=(char**)malloc(8*sizeof(char *)); // make an arry of strings with 30 characters each string.
    for(int i=0 ; i< 8 ; i++){
        Array[i]=(char*)malloc(50*sizeof(char));
    }

    const char * s=" ";
    int index=0;
    while (1){
        int i=0;
        index=0;
        if (atoi(Array[0])==2){
            Nothing();
        }
        while ((ch = getc(fp)) != EOF)
        {
            if(ch == '\n'){
                break;
            }
            if(ch != '}' && ch != '{' && ch != '"'){
                str[i]=ch;  //str is a string that keeps each line that we get from the file.
                i++;
            }
        }
        str[i]='\0';
        
        char * token = strtok(str, s);   //we use strtok in order to break the string into the different data in order to give it to the HTInsert
        //now we will use an array of strings that keeps all the variables that we need for the hash table
        while (token != NULL)   //this loop gives the variables that we need to the array from the token(strtok)
        {
            strcpy(Array[index],token);
            token = strtok(NULL, s);
            index++;
        }
   
        if( feof(fp) ) { 
            break ;
        }

        /* If the citizen has been vaccinated, yes, insert true. Otherwise insert false*/
        if (!strcmp(Array[5],"NO")){
            HTInsert(atoi(Array[index-6]), Array[index-5], Array[index-4], atoi(Array[index-3]), Array[index-2], false /*, Nothing*/); // give the arguments to the htinsert.
        }
        else if (!strcmp(Array[5],"YES")){
            HTInsert(atoi(Array[index-6]), Array[index-5], Array[index-4], atoi(Array[index-3]), Array[index-2], true /*, Date*/); // give the arguments to the htinsert.
        }

        /* After the citizen has been inserted at the hash, insert it to linked list. */
        LLInsert(List, atoi(Array[0]), 0);
        
    }
    SLInsert(slist); 

    LLPrint(List);
    
    return;
}