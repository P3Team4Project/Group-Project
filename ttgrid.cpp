#include "renderarea.h"
#include "main.h"
#include "ttgrid.h"
using namespace std;


void otptt(int W, int H);
void otptte1(int W, int H);
void otptte2(int W, int H);


void soltt(int W, int H, double ET){




    int x=0,y=0,m=0,l=0, max_it=100000, d=1;

    for (x=0;x<=W;x++){
        for (y=0;y<=H;y++){


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


                Grad2[i][j] = sqrt( pow(Ex, 2) + pow(Ey, 2));

                //cout << Grad2[i][j] << endl;

            }
        }
    }




    // cout << Grad2[500][500] << endl;
    //fix fix
    float maximum = 0;
    int k1 = 0;
    int k2 = 0;
    for (int i=0; i<=W; i++){
        for (int j=0; j<=H; j++){

            c2[i][j]=false;

            if (Grad2[i][j]>maximum) {
                maximum = Grad2[i][j];
                k1 = i;
                k2 = j;
            }

        }
    }
    //assign space ij in Grad2 to b

    c2[k1][k2] = true;




    while (l<=max_it ){



        for (x=0;x<=W;x++){
            for (y=0;y<=H;y++){

                if (!a[x][y]){  //find defect on fine grid

                    if ( x==0 ){

                        Dt[x][y]=(1/(pow(d,2)))*(V[x][y+1]+V[x][y]-4*V[x][y]+V[x+1][y]+V[x][y-1]);

                    }

                    else if (x==W){

                        Dt[x][y]=(1/(pow(d,2)))*(V[x][y+1]+V[x-1][y]-4*V[x][y]+V[x][y]+V[x][y-1]);

                    }

                    else if (y==0){

                        Dt[x][y]=(1/(pow(d,2)))*(V[x][y+1]+V[x-1][y]-4*V[x][y]+V[x+1][y]+V[x][y]);

                    }


                    else if (y==H){

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


        for (x=0;x<=W/2;x++){
            for (y=0;y<=H/2;y++){  //convert defect onto course grid

                if (!a[2*x][2*y]){

                    D2[x][y]=Dt[2*x][2*y];

                }

            }
        }

        for (m=0; m<=3;m++){
            for (x=0;x<=W/2;x++){
                for (y=0;y<=H/2;y++){  //calculate correction on course grid

                    if (!a[2*x][2*y]){

                        if ( x==0 ){

                            v2[x][y]=0.25*((D2[x][y]*(pow(2*d,2)))+v2[x][y+1]+v2[x][y]+v2[x+1][y]+v2[x][y-1]);

                        }

                        else if (x==W/2){

                            v2[x][y]=0.25*((D2[x][y]*(pow(2*d,2)))+v2[x][y+1]+v2[x-1][y]+v2[x][y]+v2[x][y-1]);

                        }

                        else if (y==0){

                            v2[x][y]=0.25*((D2[x][y]*(pow(2*d,2)))+v2[x][y+1]+v2[x-1][y]+v2[x+1][y]+v2[x][y]);

                        }

                        else if (y==H/2){

                            v2[x][y]=0.25*((D2[x][y]*(pow(2*d,2)))+v2[x][y]+v2[x-1][y]+v2[x+1][y]+v2[x][y-1]);

                        }

                        else {

                            v2[x][y]=0.25*((D2[x][y]*(pow(2*d,2)))+v2[x][y+1]+v2[x-1][y]+v2[x+1][y]+v2[x][y-1]);

                        }

                    }

                }
            }
        }

        for (x=0;x<=W/2;x++){
            for (y=0;y<=H/2;y++){  //calculate defect from correction calculation

                if (!a[2*x][2*y]){

                    if ( x==0 ){

                        D3[x][y]=D2[x][y]+(1/(pow(2*d,2)))*(v2[x][y+1]+v2[x][y]+v2[x+1][y]+v2[x][y-1]-4*v2[x][y]);

                    }

                    else if (x==W/2){

                       D3[x][y]=D2[x][y]+(1/(pow(2*d,2)))*(v2[x][y+1]+v2[x-1][y]+v2[x][y]+v2[x][y-1]-4*v2[x][y]);

                    }

                    else if (y==0){

                        D3[x][y]=D2[x][y]+(1/(pow(2*d,2)))*(v2[x][y+1]+v2[x-1][y]+v2[x+1][y]+v2[x][y]-4*v2[x][y]);

                    }

                    else if (y==H/2){

                      D3[x][y]=D2[x][y]+(1/(pow(2*d,2)))*(v2[x][y]+v2[x-1][y]+v2[x+1][y]+v2[x][y-1]-4*v2[x][y]);

                    }

                    else {

                        D3[x][y]=D2[x][y]+(1/(pow(2*d,2)))*(v2[x][y+1]+v2[x-1][y]+v2[x+1][y]+v2[x][y-1]-4*v2[x][y]);

                    }

                }

            }
        }


        for (x=0;x<=W/4;x++){
            for (y=0;y<=H/4;y++){  //convert D3 onto courser grid

                if (!a[4*x][4*y]){

                    D4[x][y]=D3[2*x][2*y];

                }

            }
        }

        for (m=0; m<=5;m++){
            for (x=0;x<=W/4;x++){
                for (y=0;y<=H/4;y++){  //find correction in the correction on the coursest grid using gauss siedel

                    if (!a[4*x][4*y]){

                        if ( x==0 ){

                            v3[x][y]=0.25*((D4[x][y]*(pow(4*d,2)))+v3[x][y+1]+v3[x][y]+v3[x+1][y]+v3[x][y-1]);

                        }

                        else if (x==W/4){

                            v3[x][y]=0.25*((D4[x][y]*(pow(4*d,2)))+v3[x][y+1]+v3[x-1][y]+v3[x][y]+v3[x][y-1]);

                        }

                        else if (y==0){

                            v3[x][y]=0.25*((D4[x][y]*(pow(4*d,2)))+v3[x][y+1]+v2[x-1][y]+v3[x+1][y]+v3[x][y]);

                        }

                        else if (y==H/4){

                            v3[x][y]=0.25*((D4[x][y]*(pow(4*d,2)))+v3[x][y]+v3[x-1][y]+v3[x+1][y]+v3[x][y-1]);

                        }

                        else {

                            v3[x][y]=0.25*((D4[x][y]*(pow(4*d,2)))+v3[x][y+1]+v3[x-1][y]+v3[x+1][y]+v3[x][y-1]);

                        }

                    }

                }
            }
        }


        for (x=0;x<=W/4;x++){
            for (y=0;y<=H/4;y++){                   //interpolate correction onto 2h grid, matching values

                if (!a[4*x][4*y]){

                    v4[2*x][2*y]=v3[x][y];

                }
            }
        }


        for (x=0;x<=W/2;x+=2){
            for (y=1;y<=H/2;y+=2){
                                     //interpolate correction onto 2h grid, even columns

                if (!a[2*x][2*y]){

                    if (y==H/2){

                        v4[x][y]=v4[x][y-1];
                    }

                    else {

                        v4[x][y]=0.5*(v4[x][y+1]+v4[x][y-1]);

                    }
                }

            }
        }


        for (x=1;x<=W/2;x+=2){
            for (y=0;y<=H/2;y++){//interpolate correction onto 2h grid, odd columns


                if (!a[2*x][2*y]){


                    if (x==W/2){

                        v4[x][y]=v4[x-1][y];

                    }


                    else {

                        v4[x][y]=0.5*(v4[x+1][y]+v4[x-1][y]);

                    }

                }

            }
        }

        for (x=0;x<=W/2;x++){
            for (y=0;y<=H/2;y++){  //correcting the correction
                if (!a[2*x][2*y]){

                    v2[x][y]=v4[x][y]+v2[x][y];

                }

            }

        }

        for (m=0; m<=3;m++){
            for (x=0;x<=W/2;x++){
                for (y=0;y<=H/2;y++){  //smoothing the correction on the 2h grid

                    if (!a[2*x][2*y]){

                        if ( x==0 ){

                            v2[x][y]=0.25*((D2[x][y]*(pow(2*d,2)))+v2[x][y+1]+v2[x][y]+v2[x+1][y]+v2[x][y-1]);

                        }

                        else if (x==W/2){

                            v2[x][y]=0.25*((D2[x][y]*(pow(2*d,2)))+v2[x][y+1]+v2[x-1][y]+v2[x][y]+v2[x][y-1]);

                        }

                        else if (y==0){

                            v2[x][y]=0.25*((D2[x][y]*(pow(2*d,2)))+v2[x][y+1]+v2[x-1][y]+v2[x+1][y]+v2[x][y]);

                        }

                        else if (y==H/2){

                            v2[x][y]=0.25*((D2[x][y]*(pow(2*d,2)))+v2[x][y]+v2[x-1][y]+v2[x+1][y]+v2[x][y-1]);

                        }

                        else {

                            v2[x][y]=0.25*((D2[x][y]*(pow(2*d,2)))+v2[x][y+1]+v2[x-1][y]+v2[x+1][y]+v2[x][y-1]);

                        }

                    }

                }
            }
        }

        for (x=0;x<=W/2;x++){
            for (y=0;y<=H/2;y++){                   //interpolate correction onto fine grid, matching values

                if (!a[2*x][2*y]){

                    vt[2*x][2*y]=v2[x][y];

                }
            }
        }


        for (x=0;x<=W;x+=2){
            for (y=1;y<=H;y+=2){
                //interpolate correction onto fine grid, even columns

                if (!a[x][y]){

                    if (y==H){

                        vt[x][y]=vt[x][y-1];
                    }

                    else {

                        vt[x][y]=0.5*(vt[x][y+1]+vt[x][y-1]);

                    }
                }

            }
        }

        for (x=1;x<=W;x+=2){
            for (y=0;y<=H;y++){//interpolate correction onto fine grid, odd columns


                if (!a[x][y]){


                    if (x==W){

                        vt[x][y]=vt[x-1][y];

                    }


                    else {

                        vt[x][y]=0.5*(vt[x+1][y]+vt[x-1][y]);

                    }

                }

            }
        }


        for (x=0;x<=W;x++){
            for (y=0;y<=H;y++){  //calculate final V values
                if (!a[x][y]){

                    V[x][y]=V[x][y]+vt[x][y];

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

                        if (c2[x][y]){
                            compare2[l]=abs(V[x][y]);
                        }
                    }

                }
            }
        }

        if ((abs(compare2[l-1]-compare2[l]))<=ET) {

               cout << "convergence after " << l << " iterations." << endl;
               break;
           }

           if (l==max_it){

               cout << "convergence not reached. " << endl;
           }


        l++;
    }




}

void ttgr(double ET){



    QDesktopWidget dw;
        int W = (int)dw.width()*0.5;
        int H = (int)dw.height()*0.5;


    soltt(W,H, ET);
    otptt(W,H);




}

void ttgr1(int xgrid, int ygrid, double ET){





    soltt(xgrid, ygrid, ET);
    otptt( xgrid, ygrid);




}


void otptt(int W, int H){

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
void ttgre1(double ET){



    QDesktopWidget dw;
        int W = (int)dw.width()*0.5;
        int H = (int)dw.height()*0.5;


    soltt(W,H, ET);
    otptte1(W,H);

}

void otptte1(int W, int H){
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

void ttgre2(double ET){



    QDesktopWidget dw;
        int W = (int)dw.width()*0.5;
        int H = (int)dw.height()*0.5;


    soltt(W,H, ET);
    otptte2(W,H);

}

void otptte2(int W, int H){
    ofstream file;
    file.open("draft3.dat");



    for (int i=0; i<=W; i++){
        for (int j=0; j<=H; j++){



            double v=(-0.02*(i-(W/2))*(1-pow((10/sqrt(pow((i-(W/2)),2)+pow((j-(H/2)),2))),3)));

            if ( pow((i-(W/2)),2)+pow((j-(H/2)),2) <= pow(100,2) ){  //cycle through and evaluate boundaries

                            file << (i) << "      "<< (H-j) << "    " <<  0 << "\n";


                        }


            else{

            file << (i) << "      "<< (H-j) << "    " << abs(V[i][j]- v) << "\n";

            }

        }
        file << "\n";
    }


    file.close();

}

