# include "skiplist.h"

void Insert(FILE * fp)
{
    char *str;
    str=(char *)calloc(150,sizeof(char));
    
    char **Array;
    Array=(char**)malloc(8*sizeof(char *)); // make an arry of strings with 30 characters each string.
    for(int i=0 ; i< 8 ; i++){
        Array[i]=(char*)malloc(50*sizeof(char));
    }

    const char * s=" ";
    int ch, index=0;
    while (1){
        int i=0;
        index=0;
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

        if (!strcmp(Array[5],"NO")){
            HTInsert(atoi(Array[index-6]), Array[index-5], Array[index-4], atoi(Array[index-3]), Array[index-2], false /*, Nothing*/); // give the arguments to the htinsert.
        }
        else if (!strcmp(Array[5],"YES")){
            HTInsert(atoi(Array[index-6]), Array[index-5], Array[index-4], atoi(Array[index-3]), Array[index-2], true /*, Date*/); // give the arguments to the htinsert.
        }
        
    }
}