#include "EasyBMP.h"

int jm(){
int jmax;
BMP I;
I.ReadFromFile("test3.bmp");

jmax=I.TellHeight();

return jmax;
}
