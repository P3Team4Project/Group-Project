//got code from  http://doc.qt.io/qt-5/qtwidgets-widgets-scribble-example.html

#include <QtWidgets>
#include <QMouseEvent>
#include "main.h"
#include "mainwindow.h"
#include "renderarea.h"


const int IdRole = Qt::UserRole;

using namespace std;
bool comp1;
bool comp2;

MainWindow::MainWindow()
{


      setMouseTracking(true);

      renderArea = new RenderArea;
      renderArea->setMouseTracking(true);

      imageDisplay = new QLabel();
      imageDisplay2 = new QLabel();
      drawDisplay= new QLabel();

      imageDisplay->setMouseTracking(true);
      imageDisplay2->setMouseTracking(true);

      VDisp = new QLabel();
      VDisp2= new QLabel();




      shapeComboBox = new QComboBox;
      shapeComboBox->addItem(tr("Line"), RenderArea::Line);
      shapeComboBox->addItem(tr("Points"), RenderArea::Points);
      shapeComboBox->addItem(tr("Circle"), RenderArea::Ellipse);
      shapeComboBox->addItem(tr("Free Hand"), RenderArea::FreeHand);
      shapeComboBox->addItem(tr("Rubber"), RenderArea::Eraser);

      shapeLabel = new QLabel(tr("&Shape:"));
      shapeLabel->setBuddy(shapeComboBox);

      VoltageSpinBox = new QDoubleSpinBox;
      VoltageSpinBox->setRange(-1000, 1000);
      VoltageSpinBox->setDecimals(6);

      VoltageLabel = new QLabel(tr("Voltage:"));
      VoltageLabel->setBuddy(VoltageSpinBox);

      ETSpinBox = new QDoubleSpinBox;
      ETSpinBox->setRange(0, 1);
      ETSpinBox->setDecimals(10);

      ETLabel = new QLabel(tr("Error &Tolerance:"));
      ETLabel->setBuddy(ETSpinBox);

      xGridSizeSpinBox = new QSpinBox;
      xGridSizeSpinBox->setRange(0, 5000);

      yGridSizeSpinBox = new QSpinBox;
      yGridSizeSpinBox->setRange(0, 5000);

      xGridSizeLabel = new QLabel(tr("Grid Size - x:"));
      xGridSizeLabel->setBuddy(xGridSizeSpinBox);

      yGridSizeLabel = new QLabel(tr("y:"));
      yGridSizeLabel->setBuddy(yGridSizeSpinBox);

      coordTitle = new QLabel(tr("Coordinates   ---------------------------------------------------------------------------"));

      freehandTitle = new QLabel(tr("Free-hand     ------------------------------------------------------------------------------"));


      xISpinBox = new QSpinBox;
      xISpinBox->setRange(0, 2000);

      yISpinBox = new QSpinBox;
      yISpinBox->setRange(0, 2000);

      xILabel = new QLabel(tr("Start/Center- x: "));
      xILabel->setBuddy(xISpinBox);

      yILabel = new QLabel(tr("y:"));
      yILabel->setBuddy(yISpinBox);

      xfSpinBox = new QSpinBox;
      xfSpinBox->setRange(0, 2000);

      yfSpinBox = new QSpinBox;
      yfSpinBox->setRange(0, 2000);

      xfLabel = new QLabel(tr("End/Radius- x/r:"));
      xfLabel->setBuddy(xfSpinBox);

      yfLabel = new QLabel(tr("y:"));
      yfLabel->setBuddy(yfSpinBox);

      VdispLabel = new QLabel(tr("Potential at mouse:"));

      Vdisp2Label = new QLabel(tr("CPU Run Time:"));

      brushStyleComboBox = new QComboBox;
      brushStyleComboBox->addItem(tr("Solid"), static_cast<int>(Qt::SolidPattern));
      brushStyleComboBox->addItem(tr("None"), static_cast<int>(Qt::NoBrush));

      brushStyleLabel = new QLabel(tr("&Fill:"));
      brushStyleLabel->setBuddy(brushStyleComboBox);

      MethodComboBox = new QComboBox;
      MethodComboBox->addItem(tr("Gauss-Seidel"), RenderArea::GS);
      MethodComboBox->addItem(tr("Jacobi"), RenderArea::Jacobi);
      MethodComboBox->addItem(tr("SOR"), RenderArea::Sor);
      MethodComboBox->addItem(tr("2-Grid"), RenderArea::Grid);
      MethodComboBox->addItem(tr("3-Grid"), RenderArea::TGrid);
      MethodComboBox->addItem(tr("4-Grid"), RenderArea::FGrid);


      MethodLabel = new QLabel(tr("Numerical &Method:"));
      MethodLabel->setBuddy(MethodComboBox);

      CoordCheckBox = new QCheckBox(tr("&Coordinates"));


      //legend = new QLabel();



      Calculate = new QPushButton(tr("GO!"));
      connect(Calculate, SIGNAL (released()),this, SLOT (handleButton()));

      reDraw = new QPushButton(tr("     Redraw     "));
      connect(reDraw, SIGNAL (released()),this, SLOT (handleButton2()));


      Vector = new QPushButton(tr("Equipotentials"));
      connect(Vector, SIGNAL (released()),this, SLOT (handleButton3()));

      Heat = new QPushButton(tr("Heat Map"));
      connect(Heat, SIGNAL (released()),this, SLOT (handleButton4()));

      Clear = new QPushButton(tr("Clear"));
      connect(Clear, SIGNAL (released()),this, SLOT (handleButton5()));

      InsertL = new QPushButton(tr("Insert Line"));
      connect(InsertL, SIGNAL (released()),this, SLOT (handleButton6()));

      InsertC = new QPushButton(tr("Insert Filled Circle"));
      connect(InsertC, SIGNAL (released()),this, SLOT (handleButton7()));

      InsertCH = new QPushButton(tr("Insert Circle"));
      connect(InsertCH, SIGNAL (released()),this, SLOT (handleButton8()));

      Comp1 = new QPushButton(tr("Comp prob1"));
      connect(Comp1, SIGNAL (released()),this, SLOT (handleButton9()));

      Comp2 = new QPushButton(tr("Comp prob2"));
      connect(Comp2, SIGNAL (released()),this, SLOT (handleButton10()));




      connect(shapeComboBox, SIGNAL(activated(int)),
              this, SLOT(shape()));

      connect(VoltageSpinBox, SIGNAL(valueChanged(double)),
                    this, SLOT(Voltage()));


      connect(brushStyleComboBox, SIGNAL(activated(int)),
              this, SLOT(brushChanged()));

      connect(ETSpinBox, SIGNAL(valueChanged(double)),
                         this, SLOT(ET()));

      connect(MethodComboBox, SIGNAL(activated(int)),
              this, SLOT(method()));

      connect(xISpinBox, SIGNAL(valueChanged(int)),
                   this, SLOT(xI()));

      connect(yISpinBox, SIGNAL(valueChanged(int)),
                   this, SLOT(yI()));

      connect(xfSpinBox, SIGNAL(valueChanged(int)),
                   this, SLOT(xf()));

      connect(yfSpinBox, SIGNAL(valueChanged(int)),
                   this, SLOT(yf()));

      connect(CoordCheckBox, SIGNAL(toggled(bool)),
                   renderArea, SLOT(setCoord(bool)));

      connect(xGridSizeSpinBox, SIGNAL(valueChanged(int)),
              this, SLOT(xgrid()));

      connect(yGridSizeSpinBox, SIGNAL(valueChanged(int)),
              this, SLOT(ygrid()));

      QGridLayout *mainLayout = new QGridLayout;

        mainLayout->addWidget(Clear,3,3);
        mainLayout->addWidget(Vdisp2Label,4,2, Qt::AlignRight);
        mainLayout->addWidget(VDisp2, 4, 3);
        mainLayout->addWidget(imageDisplay2, 0, 0, 1, 6);
        mainLayout->addWidget(imageDisplay, 0, 0, 1, 6);
        mainLayout->addWidget(drawDisplay, 0, 0, 1, 6);
        mainLayout->addWidget(renderArea, 0, 0, 1, 6);

        mainLayout->addWidget(shapeLabel, 3, 0, Qt::AlignRight);
        mainLayout->addWidget(shapeComboBox, 3, 1);
        mainLayout->addWidget(ETLabel, 1, 2, Qt::AlignRight);
        mainLayout->addWidget(ETSpinBox, 1, 3);
        mainLayout->addWidget(VoltageLabel, 2, 0, Qt::AlignRight);
        mainLayout->addWidget(VoltageSpinBox, 2, 1);
        mainLayout->addWidget(brushStyleLabel, 4, 0, Qt::AlignRight);
        mainLayout->addWidget(brushStyleComboBox, 4, 1);
        mainLayout->addWidget(VdispLabel,1,0, Qt::AlignRight);
        mainLayout->addWidget(VDisp, 1, 1);
        mainLayout->addWidget(Comp1,5,4);
        mainLayout->addWidget(Comp2,5,5);
        mainLayout->addWidget(Calculate,3,4);
        mainLayout->addWidget(reDraw,3,5);
        mainLayout->addWidget(Vector,4,5);
        mainLayout->addWidget(Heat,4,4);
        mainLayout->addWidget(CoordCheckBox, 5, 0, Qt::AlignRight);
        mainLayout->addWidget(MethodLabel, 1, 4, Qt::AlignRight);
        mainLayout->addWidget(MethodComboBox, 1, 5);

        mainLayout->addWidget(InsertL,7,4);
        mainLayout->addWidget(InsertC,8,4);
        mainLayout->addWidget(InsertCH,8,5);

        mainLayout->addWidget(xILabel, 7, 0, Qt::AlignRight);
        mainLayout->addWidget(xISpinBox, 7, 1);
        mainLayout->addWidget(yILabel, 7, 2, Qt::AlignRight);
        mainLayout->addWidget(yISpinBox, 7, 3);
        mainLayout->addWidget(xfLabel, 8, 0, Qt::AlignRight);
        mainLayout->addWidget(xfSpinBox, 8, 1);
        mainLayout->addWidget(yfLabel, 8, 2, Qt::AlignRight);
        mainLayout->addWidget(yfSpinBox, 8, 3);
        mainLayout->addWidget(xGridSizeLabel, 2, 2, Qt::AlignRight);
        mainLayout->addWidget(yGridSizeLabel, 2, 4, Qt::AlignRight);
        mainLayout->addWidget(xGridSizeSpinBox, 2, 3);
        mainLayout->addWidget(yGridSizeSpinBox, 2, 5);

        setLayout(mainLayout);




       //setMinimumSize(QSize());
       //setMaximumSize(QSize());

    brushChanged();
    shape();
    Voltage();
    ET();
    method();

    setWindowTitle(tr("StatiX"));
    //resize(500, 500);
}


