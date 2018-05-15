/********************************************************************************
** Form generated from reading UI file 'welcomescreen.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
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
    QVBoxLayout *loginButtons;
    QHBoxLayout *horizontalLayout_2;
    QLabel *userLabel;
    QLineEdit *usernameTextbox;
    QSpacerItem *verticalSpacer_8;
    QHBoxLayout *horizontalLayout_3;
    QLabel *passLabel;
    QLineEdit *passwordTextbox;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QLabel *serverLabel;
    QLineEdit *serverText;
    QSpacerItem *verticalSpacer_11;
    QPushButton *playButton;
    QSpacerItem *verticalSpacer_10;
    QPushButton *guestButton;
    QSpacerItem *verticalSpacer_9;
    QGraphicsView *welcomeGraphic;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *welcomeLabels;
    QHBoxLayout *horizontalLayout_6;
    QLabel *welcomeLabel;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_5;
    QLabel *userLabel2;
    QSpacerItem *horizontalSpacer_2;
    QLabel *loggedInAs;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout_4;
    QLabel *permissionLabel;
    QSpacerItem *horizontalSpacer;
    QLabel *permissionLevel;
    QPushButton *playGameButton;
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
        loginButtons = new QVBoxLayout(verticalLayoutWidget_3);
        loginButtons->setObjectName(QStringLiteral("loginButtons"));
        loginButtons->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        userLabel = new QLabel(verticalLayoutWidget_3);
        userLabel->setObjectName(QStringLiteral("userLabel"));

        horizontalLayout_2->addWidget(userLabel);

        usernameTextbox = new QLineEdit(verticalLayoutWidget_3);
        usernameTextbox->setObjectName(QStringLiteral("usernameTextbox"));

        horizontalLayout_2->addWidget(usernameTextbox);


        loginButtons->addLayout(horizontalLayout_2);

        verticalSpacer_8 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        loginButtons->addItem(verticalSpacer_8);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        passLabel = new QLabel(verticalLayoutWidget_3);
        passLabel->setObjectName(QStringLiteral("passLabel"));

        horizontalLayout_3->addWidget(passLabel);

        passwordTextbox = new QLineEdit(verticalLayoutWidget_3);
        passwordTextbox->setObjectName(QStringLiteral("passwordTextbox"));

        horizontalLayout_3->addWidget(passwordTextbox);


        loginButtons->addLayout(horizontalLayout_3);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        loginButtons->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        serverLabel = new QLabel(verticalLayoutWidget_3);
        serverLabel->setObjectName(QStringLiteral("serverLabel"));

        horizontalLayout->addWidget(serverLabel);

        serverText = new QLineEdit(verticalLayoutWidget_3);
        serverText->setObjectName(QStringLiteral("serverText"));

        horizontalLayout->addWidget(serverText);


        loginButtons->addLayout(horizontalLayout);

        verticalSpacer_11 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        loginButtons->addItem(verticalSpacer_11);

        playButton = new QPushButton(verticalLayoutWidget_3);
        playButton->setObjectName(QStringLiteral("playButton"));

        loginButtons->addWidget(playButton);

        verticalSpacer_10 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        loginButtons->addItem(verticalSpacer_10);

        guestButton = new QPushButton(verticalLayoutWidget_3);
        guestButton->setObjectName(QStringLiteral("guestButton"));

        loginButtons->addWidget(guestButton);

        verticalSpacer_9 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        loginButtons->addItem(verticalSpacer_9);

        welcomeGraphic = new QGraphicsView(centralwidget);
        welcomeGraphic->setObjectName(QStringLiteral("welcomeGraphic"));
        welcomeGraphic->setGeometry(QRect(0, 0, 800, 600));
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(50, 210, 168, 83));
        welcomeLabels = new QVBoxLayout(verticalLayoutWidget);
        welcomeLabels->setObjectName(QStringLiteral("welcomeLabels"));
        welcomeLabels->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        welcomeLabel = new QLabel(verticalLayoutWidget);
        welcomeLabel->setObjectName(QStringLiteral("welcomeLabel"));

        horizontalLayout_6->addWidget(welcomeLabel);


        welcomeLabels->addLayout(horizontalLayout_6);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        welcomeLabels->addItem(verticalSpacer_2);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        userLabel2 = new QLabel(verticalLayoutWidget);
        userLabel2->setObjectName(QStringLiteral("userLabel2"));

        horizontalLayout_5->addWidget(userLabel2);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_2);

        loggedInAs = new QLabel(verticalLayoutWidget);
        loggedInAs->setObjectName(QStringLiteral("loggedInAs"));

        horizontalLayout_5->addWidget(loggedInAs);


        welcomeLabels->addLayout(horizontalLayout_5);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        welcomeLabels->addItem(verticalSpacer_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        permissionLabel = new QLabel(verticalLayoutWidget);
        permissionLabel->setObjectName(QStringLiteral("permissionLabel"));

        horizontalLayout_4->addWidget(permissionLabel);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        permissionLevel = new QLabel(verticalLayoutWidget);
        permissionLevel->setObjectName(QStringLiteral("permissionLevel"));

        horizontalLayout_4->addWidget(permissionLevel);


        welcomeLabels->addLayout(horizontalLayout_4);

        playGameButton = new QPushButton(centralwidget);
        playGameButton->setObjectName(QStringLiteral("playGameButton"));
        playGameButton->setGeometry(QRect(80, 320, 90, 26));
        WelcomeScreen->setCentralWidget(centralwidget);
        welcomeGraphic->raise();
        verticalLayoutWidget_3->raise();
        verticalLayoutWidget->raise();
        playGameButton->raise();
        menubar = new QMenuBar(WelcomeScreen);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 21));
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
        userLabel->setText(QApplication::translate("WelcomeScreen", "Username:", 0));
        passLabel->setText(QApplication::translate("WelcomeScreen", "Password:", 0));
        serverLabel->setText(QApplication::translate("WelcomeScreen", "Server IP:", 0));
        playButton->setText(QApplication::translate("WelcomeScreen", "Play", 0));
        guestButton->setText(QApplication::translate("WelcomeScreen", "Play As Guest", 0));
        welcomeLabel->setText(QApplication::translate("WelcomeScreen", "Welcome to Angry Words!", 0));
        userLabel2->setText(QApplication::translate("WelcomeScreen", "Logged in as:", 0));
        loggedInAs->setText(QString());
        permissionLabel->setText(QApplication::translate("WelcomeScreen", "Permission Level:", 0));
        permissionLevel->setText(QString());
        playGameButton->setText(QApplication::translate("WelcomeScreen", "Play Game!", 0));
    } // retranslateUi

};

namespace Ui {
    class WelcomeScreen: public Ui_WelcomeScreen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WELCOMESCREEN_H
