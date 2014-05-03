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
# building vivado project
* 将hw目录从虚拟机中拷贝到为windows C盘根目录。
* 打开Vivado2013.4 软件。
* 在Vivado软件的下方TCL窗口中，输入如下命令构建硬件工程。具体过程， 请阅读相关的tcl文件命令。
  ```
  $cd C:\hw\vivado\
  $source system_project.tcl
  ```
* 等待工程构建结束， 这一过程大约需要30分钟左右。
* 当工程构建结束， 在C:\hw\vivado目录下已经生成了一个完整的工程，包括系统bit文件，以及硬件导入到SDK的目录等。
* 打开SDK软件， 将workplace定位到/path/zrobot_v1.sdk/SDK/SDK_Export目录，对硬件工程进行测试.
* 在SDK中新建一个helloworld工程，导入C:\hw\sw\helloworld.c文件， 使用xilinx tools将bit文件下载到板子上，运行helloworld程序，如果四个轮子依次转动， 说明，硬件工程构建成功。
* 
