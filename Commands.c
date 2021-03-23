# include "Interface.h"

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
                int Flag=HTInsert(atoi(Array[1]), Array[2], Array[3], Array[4], atoi(Array[5]), Array[6], false, Array[8]); // give the arguments to the htinsert.
                if(Flag){    
                    VirusInsert(&Vlist, Array[1], Array[6], false, Array[8]); // give the arguments to the htinsert.
                    CountryInsert(&CList, Array[4]);
                }
            }
            else if (!strcmp(Array[7],"YES")){
                int Flag=HTInsert(atoi(Array[1]), Array[2], Array[3], Array[4], atoi(Array[5]), Array[6], true, Array[8]); // give the arguments to the htinsert.
                if(Flag){
                    VirusInsert(&Vlist, Array[1], Array[6], true, Array[8]); // give the arguments to the htinsert.
                    CountryInsert(&CList, Array[4]);
                }
            }  
        }
    }
    else{
        if (!strcmp(Array[7],"NO")){
            int Flag=HTInsert(atoi(Array[1]), Array[2], Array[3], Array[4], atoi(Array[5]), Array[6], false, Array[8]); // give the arguments to the htinsert.
            if (Flag){
                VirusInsert(&Vlist, Array[1], Array[6], false, Array[8]); // give the arguments to the htinsert.
                CountryInsert(&CList, Array[4]);
            }
                
        }
        else if (!strcmp(Array[7],"YES")){
            int Flag=HTInsert(atoi(Array[1]), Array[2], Array[3], Array[4], atoi(Array[5]), Array[6], true, Array[8]); // give the arguments to the htinsert.
            if(Flag){
                VirusInsert(&Vlist, Array[1], Array[6], true, Array[8]); // give the arguments to the htinsert.
                CountryInsert(&CList, Array[4]);
            }
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
                    InsertByAge(Array, Record->Age, Record->Vaccinated);
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

void InsertByAge(int * Array, int recordAge, bool Vaccinated)
{
    if(recordAge < 20){
        Array[0] += (int)Vaccinated;
    }
    else if (recordAge >= 20 && recordAge < 40){
        Array[1] += (int)Vaccinated;
    }
    else if (recordAge >= 40 && recordAge < 60){
        Array[2] += (int)Vaccinated;
    }
    else if (recordAge >= 60){
        Array[3] += (int)Vaccinated;
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