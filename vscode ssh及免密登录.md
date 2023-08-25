[新窗口打开项目文件]
1.管理(左下齿轮)->设置->搜索open->找到Open Floders In New Windos->设置on

[ssh]
1.安装Remote-SSH插件
2.左下角(打开远程窗口)Connect to host->Configure SSH Hosts->C:\User\Administrator\.ssh\config(第一个)
3.粘贴保存
Host Ubuntu_22.04
         HostName 60.204.204.220
         User root
4. 左下角(打开远程窗口)Connect to host->点击远程服务器(Ubuntu_22.04已显示)
5. 输入密码


[免密登录]
本地端：
1. ssh -keygen(生成公钥)
2. 回车直到出现
Your identification has been saved in C:\Users\Administrator/.ssh/id_rsa.       
Your public key has been saved in C:\Users\Administrator/.ssh/id_rsa.pub.
3.cat C:\Users\Administrator/.ssh/id_rsa.pub.复制内容

云端：
1. 开放修改权限
sudo chmod 600 authorized_keys
sudo chmod 700 ~/.ssh
2. vim /root/.ssh/authorized_keys 粘贴复制的内容(若原先有则另起一行附加上)保存
3. sudo service sshd restart 重启ssh
4. 本地端Connect to host即可免密
