# include "Interface.h"

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

    //Level is log of the number of entries
    Size=10;
    Level=Log(Size); 
    SkipList * slist=SLInit(0);
    Virus * Vlist=VirusInit();

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
            VirusInsert(&Vlist, (Array[index-6]), Array[index-5], Array[index-4], atoi(Array[index-3]), Array[index-2], false /*, Nothing*/); // give the arguments to the htinsert.
        }
        else if (!strcmp(Array[5],"YES")){
            HTInsert(atoi(Array[index-6]), Array[index-5], Array[index-4], atoi(Array[index-3]), Array[index-2], true /*, Date*/); // give the arguments to the htinsert.
            VirusInsert(&Vlist, (Array[index-6]), Array[index-5], Array[index-4], atoi(Array[index-3]), Array[index-2], true /*, Nothing*/); // give the arguments to the htinsert.
        }

        
        
    }
    // SLInsert(slist); 

    // LLPrint(List);

    Nothing();
    
    return;
}

Virus * VirusInit()
{
    Virus * VList=(Virus *)calloc(1, sizeof(Virus));
    VList->VirusName=(char *)calloc(2, sizeof(char));
    strcpy(VList->VirusName,NULLstring); VList->Next=NULL;
    return VList;
}

void VirusInsert(Virus ** VList, char * CitizenId, char * Name, char * Country, int Age, char * VName, bool Vaccinated/*,Date*/)
{
    Virus * Temp=*VList;
    int Id=atoi(CitizenId);
    while (Temp->Next != NULL && strcmp(Temp->VirusName, VName)){
        Temp=Temp->Next;
    }
    if (Temp->Next == NULL){
        Virus *  NewNode=(Virus *)calloc(1, sizeof(Virus));
        NewNode->VirusName=(char *)calloc(strlen(VName), sizeof(char));
        strcpy(NewNode->VirusName, VName);
        if (Vaccinated){
            SkipList * slist=SLInit(0);
            LinkedList * List=slist->Header;
            LLInsert(List, Id, 0);
            NewNode->vaccinated_persons=slist;
            bloom filter=bloomInit(BloomNum);
            bloomSetBit(&filter, CitizenId);
            NewNode->filter=filter;
        }
        else{
            SkipList * slist=SLInit(0);
            LinkedList * List=slist->Header;
            LLInsert(List, Id, 0);
            NewNode->not_vaccinated_persons=slist;
        }
        Temp->Next=NewNode;
    }
    
}