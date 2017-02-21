#include "renderarea.h"
#include "main.h"
#include "ttgrid.h"

using namespace std;

double Dt[1000][1000], D2[1000][1000],D3[1000][1000],D4[1000][1000], vt[1000][1000], v2[1000][1000],v3[1000][1000],v4[1000][1000];
void otptt(double gridmax, double d);
void otptte1(double gridmax, double d);
void otptte2(double gridmax, double d);

void soltt(double gridmax, double d){

    int x=0,y=0,m=0,l=0, h=gridmax/d, max_it=100;

    for (x=0;x<=h;x++){
        for (y=0;y<=h;y++){


            if (!a[x][y]){

                    V[x][y]=0;

            }


            v3[x][y]=0;
            v4[x][y]=0;
            v2[x][y]=0;
            vt[x][y]=0;  //initialise everything else to zero
            Dt[x][y]=0;
            D2[x][y]=0;
            D3[x][y]=0;
            D4[x][y]=0;


        }
    }


    //initial smoothing using gauss-siedel

    for (m=0; m<=3; m++){
        for (x=0;x<=h;x++){
            for (y=0;y<=h;y++){

                if (!a[x][y]){

                    if ( x==0 ){  //approximations at unset boundaries

                        V[x][y]=0.25*(V[x+1][y]+V[x][y]+V[x][y+1]+V[x][y-1]);

                    }

                    else if (x==h){

                        V[x][y]=0.25*(V[x][y]+V[x-1][y]+V[x][y+1]+V[x][y-1]);

                    }

                    else if (y==0){

                        V[x][y]=0.25*(V[x+1][y]+V[x-1][y]+V[x][y+1]+V[x][y]);

                    }


                    else if (y==h){

                        V[x][y]=0.25*(V[x+1][y]+V[x-1][y]+V[x][y]+V[x][y-1]);

                    }


                    else {

                        V[x][y]=0.25*(V[x+1][y]+V[x-1][y]+V[x][y+1]+V[x][y-1]);

                    }

                }

            }
        }
    }

    while (l<=max_it ){

        cout << l << endl;

        for (x=0;x<=h;x++){
            for (y=0;y<=h;y++){

                if (!a[x][y]){  //find defect on fine grid

                    if ( x==0 ){

                        Dt[x][y]=(1/(pow(d,2)))*(V[x][y+1]+V[x][y]-4*V[x][y]+V[x+1][y]+V[x][y-1]);

                    }

                    else if (x==h){

                        Dt[x][y]=(1/(pow(d,2)))*(V[x][y+1]+V[x-1][y]-4*V[x][y]+V[x][y]+V[x][y-1]);

                    }

                    else if (y==0){

                        Dt[x][y]=(1/(pow(d,2)))*(V[x][y+1]+V[x-1][y]-4*V[x][y]+V[x+1][y]+V[x][y]);

                    }


                    else if (y==h){

                        Dt[x][y]=(1/(pow(d,2)))*(V[x][y]+V[x-1][y]-4*V[x][y]+V[x+1][y]+V[x][y-1]);

                    }


                    else {

                        Dt[x][y]=(1/(pow(d,2)))*(V[x][y+1]+V[x-1][y]-4*V[x][y]+V[x+1][y]+V[x][y-1]);

                    }

                }

                v2[x][y]=0;
                v3[x][y]=0;
                v4[x][y]=0;

            }
        }


        for (x=0;x<=h/2;x++){
            for (y=0;y<=h/2;y++){  //convert defect onto course grid

                if (!a[2*x][2*y]){

                    D2[x][y]=Dt[2*x][2*y];

                }

            }
        }

        for (m=0; m<=3;m++){
            for (x=0;x<=h/2;x++){
                for (y=0;y<=h/2;y++){  //calculate correction on course grid

                    if (!a[2*x][2*y]){

                        if ( x==0 ){

                            v2[x][y]=0.25*((D2[x][y]*(pow(2*d,2)))+v2[x][y+1]+v2[x][y]+v2[x+1][y]+v2[x][y-1]);

                        }

                        else if (x==h/2){

                            v2[x][y]=0.25*((D2[x][y]*(pow(2*d,2)))+v2[x][y+1]+v2[x-1][y]+v2[x][y]+v2[x][y-1]);

                        }

                        else if (y==0){

                            v2[x][y]=0.25*((D2[x][y]*(pow(2*d,2)))+v2[x][y+1]+v2[x-1][y]+v2[x+1][y]+v2[x][y]);

                        }

                        else if (y==h/2){

                            v2[x][y]=0.25*((D2[x][y]*(pow(2*d,2)))+v2[x][y]+v2[x-1][y]+v2[x+1][y]+v2[x][y-1]);

                        }

                        else {

                            v2[x][y]=0.25*((D2[x][y]*(pow(2*d,2)))+v2[x][y+1]+v2[x-1][y]+v2[x+1][y]+v2[x][y-1]);

                        }

                    }

                }
            }
        }

        for (x=0;x<=h/2;x++){
            for (y=0;y<=h/2;y++){  //calculate defect from correction calculation

                if (!a[2*x][2*y]){

                    if ( x==0 ){

                        D3[x][y]=D2[x][y]+(1/(pow(2*d,2)))*(v2[x][y+1]+v2[x][y]+v2[x+1][y]+v2[x][y-1]-4*v2[x][y]);

                    }

                    else if (x==h/2){

                       D3[x][y]=D2[x][y]+(1/(pow(2*d,2)))*(v2[x][y+1]+v2[x-1][y]+v2[x][y]+v2[x][y-1]-4*v2[x][y]);

                    }

                    else if (y==0){

                        D3[x][y]=D2[x][y]+(1/(pow(2*d,2)))*(v2[x][y+1]+v2[x-1][y]+v2[x+1][y]+v2[x][y]-4*v2[x][y]);

                    }

                    else if (y==h/2){

                      D3[x][y]=D2[x][y]+(1/(pow(2*d,2)))*(v2[x][y]+v2[x-1][y]+v2[x+1][y]+v2[x][y-1]-4*v2[x][y]);

                    }

                    else {

                        D3[x][y]=D2[x][y]+(1/(pow(2*d,2)))*(v2[x][y+1]+v2[x-1][y]+v2[x+1][y]+v2[x][y-1]-4*v2[x][y]);

                    }

                }

            }
        }


        for (x=0;x<=h/4;x++){
            for (y=0;y<=h/4;y++){  //convert D3 onto courser grid

                if (!a[4*x][4*y]){

                    D4[x][y]=D3[2*x][2*y];

                }

            }
        }

        for (m=0; m<=5;m++){
            for (x=0;x<=h/4;x++){
                for (y=0;y<=h/4;y++){  //find correction in the correction on the coursest grid using gauss siedel

                    if (!a[4*x][4*y]){

                        if ( x==0 ){

                            v3[x][y]=0.25*((D4[x][y]*(pow(4*d,2)))+v3[x][y+1]+v3[x][y]+v3[x+1][y]+v3[x][y-1]);

                        }

                        else if (x==h/4){

                            v3[x][y]=0.25*((D4[x][y]*(pow(4*d,2)))+v3[x][y+1]+v3[x-1][y]+v3[x][y]+v3[x][y-1]);

                        }

                        else if (y==0){

                            v3[x][y]=0.25*((D4[x][y]*(pow(4*d,2)))+v3[x][y+1]+v2[x-1][y]+v3[x+1][y]+v3[x][y]);

                        }

                        else if (y==h/4){

                            v3[x][y]=0.25*((D4[x][y]*(pow(4*d,2)))+v3[x][y]+v3[x-1][y]+v3[x+1][y]+v3[x][y-1]);

                        }

                        else {

                            v3[x][y]=0.25*((D4[x][y]*(pow(4*d,2)))+v3[x][y+1]+v3[x-1][y]+v3[x+1][y]+v3[x][y-1]);

                        }

                    }

                }
            }
        }


        for (x=0;x<=h/4;x++){
            for (y=0;y<=h/4;y++){                   //interpolate correction onto 2h grid, matching values

                if (!a[4*x][4*y]){

                    v4[2*x][2*y]=v3[x][y];

                }
            }
        }


        for (x=0;x<=h/2;x+=2){
            for (y=1;y<=h/2;y+=2){
                                     //interpolate correction onto 2h grid, even columns

                if (!a[2*x][2*y]){

                    if (y==h/2){

                        v4[x][y]=v4[x][y-1];
                    }

                    else {

                        v4[x][y]=0.5*(v4[x][y+1]+v4[x][y-1]);

                    }
                }

            }
        }


        for (x=1;x<=h/2;x+=2){
            for (y=0;y<=h/2;y++){//interpolate correction onto 2h grid, odd columns


                if (!a[2*x][2*y]){


                    if (x==h/2){

                        v4[x][y]=v4[x-1][y];

                    }


                    else {

                        v4[x][y]=0.5*(v4[x+1][y]+v4[x-1][y]);

                    }

                }

            }
        }

        for (x=0;x<=h/2;x++){
            for (y=0;y<=h/2;y++){  //correcting the correction
                if (!a[2*x][2*y]){

                    v2[x][y]=v4[x][y]+v2[x][y];

                }

            }

        }

        for (m=0; m<=3;m++){
            for (x=0;x<=h/2;x++){
                for (y=0;y<=h/2;y++){  //smoothing the correction on the 2h grid

                    if (!a[2*x][2*y]){

                        if ( x==0 ){

                            v2[x][y]=0.25*((D2[x][y]*(pow(2*d,2)))+v2[x][y+1]+v2[x][y]+v2[x+1][y]+v2[x][y-1]);

                        }

                        else if (x==h/2){

                            v2[x][y]=0.25*((D2[x][y]*(pow(2*d,2)))+v2[x][y+1]+v2[x-1][y]+v2[x][y]+v2[x][y-1]);

                        }

                        else if (y==0){

                            v2[x][y]=0.25*((D2[x][y]*(pow(2*d,2)))+v2[x][y+1]+v2[x-1][y]+v2[x+1][y]+v2[x][y]);

                        }

                        else if (y==h/2){

                            v2[x][y]=0.25*((D2[x][y]*(pow(2*d,2)))+v2[x][y]+v2[x-1][y]+v2[x+1][y]+v2[x][y-1]);

                        }

                        else {

                            v2[x][y]=0.25*((D2[x][y]*(pow(2*d,2)))+v2[x][y+1]+v2[x-1][y]+v2[x+1][y]+v2[x][y-1]);

                        }

                    }

                }
            }
        }

        for (x=0;x<=h/2;x++){
            for (y=0;y<=h/2;y++){                   //interpolate correction onto fine grid, matching values

                if (!a[2*x][2*y]){

                    vt[2*x][2*y]=v2[x][y];

                }
            }
        }


        for (x=0;x<=h;x+=2){
            for (y=1;y<=h;y+=2){
                //interpolate correction onto fine grid, even columns

                if (!a[x][y]){

                    if (y==h){

                        vt[x][y]=vt[x][y-1];
                    }

                    else {

                        vt[x][y]=0.5*(vt[x][y+1]+vt[x][y-1]);

                    }
                }

            }
        }

        for (x=1;x<=h;x+=2){
            for (y=0;y<=h;y++){//interpolate correction onto fine grid, odd columns


                if (!a[x][y]){


                    if (x==h){

                        vt[x][y]=vt[x-1][y];

                    }


                    else {

                        vt[x][y]=0.5*(vt[x+1][y]+vt[x-1][y]);

                    }

                }

            }
        }


        for (x=0;x<=h;x++){
            for (y=0;y<=h;y++){  //calculate final V values
                if (!a[x][y]){

                    V[x][y]=V[x][y]+vt[x][y];

                }

            }

        }

        //final smoothing using gauss-siedel


        for (m=0; m<=5; m++){
            for (x=0;x<=h;x++){
                for (y=0;y<=h;y++){

                    if (!a[x][y]){

                        if ( x==0 ){  //approximations at unset boundaries

                            V[x][y]=0.25*(V[x+1][y]+V[x][y]+V[x][y+1]+V[x][y-1]);

                        }

                        else if (x==h){

                            V[x][y]=0.25*(V[x][y]+V[x-1][y]+V[x][y+1]+V[x][y-1]);

                        }

                        else if (y==0){

                            V[x][y]=0.25*(V[x+1][y]+V[x-1][y]+V[x][y+1]+V[x][y]);

                        }


                        else if (y==h){

                            V[x][y]=0.25*(V[x+1][y]+V[x-1][y]+V[x][y]+V[x][y-1]);

                        }


                        else {

                            V[x][y]=0.25*(V[x+1][y]+V[x-1][y]+V[x][y+1]+V[x][y-1]);

                        }
                    }

                }
            }
        }

        l++;
    }


}

