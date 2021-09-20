# Goal:
 vaccineMonitor is a program that keeps a record for every citizen and the vaccinations that the have done.

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
    H εφαρμογή θα ελέγχει το bloom filter που σχετίζεται με virusName και θα τυπώνει μήνυμα για το αν ο
    πολίτης με αριθμό ταυτότητας citizenID έχει κάνει το εμβόλιο κατά του virusName. (Δείτε παρακάτω
    αναλυτικά τις δομές που θα πρέπει να κρατάτε).
    Output format:
     NOT VACCINATED OR
     MAYBE

    ● /vaccineStatus citizenID virusName
    H εφαρμογή θα ελέγχει τη skip list που σχετίζεται με virusName και θα τυπώνει μήνυμα για το αν ο πολίτης
    με αριθμό ταυτότητας citizenID έχει κάνει το εμβόλιο κατά του virusName.
    Output format:
     NOT VACCINATED OR
     VACCINATED ON 27-12-2020

    ● /vaccineStatus citizenID
    H εφαρμογή θα ελέγχει όλες τις skip lists (μία για κάθε ίωση), θα εντοπίζει όλες τις εγγραφές του πολίτη με
    αριθμό ταυτότητας citizenID, και θα τυπώνει για κάθε ίωση αν έχει εμβολιαστεί και την ημερομηνία
    εμβολιασμού.
    Output format: μια γραμμή για κάθε ίωση. Παράδειγμα:
    COVID-19 YES 27-12-2020
    SARS-1 NO
    H1N1 YES 11-11-2020

    ● /populationStatus [country] virusName date1 date2
    Αν δεν δοθεί country όρισμα, η εφαρμογή θα τυπώνει για την ασθένεια virusName τον αριθμό πολιτών
    σε κάθε χώρα που έχουν εμβολιαστεί μέσα στο διάστημα [date1...date2] και το ποσοστό του πληθυσμού
    της χώρας που έχει εμβολιαστεί. Αν δοθεί country όρισμα, η εφαρμογή θα τυπώνει για την ασθένεια
    virusName, τον αριθμό πολίτων που έχουν εμβολιαστεί και το ποσοστό του πληθυσμού της χώρας που έχει
    εμβολιαστεί μέσα στο διάστημα [date1...date2]. Εάν υπάρχει ο ορισμός για date1 θα πρέπει να
    υπάρχει και ορισμός για date2, αλλιώς, θα τυπώνεται το μήνυμα λάθους ERROR στον χρήστη.
     Output format: μια γραμμή για κάθε χώρα. Παράδειγμα όπου δεν έχει δοθεί country όρισμα: 
    GREECE 523415 5.02%
    USA 358000000 10.8%
    ISRAEL 3289103 38.0%

    ● /popStatusByAge [country] virusName date1 date2
    Αν δεν δοθεί country όρισμα, η εφαρμογή θα τυπώνει για την ασθένεια virusName τον αριθμό
    εμβολιασμών ανά ηλικιακή κατηγορία σε κάθε χώρα και το ποσοστό του πληθυσμού της ηλικιακής κατηγορίας
    που έχει εμβολιαστεί μέσα στο διάστημα [date1...date2]. Αν δοθεί country όρισμα, η εφαρμογή θα
    τυπώνει για την ασθένεια virusName, τον αριθμό εμβολιασμών ανά ηλικιακή κατηγορία και το ποσοστό
    του πληθυσμού της ηλικιακής κατηγορίας που έχει εμβολιαστεί μέσα στο διάστημα [date1...date2] στη
    χώρα country. Εάν υπάρχει ο ορισμός για date1 θα πρέπει να υπάρχει και ορισμός για date2, αλλιώς,
    θα τυπώνεται το μήνυμα λάθους ERROR στον χρήστη.
    Output format: Παράδειγμα όπου δεν έχει δοθεί country όρισμα:
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

    ● /insertCitizenRecord citizenID firstName lastName country age virusName YES/NO
    [date]
    H εφαρμογή θα εισάγει στο bloom filter και στη κατάλληλη skip list που σχετίζεται με την ίωση virusName
    μια νέα εγγραφή με τα στοιχεία της. Μόνο το YES συνοδεύεται από ένα date. Αν ο πολίτης με αριθμό
    ταυτότητας citizenID έχει ήδη εμβολιαστεί κατά του ιού virusName η εφαρμογή επιστρέφει:
    ERROR: CITIZEN 889 ALREADY VACCINATED ON 27-12-2020

    ● /vaccinateNow citizenID firstName lastName country age virusName
    Η εφαρμογή ελέγχει αν ο πολίτης με αριθμό ταυτότητας citizenID έχει ήδη εμβολιαστεί κατά του ιού
    virusName και αν ναι, επιστρέφει:
    ERROR: CITIZEN 889 ALREADY VACCINATED ON 27-12-2020.
    Αν δεν έχει εμβολιαστεί, η εφαρμογή εισάγει στο bloom filter και στη κατάλληλη skip list που σχετίζεται με
    την ίωση virusName την εγγραφή:
    citizenID firstName lastName country age virusName YES todays_date όπου todays_date
    είναι η σημερινή ημερομηνία.

    ● /list-nonVaccinated-Persons virusName
    H εφαρμογή θα προσπελάζει την κατάλληλη skip list που σχετίζεται με την ίωση virusName και θα τυπώνει
    όλους τους πολίτες που δεν έχουν εμβολιαστεί κατά της virusName. Συγκεκριμένα, θα τυπώνει
    citizenID, firstName, lastName, country και age.
    Output format: μια γραμμή για κάθε πολίτη. Παράδειγμα:
    125 Jon Dupont USA 76
    889 John Papadopoulos GREECE 52 

    ● /exit
    Έξοδος από την εφαρμογή. Βεβαιωθείτε πως ελευθερώνετε σωστά όλη τη δεσμευμένη μνήμη.
