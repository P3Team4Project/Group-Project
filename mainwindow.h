#ifndef WINDOW_H
#define WINDOW_H


/*#include <QList>
#include <QMainWindow>*/
#include <QWidget>
#include <QPushButton>
#include <stdio.h>
#include<stdlib.h>
#include <QDoubleSpinBox>

class QCheckBox;
class QComboBox;
class QLabel;
class QSpinBox;
class QAbstractSpinBox;

class RenderArea;

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow();


protected:
    //void closeEvent(QCloseEvent *event) override;

private slots:
    //void open();
    //void save();
    void penColor();
    void ET();
    void Voltage();
    void xI();
    void yI();
    void xf();
    void yf();
    void shape();
    void method();
    void brushChanged();
    void handleButton();
    void handleButton2();
    void handleButton3();
    void handleButton4();
    void handleButton5();

private:
    void createActions();
    void createMenus();
    bool maybeSave();
    bool saveFile(const QByteArray &fileFormat);

    RenderArea *renderArea;

    QLabel *shapeLabel;
    QLabel *VoltageLabel;
    QLabel *brushStyleLabel;
    QLabel *MethodLabel;
    QLabel *ETLabel;
    QLabel *xILabel;
    QLabel *yILabel;
    QLabel *xfLabel;
    QLabel *yfLabel;
    QLabel *imageDisplay;

    QDoubleSpinBox *ETSpinBox;
    QSpinBox *xISpinBox;
    QSpinBox *yISpinBox;
    QSpinBox *xfSpinBox;
    QSpinBox *yfSpinBox;
    QComboBox *shapeComboBox;
    QComboBox *MethodComboBox;
    QDoubleSpinBox *VoltageSpinBox;
    QComboBox *brushStyleComboBox;
    QPushButton *Calculate;
    QPushButton *reDraw;
    QPushButton *Clear;
    QPushButton *Comp1;
    QPushButton *Comp2;
    QCheckBox *CoordCheckBox;

   /* QMenu *saveAsMenu;
    QMenu *fileMenu;
    QMenu *optionMenu;
    QMenu *helpMenu;

    QAction *openAct;
    QList<QAction *> saveAsActs;
    QAction *exitAct;
    QAction *penColorAct;
    QAction *penWidthAct;
    QAction *VoltageAct;
    QAction *clearScreenAct;*/
};

#endif // WINDOW_H
