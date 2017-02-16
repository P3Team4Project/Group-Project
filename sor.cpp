#include "main.h"
#include "renderarea.h"
#include "sor.h"

using namespace std;

void SOR()
{

   int maxit=500, m=0;
    float e[500][500], w=1.3 , d=0.1, jmax=500;


    for (int i=0; i<=jmax; i++){
            for (int j=0; j<=jmax; j++){

    /*this applies an initial value of zero to all points that haven't been set by the user, i.e values where a[i][j] is false.
      you can set potentials at the boundaries if you wish by including if statements that check whether we're at a boundary, and applying potentials accordingly */

                if (!a[i][j]){



                        V[i][j]=0;




                }

            }
        }

        //evaluating all u apart from boundaries using SOR



        for (m=0; m<=maxit; m++){
            for (int i=0; i<=jmax; i++){
                for (int j=0; j<=jmax; j++){

                    //if a boundary has been set, do nothing a[i][j]==true

                    if ( a[i][j] ){

                    }

                    //if  border condition hasn't been specified, make an approximation so that they aren't constantly zero

                    else if (j==0){
                        e[i][j]=V[i+1][j]+V[i-1][j]+V[i][j+1]+V[i][j]-4*V[i][j];
                         V[i][j]=V[i][j]+0.25*w*e[i][j];
                    }

                    else if (j==jmax){
                        e[i][j]=V[i+1][j]+V[i-1][j]+V[i][j]+V[i][j-1]-4*V[i][j];
                         V[i][j]=V[i][j]+0.25*w*e[i][j];
                    }

                    else if (i==0){
                        e[i][j]=V[i+1][j]+V[i][j]+V[i][j+1]+V[i][j-1]-4*V[i][j];
                        V[i][j]=V[i][j]+0.25*w*e[i][j];
                    }

                    else if (i==jmax){
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

        for (int i=0; i<=jmax; i++){
            for (int j=0; j<=jmax; j++){

                file << (i*d) << "      "<< (j*d) << "    " <<  V[i][j] << "\n";

            }
            file << "\n";
        }


        file.close();
}
