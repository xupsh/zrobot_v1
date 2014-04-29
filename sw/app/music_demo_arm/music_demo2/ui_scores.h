/********************************************************************************
** Form generated from reading UI file 'scores.ui'
**
** Created: Sat Jul 27 13:24:22 2013
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCORES_H
#define UI_SCORES_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLCDNumber>
#include <QtGui/QPushButton>
#include <QtGui/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_scores
{
public:
    QTextEdit *textEdit;
    QPushButton *pushButton_file;
    QPushButton *pushButton_score;
    QLCDNumber *lcdNumber;

    void setupUi(QDialog *scores)
    {
        if (scores->objectName().isEmpty())
            scores->setObjectName(QString::fromUtf8("scores"));
        scores->resize(800, 480);
        scores->setStyleSheet(QString::fromUtf8("border-image:url(:/image/recoed.png)"));
        textEdit = new QTextEdit(scores);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(450, 20, 341, 241));
        textEdit->setStyleSheet(QString::fromUtf8("border-image:url(:/image/yuepu.png)"));
        pushButton_file = new QPushButton(scores);
        pushButton_file->setObjectName(QString::fromUtf8("pushButton_file"));
        pushButton_file->setGeometry(QRect(120, 30, 281, 111));
        pushButton_file->setStyleSheet(QString::fromUtf8("border-image:url(:/icon/icon/choice.png)"));
        pushButton_score = new QPushButton(scores);
        pushButton_score->setObjectName(QString::fromUtf8("pushButton_score"));
        pushButton_score->setGeometry(QRect(68, 143, 191, 171));
        pushButton_score->setStyleSheet(QString::fromUtf8("border-image:url(:/icon/icon/r.png)"));
        lcdNumber = new QLCDNumber(scores);
        lcdNumber->setObjectName(QString::fromUtf8("lcdNumber"));
        lcdNumber->setGeometry(QRect(450, 280, 341, 161));
        QPalette palette;
        QBrush brush(QColor(255, 255, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        QBrush brush1(QColor(159, 158, 158, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        lcdNumber->setPalette(palette);
        lcdNumber->setStyleSheet(QString::fromUtf8("border-image:rgb(255, 255, 255)"));
        lcdNumber->setSmallDecimalPoint(true);
        lcdNumber->setNumDigits(5);
        lcdNumber->setDigitCount(5);
        lcdNumber->setSegmentStyle(QLCDNumber::Flat);

        retranslateUi(scores);

        QMetaObject::connectSlotsByName(scores);
    } // setupUi

    void retranslateUi(QDialog *scores)
    {
        scores->setWindowTitle(QApplication::translate("scores", "Dialog", 0, QApplication::UnicodeUTF8));
        pushButton_file->setText(QString());
        pushButton_score->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class scores: public Ui_scores {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCORES_H
