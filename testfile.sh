#!/bin/bash

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
            fi
        fi
    fi
fi

lines=$3  #number of lines that the file will have
duplicate=$4 #duplicateallowed flag

# if duplicate is not 0 then make it 1
if [ $duplicate != 0 ]
    then
    duplicate=1
fi

