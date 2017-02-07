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
    enum Shape { Line, Points, Ellipse, Text, FreeHand, Eraser};
    RenderArea(QWidget *parent = 0);

    bool openImage(const QString &fileName);
    bool saveImage(const QString &fileName, const char *fileFormat);
    void setPenColor(const QColor &newColor);
    void setPenWidth(int newWidth);
    void setVoltage(float newVoltage);

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

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    void drawLineTo(const QPoint &endPoint);
    void EraseTo(const QPoint &endPoint);
    void drawPointTo(const int x, const int y);
    void drawTextTo(const int x, const int y);
    void drawElTo(const int x, const int y);
    void resizeImage(QImage *image, const QSize &newSize);

    Shape shape;
    QBrush brush;
    bool modified;
    bool scribbling;
    int myPenWidth;
    float myVoltage;
    QColor myPenColor;
    QImage image;
    QPoint lastPoint;
    int lx;
    int ly;

};

#endif // RENDERAREA_H
