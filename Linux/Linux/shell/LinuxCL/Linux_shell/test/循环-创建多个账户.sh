#!/bin/bash
# 利用循环创建多个用户账户

while read name
do
    useradd $name
done < input.csv

echo "Over!"
