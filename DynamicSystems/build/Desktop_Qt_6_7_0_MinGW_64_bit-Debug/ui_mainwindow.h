/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QFormLayout *formLayout_3;
    QFormLayout *formLayout;
    QLabel *label_2;
    QLabel *iterationLabel;
    QPushButton *iterateBtn;
    QPushButton *resetBtn;
    QFormLayout *formLayout_2;
    QLabel *label;
    QLabel *distanceLabel;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *horizontalSpacer;
    QWidget *canvas2;
    QWidget *canvas;
    QWidget *canvas3;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *horizontalSpacer_5;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(753, 562);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        formLayout_3 = new QFormLayout();
        formLayout_3->setObjectName("formLayout_3");
        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");

        formLayout->setWidget(0, QFormLayout::LabelRole, label_2);

        iterationLabel = new QLabel(centralwidget);
        iterationLabel->setObjectName("iterationLabel");

        formLayout->setWidget(0, QFormLayout::FieldRole, iterationLabel);


        formLayout_3->setLayout(0, QFormLayout::LabelRole, formLayout);

        iterateBtn = new QPushButton(centralwidget);
        iterateBtn->setObjectName("iterateBtn");

        formLayout_3->setWidget(1, QFormLayout::LabelRole, iterateBtn);

        resetBtn = new QPushButton(centralwidget);
        resetBtn->setObjectName("resetBtn");

        formLayout_3->setWidget(2, QFormLayout::LabelRole, resetBtn);

        formLayout_2 = new QFormLayout();
        formLayout_2->setObjectName("formLayout_2");
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        QFont font;
        font.setPointSize(10);
        label->setFont(font);

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label);

        distanceLabel = new QLabel(centralwidget);
        distanceLabel->setObjectName("distanceLabel");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(distanceLabel->sizePolicy().hasHeightForWidth());
        distanceLabel->setSizePolicy(sizePolicy);
        distanceLabel->setFont(font);

        formLayout_2->setWidget(0, QFormLayout::FieldRole, distanceLabel);


        formLayout_3->setLayout(3, QFormLayout::LabelRole, formLayout_2);


        gridLayout->addLayout(formLayout_3, 0, 3, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(verticalSpacer_2, 1, 3, 1, 1);

        horizontalSpacer = new QSpacerItem(50, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 2, 1, 1);

        canvas2 = new QWidget(centralwidget);
        canvas2->setObjectName("canvas2");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(canvas2->sizePolicy().hasHeightForWidth());
        canvas2->setSizePolicy(sizePolicy1);
        canvas2->setAutoFillBackground(false);

        gridLayout->addWidget(canvas2, 2, 1, 1, 1);

        canvas = new QWidget(centralwidget);
        canvas->setObjectName("canvas");
        sizePolicy1.setHeightForWidth(canvas->sizePolicy().hasHeightForWidth());
        canvas->setSizePolicy(sizePolicy1);
        canvas->setAutoFillBackground(false);

        gridLayout->addWidget(canvas, 0, 1, 1, 1);

        canvas3 = new QWidget(centralwidget);
        canvas3->setObjectName("canvas3");
        sizePolicy1.setHeightForWidth(canvas3->sizePolicy().hasHeightForWidth());
        canvas3->setSizePolicy(sizePolicy1);
        canvas3->setAutoFillBackground(false);

        gridLayout->addWidget(canvas3, 2, 3, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(verticalSpacer, 1, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(50, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 2, 2, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(50, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 0, 0, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(50, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 2, 0, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_5, 0, 1, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 753, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Koch Fractal", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Iteration Level:", nullptr));
        iterationLabel->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        iterateBtn->setText(QCoreApplication::translate("MainWindow", "Iterate", nullptr));
        resetBtn->setText(QCoreApplication::translate("MainWindow", "Reset", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Distance: ", nullptr));
        distanceLabel->setText(QCoreApplication::translate("MainWindow", "0 px", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
