#ifndef IMAGEDISPLAY_H
#define IMAGEDISPLAY_H

#include <QColor>
#include <QImage>
#include <QPoint>
#include <QWidget>
#include <iostream>
#include <math.h>
#include <cmath>
#include <cstdlib>
#include <fstream>

class imageDisplay: public QWidget
{
    Q_OBJECT

public:

protected:
void mouseMoveEvent(QMouseEvent *event) override;
private slots:

private:

}

#endif // IMAGEDISPLAY_H
