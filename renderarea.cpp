#include <QtWidgets>
#include "renderarea.h"
#include "main.h"

using namespace std;


bool a[1000][1000];
bool b[1000][1000];
double V[1000][1000];


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
    QDesktopWidget dw;
    int W = (int)dw.width()*0.5;
    int H = (int)dw.height()*0.5;

    return QSize(W, H);
}

QSize RenderArea::sizeHint() const
{
    QDesktopWidget dw;
    int W = (int)dw.width()*0.5;
    int H = (int)dw.height()*0.5;
    return QSize(H, W);
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
    QDesktopWidget dw;
    int W = (int)dw.width()*0.5;
    int H = (int)dw.height()*0.5;

    if (event->button() == Qt::LeftButton) {
        switch (shape){
        case FreeHand:
            lastPoint = event->pos();
            scribbling = true;
            break;
        case Eraser:
            lastPoint = event->pos();
            scribbling = true;
            break;
        case Text:
            break;
        case Line:
            lastPoint = event->pos();
            scribbling = true;
            for (int i=0; i<=W; i++){
                for (int j=0; j<=H; j++){
                    if (qRed(image.pixel(i,j))==255){
                        if(qBlue(image.pixel(i,j))==255){
                                if(qGreen(image.pixel(i,j))==255){
                                    b[i][j]=true;
                                }
                                }
                                }
                }
            }

             break;
        case Points:
            scribbling = true;
            for (int i=0; i<=W; i++){
                for (int j=0; j<=H; j++){
                    if (qRed(image.pixel(i,j))==255){
                        if(qBlue(image.pixel(i,j))==255){
                                if(qGreen(image.pixel(i,j))==255){
                                    b[i][j]=true;
                                }
                                }
                                }
                }
            }
             break;
        case Ellipse:
            lx=event->x();
            ly=event->y();
            lastPoint = event->pos();
            scribbling = true;
            for (int i=0; i<=W; i++){
                for (int j=0; j<=H; j++){
                    if (qRed(image.pixel(i,j))==255){
                        if(qBlue(image.pixel(i,j))==255){
                                if(qGreen(image.pixel(i,j))==255){
                                    b[i][j]=true;
                                }
                                }
                                }
                }
            }
            break;
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
        case Eraser:
            EraseTo(event->pos());
            V[event->x()][event->y()]=0;
            a[event->x()][event->y()]=false;
            break;
        case Text:
            break;
        case Line:

             break;
        case Points:
             break;
        case Ellipse:
            break;

        }
}

void RenderArea::mouseReleaseEvent(QMouseEvent *event)
{
    QDesktopWidget dw;
    int W = (int)dw.width()*0.5;
    int H = (int)dw.height()*0.5;

    if (event->button() == Qt::LeftButton && scribbling) {
        switch (shape){
        case FreeHand:
            drawLineTo(event->pos());
            V[event->x()][event->y()]=myVoltage;
            a[event->x()][event->y()]=true;
            scribbling = false;
            break;
        case Eraser:
            EraseTo(event->pos());
            a[event->x()][event->y()]=false;
            V[event->x()][event->y()]=0;
            scribbling = false;
            break;
        case Text:
            drawTextTo(event->x(),event->y());
            break;
        case Line:
             drawLineTo(event->pos());
             for (int i=0; i<=W; i++){
                 for (int j=0; j<=H; j++){
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
             drawPointTo(event->x(),event->y());
             for (int i=0; i<=W; i++){
                 for (int j=0; j<=H; j++){
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
        case Ellipse:
            drawElTo(event->x(),event->y());
            for (int i=0; i<=W; i++){
                for (int j=0; j<=H; j++){
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

void RenderArea::EraseTo(const QPoint &endPoint)
{
    QPainter painter(&image);
    painter.setPen(QPen(Qt::white, myPenWidth, Qt::SolidLine, Qt::RoundCap,
                        Qt::RoundJoin));
    painter.drawLine(lastPoint, endPoint);
    modified = true;

    int rad = (myPenWidth / 2) + 2;
    update(QRect(lastPoint, endPoint).normalized()
                                     .adjusted(-rad, -rad, +rad, +rad));
    lastPoint = endPoint;
}

void RenderArea::drawPointTo(const int x, const int y)
{
    QPainter painter(&image);
    painter.setPen(QPen(Qt::blue, myPenWidth, Qt::SolidLine, Qt::RoundCap,
                        Qt::RoundJoin));


    painter.drawPoint(x, y);
    modified = true;

   update();
}

void RenderArea::drawTextTo(const int x, const int y)
{
    QPainter painter(&image);
    painter.setPen(QPen(Qt::black, myPenWidth, Qt::SolidLine, Qt::RoundCap,
                        Qt::RoundJoin));


    painter.drawText(x, y,
                     QString("%1 V").arg(myVoltage) );
    modified = true;
    update();
}

void RenderArea::drawElTo(const int x, const int y)
{
    QPainter painter(&image);
    painter.setPen(QPen(Qt::blue, myPenWidth, Qt::SolidLine, Qt::RoundCap,
                        Qt::RoundJoin));
    painter.setBrush(brush);

    int r=sqrt((x-lx)*(x-lx)+(y-ly)*(y-ly));
    painter.drawEllipse(lastPoint, r, r);
    modified = true;
    update();
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

