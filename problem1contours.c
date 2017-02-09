#include "fstream"
#include <iostream>
#include <math.h>
#include <iomanip>
#include <stdio.h>

using namespace std;

int main(){
	double r1,r2,V,p,x,y,i;
	
	ofstream myfile;
	myfile.open("datacont.dat");

	V=100;
	r1=1000;
	r2=200;
	
	for (x=-r1; x<=r1; x++){
		for (y=-r1; y<=r1; y++){
			if(x*x+y*y<r1*r1){
				if (x*x+y*y>r2*r2){
					p=V/(log(r1/r2))*(log(sqrt(x*x+y*y))-log(r2));
					for (i=0; i<=V; i+=5){
					if (p>=i-0.01){
						if(p<=i+0.01){	
						myfile << x << " " << y << endl;
						cout << p << endl;
						}
					}
					}				
				}
				else if(x*x+y*y<r2*r2){
				p=0;
				}
				
			}
		}
	}
	myfile.close();
}
