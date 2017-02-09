#include <iostream>
#include <cmath>
#include <cstdlib>
#include "math.h"
#include "fstream"

using namespace std;

/*
 
This script runs the full multigrid algorithm, with four different grids of spacing 8d, 4d, 2d, and d, where d
 is the grid spacing of the finest grid. There are functions for solving/smoothing the laplace equation on each grid, using Gauss siedel, functions for converting from each grid to the next coursest grid, and functoions for converting from each grid to the next finest grid. These functions are combined in the main function in a particular order (See numerical recipes) that defines the full multigrid algorithm. This script can be run, compiled and plotted by running the accompanying FMG.sh script. I could still do with editing slightyl to improve effeciency and accuracy, but this works fine.
 
 
 */

float V8[1000][1000],V4[1000][1000],V2[1000][1000], V[1000][1000];
bool a[1000][1000];
int m=0,x=0,y=0, i=0, j=0;

void bound(int gridmax, float d, float a1, float b1, float r1, float V0){
    
    for (x=0;x<=gridmax/d;x++){
        for (y=0;y<=gridmax/d;y++){
            
            //cycle through and evaluate boundaries, and converting to all grids
            
            if ( pow((x*d-a1),2)+pow((y*d-b1),2) <= pow(r1,2) ){
                
                V[x][y]=V0;
                
                i=0.5*x, j=0.5*y;
                
                V2[i][j]=V0;
                
                i=0.25*x, j=25*y;
                
                V4[i][j]=V0;
                
                i=0.125*x, j=0.125*y;
                
                V8[i][j]=V0;
                
                
                a[x][y]=true;
            }
            
            else if (x==0){
                
                V[x][y]=V0;
                V2[x][y]=V0;
                V4[x][y]=V0;
                V8[x][y]=V0;
                a[x][y]=true;
                
            }
            
            else if (y==0){
                
                V[x][y]=V0;
                V2[x][y]=V0;
                V4[x][y]=V0;
                V8[x][y]=V0;
                a[x][y]=true;
                
            }
            
            else if (y==gridmax/d){
                
                V[x][y]=V0;
                a[x][y]=true;
                
            }
            
            else if (x==gridmax/d){
                
                V[x][y]=V0;
                a[x][y]=true;
                
            }
            
            else if (x==gridmax/(2*d)){
                
                V2[x][y]=V0;
                
            }
            
            else if (y==gridmax/(2*d)){
                
                V2[x][y]=V0;
                
            }
            
            
            else if (x==gridmax/(4*d)){
                
                V4[x][y]=V0;
                
            }
            
            else if (y==gridmax/(4*d)){
                
                V4[x][y]=V0;
                
            }
            
            else if (x==gridmax/(8*d)){
                
                V8[x][y]=V0;
                
            }
            
            else if (y==gridmax/(8*d)){
                
                V8[x][y]=V0;
                
            }
            
            else {
                
                
                a[x][y]=false;
                
                
            }
            
        }
    }
    
    
    
    for (x=0;x<=gridmax/(8*d);x++){
        for (y=0;y<=gridmax/(8*d);y++){
            
            if (!a[8*x][8*y]){
                
                V8[x][y]=0; //set all points on initial grid to zero
                
            }
        }
    }
}


void smooth8(int gridmax, float d){  //smoothing function for the coursest grid, grid-width 8*d
    
    for (m=0; m<=3; m++){
        for (x=0;x<=gridmax/(8*d);x++){
            for (y=0;y<=gridmax/(8*d);y++){  //using G-S to solve on the coursest grid
                
                if (!a[8*x][8*y]){
                    
                    if (x==gridmax/(8*d)){    //making approximations at boundaries
                        
                     V8[x][y]=0.25*(V8[x][y+1]+V8[x-1][y]+V8[x][y]+V8[x][y-1]);
                        
                    }
                    
                    else if (y==gridmax/(8*d)){
                        
                     V8[x][y]=0.25*(V8[x][y]+V8[x-1][y]+V8[x+1][y]+V8[x][y-1]);
                        
                    }
                    
                    else if (y==0){
                        
                    V8[x][y]=0.25*(V8[x][y+1]+V8[x-1][y]+V8[x+1][y]+V8[x][y]);
                        
                    }
        
                    else if (x==0){
                        
                        V8[x][y]=0.25*(V8[x][y+1]+V8[x][y]+V8[x+1][y]+V8[x][y-1]);
                        
                    }
                    
                    else { //if we're not at boundaries, use standard G-S
                    
                    V8[x][y]=0.25*(V8[x][y+1]+V8[x-1][y]+V8[x+1][y]+V8[x][y-1]);
                        
                    }
                    
                }
                
            }
        }
    }
}


