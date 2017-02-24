#include <QtWidgets>
#include "main.h"
#include "imagedisplay.h"




imageDisplay::imageDisplay(QWidget *parent)
    : QWidget(parent)
{
}

void imageDisplay::mouseMoveEvent(QMouseEvent *event)
{

    cout<<V[event->x()][event->y()]<<endl;
}
