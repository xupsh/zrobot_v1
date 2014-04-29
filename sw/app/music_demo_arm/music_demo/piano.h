#ifndef PIANO_H
#define PIANO_H

#include <QDialog>


namespace Ui {
class piano;
}

class piano : public QDialog
{
    Q_OBJECT
    
public:
    explicit piano(QWidget *parent = 0);
    ~piano();
    
private slots:
    void on_pushButton_1_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_record_clicked();

private:
    Ui::piano *ui;
    QString qupu;
};

#endif // PIANO_H
