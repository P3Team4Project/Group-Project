#include <iostream>
#include <math.h>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <cstring>


using namespace std;

bool a[1000][1000];
bool b[1000][1000];
double e[1000][1000],V[1000][1000],Grad[1000][1000], compare[100000], w=1.3, d=0.1, a1, b1, r1, a2, b2, r2, V0,  err_tol=0.00001;

/*This script uses the SOR method to solve laplaces equation. it is run using the shell script "plot4.sh".
 This is an updated version of SOR.cpp that had issues at boundaries, where boundaries that were not set by the
 user were assumed to be zero for all iterations. This was solved by using an approximation of the finite difference scheme when the unset boundaries are reached. This still isn't ideal for certain situations but we'll try to improve on it. At the moment, this script simply let the user set an unlimited number of circles at different potentials, and doesn't allow the user to set other shapes, or conditions at the boundaries. This would be simple to change but there's not much point if we're not having our final program run from the terminal. So, this script was pretty much to test the SOR method and sort out the boundary issues.
 */
int main(){
    
    int i, j, m, p, n, jmax, gridmax=50;
    int maxit = 100000;
    
    
    cin >> a1;
    cin >> b1;
    cin >> r1;
    cin >> a2;
    cin >> b2;
    cin >> r2;
    cin >> V0;
    
    
    
    
    
    //jmax is the number of iterations of size d needed to sweep through our grid
    
    jmax=gridmax/d;
    
    
    
    for (i=0;i<=jmax;i++){
        for (j=0;j<=jmax;j++){
            
            
            if ( pow((i*d-a1),2)+pow((j*d-b1),2) <= pow(r1,2) ){  //cycle through and evaluate boundaries
                
                V[i][j]=0;
                a[i][j]=true;
                
            }
            
            
            else if (i==jmax){
                
                V[i][j]=-V0;
                a[i][j]=true;
                
            }
            
            else if (i==0){
                
                V[i][j]=V0;
                a[i][j]=true;
                
            }
            
            
            else {
                
                V[i][j]=0;
                a[i][j]=false;
                
                
            }
            
            
            
        }
    }
    //evaluating  boundaries
    
    
    
    //evaluating all u apart from boundaries using SOR
    
    
    for (int f=0; f<=3; f++) {
        for (i=0; i<=jmax; i++){
            for (j=0; j<=jmax; j++){
                
                //if a boundary has been set, do nothing a[i][j]==true
                
                
                if ( a[i][j] ){
                    
                }
                
                //if  border condition hasn't been specified, make an approximation so that they aren't constantly zero
                
                else if (j==0){
                    e[i][j]=V[i+1][j]+V[i-1][j]+V[i][j+1]+V[i][j]-4*V[i][j];
                    V[i][j]=V[i][j]+0.25*w*e[i][j];
                    
                    
                }
                
                else if (j==jmax){
                    e[i][j]=V[i+1][j]+V[i-1][j]+V[i][j]+V[i][j-1]-4*V[i][j];
                    V[i][j]=V[i][j]+0.25*w*e[i][j];
                    
                    
                }
                
                else if (i==0){
                    e[i][j]=V[i+1][j]+V[i][j]+V[i][j+1]+V[i][j-1]-4*V[i][j];
                    V[i][j]=V[i][j]+0.25*w*e[i][j];
                    
                    
                }
                
                else if (i==jmax){
                    e[i][j]=V[i][j]+V[i-1][j]+V[i][j+1]+V[i][j-1]-4*V[i][j];
                    V[i][j]=V[i][j]+0.25*w*e[i][j];
                    
                    
                }
                
                //evaluate all other points using normal finite difference scheme
                
                else {
                    
                    
                    e[i][j]=V[i+1][j]+V[i-1][j]+V[i][j+1]+V[i][j-1]-4*V[i][j];  //calculation of residual
                    
                    
                    V[i][j]=V[i][j]+0.25*w*e[i][j];  //evaluate using SOR
                    
                    
                    
                }
                
                
            }
        }
    }
    
    for (i=0; i<=jmax; i++){
        for (j=0; j<=jmax; j++){
            
            //  cout << V[i+1][j] << "    " << V[i-1][j] << endl;
            
            if (!a[i][j]){
                
                
                double Ex =  0.5*(V[i+1][j]-V[i-1][j]);
                double Ey =  0.5*(V[i][j+1]-V[i][j-1]);
                
                // cout << Ex << "   " << Ey << endl;
                
                
                Grad[i][j] = sqrt( pow(Ex, 2) + pow(Ey, 2));
                
                //cout << Grad[i][j] << endl;
                
            }
        }
    }
    
    
    
    
    // cout << Grad[500][500] << endl;
    //fix fix
    float maximum = 0;
    int k1 = 0;
    int k2 = 0;
    for (i=0; i<=jmax; i++){
        for (j=0; j<=jmax; j++){
            
            b[i][j]=false;
            
            if (Grad[i][j]>maximum) {
                maximum = Grad[i][j];
                k1 = i;
                k2 = j;
            }
            
        }
    }
    //assign space ij in Grad to b
    
    b[k1][k2] = true;
    /////////
    
    
    
    while (m<=maxit){
        for (i=0; i<=jmax; i++){
            for (j=0; j<=jmax; j++){
                
                //if a boundary has been set, do nothing a[i][j]==true
                
                
                if (!a[i][j]){
                    
                    //if  border condition hasn't been specified, make an approximation so that they aren't constantly zero
                    
                    if (j==0){
                        e[i][j]=V[i+1][j]+V[i-1][j]+V[i][j+1]+V[i][j]-4*V[i][j];
                        V[i][j]=V[i][j]+0.25*w*e[i][j];
                        
                        
                    }
                    
                    else if (j==jmax){
                        e[i][j]=V[i+1][j]+V[i-1][j]+V[i][j]+V[i][j-1]-4*V[i][j];
                        V[i][j]=V[i][j]+0.25*w*e[i][j];
                        
                        
                    }
                    
                    else if (i==0){
                        e[i][j]=V[i+1][j]+V[i][j]+V[i][j+1]+V[i][j-1]-4*V[i][j];
                        V[i][j]=V[i][j]+0.25*w*e[i][j];
                        
                        
                    }
                    
                    else if (i==jmax){
                        e[i][j]=V[i][j]+V[i-1][j]+V[i][j+1]+V[i][j-1]-4*V[i][j];
                        V[i][j]=V[i][j]+0.25*w*e[i][j];
                        
                        
                    }
                    
                    //evaluate all other points using normal finite difference scheme
                    
                    else {
                        
                        
                        e[i][j]=V[i+1][j]+V[i-1][j]+V[i][j+1]+V[i][j-1]-4*V[i][j];  //calculation of residual
                        
                        
                        V[i][j]=V[i][j]+0.25*w*e[i][j];  //evaluate using SOR
                        
                        
                        
                        
                    }
                    
                    if (b[i][j]) {
                        
                        
                        
                        
                        compare[m]= abs(V[i][j]);
                        
                    }
                    
                }
                
                
            }
        }
        
        //COMPARISON HERE
        //when relative error small, stop
        if ((abs(compare[m-1]-compare[m]))<=err_tol) {
            
            cout << "convergence after " << m << " iterations." << endl;
            break;
        }
        
        if (m==maxit){
            
            cout << "convergence not reached. " << endl;
        }
        
        m++;
        
    }
    
    
    //*****************************************************************
    
    //output of final data to a file for plotting
    
    ofstream file;
    file.open("draft4.dat");
    
    
    for (int i=0; i<=jmax; i++){
        for (int j=0; j<=jmax; j++){
            
           file << (i*d) << "      "<< (j*d) << "    " <<  V[i][j] << "\n";
            
        }
        file << "\n";
    }
    
    
    file.close();
    

    
    
    
    
    return 0;
    
}
