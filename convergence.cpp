#include <iostream>
#include <math.h>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <cstring>
  

  

  using namespace std;
  
bool a[1000][1000];
bool b[1000][1000];
float e[1000][1000],V[1000][1000],w=1.3, d=0.1, r[100],x[100],y[100],v[100];

  /*This script uses the SOR method to solve laplaces equation. it is run using the shell script "plot4.sh".
   This is an updated version of SOR.cpp that had issues at boundaries, where boundaries that were not set by the
   user were assumed to be zero for all iterations. This was solved by using an approximation of the finite difference scheme when the unset boundaries are reached. This still isn't ideal for certain situations but we'll try to improve on it. At the moment, this script simply let the user set an unlimited number of circles at different potentials, and doesn't allow the user to set other shapes, or conditions at the boundaries. This would be simple to change but there's not much point if we're not having our final program run from the terminal. So, this script was pretty much to test the SOR method and sort out the boundary issues.
  */
  int main(){

      int i, j, m, p, n, jmax, gridmax=50;
	int maxit = 1000;
      
      
      
      
     //jmax is the number of iterations of size d needed to sweep through our grid
      
      jmax=gridmax/d;
      
      //anwers to be used for user input of boundaries
      
      char ans1[10],ans2[]="perimeter",ans3[]="fill";
      
      
      //input of circle info
      
      cout << "How many circular structures would you like?" << endl;
      cin >> n;
      
      for (p=1; p<=n; p++){
          
          cout << "Enter the radius of circle " << p << endl;
          
          cin >> r[p];
          
          cout << "Enter the x coordinate of circle " << p << endl;
          
          cin >> x[p];
          
          cout << "Enter the y coordinate of circle " << p << endl;
          
          cin >> y[p];
          
          cout << "Enter the potential you'd like to set circle " << p << " to." << endl;
          
          cin >> v[p];
          
      }
    



	//set all coordinates to false initially
      
      for (i=0; i<=jmax; i++){
          for (j=0; j<=jmax; j++){
              a[i][j]=false;
          }
      }
      
      
      //checking whether to fill the circle or just the perimeter and applying boundaries accordingly
      
      for (p=1; p<=n; p++){
          
          cout << "Would you like to apply the voltage to whole of circle " << p << "? or just the perimeter?\n\nType 'fill' or 'perimeter':" << endl;
          cin >> ans1;
          
          
          for (i=0; i<=jmax; i++){
              for (j=0; j<=jmax; j++){
                  
                  if (strcmp (ans1,ans2) == 0){
                      
                      //apply voltage to perimeter 

                      
                      if ( pow((i*d-x[p]),2)+pow((j*d-y[p]),2)>=pow(r[p],2) && pow((i*d-x[p]),2)+pow((j*d-y[p]),2)<=pow(r[p]+0.03,2)){
                          
                          
                          V[i][j]=v[p];
                          a[i][j]=true;
			
			
                          
                          
                      }
                  }
                  
                  else if (strcmp (ans1,ans3) == 0){
                      
                      //apply voltage to entire shape
                      
                      if ( pow((i*d-x[p]),2)+pow((j*d-y[p]),2)<=pow(r[p],2)){
                          
                          
                          V[i][j]=v[p];
                          a[i][j]=true;
                          
                          
                          
                      }
                  }
              }
              
          }
      }
      
      
      
      //evaluating  boundaries
      
      for (i=0; i<=jmax; i++){
          for (j=0; j<=jmax; j++){
              
  /*this applies an initial value of zero to all points that haven't been set by the user, i.e values where a[i][j] is false. you can set potentials at the boundaries if you wish by including if statements that check whether we're at a boundary, and applying potentials accordingly */
              
              if (!a[i][j]){
                  
              
                      
                      V[i][j]=0;
                      a[i][j]=false;
                      
                      
                  
              }
              
          }
      }
      
      //evaluating all u apart from boundaries using SOR
      
double Grad[1000][1000];  
for (int f=0; f<=50; f++) {          
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
                  

double Ex =  0.5*(V[i+1][j]-V[i-1][j]);
double Ey =  0.5*(V[i][j+1]-V[i][j-1]);
Grad[i][j] = sqrt( pow(Ex, 2) + pow(Ey, 2));


          
}
}
}

cout << Grad[500][500] << endl;
//fix fix
float maximum = 0;
int k1 = 0;
int k2 = 0;
 for (i=0; i<=jmax; i++){
              for (j=0; j<=jmax; j++){
			if (Grad[i][j]>maximum) {
				maximum = Grad[i][j];
				k1 = i;
				k2 = j;
			}
				
}
}
//assign space ij in Grad to b
cout << k1 << endl;
b[k1][k2] = true;
/////////

float compare[maxit];

for (m=0; m<=maxit; m++){

 

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
if (b[i][j]) {
V[i][j] = compare[m];

}

}

//COMPARISON HERE
//when relative error small, stop 
if ((abs(compare[m-1]-compare[m]))< pow(10, -30)) {
cout << m << endl;
m = maxit;
}
else {
m=m;
}


}
}

//*****************************************************************

      //output of final data to a file for plotting
      
      ofstream file;
      file.open("draft4.dat");
      
      for (i=0; i<=jmax; i++){
          for (j=0; j<=jmax; j++){
              
              file << (i*d) << "      "<< (j*d) << "    " <<  V[i][j] << "\n";
              
          }
          file << "\n";
      }
      
      
      file.close();
      
      
      
      
      
      
      return 0;

}

