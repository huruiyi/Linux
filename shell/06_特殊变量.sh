#!/bin/sh
echo "the script name is :`basename $0`"
echo "param1 is :$1"
echo "param2 is :$2"
echo "param3 is :$3"
echo "param4 is :$4"
echo "param5 is :$5"
echo "param6 is :$6"
echo "param7 is :$7"
echo "number of arguments:$#"
echo "process id:$$"
echo "before process id:$!"
echo "\$*-------:$*"
echo "\$@------:$@"
echo "dit script go with any errors:$?"

echo "\$*输出结果如下："
for a in $*
do
    echo "$a"
done

echo "\$@输出结果如下："
a=0;
for arg in $@
do
    echo "$arg"
done

