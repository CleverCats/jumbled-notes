# 推荐pycharm19版, 新版pycharm与Anaconda有兼容问题

--安装Anaconda及pytorch---
# 查看现有环境
conda env list
# 创建环境
conda create -n pytorch(环境名称) python=3.6
# 进入/激活环境
conda activate pytorch
# 查看当前环境下的包
conda pip list
------------------------------
# pytorch安装
[本地或者官网]
# 卸载旧pytorch
conda uninstall pytorch
# 卸载cpu锁
[torch.cuda.is_avaliable()==False原因]
conda uninstall pytorch-mutex
# 官网源码安装
conda install pytorch torchvision torchaudio cudatoolkit=10.2 -c pytorch
# 本地源码安装-文件置于Anaconda3\pkgs中）
conda install --use-local G:\Anaconda3\pkgs\cudatoolkit-9.2-0.tar.bz2
conda install --use-local G:\Anaconda3\pkgs\pytorch-1.3.0-py3.6_cuda92_cudnn7_0.tar.bz2
# 是否使用gpu训练
torch.cuda.is_avaliable()

----安装pycharm添加conda环境 py19----
file->
setting->
'project_name'->
project interpreter->
add->
Exisiting interpreter->
G:\Anaconda3\envs\'env_name'\python.exe
重启电脑

----安装pycharm添加conda环境 py23----
1st）Exisiting interpreter->
Conda Environment->
G:\Anaconda3\Library\bin\conda.bat->
[或根目录下的_conda.exe,不要选择在script目录下的]
[较老版本可以直接添加envs/env_name/python.exe]
->Load Environments
->选择conda虚拟环境
2st）Virtual Environment->
Base interpreter->
[‪G:\Anaconda3\envs\py3.10\python.exe]
重启电脑

---安装jupyter notebook--
#activate环境
conda activate pytorch
#本地安装ipykernel
conda install --use-local G:\ipykernel-4.6.1-py36_0.tar.bz2
#本地安装nb_conda_kernels
conda install --use-local G:\nb_conda_kernels-2.0.0-py36_0.tar.bz2
# 启动jupyter notebook
jupyter notebook
# 若无anaconda中的环境则重启电脑, 再次查看, 若仍无, 在环境中执行下述命令手动添加
# pytorch环境中运行, 将当前环境pytorch 添加内核并别名Python [conda env:pytorch]
python -m ipykernel install --user --name pytorch --display-name "Python [conda env:pytorch]"
----------------------------
# 安装内核
conda install ipykernel
python -m ipykernel install --name mmlab
# 显示所有内核
jupyter kernelspec list
# 删除某个jupyter内核
jupyter kernelspec remove kernelname
# 删除虚拟环境
conda remove -n your_env_name(虚拟环境名称) --all
# 删除当前环境下的某个包
conda remove --name $your_env_name  $package_name（包名） 
# 通过whl本地安装opencv-python 3.6适配版本
pip install G:\opencv_python-4.1.0.25-cp36-cp36m-win_amd64.whl
# diff sta
pip install D:\Microsofe下载\torch-2.0.1+cu118-cp310-cp310-win_amd64.whl
# 恢复默认源
conda config --remove-key channels

# 环境导出
conda activate your_environment
conda env export > environment.yaml
conda env create -f environment.yaml

# 环境克隆
conda create --name timer_clone --clone timer