void MainWindow::handleButton()
{
    clock_t t;
    t = clock();

    renderArea->Calc();
    t = clock() - t;


    VDisp2->setNum((float)t/(CLOCKS_PER_SEC));

    if(Vmax>0){
        if(Vmin<0){
            system("./draft3.sh");
        }
        else{
            system("./draft5.sh");
        }
    }
    else{
        system("./draft4.sh");
    }




 QPixmap pix("./SOR3.jpg");
 int we = renderArea->width();
 int h = renderArea->height();

 imageDisplay->setPixmap(pix.scaled(we,h));

    comp1=false;
    comp2=false;
    imageDisplay->show();
    imageDisplay->activateWindow();

    imageDisplay->raise();

    system("./draft2.sh");

QPixmap pix2("./contour1.jpg");
imageDisplay2->setPixmap(pix2.scaled(we,h));



}

void MainWindow::handleButton2()
{
        comp1=false;
        comp2=false;
        renderArea->show();
        renderArea->activateWindow();
        renderArea->raise();

}

void MainWindow::handleButton3()
{
    comp1=false;
    comp2=false;
    imageDisplay2->show();
    imageDisplay2->activateWindow();
    imageDisplay2->raise();
}

void MainWindow::handleButton4()
{

    comp1=false;
    comp2=false;
    imageDisplay->show();
    imageDisplay->activateWindow();
    imageDisplay->raise();

}

