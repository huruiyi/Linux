#!/bin/bash

#for循环执行ls命令
for i in `ls`
do
    echo $i
done

for i in f1 f2 f3
do
    echo $ifor i in `ls`
done

for number in 1,2,3,4,5
do
    echo "数字：$number"
done

for number in 1 2 3 4 5 
do
    echo "数字：$number"
done

list="a b c d"
for i in $list;
do
echo $i is apl ;
done

for filename in  *.sh
do
        echo "文件名：$filename"
done

for file in $(ls *.sh)
do
echo $file  \! ;
done


for file in /proc/*;
do
    echo $file is file path \! ;
done
 

echo  -n "/etc/shells文件第三行："  
sed -n 3p /etc/shells

# 第一列
sed -n 2p /etc/hosts|cut  -d  '	'  -f1
# 第二列
sed -n 2p /etc/hosts|cut  -d  '	'  -f2

# 当前登陆人第四个字符

echo "**************whoami|cut -b 4****************"
whoami|cut -b 4

# -b ：以字节为单位进行分割。这些字节位置将忽略多字节字符边界，除非也指定了 -n 标志。
# -c ：以字符为单位进行分割。
# -d ：自定义分隔符，默认为制表符。
# -f ：与-d一起使用，指定显示哪个区域。
# -n ：取消分割多字节字符。仅和 -b 标志一起使用。如果字符的最后一个字节落在由 -b 标志的 List 参数指示的
# 范围之内，该字符将被写出；否则，该字符将被排除

# 输出第二列
echo "**************cut -d ' ' -f 2 persons ****************"

cut -d ' ' -f 2 persons 

echo "**************shells****************"
for filename in `cat /etc/shells `
do
    echo "$filename"
done

for i in 1 2 3 4 5 
do
    echo "$i-->$(uptime)"
done

sum=0
for(( i=1;i<=100;i++ ))
do
     sum=$(( $sum + $i ))
done

echo "1+2+3+...+100=$sum"