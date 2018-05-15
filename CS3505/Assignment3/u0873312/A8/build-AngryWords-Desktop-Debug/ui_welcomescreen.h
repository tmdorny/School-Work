/********************************************************************************
** Form generated from reading UI file 'welcomescreen.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WELCOMESCREEN_H
#define UI_WELCOMESCREEN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WelcomeScreen
{
public:
    QWidget *centralwidget;
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *usernameTextbox;
    QSpacerItem *verticalSpacer_8;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QLineEdit *passwordTextbox;
    QSpacerItem *verticalSpacer_11;
    QPushButton *playButton;
    QSpacerItem *verticalSpacer_10;
    QPushButton *guestButton;
    QSpacerItem *verticalSpacer_9;
    QGraphicsView *welcomeGraphic;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *WelcomeScreen)
    {
        if (WelcomeScreen->objectName().isEmpty())
            WelcomeScreen->setObjectName(QStringLiteral("WelcomeScreen"));
        WelcomeScreen->resize(800, 600);
        centralwidget = new QWidget(WelcomeScreen);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        verticalLayoutWidget_3 = new QWidget(centralwidget);
        verticalLayoutWidget_3->setObjectName(QStringLiteral("verticalLayoutWidget_3"));
        verticalLayoutWidget_3->setGeometry(QRect(260, 300, 261, 261));
        verticalLayout_3 = new QVBoxLayout(verticalLayoutWidget_3);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_2 = new QLabel(verticalLayoutWidget_3);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);

        usernameTextbox = new QLineEdit(verticalLayoutWidget_3);
        usernameTextbox->setObjectName(QStringLiteral("usernameTextbox"));

        horizontalLayout_2->addWidget(usernameTextbox);


        verticalLayout_3->addLayout(horizontalLayout_2);

        verticalSpacer_8 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_8);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label = new QLabel(verticalLayoutWidget_3);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_3->addWidget(label);

        passwordTextbox = new QLineEdit(verticalLayoutWidget_3);
        passwordTextbox->setObjectName(QStringLiteral("passwordTextbox"));

        horizontalLayout_3->addWidget(passwordTextbox);


        verticalLayout_3->addLayout(horizontalLayout_3);

        verticalSpacer_11 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_11);

        playButton = new QPushButton(verticalLayoutWidget_3);
        playButton->setObjectName(QStringLiteral("playButton"));

        verticalLayout_3->addWidget(playButton);

        verticalSpacer_10 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_10);

        guestButton = new QPushButton(verticalLayoutWidget_3);
        guestButton->setObjectName(QStringLiteral("guestButton"));

        verticalLayout_3->addWidget(guestButton);

        verticalSpacer_9 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_9);

        welcomeGraphic = new QGraphicsView(centralwidget);
        welcomeGraphic->setObjectName(QStringLiteral("welcomeGraphic"));
        welcomeGraphic->setGeometry(QRect(0, 0, 800, 600));
        WelcomeScreen->setCentralWidget(centralwidget);
        welcomeGraphic->raise();
        verticalLayoutWidget_3->raise();
        menubar = new QMenuBar(WelcomeScreen);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 17));
        WelcomeScreen->setMenuBar(menubar);
        statusbar = new QStatusBar(WelcomeScreen);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        WelcomeScreen->setStatusBar(statusbar);

        retranslateUi(WelcomeScreen);

        QMetaObject::connectSlotsByName(WelcomeScreen);
    } // setupUi

    void retranslateUi(QMainWindow *WelcomeScreen)
    {
        WelcomeScreen->setWindowTitle(QApplication::translate("WelcomeScreen", "MainWindow", 0));
        label_2->setText(QApplication::translate("WelcomeScreen", "Username:", 0));
        label->setText(QApplication::translate("WelcomeScreen", "Password:", 0));
        playButton->setText(QApplication::translate("WelcomeScreen", "Play", 0));
        guestButton->setText(QApplication::translate("WelcomeScreen", "Play As Guest", 0));
    } // retranslateUi

};

namespace Ui {
    class WelcomeScreen: public Ui_WelcomeScreen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WELCOMESCREEN_H
