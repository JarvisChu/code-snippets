# 模糊匹配的方式，批量 yum remove 卸载软件

sudo yum list installed | grep rabbit > /tmp/tmp.txt

a=`cat /tmp/tmp.txt | awk '{print $1}'`

for i in $a
do
   echo "remove:" $i
   sudo yum remove -y $i
done