void MainWindow::handleButton5()
{
    comp1=false;
    comp2=false;
    renderArea->clearImage();
    renderArea->show();
    renderArea->activateWindow();
    renderArea->raise();
}

void MainWindow::handleButton6()
{

    renderArea->lineDraw();

    int we = renderArea->width();
    int h = renderArea->height();
    int newxgrid = xGridSizeSpinBox->value();
    int newygrid = yGridSizeSpinBox->value();

    QPixmap *pix = new QPixmap(newxgrid,newygrid);
    QPainter *paint = new QPainter(pix);

    for(int i=0;i<=newxgrid;i++){
        for(int j=0; j<=newygrid;j++){
            if(a[i][j]==true){
                if(V[i][j]<0){
                    paint->setPen(*(new QColor(0,0,255)));
                    paint->drawPoint(i, j);
                    update();
                }
                else if(V[i][j]>0){
                    paint->setPen(*(new QColor(255,0,0)));
                    paint->drawPoint(i, j);
                    update();
                }
                else{
                    paint->setPen(*(new QColor(0,0,0)));
                    paint->drawPoint(i, j);
                    update();
                }
            }
            else{
                paint->setPen(*(new QColor(255,255,255)));
                paint->drawPoint(i,j);
                update();
            }
        }

    }

    drawDisplay->setPixmap(pix->scaled(we,h));
    comp1=false;
    comp2=false;
    drawDisplay->show();
    drawDisplay->activateWindow();
    drawDisplay->raise();
}

