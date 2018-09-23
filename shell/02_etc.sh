#!/bin/sh
#for file in 'ls /etc'
echo  "hello\tboy"
echo \"\"

file="07_.sh"
echo `cat $file | wc -l`

file_tel="07_.sh"
#获取文件中不重复的行数（去重后）
echo `awk '{$1="";print $0;}' $file_tel | sort | uniq -c | sort -n -k1 | tail -n1`