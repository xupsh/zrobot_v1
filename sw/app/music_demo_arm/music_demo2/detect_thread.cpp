#include "detect_thread.h"
#include <math.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#define Pa_41    120
#define Pa_161   Pa_41*2
#define Freq_Pa  (Pa_161/60)
#define PI       3.1415926
#define Freq_down  8


static float bf[4+1]={
        0.0006,
        0.0026,
        0.0038,
        0.0026,
        0.0006};

static float af[4+1]={
        1.0000,
       -3.0787,
        3.6372,
       -1.9432,
        0.3948};


detect_thread::detect_thread(QObject *parent,QString filename):QObject(parent)
{
    file = filename;

    for(int i=0;i<360;i++)
    {
        cos_buf[i]=cos(((double)i*PI/180));
    }
}

struct wavehead head_wav;//wav文件头
char   yinfu_t[]={'1','2','3','4','5','6','7','a','b','c','d','e','f','g'};
int    yinfu_b[]={120,140,160,170,190,212,240,255,285,315,335,380,420,485,510};

FILE* openwav(char *,struct wavehead *);
void  DCT_music(struct segment_music *arry,int length,int num);
void  Energy_music(struct segment_music *arry,int length,int num);
void filter(short input[],float output[],int FLENGTH,int ORDER);

unsigned char   findyinfu(double t);

unsigned char   findyinfu(double t)
{
  int i;
  bool flag = false;
  for(i=0;i<14;i++)
  {
    if(t>yinfu_b[i]&&t<yinfu_b[i+1])
    {
      flag = true;
      break;
    }
  }

  if(flag)
    return yinfu_t[i];
  return 0;
}

void  Energy_music(struct segment_music *arry,int length,int num)
{
  int  N = length/2/Freq_down;//每段中的样本点数
  int  window_w = N/2;
  /*
  for(int i=0;i<num;i++)
  {
    arry[i].Energy = 0;
    for(int k=0;k<N;k++)
    {
      arry[i].Energy += arry[i].buffer[k];
    }
  }
  */
  arry[0].is_new = true;
  for(int i=1;i<num;i++)
  {
    arry[i].is_new = true;
    if(arry[i].yinfu==arry[i-1].yinfu)
    {
      arry[i-1].Energy=0;
      arry[i].Energy=0;
      for(int k=0;k<window_w;k++)
      {
    arry[i-1].Energy += abs(arry[i-1].buffer[N-k]);
    arry[i].Energy += abs(arry[i].buffer[k]);
      }
      if(arry[i].Energy<=arry[i-1].Energy)
    arry[i].is_new = false;
      else
    arry[i].is_new = true;
    }

  }
}

void  DCT_music(struct segment_music *arry,int length,int num,float *cos_buf)
{
  int  N = length/2/Freq_down;//每段中的样本点数
  double *freq_arry = (double *)malloc(N*sizeof(double));//频谱序列
  int window_wigth = 501; //极值比较窗口大小


  for(int i=0;i<num;i++)
  {
    int    freq_max_n = 0;//最大值对应的序号
    //double freq_max = freq_arry[freq_max_n];//频率序列中的最大值
    int    freq_min_n = 0;//最小值对应的序号
    //double freq_min = freq_arry[freq_min_n];	//频率序列中的最小值
    double freq_base = 0;
    bool is_find_max = false;
    bool is_find_min = false;
    {
      /*计算频谱系数*/
      /*首先计算A0频谱系数*/
      double sum0=0;
      for(int k=0;k<N-1;k++)
      {
        sum0 += (arry[i].buffer[k]);
      }
      freq_arry[0] = sum0/sqrt(N);
      /*其次计算Aj频谱系数（0<j<N）*/
      for(int j=1;j<N-1;j++)
      {
    double sumj=0;
    for(int k=0;k<N-1;k++)
    {
      //sumj += (double)(arry[i].buffer[k]*cos(((double)k+0.5)*(double)j*PI/N));
        int seq = (int)(((double)k+0.5)*(double)j*180/N);
        if(seq>359)
        {
            seq = seq % 360;
        }
        sumj += (double)(arry[i].buffer[k]*cos_buf[seq]);
    }
    //printf("segment%d sum%d:%lf\n",i,j,sumj);
    freq_arry[j] = sumj*sqrt((double)(2.0/N));
    /*求取基频*/
    /*求取基频中的极值*/

    if(j>(freq_max_n+window_wigth/2))
    {
      /*取极大值*/
      is_find_max = true;
      {
        for(int m=1;m<(window_wigth/2+1);m++)
        {
          if(freq_max_n+m>N-1)
        break;
          if(freq_arry[freq_max_n]< freq_arry[freq_max_n+m])
          {
        is_find_max = false;
        freq_max_n+=m;
        break;
          }
        }

        if(is_find_max == true)
        {
          for(int m=1;m<(window_wigth/2+1);m++)
          {
        if(freq_max_n-m<1)
          break;
        if(freq_arry[freq_max_n]< freq_arry[freq_max_n-m])
        {
          is_find_max = false;
          freq_max_n += window_wigth;
          break;
        }
          }
        }
      }
    }


    if(j>(freq_max_n+window_wigth/2))
    {
      /*取极小值*/
      is_find_min = true;
      {
        for(int m=1;m<(window_wigth/2+1);m++)
        {
          if(freq_min_n+m>N-1)
        break;
          if(freq_arry[freq_min_n]> freq_arry[freq_min_n+m])
          {
        is_find_min = false;
        freq_min_n+=m;
        break;
          }
        }

        if(is_find_min == true)
        {
          for(int m=1;m<(window_wigth/2+1);m++)
          {
        if(freq_min_n-m<1)
          break;
        if(freq_arry[freq_min_n]> freq_arry[freq_min_n-m])
        {
          is_find_min = false;
          freq_min_n += window_wigth;
          break;
        }
          }
        }
      }
    }

    if(is_find_min&&is_find_max)
    {
      freq_base = (double)(freq_max_n + freq_min_n)/2;//得到广义基频
      arry[i].Freq_base = freq_base*head_wav.samplerate/2/N;

      while(arry[i].Freq_base<125)
      {
        arry[i].Freq_base*=2;
      }
      while(arry[i].Freq_base>250)
      {
        arry[i].Freq_base/=2;
      }

      //("segment%d freq_max_n:%d freq_min_n:%d\n",i,freq_max_n,freq_min_n);
      //printf("segment%d freq_base:%lf\n",i,arry[i].Freq_base);
      arry[i].yinfu = findyinfu(arry[i].Freq_base);
      break;
    }
      }
    }
  }
}