void MainWindow::handleButton7()
{
    renderArea->circleDraw();

    int newxgrid = xGridSizeSpinBox->value();
    int newygrid = yGridSizeSpinBox->value();
    int we = renderArea->width();
    int h = renderArea->height();


    QPixmap *pix = new QPixmap(newxgrid,newygrid);
    QPainter *paint = new QPainter(pix);

    for(int i=0;i<=newxgrid;i++){
        for(int j=0; j<=newygrid;j++){
            if(a[i][j]==true){
                if(V[i][j]<0){
                    paint->setPen(*(new QColor(0,0,255)));
                    paint->drawPoint(i, j);
                    update();
                }
                else if(V[i][j]>0){
                    paint->setPen(*(new QColor(255,0,0)));
                    paint->drawPoint(i, j);
                    update();
                }
                else{
                    paint->setPen(*(new QColor(0,0,0)));
                    paint->drawPoint(i, j);
                    update();
                }
            }
            else{
                paint->setPen(*(new QColor(255,255,255)));
                paint->drawPoint(i,j);
                update();
            }
        }

    }
    drawDisplay->setPixmap(pix->scaled(we,h));
    comp1=false;
    comp2=false;
    drawDisplay->show();
    drawDisplay->activateWindow();
    drawDisplay->raise();
}

void MainWindow::handleButton8()
{
    renderArea->circleDrawHollow();

    int newxgrid = xGridSizeSpinBox->value();
    int newygrid = yGridSizeSpinBox->value();
    int we = renderArea->width();
    int h = renderArea->height();


    QPixmap *pix = new QPixmap(newxgrid,newygrid);
    QPainter *paint = new QPainter(pix);

    for(int i=0;i<=newxgrid;i++){
        for(int j=0; j<=newygrid;j++){
            if(a[i][j]==true){
                if(V[i][j]<0){
                    paint->setPen(*(new QColor(0,0,255)));
                    paint->drawPoint(i, j);
                    update();
                }
                else if(V[i][j]>0){
                    paint->setPen(*(new QColor(255,0,0)));
                    paint->drawPoint(i, j);
                    update();
                }
                else{
                    paint->setPen(*(new QColor(0,0,0)));
                    paint->drawPoint(i, j);
                    update();
                }
            }
            else{
                paint->setPen(*(new QColor(255,255,255)));
                paint->drawPoint(i,j);
                update();
            }
        }

    }
    drawDisplay->setPixmap(pix->scaled(we,h));
    comp1=false;
    comp2=false;
    drawDisplay->show();
    drawDisplay->activateWindow();
    drawDisplay->raise();
}

void MainWindow::handleButton9()
{
    clock_t t;
    t = clock();

    renderArea->comp1();

    t = clock() - t;

    VDisp2->setNum((float)t/(CLOCKS_PER_SEC));

system("./draft5.sh");

 QPixmap pix("./SOR3.jpg");
 int we = renderArea->width();
 int h = renderArea->height();
 imageDisplay->setPixmap(pix.scaled(we,h));

    comp1=true;
    comp2=false;
    imageDisplay->show();
    imageDisplay->activateWindow();
    imageDisplay->raise();


}

void MainWindow::handleButton10()
{
    clock_t t;
    t = clock();
    renderArea->comp2();

    t = clock() - t;

    VDisp2->setNum((float)t/(CLOCKS_PER_SEC));

system("./draft5.sh");

 QPixmap pix("./SOR3.jpg");
 int we = renderArea->width();
 int h = renderArea->height();
 imageDisplay->setPixmap(pix.scaled(we,h));

    comp1=false;
    comp2=true;
    imageDisplay->show();
    imageDisplay->activateWindow();
    imageDisplay->raise();

}

void MainWindow::shape()
{
    RenderArea::Shape shape = RenderArea::Shape(shapeComboBox->itemData(
            shapeComboBox->currentIndex(), IdRole).toInt());
    renderArea->setShape(shape);
}

void MainWindow::method()
{
    RenderArea::Method method = RenderArea::Method(MethodComboBox->itemData(
            MethodComboBox->currentIndex(), IdRole).toInt());
    renderArea->setMethod(method);
}

void MainWindow::brushChanged()
{
    Qt::BrushStyle style = Qt::BrushStyle(brushStyleComboBox->itemData(
            brushStyleComboBox->currentIndex(), IdRole).toInt());
    renderArea->setBrush(QBrush(Qt::blue, style));
}

void MainWindow::xI()
{
    int newxI = xISpinBox->value();
    renderArea->setxI(newxI);
}

void MainWindow::yI()
{
    int newyI = yISpinBox->value();
    renderArea->setyI(newyI);
}

