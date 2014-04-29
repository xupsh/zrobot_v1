#ifndef SCORES_H
#define SCORES_H

#include <QDialog>
#include <QDialog>
#include <QFileDialog>
#include <sys/time.h>
#include "detect_thread.h"

namespace Ui {
class scores;
}

class scores : public QDialog
{
    Q_OBJECT
    
public:
    explicit scores(QWidget *parent = 0);
    ~scores();
    
private:
    QString path_music;
    bool isfinish;
    //QTimer *timer;
    float  time_count;

private slots:
    void on_pushButton_file_clicked();

    void on_pushButton_score_clicked();

    void timerout(QTimerEvent *event);

    void showresult();

private:
    Ui::scores *ui;
    struct timeval tv_before;
    struct timeval tv_after;
    detect_thread *detect;
};

#endif // SCORES_H
