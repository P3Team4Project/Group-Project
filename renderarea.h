#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QColor>
#include <QImage>
#include <QPoint>
#include <QWidget>
#include <iostream>
#include <math.h>
#include <cmath>
#include <cstdlib>
#include <fstream>



class RenderArea : public QWidget
{
    Q_OBJECT

public:
    enum Shape { Line, Points, Ellipse, FreeHand, Eraser};
    enum Method { GS, Jacobi, Sor, Grid, MultiGrid, TGrid, FGrid};
    RenderArea(QWidget *parent = 0);

    bool openImage(const QString &fileName);
    bool saveImage(const QString &fileName, const char *fileFormat);
    void setPenColor(const QColor &newColor);
    void setPenWidth(int newWidth);
    void setVoltage(float newVoltage);
    void setxI(int newxI);
    void setxf(int newxf);
    void setyI(int newyI);
    void setyf(int newyf);
    void Calc();






    bool isModified() const { return modified; }
    QColor penColor() const { return myPenColor; }
    int penWidth() const { return myPenWidth; }
    float Voltage() const {return myVoltage; }

    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;

public slots:
    void clearImage();
    void setBrush(const QBrush &brush);
    void setShape(Shape shape);
    void setMethod(Method method);
    bool setCoord(bool coord);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;


private:

    void drawLineTo(const QPoint &endPoint);
    void setLineTo(const int xI, const int yI, const int xf, const int yf);
    void EraseTo(const QPoint &endPoint);
    void drawPointTo(const int x, const int y);
    void drawElTo(const int x, const int y);
    void setElTo(const int xI, const int yI, const int xf);
    void VCh1();
    void VE();
    void VIni();
    void VCh2();
    void resizeImage(QImage *image, const QSize &newSize);



    Shape shape;
    Method method;
    QBrush brush;
    bool modified;
    bool scribbling;
    bool coord;
    int myPenWidth;
    float myVoltage;
    int myxI;
    int myxf;
    int myyI;
    int myyf;
    QColor myPenColor;
    QImage image;
    QPoint lastPoint;
    int lx, ly;
    bool b[500][500];


};

#endif // RENDERAREA_H
