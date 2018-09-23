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
echo -n "循环2_1："
for i in `seq 1 10`
do
    echo -n "$i "
done

echo ""
echo -n "循环2_2："
 for i in $(seq 10)
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
awk  'BEGIN {for(i=1;i<=10;i++) print  i}'

echo ""
echo -n "循环5："
for i in `cat persons`
do
    echo $i
done

echo ""
echo  "循环6："
cat persons|while read tmp
do
    echo $tmp
done

echo ""
echo  "循环7："
 for((i=1;i<=10;i++));
 do 
    echo 4的倍数 $(expr $i \* 4);
 done