//A7: Sprite Editor
//Author: Nick Pershyn(uNID: u0873312)
//github: LinuxUser404

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMovie>
#include <QIcon>
#include <QScrollArea>
#include <QLabel>
#include <QPainter>
#include <QPen>
#include <QToolBar>
#include <QMouseEvent>

#include "editorserver.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    EditorServer* m_server;
    QString m_filename;
    QScrollArea* m_frameList;
    QLabel* m_canvas;
    QPen* m_pen;
    QPainter* m_painter;
    QPixmap* m_pixmap;
    QToolBar* m_penToolBar;
    QColor* m_color;

    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);

private slots:
    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionImport_triggered();

    void on_actionExport_triggered();

    void on_actionPreview_triggered();

    void progressBarUpdate(int newValue);

    void next();
    void previous();

    void update();

    void on_actionSave_as_triggered();
    void on_actionNew_triggered();
    void on_actionClose_triggered();
    void on_actionCommon_triggered();

    void on_actionInsert_empty_frame_triggered();
    void on_actionDelete_current_frame_triggered();
    void on_actionSet_color_triggered();
    void on_actionEraser_triggered();
    void on_actionQuit_triggered();
};

#endif // MAINWINDOW_H
