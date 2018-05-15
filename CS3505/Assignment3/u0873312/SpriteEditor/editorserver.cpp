//A7: Sprite Editor
//Author: Nick Pershyn(uNID: u0873312)
//github: LinuxUser404

#include "editorserver.h"
#include <QImageReader>
#include <QMessageBox>
#include <fstream>

EditorServer::EditorServer(QObject *parent) : QObject(parent)
{
    //TODO proper dialog
    m_project.resize(0);
    m_selected = 0;
    height = 128;
    width = 128;
}

void EditorServer::clean()
{
    for(size_t i = 0; i < m_project.size(); ++i)
    {
        delete (m_project[i]);
    }
    m_project.resize(0);
    m_selected = 0;
}

void EditorServer::f_new(int w, int h)
{
    //TODO: check if there is unsaved data
    clean();
    height = h;
    width = w;
    m_project.resize(1, new Image(height, width, this));

}

// load as much as possible and report errors
void EditorServer::f_open(QString filename)
{
    clean();
    if(filename == "")
        return;
    std::ifstream in;
    in.open(filename.toUtf8().constData());
    in >> height;
    in >> width;
    size_t s;
    in >> s;
    m_project.resize(s);
    setProcessRange(int(0), int(m_project.size()));
    for(size_t i = 0; i < s; ++i)
    {
        m_project[i] = new Image(height, width, this);
        for(size_t row = 0; row < height; ++row)
        {
            for(size_t col = 0; col < width; ++col)
            {
                int r,g,b,a;
                in >> r;
                in >> g;
                in >> b;
                in >> a;
                if((0 <= r && r <= 255) && (0 <= g && g <= 255) && (0 <= b && b <= 255) && (0 <= a && a <= 255))
                {
                    m_project[i]->setPixel(row, col, Pixel(r,g,b,a));
                }
                else
                {
                    // report the errors if there are any
                    QMessageBox::information(0, "Read error in project file!", "Incorrect pixel value ("
                                         + QString::number(r) + ", "
                                         + QString::number(g) + ", "
                                         + QString::number(b) + ", "
                                         + QString::number(a) + ") at:"
                                         + QString("\n") + "Frame "
                                         + QString::number(i) + QString("\n") +"Row "
                                         + QString::number(row) + QString("\n") + "Col " + QString::number(col));
                }
            }
        }
        setProcessStatus(int(i));
    }
    in.close();
    setProcessStatus(int(m_project.size()));
}

void EditorServer::f_save(QString filename)
{
    if(filename == "")
        return;
    std::ofstream out;
    out.open(filename.toUtf8().constData());

    setProcessRange(int(0), int(m_project.size()));
    out << height << " " << width << std::endl;
    out << m_project.size() << std::endl;
    for(size_t i = 0; i < m_project.size(); ++i)
    {
        for(size_t row = 0; row < height; ++row)
        {
            for(size_t col = 0; col < width; ++col)
            {
                if(col > 0)
                    out << " ";
                out << int(m_project[i]->getPixel(row, col).r) << " "
                    << int(m_project[i]->getPixel(row, col).g) << " "
                    << int(m_project[i]->getPixel(row, col).b) << " "
                    << int(m_project[i]->getPixel(row, col).a);
                if(col == width - 1)
                    out << std::endl;
            }
        }
        setProcessStatus(int(i));
    }
    out << std::flush;
    out.close();
    setProcessStatus(int(m_project.size()));
}

void EditorServer::f_import(QString filename)
{
    clean();
    m_project.resize(0);
    if(filename == "")
        return;
    QImageReader *reader = new QImageReader(filename);
    setProcessRange(int(0), int(reader->imageCount()));
    while(reader->canRead())
    {
        m_project.push_back(new Image(this, reader->read()));
        setProcessStatus(int(m_project.size()));
    }
    if(m_project.size() > 0)
    {
        height = m_project.back()->getHeight();
        width = m_project.back()->getWidth();
    }
}

void EditorServer::f_export(QString filename)
{
    if(filename == "")
        return;
}

void EditorServer::close()
{
    clean();
    m_project.resize(0);
}

QImage EditorServer::getCurrentImage()
{
    if(m_project.size() == 0)
    {
        m_project.resize(1, 0);
        m_project[0] = new Image(height, width, this);
        selectFrame(0);
    }

    return m_project[m_selected]->getQImage();
}

void EditorServer::selectFrame(int n)
{
    if(n > 0 && n < int(m_project.size()))
        m_selected = n;
}

void EditorServer::nextFrame()
{
    if(m_selected + 1 < int(m_project.size()))
        ++m_selected;
    else
        m_selected = 0;
}

void EditorServer::previousFrame()
{
    if(m_selected > 0)
        --m_selected;
    else
        m_selected = m_project.size() - 1;
}

size_t EditorServer::getFrameCount()
{
    return m_project.size();
}

size_t EditorServer::getSelectedFrameNumber()
{
    return m_selected + 1;
}

void EditorServer::insertEmptyFrameAt(const int position)
{
    if(position >= 0 && position <= int(m_project.size()))
        m_project.insert(m_project.begin() + position, new Image(height, width, this));
}

void EditorServer::deleteFrameAt(const int position)
{
    if(position >= 0 && position < int(m_project.size()))
    {
        delete m_project[position];
        m_project.erase(m_project.begin() + position);
        if(m_selected > position)
            --m_selected;
        else if((m_selected == position) && (m_selected == int(m_project.size())))
        {
            if(m_project.size() == 0)
            {
                // if there are no frames left the project should be destroyed
                clean();
            }
            else
            {
                // if it was the last frame we should select previous one
                --m_selected;
            }
        }
    }
}

int EditorServer::getHeight() const
{
    return height;
}

int EditorServer::getWidth() const
{
    return width;
}

void EditorServer::writePixel(int row, int col, Pixel p)
{
    if((col >= 0 && col < int(width)) && (row >= 0 && row < int(height)))
        m_project[m_selected]->setPixel(row, col, p);
}

std::vector<QImage> EditorServer::getAnimation()
{
    setProcessRange(int(0), int(m_project.size()));
    std::vector<QImage> animation(0);
    for(size_t frame = 0; frame < m_project.size(); ++frame)
    {
        setProcessStatus(frame);
        animation.push_back(m_project[frame]->getQImage());
    }
    setProcessStatus(int(m_project.size()));
    return animation;
}
