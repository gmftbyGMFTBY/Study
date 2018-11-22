#!/bin/bash

number=${1}

#if [ $number -gt 20 ]
#then
#    echo "The argument which you give is not correct try(10,12,15,20)!"
#    exit 0
#fi

cd /home/lantian/File/Study\ Coding/Optimisation/GLPK-Tool/TSP-Hard/GLPK/prepare

if [ $number -gt 20 ]
then
    target_floder=`expr GLPK_${1}`
    target_file=`expr pnd.*.dat`
else
    target_floder=`expr PnD_${1}`
    target_file=`expr glp.*.dat`
fi


p=`ls $target_floder | grep ${target_file}`

data=($p)

newdata=()

k=0
for i in ${data[*]}
do
    if [ $number -eq 100 ]
    then
        newdata[k]=`expr substr $i 9 2`
    else
        newdata[k]=`expr substr $i 8 2`
    fi
    k=`expr $k + 1`
done

mkdir -p `expr ../new/PnD_${number}`

k=0
for i in ${data[*]}
do
    newname=`expr ../new/PnD_${number}/new_glp_${number}_${newdata[k]}.res`
    newnameinf=`expr ../new/PnD_${number}/new_glp_${number}_${newdata[k]}.inf`

    target=`expr ./${target_floder}/$i`
    if [ $number -eq 100 ]
    then
        glpsol --tmlim 1200 -m ../TSP.mod -d $target -o $newname > $newnameinf
    else
        glpsol --tmlim 240 -m ../TSP.mod -d $target -o $newname > $newnameinf
    fi
    echo "Instance new_glp_${number}_${newdata[k]}.res has been created!"
    k=`expr $k + 1`
done

if [ $number -eq 10 ]
then
    cd ../
    python3 check_correct.py $number
else
    echo "We don't have the answer from our teacher in those instance,so I give it!"
fi
