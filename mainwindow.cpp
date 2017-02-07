//got code from  http://doc.qt.io/qt-5/qtwidgets-widgets-scribble-example.html

#include <QtWidgets>

#include "mainwindow.h"
#include "renderarea.h"

const int IdRole = Qt::UserRole;

MainWindow::MainWindow()
{
    renderArea = new RenderArea;
    //setCentralWidget(renderArea);

      shapeComboBox = new QComboBox;
      shapeComboBox->addItem(tr("Line"), RenderArea::Line);
      shapeComboBox->addItem(tr("Points"), RenderArea::Points);
      shapeComboBox->addItem(tr("Text"), RenderArea::Text);
      shapeComboBox->addItem(tr("Ellipse"), RenderArea::Ellipse);
      shapeComboBox->addItem(tr("Free Hand"), RenderArea::FreeHand);

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

      brushStyleComboBox = new QComboBox;
      brushStyleComboBox->addItem(tr("Solid"), static_cast<int>(Qt::SolidPattern));
      brushStyleComboBox->addItem(tr("None"), static_cast<int>(Qt::NoBrush));

      brushStyleLabel = new QLabel(tr("&Brush:"));
      brushStyleLabel->setBuddy(brushStyleComboBox);

      connect(shapeComboBox, SIGNAL(activated(int)),
              this, SLOT(shape()));

      connect(VoltageSpinBox, SIGNAL(valueChanged(int)),
              this, SLOT(Voltage()));

      connect(brushStyleComboBox, SIGNAL(activated(int)),
              this, SLOT(brushChanged()));

      connect(penWidthSpinBox, SIGNAL(valueChanged(int)),
                   this, SLOT(penWidth()));

      QGridLayout *mainLayout = new QGridLayout;
        mainLayout->setColumnStretch(0, 1);
        mainLayout->setColumnStretch(3, 1);
        mainLayout->addWidget(renderArea, 0, 0, 1, 4);
        mainLayout->addWidget(shapeLabel, 2, 0, Qt::AlignRight);
        mainLayout->addWidget(shapeComboBox, 2, 1);
        mainLayout->addWidget(penWidthLabel, 3, 0, Qt::AlignRight);
        mainLayout->addWidget(penWidthSpinBox, 3, 1);
        mainLayout->addWidget(VoltageLabel, 4, 0, Qt::AlignRight);
        mainLayout->addWidget(VoltageSpinBox, 4, 1);
        mainLayout->addWidget(brushStyleLabel, 5, 0, Qt::AlignRight);
        mainLayout->addWidget(brushStyleComboBox, 5, 1);

        setLayout(mainLayout);




    brushChanged();
    shape();
    Voltage();
    penWidth();


    setWindowTitle(tr("Boundary Conditions"));
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
void MainWindow::shape()
{
    RenderArea::Shape shape = RenderArea::Shape(shapeComboBox->itemData(
            shapeComboBox->currentIndex(), IdRole).toInt());
    renderArea->setShape(shape);
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
    /*bool ok;
    int newWidth = QInputDialog::getInt(this, tr("Boundary Conditions"),
                                        tr("Select pen width:"),
                                        renderArea->penWidth(),
                                        1, 50, 1, &ok);
    if (ok)
        renderArea->setPenWidth(newWidth);*/
    int newWidth = penWidthSpinBox->value();

    renderArea->setPenWidth(newWidth);      //(QPen(Qt::blue, width));
}

void MainWindow::Voltage()
{
    /*bool ok;
    float newVoltage = QInputDialog::getInt(this, tr("Boundary Conditions"),
                                        tr("Select Voltage:"),
                                        renderArea->Voltage(),
                                        -1000, 1000, 0.1, &ok);
    if (ok)*/

    float newVoltage = VoltageSpinBox->value();
    renderArea->setVoltage(newVoltage);


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
