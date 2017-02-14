#include <iostream>
#include <cmath>
#include <cstdlib>
#include "math.h"
#include "fstream"

using namespace std;

double V[1000][1000];

bool a[1000][1000];

/*script for running the gauss-siedel method, fairly self explanatory */


void soln(double gridmax, double d, double a1, double b1,double r1, double V0){
    
    int x=0,y=0,m=0,it=0, m_it=0;
    
    it=gridmax/d;
    
    //max number of iterations, this will not be needed when it has been cut out at convergence
    
    m_it=10000;
    
    for (x=0;x<=it;x++){
        for (y=0;y<=it;y++){
            
            if ( pow((x*d-a1),2)+pow((y*d-b1),2) <= pow(r1,2) ){  //if we're in the inner circle, v=0
                
                V[x][y]=0;
                a[x][y]=true;
            }
            
            else if ( x==0  ){  //if we're outwith the outer circle, v=0
                
                V[x][y]=-V0;
                 a[x][y]=true;
            }
            
            else if ( x==it ){  //if we're outwith the outer circle, v=0
                
                V[x][y]=V0;
                 a[x][y]=true;
            }
            
            else {
                
                V[x][y]=0;
                a[x][y]=false;
                
            }
            
            
        }
    }
    
    //evaluate every other x & y value apart from the boundary conditions at all times after 0
    
    for (m=0;m<=m_it;m++){
        for (x=0;x<=it;x++){
            for (y=0;y<=it;y++){
                
                if (!a[x][y]){
                
                if ( x==0 ){
                    
                     V[x][y]=0.25*(V[x+1][y]+V[x][y]+V[x][y+1]+V[x][y-1]);
                    
                }
                    
                else if (x==it){
                    
                    V[x][y]=0.25*(V[x][y]+V[x-1][y]+V[x][y+1]+V[x][y-1]);
                    
                }
                    
                else if (y==0){
                    
                    V[x][y]=0.25*(V[x+1][y]+V[x-1][y]+V[x][y+1]+V[x][y]);
                    
                    }
                    
                    
                else if (y==it){
                    
                    V[x][y]=0.25*(V[x+1][y]+V[x-1][y]+V[x][y]+V[x][y-1]);
                    
                }

                
                else {
                    
                    V[x][y]=0.25*(V[x+1][y]+V[x-1][y]+V[x][y+1]+V[x][y-1]);
                    
                }
               
                }
            }
        }
    }
    
    //output all the final V values for all x & y  to a file for plotting
    
    
    ofstream file;
    file.open("GS.dat");

    for (x=0; x<=it; x++){
        for (y=0; y<=it; y++){
            
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
