//A7: Sprite Editor
//Author: Nick Pershyn(uNID: u0873312)
//github: LinuxUser404

#include "image.h"
#include <QImage>

Image::Image(QObject *parent) : QObject(parent)
{
    m_cols = 0;
    m_rows = 0;
}

Image::Image(QObject *parent, QImage qimage) : QObject(parent)
{
    // setting Image size
    m_cols = qimage.width();
    m_rows = qimage.height();
    m_image2D.resize(m_rows);
    for(size_t row = 0; row < m_image2D.size(); ++row)
    {
        m_image2D[row].resize(m_cols);
        // setting pixel data
        for(size_t col = 0; col < m_image2D[row].size(); ++col)
            m_image2D[row][col] = Pixel(qimage.pixel(col, row));
    }


}

Image::Image(size_t height, size_t width, QObject *parent) : QObject(parent)
{
    m_rows = (height);
    m_cols = (width);
    m_image2D.resize(m_rows);
    for(size_t row = 0; row < m_image2D.size(); ++row)
    {
        m_image2D[row].resize(m_cols);
        // setting pixel data
        for(size_t col = 0; col < m_image2D[row].size(); ++col)
            m_image2D[row][col] = Pixel();
    }
}

QImage Image::getQImage()
{
    QImage image(m_cols, m_rows, QImage::Format_ARGB32);
    for(size_t row = 0; row < m_image2D.size(); ++row)
    {
        // setting pixel data
        for(size_t col = 0; col < m_image2D[row].size(); ++col)
            image.setPixel(col, row, m_image2D[row][col].getQRgb());
    }
    return image;
}

Pixel Image::getPixel(int row, int col) const
{
    return m_image2D[row][col];
}

void Image::setPixel(const size_t row, const size_t col, Pixel p)
{
    m_image2D[row][col] = p;
}

size_t Image::getHeight() const
{
    return m_rows;
}

size_t Image::getWidth() const
{
    return m_cols;
}
