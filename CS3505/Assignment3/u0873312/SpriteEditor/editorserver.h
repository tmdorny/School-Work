//A7: Sprite Editor
//Author: Nick Pershyn(uNID: u0873312)
//github: LinuxUser404

#ifndef EDITORSERVER_H
#define EDITORSERVER_H

#include <QObject>
#include <QFile>
#include <QString>
#include <vector>
#include "image.h"
#include <QMovie>
#include <QLayout>

class EditorServer : public QObject
{
    Q_OBJECT
public:
    explicit EditorServer(QObject *parent = 0);

private:
    std::vector<Image*> m_project;
    size_t height;
    size_t width;

    int m_selected;

    void clean();

signals:
    void setProcessRange(int low_value, int high_value);
    void setProcessStatus(int value);

public slots:
    void f_new(int w, int h);
    void f_open(QString filename); //open project from a file
    void f_save(QString filename); //save project to a file
    void f_import(QString filename); //import project from a gif file
    void f_export(QString filename); //export project to a gif file

    void close();

    QImage getCurrentImage();

    void selectFrame(int n);
    void nextFrame();
    void previousFrame();

    size_t getFrameCount();
    size_t getSelectedFrameNumber();

    void insertEmptyFrameAt(const int position);
    void deleteFrameAt(const int position);
    //void copyCurrentFrame();
    //void pasteFrame();
    //void cutFrame();

    //void writeSelectedFrame(QImage& Frame);

    int getHeight() const;
    int getWidth() const;

    void writePixel(int row, int col, Pixel p);


    std::vector<QImage> getAnimation();

};

#endif // EDITORSERVER_H
