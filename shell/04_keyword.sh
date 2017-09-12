#!/bin/sh
# 双引号对特殊字符敏感
echo "\$"  #输出$
echo "\$$" #输出 $$
echo "$$"  #3853
echo "hello world"
echo "`v_v`" #``特殊字符，需要转义输出，此处错误
echo "\`v_v\`"

# 单引号输入不用转义符，对特殊字符不敏感
echo '$$'  
echo '`v_v`'

# `` 反单引号用于执行命令
echo `hello` #错误
echo `date` #输出时间
echo "当前时间：`date`"
echo * #输出当前目录下的所有文件名
echo \* #输出*
echo "The pen is \$2"
echo 'The pen is $2'

AA=`date`
echo $AA
echo "The time is AA"