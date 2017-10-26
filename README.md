# LInuxList

linux 双向链表使用例子
indata2和indata3是测试数据，使用json格式，程序中对其进行解码

编译程序
make
运行程序
./test 

.测试说明
运行程序后，另外开一个命令行窗口，进入该文件夹
使用indata2测试数据
cp indata2 indata
输入以上命令，将得到以下结果
load file end 
add 
    hashval:7  id:20170007 name : name007 
    hashval:21  id:20170006 name : name006 
    hashval:36  id:20170001 name : name001 
    hashval:45  id:20170008 name : name008 
    hashval:61  id:20170003 name : name003 
    hashval:75  id:20170002 name : name002 
    hashval:85  id:20170005 name : name005 
    hashval:99  id:20170004 name : name004 
del 

使用indata3测试数据
cp indata3 indata
输入以上命令，将得到以下结果
load file end 
add 
    hashval:4  id:20170012 name : name012 
    hashval:18  id:20170013 name : name013 
    hashval:30  id:20170018 name : name018 
    hashval:43  id:20170011 name : name011 
    hashval:56  id:20170016 name : name016 
    hashval:70  id:20170017 name : name017 
    hashval:81  id:20170014 name : name014 
    hashval:95  id:20170015 name : name015 
del 