FILE* openwav(char *filename,struct wavehead *head)
{
    FILE *fd;
    int ret;

    if((fd=fopen(filename,"r"))==NULL)
    {
      //printf("cannot read the wave file：%s\n",filename);
      return NULL;
    }

    if((ret=fread(head,sizeof(wavehead),1,fd))!=1)
    {
      //printf("cannot get wavhead of %s\n",filename);
      return NULL;
    }

    return fd;
}

void filter(short *input,float *output,int FLENGTH,int ORDER)
{
    int i,j;
    float *inputbuff,*outputbuff;
    inputbuff=(float*)malloc(sizeof(float)*(FLENGTH+ORDER));
    outputbuff=(float*)malloc(sizeof(float)*(FLENGTH+ORDER));
    for (i=0;i<FLENGTH;i++)
        inputbuff[ORDER+i]=input[i]-0xffff;
    for (i=0;i<ORDER;i++)
    {
        inputbuff[i]=0;
        outputbuff[i]=0;
    }

    for(i=ORDER;i<FLENGTH+ORDER;i++)
    {
        outputbuff[i]=0;
        for(j=0;j<=ORDER;j++)
            outputbuff[i]+=bf[j]*inputbuff[i-j];
        for(j=1;j<=ORDER;j++)
            outputbuff[i]-=af[j]*outputbuff[i-j];
    }

    for(i=0;i<FLENGTH/Freq_down;i++)
    output[i]=outputbuff[i*Freq_down+ORDER];
}

void *run(void *data)
{
    detect_thread *t = (detect_thread *)data;
    char *file_in = t->file.toAscii().data();//输入文件
    char *file_out = "./out";//输出文件
    int  length_segment;//段的长度
    int  num_segment;//总分段数

    printf("The input wav file is %s\n",file_in);
    printf("The output file is %s\n",file_out);

    /*打开wav文件，并解析出文件头信息*/

    FILE *fp_in = openwav(file_in,&head_wav);

    {
      /*将wav文件头信息输出出来*/
      printf("Information about %s\n",file_in);
      printf("channel number: %d\n",head_wav.channelnum);
      printf("sample rate %ld\n",head_wav.samplerate);
      printf("sample length %d\n",head_wav.databitnum);
      printf("transfer rate %ld\n",head_wav.transferrate);
      printf("data length %ld\n",head_wav.datalength);
    }

    /*读出文件内容，以每秒Freq_Pa拍，十六分音符对应时值为步长将乐曲分段*/
    {
      /*计算一段的长度（字节）*/
      length_segment = ((float)head_wav.transferrate/Freq_Pa+0.5);
      printf("length of every segment：%d\n",length_segment);
      /*计算总分段数*/
      num_segment = (int)head_wav.datalength/length_segment;
      printf("total number of segments：%d\n",num_segment);
    }

    struct segment_music *segment_array;
    segment_array = (struct segment_music *)(malloc(num_segment*sizeof(segment_music)));

    //while(ftell(fp_in)!=sizeof(wavehead))
    {
      fseek(fp_in,sizeof(wavehead),SEEK_SET);
    }

    short *tmp_buffer = (short *)malloc(length_segment);
    //cout<<"hh"<<endl;
    for(int i=0;i<num_segment;i++)
    {
      fread(tmp_buffer,1,length_segment,fp_in);
      segment_array[i].buffer = (float *)malloc((length_segment/2/Freq_down+1)*sizeof(float));
      filter(tmp_buffer,segment_array[i].buffer,length_segment/2,4);
    }
    /*对每段进行离散余弦变换，提取基音频率*/
    DCT_music(segment_array,length_segment,num_segment,t->cos_buf);

    /*对每段能量求和，判断音符端点位置*/
    Energy_music(segment_array,length_segment,num_segment);

    /*输出曲谱*/
    FILE *fp_out;
    fp_out = fopen(file_out,"w+");
    fprintf(fp_out,"Qu Pu:\n");
    for(int i=0;i<num_segment;i++)
    {
      if(segment_array[i].is_new==true&&segment_array[i].yinfu!=0)
      {
    fprintf(fp_out,"%c ",segment_array[i].yinfu);
      }
    }
    fprintf(fp_out,"\nEnd");
    fclose(fp_out);
    fclose(fp_in);
    //emit t->finished();
    return NULL;
}

void detect_thread::start()
{
    pthread_t pid;
    //pthread_create(&pid,NULL,run,(void *)this);
    run((void *)this);
    return;
}
