#include "renderarea.h"
#include "main.h"
#include "fgrid.h"


using namespace std;



void otpf(int W, int H);
void otpfe1(int W, int H);
void otpfe2(int W, int H);

void solf(int W, int H, double ET){

    int x=0,y=0,m=0,l=0, max_it=100000, d=1;

    for (x=0;x<=W;x++){
        for (y=0;y<=H;y++){


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


                Grad3[i][j] = sqrt( pow(Ex, 2) + pow(Ey, 2));

                //cout << Grad3[i][j] << endl;

            }
        }
    }




    // cout << Grad3[500][500] << endl;
    //fix fix
    float maximum = 0;
    int k1 = 0;
    int k2 = 0;
    for (int i=0; i<=W; i++){
        for (int j=0; j<=H; j++){

            c3[i][j]=false;

            if (Grad3[i][j]>maximum) {
                maximum = Grad3[i][j];
                k1 = i;
                k2 = j;
            }

        }
    }
    //assign space ij in Grad3 to b

    c3[k1][k2] = true;



    while (l<=max_it ){



        for (x=0;x<=W;x++){
            for (y=0;y<=H;y++){

                if (!a[x][y]){  //find defect on fine grid

                    if ( x==0 ){

                        Df[x][y]=(1/(pow(d,2)))*(V[x][y+1]+V[x][y]-4*V[x][y]+V[x+1][y]+V[x][y-1]);

                    }

                    else if (x==W){

                        Df[x][y]=(1/(pow(d,2)))*(V[x][y+1]+V[x-1][y]-4*V[x][y]+V[x][y]+V[x][y-1]);

                    }

                    else if (y==0){

                        Df[x][y]=(1/(pow(d,2)))*(V[x][y+1]+V[x-1][y]-4*V[x][y]+V[x+1][y]+V[x][y]);

                    }


                    else if (y==H){

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


        for (x=0;x<=W/2;x++){
            for (y=0;y<=H/2;y++){  //convert defect onto course grid

                if (!a[2*x][2*y]){

                    Df2[x][y]=Df[2*x][2*y];

                }

            }
        }

        for (m=0; m<=3;m++){
            for (x=0;x<=W/2;x++){
                for (y=0;y<=H/2;y++){  //calculate correction on course grid

                    if (!a[2*x][2*y]){

                        if ( x==0 ){

                            vf2[x][y]=0.25*((Df2[x][y]*(pow(2*d,2)))+vf2[x][y+1]+vf2[x][y]+vf2[x+1][y]+vf2[x][y-1]);

                        }

                        else if (x==W/2){

                            vf2[x][y]=0.25*((Df2[x][y]*(pow(2*d,2)))+vf2[x][y+1]+vf2[x-1][y]+vf2[x][y]+vf2[x][y-1]);

                        }

                        else if (y==0){

                            vf2[x][y]=0.25*((Df2[x][y]*(pow(2*d,2)))+vf2[x][y+1]+vf2[x-1][y]+vf2[x+1][y]+vf2[x][y]);

                        }

                        else if (y==H/2){

                            vf2[x][y]=0.25*((Df2[x][y]*(pow(2*d,2)))+vf2[x][y]+vf2[x-1][y]+vf2[x+1][y]+vf2[x][y-1]);

                        }

                        else {

                            vf2[x][y]=0.25*((Df2[x][y]*(pow(2*d,2)))+vf2[x][y+1]+vf2[x-1][y]+vf2[x+1][y]+vf2[x][y-1]);

                        }

                    }

                }
            }
        }

        for (x=0;x<=W/2;x++){
            for (y=0;y<=H/2;y++){  //calculate defect from correction calculation

                if (!a[2*x][2*y]){

                    if ( x==0 ){

                        Df3[x][y]=Df2[x][y]+(1/(pow(2*d,2)))*(vf2[x][y+1]+vf2[x][y]+vf2[x+1][y]+vf2[x][y-1]-4*vf2[x][y]);

                    }

                    else if (x==W/2){

                        Df3[x][y]=Df2[x][y]+(1/(pow(2*d,2)))*(vf2[x][y+1]+vf2[x-1][y]+vf2[x][y]+vf2[x][y-1]-4*vf2[x][y]);

                    }

                    else if (y==0){

                        Df3[x][y]=Df2[x][y]+(1/(pow(2*d,2)))*(vf2[x][y+1]+vf2[x-1][y]+vf2[x+1][y]+vf2[x][y]-4*vf2[x][y]);

                    }

                    else if (y==H/2){

                        Df3[x][y]=Df2[x][y]+(1/(pow(2*d,2)))*(vf2[x][y]+vf2[x-1][y]+vf2[x+1][y]+vf2[x][y-1]-4*vf2[x][y]);

                    }

                    else {

                        Df3[x][y]=Df2[x][y]+(1/(pow(2*d,2)))*(vf2[x][y+1]+vf2[x-1][y]+vf2[x+1][y]+vf2[x][y-1]-4*vf2[x][y]);

                    }

                }

            }
        }


        for (x=0;x<=W/4;x++){
            for (y=0;y<=H/4;y++){  //convert D3 onto courser grid

                if (!a[4*x][4*y]){

                    Df4[x][y]=Df3[2*x][2*y];

                }

            }
        }

        for (m=0; m<=5;m++){
            for (x=0;x<=W/4;x++){
                for (y=0;y<=H/4;y++){  //find correction in the correction on the 4*d grid using gauss siedel

                    if (!a[4*x][4*y]){

                        if ( x==0 ){

                            vf3[x][y]=0.25*((Df4[x][y]*(pow(4*d,2)))+vf3[x][y+1]+vf3[x][y]+vf3[x+1][y]+vf3[x][y-1]);

                        }

                        else if (x==W/4){

                            vf3[x][y]=0.25*((Df4[x][y]*(pow(4*d,2)))+vf3[x][y+1]+vf3[x-1][y]+vf3[x][y]+vf3[x][y-1]);

                        }

                        else if (y==0){

                            vf3[x][y]=0.25*((Df4[x][y]*(pow(4*d,2)))+vf3[x][y+1]+vf2[x-1][y]+vf3[x+1][y]+vf3[x][y]);

                        }

                        else if (y==H/4){

                            vf3[x][y]=0.25*((Df4[x][y]*(pow(4*d,2)))+vf3[x][y]+vf3[x-1][y]+vf3[x+1][y]+vf3[x][y-1]);

                        }

                        else {

                            vf3[x][y]=0.25*((Df4[x][y]*(pow(4*d,2)))+vf3[x][y+1]+vf3[x-1][y]+vf3[x+1][y]+vf3[x][y-1]);

                        }

                    }

                }
            }
        }

        for (x=0;x<=W/4;x++){
            for (y=0;y<=H/4;y++){  //calculate defect from correction of correction calculation

                if (!a[4*x][4*y]){

                    if ( x==0 ){

                        Df5[x][y]=Df4[x][y]+(1/(pow(4*d,2)))*(vf3[x][y+1]+vf3[x][y]+vf3[x+1][y]+vf3[x][y-1]-4*vf3[x][y]);

                    }

                    else if (x==W/4){

                        Df5[x][y]=Df4[x][y]+(1/(pow(4*d,2)))*(vf3[x][y+1]+vf3[x-1][y]+vf3[x][y]+vf3[x][y-1]-4*vf3[x][y]);

                    }

                    else if (y==0){

                        Df5[x][y]=Df4[x][y]+(1/(pow(4*d,2)))*(vf3[x][y+1]+vf3[x-1][y]+vf3[x+1][y]+vf3[x][y]-4*vf3[x][y]);

                    }

                    else if (y==H/4){

                        Df5[x][y]=Df4[x][y]+(1/(pow(4*d,2)))*(vf3[x][y]+vf3[x-1][y]+vf3[x+1][y]+vf3[x][y-1]-4*vf3[x][y]);

                    }

                    else {

                        Df5[x][y]=Df4[x][y]+(1/(pow(4*d,2)))*(vf3[x][y+1]+vf3[x-1][y]+vf3[x+1][y]+vf3[x][y-1]-4*vf3[x][y]);

                    }

                }

            }
        }

        for (x=0;x<=W/8;x++){
            for (y=0;y<=H/8;y++){  //convert Df5 onto courser grid

                if (!a[8*x][8*y]){

                    Df6[x][y]=Df5[2*x][2*y];

                }

            }
        }

        for (m=0; m<=5;m++){
            for (x=0;x<=W/8;x++){
                for (y=0;y<=H/8;y++){  //find correction in the correction of the correction on the coursest grid using gauss siedel

                    if (!a[8*x][8*y]){

                        if ( x==0 ){

                            vf4[x][y]=0.25*((Df6[x][y]*(pow(8*d,2)))+vf4[x][y+1]+vf4[x][y]+vf4[x+1][y]+vf4[x][y-1]);

                        }

                        else if (x==W/8){

                            vf4[x][y]=0.25*((Df6[x][y]*(pow(8*d,2)))+vf4[x][y+1]+vf4[x-1][y]+vf4[x][y]+vf4[x][y-1]);

                        }

                        else if (y==0){

                            vf4[x][y]=0.25*((Df6[x][y]*(pow(8*d,2)))+vf4[x][y+1]+vf4[x-1][y]+vf4[x+1][y]+vf4[x][y]);

                        }

                        else if (y==H/8){

                            vf4[x][y]=0.25*((Df6[x][y]*(pow(8*d,2)))+vf4[x][y]+vf4[x-1][y]+vf4[x+1][y]+vf4[x][y-1]);

                        }

                        else {

                            vf4[x][y]=0.25*((Df6[x][y]*(pow(8*d,2)))+vf4[x][y+1]+vf4[x-1][y]+vf4[x+1][y]+vf4[x][y-1]);

                        }

                    }

                }
            }
        }



        for (x=0;x<=W/8;x++){
            for (y=0;y<=H/8;y++){              //interpolate correction/correction/correction onto 4d grid, matching values

                if (!a[8*x][8*y]){

                    vf5[2*x][2*y]=vf4[x][y];

                }
            }
        }


        for (x=0;x<=W/4;x+=2){
            for (y=1;y<=H/4;y+=2){
                                        //interpolate correction/correction/correction onto 4d grid, even columns

                if (!a[4*x][4*y]){

                    if (y==H/4){

                        vf5[x][y]=vf5[x][y-1];
                    }

                    else {

                        vf5[x][y]=0.5*(vf5[x][y+1]+vf5[x][y-1]);

                    }
                }

            }
        }


        for (x=1;x<=W/4;x+=2){
            for (y=0;y<=H/4;y++){//interpolate correction/correction/correction onto 4*d grid, odd columns


                if (!a[4*x][4*y]){


                    if (x==W/4){

                        vf5[x][y]=vf5[x-1][y];

                    }


                    else {

                        vf5[x][y]=0.5*(vf5[x+1][y]+vf5[x-1][y]);

                    }

                }

            }
        }

        for (x=0;x<=W/4;x++){
            for (y=0;y<=H/4;y++){  //correcting the correction/correction
                if (!a[4*x][4*y]){

                    vf3[x][y]=vf3[x][y]+vf5[x][y];

                }

            }

        }


        for (m=0; m<=3;m++){
            for (x=0;x<=W/4;x++){
                for (y=0;y<=H/4;y++){  //smooth correction/correction on the 4*d grid using gauss siedel

                    if (!a[4*x][4*y]){

                        if ( x==0 ){

                            vf3[x][y]=0.25*((Df4[x][y]*(pow(4*d,2)))+vf3[x][y+1]+vf3[x][y]+vf3[x+1][y]+vf3[x][y-1]);

                        }

                        else if (x==W/4){

                            vf3[x][y]=0.25*((Df4[x][y]*(pow(4*d,2)))+vf3[x][y+1]+vf3[x-1][y]+vf3[x][y]+vf3[x][y-1]);

                        }

                        else if (y==0){

                            vf3[x][y]=0.25*((Df4[x][y]*(pow(4*d,2)))+vf3[x][y+1]+vf2[x-1][y]+vf3[x+1][y]+vf3[x][y]);

                        }

                        else if (y==H/4){

                            vf3[x][y]=0.25*((Df4[x][y]*(pow(4*d,2)))+vf3[x][y]+vf3[x-1][y]+vf3[x+1][y]+vf3[x][y-1]);

                        }

                        else {

                            vf3[x][y]=0.25*((Df4[x][y]*(pow(4*d,2)))+vf3[x][y+1]+vf3[x-1][y]+vf3[x+1][y]+vf3[x][y-1]);

                        }

                    }

                }
            }
        }


        for (x=0;x<=W/4;x++){
            for (y=0;y<=H/4;y++){                   //interpolate correction/correction onto 2*d grid, matching values

                if (!a[4*x][4*y]){

                    vf6[2*x][2*y]=vf3[x][y];

                }
            }
        }


        for (x=0;x<=W/2;x+=2){
            for (y=1;y<=H/2;y+=2){
                                        //interpolate correction/correction onto 2*d grid, even columns

                if (!a[2*x][2*y]){

                    if (y==H/2){

                        vf6[x][y]=vf6[x][y-1];
                    }

                    else {

                        vf6[x][y]=0.5*(vf6[x][y+1]+vf6[x][y-1]);

                    }
                }

            }
        }

        for (x=1;x<=W/2;x+=2){
            for (y=0;y<=H/2;y++){//interpolate correction/correction onto 2*d grid, odd columns



                if (!a[2*x][2*y]){


                    if (x==W/2){

                        vf6[x][y]=vf6[x-1][y];

                    }


                    else {

                        vf6[x][y]=0.5*(vf6[x+1][y]+vf6[x-1][y]);

                    }

                }

            }
        }

        for (x=0;x<=W/2;x++){
            for (y=0;y<=H/2;y++){  //correcting the correction
                if (!a[2*x][2*y]){

                    vf2[x][y]=vf2[x][y]+vf6[x][y];

                }

            }

        }


        for (m=0; m<=3;m++){
            for (x=0;x<=W/2;x++){
                for (y=0;y<=H/2;y++){  //smoothing the correction on the 2d grid

                    if (!a[2*x][2*y]){

                        if ( x==0 ){

                            vf2[x][y]=0.25*((Df2[x][y]*(pow(2*d,2)))+vf2[x][y+1]+vf2[x][y]+vf2[x+1][y]+vf2[x][y-1]);

                        }

                        else if (x==W/2){

                            vf2[x][y]=0.25*((Df2[x][y]*(pow(2*d,2)))+vf2[x][y+1]+vf2[x-1][y]+vf2[x][y]+vf2[x][y-1]);

                        }

                        else if (y==0){

                            vf2[x][y]=0.25*((Df2[x][y]*(pow(2*d,2)))+vf2[x][y+1]+vf2[x-1][y]+vf2[x+1][y]+vf2[x][y]);

                        }

                        else if (y==H/2){

                            vf2[x][y]=0.25*((Df2[x][y]*(pow(2*d,2)))+vf2[x][y]+vf2[x-1][y]+vf2[x+1][y]+vf2[x][y-1]);

                        }

                        else {

                            vf2[x][y]=0.25*((Df2[x][y]*(pow(2*d,2)))+vf2[x][y+1]+vf2[x-1][y]+vf2[x+1][y]+vf2[x][y-1]);

                        }

                    }

                }
            }
        }

        for (x=0;x<=W/2;x++){
            for (y=0;y<=H/2;y++){                   //interpolate correction onto fine grid, matching values

                if (!a[2*x][2*y]){

                    vf[2*x][2*y]=vf2[x][y];

                }
            }
        }


        for (x=0;x<=W;x+=2){
            for (y=1;y<=H;y+=2){
                //interpolate correction onto fine grid, even columns

                if (!a[x][y]){

                    if (y==H){

                        vf[x][y]=vf[x][y-1];
                    }

                    else {

                        vf[x][y]=0.5*(vf[x][y+1]+vf[x][y-1]);

                    }
                }

            }
        }

        for (x=1;x<=W;x+=2){
            for (y=0;y<=H;y++){//interpolate correction onto fine grid, odd columns


                if (!a[x][y]){


                    if (x==W){

                        vf[x][y]=vf[x-1][y];

                    }


                    else {

                        vf[x][y]=0.5*(vf[x+1][y]+vf[x-1][y]);

                    }

                }

            }
        }


        for (x=0;x<=W;x++){
            for (y=0;y<=H;y++){  //calculate final V values
                if (!a[x][y]){

                    V[x][y]=V[x][y]+vf[x][y];

                }

            }

        }

        //final smoothing using gauss-siedel


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

                      if (c3[x][y]){
                          compare3[l]=abs(V[x][y]);
                      }

                }
            }
        }
        }

        if ((abs(compare3[l-1]-compare3[l]))<=ET) {

               cout << "convergence after " << l << " iterations." << endl;
               break;
           }

           if (l==max_it){

               cout << "convergence not reached. " << endl;
           }


        l++;
    }



}


