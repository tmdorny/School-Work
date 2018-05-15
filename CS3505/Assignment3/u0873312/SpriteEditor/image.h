//A7: Sprite Editor
//Author: Nick Pershyn(uNID: u0873312)
//github: LinuxUser404

#ifndef IMAGE_H
#define IMAGE_H

#include <QObject>
#include <vector>
#include <QImage>
#include "pixel.h"

class Image : public QObject
{
    Q_OBJECT
public:
    explicit Image(QObject *parent = 0);
    Image(QObject *parent, QImage qimage);
    Image(size_t height, size_t width ,QObject *parent);

    QImage getQImage();

    Pixel getPixel(int row, int col) const;
    void setPixel(const size_t row, const size_t col, const Pixel p);

    size_t getHeight() const;
    size_t getWidth() const;

private:
    std::vector< std::vector<Pixel> > m_image2D;
    size_t m_cols;
    size_t m_rows;
signals:

public slots:
};

#endif // IMAGE_H
