/********************************************************************************
** Form generated from reading UI file 'startwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STARTWINDOW_H
#define UI_STARTWINDOW_H

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

class Ui_startWindow
{
public:
    QWidget *centralWidget;
    QLabel *label;
    QPushButton *pushButton;
    QLabel *label_2;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *startWindow)
    {
        if (startWindow->objectName().isEmpty())
            startWindow->setObjectName(QStringLiteral("startWindow"));
        startWindow->resize(900, 600);
        centralWidget = new QWidget(startWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(0, 0, 900, 600));
        label->setAutoFillBackground(true);
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(460, 80, 331, 146));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(230, 200, 291, 361));
        startWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(startWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 900, 22));
        startWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(startWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        startWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(startWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        startWindow->setStatusBar(statusBar);

        retranslateUi(startWindow);

        QMetaObject::connectSlotsByName(startWindow);
    } // setupUi

    void retranslateUi(QMainWindow *startWindow)
    {
        startWindow->setWindowTitle(QApplication::translate("startWindow", "startWindow", 0));
        label->setText(QApplication::translate("startWindow", "TextLabel", 0));
        pushButton->setText(QString());
        label_2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class startWindow: public Ui_startWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STARTWINDOW_H
