# include "Interface.h"

unsigned int Log(unsigned int n) 
{ 
    return (n > 1) ? 1 + Log(n / 2) : 0; 
} 

void Nothing()
{
    return;
}

char ** BreakString(char * str, const char * s, int Num)
{
    int index=0;
    char **Array;
    Array=(char**)malloc(Num*sizeof(char *)); // make an arry of strings with 30 characters each string.
    for(int i=0 ; i< Num ; i++){
        Array[i]=(char*)malloc(50*sizeof(char));
    }

    char * token = strtok(str, s);   //we use strtok in order to break the string into the different data in order to give it to the HTInsert
    //now we will use an array of strings that keeps all the variables that we need for the hash table
    while (token != NULL && index < Num)   //this loop gives the variables that we need to the array from the token(strtok)
    {
        strcpy(Array[index],token);
        token = strtok(NULL, s);
        index++;
    }
    return Array;
}

void Insert(FILE * fp)
{
    int ch,Size=0,Bloom;

    //Level is log of the number of entries
    Size=12;
    Level=Log(Size); 
    SkipList * slist=SLInit(0);
    Virus * Vlist=VirusInit();

    HTCreate(Size);

    LinkedList * List=slist->Header;


    char *str;
    str=(char *)calloc(150,sizeof(char));
    


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
        
        
   
        if( feof(fp) ) { 
            break ;
        }

        
        char **Array=BreakString(str, s, 8);

        if (atoi(Array[0]) == 21)
        {
            Nothing();
        }
        
        /* If the citizen has been vaccinated, yes, insert true. Otherwise insert false*/
        if (!strcmp(Array[5],"NO")){
            HTInsert(atoi(Array[0]), Array[1], Array[2], atoi(Array[3]), Array[4], false, Array[6]); // give the arguments to the htinsert.
            VirusInsert(&Vlist, Array[0], Array[4], false , Array[6]); // give the arguments to the htinsert.
        }
        else if (!strcmp(Array[5],"YES")){
            HTInsert(atoi(Array[0]), Array[1], Array[2], atoi(Array[3]), Array[4], true, Array[6]); // give the arguments to the htinsert.
            VirusInsert(&Vlist, Array[0], Array[4], true, Array[6]); // give the arguments to the htinsert.
        }  
    }

    Nothing();

    VirusSkipList(&Vlist);

    TTY(Vlist);
    
    return;
}

Virus * VirusInit()
{
    Virus * VList=(Virus *)calloc(1, sizeof(Virus));
    VList->VirusName=(char *)calloc(2, sizeof(char));
    strcpy(VList->VirusName,NULLstring); VList->Next=NULL;
    return VList;
}

