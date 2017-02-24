#include "renderarea.h"
#include "main.h"
#include "tgrid.h"

using namespace std;

void otpt(int W, int H);
void otpte1(int W, int H);
void otpte2(int W, int H);



void solt(int W, int H, double ET){

    int x=0,y=0,m=0,l=0, d=1, max_it=100000;

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

    for (int i=0; i<=W; i++){
        for (int j=0; j<=H; j++){

            //  cout << V[i+1][j] << "    " << V[i-1][j] << endl;

            if (!a[i][j]){


                double Ex =  0.5*(V[i+1][j]-V[i-1][j]);
                double Ey =  0.5*(V[i][j+1]-V[i][j-1]);

                // cout << Ex << "   " << Ey << endl;


                Grad1[i][j] = sqrt( pow(Ex, 2) + pow(Ey, 2));

                //cout << Grad1[i][j] << endl;

            }
        }
    }




    // cout << Grad1[500][500] << endl;
    //fix fix
    float maximum = 0;
    int k1 = 0;
    int k2 = 0;
    for (int i=0; i<=W; i++){
        for (int j=0; j<=H; j++){

            c1[i][j]=false;

            if (Grad1[i][j]>maximum) {
                maximum = Grad1[i][j];
                k1 = i;
                k2 = j;
            }

        }
    }
    //assign space ij in Grad1 to b

    c1[k1][k2] = true;





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



        for (x=0;x<=W/2;x++){
            for (y=0;y<=H/2;y++){                   //interpolate correction onto fine grid, matching values

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

                        if (c1[x][y]){
                            compare1[l]=abs(V[x][y]);
                        }


                    }

                }
            }
        }

        if ((abs(compare1[l-1]-compare1[l]))<=ET) {

               cout << "convergence after " << l << " iterations." << endl;
               break;
           }

           if (l==max_it){

               cout << "convergence not reached. " << endl;
           }


        l++;


  }



}

void tgr(double ET){



    QDesktopWidget dw;
        int W = (int)dw.width()*0.5;
        int H = (int)dw.height()*0.5;

    //input of variables from shell script

    clock_t t;
    t = clock();
    solt(W,H, ET);
    otpt(W,H);
    t = clock() - t;

    cout << "CPU time=" << (float)t/(CLOCKS_PER_SEC) <<"s." << endl;



}


void otpt(int W, int H){

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
void tgre1(double ET){



    QDesktopWidget dw;
        int W = (int)dw.width()*0.5;
        int H = (int)dw.height()*0.5;

    //input of variables from shell script

    clock_t t;
    t = clock();
    solt(W,H, ET);
    otpte1(W,H);
    t = clock() - t;

    cout << "CPU time=" << (float)t/(CLOCKS_PER_SEC) <<"s." << endl;
}

void otpte1(int W, int H){
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

void tgre2(double ET){



    QDesktopWidget dw;
        int W = (int)dw.width()*0.5;
        int H = (int)dw.height()*0.5;


    //input of variables from shell script

    clock_t t;
    t = clock();
    solt(W,H, ET);
    otpte2(W,H);
    t = clock() - t;

    cout << "CPU time=" << (float)t/(CLOCKS_PER_SEC) <<"s." << endl;
}

void otpte2(int W, int H){
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



