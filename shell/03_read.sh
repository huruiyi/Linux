#!/bin/sh
echo "enter your name"
read name
echo "your name:" $name


#read  如果同时读取多个变量，则输入的值以空格进行分割，多余的赋值给最后一个变量
read name1 name2
echo $name1
echo $name2