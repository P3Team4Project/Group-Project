#include "renderarea.h"
#include "main.h"


using namespace std;

double D[1000][1000], Dc[1000][1000], v[1000][1000], vc[1000][1000];


void solt(double gridmax, double d){

    QDesktopWidget dw;
    int W = (int)dw.width()*0.5;
    int H = (int)dw.height()*0.5;

    int x=0,y=0,m=0,l=0, max_it=100;

    gridmax = gridmax;

    for (x=0;x<=W;x++){
        for (y=0;y<=H;y++){

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
        for (x=0;x<=W;x++){
            for (y=0;y<=H;y++){

                if (!a[x][y]){

                    if ( x==0 ){  //approximations at unset boundaries

                        V[x][y]=0.25*(V[x+1][y]+V[x][y]+V[x][y+1]+V[x][y-1]);

                    }

                    else if (x==W){

                        V[x][y]=0.25*(V[x][y]+V[x-1][y]+V[x][y+1]+V[x][y-1]);

                    }

                    else if (y==0){

                        V[x][y]=0.25*(V[x+1][y]+V[x-1][y]+V[x][y+1]+V[x][y]);

                    }


                    else if (y==H){

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



        for (x=0;x<=W;x++){
            for (y=0;y<=H;y++){

                if (!a[x][y]){  //find defect on fine grid

                   if ( x==0 ){

                    D[x][y]=(1/(pow(d,2)))*(V[x][y+1]+V[x][y]-4*V[x][y]+V[x+1][y]+V[x][y-1]);

                    }

                    else if (x==W){

                    D[x][y]=(1/(pow(d,2)))*(V[x][y+1]+V[x-1][y]-4*V[x][y]+V[x][y]+V[x][y-1]);

                    }

                    else if (y==0){

                    D[x][y]=(1/(pow(d,2)))*(V[x][y+1]+V[x-1][y]-4*V[x][y]+V[x+1][y]+V[x][y]);

                    }


                    else if (y==H){

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


        for (x=0;x<=W/2;x++){
            for (y=0;y<=H/2;y++){  //convert defect onto course grid

                if (!a[2*x][2*y]){

                    Dc[x][y]=D[2*x][2*y];

                }

            }
        }

    for (m=0; m<=5;m++){
       for (x=0;x<=W/2;x++){
            for (y=0;y<=H/2;y++){  //calculate correction on course grid

                    if (!a[2*x][2*y]){

                        if ( x==0 ){

                         vc[x][y]=0.25*((Dc[x][y]*(pow(2*d,2)))+vc[x][y+1]+vc[x][y]+vc[x+1][y]+vc[x][y-1]);

                        }

                        else if (x==W/2){

                        vc[x][y]=0.25*((Dc[x][y]*(pow(2*d,2)))+vc[x][y+1]+vc[x-1][y]+vc[x][y]+vc[x][y-1]);

                        }

                        else if (y==0){

                        vc[x][y]=0.25*((Dc[x][y]*(pow(2*d,2)))+vc[x][y+1]+vc[x-1][y]+vc[x+1][y]+vc[x][y]);

                        }

                        else if (y==H/2){

                         vc[x][y]=0.25*((Dc[x][y]*(pow(2*d,2)))+vc[x][y]+vc[x-1][y]+vc[x+1][y]+vc[x][y-1]);

                        }

                        else {

                        vc[x][y]=0.25*((Dc[x][y]*(pow(2*d,2)))+vc[x][y+1]+vc[x-1][y]+vc[x+1][y]+vc[x][y-1]);

                        }

                    }

                }
            }
        }



        for (y=0;y<=H/2;y++){
            for (x=0;x<=W/2;x++){                   //interpolate correction onto fine grid, matching values

                if (!a[2*x][2*y]){

                    v[2*x][2*y]=vc[x][y];

                }
            }
        }


        for (x=0;x<=W;x+=2){
                for (y=1;y<=H;y+=2){
                //interpolate correction onto fine grid, even columns

                if (!a[x][y]){

                    if (y==H){

                       v[x][y]=v[x][y-1];
                    }

                    else {

                    v[x][y]=0.5*(v[x][y+1]+v[x][y-1]);

                    }
                }

            }
        }

            for (x=1;x<=W;x+=2){
                 for (y=0;y<=H;y++){//interpolate correction onto fine grid, odd columns


                if (!a[x][y]){


                   if (x==W){

                       v[x][y]=v[x-1][y];

                   }


                    else {

                        v[x][y]=0.5*(v[x+1][y]+v[x-1][y]);

                    }

                }

            }
        }


        for (x=0;x<=W;x++){
            for (y=0;y<=H;y++){  //calculate final V values
                if (!a[x][y]){

                    V[x][y]+=v[x][y];

                }

            }

        }

        //final smoothing using gauss-siedel


        for (m=0; m<=5; m++){
            for (x=0;x<=W;x++){
                for (y=0;y<=H;y++){

                    if (!a[x][y]){

                        if ( x==0 ){  //approximations at unset boundaries

                            V[x][y]=0.25*(V[x+1][y]+V[x][y]+V[x][y+1]+V[x][y-1]);

                        }

                        else if (x==W){

                            V[x][y]=0.25*(V[x][y]+V[x-1][y]+V[x][y+1]+V[x][y-1]);

                        }

                        else if (y==0){

                            V[x][y]=0.25*(V[x+1][y]+V[x-1][y]+V[x][y+1]+V[x][y]);

                        }


                        else if (y==H){

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

void tgr(){

    double gridmax=50, d=0.1;


    //input of variables from shell script

    clock_t t;
    t = clock();
    solt(gridmax,d);
    t = clock() - t;

    cout << "CPU time=" << (float)t/(CLOCKS_PER_SEC) <<"s." << endl;


}
