zrobot
======

**第一版Zrobot小车工程**  
* hw文件夹中为小车Vivado工程，使用Vivado 2013.4构建  
* sw文件夹中为小车linux 软件工程，app为用户空间程序， driver中包括了一个pwm驱动  
* libs文件夹为一些lib文件， 其中xil_io.h文件为linux用户空间直接对底层硬件寄存器进行读写的两个接口  
* ready_to_download文件夹下为最终系统运行所需的文件 
* source文件夹下为制作boot.bin的三个所需文件以及该工程的devicetree源文件
* Android文件夹下面为Android客户端的源工程文件。
# Getting Started
使用如下命令将工程下载到你的本地环境中  
  
  ```
  $git clone https://github.com/xupsh/zrobot_v1.git
  ```

## build hw
