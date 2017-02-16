#include <QApplication>
#include "main.h"
#include "mainwindow.h"
#include <QDesktopWidget>
#include <QMainWindow>

using namespace std;

int main(int argc, char *argv[])
{
    //int i, j, maxit=5000, m;
    //float e[1000][1000], w=1.3, d=0.1;

    /*float V[500][500];
    bool a[500][500];*/
    QApplication app(argc, argv);
    MainWindow window;
    window.show();
    app.exec();

/*
    for (m=0; m<=maxit; m++){
        for (i=0; i<=500; i++){
            for (j=0; j<=500; j++){

                //if a boundary has been set, do nothing
                if ( a[i][j] ){

                }
                  //if  border condition hasn't been specified, make an approximation so that they aren't constantly zero

                    else if (j==0){
                            e[i][j]=V[i+1][j]+V[i-1][j]+V[i][j+1]+V[i][j]-4*V[i][j];
                         V[i][j]=V[i][j]+0.25*w*e[i][j];
                    }

                    else if (j==500){
                        e[i][j]=V[i+1][j]+V[i-1][j]+V[i][j]+V[i][j-1]-4*V[i][j];
                         V[i][j]=V[i][j]+0.25*w*e[i][j];
                    }

                    else if (i==0){
                        e[i][j]=V[i+1][j]+V[i][j]+V[i][j+1]+V[i][j-1]-4*V[i][j];
                        V[i][j]=V[i][j]+0.25*w*e[i][j];
                    }

                    else if (i==500){
                        e[i][j]=V[i][j]+V[i-1][j]+V[i][j+1]+V[i][j-1]-4*V[i][j];
                        V[i][j]=V[i][j]+0.25*w*e[i][j];
                    }

                    //evaluate all other points using normal finite difference scheme

                else {

                e[i][j]=V[i+1][j]+V[i-1][j]+V[i][j+1]+V[i][j-1]-4*V[i][j];  //calculation of residual
                V[i][j]=V[i][j]+0.25*w*e[i][j];  //evaluate using SOR

                }
            }
        }
    }

        //output of final data to a file for plotting

        ofstream file;
        file.open("draft3.dat");

        for (i=0; i<=500; i++){
            for (j=0; j<=500; j++){

                file << (i*d) << "      "<< (j*d) << "    " <<  V[i][j] << "\n";

            }
            file << "\n";
        }


        file.close();

*/


    return 0;
}
