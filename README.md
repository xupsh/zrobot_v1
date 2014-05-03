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
# Building Vivado Project
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
* 关于pwm控制模块，请参考hw/ipcores目录下的AXI_PWM_1.0/，请仔细阅读其HDL代码。

## Building Software
在zrobot_v1/sw/app/文件夹下是本小车相关的一些应用程序。
* 其中mjpeg_face_leaf_detection文件夹下是将Opencv树叶识别加入到mjpg程序中的一个demo; 
* music_demo_arm文件夹下是在zedboard下使用QT实现的一个音乐应用;
* smart_car_CGI是一些从网页控制小车的接口;
* smart_car_webpage是我们自己做个一个控制小车的页面;

这里我们主要关心的是smart_car_socket文件夹，这里面主要是一个socket服务器，它不断的监听来自android手机的请求， 并解析请求数据包， 进而调用xil_io.h中的io函数， 直接对vivado工程中定义的小车寄存器进行控制进行控制。 这里我们没有使用内核驱动的方式而是直接在用户空间中来对小车的寄存器进行读写， 这样可以方便对应用程序的调试， 同时也很方便我们来进行应用程序的编写， 具体请参考zrobot_v1/libs文件夹下的xil_io.h文件。  
这里用到的socket服务器还不够完善， 没有进行多线程的处理，只对单用户模式进行处理， 具体请参考zynq_server_arm.c文件中的详细代码。使用如下命令来对socket服务器进行构建， 具体请参考Makefile文件。
  ```
  $cd ~/zrobot_v1/sw/app/smart_car_socket/
  $make
  ```
自此，我们的软件程序构建完成， 对于其他的程序请根据实际情况进行添加。在编译完成后，在smar_car_socket文件夹下会生成一个 zynq_server_arm.o文件，这就是我们所需要的可运行程序。

## Building BOOT.BIN
BOOT.bin文件是系统的启动镜像， 它由三个文件组成，第一个是在SDK中生成的fsbl.elf文件， 第二个是系统的bit文件， 第三个是u-boot.elf文件，在zrobot_v1/source目录下可以找到这三个文件, 在该目录中还有一个output.bif文件， 该文件用于bootgen命令的输入，具体可以使用文本编辑器打开该文件， 查看其具体结构。  
将source文件夹复制到windows C盘，依次点击Start > All Program > Xilinx Design Tools > Vivado 2013.4 > SDK > Xilinx Microprocess Debugger20134.4打开XMD控制台，使用如下命令生成BOOT.bin。
  ```
  $cd C:\source\
  $bootgen -image output.bif -o i BOOT.BIN -w on
  ```

## Booting on Linux
对于如何编译uboot、uImage、uramdisk.image.gz以及devicetree.dtb就不在进行讲解了， 具体请参考嵌入式系统软硬件系统设计实战指南或者Xilinx wiki:   
http://www.wiki.xilinx.com/Getting+Started   
这里注意一点的是， 在编译uImage的时候， 由于要加入对v4l2的支持， 所以请使用source文件夹下的xup_zed_defconfig文件对内核进行配置，可以直接将该文件拷贝到内核源码根目录，并将其重命名为.config，然后再对内核进行编译;  
对于devicetree.dtb的制作， 请使用source目录下的zrobot_v1_1.dts文件，该文件在SDK中生成， 关于如何在SDK中生成devicetree.dts请参考：  
http://www.wiki.xilinx.com/Build+Device+Tree+Blob  
在ready_to_download文件夹下是一个可以运行的完整系统， 请仔细阅读该文件夹下的init.sh文件， 该文件描述了如何对系统相关的服务进行启动。  
将ready_to_download文件夹下的所有的文件复制到SD卡的FAT分区， 设置ZedBoard跳线从SD卡启动。观察串口打印信息。  

## Building Android
对于android环境的搭建请参考:http://developer.android.com/index.html  
打开eclipse， 将该工程导入到工作空间， 系统会自动进行编译， 将程序下载到android 手机，点击Connect按钮建立TCP连接， 进而通过相关的摇杆对小车进行控制，你还可以点击Video查看小车视频。这里需要注意的是手机的android版本应该在2.2以上、4.2以下。当然， 在android\bin\目录下已经存在编译好的apk文件， 你可以直接下载到你的手机中进行运用。
