#!/bin/bash

# 如果5秒内没有到到输入信息，则提示"sorry,, you are too slow"
if read -t 5  -p "Enter your name:" name
then
    echo "hello $name. welcome to my program"
else
    echo "sorry,your are too slow"
fi
exit 0
