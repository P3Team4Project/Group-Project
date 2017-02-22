//got code from  http://doc.qt.io/qt-5/qtwidgets-widgets-scribble-example.html

#include <QtWidgets>
#include <QMouseEvent>
#include "main.h"
#include "mainwindow.h"
#include "renderarea.h"


const int IdRole = Qt::UserRole;

using namespace std;


MainWindow::MainWindow()
{

      setMouseTracking(true);


      renderArea = new RenderArea;


      shapeComboBox = new QComboBox;
      shapeComboBox->addItem(tr("Line"), RenderArea::Line);
      shapeComboBox->addItem(tr("Points"), RenderArea::Points);
      shapeComboBox->addItem(tr("Circle"), RenderArea::Ellipse);
      shapeComboBox->addItem(tr("Free Hand"), RenderArea::FreeHand);
      shapeComboBox->addItem(tr("Rubber"), RenderArea::Eraser);

      shapeLabel = new QLabel(tr("&Shape:"));
      shapeLabel->setBuddy(shapeComboBox);

      VoltageSpinBox = new QSpinBox;
      VoltageSpinBox->setRange(-1000, 1000);

      VoltageLabel = new QLabel(tr("Voltage (Volts):"));
      VoltageLabel->setBuddy(VoltageSpinBox);

      penWidthSpinBox = new QSpinBox;
      penWidthSpinBox->setRange(0, 20);

      xGridSizeSpinBox = new QSpinBox;
      xGridSizeSpinBox->setRange(0, 5000);

      yGridSizeSpinBox = new QSpinBox;
      yGridSizeSpinBox->setRange(0, 5000);

      xGridSizeLabel = new QLabel(tr("Grid Size - X:"));
      xGridSizeLabel->setBuddy(xGridSizeSpinBox);

      yGridSizeLabel = new QLabel(tr("Y:"));
      yGridSizeLabel->setBuddy(yGridSizeSpinBox);


      penWidthLabel = new QLabel(tr("Pen &Width:"));
      penWidthLabel->setBuddy(penWidthSpinBox);

      xISpinBox = new QSpinBox;
      xISpinBox->setRange(0, 500);

      yISpinBox = new QSpinBox;
      yISpinBox->setRange(0, 500);

      xILabel = new QLabel(tr("Start point/Center Coordinates: x: "));
      xILabel->setBuddy(xISpinBox);

      yILabel = new QLabel(tr("y:"));
      yILabel->setBuddy(yISpinBox);

      xfSpinBox = new QSpinBox;
      xfSpinBox->setRange(0, 500);

      yfSpinBox = new QSpinBox;
      yfSpinBox->setRange(0, 500);

      xfLabel = new QLabel(tr("End point/on Circle Coordinates: x:"));
      xfLabel->setBuddy(xfSpinBox);

      yfLabel = new QLabel(tr("y:"));
      yfLabel->setBuddy(yfSpinBox);

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
      MethodComboBox->addItem(tr("MultiGrid"), RenderArea::MultiGrid);

      MethodLabel = new QLabel(tr("Numerical &Method:"));
      MethodLabel->setBuddy(MethodComboBox);

      CoordCheckBox = new QCheckBox(tr("Set &Coordinates?"));

      imageDisplay = new QLabel();
      imageDisplay2 = new QLabel();
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



      connect(shapeComboBox, SIGNAL(activated(int)),
              this, SLOT(shape()));

      connect(VoltageSpinBox, SIGNAL(valueChanged(int)),
              this, SLOT(Voltage()));

      connect(brushStyleComboBox, SIGNAL(activated(int)),
              this, SLOT(brushChanged()));

      connect(penWidthSpinBox, SIGNAL(valueChanged(int)),
                   this, SLOT(penWidth()));

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
        //mainLayout->setColumnStretch(0, 1);
        mainLayout->setColumnStretch(1, 1);
        mainLayout->addWidget(Clear,3,3, Qt::AlignRight );
        mainLayout->addWidget(imageDisplay2, 0, 0, 1, 6);
        mainLayout->addWidget(imageDisplay, 0, 0, 1, 6);
        mainLayout->addWidget(renderArea, 0, 0, 1, 6);
        mainLayout->addWidget(shapeLabel, 1, 0, Qt::AlignRight);
        mainLayout->addWidget(shapeComboBox, 1, 1);
        mainLayout->addWidget(penWidthLabel, 2, 0, Qt::AlignRight);
        mainLayout->addWidget(penWidthSpinBox, 2, 1);
        mainLayout->addWidget(VoltageLabel, 3, 0, Qt::AlignRight);
        mainLayout->addWidget(VoltageSpinBox, 3, 1);
        mainLayout->addWidget(brushStyleLabel, 4, 0, Qt::AlignRight);
        mainLayout->addWidget(brushStyleComboBox, 4, 1);
        mainLayout->addWidget(Calculate,3,4, Qt::AlignRight );
        mainLayout->addWidget(reDraw,3,5, Qt::AlignRight );
        mainLayout->addWidget(Vector,4,5,Qt::AlignRight );
        mainLayout->addWidget(Heat,4,4,Qt::AlignRight );
        mainLayout->addWidget(CoordCheckBox, 6, 2, 1, 4, Qt::AlignRight);
        mainLayout->addWidget(MethodLabel, 1, 4, Qt::AlignRight);
        mainLayout->addWidget(MethodComboBox, 1, 5);

        mainLayout->addWidget(xILabel, 7, 2, Qt::AlignRight);
        mainLayout->addWidget(xISpinBox, 7, 3);
        mainLayout->addWidget(yILabel, 7, 4, Qt::AlignRight);
        mainLayout->addWidget(yISpinBox, 7, 5);
        mainLayout->addWidget(xfLabel, 8, 2, Qt::AlignRight);
        mainLayout->addWidget(xfSpinBox, 8, 3);
        mainLayout->addWidget(yfLabel, 8, 4, Qt::AlignRight);
        mainLayout->addWidget(yfSpinBox, 8, 5);
        mainLayout->addWidget(xGridSizeLabel, 2, 2, Qt::AlignRight);
        mainLayout->addWidget(yGridSizeLabel, 2, 4, Qt::AlignRight);
        mainLayout->addWidget(xGridSizeSpinBox, 2, 3, Qt::AlignJustify);
        mainLayout->addWidget(yGridSizeSpinBox, 2, 5, Qt::AlignJustify);

        setLayout(mainLayout);




       setMinimumSize(QSize());
       setMaximumSize(QSize());

    brushChanged();
    shape();
    Voltage();
    penWidth();
    method();

    //setWindowTitle(tr("Solution to Laplace's Equation"));
    //resize(500, 500);
}


