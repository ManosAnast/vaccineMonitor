# include "Interface.h"

Virus * VirusInit()
{
    Virus * VList=(Virus *)calloc(1, sizeof(Virus));
    char * Vname=(char *)calloc(2, sizeof(char));
    VList->VirusName=Vname;
    VList->vaccinated_persons=SLInit(0);
    VList->not_vaccinated_persons=SLInit(0);
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
        NewNode->VirusName=(char *)calloc(strlen(VName)+1, sizeof(char)); strcpy(NewNode->VirusName, VName);
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

void VirusDestroy(Virus ** VList)
{
    Virus * Current=(*VList)/*->Next*/, *Next;
    while (Current!= NULL){
        Next=Current->Next;
        free(Current->VirusName); 
        SLDestroy(&(Current->vaccinated_persons)); 
        SLDestroy(&(Current->not_vaccinated_persons)); 
        bloomDestroy(&(Current->filter)); 
        free(Current);
        Current=Next;
    }
    return;
}


Country * CountryCreate()
{
    Country * CList=(Country *)calloc(1, sizeof(Country)); CList->Next=NULL; 
    CList->CName=(char *)calloc(20, sizeof(char)); strcpy(CList->CName, NULLstring);
    return CList;
}

Country * CountrySearch(Country * CList, char * Name)
{
    while (CList->Next != NULL && strcmp(CList->CName, Name)){
        CList=CList->Next;
    }
    return CList;
}

void CountryInsert(Country ** CList, char * CName)
{
    Country * Temp=*CList;
    while (Temp->Next != NULL && strcmp(Temp->CName, CName)){
        Temp=Temp->Next;
    }
    if (Temp->Next == NULL && strcmp(Temp->CName, CName)){
        // Temp=Temp->Next;
        Country * NewNode=(Country *)calloc(1, sizeof(Country));
        NewNode->CName=(char *)calloc(20, sizeof(char)); 
        strcpy(NewNode->CName, CName); NewNode->Population=1; NewNode->Next=NULL;
        Temp->Next=NewNode;
        return;
    }
    else if (!strcmp(Temp->CName, NULLstring)){
        strcpy(Temp->CName, CName);
    }
    Temp->Population += 1;
    return;
}

void CountryDestroy(Country ** CList)
{
    Country * Current=*CList, *Next;
    while (Current!= NULL){
        Next=Current->Next;
        free(Current->CName); free(Current);
        Current=Next;
    }
    return;
}