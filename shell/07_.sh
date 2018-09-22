#!/bin/bash
#by huruiyi
echo "Hello world"
echo Hello World

Version='1.11'

# 双引号中可以使用变量
server1="Nginx $Version"
echo $server1

server2='Nginx $Version'
echo $server2