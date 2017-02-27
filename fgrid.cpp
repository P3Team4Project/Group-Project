#include "renderarea.h"
#include "main.h"
#include "fgrid.h"


using namespace std;



void otpf(int myxgrid, int myygrid);
void otpfe1(int myxgrid, int myygrid);
void otpfe2(int myxgrid, int myygrid);

void solf(int myxgrid,int myygrid){

    int x=0,y=0,m=0,l=0, max_it=100,d=1;

    for (x=0;x<=myxgrid;x++){
        for (y=0;y<=myygrid;y++){


            if (!a[x][y]){

                    V[x][y]=0;

            }



            vf2[x][y]=0;
            vf[x][y]=0;  //initialise everything else to zero
            Df[x][y]=0;
            Df2[x][y]=0;


        }
    }

    //initial smoothing using gauss-siedel

    for (m=0; m<=3; m++){
        for (x=0;x<=myxgrid;x++){
            for (y=0;y<=myygrid;y++){

                if (!a[x][y]){

                    if ( x==0 ){  //approximations at unset boundaries

                        V[x][y]=0.25*(V[x+1][y]+V[x][y]+V[x][y+1]+V[x][y-1]);

                    }

                    else if (x==myxgrid){

                        V[x][y]=0.25*(V[x][y]+V[x-1][y]+V[x][y+1]+V[x][y-1]);

                    }

                    else if (y==0){

                        V[x][y]=0.25*(V[x+1][y]+V[x-1][y]+V[x][y+1]+V[x][y]);

                    }


                    else if (y==myygrid){

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



        for (x=0;x<=myxgrid;x++){
            for (y=0;y<=myygrid;y++){

                if (!a[x][y]){  //find defect on fine grid

                    if ( x==0 ){

                        Df[x][y]=(1/(pow(d,2)))*(V[x][y+1]+V[x][y]-4*V[x][y]+V[x+1][y]+V[x][y-1]);

                    }

                    else if (x==myxgrid){

                        Df[x][y]=(1/(pow(d,2)))*(V[x][y+1]+V[x-1][y]-4*V[x][y]+V[x][y]+V[x][y-1]);

                    }

                    else if (y==0){

                        Df[x][y]=(1/(pow(d,2)))*(V[x][y+1]+V[x-1][y]-4*V[x][y]+V[x+1][y]+V[x][y]);

                    }


                    else if (y==myygrid){

                        Df[x][y]=(1/(pow(d,2)))*(V[x][y]+V[x-1][y]-4*V[x][y]+V[x+1][y]+V[x][y-1]);

                    }


                    else {

                        Df[x][y]=(1/(pow(d,2)))*(V[x][y+1]+V[x-1][y]-4*V[x][y]+V[x+1][y]+V[x][y-1]);

                    }

                }

                vf2[x][y]=0;
                vf3[x][y]=0;
                vf4[x][y]=0;  //initialise corrections to zero at the start of each loop
                vf5[x][y]=0;
                vf6[x][y]=0;

            }
        }


        for (x=0;x<=myxgrid/2;x++){
            for (y=0;y<=myygrid/2;y++){  //convert defect onto course grid

                if (!a[2*x][2*y]){

                    Df2[x][y]=Df[2*x][2*y];

                }

            }
        }

        for (m=0; m<=3;m++){
            for (x=0;x<=myxgrid/2;x++){
                for (y=0;y<=myygrid/2;y++){  //calculate correction on course grid

                    if (!a[2*x][2*y]){

                        if ( x==0 ){

                            vf2[x][y]=0.25*((Df2[x][y]*(pow(2*d,2)))+vf2[x][y+1]+vf2[x][y]+vf2[x+1][y]+vf2[x][y-1]);

                        }

                        else if (x==myxgrid/2){

                            vf2[x][y]=0.25*((Df2[x][y]*(pow(2*d,2)))+vf2[x][y+1]+vf2[x-1][y]+vf2[x][y]+vf2[x][y-1]);

                        }

                        else if (y==0){

                            vf2[x][y]=0.25*((Df2[x][y]*(pow(2*d,2)))+vf2[x][y+1]+vf2[x-1][y]+vf2[x+1][y]+vf2[x][y]);

                        }

                        else if (y==myygrid/2){

                            vf2[x][y]=0.25*((Df2[x][y]*(pow(2*d,2)))+vf2[x][y]+vf2[x-1][y]+vf2[x+1][y]+vf2[x][y-1]);

                        }

                        else {

                            vf2[x][y]=0.25*((Df2[x][y]*(pow(2*d,2)))+vf2[x][y+1]+vf2[x-1][y]+vf2[x+1][y]+vf2[x][y-1]);

                        }

                    }

                }
            }
        }

        for (x=0;x<=myxgrid/2;x++){
            for (y=0;y<=myygrid/2;y++){  //calculate defect from correction calculation

                if (!a[2*x][2*y]){

                    if ( x==0 ){

                        Df3[x][y]=Df2[x][y]+(1/(pow(2*d,2)))*(vf2[x][y+1]+vf2[x][y]+vf2[x+1][y]+vf2[x][y-1]-4*vf2[x][y]);

                    }

                    else if (x==myxgrid/2){

                        Df3[x][y]=Df2[x][y]+(1/(pow(2*d,2)))*(vf2[x][y+1]+vf2[x-1][y]+vf2[x][y]+vf2[x][y-1]-4*vf2[x][y]);

                    }

                    else if (y==0){

                        Df3[x][y]=Df2[x][y]+(1/(pow(2*d,2)))*(vf2[x][y+1]+vf2[x-1][y]+vf2[x+1][y]+vf2[x][y]-4*vf2[x][y]);

                    }

                    else if (y==myygrid/2){

                        Df3[x][y]=Df2[x][y]+(1/(pow(2*d,2)))*(vf2[x][y]+vf2[x-1][y]+vf2[x+1][y]+vf2[x][y-1]-4*vf2[x][y]);

                    }

                    else {

                        Df3[x][y]=Df2[x][y]+(1/(pow(2*d,2)))*(vf2[x][y+1]+vf2[x-1][y]+vf2[x+1][y]+vf2[x][y-1]-4*vf2[x][y]);

                    }

                }

            }
        }


        for (x=0;x<=myxgrid/4;x++){
            for (y=0;y<=myygrid/4;y++){  //convert D3 onto courser grid

                if (!a[4*x][4*y]){

                    Df4[x][y]=Df3[2*x][2*y];

                }

            }
        }

        for (m=0; m<=5;m++){
            for (x=0;x<=myxgrid/4;x++){
                for (y=0;y<=myygrid/4;y++){  //find correction in the correction on the 4*d grid using gauss siedel

                    if (!a[4*x][4*y]){

                        if ( x==0 ){

                            vf3[x][y]=0.25*((Df4[x][y]*(pow(4*d,2)))+vf3[x][y+1]+vf3[x][y]+vf3[x+1][y]+vf3[x][y-1]);

                        }

                        else if (x==myxgrid/4){

                            vf3[x][y]=0.25*((Df4[x][y]*(pow(4*d,2)))+vf3[x][y+1]+vf3[x-1][y]+vf3[x][y]+vf3[x][y-1]);

                        }

                        else if (y==0){

                            vf3[x][y]=0.25*((Df4[x][y]*(pow(4*d,2)))+vf3[x][y+1]+vf2[x-1][y]+vf3[x+1][y]+vf3[x][y]);

                        }

                        else if (y==myygrid/4){

                            vf3[x][y]=0.25*((Df4[x][y]*(pow(4*d,2)))+vf3[x][y]+vf3[x-1][y]+vf3[x+1][y]+vf3[x][y-1]);

                        }

                        else {

                            vf3[x][y]=0.25*((Df4[x][y]*(pow(4*d,2)))+vf3[x][y+1]+vf3[x-1][y]+vf3[x+1][y]+vf3[x][y-1]);

                        }

                    }

                }
            }
        }

        for (x=0;x<=myxgrid/4;x++){
            for (y=0;y<=myygrid/4;y++){  //calculate defect from correction of correction calculation

                if (!a[4*x][4*y]){

                    if ( x==0 ){

                        Df5[x][y]=Df4[x][y]+(1/(pow(4*d,2)))*(vf3[x][y+1]+vf3[x][y]+vf3[x+1][y]+vf3[x][y-1]-4*vf3[x][y]);

                    }

                    else if (x==myxgrid/4){

                        Df5[x][y]=Df4[x][y]+(1/(pow(4*d,2)))*(vf3[x][y+1]+vf3[x-1][y]+vf3[x][y]+vf3[x][y-1]-4*vf3[x][y]);

                    }

                    else if (y==0){

                        Df5[x][y]=Df4[x][y]+(1/(pow(4*d,2)))*(vf3[x][y+1]+vf3[x-1][y]+vf3[x+1][y]+vf3[x][y]-4*vf3[x][y]);

                    }

                    else if (y==myygrid/4){

                        Df5[x][y]=Df4[x][y]+(1/(pow(4*d,2)))*(vf3[x][y]+vf3[x-1][y]+vf3[x+1][y]+vf3[x][y-1]-4*vf3[x][y]);

                    }

                    else {

                        Df5[x][y]=Df4[x][y]+(1/(pow(4*d,2)))*(vf3[x][y+1]+vf3[x-1][y]+vf3[x+1][y]+vf3[x][y-1]-4*vf3[x][y]);

                    }

                }

            }
        }

        for (x=0;x<=myxgrid/8;x++){
            for (y=0;y<=myygrid/8;y++){  //convert Df5 onto courser grid

                if (!a[8*x][8*y]){

                    Df6[x][y]=Df5[2*x][2*y];

                }

            }
        }

        for (m=0; m<=5;m++){
            for (x=0;x<=myxgrid/8;x++){
                for (y=0;y<=myygrid/8;y++){  //find correction in the correction of the correction on the coursest grid using gauss siedel

                    if (!a[8*x][8*y]){

                        if ( x==0 ){

                            vf4[x][y]=0.25*((Df6[x][y]*(pow(8*d,2)))+vf4[x][y+1]+vf4[x][y]+vf4[x+1][y]+vf4[x][y-1]);

                        }

                        else if (x==myxgrid/8){

                            vf4[x][y]=0.25*((Df6[x][y]*(pow(8*d,2)))+vf4[x][y+1]+vf4[x-1][y]+vf4[x][y]+vf4[x][y-1]);

                        }

                        else if (y==0){

                            vf4[x][y]=0.25*((Df6[x][y]*(pow(8*d,2)))+vf4[x][y+1]+vf4[x-1][y]+vf4[x+1][y]+vf4[x][y]);

                        }

                        else if (y==myygrid/8){

                            vf4[x][y]=0.25*((Df6[x][y]*(pow(8*d,2)))+vf4[x][y]+vf4[x-1][y]+vf4[x+1][y]+vf4[x][y-1]);

                        }

                        else {

                            vf4[x][y]=0.25*((Df6[x][y]*(pow(8*d,2)))+vf4[x][y+1]+vf4[x-1][y]+vf4[x+1][y]+vf4[x][y-1]);

                        }

                    }

                }
            }
        }



        for (y=0;y<=myygrid/8;y++){
            for (x=0;x<=myxgrid/8;x++){              //interpolate correction/correction/correction onto 4d grid, matching values

                if (!a[8*x][8*y]){

                    vf5[2*x][2*y]=vf4[x][y];

                }
            }
        }


        for (x=0;x<=myxgrid/4;x+=2){
            for (y=1;y<=myygrid/4;y+=2){
                                        //interpolate correction/correction/correction onto 4d grid, even columns

                if (!a[4*x][4*y]){

                    if (y==myygrid/4){

                        vf5[x][y]=vf5[x][y-1];
                    }

                    else {

                        vf5[x][y]=0.5*(vf5[x][y+1]+vf5[x][y-1]);

                    }
                }

            }
        }


        for (x=1;x<=myxgrid/4;x+=2){
            for (y=0;y<=myygrid/4;y++){//interpolate correction/correction/correction onto 4*d grid, odd columns


                if (!a[4*x][4*y]){


                    if (x==myxgrid/4){

                        vf5[x][y]=vf5[x-1][y];

                    }


                    else {

                        vf5[x][y]=0.5*(vf5[x+1][y]+vf5[x-1][y]);

                    }

                }

            }
        }

        for (x=0;x<=myxgrid/4;x++){
            for (y=0;y<=myygrid/4;y++){  //correcting the correction/correction
                if (!a[4*x][4*y]){

                    vf3[x][y]=vf3[x][y]+vf5[x][y];

                }

            }

        }


        for (m=0; m<=3;m++){
            for (x=0;x<=myxgrid/4;x++){
                for (y=0;y<=myygrid/4;y++){  //smooth correction/correction on the 4*d grid using gauss siedel

                    if (!a[4*x][4*y]){

                        if ( x==0 ){

                            vf3[x][y]=0.25*((Df4[x][y]*(pow(4*d,2)))+vf3[x][y+1]+vf3[x][y]+vf3[x+1][y]+vf3[x][y-1]);

                        }

                        else if (x==myxgrid/4){

                            vf3[x][y]=0.25*((Df4[x][y]*(pow(4*d,2)))+vf3[x][y+1]+vf3[x-1][y]+vf3[x][y]+vf3[x][y-1]);

                        }

                        else if (y==0){

                            vf3[x][y]=0.25*((Df4[x][y]*(pow(4*d,2)))+vf3[x][y+1]+vf2[x-1][y]+vf3[x+1][y]+vf3[x][y]);

                        }

                        else if (y==myygrid/4){

                            vf3[x][y]=0.25*((Df4[x][y]*(pow(4*d,2)))+vf3[x][y]+vf3[x-1][y]+vf3[x+1][y]+vf3[x][y-1]);

                        }

                        else {

                            vf3[x][y]=0.25*((Df4[x][y]*(pow(4*d,2)))+vf3[x][y+1]+vf3[x-1][y]+vf3[x+1][y]+vf3[x][y-1]);

                        }

                    }

                }
            }
        }


        for (y=0;y<=myygrid/4;y++){
            for (x=0;x<=myxgrid/4;x++){                   //interpolate correction/correction onto 2*d grid, matching values

                if (!a[4*x][4*y]){

                    vf6[2*x][2*y]=vf3[x][y];

                }
            }
        }


        for (x=0;x<=myxgrid/2;x+=2){
            for (y=1;y<=myygrid/2;y+=2){
                                        //interpolate correction/correction onto 2*d grid, even columns

                if (!a[2*x][2*y]){

                    if (y==myygrid/2){

                        vf6[x][y]=vf6[x][y-1];
                    }

                    else {

                        vf6[x][y]=0.5*(vf6[x][y+1]+vf6[x][y-1]);

                    }
                }

            }
        }

        for (x=1;x<=myxgrid/2;x+=2){
            for (y=0;y<=myygrid/2;y++){//interpolate correction/correction onto 2*d grid, odd columns



                if (!a[2*x][2*y]){


                    if (x==myxgrid/2){

                        vf6[x][y]=vf6[x-1][y];

                    }


                    else {

                        vf6[x][y]=0.5*(vf6[x+1][y]+vf6[x-1][y]);

                    }

                }

            }
        }

        for (x=0;x<=myxgrid/2;x++){
            for (y=0;y<=myygrid/2;y++){  //correcting the correction
                if (!a[2*x][2*y]){

                    vf2[x][y]=vf2[x][y]+vf6[x][y];

                }

            }

        }


        for (m=0; m<=3;m++){
            for (x=0;x<=myxgrid/2;x++){
                for (y=0;y<=myygrid/2;y++){  //smoothing the correction on the 2d grid

                    if (!a[2*x][2*y]){

                        if ( x==0 ){

                            vf2[x][y]=0.25*((Df2[x][y]*(pow(2*d,2)))+vf2[x][y+1]+vf2[x][y]+vf2[x+1][y]+vf2[x][y-1]);

                        }

                        else if (x==myxgrid/2){

                            vf2[x][y]=0.25*((Df2[x][y]*(pow(2*d,2)))+vf2[x][y+1]+vf2[x-1][y]+vf2[x][y]+vf2[x][y-1]);

                        }

                        else if (y==0){

                            vf2[x][y]=0.25*((Df2[x][y]*(pow(2*d,2)))+vf2[x][y+1]+vf2[x-1][y]+vf2[x+1][y]+vf2[x][y]);

                        }

                        else if (y==myygrid/2){

                            vf2[x][y]=0.25*((Df2[x][y]*(pow(2*d,2)))+vf2[x][y]+vf2[x-1][y]+vf2[x+1][y]+vf2[x][y-1]);

                        }

                        else {

                            vf2[x][y]=0.25*((Df2[x][y]*(pow(2*d,2)))+vf2[x][y+1]+vf2[x-1][y]+vf2[x+1][y]+vf2[x][y-1]);

                        }

                    }

                }
            }
        }

        for (y=0;y<=myygrid/2;y++){
            for (x=0;x<=myxgrid/2;x++){                   //interpolate correction onto fine grid, matching values

                if (!a[2*x][2*y]){

                    vf[2*x][2*y]=vf2[x][y];

                }
            }
        }


        for (x=0;x<=myxgrid;x+=2){
            for (y=1;y<=myygrid;y+=2){
                //interpolate correction onto fine grid, even columns

                if (!a[x][y]){

                    if (y==myygrid){

                        vf[x][y]=vf[x][y-1];
                    }

                    else {

                        vf[x][y]=0.5*(vf[x][y+1]+vf[x][y-1]);

                    }
                }

            }
        }

        for (x=1;x<=myxgrid;x+=2){
            for (y=0;y<=myygrid;y++){//interpolate correction onto fine grid, odd columns


                if (!a[x][y]){


                    if (x==myxgrid){

                        vf[x][y]=vf[x-1][y];

                    }


                    else {

                        vf[x][y]=0.5*(vf[x+1][y]+vf[x-1][y]);

                    }

                }

            }
        }


        for (x=0;x<=myxgrid;x++){
            for (y=0;y<=myygrid;y++){  //calculate final V values
                if (!a[x][y]){

                    V[x][y]=V[x][y]+vf[x][y];

                }

            }

        }

        //final smoothing using gauss-siedel


        for (m=0; m<=3; m++){
            for (x=0;x<=myxgrid;x++){
                for (y=0;y<=myygrid;y++){

                    if (!a[x][y]){

                        if ( x==0 ){  //approximations at unset boundaries

                            V[x][y]=0.25*(V[x+1][y]+V[x][y]+V[x][y+1]+V[x][y-1]);

                        }

                        else if (x==myxgrid){

                            V[x][y]=0.25*(V[x][y]+V[x-1][y]+V[x][y+1]+V[x][y-1]);

                        }

                        else if (y==0){

                            V[x][y]=0.25*(V[x+1][y]+V[x-1][y]+V[x][y+1]+V[x][y]);

                        }


                        else if (y==myygrid){

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

    int i, j;

    ofstream file;
    file.open("draft3.dat");
    ofstream file2;
    file2.open("grad1.dat");


    double Ex,Ey;
    for (i=1; i<myxgrid; i++){
        for (j=1; j<myygrid; j++){

            file << (i) << "      "<< ((myygrid-j)) << "    " <<  V[i][j] << "\n";
            if(j%25==0){
                if(i%25==0){
                Ex =  0.5*(V[i+1][j]-V[i-1][j]);
                Ey =  0.5*(V[i][j+1]-V[i][j-1]);
                if (Ex+Ey<2){
                file2 << (i) << " " << (myygrid-j) << " " << 20*Ex << " " << 20*Ey << endl;
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




void fgr(int myxgrid, int myygrid){


    //input of variables from shell script

    clock_t t;
    t = clock();
    solf(myxgrid,myygrid);
    otpf(myxgrid,myygrid);
    t = clock() - t;

    cout << "CPU time=" << (float)t/(CLOCKS_PER_SEC) <<"s." << endl;





}
void otpf(int myxgrid, int myygrid){
    ofstream file;
    file.open("draft3.dat");



    for (int i=0; i<=myxgrid; i++){
        for (int j=0; j<=myygrid; j++){

            file << (i*myygrid) << "      "<< (j*myygrid) << "    " <<  V[i][j] << "\n";

        }
        file << "\n";
    }


    file.close();

}
void fgre1(int myxgrid, int myygrid){





    //input of variables from shell script

    clock_t t;
    t = clock();
    solf(myxgrid,myygrid);
    otpfe1(myxgrid,myygrid);
    t = clock() - t;

    cout << "CPU time=" << (float)t/(CLOCKS_PER_SEC) <<"s." << endl;
}

void otpfe1(int myxgrid, int myygrid){
    ofstream file;
    file.open("draft3.dat");
    int d=1;
    for (int i=0; i<=myxgrid; i++){
        for (int j=0; j<=myygrid; j++){

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

void fgre2(int myxgrid, int myygrid){




    //input of variables from shell script

    clock_t t;
    t = clock();
    solf(myxgrid,myygrid);
    otpfe2(myxgrid,myygrid);
    t = clock() - t;

    cout << "CPU time=" << (float)t/(CLOCKS_PER_SEC) <<"s." << endl;
}

void otpfe2(int myxgrid, int myygrid){
    ofstream file;
    file.open("draft3.dat");
    int d =1;
    for (int i=0; i<=myxgrid; i++){
        for (int j=0; j<=myygrid; j++){

            double v=(-0.40*(i*d-25)*(1-pow((10/sqrt(pow((i*d-25),2)+pow((j*d-25),2))),3)));

            if ( pow((i*d-25),2)+pow((j*d-25),2) <= pow(10,2) ){  //cycle through and evaluate boundaries

                            file << (i*d) << "      "<< (j*d) << "    " <<  0 << "\n";


                        }

            else{

            file << (i*d) << "      "<< (j*d) << "    " <<  abs(V[i][j] -v )<< "\n";
            }

        }
        file << "\n";
    }


    file.close();

}