void VirusInsert(Virus ** VList, char * CitizenId, char * VName, bool Vaccinated, char * DateStr)
{
    Virus * Temp=*VList;
    int Id=atoi(CitizenId);
    while (Temp->Next != NULL && strcmp(Temp->VirusName, VName)){
        Temp=Temp->Next;
    }
    if (Temp->Next == NULL && strcmp(Temp->VirusName, VName)){
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
    else if ( !strcmp(Temp->VirusName, VName) ){
        if (Vaccinated){
            SkipList * slist=Temp->vaccinated_persons;
            if (slist == NULL){
                slist=SLInit(0);
                LinkedList * List=slist->Header;
                LLInsert(List, Id, 0);
                Temp->vaccinated_persons=slist;
                bloom filter=bloomInit(BloomNum);
                bloomSetBit(&filter, CitizenId);
                Temp->filter=filter;
            }
            else{
                LinkedList * List=slist->Header;
                LLInsert(List, Id, 0);
                Temp->vaccinated_persons=slist;
                bloom filter=Temp->filter;
                bloomSetBit(&filter, CitizenId);
                Temp->filter=filter;
            }
        }
        else{
            SkipList * slist=Temp->not_vaccinated_persons;
            if (slist == NULL){
                slist=SLInit(0);
                LinkedList * List=slist->Header;
                LLInsert(List, Id, 0);
                Temp->not_vaccinated_persons=slist;
            }
            else{
                LinkedList * List=slist->Header;
                LLInsert(List, Id, 0);
                Temp->not_vaccinated_persons=slist;
            }
        }
    }
    
}


void VirusSkipList(Virus ** VList)
{
    Virus * Temp= *VList;
    Temp=Temp->Next;
    
    while (Temp != NULL){
        SLInsert(Temp->vaccinated_persons); 
        SLInsert(Temp->not_vaccinated_persons);
        printf("%s\nvaccinated_persons:\n",Temp->VirusName);
        SLPrint(Temp->vaccinated_persons);
        printf("\n\nnot_vaccinated_persons:\n");
        SLPrint(Temp->not_vaccinated_persons); printf("\n\n");
        Temp=Temp->Next;
    }
    
}


Virus * VirusFind(Virus * Vlist, char * VirusName)
{
    Virus * Temp= Vlist;
    while (Temp != NULL && strcmp(Temp->VirusName, VirusName))
    {
        Temp=Temp->Next;
    }
    return Temp;
}


void VaccinateStatusBloom(Virus * Vlist, char * Id, char * VirusName)
{
    Virus * Temp = VirusFind(Vlist, VirusName);
    bloom filter= Temp->filter;
    int exist=bloomBitExist(&filter, Id);
    if (exist)
    {
        printf("MAYBE\n");
    }
    else{
        printf("NOT VACCINATED\n");
    }
    return;
}

void VaccinateStatus(Virus * Vlist, char * Id, char * VirusName)
{
    Virus * Temp = VirusFind(Vlist, VirusName);
    LinkedList * exist = SLSearch(Temp->vaccinated_persons, atoi(Id));
    if (exist != NULL)
    {
        printf("VACCINATED ON\n");
    }
    else{
        printf("NOT VACCINATED\n");
    }
    return;
}

void TTY(Virus * Vlist)
{
    while (1){
        char Answer[200];
        printf("Give a command\n");
        fgets(Answer,90,stdin);
        if(( strlen(Answer)>0 ) && (Answer[strlen(Answer) - 1])=='\n'){
            Answer[strlen(Answer)-1]='\0';
        }
        if(!strcmp(Answer, "exit")){
            break;
        }
        char ** Array=BreakString(Answer, " ", 8);
        if (!strcmp(Array[0], "vaccineStatusBloom")){
            VaccinateStatusBloom(Vlist, Array[1], Array[2]);
        }
        else if (!strcmp(Array[0], "vaccineStatus") && strcmp(Array[1], "")){
            if(!strcmp(Array[2], "")){
                Virus * Temp=Vlist;
                Temp=Temp->Next;
                while (Temp!=NULL){
                    printf("%s ", Temp->VirusName);
                    VaccinateStatus(Vlist, Array[1], Temp->VirusName);
                    Temp=Temp->Next;
                }
            }
            else{
                VaccinateStatus(Vlist, Array[1], Array[2]);
            }
        }
        else if (!strcmp(Array[0], "list-nonVaccinated-Persons")){
            ListNonVaccinated(Vlist, Array[1]);
        }
        else if (!strcmp(Array[0], "insertCitizenRecord")){
            InsertCitizenRecord(Vlist, Array);
        }
        else if (!strcmp(Array[0], "vaccinateNow")){
            VaccinateNow(Vlist, Array);
        }
        else if (!strcmp(Array[0], "populationStatus")){
            
        }
        for (int i = 0; i < 8; i++){
            free(Array[i]);
        }
        free(Array);
        printf("\n");
    }
}

void ListNonVaccinated(Virus * Vlist, char * VName)
{
    Virus * Temp=Vlist->Next;
    while (Temp->Next != NULL && strcmp(Temp->VirusName, VName)){
        Temp=Temp->Next;
    }
    if(Temp == NULL){
        printf("Didn't find any skiplist for %s\n",VName);
        return;
    }
    LinkedList * List=Temp->not_vaccinated_persons->Header->Next[0];
    Citizens * Person;
    while (List != NULL){
        Person=HTSearch(List->Id);
        printf("%d %s %s %d\n",Person->citizenId, Person->Name, Person->Country, Person->Age);
        List=List->Next[0];
    }
    return;
}

void InsertCitizenRecord(Virus * Vlist, char ** Array)
{
    Virus * Temp = VirusFind(Vlist, Array[5]);
    bloom filter= Temp->filter;
    int exist=bloomBitExist(&filter, Array[1]);
    if (exist)
    {
        Virus * Temp = VirusFind(Vlist, Array[5]);
        LinkedList * exist = SLSearch(Temp->vaccinated_persons, atoi(Array[1]));
        if (exist != NULL)
        {
            printf("VACCINATED ON\n");
        }
        else{
            if (!strcmp(Array[6],"NO")){
                HTInsert(atoi(Array[1]), Array[2], Array[3], atoi(Array[4]), Array[5], false, Array[7]); // give the arguments to the htinsert.
                VirusInsert(&Vlist, Array[1], Array[5], false, Array[7]); // give the arguments to the htinsert.
            }
            else if (!strcmp(Array[6],"YES")){
                HTInsert(atoi(Array[1]), Array[2], Array[3], atoi(Array[4]), Array[5], true, Array[7]); // give the arguments to the htinsert.
                VirusInsert(&Vlist, Array[1], Array[5], true, Array[7]); // give the arguments to the htinsert.
            }  
        }
    }
    else{
        if (!strcmp(Array[6],"NO")){
            HTInsert(atoi(Array[1]), Array[2], Array[3], atoi(Array[4]), Array[5], false, Array[7]); // give the arguments to the htinsert.
            VirusInsert(&Vlist, Array[1], Array[5], false, Array[7]); // give the arguments to the htinsert.
        }
        else if (!strcmp(Array[6],"YES")){
            HTInsert(atoi(Array[1]), Array[2], Array[3], atoi(Array[4]), Array[5], true, Array[7]); // give the arguments to the htinsert.
            VirusInsert(&Vlist, Array[1], Array[5], true, Array[7]); // give the arguments to the htinsert.
        }  
    }
    return;
}

void VaccinateNow(Virus * Vlist, char ** Array)
{
    Virus * Temp = VirusFind(Vlist, Array[5]);
    LinkedList * exist = SLSearch(Temp->vaccinated_persons, atoi(Array[1]));
    if (exist != NULL)
    {
        printf("ERROR: CITIZEN %s ALREADY VACCINATED ON ", Array[1]);
        Citizens * Rec=HTSearch(atoi(Array[1]));
        PrintDate(Rec->Timing);
    }
    else{
        VirusInsert(&Vlist, Array[1], Array[5], true, Array[7]); // give the arguments to the htinsert.
        Citizens * Rec=HTSearch(atoi(Array[1])); Rec->Vaccinated=true; Rec->Timing=CreateDate("Today");
    }
}