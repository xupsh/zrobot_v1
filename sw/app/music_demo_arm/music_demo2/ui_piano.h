/********************************************************************************
** Form generated from reading UI file 'piano.ui'
**
** Created: Fri Jul 26 20:44:16 2013
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PIANO_H
#define UI_PIANO_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTextEdit>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_piano
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QTextEdit *textEdit;
    QPushButton *pushButton_record;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_1;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QPushButton *pushButton_7;
    QPushButton *pushButton_8;

    void setupUi(QDialog *piano)
    {
        if (piano->objectName().isEmpty())
            piano->setObjectName(QString::fromUtf8("piano"));
        piano->resize(800, 480);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icon/icon/e.png"), QSize(), QIcon::Normal, QIcon::Off);
        piano->setWindowIcon(icon);
        piano->setStyleSheet(QString::fromUtf8("border-image:url(:/image/piano.png)"));
        verticalLayout = new QVBoxLayout(piano);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, -1, 0, -1);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(10);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        textEdit = new QTextEdit(piano);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        font.setItalic(true);
        font.setWeight(75);
        textEdit->setFont(font);
        textEdit->setStyleSheet(QString::fromUtf8("border-image:rurl(:/image/yuepu.png)"));

        horizontalLayout_2->addWidget(textEdit);

        pushButton_record = new QPushButton(piano);
        pushButton_record->setObjectName(QString::fromUtf8("pushButton_record"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton_record->sizePolicy().hasHeightForWidth());
        pushButton_record->setSizePolicy(sizePolicy);
        pushButton_record->setStyleSheet(QString::fromUtf8("border-image:url(:/icon/icon/q.png)"));

        horizontalLayout_2->addWidget(pushButton_record);

        horizontalLayout_2->setStretch(0, 5);
        horizontalLayout_2->setStretch(1, 1);

        verticalLayout->addLayout(horizontalLayout_2);

        verticalSpacer = new QSpacerItem(20, 47, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, -1, 25, -1);
        pushButton_1 = new QPushButton(piano);
        pushButton_1->setObjectName(QString::fromUtf8("pushButton_1"));
        sizePolicy.setHeightForWidth(pushButton_1->sizePolicy().hasHeightForWidth());
        pushButton_1->setSizePolicy(sizePolicy);
        pushButton_1->setStyleSheet(QString::fromUtf8("border-image:rgb(255, 255, 255)"));
        pushButton_1->setFlat(true);

        horizontalLayout->addWidget(pushButton_1);

        pushButton_2 = new QPushButton(piano);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        sizePolicy.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
        pushButton_2->setSizePolicy(sizePolicy);
        pushButton_2->setStyleSheet(QString::fromUtf8("border-image:rgb(255, 255, 255)"));
        pushButton_2->setFlat(true);

        horizontalLayout->addWidget(pushButton_2);

        pushButton_3 = new QPushButton(piano);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        sizePolicy.setHeightForWidth(pushButton_3->sizePolicy().hasHeightForWidth());
        pushButton_3->setSizePolicy(sizePolicy);
        pushButton_3->setStyleSheet(QString::fromUtf8("border-image:rgb(255, 255, 255)"));
        pushButton_3->setFlat(true);

        horizontalLayout->addWidget(pushButton_3);

        pushButton_4 = new QPushButton(piano);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        sizePolicy.setHeightForWidth(pushButton_4->sizePolicy().hasHeightForWidth());
        pushButton_4->setSizePolicy(sizePolicy);
        pushButton_4->setStyleSheet(QString::fromUtf8("border-image:rgb(255, 255, 255)"));
        pushButton_4->setFlat(true);

        horizontalLayout->addWidget(pushButton_4);

        pushButton_5 = new QPushButton(piano);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        sizePolicy.setHeightForWidth(pushButton_5->sizePolicy().hasHeightForWidth());
        pushButton_5->setSizePolicy(sizePolicy);
        pushButton_5->setStyleSheet(QString::fromUtf8("border-image:rgb(255, 255, 255)"));
        pushButton_5->setFlat(true);

        horizontalLayout->addWidget(pushButton_5);

        pushButton_6 = new QPushButton(piano);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        sizePolicy.setHeightForWidth(pushButton_6->sizePolicy().hasHeightForWidth());
        pushButton_6->setSizePolicy(sizePolicy);
        pushButton_6->setStyleSheet(QString::fromUtf8("border-image:rgb(255, 255, 255)"));
        pushButton_6->setFlat(true);

        horizontalLayout->addWidget(pushButton_6);

        pushButton_7 = new QPushButton(piano);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));
        sizePolicy.setHeightForWidth(pushButton_7->sizePolicy().hasHeightForWidth());
        pushButton_7->setSizePolicy(sizePolicy);
        pushButton_7->setStyleSheet(QString::fromUtf8("border-image:rgb(255, 255, 255)"));
        pushButton_7->setFlat(true);

        horizontalLayout->addWidget(pushButton_7);

        pushButton_8 = new QPushButton(piano);
        pushButton_8->setObjectName(QString::fromUtf8("pushButton_8"));
        pushButton_8->setEnabled(false);
        sizePolicy.setHeightForWidth(pushButton_8->sizePolicy().hasHeightForWidth());
        pushButton_8->setSizePolicy(sizePolicy);
        pushButton_8->setStyleSheet(QString::fromUtf8("border-image:rgb(255, 255, 255)"));
        pushButton_8->setFlat(true);

        horizontalLayout->addWidget(pushButton_8);


        verticalLayout->addLayout(horizontalLayout);

        verticalLayout->setStretch(0, 3);
        verticalLayout->setStretch(1, 1);
        verticalLayout->setStretch(2, 5);

        retranslateUi(piano);

        QMetaObject::connectSlotsByName(piano);
    } // setupUi

    void retranslateUi(QDialog *piano)
    {
        piano->setWindowTitle(QApplication::translate("piano", "Dialog", 0, QApplication::UnicodeUTF8));
        textEdit->setHtml(QApplication::translate("piano", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:16pt; font-weight:600; font-style:italic;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:11pt; font-weight:400; font-style:normal;\"><br /></p></body></html>", 0, QApplication::UnicodeUTF8));
        pushButton_record->setText(QString());
        pushButton_1->setText(QString());
        pushButton_2->setText(QString());
        pushButton_3->setText(QString());
        pushButton_4->setText(QString());
        pushButton_5->setText(QString());
        pushButton_6->setText(QString());
        pushButton_7->setText(QString());
        pushButton_8->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class piano: public Ui_piano {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PIANO_H
