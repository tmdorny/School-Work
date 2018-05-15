//A7: Sprite Editor
//Author: Nick Pershyn(uNID: u0873312)
//github: LinuxUser404

#ifndef PIXEL_H
#define PIXEL_H

#include <stdint.h>
#include <QColor>

struct Pixel
{
    uint8_t r, g, b, a;
    Pixel()
    {
        r = 0;
        g = 0;
        b = 0;
        a = 0;
    }
    Pixel(const uint8_t R, const uint8_t G, const uint8_t B, const uint8_t A) : r(R), g(G), b(B), a(A) {}
    Pixel(QRgb rbga)
    {
        r = qRed(rbga);
        g = qGreen(rbga);
        b = qBlue(rbga);
        a = qAlpha(rbga);
    }
    QRgb getQRgb()
    {
        return ((((a*256)+r)*256+g)*256+b);
    }
};

#endif // PIXEL_H
