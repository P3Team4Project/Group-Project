#ifndef WINDOW_H
#define WINDOW_H


/*#include <QList>
#include <QMainWindow>*/
#include <QWidget>
#include <QPushButton>
#include <stdio.h>
#include<stdlib.h>
#include <QDesktopWidget>
#include <QMainWindow>

class QCheckBox;
class QComboBox;
class QLabel;
class QSpinBox;

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
    void penWidth();
    void Voltage();
    void xI();
    void yI();
    void xf();
    void yf();
    void xgrid();
    void ygrid();
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
    QLabel *penWidthLabel;
    QLabel *MethodLabel;
    QLabel *xILabel;
    QLabel *yILabel;
    QLabel *xfLabel;
    QLabel *yfLabel;
    QLabel *imageDisplay;
    QLabel *imageDisplay2;
    QLabel *xGridSizeLabel;
    QLabel *yGridSizeLabel;


    QSpinBox *penWidthSpinBox;
    QSpinBox *xISpinBox;
    QSpinBox *yISpinBox;
    QSpinBox *xfSpinBox;
    QSpinBox *yfSpinBox;
    QSpinBox *xGridSizeSpinBox;
    QSpinBox *yGridSizeSpinBox;
    QComboBox *shapeComboBox;
    QComboBox *MethodComboBox;
    QSpinBox *VoltageSpinBox;
    QComboBox *brushStyleComboBox;
    QPushButton *Calculate;
    QPushButton *reDraw;
    QPushButton *Vector;
    QPushButton *Heat;
    QPushButton *Clear;
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
