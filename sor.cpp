#include "main.h"
#include "renderarea.h"
#include "sor.h"

using namespace std;

void otps(double gridmax, double d);
void otpse1(double gridmax, double d);
void otpse2(double gridmax, double d);

void sols(double gridmax , double d)
{

   int maxit=500, m=0;
    float  w=1.3 , jmax=gridmax/d;
    double e[1000][1000];


    for (int i=0; i<=jmax; i++){
            for (int j=0; j<=jmax; j++){

    /*this applies an initial value of zero to all points that haven't been set by the user, i.e values where a[i][j] is false.
      you can set potentials at the boundaries if you wish by including if statements that check whether we're at a boundary, and applying potentials accordingly */

                if (!a[i][j]){

                        V[i][j]=0;

                }
                else{
                    //cout<<"i j V "<<i<<" "<<j<<" "<<V[i][j]<<endl;
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

}

void SOR(){

    double gridmax=50, d=0.1;


    //input of variables from shell script

    clock_t t;
    t = clock();
    sols(gridmax,d);
    otps(gridmax,d);
    t = clock() - t;

    cout << "CPU time=" << (float)t/(CLOCKS_PER_SEC) <<"s." << endl;
}

void otps(double gridmax, double d){
    ofstream file;
    file.open("draft3.dat");

    double jmax=gridmax/d;

    for (int i=0; i<=jmax; i++){
        for (int j=0; j<=jmax; j++){

            file << (i*d) << "      "<< (j*d) << "    " <<  V[i][j] << "\n";

        }
        file << "\n";
    }


    file.close();

}
void SORE1(){

    double gridmax=50, d=0.1;



    //input of variables from shell script

    clock_t t;
    t = clock();
    sols(gridmax,d);
    otpse1(gridmax,d);
    t = clock() - t;

    cout << "CPU time=" << (float)t/(CLOCKS_PER_SEC) <<"s." << endl;
}

void otpse1(double gridmax, double d){
    ofstream file;
    file.open("draft3.dat");

    double jmax=gridmax/d;

    for (int i=0; i<=jmax; i++){
        for (int j=0; j<=jmax; j++){

            if ( pow((i*d-25),2)+pow((j*d-25),2) <= pow(10,2) ){  //cycle through and evaluate boundaries

                            file << (i*d) << "      "<< (j*d) << "    " <<  0 << "\n";


                        }
            else{

            file << (i*d) << "      "<< (j*d) << "    " <<  abs(V[i][j] -((10/log(20/10))*(log(sqrt(pow((i*d-25),2)+pow((j*d-25),2)))-log(10)))) << "\n";

            }
        }
        file << "\n";
    }


    file.close();

}

void SORE2(){

    double gridmax=50, d=0.1;


    //input of variables from shell script

    clock_t t;
    t = clock();
    sols(gridmax,d);
    otpse2(gridmax,d);
    t = clock() - t;

    cout << "CPU time=" << (float)t/(CLOCKS_PER_SEC) <<"s." << endl;
}

void otpse2(double gridmax, double d){
    ofstream file;
    file.open("draft3.dat");

    double jmax=gridmax/d;

    for (int i=0; i<=jmax; i++){
        for (int j=0; j<=jmax; j++){

            double v=(-0.40*(i*d-25)*(1-pow((10/sqrt(pow((i*d-25),2)+pow((j*d-25),2))),3)));

            if ( pow((i*d-25),2)+pow((j*d-25),2) <= pow(10,2) ){  //cycle through and evaluate boundaries

                            file << (i*d) << "      "<< (j*d) << "    " <<  0 << "\n";


                        }

            else{

            file << (i*d) << "      "<< (j*d) << "    " <<  abs(V[i][j] -v) << "\n";
            }

        }
        file << "\n";
    }


    file.close();

}