void fgr(double ET){



    QDesktopWidget dw;
        int W = (int)dw.width()*0.5;
        int H = (int)dw.height()*0.5;

    //input of variables from shell script

    clock_t t;
    t = clock();
    solf(W,H, ET);
    otpf(W,H);
    t = clock() - t;

    cout << "CPU time=" << (float)t/(CLOCKS_PER_SEC) <<"s." << endl;



}

void fgr1(int xgrid, int ygrid, double ET){





    //input of variables from shell script

    clock_t t;
    t = clock();
    solf(xgrid, ygrid, ET);
    otpf( xgrid, ygrid);
    t = clock() - t;

    cout << "CPU time=" << (float)t/(CLOCKS_PER_SEC) <<"s." << endl;



}



void otpf(int W, int H){

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
void fgre1(double ET){



    QDesktopWidget dw;
        int W = (int)dw.width()*0.5;
        int H = (int)dw.height()*0.5;

    //input of variables from shell script

    clock_t t;
    t = clock();
    solf(W,H, ET);
    otpfe1(W,H);
    t = clock() - t;

    cout << "CPU time=" << (float)t/(CLOCKS_PER_SEC) <<"s." << endl;
}

void otpfe1(int W, int H){
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

void fgre2(double ET){



    QDesktopWidget dw;
        int W = (int)dw.width()*0.5;
        int H = (int)dw.height()*0.5;


    //input of variables from shell script

    clock_t t;
    t = clock();
    solf(W,H, ET);
    otpfe2(W,H);
    t = clock() - t;

    cout << "CPU time=" << (float)t/(CLOCKS_PER_SEC) <<"s." << endl;
}

void otpfe2(int W, int H){
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

