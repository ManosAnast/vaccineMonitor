# include "skiplist.h"

int M;
Citizens ** Table;

void HTCreate(int Size)
{
    M=Size/5;
    Table=(Citizens **)calloc(M, sizeof(Citizens *));
}

Citizens * NewRecord(int Id, char * Name, char * Country, int Age, char * Virus, bool Vaccinated/*,Date*/)
{
    Citizens * NewNode=(Citizens *)calloc(1, sizeof(Citizens));
    NewNode->citizenId=Id; NewNode->Age=Age; NewNode->Vaccinated=Vaccinated; NewNode->Next=NULL;
    NewNode->Name=(char *)calloc(strlen(Name), sizeof(char)); strcpy(NewNode->Name, Name);
    NewNode->Country=(char *)calloc(strlen(Country), sizeof(char)); strcpy(NewNode->Country, Country);
    NewNode->Virus=(char *)calloc(strlen(Virus), sizeof(char)); strcpy(NewNode->Virus, Virus);
    return NewNode;
}

// I took it from the book "Algorithms in c" 
int Hash(int Item)
{
    return Item % M;
}

void HTInsert(int Id, char * Name, char * Country, int Age, char * Virus, bool Vaccinated/*,Date*/)
{
    int i = Hash(Id);
    if(Table[i] == NULL){   //if the table that we want is null make it using the new function
        Table[i]=NewRecord(Id, Name, Country, Age, Virus, Vaccinated);
        return;
    }
    else{
        Citizens * Temp=Table[i];
        while (Temp->Next != NULL){ //find the end of the tables chain
            Temp=Temp->Next;
        }
        Temp->Next=NewRecord(Id, Name, Country, Age, Virus, Vaccinated);
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
        printf("- %d %s %s %d %s %d\n",Temp->citizenId,Temp->Name,Temp->Country,Temp->Age,Temp->Virus,Temp->Vaccinated);
        while (Temp != NULL ){
            printf("- %d %s %s %d %s %d\n",Temp->citizenId,Temp->Name,Temp->Country,Temp->Age,Temp->Virus,Temp->Vaccinated);
            Temp=Temp->Next;
        }
    }
    return;
}