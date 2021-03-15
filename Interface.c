# include "Interface.h"

unsigned int Log(unsigned int n) 
{ 
    return (n > 1) ? 1 + Log(n / 2) : 0; 
} 

void Nothing()
{
    return;
}

void BreakString(char *** Array, char * str, const char * s, int Num)
{
    int index=0;
    char ** Temp=*Array;
    char * Break=(char *)calloc(strlen(str)+1, sizeof(char)); 
    strcpy(Break, str);
    char * token = strtok(Break, s);   //we use strtok in order to break the string into the different data in order to give it to the HTInsert
    //now we will use an array of strings that keeps all the variables that we need for the hash table
    while (token != NULL && index < Num)   //this loop gives the variables that we need to the array from the token(strtok)
    {
        strcpy(Temp[index],token);
        token = strtok(NULL, s);
        index++;
    }
    for (int i = index; i < Num; i++){
        strcpy(Temp[i], NULLstring);
    }
    free(Break);
    return;
}

void Insert(FILE * fp)
{
    int ch,Size=0,Bloom;

    //Level is log of the number of entries
    Size=12;
    Level=Log(Size);
    Virus * Vlist=VirusInit();
    Country * CList=CountryCreate();

    HTCreate(Size);

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

        if( feof(fp) ) { 
            break ;
        }
        
        BreakString(&Array, str, s, 8);
        if (atoi(Array[0])== 23)
        {
            Nothing();
        }
        /* If the citizen has been vaccinated, yes, insert true. Otherwise insert false*/
        if (!strcmp(Array[6],"NO")){
            if(HTSearch(atoi(Array[0]), Array[5])!=NULL){
                printf("Citizen with %d has already been added for %s\n", atoi(Array[0]), Array[5]);
            }
            else{
                HTInsert(atoi(Array[0]), Array[1], Array[2], Array[3], atoi(Array[4]), Array[5], false, Array[7]); // give the arguments to the htinsert.
                VirusInsert(&Vlist, Array[0], Array[5], false , Array[7]); // give the arguments to the htinsert.
                CountryInsert(&CList, Array[3]);
            }
        }
        else if (!strcmp(Array[6],"YES")){
            if(HTSearch(atoi(Array[0]), Array[5])!=NULL){
                printf("Citizen with %d has already been added for %s\n", atoi(Array[0]), Array[5]);
            }
            else{
                HTInsert(atoi(Array[0]), Array[1], Array[2], Array[3], atoi(Array[4]), Array[5], true, Array[7]); // give the arguments to the htinsert.
                VirusInsert(&Vlist, Array[0], Array[5], true, Array[7]); // give the arguments to the htinsert.
                CountryInsert(&CList, Array[3]);
            }
        }  
    }
    
    for (int i = 0; i < 8; i++){
        free(Array[i]);
    }
    free(Array);

    Nothing();

    VirusSkipList(&Vlist);

    TTY(Vlist, CList);
    
    VirusDestroy(&Vlist);
    CountryDestroy(&CList); 
    // free(Vlist); free(CList);

    free(str);
    return;
}


void TTY(Virus * Vlist, Country * CList)
{
    char **Array;
    Array=(char**)malloc(9*sizeof(char *)); // make an arry of strings with 30 characters each string.
    for(int i=0 ; i< 9 ; i++){
        Array[i]=(char*)malloc(50*sizeof(char));
    }
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
        BreakString(&Array, Answer, " ", 9);
        if (!strcmp(Array[0], "vaccineStatusBloom")){
            VaccinateStatusBloom(Vlist, Array[1], Array[2]);
        }
        else if (!strcmp(Array[0], "vaccineStatus") && strcmp(Array[1], NULLstring)){
            if(!strcmp(Array[2], NULLstring)){
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
            populationStatus(Vlist, CList, Array, false);
        }
        else if (!strcmp(Array[0], "popStatusByAge")){
            populationStatus(Vlist, CList, Array, true);
        }
        
        printf("\n");
    }
    for (int i = 0; i < 9; i++){
        free(Array[i]);
    }
    free(Array);
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
        printf("VACCINATED ON "); 
        Citizens * Rec=HTSearch(atoi(Id), VirusName); PrintDate(Rec->Timing);
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
        Person=HTSearch(List->Id, VName);
        if (Person != NULL){
            printf("%d %s %s %s %d\n",Person->citizenId, Person->FirstName, Person->LastName, Person->Country, Person->Age);
        }
        List=List->Next[0];
    }
    return;
}

void InsertCitizenRecord(Virus * Vlist, Country * CList, char ** Array)
{
    Virus * Temp = VirusFind(Vlist, Array[6]);
    bloom filter= Temp->filter;
    int exist=bloomBitExist(&filter, Array[1]);
    if (exist)
    {
        Virus * Temp = VirusFind(Vlist, Array[6]);
        LinkedList * exist = SLSearch(Temp->vaccinated_persons, atoi(Array[1]));
        if (exist != NULL)
        {
            printf("VACCINATED ON\n");
        }
        else{
            if (!strcmp(Array[7],"NO")){
                HTInsert(atoi(Array[1]), Array[2], Array[3], Array[4], atoi(Array[5]), Array[6], false, Array[8]); // give the arguments to the htinsert.
                VirusInsert(&Vlist, Array[1], Array[6], false, Array[8]); // give the arguments to the htinsert.
                CountryInsert(&CList, Array[4]);
            }
            else if (!strcmp(Array[7],"YES")){
                HTInsert(atoi(Array[1]), Array[2], Array[3], Array[4], atoi(Array[5]), Array[6], true, Array[8]); // give the arguments to the htinsert.
                VirusInsert(&Vlist, Array[1], Array[6], true, Array[8]); // give the arguments to the htinsert.
                CountryInsert(&CList, Array[4]);
            }  
        }
    }
    else{
        if (!strcmp(Array[7],"NO")){
            HTInsert(atoi(Array[1]), Array[2], Array[3], Array[4], atoi(Array[5]), Array[6], false, Array[8]); // give the arguments to the htinsert.
            VirusInsert(&Vlist, Array[1], Array[6], false, Array[8]); // give the arguments to the htinsert.
            CountryInsert(&CList, Array[4]);
        }
        else if (!strcmp(Array[7],"YES")){
            HTInsert(atoi(Array[1]), Array[2], Array[3], Array[4], atoi(Array[5]), Array[6], true, Array[8]); // give the arguments to the htinsert.
            VirusInsert(&Vlist, Array[1], Array[6], true, Array[8]); // give the arguments to the htinsert.
            CountryInsert(&CList, Array[4]);
        } 
    }
    return;
}

