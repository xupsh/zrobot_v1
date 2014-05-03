zrobot
======

**第一版Zrobot小车工程**  
* hw文件夹中为小车Vivado工程，使用Vivado 2013.4构建  
* sw文件夹中为小车linux 软件工程，app为用户空间程序， driver中包括了一个pwm驱动  
* libs文件夹为一些lib文件， 其中xil_io.h文件为linux用户空间直接对底层硬件寄存器进行读写的两个接口  
* ready_to_download文件夹下为最终系统运行所需的文件 
* source文件夹下为制作boot.bin的三个所需文件以及该工程的devicetree源文件
* Android文件夹下面为Android客户端的源工程文件。  
* 本工程推荐使用Windows7 + Ubuntu2012.04虚拟机的环境来进行开发
* 本工程的Vivado硬件工程， Boot.bin文件的制作都是使用tcl命令以及SDK命令行的方式进行构建。

# Getting Started
在开始之前， 首先你得构建好系统环境，如果你还没有安装vivado 2013.4， 请到如下地址下载安装：  
  http://www.xilinx.com/support/download/index.html/content/xilinx/en/downloadNav/vivado-design-tools/2013-4.html  
对于虚拟机， 你可以使用vmware或者vitualbox, 这里我们推荐大家使用vitualbox， 具体的下载、安装及使用，请参考官网  
  https://www.virtualbox.org/  
在Ubuntu虚拟机中， 使用git命令将工程clone到你的本地目录中  
  ```
  $cd ~
  $git clone https://github.com/xupsh/zrobot_v1.git
  ```
如果你还没有安装git命令，使用如下命令进行安装：  
  ```
  $sudo apt-get update
  $sudo apt-get install git
  ```
关于git的详细介绍请参考:http://git-scm.com/  
本工程的软件程序使用交叉编译的方式在ubuntu虚拟机中进行开发， 使用如下命令构建交叉编译环境。
  ```
  $cd ~
  $git clone https://github.com/xupsh/CodeSoucery.git
  $echo “export PATH=~/CodeSourcery/bin:$PATH” >>  ~/.bashrc
  $echo “export CROSS_COMPILE=arm-xilinx-linux-gnueabi-“ >> ~/.bashrc
  ```
关于构建工程目录：如果没有特殊说明， 在windows下的工程都默认放到C盘， 在虚拟机中默认放到用户根目录(~)中。
# build hw
