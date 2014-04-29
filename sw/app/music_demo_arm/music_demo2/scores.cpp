#include "scores.h"
#include "ui_scores.h"
#include <QMessageBox>

scores::scores(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::scores)
{
    ui->setupUi(this);
    time_count = 0;
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

    time_count = 0;

    gettimeofday(&tv_before,NULL);

    detect = new detect_thread(this,path_music);    

    ui->pushButton_score->setEnabled(false);

    detect->start();

    gettimeofday(&tv_after,NULL);

    showresult();

    return;
}

void scores::timerout(QTimerEvent *event)
{
    time_count+=0.1;
    ui->lcdNumber->display(time_count);
}

void scores::showresult()
{
    delete detect;
    ui->pushButton_score->setEnabled(true);
    time_count=(tv_after.tv_sec-tv_before.tv_sec)+(tv_after.tv_usec-tv_before.tv_usec)*0.000001;
    ui->lcdNumber->display(time_count);
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
