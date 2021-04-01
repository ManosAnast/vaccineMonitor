#!/bin/bash

total=$#
Check=4
#test number of parametrs
if (( $total<$Check ))
    then
    echo Bash Format is ./testFile.sh virusesFile countriesFile numLines duplicatesAllowed 
    exit
fi

#test if the files are correct
# e1=(-e $1)
# e2=(-e $2)
# echo $e1 $e2
# if (( $e1=="true" & $e2=="true" )) 
#     then
#     if  (( -f $1 & -f $2 ))
#         then
#         echo Correct files
#     else
#         echo Wrong file
#         exit
#     fi
# else
#     echo Wrong file
#     exit
# fi

lines=$3  #number of lines that the file will have
duplicate=$4 #duplicateallowed flag

# Name of file that the script is writing to
input=inputFile.txt


virus=($(cat "$1")) # Array with viruses names
countries=($(cat "$2")) # Array with countries
viruslength=$[${#virus[@]}-1] # Length of virus array
countrieslength=$[${#countries[@]}-1] # Length of countries array

# Empty the new file from the previous things that it contained and insert the first entry
if [ $(( $RANDOM % 2 )) == 1 ]
    then
    vac="YES"
    Date="$(( $RANDOM % 30 + 1 ))-$(( $RANDOM % 12 +1 ))-$(( $RANDOM % 50 + 2000 ))"
else
    vac="NO"
    Date=""
fi 
# id=$(( $RANDOM % $lines ))
id=($(shuf -i 0-$lines -n $lines))
var="${id[0]} name${id[0]} surname${id[0]} ${countries[$(( $RANDOM % $countrieslength ))]} $(( $RANDOM % 120 + 1 )) ${virus[$(( $RANDOM % $viruslength ))]} $vac $Date"
echo $var > $input

# Make of input file
flag=0
for ((i=1; i<$lines; i++))
do
    if [[ ( $duplicate != 0 ) && ( $(( $RANDOM % 2 )) == 1 ) && ( $flag == 0 ) ]] # Checks if duplication is allowed
        then 
        flag=1
        echo $var >> $input
        continue
    fi

    if [ $(( $RANDOM % 2 )) == 1 ] # Figures out if the citizen is vaccinated or not
        then
        vac="YES"
        Date="$(( $RANDOM % 30 + 1 ))-$(( $RANDOM % 12 +1 ))-$(( $RANDOM % 50 + 2000 ))"
    else
        vac="NO"
        Date=""
    fi 

    flag=0
    var="${id[$i]} name${id[$i]} surname${id[$i]} ${countries[$(( $RANDOM % $countrieslength ))]} $(( $RANDOM % 120 + 1 )) ${virus[$(( $RANDOM % $viruslength ))]} $vac $Date"
    echo $var >> $input

done

# make
# ./vaccineMonitor -c inputFile.txt -b 100000