#include "maindialog.h"
#include "ui_maindialog.h"
#include "play.h"
#include "piano.h"
#include "scores.h"

MainDialog::MainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainDialog)
{
    ui->setupUi(this);
}

MainDialog::~MainDialog()
{
    delete ui;
}

void MainDialog::on_pushButton_play_clicked()
{
    play *d = new play(this);

    d->exec();

    delete d;
    return;
}

void MainDialog::on_pushButton_qupu_clicked()
{
    piano *d = new piano(this);

    d->exec();

    delete d;
    return;
}

void MainDialog::on_pushButton_piano_clicked()
{
    scores *d = new scores(this);

    d->exec();

    delete d;
    return;
}