/*Remove from nonvaccinated skip list*/
void VaccinateNow(Virus * Vlist, char ** Array)
{
    Virus * Temp = VirusFind(Vlist, Array[6]);
    LinkedList * exist = SLSearch(Temp->vaccinated_persons, atoi(Array[1]));
    if (exist != NULL)
    {
        printf("ERROR: CITIZEN %s ALREADY VACCINATED ON ", Array[1]);
        Citizens * Rec=HTSearch(atoi(Array[1]), Array[6]);
        if (Rec != NULL){
            PrintDate(Rec->Timing);
        }
    }
    else{
        VirusInsert(&Vlist, Array[1], Array[6], true, Array[8]); // give the arguments to the htinsert.
        Citizens * Rec=HTSearch(atoi(Array[1]), Array[6]); 
        if (Rec != NULL){
            SLDelete(&(Temp->not_vaccinated_persons), atoi(Array[1]));
            Rec->Vaccinated=true; Rec->Timing=CreateDate("Today");
        }
        
    }
}

void populationStatus(Virus * VList, Country * CList, char ** Array, bool Age)
{
    Virus * Temp=VList;
    int * Cat;
    if (Age){
        Cat=(int *)calloc(4, sizeof(int));
    }
    else{
        Cat=(int *)calloc(1, sizeof(int));
    }
    

    if (strcmp(Array[4], NULLstring)){
        while (Temp->Next!=NULL && strcmp(Temp->VirusName, Array[2])){
            Temp=Temp->Next;
        }
        if(Temp->Next == NULL && strcmp(Temp->VirusName, Array[2])){
            printf("ERROR: Couldn't find the virus that you gave\n");
            free(Cat);
            return;
        }
        SkipList *SList=Temp->vaccinated_persons;
        Cat = CalculateVaccinated(Temp, Array[1], Age, Cat, Array[3], Array[4]);
        Country * country=CountrySearch(CList, Array[1]);        
        PrintCat(country->CName, Cat, Age, country->Population);
        free(Cat);
        return;
    }
    while (Temp->Next!=NULL && strcmp(Temp->VirusName, Array[1])){
        Temp=Temp->Next;
    }
    if(Temp->Next == NULL && strcmp(Temp->VirusName, Array[1])){
        printf("ERROR: Couldn't find the virus that you gave\n");
        free(Cat);
        return;
    }
    CList=CList->Next;
    while (CList != NULL){
        SkipList *SList=Temp->vaccinated_persons;
        Cat = CalculateVaccinated(Temp, CList->CName, Age, Cat, Array[2], Array[3]);
        PrintCat(CList->CName, Cat, Age, CList->Population);
        CList=CList->Next;
    }
    
    free(Cat);
    return;
}

int * CalculateVaccinated(Virus * Vlist, char * Country, bool Age, int * Array, char * Date1, char * Date2)
{
    LinkedList * Temp=Vlist->vaccinated_persons->Header;
    Date * Timing1=CreateDate(Date1), * Timing2=CreateDate(Date2);
    Citizens * Record;
    Temp=Temp->Next[0];
    while (Temp != NULL){
        Record=HTSearch(Temp->Id, Vlist->VirusName);
        if(Record != NULL){    
            if(!strcmp(Record->Country, Country) && CheckDate(Record->Timing, Timing1) && CheckDate(Timing2, Record->Timing)){ 
                if(Age){
                    InsertByAge(Array, Record);
                }
                else{
                    *Array += (int)Record->Vaccinated;
                }
            }
        }
        Temp=Temp->Next[0];
    }
    free(Timing1); free(Timing2);
    return Array;
}

void InsertByAge(int * Array, Citizens * Record)
{
    if(Record->Age < 20){
        Array[0] += (int)Record->Vaccinated;
    }
    else if (Record->Age >= 20 && Record->Age < 40){
        Array[1] += (int)Record->Vaccinated;
    }
    else if (Record->Age >= 40 && Record->Age < 60){
        Array[2] += (int)Record->Vaccinated;
    }
    else if (Record->Age >= 60){
        Array[3] += (int)Record->Vaccinated;
    }
    return;
}

void PrintCat(char * Country, int * Array, bool Age, int Population)
{
    if (Age){
        printf("%s\n", Country);
        printf("0-20 %d %f% \n", Array[0], (double)Array[0]/(double)Population * 100);
        printf("20-40 %d %f% \n", Array[1], (double)Array[1]/(double)Population * 100);
        printf("40-60 %d %f% \n", Array[2], (double)Array[2]/(double)Population * 100);
        printf("60+ %d %f% \n", Array[3], (double)Array[3]/(double)Population * 100);
        for (int i = 0; i < 4; i++){
            Array[i]=0;
        }
        return;
    }
    printf("%s:%d %f% \n", Country, *Array, (double)*Array/(double)Population * 100);
    *Array=0;
    return;
}