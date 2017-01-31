#include <iostream>
#include <cmath>
#include <cstdlib>
#include "math.h"
#include "fstream"

using namespace std;

double V[1000][1000], D[1000][1000], v[1000][1000];
bool a[1000][1000];

void soln(double gridmax, double d, double a1, double b1,double r1, double V0){
    
    int x=0,y=0,m=0,l=0, h=gridmax/d, max_it=50;
    

    for (x=0;x<=h;x++){
        for (y=0;y<=h;y++){
         
            /*
            if ( pow((x*d-a1),2)+pow((y*d-b1),2) <= pow(r1,2) ){  //cycle through and evaluate boundaries
                
                V[x][y]=V0;
                a[x][y]=true;
            }
            */
            
             if (x==0){
                
                V[x][y]=V0;
                a[x][y]=true;
                
            }
           
            else if (y==0){
                
                V[x][y]=V0;
                a[x][y]=true;
                
            }
            
            else if (y==h){
                
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
            
            v[x][y]=0;
            
            
            
        }
    }
    
 //initial smoothing using gauss-siedel
    
    for (m=0; m<=3; m++){
        for (x=0;x<=h;x++){
            for (y=0;y<=h;y++){
                
                if (!a[x][y]){
                    
                    V[x][y]=0.25*(V[x+1][y]+V[x-1][y]+V[x][y+1]+V[x][y-1]);
                    
                }
                
                
            }
        }
    }
    
    
   
while ( l<=max_it ){
    
    for (x=0;x<=h;x++){
        for (y=0;y<=h;y++){
            
             if (!a[x][y]){  //find defect on fine grid
            
            D[x][y]=(1/(pow(d,2)))*(V[x][y+1]+V[x-1][y]-4*V[x][y]+V[x+1][y]+V[x][y-1]);
                 
             }
            
        }
    }
    

    for (x=0;x<=h;x+=2){
        for (y=0;y<=h;y+=2){  //convert defect onto course grid
           
            if (!a[x][y]){
            
            D[x][y]=0.5*D[x][y]+0.125*(D[x][y+2]+D[x-2][y]+D[x+2][y]+D[x][y-2]);
                
            }
            
        }
    }
    
        
for (m=0; m<=3; m++){
    for (x=0;x<=h;x+=2){
        for (y=0;y<=h;y+=2){  //calculate correction on course grid
            
       
         
            if (!a[x][y]){
                
                v[x][y]=0.25*((-D[x][y]*(pow(2*d,2)))+v[x][y+2]+v[x-2][y]+v[x+2][y]+v[x][y-2]);
                
            }
            
        }
    }
}
    
    
    for (x=0;x<=h;x++){
        for (y=0;y<=h;y++){  //interpolate correction onto fine grid
            
              if (!a[x][y]){
                  
                  v[x][y]=0.25*(v[2*(x-1)][2*(y+1)]+v[2*(x+1)][2*(y+1)]+v[2*(x-1)][2*(y-1)]+v[2*(x+1)][2*(y-1)])+0.5*(v[2*x][2*(y+1)]+v[2*(x-1)][2*y]+v[2*(x+1)][2*y]+v[2*x][2*(y-1)])+v[2*x][2*y];
             
                  V[x][y]=V[x][y]+v[x][y];
                  
              }
        }
    }
    
    
    for (m=0; m<=3; m++){
        for (x=0;x<=h;x++){
            for (y=0;y<=h;y++){
                
                if (!a[x][y]){
                    
                    V[x][y]=0.25*(V[x+1][y]+V[x-1][y]+V[x][y+1]+V[x][y-1]);
                    
                }
                
            }
        }
    }
    
    
        l++;
        cout << l << endl;
        
    }
    
    
 
    //final smoothing using gauss-siedel
    

    
    
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
    
    
    soln(gridmax,d,a1,b1,r1,V0);
    
    
    return 0;
    
}
