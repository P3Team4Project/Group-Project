#include "fstream"
#include <iostream>
#include <math.h>
#include <iomanip>
#include <stdio.h>

using namespace std;
double p[2001][2001];

int main(){
	double r1,r2,V,Ex=0,Ey=0;
	int x,y;
	
	
	V=100;
	r1=1000;
	r2=200;
	for(x=-r1; x<=r1; x++){
		for(y=-r1;y<=r1;y++){
			if((double)x*x+y*y>r1*r1){
				p[x+1000][y+1000]=0;
			}
			else{
				if((double)x*x+y*y<r2*r2){
					p[x+1000][y+1000]=0;
				}
				else{	
					p[x+1000][y+1000]=V/(log(r1/r2))*(log(sqrt(x*x+y*y))-log(r2));
				}
			}
		
		}
	}
	ofstream myfile;
	myfile.open("grad1.dat");
	
	for(x=-r1+1; x<=(r1-1); x+=50){
		for(y=-r1+1;y<=(r1-1);y+=50){
			Ex =  0.5*(p[x+1001][y+1000]-p[x+999][y+1000]);
			Ey =  0.5*(p[x+1000][y+1001]-p[x+1000][y+999]);
			if(Ey < 10.0){
			if(Ey > -10.0){
				if(Ex < 10.0){ 
				if(Ex > -10.0){
				myfile << x << " " << y << " " << 500*Ex << " " << 500*Ey << endl;
				}
				}
			}
			}
		}
		myfile << endl;
	}
	myfile.close();
}
