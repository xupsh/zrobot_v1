#include "play.h"
#include "ui_play.h"
#include <QMessageBox>
#include <unistd.h>

play::play(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::play)
{
    ui->setupUi(this);
}

play::~play()
{
    delete ui;
}

void play::on_pushButton_start_clicked()
{
    if((path_music.isEmpty()==true))
    {
        QMessageBox::about(NULL,tr("Warning"),tr("Please Open a Wav File First!"));
        return;
    }

    if(vfork()==0)
    {
        execlp("aplay","aplay",path_music.toAscii().data(),NULL);
    }
}

void play::on_pushButton_stop_clicked()
{
    system("pkill aplay");
}

void play::on_pushButton_file_clicked()
{
    path_music =QFileDialog::getOpenFileName(NULL,tr("Open a Wav Music File"),QDir::currentPath(),tr("Sound (*.wav)"));

    if((path_music.isEmpty()==false))
    {
        ui->pushButton_file->setText(path_music);
    }
}
