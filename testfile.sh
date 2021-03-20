#!/bin/bash

total=$#

#test number of parametrs
if [ $total < 4 ]
    then
    echo Bash Format is ./testFile.sh virusesFile countriesFile numLines duplicatesAllowed 
    exit
fi

#test if the files are correct
if [ -e $1 ]
    then
    if [ -e $2 ]
        then
        if [ -f $1 ]
            then
            if [ -f $2 ]
                then
                echo Correct files
            else
                echo Wrong file
                exit
            fi
        else
            echo Wrong file
            exit
        fi
    else
        echo Wrong file
        exit
    fi
fi

virusfile=$1
countryfile=$2
lines=$3  #number of lines that the file will have
duplicate=$4 #duplicateallowed flag

# if file doesn't exist, create it
input=inputFile.txt
if [ ! -a $input ]
    then
    touch $input
fi

# if duplicate is not 0 then make it 1
if [ $duplicate != 0 ]
    then
    duplicate=1
fi

virus=($(cat "$virusfile")) # Array with viruses names
countries=($(cat "$countryfile")) # Array with countries
viruslength=${#virus[@]}
countrieslength=${#countries[@]}

# Empty the new file from the previous things that it contained and insert the first entry
if [ $(shuf -i 0-1 -n 1) == 1 ]
    then
    vac="YES"
    Date="$(shuf -i 1-30 -n 1)-$(shuf -i 1-12 -n 1)-$(shuf -i 2000-2050 -n 1)"
else
    vac="NO"
    Date=""
fi 
var="0 name0 surname0 ${countries[$(shuf -i 0-$countrieslength -n 1)]} $(shuf -i 10-80 -n 1) ${virus[$(shuf -i 0-$viruslength -n 1)]} $vac $Date"
echo $var > $input

# Make of input file
flag=0
for ((i=1; i<$lines; i++))
do
    if [ $(shuf -i 0-1 -n 1) == 1 ] # Figures out if the citizen is vaccinated or not
        then
        vac="YES"
        Date="$(shuf -i 1-30 -n 1)-$(shuf -i 1-12 -n 1)-$(shuf -i 2000-2050 -n 1)"
    else
        vac="NO"
        Date=""
    fi 

    if [[ ( $duplicate == 1 ) && ( $(shuf -i 0-1 -n 1) == 1 ) && ( $flag == 0 ) ]] # Checks if duplication is allowed
        then 
        flag=1
        echo $var >> $input
        continue
    else
        flag=0
        var="$i name$i surname$i ${countries[$(shuf -i 0-$countrieslength -n 1)]} $(shuf -i 10-80 -n 1) ${virus[$(shuf -i 0-$viruslength -n 1)]} $vac $Date"
        echo $var >> $input
    fi

done