/********************************************************************************
** Form generated from reading UI file 'maindialog.ui'
**
** Created: Fri Jul 26 20:44:16 2013
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINDIALOG_H
#define UI_MAINDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_MainDialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_2;
    QLabel *label;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *pushButton_play;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButton_qupu;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_piano;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *verticalSpacer_3;

    void setupUi(QDialog *MainDialog)
    {
        if (MainDialog->objectName().isEmpty())
            MainDialog->setObjectName(QString::fromUtf8("MainDialog"));
        MainDialog->setWindowModality(Qt::ApplicationModal);
        MainDialog->resize(1024, 768);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icon/icon/r_record.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainDialog->setWindowIcon(icon);
        MainDialog->setLayoutDirection(Qt::LeftToRight);
        MainDialog->setStyleSheet(QString::fromUtf8("border-image:url(:/image/main1.png)"));
        verticalLayout_2 = new QVBoxLayout(MainDialog);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        label = new QLabel(MainDialog);
        label->setObjectName(QString::fromUtf8("label"));
        QPalette palette;
        QBrush brush(QColor(0, 85, 127, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        QBrush brush1(QColor(159, 158, 158, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        label->setPalette(palette);
        QFont font;
        font.setPointSize(100);
        font.setBold(true);
        font.setItalic(true);
        font.setUnderline(false);
        font.setWeight(75);
        label->setFont(font);
        label->setContextMenuPolicy(Qt::DefaultContextMenu);
        label->setStyleSheet(QString::fromUtf8("border-image:rgb(255, 255, 255)"));
        label->setScaledContents(false);
        label->setAlignment(Qt::AlignCenter);
        label->setWordWrap(false);

        verticalLayout->addWidget(label);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        pushButton_play = new QPushButton(MainDialog);
        pushButton_play->setObjectName(QString::fromUtf8("pushButton_play"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton_play->sizePolicy().hasHeightForWidth());
        pushButton_play->setSizePolicy(sizePolicy);
        pushButton_play->setStyleSheet(QString::fromUtf8("border-image:url(:/icon/icon/w.png)"));

        horizontalLayout->addWidget(pushButton_play);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        pushButton_qupu = new QPushButton(MainDialog);
        pushButton_qupu->setObjectName(QString::fromUtf8("pushButton_qupu"));
        sizePolicy.setHeightForWidth(pushButton_qupu->sizePolicy().hasHeightForWidth());
        pushButton_qupu->setSizePolicy(sizePolicy);
        pushButton_qupu->setStyleSheet(QString::fromUtf8("border-image:url(:/icon/icon/e.png)"));

        horizontalLayout->addWidget(pushButton_qupu);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton_piano = new QPushButton(MainDialog);
        pushButton_piano->setObjectName(QString::fromUtf8("pushButton_piano"));
        sizePolicy.setHeightForWidth(pushButton_piano->sizePolicy().hasHeightForWidth());
        pushButton_piano->setSizePolicy(sizePolicy);
        pushButton_piano->setStyleSheet(QString::fromUtf8("border-image:url(:/icon/icon/r.png)"));

        horizontalLayout->addWidget(pushButton_piano);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);

        horizontalLayout->setStretch(1, 3);
        horizontalLayout->setStretch(2, 1);
        horizontalLayout->setStretch(3, 3);
        horizontalLayout->setStretch(4, 1);
        horizontalLayout->setStretch(5, 3);
        horizontalLayout->setStretch(6, 1);

        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);

        verticalLayout->setStretch(0, 1);
        verticalLayout->setStretch(1, 2);
        verticalLayout->setStretch(2, 1);
        verticalLayout->setStretch(3, 3);
        verticalLayout->setStretch(4, 1);

        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(MainDialog);

        QMetaObject::connectSlotsByName(MainDialog);
    } // setupUi

    void retranslateUi(QDialog *MainDialog)
    {
        MainDialog->setWindowTitle(QApplication::translate("MainDialog", "ZYNQ PIANO", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainDialog", "ZYNQ PIANO", 0, QApplication::UnicodeUTF8));
        pushButton_play->setText(QString());
        pushButton_qupu->setText(QString());
        pushButton_piano->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainDialog: public Ui_MainDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINDIALOG_H