void ttgr(){

    double gridmax=50, d=0.01;


    //input of variables from shell script

    clock_t t;
    t = clock();
    soltt(gridmax,d);
    otptt(gridmax,d);
    t = clock() - t;

    cout << "CPU time=" << (float)t/(CLOCKS_PER_SEC) <<"s." << endl;



}
void otptt(double gridmax, double d){
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

void ttgre1(){

    double gridmax=50, d=0.1;



    //input of variables from shell script

    clock_t t;
    t = clock();
    soltt(gridmax,d);
    otptte1(gridmax,d);
    t = clock() - t;

    cout << "CPU time=" << (float)t/(CLOCKS_PER_SEC) <<"s." << endl;
}

void otptte1(double gridmax, double d){
    ofstream file;
    file.open("draft3.dat");

    double jmax=gridmax/d;

    for (int i=0; i<=jmax; i++){
        for (int j=0; j<=jmax; j++){

            if ( pow((i*d-25),2)+pow((j*d-25),2) <= pow(10,2) ){  //cycle through and evaluate boundaries

                            file << (i*d) << "      "<< (j*d) << "    " <<  0 << "\n";


                        }
            else{

            file << (i*d) << "      "<< (j*d) << "    " <<  abs(V[i][j] -((10/log(20/10))*(log(sqrt(pow((i*d-25),2)+pow((j*d-25),2)))-log(10))))<< "\n";

            }
        }
        file << "\n";
    }


    file.close();

}

void ttgre2(){

    double gridmax=50, d=0.1;


    //input of variables from shell script

    clock_t t;
    t = clock();
    soltt(gridmax,d);
    otptte2(gridmax,d);
    t = clock() - t;

    cout << "CPU time=" << (float)t/(CLOCKS_PER_SEC) <<"s." << endl;
}

void otptte2(double gridmax, double d){
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

