#include <QApplication>
#include "main.h"
#include "mainwindow.h"


int main(int argc, char *argv[])
{



    QApplication app(argc, argv);
    MainWindow window;
    window.show();
    app.exec();

    return 0;

}
