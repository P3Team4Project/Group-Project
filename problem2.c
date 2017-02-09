#include "fstream"
#include <iostream>
#include <math.h>


using namespace std;

int main(){
	double R,V,p,x,y;

	ofstream myfile;
	myfile.open("data2.dat");

	V=100;
	R=300;
	
	for (x=-1000; x<=1000; x++){
		for (y=-1000; y<=1000; y++){
			if(x*x+y*y>R*R){
				p=-0.1*x*(1.0-pow((R)/(sqrt(x*x+y*y)),3));
			}
			else if(x*x+y*y<R*R){
				p=0;
			}
			myfile << x << " " << y << " " << p << endl;
		}
		myfile << endl;	
	}
	myfile.close();
}
