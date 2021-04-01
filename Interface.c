# include "Interface.h"

void BreakString(char *** Array, char * str, const char * s, int Num)
{
    int index=0;
    char ** Temp=*Array;
    char * Break=(char *)calloc(strlen(str)+1, sizeof(char)); 
    strcpy(Break, str); // I use a new string variable because i want the str variable intacted
    // Use of strtok in order to break the string.
    char * token = strtok(Break, s);
    while (token != NULL && index < Num)   //this loop gives the variables that we need to the array from the token(strtok)
    {
        strcpy(Temp[index],token);
        token = strtok(NULL, s);
        index++;
    }
    // If the array isn't "filled" add the nullstring to those that are empty.
    for (int i = index; i < Num; i++){
        strcpy(Temp[i], NULLstring);
    }
    free(Break);
    return;
}

void Start(char * text)
{
    int ch,Size=0;

    Virus * Vlist=VirusInit();
    Country * CList=CountryCreate();
    FILE * fp;

    fp=fopen(text , "r");   
    // Find the number of entries that the given file has
    while(1) {
        ch = getc(fp);
        if( feof(fp) ) { 
            break ;
        }
        if(ch == '\n'){  //Finds how many students are added.
            Size+=1;
        }
    }
    fclose(fp);
    fp=fopen(text , "r");   

    // Create the hash table and a string that takes each line
    HTCreate(Size);
    char *str;
    str=(char *)calloc(150,sizeof(char));
    
    char **Array=(char**)malloc(8*sizeof(char *)); // make an arry of strings with 50 characters each string.
    for(int i=0 ; i< 8 ; i++){
        Array[i]=(char*)malloc(50*sizeof(char));
    }
    const char * s=" "; // Char that indicates the breaking point of the string
    while (1){
        int i=0;
        while ((ch = getc(fp)) != EOF) // Read each line of the entries
        {
            if(ch == '\n'){
                break;
            }
            str[i]=ch;  //str is a string that keeps each line that we get from the file.
            i++;
        }
        str[i]='\0';

        if( feof(fp) ) { 
            break ;
        }
        
        BreakString(&Array, str, s, 8);
        /* If the citizen has been vaccinated, yes, insert true. Otherwise insert false*/
        if (!strcmp(Array[6],"NO")){
            if(HTSearch(atoi(Array[0]), Array[5])!=NULL){ // Check for duplication
                printf("Citizen with %d has already been added for %s\n", atoi(Array[0]), Array[5]);
            }
            else{
                int Flag=HTInsert(atoi(Array[0]), Array[1], Array[2], Array[3], atoi(Array[4]), Array[5], false, Array[7]);
                if (Flag){ // If the hash table insertion had an error, don't insert to the other structs.
                    VirusInsert(&Vlist, Array[0], Array[5], false , Array[7]);
                    CountryInsert(&CList, Array[3]);
                }
            }
        }
        else if (!strcmp(Array[6],"YES")){
            if(HTSearch(atoi(Array[0]), Array[5])!=NULL){ // Check for duplication
                printf("Citizen with %d has already been added for %s\n", atoi(Array[0]), Array[5]);
            }
            else{
                int Flag=HTInsert(atoi(Array[0]), Array[1], Array[2], Array[3], atoi(Array[4]), Array[5], true, Array[7]);
                if(Flag){  // If the hash table insertion had an error, don't insert to the other structs.
                    VirusInsert(&Vlist, Array[0], Array[5], true, Array[7]);
                    CountryInsert(&CList, Array[3]);
                }
            }
        }  
    }
    fclose(fp);
    Level=Log(Size);
    for (int i = 0; i < 8; i++){
        free(Array[i]);
    }
    free(Array);
    free(str);

    VirusSkipList(&Vlist);

    TTY(Vlist, CList);
    
    Destroy(Vlist, CList);

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
        char Answer[100];
        printf("Give a command\n");
        fgets(Answer,100,stdin);
        if(( strlen(Answer)>0 ) && (Answer[strlen(Answer) - 1])=='\n'){
            Answer[strlen(Answer)-1]='\0';
        }
        if(!strcmp(Answer, "exit")){
            break;
        }
        BreakString(&Array, Answer, " ", 9);// Array has the userts input
        // Checks for commands and if the call is complete.
        if (!strcmp(Array[0], "vaccineStatusBloom")){
            if(!strcmp(Array[2], NULLstring)){
                printf("Wrong command. vaccineStatusBloom is called like:\nvaccineStatusBloom citizenID virusName \n\n"); continue;
            }
            VaccinateStatusBloom(Vlist, Array[1], Array[2]);
        }
        else if (!strcmp(Array[0], "vaccineStatus")){
            if(!strcmp(Array[1], NULLstring)){
                printf("Wrong command. vaccineStatus is called like:\nvaccineStatus citizenID virusName \n\n"); continue;
            }
            if(!strcmp(Array[2], NULLstring)){ // If there is no specified virus name.
                Virus * Temp=Vlist;
                Temp=Temp->Next;
                while (Temp!=NULL){ // Traverse the virus list.
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
            if(!strcmp(Array[1], NULLstring)){
                printf("Wrong command. list-nonVaccinated-Persons is called like:\nlist-nonVaccinated-Persons virusName \n\n"); continue;
            }
            ListNonVaccinated(Vlist, Array[1]);
        }
        else if (!strcmp(Array[0], "insertCitizenRecord")){
            if(!strcmp(Array[7], NULLstring)){
                printf("Wrong command. insertCitizenRecord is called like:\ninsertCitizenRecord citizenID firstName lastName country age virusName YES/NO [date] \n\n"); continue;
            }
            InsertCitizenRecord(Vlist, CList, Array);
        }
        else if (!strcmp(Array[0], "vaccinateNow")){
            if(!strcmp(Array[6], NULLstring)){
                printf("Wrong command. vaccinateNow is called like:\nvaccinateNow citizenID firstName lastName country age virusName \n\n"); continue;
            }
            VaccinateNow(Vlist, CList, Array);
        }
        else if (!strcmp(Array[0], "populationStatus")){
            if(!strcmp(Array[3], NULLstring)){
                printf("Wrong command. populationStatus is called like:\npopulationStatus [country] virusName date1 date2 \n\n"); continue;
            }
            populationStatus(Vlist, CList, Array, false);
        }
        else if (!strcmp(Array[0], "popStatusByAge")){
            if(!strcmp(Array[3], NULLstring)){
                printf("Wrong command. popStatusByAge is called like:\npopStatusByAge [country] virusName date1 date2 \n\n"); continue;
            }
            populationStatus(Vlist, CList, Array, true);
        }
        else{
            printf("There is no %s command. Try again\n", Array[0]);
        }
        printf("\n");
    }
    for (int i = 0; i < 9; i++){
        free(Array[i]);
    }
    free(Array);
    return;
}

void Destroy(Virus * Vlist, Country * CList)
{
    VirusDestroy(&Vlist);
    CountryDestroy(&CList);
    HTDestroy();
}