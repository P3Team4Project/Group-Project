#include "main.h"
#include "renderarea.h"
#include "sor.h"

using namespace std;

void SOR()
{

    QDesktopWidget dw;
    int W = (int)dw.width()*0.5;
    int H = (int)dw.height()*0.5;

    int i, j, maxit=1000, m;
    double e[1000][1000], w=1.3,max;

    for (m=0; m<=maxit; m++){
        for (i=0; i<=W; i++){
            for (j=0; j<=H; j++){

                //if a boundary has been set, do nothing
                if ( a[i][j] ){

                }
                  //if  border condition hasn't been specified, make an approximation so that they aren't constantly zero

                    else if (j==0){
                            e[i][j]=V[i+1][j]+V[i-1][j]+V[i][j+1]+V[i][j]-4*V[i][j];
                         V[i][j]=V[i][j]+0.25*w*e[i][j];
                    }

                    else if (j==H){
                        e[i][j]=V[i+1][j]+V[i-1][j]+V[i][j]+V[i][j-1]-4*V[i][j];
                         V[i][j]=V[i][j]+0.25*w*e[i][j];
                    }

                    else if (i==0){
                        e[i][j]=V[i+1][j]+V[i][j]+V[i][j+1]+V[i][j-1]-4*V[i][j];
                        V[i][j]=V[i][j]+0.25*w*e[i][j];
                    }

                    else if (i==W){
                        e[i][j]=V[i][j]+V[i-1][j]+V[i][j+1]+V[i][j-1]-4*V[i][j];
                        V[i][j]=V[i][j]+0.25*w*e[i][j];
                    }

                    //evaluate all other points using normal finite difference scheme

                else {

                e[i][j]=V[i+1][j]+V[i-1][j]+V[i][j+1]+V[i][j-1]-4*V[i][j];  //calculation of residual
                V[i][j]=V[i][j]+0.25*w*e[i][j];  //evaluate using SOR

                }
                if(abs(V[i][j]) > max){
                                max = V[i][j];
                }
            }
        }
    }

        //output of final data to a file for plotting


    ofstream file;
    file.open("draft3.dat");
    ofstream file2;
    file2.open("grad1.dat");


    double Ex,Ey;
    for (i=1; i<W; i++){
        for (j=1; j<H; j++){

            file << (i) << "      "<< ((H-j)) << "    " <<  V[i][j] << "\n";
            if(j%25==0){
                if(i%25==0){
                Ex =  0.5*(V[i+1][j]-V[i-1][j]);
                Ey =  0.5*(V[i][j+1]-V[i][j-1]);
                if (Ex+Ey<2){
                file2 << (i) << " " << (H-j) << " " << 20*Ex << " " << 20*Ey << endl;
                }

                }

            }

            if(V[i][j]<Vmin){
                Vmin=V[i][j];
            }
            if(V[i][j]>Vmax){
                Vmax=V[i][j];
            }
            }
            file << "\n";
        }


        file2.close();

        file.close();



}
