//A7: Sprite Editor
//Author: Nick Pershyn(uNID: u0873312)
//github: LinuxUser404

#ifndef PREVIEWWIDGET_H
#define PREVIEWWIDGET_H

#include <QDialog>
#include <QBoxLayout>
#include <QTimer>
#include <QLabel>
#include <QSpinBox>

class PreviewWidget : public QDialog
{
    Q_OBJECT
public:
    explicit PreviewWidget(QWidget *parent, const std::vector<QImage> animation);
private:
    QTimer* timer;
    std::vector<QImage> m_animation;
    size_t currentFrameNumber;
    size_t FPS;

    QLabel* frame;
    QPushButton* playButton;
    QPushButton* pauseButton;
    QPushButton* left;
    QPushButton* right;

    QLabel* frameNumberLabel;
    QSpinBox* speedInFPS;
signals:

public slots:
private slots:
    void nextFrame();
    void prevFrame();

    void update();

    void play();
    void stop();

    void changedFPS(int newValue);
};

#endif // PREVIEWWIDGET_H
