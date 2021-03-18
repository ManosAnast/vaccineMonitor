#!/bin/bash

total=$#

#test number of parametrs
if [ total < 4 ]
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

