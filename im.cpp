#include "EasyBMP.h"

int im(){
int imax;
BMP I;
I.ReadFromFile("test3.bmp");

imax=I.TellWidth();
return imax;
}
