#include <iostream>
#include <cmath>
#include <cstdlib>
#include "math.h"
#include "fstream"
#include <time.h>
#include <ctime>

using namespace std;

double V[1000][1000], D[1000][1000], Dc[1000][1000], v[1000][1000], vc[1000][1000];
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
                
                vc[x][y]=0;
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
                    
                    V[x][y]=V[x][y]+v[x][y];
                   
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
    
    

    //output all the final V values for all x & y  to a file for plotting
    
    
    ofstream file;
    file.open("two_grid.dat");
    
    
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
