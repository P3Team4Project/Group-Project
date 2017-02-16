#include <iostream>
#include <cmath>
#include <cstdlib>
#include "math.h"
#include "fstream"
#include <time.h>
#include <ctime>

using namespace std;

double V[1000][1000], D[1000][1000], D2[1000][1000],D3[1000][1000],D4[1000][1000],D5[1000][1000],D6[1000][1000], v[1000][1000], v2[1000][1000],v3[1000][1000],v4[1000][1000],v5[1000][1000],v6[1000][1000];
bool a[1000][1000];


void soln(double gridmax, double d,  double a1, double b1,double r1, double V0){
    
    int x=0,y=0,m=0,l=0, h=gridmax/d, max_it=100;
    
    for (x=0;x<=h;x++){
        for (y=0;y<=h;y++){
            
            
            if ( pow((x*d-a1),2)+pow((y*d-b1),2) <= pow(r1,2) ){  //cycle through and evaluate boundaries
                
                V[x][y]=V0;
                a[x][y]=true;
                
            }
            
            
            else if (x==0){
                
                V[x][y]=V0;
                a[x][y]=true;
                
            }
            
            
            else if (x==h){
                
                V[x][y]=V0;
                a[x][y]=true;
                
            }
            
            
            else {
                
                V[x][y]=0;
                a[x][y]=false;
                
                
            }
            
            
            v2[x][y]=0;
            v[x][y]=0;  //initialise everything else to zero
            D[x][y]=0;
            D2[x][y]=0;
            
            
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
                
                v2[x][y]=0;
                v3[x][y]=0;
                v4[x][y]=0;  //initialise corrections to zero at the start of each loop
                v5[x][y]=0;
                v6[x][y]=0;
                
            }
        }
        
        
        for (x=0;x<=h/2;x++){
            for (y=0;y<=h/2;y++){  //convert defect onto course grid
                
                if (!a[2*x][2*y]){
                    
                    D2[x][y]=D[2*x][2*y];
                    
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
                for (y=0;y<=h/4;y++){  //find correction in the correction on the 4*d grid using gauss siedel
                    
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
            for (y=0;y<=h/4;y++){  //calculate defect from correction of correction calculation
                
                if (!a[4*x][4*y]){
                    
                    if ( x==0 ){
                        
                        D5[x][y]=D4[x][y]+(1/(pow(4*d,2)))*(v3[x][y+1]+v3[x][y]+v3[x+1][y]+v3[x][y-1]-4*v3[x][y]);
                        
                    }
                    
                    else if (x==h/4){
                        
                        D5[x][y]=D4[x][y]+(1/(pow(4*d,2)))*(v3[x][y+1]+v3[x-1][y]+v3[x][y]+v3[x][y-1]-4*v3[x][y]);
                        
                    }
                    
                    else if (y==0){
                        
                        D5[x][y]=D4[x][y]+(1/(pow(4*d,2)))*(v3[x][y+1]+v3[x-1][y]+v3[x+1][y]+v3[x][y]-4*v3[x][y]);
                        
                    }
                    
                    else if (y==h/4){
                        
                        D5[x][y]=D4[x][y]+(1/(pow(4*d,2)))*(v3[x][y]+v3[x-1][y]+v3[x+1][y]+v3[x][y-1]-4*v3[x][y]);
                        
                    }
                    
                    else {
                        
                        D5[x][y]=D4[x][y]+(1/(pow(4*d,2)))*(v3[x][y+1]+v3[x-1][y]+v3[x+1][y]+v3[x][y-1]-4*v3[x][y]);
                        
                    }
                    
                }
                
            }
        }
        
        for (x=0;x<=h/8;x++){
            for (y=0;y<=h/8;y++){  //convert D5 onto courser grid
                
                if (!a[8*x][8*y]){
                    
                    D6[x][y]=D5[2*x][2*y];
                    
                }
                
            }
        }
        
        for (m=0; m<=5;m++){
            for (x=0;x<=h/8;x++){
                for (y=0;y<=h/8;y++){  //find correction in the correction of the correction on the coursest grid using gauss siedel
                    
                    if (!a[8*x][8*y]){
                        
                        if ( x==0 ){
                            
                            v4[x][y]=0.25*((D6[x][y]*(pow(8*d,2)))+v4[x][y+1]+v4[x][y]+v4[x+1][y]+v4[x][y-1]);
                            
                        }
                        
                        else if (x==h/8){
                            
                            v4[x][y]=0.25*((D6[x][y]*(pow(8*d,2)))+v4[x][y+1]+v4[x-1][y]+v4[x][y]+v4[x][y-1]);
                            
                        }
                        
                        else if (y==0){
                            
                            v4[x][y]=0.25*((D6[x][y]*(pow(8*d,2)))+v4[x][y+1]+v4[x-1][y]+v4[x+1][y]+v4[x][y]);
                            
                        }
                        
                        else if (y==h/8){
                            
                            v4[x][y]=0.25*((D6[x][y]*(pow(8*d,2)))+v4[x][y]+v4[x-1][y]+v4[x+1][y]+v4[x][y-1]);
                            
                        }
                        
                        else {
                            
                            v4[x][y]=0.25*((D6[x][y]*(pow(8*d,2)))+v4[x][y+1]+v4[x-1][y]+v4[x+1][y]+v4[x][y-1]);
                            
                        }
                        
                    }
                    
                }
            }
        }
        
        
        
        for (y=0;y<=h/8;y++){
            for (x=0;x<=h/8;x++){              //interpolate correction/correction/correction onto 4d grid, matching values
                
                if (!a[8*x][8*y]){
                    
                    v5[2*x][2*y]=v4[x][y];
                    
                }
            }
        }
        
        
        for (x=0;x<=h/4;x+=2){
            for (y=1;y<=h/4;y+=2){
                                        //interpolate correction/correction/correction onto 4d grid, even columns
                
                if (!a[4*x][4*y]){
                    
                    if (y==h/4){
                        
                        v5[x][y]=v5[x][y-1];
                    }
                    
                    else {
                        
                        v5[x][y]=0.5*(v5[x][y+1]+v5[x][y-1]);
                        
                    }
                }
                
            }
        }
        
        
        for (x=1;x<=h/4;x+=2){
            for (y=0;y<=h/4;y++){//interpolate correction/correction/correction onto 4*d grid, odd columns
                
                
                if (!a[4*x][4*y]){
                    
                    
                    if (x==h/4){
                        
                        v5[x][y]=v5[x-1][y];
                        
                    }
                    
                    
                    else {
                        
                        v5[x][y]=0.5*(v5[x+1][y]+v5[x-1][y]);
                        
                    }
                    
                }
                
            }
        }
        
        for (x=0;x<=h/4;x++){
            for (y=0;y<=h/4;y++){  //correcting the correction/correction
                if (!a[4*x][4*y]){
                    
                    v3[x][y]=v3[x][y]+v5[x][y];
                    
                }
                
            }
            
        }
        
        
        for (m=0; m<=3;m++){
            for (x=0;x<=h/4;x++){
                for (y=0;y<=h/4;y++){  //smooth correction/correction on the 4*d grid using gauss siedel
                    
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
        
        
        for (y=0;y<=h/4;y++){
            for (x=0;x<=h/4;x++){                   //interpolate correction/correction onto 2*d grid, matching values
                
                if (!a[4*x][4*y]){
                    
                    v6[2*x][2*y]=v3[x][y];
                    
                }
            }
        }
        
        
        for (x=0;x<=h/2;x+=2){
            for (y=1;y<=h/2;y+=2){
                                        //interpolate correction/correction onto 2*d grid, even columns
                
                if (!a[2*x][2*y]){
                    
                    if (y==h/2){
                        
                        v6[x][y]=v6[x][y-1];
                    }
                    
                    else {
                        
                        v6[x][y]=0.5*(v6[x][y+1]+v6[x][y-1]);
                        
                    }
                }
                
            }
        }
        
        for (x=1;x<=h/2;x+=2){
            for (y=0;y<=h/2;y++){//interpolate correction/correction onto 2*d grid, odd columns
                
                
                
                if (!a[2*x][2*y]){
                    
                    
                    if (x==h/2){
                        
                        v6[x][y]=v6[x-1][y];
                        
                    }
                    
                    
                    else {
                        
                        v6[x][y]=0.5*(v6[x+1][y]+v6[x-1][y]);
                        
                    }
                    
                }
                
            }
        }
        
        for (x=0;x<=h/2;x++){
            for (y=0;y<=h/2;y++){  //correcting the correction
                if (!a[2*x][2*y]){
                    
                    v2[x][y]=v2[x][y]+v6[x][y];
                    
                }
                
            }
            
        }
        
        
        for (m=0; m<=3;m++){
            for (x=0;x<=h/2;x++){
                for (y=0;y<=h/2;y++){  //smoothing the correction on the 2d grid
                    
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
        
        for (y=0;y<=h/2;y++){
            for (x=0;x<=h/2;x++){                   //interpolate correction onto fine grid, matching values
                
                if (!a[2*x][2*y]){
                    
                    v[2*x][2*y]=v2[x][y];
                    
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
                    
                    V[x][y]=V[x][y]+v[x][y];
                    
                }
                
            }
            
        }
        
        //final smoothing using gauss-siedel
        
        
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
        
        l++;
    }
    
    
    
    //output all the final V values for all x & y  to a file for plotting
    
    
    ofstream file;
    file.open("4grid.dat");
    
    
    for (x=0; x<=h; x++){
        for (y=0; y<=h; y++){
            
            file << (x*d) << "      "<< (y*d) << "    " <<  V[x][y] << "\n";
            
        }
        
        file << "\n";
    }
    
    file.close();
    
}

int main(){
    
    double gridmax, d, a1, b1, r1, V0;
    
    
    cin >> gridmax;
    cin >> d;
    cin >> a1;
    cin >> b1;
    cin >> r1;
    cin >> V0;
    
    //input of variables from shell script
    
    clock_t t;
    t = clock();
    soln(gridmax,d,a1,b1,r1,V0);
    t = clock() - t;
    
    cout << "CPU time=" << (float)t/(CLOCKS_PER_SEC) <<"s." << endl;
    
    
    
    
    return 0;
    
}