void smooth4(int gridmax, float d){  //smoothing function for the second-coursest grid, grid-width 4*d
    
    for (m=0; m<=3; m++){
        for (x=0;x<=gridmax/(4*d);x++){
            for (y=0;y<=gridmax/(4*d);y++){  //using G-S to solve on the second-coursest grid
                
                if (!a[4*x][4*y]){
                    
                    if (x==gridmax/(4*d)){    //making approximations at boundaries
                        
                        V4[x][y]=0.25*(V4[x][y+1]+V4[x-1][y]+V4[x][y]+V4[x][y-1]);
                        
                    }
                    
                    else if (y==gridmax/(4*d)){
                        
                        V4[x][y]=0.25*(V4[x][y]+V4[x-1][y]+V4[x+1][y]+V4[x][y-1]);
                        
                    }
                    
                    else if (y==0){
                        
                        V4[x][y]=0.25*(V4[x][y+1]+V4[x-1][y]+V4[x+1][y]+V4[x][y]);
                        
                    }
                    
                    else if (x==0){
                        
                        V4[x][y]=0.25*(V4[x][y+1]+V4[x][y]+V4[x+1][y]+V4[x][y-1]);
                        
                    }
                    
                    else {  //if we're not at boundaries, use standard G-S
                        
                        V4[x][y]=0.25*(V4[x][y+1]+V4[x-1][y]+V4[x+1][y]+V4[x][y-1]);
                        
                    }
                }
                
            }
        }
    }
}

void smooth2(int gridmax, float d){  //smoothing function for the third-coursest grid, grid-width 2*d
    
    for (m=0; m<=3; m++){
        for (x=0;x<=gridmax/(2*d);x++){
            for (y=0;y<=gridmax/(2*d);y++){  //using G-S to solve on the third-coursest grid
                
                if (!a[2*x][2*y]){
                    
                    if (x==gridmax/(2*d)){    //making approximations at boundaries
                        
                        V2[x][y]=0.25*(V2[x][y+1]+V2[x-1][y]+V2[x][y]+V2[x][y-1]);
                        
                    }
                    
                    else if (y==gridmax/(2*d)){
                        
                        V2[x][y]=0.25*(V2[x][y]+V2[x-1][y]+V2[x+1][y]+V2[x][y-1]);
                        
                    }
                    
                    else if (y==0){
                        
                        V2[x][y]=0.25*(V2[x][y+1]+V2[x-1][y]+V2[x+1][y]+V2[x][y]);
                        
                    }
                    
                    else if (x==0){
                        
                        V2[x][y]=0.25*(V2[x][y+1]+V2[x][y]+V2[x+1][y]+V2[x][y-1]);
                        
                    }
                    
                    else { //if we're not at boundaries, use standard G-S
                        
                        V2[x][y]=0.25*(V2[x][y+1]+V2[x-1][y]+V2[x+1][y]+V2[x][y-1]);
                        
                    }
                }
                
            }
        }
    }
}

void smooth1(int gridmax, float d){  //smoothing function for the finest grid, grid-width d
    
    for (m=0; m<=3; m++){
        for (x=0;x<=gridmax/d;x++){
            for (y=0;y<=gridmax/d;y++){  //using G-S to solve on the finest grid
                
                if (!a[x][y]){
                    
                    
                    if (x==gridmax/d){    //making approximations at boundaries
                        
                        V[x][y]=0.25*(V[x][y+1]+V[x-1][y]+V[x][y]+V[x][y-1]);
                        
                    }
                    
                    else if (y==gridmax/d){
                        
                        V[x][y]=0.25*(V[x][y]+V[x-1][y]+V[x+1][y]+V[x][y-1]);
                        
                    }
                    
                    else if (y==0){
                        
                        V[x][y]=0.25*(V[x][y+1]+V[x-1][y]+V[x+1][y]+V[x][y]);
                        
                    }
                    
                    else if (x==0){
                        
                        V[x][y]=0.25*(V[x][y+1]+V[x][y]+V[x+1][y]+V[x][y-1]);
                        
                    }
                    
                    else { //if we're not at boundaries, use standard G-S
                        
                        V[x][y]=0.25*(V[x][y+1]+V[x-1][y]+V[x+1][y]+V[x][y-1]);
                        
                    }
                }
                
            }
        }
    }
}


void inject48(int gridmax, float d){  //function for injecting values from 4d grid to 8d grid
    
    for (x=0;x<=gridmax/(8*d);x++){
        for (y=0;y<=gridmax/(8*d);y++){  //convert potential onto courser grid
            
            if (!a[8*x][8*y]){
                
                V8[x][y]=V4[2*x][2*y];
                
            }
            
        }
    }
    
}

void inject24(int gridmax, float d){  //function for injecting values from 2d grid to 4d grid
    
    for (x=0;x<=gridmax/(4*d);x++){
        for (y=0;y<=gridmax/(4*d);y++){  //convert potential onto courser grid
            
            if (!a[4*x][4*y]){
                
                V4[x][y]=V2[2*x][2*y];
                
            }
            
        }
    }
    
}

void inject12(int gridmax, float d){  //function for injecting values from 1d grid to 2d grid
    
    for (x=0;x<=gridmax/(2*d);x++){
        for (y=0;y<=gridmax/(2*d);y++){  //convert defect onto courser grid
            
            if (!a[4*x][4*y]){
                
                V2[x][y]=V[2*x][2*y];
                
            }
            
        }
    }
    
}

