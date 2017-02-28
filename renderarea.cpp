#include <QtWidgets>
#include "renderarea.h"
#include "main.h"

using namespace std;


bool a[1000][1000];
bool b[1000][1000];
double V[1000][1000];
double Vmin=0,Vmax=0;


RenderArea::RenderArea(QWidget *parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_StaticContents);
    modified = false;
    scribbling = false;
    myET = 0.1;
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


void RenderArea::setShape(Shape shape)
{
    this->shape = shape;
    update();
}

void RenderArea::setMethod(Method method)
{
    this->method = method;
    update();
}


void RenderArea::setBrush(const QBrush &brush)
{
    this->brush = brush;
    update();
}

bool RenderArea::setCoord(bool coord)
{
    this->coord = coord;
    update();
    return coord;
}

void RenderArea::setET(double newEt)
{
    myET = newEt;
}

void RenderArea::setVoltage(double newVoltage)
{
    myVoltage = newVoltage;

}

void RenderArea::setxI(int newxI)
{
    myxI = newxI;
    update();
}

void RenderArea::setyI(int newyI)
{
    myyI = newyI;
    update();

}

void RenderArea::setxf(int newxf)
{
    myxf = newxf;
    update();

}

void RenderArea::setyf(int newyf)
{
    myyf = newyf;
    update();

}

void RenderArea::setxgrid(int newxgrid)
{
    myxgrid = newxgrid;
    update();

}

void RenderArea::setygrid(int newygrid)
{
    myygrid = newygrid;
    update();

}


void RenderArea::clearImage()
{
    if(coord==false){
        QDesktopWidget dw;
        int W = (int)dw.width()*0.5;
        int H = (int)dw.height()*0.5;

        image.fill(qRgb(255, 255, 255));
        modified = true;
        for (int i=0; i<=W; i++){
            for (int j=0; j<=H; j++){
                V[i][j]=0;
                a[i][j]=false;
            }
        }
        update();
    }
    else{

        image.fill(qRgb(255, 255, 255));
        modified = true;
        for (int i=0; i<=myxgrid; i++){
            for (int j=0; j<=myygrid; j++){
                V[i][j]=0;
                a[i][j]=false;
            }
        }
        update();

    }
}



void RenderArea::mousePressEvent(QMouseEvent *event)
{

    if (event->button() == Qt::LeftButton) {
        if(coord==false){
        switch (shape){
            case FreeHand:
                lastPoint = event->pos();
                VIni();
                scribbling = true;
                break;
            case Eraser:
                lastPoint = event->pos();
                VE();
                scribbling = true;
                break;
            case Line:
                lastPoint = event->pos();
                scribbling = true;
                VIni();
                break;
            case Points:
                scribbling = true;
                VIni();
                break;
            case Ellipse:
                lx=event->x();
                ly=event->y();
                lastPoint = event->pos();
                scribbling = true;
                VIni();
                break;
            }
        }
        else if(coord==true){
        switch (shape){
            case FreeHand:

                break;
            case Eraser:

                break;
            case Line:

                break;
            case Points:

                break;
            case Ellipse:

                break;
            }
        }
    }
}

void RenderArea::mouseMoveEvent(QMouseEvent *event)
{


    if ((event->buttons() & Qt::LeftButton) && scribbling){
        if(coord==false){
            switch (shape){
            case FreeHand:
                drawLineTo(event->pos());
                break;
            case Eraser:
                EraseTo(event->pos());
                break;
            case Line:
                break;
            case Points:
                break;
            case Ellipse:
                break;
            }
        }
            else if(coord==true){
                switch (shape){
                case FreeHand:
                    break;
                case Eraser:
                    break;
                case Line:
                    break;
                case Points:
                    break;
                case Ellipse:
                    break;
                }

        }
    }
}

