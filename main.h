#ifndef MAIN_H
#define MAIN_H

#include <QDesktopWidget>
#include <QMainWindow>

extern bool a[1000][1000];
extern double V[1000][1000];


extern double Vmax;
extern double Vmin;
void jac(double ET);
void jac1(int xgrid, int ygrid, double ET);
void jace1(double ET);
void jace2(double ET);
void SOR(double ET);
void SOR1(int xgrid, int ygrid, double ET);
void SORE1(double ET);
void SORE2(double ET);
void gs(double ET);
void gs1(int xgrid, int ygrid, double ET);
void gse1(double ET);
void gse2(double ET);
void tgr(double ET);
void tgr1(int xgrid, int ygrid, double ET);
void tgre1(double ET);
void tgre2(double ET);
void ttgr(double ET);
void ttgr1(int xgrid, int ygrid, double ET);
void ttgre1(double ET);
void ttgre2(double ET);
void fgr(double ET);
void fgr1(int xgrid, int ygrid, double ET);
void fgre1(double ET);
void fgre2(double ET);



#endif // MAIN_H
