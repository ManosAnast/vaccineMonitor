# include "Interface.h"

int M;
Citizens ** Table;

Date * CreateDate(char * DateStr)
{
    Date * Timing=(Date *)calloc(1, sizeof(Date));
    if (!strcmp(DateStr, "Today")){
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        Timing->Days=tm.tm_mday; Timing->Month=tm.tm_mon + 1; Timing->Year=tm.tm_year+1900;
        return Timing;
    }
    
    const char * s="-";
    char **Array=BreakString(DateStr, s, 3);
    if (atoi(Array[0])<=30 && atoi(Array[0])>0 && atoi(Array[1])>0 && atoi(Array[1])<=12){
        Timing->Days=atoi(Array[0]); Timing->Month=atoi(Array[1]); Timing->Year=atoi(Array[2]);
        return Timing;
    }
    else{
        printf("Wrong Date\n"); return NULL;
    }
}

void PrintDate(Date * Timing)
{
    if (Timing != NULL){
        printf("%d-%d-%d\n", Timing->Days, Timing->Month, Timing->Year);
        return;
    }
    printf("\n"); return;
}

void HTCreate(int Size)
{
    M=Size/5;
    Table=(Citizens **)calloc(M, sizeof(Citizens *));
}

Citizens * NewRecord(int Id, char * Name, char * Country, int Age, char * Virus, bool Vaccinated, char * DateStr)
{
    Citizens * NewNode=(Citizens *)calloc(1, sizeof(Citizens));
    NewNode->citizenId=Id; NewNode->Age=Age; NewNode->Vaccinated=Vaccinated; NewNode->Next=NULL;
    NewNode->Name=(char *)calloc(strlen(Name), sizeof(char)); strcpy(NewNode->Name, Name);
    NewNode->Country=(char *)calloc(strlen(Country), sizeof(char)); strcpy(NewNode->Country, Country);
    NewNode->Virus=(char *)calloc(strlen(Virus), sizeof(char)); strcpy(NewNode->Virus, Virus);
    if (!Vaccinated){
        NewNode->Timing=NULL;  return NewNode;
    }
    NewNode->Timing=CreateDate(DateStr);
    return NewNode;
}

// I took it from the book "Algorithms in c" 
int Hash(int Item)
{
    return Item % M;
}

void HTInsert(int Id, char * Name, char * Country, int Age, char * Virus, bool Vaccinated, char * DateStr)
{
    int i = Hash(Id);
    if(Table[i] == NULL){   //if the table that we want is null make it using the new function
        Table[i]=NewRecord(Id, Name, Country, Age, Virus, Vaccinated, DateStr);
        return;
    }
    else{
        Citizens * Temp=Table[i];
        while (Temp->Next != NULL){ //find the end of the tables chain
            Temp=Temp->Next;
        }
        Temp->Next=NewRecord(Id, Name, Country, Age, Virus, Vaccinated, DateStr);
        return;
    }
}

//Searches for a citizen.If the citizen doesn't exist print error and return null
// If the citizen do exist return the citizen.
Citizens * HTSearch(int Item)
{
    Citizens * Temp = Table[Hash(Item)];
    while (Temp != NULL && Temp->citizenId != Item ){
        Temp=Temp->Next;
    }
    if(Temp == NULL){
        printf("Citizen %d does not exist\n",Item);
    }
    return Temp;
}

void HTPrint()
{
    for (int i = 0; i < M; i++){
        Citizens * Temp = Table[i];
        printf("- %d %s %s %d %s %d ",Temp->citizenId,Temp->Name,Temp->Country,Temp->Age,Temp->Virus,Temp->Vaccinated); PrintDate(Temp->Timing);
        Temp=Temp->Next;
        while (Temp != NULL ){
            printf("- %d %s %s %d %s %d ",Temp->citizenId,Temp->Name,Temp->Country,Temp->Age,Temp->Virus,Temp->Vaccinated); PrintDate(Temp->Timing);
            Temp=Temp->Next;
        }
    }
    return;
}