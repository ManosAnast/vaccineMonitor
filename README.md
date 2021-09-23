# Goal:
 vaccineMonitor is a program that keeps a record for every citizen and the vaccinations that the have done.
 Linux terminal application

# Program call:
  
First compile the code with:
    
    make

  Then, the program is called with this format:
    
    ./vaccineMonitor -c citizenRecordsFile –b bloomSize

    – citizenRecordsFile is the file that has the citizens.

    – bloomSize is the number of bytes that the bloom filter will have ,

File format:
  ID FirstName LastName Country Age Virus vaccinationStatus(YES/NO) Date(If vaccinationStatus is YES)

Script:

  Call format:
    
    ./testFile.sh virusesFile countriesFile numLines duplicatesAllowed
    
    - virusesFile: file that contains the names of the viruses
    
    - countriesFile: file that contains the names of the countries
    
    - numLines: number of lines that the file will have
    
    - duplicatesAllowed: if it is 0, there won't be any duplicates. Otherwise, the duplication is allowed.

# Commands:

    ● /vaccineStatusBloom citizenID virusName
    
  Check if the citizen with the given citizenID is vaccinated for the virusName.(Use of bloom filter)

  Output format:
   NOT VACCINATED *OR*
   MAYBE

    ● /vaccineStatus citizenID virusName
    
  Check if the citizen that with the given citizenID is vaccinated for the virusName. If the citizen is vaccinated, print the date of the vaccination.(Use of Skip List)

  Output format:
   NOT VACCINATED OR
   VACCINATED ON 27-12-2020

    ● /vaccineStatus citizenID
    
  Check the vaccination status for the citizen that with the given citizenID for every virus that we keep a record for.

  Output format: 
  COVID-19 YES 27-12-2020
  SARS-1 NO
  H1N1 YES 11-11-2020

    ● /populationStatus [country] virusName date1 date2
  
  Print the number and percentage of vaccinations that have been done to every country.
  If the country hasn't been given, the app will print the exact number of vaccinations for the given dates, for every single country.
  The percentage of every country has been made by taking into consideration the number of citizens that have been given to the program. Not the actual number of citizens that every country has.

   Output format: 
  GREECE 523415 5.02%
  USA 358000000 10.8%
  ISRAEL 3289103 38.0%

    ● /popStatusByAge [country] virusName date1 date2
    
  Print the number and percentage of vaccinations that have been done to every country categorized by age.
  If the country hasn't been given, the app will print the exact number of vaccinations for the given dates, for every single country.
  The percentage of every country has been made by taking into consideration the number of citizens that have been given to the program. Not the actual number of citizens that every country has.

  Output format:
  GREECE
  0-20 0 0%
  20-40 18795 0.36%
  40-60 64650 1.24%
  60+ 439970 8.44%
  ISRAEL
  0-20 0 15%
  20-40 18795 23%
  40-60 64650 32.24%
  60+ 4399070 90.44%

    ● /insertCitizenRecord citizenID firstName lastName country age virusName YES/NO [date]

  The app insert a new citizen with this informations. In case of an error, it returns:
  
  ERROR: CITIZEN 889 ALREADY VACCINATED ON 27-12-2020

    ● /vaccinateNow citizenID firstName lastName country age virusName
  
  Change the status of a non vaccinated person to vaccinated. If the citizen has been already vaccinated, it returns:
  
  ERROR: CITIZEN 889 ALREADY VACCINATED ON 27-12-2020.

    ● /list-nonVaccinated-Persons virusName
    
  Returns a list of all the non vaccinated citizens for a certain virus.
  Output format:
  125 Jon Dupont USA 76
  889 John Papadopoulos GREECE 52 

    ● /exit
    
  The app is stopped.
