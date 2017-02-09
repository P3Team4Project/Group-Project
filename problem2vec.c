#include "fstream"
#include <iostream>
#include <math.h>


using namespace std;
double p[2001][2001];

int main(){
	double R,V,Ex=0,Ey=0,r1;
	int x,y;

	ofstream myfile;
	myfile.open("data2vec.dat");

	V=100;
	R=300;
	r1=1000;
	
	for (x=-r1; x<=r1; x++){
		for (y=-r1; y<=r1; y++){
			if(x*x+y*y>R*R){
				p[x+1000][y+1000]=-0.1*x*(1.0-pow((R)/(sqrt(x*x+y*y)),3));
			}
			else if(x*x+y*y<R*R){
				p[x+1000][y+1000]=0;
			}
		}
	}
	for(x=-r1+1; x<=(r1-1); x+=50){
		for(y=-r1+1;y<=(r1-1);y+=50){
			Ex =  0.5*(p[x+1001][y+1000]-p[x+999][y+1000]);
			Ey =  0.5*(p[x+1000][y+1001]-p[x+1000][y+999]);
			if(Ey!=0){
				if(Ex!=0){ 
				myfile << x << " " << y << " " << 400*Ex << " " << 400*Ey << endl;
				}
			}
		}
		
	}
	myfile.close();
}
