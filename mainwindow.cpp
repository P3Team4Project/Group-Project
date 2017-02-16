//got code from  http://doc.qt.io/qt-5/qtwidgets-widgets-scribble-example.html

#include <QtWidgets>
#include "mainwindow.h"
#include "renderarea.h"

const int IdRole = Qt::UserRole;

using namespace std;

MainWindow::MainWindow()
{
    renderArea = new RenderArea;
    //setCentralWidget(renderArea);

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
      MethodComboBox->addItem(tr("Successive Over Relaxation"), RenderArea::Sor);
      MethodComboBox->addItem(tr("2-Grid"), RenderArea::Grid);
      MethodComboBox->addItem(tr("3-Grid"), RenderArea::TGrid);
      MethodComboBox->addItem(tr("4-Grid"), RenderArea::FGrid);
      MethodComboBox->addItem(tr("MultiGrid"), RenderArea::MultiGrid);


      MethodLabel = new QLabel(tr("Numerical &Methods:"));
      MethodLabel->setBuddy(MethodComboBox);

      CoordCheckBox = new QCheckBox(tr("Set &Coordinates?"));


            imageDisplay = new QLabel();



            Calculate = new QPushButton(tr("GO!"));
            connect(Calculate, SIGNAL (released()),this, SLOT (handleButton()));


            reDraw = new QPushButton(tr("Redraw"));
            connect(reDraw, SIGNAL (released()),this, SLOT (handleButton2()));

            Clear = new QPushButton(tr("Clear"));
            connect(Clear, SIGNAL (released()),this, SLOT (handleButton3()));

      connect(shapeComboBox, SIGNAL(activated(int)),
              this, SLOT(shape()));

      connect(VoltageSpinBox, SIGNAL(valueChanged(int)),
              this, SLOT(Voltage()));

      connect(brushStyleComboBox, SIGNAL(activated(int)),
              this, SLOT(brushChanged()));

      connect(MethodComboBox, SIGNAL(activated(int)),
              this, SLOT(method()));


      connect(penWidthSpinBox, SIGNAL(valueChanged(int)),
                   this, SLOT(penWidth()));

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

      QGridLayout *mainLayout = new QGridLayout;
        mainLayout->setColumnStretch(0, 1);
        mainLayout->setColumnStretch(3, 1);
        mainLayout->addWidget(imageDisplay, 0, 0, 1, 4);
        mainLayout->addWidget(renderArea, 0, 0, 1, 4);
        mainLayout->addWidget(Clear,1,1, Qt::AlignRight );
        mainLayout->addWidget(shapeLabel, 2, 0, Qt::AlignRight);
        mainLayout->addWidget(shapeComboBox, 2, 1);
        mainLayout->addWidget(penWidthLabel, 3, 0, Qt::AlignRight);
        mainLayout->addWidget(penWidthSpinBox, 3, 1);
        mainLayout->addWidget(VoltageLabel, 4, 0, Qt::AlignRight);
        mainLayout->addWidget(VoltageSpinBox, 4, 1);
        mainLayout->addWidget(brushStyleLabel, 5, 0, Qt::AlignRight);
        mainLayout->addWidget(brushStyleComboBox, 5, 1);
        mainLayout->addWidget(MethodLabel, 1, 2, Qt::AlignRight);
        mainLayout->addWidget(MethodComboBox, 1, 3);
        mainLayout->addWidget(Calculate,2,3, Qt::AlignRight );
        mainLayout->addWidget(reDraw,3,3, Qt::AlignRight );
        mainLayout->addWidget(CoordCheckBox, 6, 2, 1, 2, Qt::AlignRight);

        mainLayout->addWidget(xILabel, 7, 0, Qt::AlignRight);
        mainLayout->addWidget(xISpinBox, 7, 1);
        mainLayout->addWidget(yILabel, 7, 2, Qt::AlignRight);
        mainLayout->addWidget(yISpinBox, 7, 3);
        mainLayout->addWidget(xfLabel, 8, 0, Qt::AlignRight);
        mainLayout->addWidget(xfSpinBox, 8, 1);
        mainLayout->addWidget(yfLabel, 8, 2, Qt::AlignRight);
        mainLayout->addWidget(yfSpinBox, 8, 3);


        setLayout(mainLayout);




    brushChanged();
    shape();
    Voltage();
    penWidth();
    method();


    setWindowTitle(tr("Solution to Laplace's Equation"));
    //resize(500, 500);
}

/*void MainWindow::closeEvent(QCloseEvent *event)
{
    if (maybeSave()) {
        event->accept();
    } else {
        event->ignore();
    }
}*/