void MainWindow::handleButton()
{

    renderArea->Calc();

    cout << Vmax << " " << Vmin << endl;

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

    imageDisplay->show();
    imageDisplay->activateWindow();
    imageDisplay->raise();

    system("./draft2.sh");

QPixmap pix2("./contour1.jpg");
imageDisplay2->setPixmap(pix2.scaled(we,h));


}

void MainWindow::handleButton2()
{
    renderArea->show();
    renderArea->activateWindow();
    renderArea->raise();
}

void MainWindow::handleButton3()
{

    imageDisplay2->show();
    imageDisplay2->activateWindow();
    imageDisplay2->raise();
}

void MainWindow::handleButton4()
{

    imageDisplay->show();
    imageDisplay->activateWindow();
    imageDisplay->raise();

}

void MainWindow::handleButton5()
{
    renderArea->clearImage();
    renderArea->show();
    renderArea->activateWindow();
    renderArea->raise();
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

void MainWindow::penColor()
{
    QColor newColor = QColorDialog::getColor(renderArea->penColor());
    if (newColor.isValid())
        renderArea->setPenColor(newColor);
}

void MainWindow::penWidth()
{
    int newWidth = penWidthSpinBox->value();
    renderArea->setPenWidth(newWidth);      //(QPen(Qt::blue, width));
}

void MainWindow::Voltage()
{
    float newVoltage = VoltageSpinBox->value();
    renderArea->setVoltage(newVoltage);
}


