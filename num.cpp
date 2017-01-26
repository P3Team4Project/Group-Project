    //output of final data to a file for plotting

#include "dec.h"

int num(){

int i, j, imax, jmax, m , maxit=5000;
float V[1000][1000], w=1.3, d=0.1;   

//use functions to get dimensions of image
imax=im();
jmax=jm(); 
  
 //opens image      
  BMP I;
I.ReadFromFile("test3.bmp");

    //set all coordinates to false initially
     for (i=0; i<jmax; i++){
        for (j=0; j<jmax; j++){
            a[i][j]=false;
        }
    }
    
    
	//gives inputed values to matrice row by row by checking what the colour of a pixel is and associating a voltage to that colour, also sets the coordinate to true to avoid re-estmating the value at the coordinate
	for (i=0 ; i <imax ; i++) {
		for (j=0 ; j <jmax ; j++ ){			
			if((float) I(i,j)->Red==0){
			V[i][j]=0;
			a[i][j]=true;
			}
			else if((float) I(i,j)->Red==32){
			V[i][j]=0.7;
			a[i][j]=true;
			}
			else if((float) I(i,j)->Red==224){
			V[i][j]=0.3;
			a[i][j]=true;
			}
			else if((float) I(i,j)->Red==64){
			V[i][j]=1;
			a[i][j]=true;
			}
			}
	}
	
	

    //evaluating all u apart from boundaries using SOR
    

    
for (m=0; m<=maxit; m++){
    for (i=0; i<imax; i++){
        for (j=0; j<jmax; j++){

            //if a boundary has been set, do nothing
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
  
    //output of final data to a file for plotting
    
    ofstream file;
    file.open("draft3.dat");
    
    for (i=0; i<=imax; i++){
        for (j=0; j<=jmax; j++){
            
            file << (i*d) << "      "<< (j*d) << "    " <<  V[i][j] << "\n";
            
        }
        file << "\n";
    }
    
    
    file.close();
    

            
            
    
    
    return 0;
    
}