void MainWindow::handleButton()
{
    renderArea->Calc();

system("./draft3.sh");

 QPixmap pix("./SOR3.jpg");
 int we = renderArea->width();
 int h = renderArea->height();
 imageDisplay->setPixmap(pix.scaled(we,h,Qt::KeepAspectRatio));

    imageDisplay->show();
    imageDisplay->activateWindow();
    imageDisplay->raise();

}

void MainWindow::handleButton2()
{
    renderArea->show();
    renderArea->activateWindow();
    renderArea->raise();
}

void MainWindow::handleButton3()
{
    renderArea->clearImage();

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


/*void MainWindow::open()
{
    if (maybeSave()) {
        QString fileName = QFileDialog::getOpenFileName(this,
                                   tr("Open File"), QDir::currentPath());
        if (!fileName.isEmpty())
            renderArea->openImage(fileName);
    }
}*/

/*void MainWindow::save()
{
    QAction *action = qobject_cast<QAction *>(sender());
    QByteArray fileFormat = action->data().toByteArray();
    saveFile(fileFormat);
}*/

void MainWindow::penColor()
{
    QColor newColor = QColorDialog::getColor(renderArea->penColor());
    if (newColor.isValid())
        renderArea->setPenColor(newColor);
}

void MainWindow::penWidth()
{

    int newWidth = penWidthSpinBox->value();

    renderArea->setPenWidth(newWidth);
}

void MainWindow::Voltage()
{


    float newVoltage = VoltageSpinBox->value();
    renderArea->setVoltage(newVoltage);


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


/*void MainWindow::createActions()
{
    openAct = new QAction(tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

    foreach (QByteArray format, QImageWriter::supportedImageFormats()) {
        QString text = tr("%1...").arg(QString(format).toUpper());

        QAction *action = new QAction(text, this);
        action->setData(format);
        connect(action, SIGNAL(triggered()), this, SLOT(save()));
        saveAsActs.append(action);
    }

    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    penColorAct = new QAction(tr("&Pen Color..."), this);
    connect(penColorAct, SIGNAL(triggered()), this, SLOT(penColor()));

    penWidthAct = new QAction(tr("Pen &Width..."), this);
    connect(penWidthAct, SIGNAL(triggered()), this, SLOT(penWidth()));


    VoltageAct = new QAction(tr("Voltage"), this);
    connect(VoltageAct, SIGNAL(triggered()), this, SLOT(Voltage()));

    clearScreenAct = new QAction(tr("&Clear Screen"), this);
    clearScreenAct->setShortcut(tr("Ctrl+L"));
    connect(clearScreenAct, SIGNAL(triggered()),
            renderArea, SLOT(clearImage()));
}

void MainWindow::createMenus()
{
    saveAsMenu = new QMenu(tr("&Save As"), this);
    foreach (QAction *action, saveAsActs)
        saveAsMenu->addAction(action);

    fileMenu = new QMenu(tr("&File"), this);
    fileMenu->addAction(openAct);
    fileMenu->addMenu(saveAsMenu);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    optionMenu = new QMenu(tr("&Options"), this);
    optionMenu->addAction(penColorAct);
    optionMenu->addAction(penWidthAct);
    //optionMenu->addAction(VoltageAct);
    optionMenu->addSeparator();
    optionMenu->addAction(clearScreenAct);


    menuBar()->addMenu(fileMenu);
    menuBar()->addMenu(optionMenu);

}

bool MainWindow::maybeSave()
{
    if (renderArea->isModified()) {
       QMessageBox::StandardButton ret;
       ret = QMessageBox::warning(this, tr("Boundary Conditions"),
                          tr("The image has been modified.\n"
                             "Do you want to save your changes?"),
                          QMessageBox::Save | QMessageBox::Discard
                          | QMessageBox::Cancel);
        if (ret == QMessageBox::Save) {
            return saveFile("png");
        } else if (ret == QMessageBox::Cancel) {
            return false;
        }
    }
    return true;
}

bool MainWindow::saveFile(const QByteArray &fileFormat)
{
    QString initialPath = QDir::currentPath() + "/untitled." + fileFormat;

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"),
                               initialPath,
                               tr("%1 Files (*.%2);;All Files (*)")
                               .arg(QString::fromLatin1(fileFormat.toUpper()))
                               .arg(QString::fromLatin1(fileFormat)));
    if (fileName.isEmpty()) {
        return false;
    } else {
        return renderArea->saveImage(fileName, fileFormat.constData());
    }
}
*/
