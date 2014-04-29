#include "piano.h"
#include "ui_piano.h"
#include <QMessageBox>

piano::piano(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::piano)
{
    ui->setupUi(this);
    qupu="";
}

piano::~piano()
{
    delete ui;
}

void piano::on_pushButton_1_clicked()
{
    qupu.append("1 ");
    ui->textEdit->setText(qupu);

    system("aplay 1.wav");
}

void piano::on_pushButton_2_clicked()
{
    qupu.append("2 ");
    ui->textEdit->setText(qupu);
    system("aplay 2.wav");
}

void piano::on_pushButton_3_clicked()
{
    qupu.append("3 ");
    ui->textEdit->setText(qupu);
    system("aplay 3.wav");
}

void piano::on_pushButton_4_clicked()
{
    qupu.append("4 ");
    ui->textEdit->setText(qupu);
    system("aplay 4.wav");
}

void piano::on_pushButton_5_clicked()
{
    qupu.append("5 ");
    ui->textEdit->setText(qupu);
    system("aplay 5.wav");
}

void piano::on_pushButton_6_clicked()
{
    qupu.append("6 ");
    ui->textEdit->setText(qupu);
    system("aplay 6.wav");
}

void piano::on_pushButton_7_clicked()
{
    qupu.append("7 ");
    ui->textEdit->setText(qupu);
    system("aplay 7.wav");
}

void piano::on_pushButton_record_clicked()
{
    QString cmd = "./mksound ";
    cmd.append(qupu);
    system(cmd.toAscii().data());
    QMessageBox::about(NULL,tr("Warning"),tr("Make a new song named output.wav!"));
}
