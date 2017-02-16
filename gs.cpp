#include "main.h"
#include "renderarea.h"


using namespace std;

/*script for running the gauss-siedel method, fairly self explanatory */

void soln(double gridmax, double d){

    int x=0,y=0,m=0,it=0, m_it=0;

    it=gridmax/d;

    //max number of iterations, this will not be needed when it has been cut out at convergence

    m_it=10000;


    for (x=0; x<=it; x++){
            for (y=0; y<=it; y++){

    /*this applies an initial value of zero to all points that haven't been set by the user, i.e values where a[i][j] is false.
      you can set potentials at the boundaries if you wish by including if statements that check whether we're at a boundary, and applying potentials accordingly */

                if (!a[x][y]){



                        V[x][y]=0;




                }

            }
        }

    //evaluate every other x & y value apart from the boundary conditions at all times after 0

    for (m=0;m<=m_it;m++){
        for (x=0;x<=it;x++){
            for (y=0;y<=it;y++){

                if (!a[x][y]){

                if ( x==0 ){

                     V[x][y]=0.25*(V[x+1][y]+V[x][y]+V[x][y+1]+V[x][y-1]);

                }

                else if (x==it){

                    V[x][y]=0.25*(V[x][y]+V[x-1][y]+V[x][y+1]+V[x][y-1]);

                }

                else if (y==0){

                    V[x][y]=0.25*(V[x+1][y]+V[x-1][y]+V[x][y+1]+V[x][y]);

                    }


                else if (y==it){

                    V[x][y]=0.25*(V[x+1][y]+V[x-1][y]+V[x][y]+V[x][y-1]);

                }


                else {

                    V[x][y]=0.25*(V[x+1][y]+V[x-1][y]+V[x][y+1]+V[x][y-1]);

                }

                }
            }
        }
    }

    //output all the final V values for all x & y  to a file for plotting


    ofstream file;
    file.open("draft3.dat");

    for (x=0; x<=it; x++){
        for (y=0; y<=it; y++){

            file << (x*d) << "      "<< (y*d) << "    " <<  V[x][y] << "\n";

        }
        file << "\n";
    }


    file.close();

}



void gs(){

    double gridmax=50, d=0.1;



    //input of variables from shell script

    clock_t t;
    t = clock();

    soln(gridmax,d);

    t = clock() - t;

    cout << "CPU time=" << (float)t/(CLOCKS_PER_SEC) <<"s." << endl;


}
