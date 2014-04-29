#ifndef DETECT_THREAD_H
#define DETECT_THREAD_H

#include <QThread>
#include <QString>

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
};

struct segment_music
{
  float *buffer;	//每一段的数据缓冲
  double     Freq_base;	//每一段的基频
  long       Energy;//每一段的能量
  bool       is_new;//端点标志
  unsigned char  yinfu;//每一段对应的音符
};


class detect_thread : public QThread
{
    Q_OBJECT
public:
    explicit detect_thread(QObject *parent = 0,QString filename="");

    virtual void run();

private:
    QString file;
    float cos_buf[360];
    
signals:
    
public slots:
    
};

#endif // DETECT_THREAD_H
