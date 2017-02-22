#ifndef MAIN_H
#define MAIN_H
#include <iostream>
#include <math.h>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <QDesktopWidget>
#include <QMainWindow>

extern bool a[1000][1000];
extern double V[1000][1000];
extern double Vmax;
extern double Vmin;
void SOR();
void gs();
void tgr();
void ttgr();
void fgr();

#endif // MAIN_H
