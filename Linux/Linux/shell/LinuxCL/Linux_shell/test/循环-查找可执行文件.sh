#!/bin/bash
# 利用环境变量PATH查找可以执行的可执行程序

IFS=$:

for folder in $PATH
do
    echo "$folder"
    for file in $folder/*
    do
        if [ -x $file ]
        then
            echo "    $file"
        fi
    done
done

