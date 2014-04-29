#include "scores.h"
#include "ui_scores.h"
#include <QMessageBox>

scores::scores(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::scores)
{
    ui->setupUi(this);
    time_count = 0;
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timerout()));
}

scores::~scores()
{
    delete ui;
}

void scores::on_pushButton_file_clicked()
{
    path_music =QFileDialog::getOpenFileName(NULL,tr("Open a Wav Music File"),QDir::currentPath(),tr("Sound (*.wav)"));

    if((path_music.isEmpty()==false))
    {
        ui->pushButton_file->setText(path_music);
    }
}

void scores::on_pushButton_score_clicked()
{
    if((path_music.isEmpty()==true))
    {
        QMessageBox::about(NULL,tr("Warning"),tr("Please Open a Wav File First!"));
        return;
    }

    timer->start(100);

    detect = new detect_thread(this,path_music);

    connect(detect,SIGNAL(finished()),this,SLOT(showresult()));

    ui->pushButton_score->setEnabled(false);

    detect->start();

    return;
}

void scores::timerout()
{
    time_count+=0.1;
    ui->lcdNumber->display(time_count);
}

void scores::showresult()
{
    timer->stop();    
    delete detect;
    ui->pushButton_score->setEnabled(true);
    time_count=0;
    FILE *file;
    char buf[1024];
    int ret;

    if(!(file=fopen("./out","r")))
    {
        QMessageBox::about(this,tr("Error"),tr("No help file found!"));
        return;
    }

    while(!feof(file))
        {
            ret=fread(buf,1,1024,file);
            buf[ret]='\0';
            ui->textEdit->append(buf);
        }
    fclose(file);
}
