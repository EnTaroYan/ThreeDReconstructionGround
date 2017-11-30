/********************************************************************************
** Form generated from reading UI file 'ThreeDReconstructionGround.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_THREEDRECONSTRUCTIONGROUND_H
#define UI_THREEDRECONSTRUCTIONGROUND_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ThreeDReconstructionGroundClass
{
public:
    QWidget *centralWidget;
    QPushButton *pushButton1;
    QPushButton *pushButton2;
    QLabel *label1;
    QLabel *label2;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ThreeDReconstructionGroundClass)
    {
        if (ThreeDReconstructionGroundClass->objectName().isEmpty())
            ThreeDReconstructionGroundClass->setObjectName(QStringLiteral("ThreeDReconstructionGroundClass"));
        ThreeDReconstructionGroundClass->resize(1399, 564);
        centralWidget = new QWidget(ThreeDReconstructionGroundClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        pushButton1 = new QPushButton(centralWidget);
        pushButton1->setObjectName(QStringLiteral("pushButton1"));
        pushButton1->setGeometry(QRect(10, 10, 75, 40));
        pushButton2 = new QPushButton(centralWidget);
        pushButton2->setObjectName(QStringLiteral("pushButton2"));
        pushButton2->setGeometry(QRect(10, 60, 75, 40));
        label1 = new QLabel(centralWidget);
        label1->setObjectName(QStringLiteral("label1"));
        label1->setGeometry(QRect(100, 10, 640, 480));
        label2 = new QLabel(centralWidget);
        label2->setObjectName(QStringLiteral("label2"));
        label2->setGeometry(QRect(740, 10, 640, 480));
        ThreeDReconstructionGroundClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(ThreeDReconstructionGroundClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1399, 23));
        ThreeDReconstructionGroundClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ThreeDReconstructionGroundClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        ThreeDReconstructionGroundClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(ThreeDReconstructionGroundClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        ThreeDReconstructionGroundClass->setStatusBar(statusBar);

        retranslateUi(ThreeDReconstructionGroundClass);
        QObject::connect(pushButton1, SIGNAL(clicked()), ThreeDReconstructionGroundClass, SLOT(button1Click()));
        QObject::connect(pushButton2, SIGNAL(clicked()), ThreeDReconstructionGroundClass, SLOT(button2Click()));

        QMetaObject::connectSlotsByName(ThreeDReconstructionGroundClass);
    } // setupUi

    void retranslateUi(QMainWindow *ThreeDReconstructionGroundClass)
    {
        ThreeDReconstructionGroundClass->setWindowTitle(QApplication::translate("ThreeDReconstructionGroundClass", "ThreeDReconstructionGround", Q_NULLPTR));
        pushButton1->setText(QApplication::translate("ThreeDReconstructionGroundClass", "PushButton1", Q_NULLPTR));
        pushButton2->setText(QApplication::translate("ThreeDReconstructionGroundClass", "PushButton2", Q_NULLPTR));
        label1->setText(QString());
        label2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ThreeDReconstructionGroundClass: public Ui_ThreeDReconstructionGroundClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_THREEDRECONSTRUCTIONGROUND_H
