/********************************************************************************
** Form generated from reading UI file 'gamewindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMEWINDOW_H
#define UI_GAMEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GameWindow
{
public:
    QAction *actionNew_Game;
    QAction *actionEnd_Game;
    QAction *actionQuit;
    QAction *actionPlay_music;
    QAction *actionStop_music;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QGraphicsView *graphicsView;
    QLabel *label;
    QLabel *testWord;
    QLabel *label_2;
    QLabel *userWordLabel;
    QMenuBar *menuBar;
    QMenu *menuGame;
    QMenu *menuMusic;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *GameWindow)
    {
        if (GameWindow->objectName().isEmpty())
            GameWindow->setObjectName(QStringLiteral("GameWindow"));
        GameWindow->resize(732, 462);
        actionNew_Game = new QAction(GameWindow);
        actionNew_Game->setObjectName(QStringLiteral("actionNew_Game"));
        actionEnd_Game = new QAction(GameWindow);
        actionEnd_Game->setObjectName(QStringLiteral("actionEnd_Game"));
        actionQuit = new QAction(GameWindow);
        actionQuit->setObjectName(QStringLiteral("actionQuit"));
        actionPlay_music = new QAction(GameWindow);
        actionPlay_music->setObjectName(QStringLiteral("actionPlay_music"));
        actionStop_music = new QAction(GameWindow);
        actionStop_music->setObjectName(QStringLiteral("actionStop_music"));
        centralWidget = new QWidget(GameWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(graphicsView->sizePolicy().hasHeightForWidth());
        graphicsView->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(graphicsView);

        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        testWord = new QLabel(centralWidget);
        testWord->setObjectName(QStringLiteral("testWord"));
        QFont font;
        font.setPointSize(20);
        font.setBold(true);
        font.setWeight(75);
        testWord->setFont(font);
        testWord->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(testWord);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_2);

        userWordLabel = new QLabel(centralWidget);
        userWordLabel->setObjectName(QStringLiteral("userWordLabel"));
        userWordLabel->setFont(font);
        userWordLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(userWordLabel);

        GameWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(GameWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 732, 19));
        menuGame = new QMenu(menuBar);
        menuGame->setObjectName(QStringLiteral("menuGame"));
        menuMusic = new QMenu(menuBar);
        menuMusic->setObjectName(QStringLiteral("menuMusic"));
        GameWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(GameWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        GameWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(GameWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        GameWindow->setStatusBar(statusBar);

        menuBar->addAction(menuGame->menuAction());
        menuBar->addAction(menuMusic->menuAction());
        menuGame->addAction(actionEnd_Game);
        menuGame->addAction(actionQuit);
        menuMusic->addAction(actionPlay_music);
        menuMusic->addAction(actionStop_music);
        mainToolBar->addAction(actionNew_Game);

        retranslateUi(GameWindow);
        QObject::connect(actionQuit, SIGNAL(triggered()), GameWindow, SLOT(close()));

        QMetaObject::connectSlotsByName(GameWindow);
    } // setupUi

    void retranslateUi(QMainWindow *GameWindow)
    {
        GameWindow->setWindowTitle(QApplication::translate("GameWindow", "GameWindow", 0));
        actionNew_Game->setText(QApplication::translate("GameWindow", "New Game", 0));
        actionEnd_Game->setText(QApplication::translate("GameWindow", "End Game", 0));
        actionQuit->setText(QApplication::translate("GameWindow", "Quit", 0));
        actionPlay_music->setText(QApplication::translate("GameWindow", "Play music", 0));
        actionStop_music->setText(QApplication::translate("GameWindow", "Stop music", 0));
        label->setText(QApplication::translate("GameWindow", "Word:", 0));
        testWord->setText(QApplication::translate("GameWindow", "Test", 0));
        label_2->setText(QApplication::translate("GameWindow", "Your Word:", 0));
        userWordLabel->setText(QString());
        menuGame->setTitle(QApplication::translate("GameWindow", "Game", 0));
        menuMusic->setTitle(QApplication::translate("GameWindow", "Music", 0));
    } // retranslateUi

};

namespace Ui {
    class GameWindow: public Ui_GameWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMEWINDOW_H
