#!/bin/bash

echo -n "循环1："
for((i=1;i<=10;i++))
do
    echo -n "$i "
done

echo ""
echo -n "循环2："
for i in $(seq 1 10)
do
    echo -n "$i "
done

echo ""
echo  -n "循环3："
for i in {1..10}
do
    echo -n "$i "
done


echo ""
echo -n "循环4："
awk 'BEGIN {for(i=1;i<=10;i++) print  i}'

#for循环执行ls命令
for i in `ls`
do
    echo $i
done


for i in f1 f2 f3
do
    echo $i
done


list="a b c d"
for i in $list;
do
echo $i is apl ;
done

for file in /proc/*;
do
echo $file is file path \! ;
done

for file in $(ls *.sh)
do
echo $file  \! ;
done