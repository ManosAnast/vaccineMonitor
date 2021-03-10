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
    Country * CList=CountryCreate();

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
        /* If the citizen has been vaccinated, yes, insert true. Otherwise insert false*/
        if (!strcmp(Array[5],"NO")){
            HTInsert(atoi(Array[0]), Array[1], Array[2], atoi(Array[3]), Array[4], false, Array[6]); // give the arguments to the htinsert.
            VirusInsert(&Vlist, Array[0], Array[4], false , Array[6]); // give the arguments to the htinsert.
            CountryInsert(&CList, Array[2]);
        }
        else if (!strcmp(Array[5],"YES")){
            HTInsert(atoi(Array[0]), Array[1], Array[2], atoi(Array[3]), Array[4], true, Array[6]); // give the arguments to the htinsert.
            VirusInsert(&Vlist, Array[0], Array[4], true, Array[6]); // give the arguments to the htinsert.
            CountryInsert(&CList, Array[2]);
        }  
    }
    VirusSkipList(&Vlist);

    Nothing();

    TTY(Vlist, CList);
    
    return;
}


void TTY(Virus * Vlist, Country * CList)
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
            InsertCitizenRecord(Vlist, CList, Array);
        }
        else if (!strcmp(Array[0], "vaccinateNow")){
            VaccinateNow(Vlist, Array);
        }
        else if (!strcmp(Array[0], "populationStatus")){
            populationStatus(Vlist, CList, Array);
        }
        else if (!strcmp(Array[0], "popStatusByAge")){
            popStatusByAge(Vlist, CList, Array);
        }
        
        // for (int i = 0; i < 8; i++){
        //     free(Array[i]);
        // }
        free(Array);
        printf("\n");
    }
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

void InsertCitizenRecord(Virus * Vlist, Country * CList, char ** Array)
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
                CountryInsert(&CList, Array[3]);
            }
            else if (!strcmp(Array[6],"YES")){
                HTInsert(atoi(Array[1]), Array[2], Array[3], atoi(Array[4]), Array[5], true, Array[7]); // give the arguments to the htinsert.
                VirusInsert(&Vlist, Array[1], Array[5], true, Array[7]); // give the arguments to the htinsert.
                CountryInsert(&CList, Array[3]);
            }  
        }
    }
    else{
        if (!strcmp(Array[6],"NO")){
            HTInsert(atoi(Array[1]), Array[2], Array[3], atoi(Array[4]), Array[5], false, Array[7]); // give the arguments to the htinsert.
            VirusInsert(&Vlist, Array[1], Array[5], false, Array[7]); // give the arguments to the htinsert.
            CountryInsert(&CList, Array[3]);
        }
        else if (!strcmp(Array[6],"YES")){
            HTInsert(atoi(Array[1]), Array[2], Array[3], atoi(Array[4]), Array[5], true, Array[7]); // give the arguments to the htinsert.
            VirusInsert(&Vlist, Array[1], Array[5], true, Array[7]); // give the arguments to the htinsert.
            CountryInsert(&CList, Array[3]);
        } 
    }
    return;
}

/*Remove from nonvaccinated skip list*/
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

void populationStatus(Virus * VList, Country * CList, char ** Array)
{
    Virus * Temp=VList;

    if (strcmp(Array[4], "")){
        while (Temp->Next!=NULL && strcmp(Temp->VirusName, Array[2])){
            Temp=Temp->Next;
        }
        if(Temp->Next == NULL && strcmp(Temp->VirusName, Array[2])){
            printf("ERROR: Couldn't find the virus that you gave\n");
            return;
        }
        SkipList *SList=Temp->vaccinated_persons;
        int Num= CalculateVaccinated(SList, Array[1]);
        Country * country=CountrySearch(CList, Array[1]);
        printf("%s:%d %d \n",Array[1], Num, Num/country->Population * 100);
        return;
    }
    while (Temp->Next!=NULL && strcmp(Temp->VirusName, Array[1])){
        Temp=Temp->Next;
    }
    if(Temp->Next == NULL && strcmp(Temp->VirusName, Array[1])){
        printf("ERROR: Couldn't find the virus that you gave\n");
        return;
    }
    CList=CList->Next;
    while (CList != NULL){
        SkipList *SList=Temp->vaccinated_persons;
        int Num= CalculateVaccinated(SList, CList->CName);
        printf("%s:%d %d% \n", CList->CName, Num, Num/CList->Population * 100);
        CList=CList->Next;
    }
    
    return;
}

int CalculateVaccinated(SkipList * SList, char * Country)
{
    int Vaccinated=0;
    LinkedList * Temp=SList->Header;
    Citizens * Record;
    Temp=Temp->Next[0];
    while (Temp != NULL){
        Record=HTSearch(Temp->Id);
        if(!strcmp(Record->Country, Country)){ 
            Vaccinated += (int)Record->Vaccinated;
        }
        Temp=Temp->Next[0];
    }
    return Vaccinated;
}

void popStatusByAge(Virus * VList, Country * CList, char ** Array)
{
    Virus * Temp=VList;

    if (strcmp(Array[4], "")){
        while (Temp->Next!=NULL && strcmp(Temp->VirusName, Array[2])){
            Temp=Temp->Next;
        }
        if(Temp->Next == NULL && strcmp(Temp->VirusName, Array[2])){
            printf("ERROR: Couldn't find the virus that you gave\n");
            return;
        }
        SkipList *SList=Temp->vaccinated_persons;
        int Num= CalculateVaccinated(SList, Array[1]);
        Country * country=CountrySearch(CList, Array[1]);
        printf("%s:%d %d \n",Array[1], Num, Num/country->Population * 100);
        return;
    }
    while (Temp->Next!=NULL && strcmp(Temp->VirusName, Array[1])){
        Temp=Temp->Next;
    }
    if(Temp->Next == NULL && strcmp(Temp->VirusName, Array[1])){
        printf("ERROR: Couldn't find the virus that you gave\n");
        return;
    }
    CList=CList->Next;
    while (CList != NULL){
        SkipList *SList=Temp->vaccinated_persons;
        int Num= CalculateVaccinated(SList, CList->CName);
        printf("%s:%d %d% \n", CList->CName, Num, Num/CList->Population * 100);
        CList=CList->Next;
    }
    
    return;
}