void MainWindow::xf()
{
    int newxf = xfSpinBox->value();
    renderArea->setxf(newxf);
}

void MainWindow::yf()
{
    int newyf = yfSpinBox->value();
    renderArea->setyf(newyf);
}

void MainWindow::xgrid()
{
    int newxgrid = xGridSizeSpinBox->value();
    renderArea->setxgrid(newxgrid);
}

void MainWindow::ygrid()
{
    int newygrid = yGridSizeSpinBox->value();
    renderArea->setygrid(newygrid);
}


void MainWindow::ET()
{

    double newET = ETSpinBox->value();

    renderArea->setET(newET);
}

void MainWindow::Voltage()
{
    float newVoltage = VoltageSpinBox->value();
    renderArea->setVoltage(newVoltage);

}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    int we = renderArea->width();
    int h = renderArea->height();
    int xr=renderArea->x();
    int yr=renderArea->y();
    int xgr = xGridSizeSpinBox->value();
    int ygr = yGridSizeSpinBox->value();
    double WE= renderArea->width();
    double XGR = xGridSizeSpinBox->value();
    double H=renderArea->height();
    double YGR=yGridSizeSpinBox->value();
    int x=(int) rint((XGR/WE)*abs(xr-event->x()));
    int y=(int) rint((YGR/H)*abs(yr-event->y()));


    if (comp1==true){

            if (event->x()>=xr && event->y()>=yr){

                if(((event->x())>=(xr+we)) || ((event->y())>=(yr+h))){

            //cout<<"bla"<<endl;

                }
                else if (((event->x())<=(xr+we)) || ((event->y())<=(yr+h))){
                    if ( pow((abs(xr-event->x())-(we/2)),2)+pow((abs(yr-event->y())-(h/2)),2) <= pow(100,2) ){  //cycle through and evaluate boundaries

                                    VDisp->setNum(0);


                                }
                    else if ( pow((abs(xr-event->x())-(we/2)),2)+pow((abs(yr-event->y())-(h/2)),2) >= pow(200,2) ){  //cycle through and evaluate boundaries

                                    VDisp->setNum(0);


                                }

                    else{

                    VDisp->setNum(abs(V[abs(xr-event->x())][abs(yr-event->y())] -((10/log(200/100))*(log(sqrt(pow((abs(xr-event->x())-(we/2)),2)+pow((abs(yr-event->y())-(h/2)),2)))-log(100)))));

                    }


                    //VDisp->setNum(V[abs(xr-event->x())][abs(yr-event->y())]);
                    }
            }
            else {
            //cout<<"No Pot"<<endl;
            }


    }
    else if (comp2==true){

            if (event->x()>=xr && event->y()>=yr){

                if(((event->x())>=(xr+we)) || ((event->y())>=(yr+h))){

            //cout<<"bla"<<endl;

                }
                else if (((event->x())<=(xr+we)) || ((event->y())<=(yr+h))){

                    double v=(-0.02*(abs(xr-event->x())-(we/2))*(1-pow((10/sqrt(pow((abs(xr-event->x())-(we/2)),2)+pow((abs(yr-event->y())-(h/2)),2))),3)));

                    if ( pow((abs(xr-event->x())-(we/2)),2)+pow((abs(yr-event->y())-(h/2)),2) <= pow(100,2) ){  //cycle through and evaluate boundaries

                                    VDisp->setNum(0);


                                }

                    else{

                    VDisp->setNum(abs(V[abs(xr-event->x())][abs(yr-event->y())] -v));

                    }


                    }
            }
            else {
            //cout<<"No Pot"<<endl;
            }

        }

    else {
        if(CoordCheckBox->isChecked()==false){
            if (event->x()>=xr && event->y()>=yr){

                if(((event->x())>=(xr+we)) || ((event->y())>=(yr+h))){

            //cout<<"bla"<<endl;

                }
                else if (((event->x())<=(xr+we)) || ((event->y())<=(yr+h))){

                    VDisp->setNum(V[abs(xr-event->x())][abs(yr-event->y())]);
                    }
            }
            else {
            //cout<<"No Pot"<<endl;
            }
        }
        else{
            if (event->x()>=xr && event->y()>=yr){

                if(((event->x())>=(xr+xgr)) || ((event->y())>=(yr+ygr))){

                //cout<<"bla"<<endl;

                }
                else if (((event->x())<=(xr+xgr)) || ((event->y())<=(yr+ygr))){




                    VDisp->setNum(V[x][y]);
                    }
            }
            else {
            //cout<<"No Pot"<<endl;
            }

        }

    }



}



