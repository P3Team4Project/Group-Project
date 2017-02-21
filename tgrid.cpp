#include "renderarea.h"
#include "main.h"
#include "tgrid.h"

using namespace std;

void otpt(double gridmax, double d);
void otpte1(double gridmax, double d);
void otpte2(double gridmax, double d);



void solt(double gridmax, double d){

    int x=0,y=0,m=0,l=0, h=gridmax/d, max_it=100;

    for (x=0;x<=h;x++){
        for (y=0;y<=h;y++){

            if (!a[x][y]){



                    V[x][y]=0;

            }


            vc[x][y]=0;
            v[x][y]=0;  //initialise everything else to zero
            D[x][y]=0;
            Dc[x][y]=0;


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



        for (x=0;x<=h;x++){
            for (y=0;y<=h;y++){

                if (!a[x][y]){  //find defect on fine grid

                   if ( x==0 ){

                    D[x][y]=(1/(pow(d,2)))*(V[x][y+1]+V[x][y]-4*V[x][y]+V[x+1][y]+V[x][y-1]);

                    }

                    else if (x==h){

                    D[x][y]=(1/(pow(d,2)))*(V[x][y+1]+V[x-1][y]-4*V[x][y]+V[x][y]+V[x][y-1]);

                    }

                    else if (y==0){

                    D[x][y]=(1/(pow(d,2)))*(V[x][y+1]+V[x-1][y]-4*V[x][y]+V[x+1][y]+V[x][y]);

                    }


                    else if (y==h){

                    D[x][y]=(1/(pow(d,2)))*(V[x][y]+V[x-1][y]-4*V[x][y]+V[x+1][y]+V[x][y-1]);

                    }


                    else {

                    D[x][y]=(1/(pow(d,2)))*(V[x][y+1]+V[x-1][y]-4*V[x][y]+V[x+1][y]+V[x][y-1]);

                    }
                }
                //cout<<"bla"<<endl;
                vc[x][y]=0;
                v[x][y]=0;
            }
        }


        for (x=0;x<=h/2;x++){
            for (y=0;y<=h/2;y++){  //convert defect onto course grid

                if (!a[2*x][2*y]){

                    Dc[x][y]=D[2*x][2*y];

                }

            }
        }

    for (m=0; m<=5;m++){
       for (x=0;x<=h/2;x++){
            for (y=0;y<=h/2;y++){  //calculate correction on course grid

                    if (!a[2*x][2*y]){

                        if ( x==0 ){

                         vc[x][y]=0.25*((Dc[x][y]*(pow(2*d,2)))+vc[x][y+1]+vc[x][y]+vc[x+1][y]+vc[x][y-1]);

                        }

                        else if (x==h/2){

                        vc[x][y]=0.25*((Dc[x][y]*(pow(2*d,2)))+vc[x][y+1]+vc[x-1][y]+vc[x][y]+vc[x][y-1]);

                        }

                        else if (y==0){

                        vc[x][y]=0.25*((Dc[x][y]*(pow(2*d,2)))+vc[x][y+1]+vc[x-1][y]+vc[x+1][y]+vc[x][y]);

                        }

                        else if (y==h/2){

                         vc[x][y]=0.25*((Dc[x][y]*(pow(2*d,2)))+vc[x][y]+vc[x-1][y]+vc[x+1][y]+vc[x][y-1]);

                        }

                        else {

                        vc[x][y]=0.25*((Dc[x][y]*(pow(2*d,2)))+vc[x][y+1]+vc[x-1][y]+vc[x+1][y]+vc[x][y-1]);

                        }

                    }

                }
            }
        }



        for (y=0;y<=h/2;y++){
            for (x=0;x<=h/2;x++){                   //interpolate correction onto fine grid, matching values

                if (!a[2*x][2*y]){

                    v[2*x][2*y]=vc[x][y];

                }
            }
        }


        for (x=0;x<=h;x+=2){
                for (y=1;y<=h;y+=2){
                //interpolate correction onto fine grid, even columns

                if (!a[x][y]){

                    if (y==h){

                       v[x][y]=v[x][y-1];
                    }

                    else {

                    v[x][y]=0.5*(v[x][y+1]+v[x][y-1]);

                    }
                }

            }
        }

            for (x=1;x<=h;x+=2){
                 for (y=0;y<=h;y++){//interpolate correction onto fine grid, odd columns


                if (!a[x][y]){


                   if (x==h){

                       v[x][y]=v[x-1][y];

                   }


                    else {

                        v[x][y]=0.5*(v[x+1][y]+v[x-1][y]);

                    }

                }

            }
        }


        for (x=0;x<=h;x++){
            for (y=0;y<=h;y++){  //calculate final V values
                if (!a[x][y]){

                    V[x][y]+=v[x][y];

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

                        //cout << V[x][y] << endl;
                    }

                }
            }
        }
       // cout << "l"<< l << endl;
        l++;
  }



}

void tgr(){

    double gridmax=50, d=0.1;


    //input of variables from shell script

    clock_t t;
    t = clock();
    solt(gridmax,d);
    otpt(gridmax,d);
    t = clock() - t;

    cout << "CPU time=" << (float)t/(CLOCKS_PER_SEC) <<"s." << endl;


}
void otpt(double gridmax, double d){
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
void tgre1(){

    double gridmax=50, d=0.1;



    //input of variables from shell script

    clock_t t;
    t = clock();
    solt(gridmax,d);
    otpte1(gridmax,d);
    t = clock() - t;

    cout << "CPU time=" << (float)t/(CLOCKS_PER_SEC) <<"s." << endl;
}

void otpte1(double gridmax, double d){
    ofstream file;
    file.open("draft3.dat");

    double jmax=gridmax/d;

    for (int i=0; i<=jmax; i++){
        for (int j=0; j<=jmax; j++){

            if ( pow((i*d-25),2)+pow((j*d-25),2) <= pow(10,2) ){  //cycle through and evaluate boundaries

                            file << (i*d) << "      "<< (j*d) << "    " <<  0 << "\n";


                        }           

            else{

            file << (i*d) << "      "<< (j*d) << "    " << abs(V[i][j] -((10/log(20/10))*(log(sqrt(pow((i*d-25),2)+pow((j*d-25),2)))-log(10)))) << "\n";

            }
        }
        file << "\n";
    }


    file.close();

}

void tgre2(){

    double gridmax=50, d=0.1;


    //input of variables from shell script

    clock_t t;
    t = clock();
    solt(gridmax,d);
    otpte2(gridmax,d);
    t = clock() - t;

    cout << "CPU time=" << (float)t/(CLOCKS_PER_SEC) <<"s." << endl;
}

void otpte2(double gridmax, double d){
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

            file << (i*d) << "      "<< (j*d) << "    " <<  abs(V[i][j]-v) << "\n";

            }

        }
        file << "\n";
    }


    file.close();

}


