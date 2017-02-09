#include "fstream"
#include <iostream>
#include <math.h>


using namespace std;

int main(){
	double R,V,p,x,y,i;

	ofstream myfile;
	myfile.open("data2contour.dat");

	V=100;
	R=50;
	
	for (x=-500; x<=500; x++){
		for (y=-500; y<=500; y++){
			if(x*x+y*y>R*R){
				p=-x*(1.0-pow((R)/(sqrt(x*x+y*y)),3));
				for (i=-100; i<=V; i+=5){
					if (p>=i-0.01){
						if(p<=i+0.01){	
						myfile << x << " " << y << " " << p << endl;
						
						}
					}
				}
			}
			else if(x*x+y*y<R*R){
				p=0;
			}
		}
		myfile << endl;	
	}
	myfile.close();
}