void inter84(int gridmax, float d){  //function for interpolating values from 8d grid to 4d grid
    
    for (x=0;x<=gridmax/(8*d);x++){
        for (y=0;y<=gridmax/(8*d);y++){  //convert matching values
            
            if (!a[8*x][8*y]){
                
                V4[2*x][2*y]=V8[x][y];
                
            }
            
        }
    }
    
          //interpolate potential onto finer grid, even columns
    
    for (x=0;x<=gridmax/(4*d);x+=2){
        for (y=1;y<=gridmax/(4*d);y+=2){
    
            
            if (!a[4*x][4*y]){
                
                
                V4[x][y]=0.5*(V4[x][y+1]+V4[x][y-1]);
                
            }
            
        }
    }
    //interpolate potential onto finer grid, odd columns
    
    for (x=1;x<=gridmax/(4*d);x+=2){
        for (y=0;y<=gridmax/(4*d);y++){
            
            
            if (!a[4*x][4*y]){
                
                V4[x][y]=0.5*(V4[x+1][y]+V4[x-1][y]);
                
            }
            
        }
    }
    
    
}


void inter42(int gridmax, float d){  //function for interpolating values from 8d grid to 4d grid
    
    for (x=0;x<=gridmax/(4*d);x++){
        for (y=0;y<=gridmax/(4*d);y++){  //convert matching values
            
            if (!a[4*x][4*y]){
                
                V2[2*x][2*y]=V4[x][y];
                
            }
            
        }
    }
    
    //interpolate potential onto finer grid, even columns
    
    for (x=0;x<=gridmax/(2*d);x+=2){
        for (y=1;y<=gridmax/(2*d);y+=2){
          
            
            
            if (!a[2*x][2*y]){
                
                V2[x][y]=0.5*(V2[x][y+1]+V2[x][y-1]);
                
            }
            
        }
    }
    
    //interpolate potential onto finer grid, odd columns
    
    for (x=1;x<=gridmax/(2*d);x+=2){
        for (y=0;y<=gridmax/(2*d);y++){
            
            
            if (!a[2*x][2*y]){
                
                V2[x][y]=0.5*(V2[x+1][y]+V2[x-1][y]);
                
            }
            
        }
    }
    
    
}

void inter21(int gridmax, float d){  //function for interpolating values from 8d grid to 4d grid
    
    for (x=0;x<=gridmax/(2*d);x++){
        for (y=0;y<=gridmax/(2*d);y++){  //convert matching values
            
            if (!a[2*x][2*y]){
                
                V[2*x][2*y]=V2[x][y];
                
            }
            
        }
    }
    
    for (x=0;x<=gridmax/d;x+=2){
        for (y=1;y<=gridmax/d;y+=2){
            //interpolate potential onto finest grid, even columns
            
            
            if (!a[x][y]){
                
                V[x][y]=0.5*(V[x][y+1]+V[x][y-1]);
                
            }
            
        }
    }
    
    for (x=1;x<=gridmax/d;x+=2){
        for (y=0;y<=gridmax/d;y++){//interpolate potential onto finest grid, odd columns
            
            
            if (!a[x][y]){
                
                V[x][y]=0.5*(V[x+1][y]+V[x-1][y]);
                
            }
            
        }
    }
    
    
}



int main(){
    
    float d, a1, b1, r1, V0;
    int gridmax;
    
    cin >> gridmax;
    cin >> d;
    cin >> a1;
    cin >> b1;
    cin >> r1;
    cin >> V0;
    
    bound(gridmax, d, a1, b1, r1, V0);
    
//run functions in order to build full multi-grid algorithm
    
    smooth8(gridmax, d);
    inter84(gridmax, d);
    smooth4(gridmax, d);
    inject48(gridmax, d);
    smooth8(gridmax, d);
    inter84(gridmax, d);
    smooth4(gridmax, d);
    inter42(gridmax, d);
    smooth2(gridmax, d);
    inject24(gridmax, d);
    smooth4(gridmax, d);
    inject48(gridmax, d);
    smooth8(gridmax, d);
    inter84(gridmax, d);
    smooth4(gridmax, d);
    inter42(gridmax, d);
    smooth2(gridmax, d);
    inter21(gridmax, d);
    smooth1(gridmax, d);
    inject12(gridmax, d);
    smooth2(gridmax, d);
    inject24(gridmax, d);
    smooth4(gridmax, d);
    inject48(gridmax, d);
    smooth8(gridmax, d);
    inter84(gridmax, d);
    smooth4(gridmax, d);
    inter42(gridmax, d);
    smooth2(gridmax, d);
    inter21(gridmax, d);
    smooth1(gridmax, d);
    
    
    ofstream file;
    file.open("FMG2.dat");
    
    //output to file for plotting
    
    
    for (x=0; x<=gridmax/d; x++){
        for (y=0; y<=gridmax/d; y++){
            
            file << (x*d) << "      "<< (y*d) << "    " <<  V[x][y] << "\n";
            
        }
        
        file << "\n";
    }
    
    
    file.close();
    
    return 0;
}