void RenderArea::mouseReleaseEvent(QMouseEvent *event)
{

    if (event->button() == Qt::LeftButton && scribbling) {
        if(coord==false){
            switch (shape){
            case FreeHand:
                drawLineTo(event->pos());
                VCh2();
                scribbling = false;
                break;
            case Eraser:
                EraseTo(event->pos());
                VCh1();
                scribbling = false;
                break;
            case Line:
                drawLineTo(event->pos());
                VCh2();
                break;
            case Points:
                drawPointTo(event->x(),event->y());
                VCh2();
                break;
            case Ellipse:
                drawElTo(event->x(),event->y());
                VCh2();
                break;
            }

        }
        else if(coord==true){
            switch (shape){
            case FreeHand:

                break;
            case Eraser:

                break;
            case Line:

                break;
            case Points:

                break;
            case Ellipse:

                break;
            }


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
    painter.setPen(QPen(Qt::blue, 4, Qt::SolidLine, Qt::RoundCap,
                        Qt::RoundJoin));
    painter.drawLine(lastPoint, endPoint);
    modified = true;

    int rad = (4 / 2) + 2;
    update(QRect(lastPoint, endPoint).normalized()
                                     .adjusted(-rad, -rad, +rad, +rad));
    lastPoint = endPoint;
}

void RenderArea::setLineTo(const int xI, const int yI, const int xf, const int yf)
{
    QPainter painter(&image);
    painter.setPen(QPen(Qt::blue, 4, Qt::SolidLine, Qt::RoundCap,
                        Qt::RoundJoin));
    painter.drawLine(xI, yI, xf , yf);
    modified = true;


    update();
}

void RenderArea::EraseTo(const QPoint &endPoint)
{
    QPainter painter(&image);
    painter.setPen(QPen(Qt::white, 10, Qt::SolidLine, Qt::RoundCap,
                        Qt::RoundJoin));
    painter.drawLine(lastPoint, endPoint);
    modified = true;

    int rad = (10 / 2) + 2;
    update(QRect(lastPoint, endPoint).normalized()
                                     .adjusted(-rad, -rad, +rad, +rad));
    lastPoint = endPoint;
}

void RenderArea::drawPointTo(const int x, const int y)
{
    QPainter painter(&image);
    painter.setPen(QPen(Qt::blue, 4, Qt::SolidLine, Qt::RoundCap,
                        Qt::RoundJoin));


    painter.drawPoint(x, y);
    modified = true;

   update();
}



void RenderArea::setElTo(const int xI, const int yI,const int xf)
{
    QPainter painter(&image);
    painter.setPen(QPen(Qt::blue, 4, Qt::SolidLine, Qt::RoundCap,
                        Qt::RoundJoin));
    painter.setBrush(brush);
    QPoint center= {
            QPoint(xI, yI),

        };


    painter.drawEllipse(center, xf,xf);
    modified = true;
    update();
}
void RenderArea::setElTof(const int xI, const int yI,const int xf)
{
    QPainter painter(&image);

    painter.setBrush(QBrush(Qt::blue, Qt::SolidPattern));
    painter.setPen(QPen(Qt::blue, 4, Qt::SolidLine, Qt::RoundCap,
                        Qt::RoundJoin));
    QPoint center= {
            QPoint(xI, yI),

        };


    painter.drawEllipse(center, xf,xf);
    modified = true;
    update();
}
void RenderArea::setElToc(const int xI, const int yI,const int xf)
{
    QPainter painter(&image);
    painter.setPen(QPen(Qt::blue, 4, Qt::SolidLine, Qt::RoundCap,
                        Qt::RoundJoin));
    painter.setBrush(QBrush(Qt::NoBrush));
    QPoint center= {
            QPoint(xI, yI),

        };


    painter.drawEllipse(center, xf,xf);
    modified = true;
    update();
}

void RenderArea::drawElTo(const int x, const int y)
{
    QPainter painter(&image);
    painter.setPen(QPen(Qt::blue, 4, Qt::SolidLine, Qt::RoundCap,
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

void RenderArea::VCh1()
{
    QDesktopWidget dw;
    int W = (int)dw.width()*0.5;
    int H = (int)dw.height()*0.5;

    for (int i=0; i<=W; i++){
        for (int j=0; j<=H; j++){
            if (b[i][j]){
                if (qRed(image.pixel(i,j))==255){
                    if(qBlue(image.pixel(i,j))==255){
                            if(qGreen(image.pixel(i,j))==255){

                                V[i][j]=0;
                                a[i][j]=false;
                                b[i][j]=false;

                            }
                      }


                }
            }
        }
    }
    update();
}

void RenderArea::VE()
{
    QDesktopWidget dw;
    int W = (int)dw.width()*0.5;
    int H = (int)dw.height()*0.5;

    for (int i=0; i<=W; i++){
        for (int j=0; j<=H; j++){
            if (qRed(image.pixel(i,j))!=255||qBlue(image.pixel(i,j))!=255||qGreen(image.pixel(i,j))!=255){
                            b[i][j]=true;


              }
        }
    }
    update();
}

void RenderArea::VCh2()
{
    QDesktopWidget dw;
    int W = (int)dw.width()*0.5;
    int H = (int)dw.height()*0.5;

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

    update();
}

void RenderArea::VG(double v)
{
    QDesktopWidget dw;
    int W = (int)dw.width()*0.5;
    int H = (int)dw.height()*0.5;

    for (int i=0; i<=W; i++){
        for (int j=0; j<=H; j++){
            if (b[i][j]){
                if (qRed(image.pixel(i,j))!=255||qBlue(image.pixel(i,j))!=255||qGreen(image.pixel(i,j))!=255){

                                V[i][j]=v;
                                a[i][j]=true;
                                b[i][j]=false;
                        }

                }
            }
        }

    update();
}


void RenderArea::VIni()
{
    QDesktopWidget dw;
    int W = (int)dw.width()*0.5;
    int H = (int)dw.height()*0.5;

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
    update();

}

void RenderArea::Calc()
{

    if (coord==false){
    switch (method){
    case Sor:
      SOR(myET);
        break;
    case GS:
        gs(myET);
        break;
    case Jacobi:
        jac(myET);
        break;
    case Grid:
        tgr(myET);
        break;
    case TGrid:
        ttgr(myET);
        break;
    case FGrid:
        fgr(myET);
        break;
    }
}
    else {
    switch (method){
    case Sor:
      SOR1(myxgrid, myygrid, myET);
        break;
    case GS:
        gs1(myxgrid, myygrid,myET);
        break;
    case Jacobi:
        jac1(myxgrid, myygrid,myET);
        break;
    case Grid:
        tgr1(myxgrid, myygrid,myET);
        break;
    case TGrid:
        ttgr1(myxgrid, myygrid,myET);
        break;
    case FGrid:
        fgr1(myxgrid, myygrid,myET);
        break;
    }
    }
}

void RenderArea::comp1()
{

    QDesktopWidget dw;
    int W = (int)dw.width()*0.5;
    int H = (int)dw.height()*0.5;

    clearImage();
    switch (method){
    case Sor:

      VIni();
      setElTof((W/2),(H/2),100);
      VG(0);
      VIni();
      setElToc((W/2),(H/2),200);
      VG(10);
      SORE1(myET);
        break;
    case GS:
        VIni();
        setElTof((W/2),(H/2),100);
        VG(0);
        VIni();
        setElToc((W/2),(H/2),200);
        VG(10);
        gse1(myET);
        break;
    case Jacobi:
        VIni();
        setElTof((W/2),(H/2),100);
        VG(0);
        VIni();
        setElToc((W/2),(H/2),200);
        VG(10);
        jace1(myET);
        break;
    case Grid:
        VIni();
        setElTof((W/2),(H/2),100);
        VG(0);
        VIni();
        setElToc((W/2),(H/2),200);
        VG(10);
        tgre1(myET);
        break;
    case TGrid:
        VIni();
        setElTof((W/2),(H/2),100);
        VG(0);
        VIni();
        setElToc((W/2),(H/2),200);
        VG(10);
        ttgre1(myET);
        break;
    case FGrid:
        VIni();
        setElTof((W/2),(H/2),100);
        VG(0);
        VIni();
        setElToc((W/2),(H/2),200);
        VG(10);
        fgre1(myET);
        break;


}
}

void RenderArea::comp2()
{

    QDesktopWidget dw;
    int W = (int)dw.width()*0.5;
    int H = (int)dw.height()*0.5;

    clearImage();
    switch (method){
    case Sor:
        VIni();
        setElTof((W/2),(H/2),100);
        VG(0);
        VIni();
        setLineTo(0,0,0,W);
        VG(10);
        VIni();
        setLineTo(W,H,W,0);
        VG(-10);
        SORE2(myET);
        break;
    case GS:
        VIni();
        setElTof((W/2),(H/2),100);
        VG(0);
        VIni();
        setLineTo(0,0,0,W);
        VG(10);
        VIni();
        setLineTo(W,H,W,0);
        VG(-10);
        gse2(myET);
        break;
    case Jacobi:
        VIni();
        setElTof((W/2),(H/2),100);
        VG(0);
        VIni();
        setLineTo(0,0,0,W);
        VG(10);
        VIni();
        setLineTo(W,H,W,0);
        VG(-10);
        jace2(myET);
        break;
    case Grid:
        VIni();
        setElTof((W/2),(H/2),100);
        VG(0);
        VIni();
        setLineTo(0,0,0,W);
        VG(10);
        VIni();
        setLineTo(W,H,W,0);
        VG(-10);
        tgre2(myET);
        break;
    case TGrid:
        VIni();
        setElTof((W/2),(H/2),100);
        VG(0);
        VIni();
        setLineTo(0,0,0,W);
        VG(10);
        VIni();
        setLineTo(W,H,W,0);
        VG(-10);
        ttgre2(myET);
        break;
    case FGrid:
        VIni();
        setElTof((W/2),(H/2),100);
        VG(0);
        VIni();
        setLineTo(0,0,0,W);
        VG(10);
        VIni();
        setLineTo(W,H,W,0);
        VG(-10);
        fgre2(myET);
        break;


}
}

void RenderArea::lineDraw()
{
    double dx = myxf - myxI;
    double dy = myyf -  myyI;
    double m = dy/dx;
    double c = myyI - m*myxI;
    int y,x;
    cout<<m<<endl;
    if(myxI==myxf){
        if(myyI<myyf){
          for (int i=myyI; i<=myyf; i++){
              if(myxI==0){
                  for (int j=0; j<=2; j++){
                         V[j][i]= myVoltage;
                         a[j][i]=true;
                         b[j][i]=false;
                      }
              }
              else if(myxf==1){
                  for (int j=0; j<=3; j++){
                         V[j][i]= myVoltage;
                         a[j][i]=true;
                         b[j][i]=false;
                      }
              }
              else{
              for (int j=myxf-3; j<=myxf+2; j++){
                     V[j][i]= myVoltage;
                     a[j][i]=true;
                     b[j][i]=false;
                  }
              }
          }
          }
          if(myyI>myyf){
              for (int i=myyf; i<=myyI; i++){
                  if(myxf==0){
                      for (int j=0; j<=2; j++){
                             V[j][i]= myVoltage;
                             a[j][i]=true;
                             b[j][i]=false;
                          }
                  }
                  else if(myxf==1){
                      for (int j=0; j<=3; j++){
                             V[j][i]= myVoltage;
                             a[j][i]=true;
                             b[j][i]=false;
                          }
                  }
                  else{
                  for (int j=myxf-3; j<=myxf+2; j++){
                         V[j][i]= myVoltage;
                         a[j][i]=true;
                         b[j][i]=false;
                      }
                  }
              }
          }
    }
    else{
    if(m<=1){
    if(m>=-1){
        if(myxI<myxf){
        for (int i=myxI; i<=myxf; i++){
            y = m*i + c;
                for (int j=y-3; j<=y+2; j++){
                   V[i][j]= myVoltage;
                   a[i][j]=true;
                   b[i][j]=false;
                }
        }
        }
        else{
            for (int i=myxf; i<=myxI; i++){
                y = m*i + c;
                    for (int j=y-3; j<=y+2; j++){
                       V[i][j]= myVoltage;
                       a[i][j]=true;
                       b[i][j]=false;
                    }
            }
        }
    }
    }
    if(m>1){
      if(myyI<myyf){
        for (int i=myyI; i<=myyf; i++){
            x = (i-c)/m;

                for (int j=x-3; j<=x+2; j++){
                   V[j][i]= myVoltage;
                   a[j][i]=true;
                   b[j][i]=false;
                }
        }
        }
        if(myyI>=myyf){
        for (int i=myyf; i<=myyI; i++){
            x = (i-c)/m;

                for (int j=x-3; j<=x+2; j++){
                   V[j][i]= myVoltage;
                   a[j][i]=true;
                   b[j][i]=false;
                }
        }
        }
    }

    if(m<-1){
        if(myyI<myyf){
        for (int i=myyI; i<=myyf; i++){
            x = (i-c)/m;

                for (int j=x-3; j<=x+2; j++){
                   V[j][i]= myVoltage;
                   a[j][i]=true;
                   b[j][i]=false;
                }
        }
        }
        if(myyI>=myyf){
        for (int i=myyf; i<=myyI; i++){
            x = (i-c)/m;

                for (int j=x-3; j<=x+2; j++){
                   V[j][i]= myVoltage;
                   a[j][i]=true;
                   b[j][i]=false;
                }
        }
        }
    }

}
}




void RenderArea::circleDraw()
{
    if(myxI - myxf < 0){
        int r = myxf;
        for (int i=0; i <= myxI + r; i++){
            for (int j = myyI - r; j <= myyI + r; j++){
                if((myxI-i)*(myxI-i) + (myyI-j)*(myyI-j) <= r*r){
                    V[i][j]= myVoltage;
                    a[i][j]=true;
                    b[i][j]=false;



                }
            }
        }
    }
    else{

    int r = myxf;
    for (int i=myxI - r; i <= myxI + r; i++){
        for (int j = myyI - r; j <= myyI + r; j++){
            if((myxI-i)*(myxI-i) + (myyI-j)*(myyI-j) <= r*r){
                V[i][j]= myVoltage;
                a[i][j]=true;
                b[i][j]=false;



            }
        }
    }
    }
}

void RenderArea::circleDrawHollow()
{
    int r = myxf;
    if(myxI - myxf < 0){
        for (int i=0; i <= myxI + r; i++){
        for (int j = myyI - r; j <= myyI + r; j++){
            if((myxI-i)*(myxI-i) + (myyI-j)*(myyI-j) <= r*r){
                if((myxI-i)*(myxI-i) + (myyI-j)*(myyI-j) >= (r-2)*(r-2)){
                V[i][j]= myVoltage;
                a[i][j]=true;
                b[i][j]=false;
                }
            }
        }
    }
    }
    else{
        for (int i=myxI - r; i <= myxI + r; i++){
        for (int j = myyI - r; j <= myyI + r; j++){
            if((myxI-i)*(myxI-i) + (myyI-j)*(myyI-j) <= r*r){
                if((myxI-i)*(myxI-i) + (myyI-j)*(myyI-j) >= (r-2)*(r-2)){
                V[i][j]= myVoltage;
                a[i][j]=true;
                b[i][j]=false;
                }
            }
        }
    }
    }
}
