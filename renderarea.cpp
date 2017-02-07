#include <QtWidgets>
#include "renderarea.h"
#include "main.h"

using namespace std;

bool a[500][500];
bool b[500][500];
float V[500][500];

RenderArea::RenderArea(QWidget *parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_StaticContents);
    modified = false;
    scribbling = false;
    myPenWidth = 1;
    myVoltage=0;
    myPenColor = Qt::blue;
    shape=Line;
}

QSize RenderArea::minimumSizeHint() const
{
    return QSize(500, 500);
}

QSize RenderArea::sizeHint() const
{
    return QSize(500, 500);
}

bool RenderArea::openImage(const QString &fileName)
{
    QImage loadedImage;
    if (!loadedImage.load(fileName))
        return false;

    QSize newSize = loadedImage.size().expandedTo(size());
    resizeImage(&loadedImage, newSize);
    image = loadedImage;
    modified = false;
    update();
    return true;
}

bool RenderArea::saveImage(const QString &fileName, const char *fileFormat)
{
    QImage visibleImage = image;
    resizeImage(&visibleImage, size());

    if (visibleImage.save(fileName, fileFormat)) {
        modified = false;
        return true;
    } else {
        return false;
    }
}

void RenderArea::setShape(Shape shape)
{
    this->shape = shape;
    update();
}


void RenderArea::setPenColor(const QColor &newColor)
{
    myPenColor = newColor;
}

void RenderArea::setBrush(const QBrush &brush)
{
    this->brush = brush;
    update();
}


void RenderArea::setPenWidth(int newWidth)
{
    myPenWidth = newWidth;
}

void RenderArea::setVoltage(float newVoltage)
{
    myVoltage = newVoltage;

}

void RenderArea::clearImage()
{
    image.fill(qRgb(255, 255, 255));
    modified = true;
    update();
}

void RenderArea::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {

            lastPoint = event->pos();
            scribbling = true;
            for (int i=0; i<=500; i++){
                for (int j=0; j<=500; j++){
                    if (qRed(image.pixel(i,j))==255){
                        if(qBlue(image.pixel(i,j))==255){
                                if(qGreen(image.pixel(i,j))==255){
                                    b[i][j]=true;
                                }
                                }
                                }
                }
            }

    }
}

void RenderArea::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && scribbling)
        switch (shape){
        case FreeHand:
            drawLineTo(event->pos());
            V[event->x()][event->y()]=myVoltage;
            a[event->x()][event->y()]=true;
            break;
        case Text:
            /*painter.drawText(rect,
                            Qt::AlignCenter,
                            tr("Voltage = ", myVoltage));*/
            break;
        case Line:

             break;
        case Points:
             break;
        case Ellipse:
            break;
           /* QRect rect(lastPoint, lastPoint, lastPoint, lastPoint);
             painter.drawEllipse(rect);*/
        }
}

void RenderArea::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && scribbling) {
        switch (shape){
        case FreeHand:
            drawLineTo(event->pos());
            V[event->x()][event->y()]=myVoltage;
            a[event->x()][event->y()]=true;
            scribbling = false;
            break;
        case Text:
            /*painter.drawText(event->pos(),
                            Qt::AlignCenter,
                            tr("Voltage = ", myVoltage));*/
            break;
        case Line:
             drawLineTo(event->pos());
             for (int i=0; i<=500; i++){
                 for (int j=0; j<=500; j++){
                     if (b[i][j]){
                         if (qRed(image.pixel(i,j))!=255||qBlue(image.pixel(i,j))!=255||qGreen(image.pixel(i,j))!=255){

                                         V[i][j]=myVoltage;
                                         a[i][j]=true;
                                         b[i][j]=false;

                         }
                     }
                 }
             }
             break;
        case Points:
             //painter.drawPoints(lastPoint, 1);
             break;
        case Ellipse:
            break;
            /*QRect rect(lastPoint, lastPoint, lastPoint, lastPoint);
             painter.drawEllipse(rect);*/
        }
    }
}

void RenderArea::paintEvent(QPaintEvent *event)
{

        QPainter painter(this);
        QRect dirtyRect = event->rect();
        painter.drawImage(dirtyRect, image, dirtyRect);

}

void RenderArea::resizeEvent(QResizeEvent *event)
{
    if (width() > image.width() || height() > image.height()) {
        int newWidth = qMax(width() + 128, image.width());
        int newHeight = qMax(height() + 128, image.height());
        resizeImage(&image, QSize(newWidth, newHeight));
        update();
    }
    QWidget::resizeEvent(event);
}

void RenderArea::drawLineTo(const QPoint &endPoint)
{
    QPainter painter(&image);
    painter.setPen(QPen(Qt::blue, myPenWidth, Qt::SolidLine, Qt::RoundCap,
                        Qt::RoundJoin));
    painter.drawLine(lastPoint, endPoint);
    modified = true;

    int rad = (myPenWidth / 2) + 2;
    update(QRect(lastPoint, endPoint).normalized()
                                     .adjusted(-rad, -rad, +rad, +rad));
    lastPoint = endPoint;
}


void RenderArea::resizeImage(QImage *image, const QSize &newSize)
{
    if (image->size() == newSize)
        return;

    QImage newImage(newSize, QImage::Format_RGB32);
    newImage.fill(qRgb(255, 255, 255));
    QPainter painter(&newImage);
    painter.drawImage(QPoint(0, 0), *image);
    *image = newImage;
}

