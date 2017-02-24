#include "main.h"
#include "jac.h"
#include "renderarea.h"

using namespace std;

/*script for running the jacobi method, fairly self explanatory */
void otpj(int W, int H);
void otpje1(int W, int H);
void otpje2(int W, int H);

void solj(int W, int H, double ET){

    int x=0,y=0,m=0, m_it=100000;



    //max number of iterations, this will not be needed when it has been cut out at convergence


    for (x=0;x<=W;x++){
        for (y=0;y<=H;y++){

            if ( !a[x][y]){
                V[x][y]=0;
            }


        }
    }

    for (m=0;m<=3;m++){
        for (x=0;x<=W;x++){
            for (y=0;y<=H;y++){

                if (!a[x][y]){

                    if ( x==0 ){

                        V1[x][y]=0.25*(V[x+1][y]+V[x][y]+V[x][y+1]+V[x][y-1]);

                    }

                    else if (x==W){

                        V1[x][y]=0.25*(V[x][y]+V[x-1][y]+V[x][y+1]+V[x][y-1]);

                    }

                    else if (y==0){

                        V1[x][y]=0.25*(V[x+1][y]+V[x-1][y]+V[x][y+1]+V[x][y]);

                    }


                    else if (y==H){

                        V1[x][y]=0.25*(V[x+1][y]+V[x-1][y]+V[x][y]+V[x][y-1]);

                    }


                    else {

                        V1[x][y]=0.25*(V[x+1][y]+V[x-1][y]+V[x][y+1]+V[x][y-1]);

                    }


                }


            }
        }

        for (x=0;x<=W;x++){
            for (y=0;y<=H;y++){
                if (!a[x][y]){
                V[x][y]=V1[x][y];
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


                Grad6[i][j] = sqrt( pow(Ex, 2) + pow(Ey, 2));

                //cout << Grad6[i][j] << endl;

            }
        }
    }




    // cout << Grad6[500][500] << endl;
    //fix fix
    float maximum = 0;
    int k1 = 0;
    int k2 = 0;
    for (int i=0; i<=W; i++){
        for (int j=0; j<=H; j++){

            c6[i][j]=false;

            if (Grad6[i][j]>maximum) {
                maximum = Grad6[i][j];
                k1 = i;
                k2 = j;
            }

        }
    }
    //assign space ij in Grad4 to b

    c6[k1][k2] = true;



    //evaluate every other x & y value apart from the boundary conditions at all times after 0
while(m<=m_it){
        for (x=0;x<=W;x++){
            for (y=0;y<=H;y++){

                if (!a[x][y]){

                    if ( x==0 ){

                        V1[x][y]=0.25*(V[x+1][y]+V[x][y]+V[x][y+1]+V[x][y-1]);

                    }

                    else if (x==W){

                        V1[x][y]=0.25*(V[x][y]+V[x-1][y]+V[x][y+1]+V[x][y-1]);

                    }

                    else if (y==0){

                        V1[x][y]=0.25*(V[x+1][y]+V[x-1][y]+V[x][y+1]+V[x][y]);

                    }


                    else if (y==H){

                        V1[x][y]=0.25*(V[x+1][y]+V[x-1][y]+V[x][y]+V[x][y-1]);

                    }


                    else {

                        V1[x][y]=0.25*(V[x+1][y]+V[x-1][y]+V[x][y+1]+V[x][y-1]);

                    }




                }


            }
        }



        for (x=0;x<=W;x++){
            for (y=0;y<=H;y++){
                if (!a[x][y]){
                V[x][y]=V1[x][y];




                if (c6[x][y]){
                    compare6[m]=abs(V[x][y]);
                }







                }
            }
        }


        if ((abs(compare6[m-1]-compare6[m]))<=ET) {

               cout << "convergence after " << m << " iterations." << endl;
               break;
           }

           if (m==m_it){

               cout << "convergence not reached. " << endl;
           }




        m++;

    }

    //output all the final V values for all x & y  to a file for plotting

}



void jac(double ET){

    QDesktopWidget dw;
        int W = (int)dw.width()*0.5;
        int H = (int)dw.height()*0.5;

    //input of variables from shell script

    clock_t t;
    t = clock();

    solj(W,H,ET);
    otpj(W,H);

    t = clock() - t;

    cout << "CPU time=" << (float)t/(CLOCKS_PER_SEC) <<"s." << endl;


}

void otpj(int W, int H){

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
void jace1(double ET){



    QDesktopWidget dw;
        int W = (int)dw.width()*0.5;
        int H = (int)dw.height()*0.5;

    //input of variables from shell script

    clock_t t;
    t = clock();
    solj(W,H, ET);
    otpje1(W,H);
    t = clock() - t;

    cout << "CPU time=" << (float)t/(CLOCKS_PER_SEC) <<"s." << endl;
}

void otpje1(int W, int H){
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

void jace2(double ET){



    QDesktopWidget dw;
        int W = (int)dw.width()*0.5;
        int H = (int)dw.height()*0.5;


    //input of variables from shell script

    clock_t t;
    t = clock();
    solj(W,H, ET);
    otpje2(W,H);
    t = clock() - t;

    cout << "CPU time=" << (float)t/(CLOCKS_PER_SEC) <<"s." << endl;
}

void otpje2(int W, int H){
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


