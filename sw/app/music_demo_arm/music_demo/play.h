#ifndef PLAY_H
#define PLAY_H

#include <QDialog>
#include <QString>
#include <QDialog>
#include <QFileDialog>


namespace Ui {
class play;
}

class play : public QDialog
{
    Q_OBJECT
    
public:
    explicit play(QWidget *parent = 0);
    ~play();

private:
    QString path_music;
    
private slots:
    void on_pushButton_file_clicked();

    void on_pushButton_start_clicked();

    void on_pushButton_stop_clicked();

private:
    Ui::play *ui;
};

#endif // PLAY_H
