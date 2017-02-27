#include "renderarea.h"
#include "main.h"

using namespace std;

double Dt[1000][1000], D2[1000][1000],D3[1000][1000],D4[1000][1000], vt[1000][1000], v2[1000][1000],v3[1000][1000],v4[1000][1000];



void soltt(int myxgrid, int myygrid){

    int x=0,y=0,m=0,l=0, max_it=100,d=1;

    for (x=0;x<=myxgrid;x++){
        for (y=0;y<=myygrid;y++){


            if (!a[x][y]){



                    V[x][y]=0;

            }


            v2[x][y]=0;
            vt[x][y]=0;  //initialise everything else to zero
            Dt[x][y]=0;
            D2[x][y]=0;


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

                        Dt[x][y]=(1/(pow(d,2)))*(V[x][y+1]+V[x][y]-4*V[x][y]+V[x+1][y]+V[x][y-1]);

                    }

                    else if (x==myxgrid){

                        Dt[x][y]=(1/(pow(d,2)))*(V[x][y+1]+V[x-1][y]-4*V[x][y]+V[x][y]+V[x][y-1]);

                    }

                    else if (y==0){

                        Dt[x][y]=(1/(pow(d,2)))*(V[x][y+1]+V[x-1][y]-4*V[x][y]+V[x+1][y]+V[x][y]);

                    }


                    else if (y==myygrid){

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


        for (x=0;x<=myxgrid/2;x++){
            for (y=0;y<=myygrid/2;y++){  //convert defect onto course grid

                if (!a[2*x][2*y]){

                    D2[x][y]=Dt[2*x][2*y];

                }

            }
        }

        for (m=0; m<=3;m++){
            for (x=0;x<=myxgrid/2;x++){
                for (y=0;y<=myygrid/2;y++){  //calculate correction on course grid

                    if (!a[2*x][2*y]){

                        if ( x==0 ){

                            v2[x][y]=0.25*((D2[x][y]*(pow(2*d,2)))+v2[x][y+1]+v2[x][y]+v2[x+1][y]+v2[x][y-1]);

                        }

                        else if (x==myxgrid/2){

                            v2[x][y]=0.25*((D2[x][y]*(pow(2*d,2)))+v2[x][y+1]+v2[x-1][y]+v2[x][y]+v2[x][y-1]);

                        }

                        else if (y==0){

                            v2[x][y]=0.25*((D2[x][y]*(pow(2*d,2)))+v2[x][y+1]+v2[x-1][y]+v2[x+1][y]+v2[x][y]);

                        }

                        else if (y==myygrid/2){

                            v2[x][y]=0.25*((D2[x][y]*(pow(2*d,2)))+v2[x][y]+v2[x-1][y]+v2[x+1][y]+v2[x][y-1]);

                        }

                        else {

                            v2[x][y]=0.25*((D2[x][y]*(pow(2*d,2)))+v2[x][y+1]+v2[x-1][y]+v2[x+1][y]+v2[x][y-1]);

                        }

                    }

                }
            }
        }

        for (x=0;x<=myxgrid/2;x++){
            for (y=0;y<=myygrid/2;y++){  //calculate defect from correction calculation

                if (!a[2*x][2*y]){

                    if ( x==0 ){

                        D3[x][y]=D2[x][y]+(1/(pow(2*d,2)))*(v2[x][y+1]+v2[x][y]+v2[x+1][y]+v2[x][y-1]-4*v2[x][y]);

                    }

                    else if (x==myxgrid/2){

                       D3[x][y]=D2[x][y]+(1/(pow(2*d,2)))*(v2[x][y+1]+v2[x-1][y]+v2[x][y]+v2[x][y-1]-4*v2[x][y]);

                    }

                    else if (y==0){

                        D3[x][y]=D2[x][y]+(1/(pow(2*d,2)))*(v2[x][y+1]+v2[x-1][y]+v2[x+1][y]+v2[x][y]-4*v2[x][y]);

                    }

                    else if (y==myygrid/2){

                      D3[x][y]=D2[x][y]+(1/(pow(2*d,2)))*(v2[x][y]+v2[x-1][y]+v2[x+1][y]+v2[x][y-1]-4*v2[x][y]);

                    }

                    else {

                        D3[x][y]=D2[x][y]+(1/(pow(2*d,2)))*(v2[x][y+1]+v2[x-1][y]+v2[x+1][y]+v2[x][y-1]-4*v2[x][y]);

                    }

                }

            }
        }


        for (x=0;x<=myxgrid/4;x++){
            for (y=0;y<=myygrid/4;y++){  //convert D3 onto courser grid

                if (!a[4*x][4*y]){

                    D4[x][y]=D3[2*x][2*y];

                }

            }
        }

        for (m=0; m<=5;m++){
            for (x=0;x<=myxgrid/4;x++){
                for (y=0;y<=myygrid/4;y++){  //find correction in the correction on the coursest grid using gauss siedel

                    if (!a[4*x][4*y]){

                        if ( x==0 ){

                            v3[x][y]=0.25*((D4[x][y]*(pow(4*d,2)))+v3[x][y+1]+v3[x][y]+v3[x+1][y]+v3[x][y-1]);

                        }

                        else if (x==myxgrid/4){

                            v3[x][y]=0.25*((D4[x][y]*(pow(4*d,2)))+v3[x][y+1]+v3[x-1][y]+v3[x][y]+v3[x][y-1]);

                        }

                        else if (y==0){

                            v3[x][y]=0.25*((D4[x][y]*(pow(4*d,2)))+v3[x][y+1]+v2[x-1][y]+v3[x+1][y]+v3[x][y]);

                        }

                        else if (y==myygrid/4){

                            v3[x][y]=0.25*((D4[x][y]*(pow(4*d,2)))+v3[x][y]+v3[x-1][y]+v3[x+1][y]+v3[x][y-1]);

                        }

                        else {

                            v3[x][y]=0.25*((D4[x][y]*(pow(4*d,2)))+v3[x][y+1]+v3[x-1][y]+v3[x+1][y]+v3[x][y-1]);

                        }

                    }

                }
            }
        }


        for (y=0;y<=myygrid/4;y++){
            for (x=0;x<=myxgrid/4;x++){                   //interpolate correction onto 2h grid, matching values

                if (!a[4*x][4*y]){

                    v4[2*x][2*y]=v3[x][y];

                }
            }
        }


        for (x=0;x<=myxgrid/2;x+=2){
            for (y=1;y<=myygrid/2;y+=2){
                                     //interpolate correction onto 2h grid, even columns

                if (!a[2*x][2*y]){

                    if (y==myygrid/2){

                        v4[x][y]=v4[x][y-1];
                    }

                    else {

                        v4[x][y]=0.5*(v4[x][y+1]+v4[x][y-1]);

                    }
                }

            }
        }


        for (x=1;x<=myxgrid/2;x+=2){
            for (y=0;y<=myygrid/2;y++){//interpolate correction onto 2h grid, odd columns


                if (!a[2*x][2*y]){


                    if (x==myxgrid/2){

                        v4[x][y]=v4[x-1][y];

                    }


                    else {

                        v4[x][y]=0.5*(v4[x+1][y]+v4[x-1][y]);

                    }

                }

            }
        }

        for (x=0;x<=myxgrid/2;x++){
            for (y=0;y<=myygrid/2;y++){  //correcting the correction
                if (!a[2*x][2*y]){

                    v2[x][y]=v4[x][y]+v2[x][y];

                }

            }

        }

        for (m=0; m<=3;m++){
            for (x=0;x<=myxgrid/2;x++){
                for (y=0;y<=myygrid/2;y++){  //smoothing the correction on the 2h grid

                    if (!a[2*x][2*y]){

                        if ( x==0 ){

                            v2[x][y]=0.25*((D2[x][y]*(pow(2*d,2)))+v2[x][y+1]+v2[x][y]+v2[x+1][y]+v2[x][y-1]);

                        }

                        else if (x==myxgrid/2){

                            v2[x][y]=0.25*((D2[x][y]*(pow(2*d,2)))+v2[x][y+1]+v2[x-1][y]+v2[x][y]+v2[x][y-1]);

                        }

                        else if (y==0){

                            v2[x][y]=0.25*((D2[x][y]*(pow(2*d,2)))+v2[x][y+1]+v2[x-1][y]+v2[x+1][y]+v2[x][y]);

                        }

                        else if (y==myygrid/2){

                            v2[x][y]=0.25*((D2[x][y]*(pow(2*d,2)))+v2[x][y]+v2[x-1][y]+v2[x+1][y]+v2[x][y-1]);

                        }

                        else {

                            v2[x][y]=0.25*((D2[x][y]*(pow(2*d,2)))+v2[x][y+1]+v2[x-1][y]+v2[x+1][y]+v2[x][y-1]);

                        }

                    }

                }
            }
        }

        for (y=0;y<=myygrid/2;y++){
            for (x=0;x<=myxgrid/2;x++){                   //interpolate correction onto fine grid, matching values

                if (!a[2*x][2*y]){

                    vt[2*x][2*y]=v2[x][y];

                }
            }
        }


        for (x=0;x<=myxgrid;x+=2){
            for (y=1;y<=myygrid;y+=2){
                //interpolate correction onto fine grid, even columns

                if (!a[x][y]){

                    if (y==myygrid){

                        vt[x][y]=vt[x][y-1];
                    }

                    else {

                        vt[x][y]=0.5*(vt[x][y+1]+vt[x][y-1]);

                    }
                }

            }
        }

        for (x=1;x<=myxgrid;x+=2){
            for (y=0;y<=myygrid;y++){//interpolate correction onto fine grid, odd columns


                if (!a[x][y]){


                    if (x==myxgrid){

                        vt[x][y]=vt[x-1][y];

                    }


                    else {

                        vt[x][y]=0.5*(vt[x+1][y]+vt[x-1][y]);

                    }

                }

            }
        }


        for (x=0;x<=myxgrid;x++){
            for (y=0;y<=myygrid;y++){  //calculate final V values
                if (!a[x][y]){

                    V[x][y]=V[x][y]+vt[x][y];

                }

            }

        }

        //final smoothing using gauss-siedel


        for (m=0; m<=5; m++){
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



    //output all the final V values for all x & y  to a file for plotting


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

void ttgr(int myxgrid,int myygrid){




    //input of variables from shell script

    clock_t t;
    t = clock();
    soltt(myxgrid,myygrid);
    t = clock() - t;

    cout << "CPU time=" << (float)t/(CLOCKS_PER_SEC) <<"s." << endl;



}
