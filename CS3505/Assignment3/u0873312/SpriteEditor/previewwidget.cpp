//A7: Sprite Editor
//Author: Nick Pershyn(uNID: u0873312)
//github: LinuxUser404

#include "previewwidget.h"
#include <QPushButton>
#include <QTimer>
#include <QSizePolicy>
#include <QLabel>
#include <QSpinBox>

PreviewWidget::PreviewWidget(QWidget *parent, const std::vector<QImage> animation) : QDialog(parent), m_animation(animation)
{
    currentFrameNumber = 0;
    FPS = 10;

    timer = new QTimer(this);
    frame = new QLabel(this);
    playButton = new QPushButton("Play", this);
    pauseButton = new QPushButton("Pause", this);
    left = new QPushButton("Previous frame", this);
    right = new QPushButton("Next frame", this);
    frameNumberLabel = new QLabel(this);
    speedInFPS = new QSpinBox(this);


    speedInFPS->setMaximum(60);
    speedInFPS->setMinimum(1);
    speedInFPS->setValue(FPS);

    update();
    frame->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);


    QHBoxLayout* buttons = new QHBoxLayout;
    buttons->addWidget(left);
    buttons->addWidget(frameNumberLabel);
    buttons->addWidget(right);
    buttons->addWidget(new QLabel("FPS:", this));
    buttons->addWidget(speedInFPS);


    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addWidget(frame);
    mainLayout->setAlignment(frame, Qt::AlignCenter);
    mainLayout->addLayout(buttons);
    mainLayout->addWidget(playButton);
    mainLayout->addWidget(pauseButton);

    connect(left, SIGNAL(clicked()), this, SLOT(prevFrame()));
    connect(right, SIGNAL(clicked()), this, SLOT(nextFrame()));
    connect(playButton, SIGNAL(clicked()), this, SLOT(play()));
    connect(pauseButton, SIGNAL(clicked()), this, SLOT(stop()));
    connect(speedInFPS, SIGNAL(valueChanged(int)), this, SLOT(changedFPS(int)));


    this->setLayout(mainLayout);
    this->show();
    stop();
}

void PreviewWidget::nextFrame()
{
    ++currentFrameNumber;
    currentFrameNumber %= m_animation.size();
    update();
}

void PreviewWidget::prevFrame()
{
    if(currentFrameNumber == 0)
    {
        currentFrameNumber = m_animation.size() - 1;
    }
    else
    {
        --currentFrameNumber;
    }
    update();
}

void PreviewWidget::update()
{
    //TODO: gtest next and prev frame
    frame->setPixmap(QPixmap::fromImage(m_animation[currentFrameNumber]));
    frameNumberLabel->setText(QString::number(currentFrameNumber + 1) + "/" + QString::number(m_animation.size()));
}

void PreviewWidget::play()
{
    playButton->setVisible(false);
    //TODO: verify with valgrind
    delete timer;
    timer = new QTimer(this);
    timer->setInterval(1000 / FPS);
    connect(timer, SIGNAL(timeout()), this, SLOT(nextFrame()));
    //speedInFPS->setEnabled(true);
    pauseButton->setVisible(true);
    timer->start();
}

void PreviewWidget::stop()
{
    pauseButton->setVisible(false);
    timer->stop();
    playButton->setVisible(true);
}

void PreviewWidget::changedFPS(int newValue)
{
    FPS = newValue;
    timer->setInterval(1000 / FPS);
}
