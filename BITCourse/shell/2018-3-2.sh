#!/bin/bash

echo "Please define how to search (1 - filename, 2 - date)"

read option

if [ $option -eq 1 ]
then
    echo "search by name"
    read filename
    find . -type f -name "*$filename*"
else
    echo "search by date, the date is the format of example (2017-2-2)"
    read date
    ls --full-time . | grep "$date"
    if [ $? -eq 0 ]
    then
        echo "find the result !"
    else
        echo "can not find the result !"
    fi
fi
