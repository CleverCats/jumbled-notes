迁移wsl2
1. wsl -l -v 查看版本名称
2. wsl --shutdown
3. wsl --export Ubuntu-20.04 F:/export.tar 压缩成export.tar导入Ubuntu-20.04到F盘
4. wsl --unregister Ubuntu-20.04 卸载并注销原所在盘的wsl
5. wsl --import Ubuntu F:\export\ F:\export.tar --version 2  将导出的文件放到需要保存的地方, 并进行导入
6. Ubuntu config --default-user serein