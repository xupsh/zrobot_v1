#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct wavehead
{
    char sign[4];         //"RIFF"标志
    long int flength;     //文件长度
    char wavesign[4];     //"WAVE"标志
    char fmtsign[4];      //"fmt"标志
    long int unused;      // 过渡字节（不定）
    short formattype;     //格式类别（10H为PCM形式的声音数据)
    short  channelnum;    //通道数，单声道为1，双声道为2
    long int  samplerate; //采样率（每秒样本数），表示每个通道的播放速度
    long int transferrate;//波形音频数据传送速率，其值为通道数×每秒数据位数×每样
                          //本的数据位数／8。播放软件利用此值可以估计缓冲区的大小
    short int adjustnum;  //数据块的调整数（按字节算的），其值为通道数×每样本的数据位值／8。
                          //播放软件需要一次处理多个该值大小的字节数据，以便将其值用于缓冲区的调整。
    short int databitnum; //每样本的数据位数，表示每个声道中各个样本的数据位数
    char datasign[4];     //数据标记符＂data＂
    long int datalength;  //语音数据的长度(字节）
} head_wav;

const char *out_file = "output.wav";
char in_file[10]={'\0'};

int main(int argc,char **argv)
{
  int num_yinfu = argc - 1;
  int res,res_write,res_read;
  FILE *fp_out,*fp_in;
  char *ptr;
  
  res = access(out_file,F_OK);
  if(res == 0)
  {
    remove(out_file);
  }
  
  fp_out = fopen(out_file,"w+");
  if(fp_out == NULL)
  {
    printf("Can not creat output file!\n");
    exit(0);
  }
  
  //写入原始头部
  while((fwrite((char *)&head_wav,1,sizeof(head_wav),fp_out))!=sizeof(head_wav))
  {
    fseek(fp_out,0,SEEK_SET);
  }
  
  
  //定位歌曲到数据区
  while(ftell(fp_out)!=sizeof(head_wav)) 
  {
    fseek(fp_out,sizeof(head_wav),SEEK_SET);
  }  
  
  int i;
  long int length=0;
  char *buffer;  
  
  for(i=1;i<=num_yinfu;i++)
  {
    memset(in_file,'\0',sizeof(in_file));
    sprintf(in_file,"%s.wav",argv[i]);
    
    fp_in = fopen(in_file,"r");
    if(fp_in == NULL)
    {
      printf("Can not open yinfu file %s!\n",in_file);
      continue;
    }
    
    fread(&head_wav,sizeof(head_wav),1,fp_in);
    length += head_wav.datalength;
    buffer = malloc(head_wav.datalength);
    //printf("datalength:%d\n",head_wav.datalength);
    
    
    //定位歌曲到数据区
    while(ftell(fp_in)!=sizeof(head_wav)) 
    {
      fseek(fp_in,sizeof(head_wav),SEEK_SET);
    }
    
    
    
    do{
      res = fread(buffer,1,head_wav.datalength,fp_in);
      res_read = res;
      ptr = buffer;
      res_write = 0;
      //printf("res_read:%d\n",res);
      do{        
        res_read -= res_write;
        ptr += res_write;
        res_write = fwrite(ptr,1,res_read,fp_out);  
        //printf("res_write:%d\n",res_write);              
      }while(res_write<res_read);
    }while(res<head_wav.datalength);
           
    //printf("add yinfu %s\n",in_file);
    free(buffer);
    fclose(fp_in);
  } 
  
  //定位到文件头部
  while(ftell(fp_out)!=0) 
  {
    fseek(fp_out,0,SEEK_SET);
  } 
  
  //更新输出文件的头部
  head_wav.datalength = length;
  //head_wav.channelnum = 2;
  while((fwrite((char *)&head_wav,1,sizeof(head_wav),fp_out))!=sizeof(head_wav))
  {
    fseek(fp_out,0,SEEK_SET);
  }
  
  fclose(fp_out);
  chmod(out_file,0777);
  
  exit(1);
}
