/********************************************************************************
** Form generated from reading UI file 'play.ui'
**
** Created: Fri Jul 26 20:44:16 2013
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLAY_H
#define UI_PLAY_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_play
{
public:
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_file;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *pushButton_start;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *pushButton_stop;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *verticalSpacer;

    void setupUi(QDialog *play)
    {
        if (play->objectName().isEmpty())
            play->setObjectName(QString::fromUtf8("play"));
        play->resize(800, 480);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icon/icon/w.png"), QSize(), QIcon::Normal, QIcon::Off);
        play->setWindowIcon(icon);
        play->setStyleSheet(QString::fromUtf8("border-image:url(:/image/play.png)"));
        verticalLayout = new QVBoxLayout(play);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton_file = new QPushButton(play);
        pushButton_file->setObjectName(QString::fromUtf8("pushButton_file"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton_file->sizePolicy().hasHeightForWidth());
        pushButton_file->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        font.setItalic(true);
        font.setWeight(75);
        pushButton_file->setFont(font);
        pushButton_file->setStyleSheet(QString::fromUtf8("border-image:url(:/icon/icon/choice.png)"));

        horizontalLayout->addWidget(pushButton_file);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 2);
        horizontalLayout->setStretch(2, 1);

        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        pushButton_start = new QPushButton(play);
        pushButton_start->setObjectName(QString::fromUtf8("pushButton_start"));
        pushButton_start->setEnabled(true);
        sizePolicy.setHeightForWidth(pushButton_start->sizePolicy().hasHeightForWidth());
        pushButton_start->setSizePolicy(sizePolicy);
        pushButton_start->setCursor(QCursor(Qt::ArrowCursor));
        pushButton_start->setStyleSheet(QString::fromUtf8("border-image:url(:/icon/icon/start.png)"));

        horizontalLayout_2->addWidget(pushButton_start);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);

        pushButton_stop = new QPushButton(play);
        pushButton_stop->setObjectName(QString::fromUtf8("pushButton_stop"));
        pushButton_stop->setEnabled(true);
        sizePolicy.setHeightForWidth(pushButton_stop->sizePolicy().hasHeightForWidth());
        pushButton_stop->setSizePolicy(sizePolicy);
        pushButton_stop->setStyleSheet(QString::fromUtf8("border-image:url(:/icon/icon/stop.png)"));

        horizontalLayout_2->addWidget(pushButton_stop);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_5);

        horizontalLayout_2->setStretch(0, 2);
        horizontalLayout_2->setStretch(1, 2);
        horizontalLayout_2->setStretch(2, 3);
        horizontalLayout_2->setStretch(3, 2);
        horizontalLayout_2->setStretch(4, 2);

        verticalLayout->addLayout(horizontalLayout_2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        verticalLayout->setStretch(0, 1);
        verticalLayout->setStretch(1, 2);
        verticalLayout->setStretch(2, 1);
        verticalLayout->setStretch(3, 3);
        verticalLayout->setStretch(4, 1);

        retranslateUi(play);

        QMetaObject::connectSlotsByName(play);
    } // setupUi

    void retranslateUi(QDialog *play)
    {
        play->setWindowTitle(QApplication::translate("play", "PLAY MUSIC", 0, QApplication::UnicodeUTF8));
        pushButton_file->setText(QString());
        pushButton_start->setText(QString());
        pushButton_stop->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class play: public Ui_play {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLAY_H
