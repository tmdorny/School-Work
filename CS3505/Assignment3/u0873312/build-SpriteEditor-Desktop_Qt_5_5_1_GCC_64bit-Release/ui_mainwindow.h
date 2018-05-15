/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionImport;
    QAction *actionExport;
    QAction *actionQuit;
    QAction *actionUndo;
    QAction *actionRedo;
    QAction *actionCopy;
    QAction *actionCut;
    QAction *actionPaste;
    QAction *actionNew;
    QAction *actionSave_as;
    QAction *actionClose;
    QAction *actionAbout;
    QAction *actionPreview;
    QAction *actionLine;
    QAction *actionPensil;
    QAction *actionEllipse;
    QAction *actionText;
    QAction *actionEraser;
    QAction *actionPens;
    QAction *actionCommon;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QFrame *mainFrame;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QLabel *viewPort;
    QFrame *projectArea;
    QHBoxLayout *horizontalLayout;
    QPushButton *prevFrameButton;
    QLabel *frameNumberLabel;
    QPushButton *nextFrameButton;
    QPushButton *scaleUpButton;
    QPushButton *originalSizeButton;
    QPushButton *scaleDownButton;
    QPushButton *newFrameButton;
    QSpacerItem *horizontalSpacer;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QProgressBar *progressBar;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuEdit;
    QMenu *menuHelp;
    QMenu *menuView;
    QMenu *menuPens;
    QMenu *menuTools;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(782, 480);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/icons/icons/document-open.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpen->setIcon(icon);
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/icons/icons/document-save.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave->setIcon(icon1);
        actionImport = new QAction(MainWindow);
        actionImport->setObjectName(QStringLiteral("actionImport"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/icons/icons/document-import.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionImport->setIcon(icon2);
        actionExport = new QAction(MainWindow);
        actionExport->setObjectName(QStringLiteral("actionExport"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/icons/icons/document-export.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionExport->setIcon(icon3);
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QStringLiteral("actionQuit"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/icons/icons/application-exit.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionQuit->setIcon(icon4);
        actionUndo = new QAction(MainWindow);
        actionUndo->setObjectName(QStringLiteral("actionUndo"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/icons/icons/edit-undo.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionUndo->setIcon(icon5);
        actionRedo = new QAction(MainWindow);
        actionRedo->setObjectName(QStringLiteral("actionRedo"));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/icons/icons/edit-redo.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRedo->setIcon(icon6);
        actionCopy = new QAction(MainWindow);
        actionCopy->setObjectName(QStringLiteral("actionCopy"));
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/icons/icons/edit-copy.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCopy->setIcon(icon7);
        actionCut = new QAction(MainWindow);
        actionCut->setObjectName(QStringLiteral("actionCut"));
        QIcon icon8;
        icon8.addFile(QStringLiteral(":/icons/icons/edit-cut.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCut->setIcon(icon8);
        actionPaste = new QAction(MainWindow);
        actionPaste->setObjectName(QStringLiteral("actionPaste"));
        QIcon icon9;
        icon9.addFile(QStringLiteral(":/icons/icons/edit-paste.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionPaste->setIcon(icon9);
        actionNew = new QAction(MainWindow);
        actionNew->setObjectName(QStringLiteral("actionNew"));
        QIcon icon10;
        icon10.addFile(QStringLiteral(":/icons/icons/document-new.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNew->setIcon(icon10);
        actionSave_as = new QAction(MainWindow);
        actionSave_as->setObjectName(QStringLiteral("actionSave_as"));
        QIcon icon11;
        icon11.addFile(QStringLiteral(":/icons/icons/document-save-as.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave_as->setIcon(icon11);
        actionClose = new QAction(MainWindow);
        actionClose->setObjectName(QStringLiteral("actionClose"));
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        actionPreview = new QAction(MainWindow);
        actionPreview->setObjectName(QStringLiteral("actionPreview"));
        QIcon icon12;
        icon12.addFile(QStringLiteral(":/icons/icons/document-preview.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionPreview->setIcon(icon12);
        actionLine = new QAction(MainWindow);
        actionLine->setObjectName(QStringLiteral("actionLine"));
        actionPensil = new QAction(MainWindow);
        actionPensil->setObjectName(QStringLiteral("actionPensil"));
        actionEllipse = new QAction(MainWindow);
        actionEllipse->setObjectName(QStringLiteral("actionEllipse"));
        actionText = new QAction(MainWindow);
        actionText->setObjectName(QStringLiteral("actionText"));
        actionEraser = new QAction(MainWindow);
        actionEraser->setObjectName(QStringLiteral("actionEraser"));
        actionPens = new QAction(MainWindow);
        actionPens->setObjectName(QStringLiteral("actionPens"));
        actionPens->setCheckable(true);
        actionPens->setChecked(false);
        actionCommon = new QAction(MainWindow);
        actionCommon->setObjectName(QStringLiteral("actionCommon"));
        actionCommon->setCheckable(true);
        actionCommon->setChecked(true);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        mainFrame = new QFrame(centralWidget);
        mainFrame->setObjectName(QStringLiteral("mainFrame"));
        mainFrame->setFrameShape(QFrame::StyledPanel);
        mainFrame->setFrameShadow(QFrame::Raised);
        verticalLayout_3 = new QVBoxLayout(mainFrame);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        viewPort = new QLabel(mainFrame);
        viewPort->setObjectName(QStringLiteral("viewPort"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(1);
        sizePolicy.setHeightForWidth(viewPort->sizePolicy().hasHeightForWidth());
        viewPort->setSizePolicy(sizePolicy);
        viewPort->setMinimumSize(QSize(0, 64));
        viewPort->setLayoutDirection(Qt::LeftToRight);
        viewPort->setAutoFillBackground(false);
        viewPort->setText(QStringLiteral(""));
        viewPort->setAlignment(Qt::AlignCenter);
        viewPort->setTextInteractionFlags(Qt::NoTextInteraction);

        verticalLayout_2->addWidget(viewPort);

        projectArea = new QFrame(mainFrame);
        projectArea->setObjectName(QStringLiteral("projectArea"));
        projectArea->setMinimumSize(QSize(0, 32));
        projectArea->setFrameShape(QFrame::StyledPanel);
        projectArea->setFrameShadow(QFrame::Plain);
        horizontalLayout = new QHBoxLayout(projectArea);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        prevFrameButton = new QPushButton(projectArea);
        prevFrameButton->setObjectName(QStringLiteral("prevFrameButton"));
        QIcon icon13;
        icon13.addFile(QStringLiteral(":/icons/icons/go-previous.png"), QSize(), QIcon::Normal, QIcon::Off);
        prevFrameButton->setIcon(icon13);

        horizontalLayout->addWidget(prevFrameButton);

        frameNumberLabel = new QLabel(projectArea);
        frameNumberLabel->setObjectName(QStringLiteral("frameNumberLabel"));

        horizontalLayout->addWidget(frameNumberLabel);

        nextFrameButton = new QPushButton(projectArea);
        nextFrameButton->setObjectName(QStringLiteral("nextFrameButton"));
        QIcon icon14;
        icon14.addFile(QStringLiteral(":/icons/icons/go-next.png"), QSize(), QIcon::Normal, QIcon::Off);
        nextFrameButton->setIcon(icon14);

        horizontalLayout->addWidget(nextFrameButton);

        scaleUpButton = new QPushButton(projectArea);
        scaleUpButton->setObjectName(QStringLiteral("scaleUpButton"));

        horizontalLayout->addWidget(scaleUpButton);

        originalSizeButton = new QPushButton(projectArea);
        originalSizeButton->setObjectName(QStringLiteral("originalSizeButton"));

        horizontalLayout->addWidget(originalSizeButton);

        scaleDownButton = new QPushButton(projectArea);
        scaleDownButton->setObjectName(QStringLiteral("scaleDownButton"));

        horizontalLayout->addWidget(scaleDownButton);

        newFrameButton = new QPushButton(projectArea);
        newFrameButton->setObjectName(QStringLiteral("newFrameButton"));

        horizontalLayout->addWidget(newFrameButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout_2->addWidget(projectArea);

        scrollArea = new QScrollArea(mainFrame);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 744, 214));
        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout_2->addWidget(scrollArea);


        verticalLayout_3->addLayout(verticalLayout_2);


        verticalLayout->addWidget(mainFrame);

        progressBar = new QProgressBar(centralWidget);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setValue(24);

        verticalLayout->addWidget(progressBar);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 782, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuEdit = new QMenu(menuBar);
        menuEdit->setObjectName(QStringLiteral("menuEdit"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        menuView = new QMenu(menuBar);
        menuView->setObjectName(QStringLiteral("menuView"));
        menuPens = new QMenu(menuBar);
        menuPens->setObjectName(QStringLiteral("menuPens"));
        menuTools = new QMenu(menuBar);
        menuTools->setObjectName(QStringLiteral("menuTools"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuEdit->menuAction());
        menuBar->addAction(menuView->menuAction());
        menuBar->addAction(menuTools->menuAction());
        menuBar->addAction(menuPens->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionNew);
        menuFile->addSeparator();
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSave);
        menuFile->addAction(actionSave_as);
        menuFile->addSeparator();
        menuFile->addAction(actionImport);
        menuFile->addAction(actionExport);
        menuFile->addSeparator();
        menuFile->addAction(actionClose);
        menuFile->addAction(actionQuit);
        menuEdit->addAction(actionUndo);
        menuEdit->addAction(actionRedo);
        menuEdit->addSeparator();
        menuEdit->addAction(actionCopy);
        menuEdit->addAction(actionCut);
        menuEdit->addAction(actionPaste);
        menuHelp->addAction(actionAbout);
        menuView->addAction(actionPreview);
        menuPens->addAction(actionLine);
        menuPens->addAction(actionPensil);
        menuPens->addAction(actionEllipse);
        menuPens->addAction(actionText);
        menuPens->addAction(actionEraser);
        menuTools->addAction(actionPens);
        menuTools->addAction(actionCommon);
        mainToolBar->addAction(actionNew);
        mainToolBar->addAction(actionOpen);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionSave);
        mainToolBar->addAction(actionSave_as);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionClose);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionUndo);
        mainToolBar->addAction(actionRedo);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionImport);
        mainToolBar->addAction(actionExport);
        mainToolBar->addAction(actionPreview);

        retranslateUi(MainWindow);
        QObject::connect(actionQuit, SIGNAL(triggered()), MainWindow, SLOT(close()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Sprite editor (Nick Pershyn)", 0));
        actionOpen->setText(QApplication::translate("MainWindow", "Open", 0));
        actionOpen->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", 0));
        actionSave->setText(QApplication::translate("MainWindow", "Save", 0));
        actionSave->setShortcut(QApplication::translate("MainWindow", "Ctrl+S", 0));
        actionImport->setText(QApplication::translate("MainWindow", "Import", 0));
        actionExport->setText(QApplication::translate("MainWindow", "Export", 0));
        actionQuit->setText(QApplication::translate("MainWindow", "Quit", 0));
        actionQuit->setShortcut(QApplication::translate("MainWindow", "Ctrl+Q", 0));
        actionUndo->setText(QApplication::translate("MainWindow", "Undo", 0));
        actionRedo->setText(QApplication::translate("MainWindow", "Redo", 0));
        actionCopy->setText(QApplication::translate("MainWindow", "Copy", 0));
        actionCut->setText(QApplication::translate("MainWindow", "Cut", 0));
        actionPaste->setText(QApplication::translate("MainWindow", "Paste", 0));
        actionNew->setText(QApplication::translate("MainWindow", "New", 0));
        actionNew->setShortcut(QApplication::translate("MainWindow", "Ctrl+N", 0));
        actionSave_as->setText(QApplication::translate("MainWindow", "Save as...", 0));
        actionClose->setText(QApplication::translate("MainWindow", "Close", 0));
        actionAbout->setText(QApplication::translate("MainWindow", "About", 0));
        actionPreview->setText(QApplication::translate("MainWindow", "Preview", 0));
        actionLine->setText(QApplication::translate("MainWindow", "Line", 0));
        actionPensil->setText(QApplication::translate("MainWindow", "Pensil", 0));
        actionEllipse->setText(QApplication::translate("MainWindow", "Ellipse", 0));
        actionText->setText(QApplication::translate("MainWindow", "Text", 0));
        actionEraser->setText(QApplication::translate("MainWindow", "Eraser", 0));
        actionPens->setText(QApplication::translate("MainWindow", "Pens", 0));
        actionCommon->setText(QApplication::translate("MainWindow", "Common", 0));
        prevFrameButton->setText(QString());
        frameNumberLabel->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        nextFrameButton->setText(QString());
        scaleUpButton->setText(QApplication::translate("MainWindow", "Scale Up", 0));
        originalSizeButton->setText(QApplication::translate("MainWindow", "100%", 0));
        scaleDownButton->setText(QApplication::translate("MainWindow", "Scale Down", 0));
        newFrameButton->setText(QApplication::translate("MainWindow", "Insert empty frame", 0));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0));
        menuEdit->setTitle(QApplication::translate("MainWindow", "Edit", 0));
        menuHelp->setTitle(QApplication::translate("MainWindow", "Help", 0));
        menuView->setTitle(QApplication::translate("MainWindow", "View", 0));
        menuPens->setTitle(QApplication::translate("MainWindow", "Pens", 0));
        menuTools->setTitle(QApplication::translate("MainWindow", "Tools", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
