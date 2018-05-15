//A7: Sprite Editor
//Author: Nick Pershyn(uNID: u0873312)
//github: LinuxUser404

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "editorserver.h"
#include "previewwidget.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QScrollArea>
#include <QCursor>
#include <QFrame>
#include <QColorDialog>
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_filename = "";

    m_server = new EditorServer(this);
    m_canvas = this->ui->viewPort;
    m_frameList = this->ui->scrollArea;
    //m_pen = new QPen();
    //m_painter = new QPainter();
    m_pixmap = new QPixmap();
    m_color = new QColor(255,255,255,255);
    m_penToolBar = addToolBar("Pen");

    m_penToolBar->addActions(this->ui->menuPens->actions());

    m_canvas->setFrameShape(QFrame::Box);





    connect(m_server, SIGNAL(setProcessRange(int, int)), this->ui->progressBar, SLOT(setRange(int, int)));
    connect(m_server, SIGNAL(setProcessStatus(int)), this->ui->progressBar, SLOT(setValue(int)));

    connect(this->ui->prevFrameButton, SIGNAL(clicked()), this, SLOT(previous()));
    connect(this->ui->nextFrameButton, SIGNAL(clicked()), this, SLOT(next()));

    connect(this->ui->progressBar, SIGNAL(valueChanged(int)), this, SLOT(progressBarUpdate(int)));
    this->ui->progressBar->setVisible(false);
    update();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent* event)
{
    int tx = event->globalX();
    int ty = event->globalY();
    if(m_server->getFrameCount() > 0)
    {
        int ax = m_canvas->mapFromGlobal(QPoint(0,0)).x();
        int ay = m_canvas->mapFromGlobal(QPoint(0,0)).y();
        int dx = tx+ax;
        int dy = ty+ay;
        // if pessed on on canvas
        if((dx >= 0 && dy >= 0) && (dx < (m_server->getWidth()) && dy < (m_server->getHeight())))
        {
            for(int i = 0; i < 10; ++i)
            {
                for(int j = 0; j < 10; ++j)
                {
                    // writing a pixel in server results in nothing if pixel
                    // position is out of bounds, so it is safe to do that
                    m_server->writePixel(dy - 5 + i, dx - 5 + j, Pixel(m_color->red(),m_color->green(),m_color->blue(),m_color->alpha()));
                }
            }
            update();
        }
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent* event)
{
    int tx = event->globalX();
    int ty = event->globalY();
    if(m_server->getFrameCount() > 0)
    {
        int ax = m_canvas->mapFromGlobal(QPoint(0,0)).x();
        int ay = m_canvas->mapFromGlobal(QPoint(0,0)).y();
        int dx = tx+ax;
        int dy = ty+ay;
        // if pessed on on canvas
        if((dx >= 0 && dy >= 0) && (dx < (m_server->getWidth()) && dy < (m_server->getHeight())))
        {
            for(int i = 0; i < 10; ++i)
            {
                for(int j = 0; j < 10; ++j)
                {
                    // writing a pixel in server results in nothing if pixel
                    // position is out of bounds, so it is safe to do that
                    m_server->writePixel(dy - 5 + i, dx - 5 + j, Pixel(m_color->red(),m_color->green(),m_color->blue(),m_color->alpha()));
                }
            }
            update();
        }
    }
}

void MainWindow::on_actionOpen_triggered()
{
    m_filename = QFileDialog::getOpenFileName(this, "Open sprite project", "", "*.ssp");
    m_server->f_open(m_filename);
    m_canvas->setPixmap(QPixmap::fromImage(m_server->getCurrentImage()));

    update();
}

void MainWindow::on_actionSave_triggered()
{
    if(m_filename == "")
        m_filename = QFileDialog::getSaveFileName(this, "Save sprite project", "", "*.ssp");
    m_server->f_save(m_filename);
}

void MainWindow::on_actionImport_triggered()
{
    m_server->f_import(QFileDialog::getOpenFileName(this, "Import sprite", "", "*.gif"));
    m_canvas->setPixmap(QPixmap::fromImage(m_server->getCurrentImage()));
    m_filename = "";
    update();
}

void MainWindow::on_actionExport_triggered()
{
    m_server->f_export(QFileDialog::getSaveFileName(this, "Export sprite", "", "*.gif"));
    m_filename = "";
}

void MainWindow::on_actionPreview_triggered()
{
    std::vector<QImage> animation(m_server->getAnimation());
    if(animation.size() > 0)
    {
        PreviewWidget* preview = new PreviewWidget(this, animation);
        preview->setWindowTitle("Preview");
    }
    else
    {
        QMessageBox::information(this, "SpriteEditor", "The project is empty. There is nothing to preview");
    }
}

void MainWindow::progressBarUpdate(int newValue)
{
    if(newValue == (this->ui->progressBar->maximum()))
    {
        this->ui->progressBar->setVisible(false);
    }
    else
    {
        this->ui->progressBar->setVisible(true);
    }
}

void MainWindow::next()
{
    m_server->nextFrame();
    update();
}

void MainWindow::previous()
{
    m_server->previousFrame();
    update();
}

void MainWindow::update()
{
    if(m_server->getFrameCount() > 0)
    {
        m_pixmap = new QPixmap(QPixmap::fromImage(m_server->getCurrentImage()));
/*        m_painter = new QPainter(m_pixmap);
        m_painter->setOpacity(0.5);
        m_painter->setPen(QColor(255,0,0));
        m_painter->drawLine(10 * server->getSelectedFrameNumber(),0,50,50);*/
        m_canvas->setPixmap(*m_pixmap);
        this->ui->frameNumberLabel->setText(QString::number(m_server->getSelectedFrameNumber()) + "/" + QString::number(m_server->getFrameCount()));
/*        std::vector<QImage> anim = server->getAnimation();
        QHBoxLayout* frameListLayout = new QHBoxLayout();
        for(int i = 0; i < anim.size(); ++i)
        {
            QLabel* temp = new QLabel(this);
            temp->setPixmap(QPixmap::fromImage(anim[i]));
            frameListLayout->addWidget(temp);
        }
        m_frameList->setLayout(frameListLayout);*/

        this->ui->mainFrame->setVisible(true);
    }
    else
    {
        this->ui->frameNumberLabel->setText("Press New, Open or Import to make a new project.");
        this->ui->mainFrame->setVisible(false);
    }
}

void MainWindow::on_actionSave_as_triggered()
{
    m_filename = QFileDialog::getSaveFileName(this, "Save sprite project", "", "*.ssp");
    m_server->f_save(m_filename);
}

void MainWindow::on_actionNew_triggered()
{
    int w = QInputDialog::getInt(this,"Width","Enter project width", 128, 16, 1920);
    int h = QInputDialog::getInt(this,"Height","Enter project height", 128, 16, 1080);
    m_server->f_new(w,h);
    m_filename = "";
    update();
}

void MainWindow::on_actionClose_triggered()
{
    m_server->close();
    update();
}

void MainWindow::on_actionCommon_triggered()
{
    if(this->ui->actionPens->isChecked())
    {
        m_penToolBar->hide();
    }
    else
    {
        m_penToolBar->show();
    }

}

void MainWindow::on_actionInsert_empty_frame_triggered()
{
    if(m_server->getFrameCount() > 0)
    {
        m_server->insertEmptyFrameAt(m_server->getSelectedFrameNumber() - 1);
        update();
    }
    else
    {
        this->on_actionNew_triggered();
    }
}

void MainWindow::on_actionDelete_current_frame_triggered()
{
    m_server->deleteFrameAt(m_server->getSelectedFrameNumber() - 1);
    update();
}

void MainWindow::on_actionSet_color_triggered()
{
    //QColorDialog* colorDialog = new QColorDialog(this);
    m_color->operator =(QColorDialog::getColor());
}

void MainWindow::on_actionEraser_triggered()
{
    m_color->operator =(QColor(0,0,0,0));
}
