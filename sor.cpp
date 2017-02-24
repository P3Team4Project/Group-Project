#include "main.h"
#include "renderarea.h"
#include "sor.h"

using namespace std;

void otps(int W, int H);
void otpse1(int W, int H);
void otpse2(int W, int H);


void sols(int W , int H, double ET)
{

   int maxit=100000, m=0;
    float  w=1.3;
    double e[1000][1000];


    for (int i=0; i<=W; i++){
            for (int j=0; j<=H; j++){

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

    for (m=0; m<=3; m++){
        for (int i=0; i<=W; i++){
            for (int j=0; j<=H; j++){

                //if a boundary has been set, do nothing a[i][j]==true

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


            }
        }


    }

    for (int i=0; i<=W; i++){
        for (int j=0; j<=H; j++){

            //  cout << V[i+1][j] << "    " << V[i-1][j] << endl;

            if (!a[i][j]){


                double Ex =  0.5*(V[i+1][j]-V[i-1][j]);
                double Ey =  0.5*(V[i][j+1]-V[i][j-1]);

                // cout << Ex << "   " << Ey << endl;


                Grad[i][j] = sqrt( pow(Ex, 2) + pow(Ey, 2));

                //cout << Grad[i][j] << endl;

            }
        }
    }




    // cout << Grad[500][500] << endl;
    //fix fix
    float maximum = 0;
    int k1 = 0;
    int k2 = 0;
    for (int i=0; i<=W; i++){
        for (int j=0; j<=H; j++){

            c[i][j]=false;

            if (Grad[i][j]>maximum) {
                maximum = Grad[i][j];
                k1 = i;
                k2 = j;
            }

        }
    }
    //assign space ij in Grad to b

    c[k1][k2] = true;
    /////////



        //evaluating all u apart from boundaries using SOR


while (m<=maxit){
            for (int i=0; i<=W; i++){
                for (int j=0; j<=H; j++){

                    //if a boundary has been set, do nothing a[i][j]==true

                    if ( !a[i][j] ){



                    //if  border condition hasn't been specified, make an approximation so that they aren't constantly zero

                     if (j==0){
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
                     if (c[i][j]){
                         compare[m]=abs(V[i][j]);
                     }

                    }

                }
            }

            if ((abs(compare[m-1]-compare[m]))<=ET) {

                   cout << "convergence after " << m << " iterations." << endl;
                   break;
               }

               if (m==maxit){

                   cout << "convergence not reached. " << endl;
               }


        m++;

        }

}

void SOR(double ET){



    QDesktopWidget dw;
        int W = (int)dw.width()*0.5;
        int H = (int)dw.height()*0.5;

    //input of variables from shell script

    clock_t t;
    t = clock();
    sols(W,H,ET);
    otps(W,H);
    t = clock() - t;

    cout << "CPU time=" << (float)t/(CLOCKS_PER_SEC) <<"s." << endl;



}


void otps(int W, int H){

    //output all the final V values for all x & y  to a file for plotting


    int i, j;

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
void SORE1(double ET){



    QDesktopWidget dw;
        int W = (int)dw.width()*0.5;
        int H = (int)dw.height()*0.5;

    //input of variables from shell script

    clock_t t;
    t = clock();
    sols(W,H, ET);
    otpse1(W,H);
    t = clock() - t;

    cout << "CPU time=" << (float)t/(CLOCKS_PER_SEC) <<"s." << endl;
}

void otpse1(int W, int H){
    ofstream file;
    file.open("draft3.dat");




    for (int i=0; i<=W; i++){
        for (int j=0; j<=H; j++){

            if ( pow((i-(W/2)),2)+pow((j-(H/2)),2) <= pow(100,2) ){  //cycle through and evaluate boundaries

                            file << (i) << "      "<< (H-j) << "    " <<  0 << "\n";


                        }
            else if ( pow((i-(W/2)),2)+pow((j-(H/2)),2) >= pow(200,2) ){  //cycle through and evaluate boundaries

                            file << (i) << "      "<< (H-j) << "    " <<  0 << "\n";


                        }

            else{

            file << (i) << "      "<< (H-j) << "    " << abs(V[i][j] -((10/log(200/100))*(log(sqrt(pow((i-(W/2)),2)+pow((j-(H/2)),2)))-log(100)))) << "\n";

            }
        }
        file << "\n";
    }


    file.close();

}

void SORE2(double ET){



    QDesktopWidget dw;
        int W = (int)dw.width()*0.5;
        int H = (int)dw.height()*0.5;


    //input of variables from shell script

    clock_t t;
    t = clock();
    sols(W,H, ET);
    otpse2(W,H);
    t = clock() - t;

    cout << "CPU time=" << (float)t/(CLOCKS_PER_SEC) <<"s." << endl;
}

void otpse2(int W, int H){
    ofstream file;
    file.open("draft3.dat");



    for (int i=0; i<=W; i++){
        for (int j=0; j<=H; j++){



            double v=(-0.02*(i-(W/2))*(1-pow((10/sqrt(pow((i-(W/2)),2)+pow((j-(H/2)),2))),3)));

            if ( pow((i-(W/2)),2)+pow((j-(H/2)),2) <= pow(100,2) ){  //cycle through and evaluate boundaries

                            file << (i) << "      "<< (H-j) << "    " <<  0 << "\n";


                        }

            else{

            file << (i) << "      "<< (H-j) << "    " <<  abs(V[i][j]-v) << "\n";

            }

        }
        file << "\n";
    }


    file.close();

}


