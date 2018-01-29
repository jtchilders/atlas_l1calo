#ifndef FERMI_H
#define FERMI_H

///---------------
/// Declaring a functor for the Fermi fit function
///---------------

#include <cmath>

class FermiFunc{
public:
	double operator() (double *x,double *par){
		double amp       =  par[0];
		double x_mean    =  par[1];
		double sigma     =  par[2];
		double pedestal  =  par[3];
		
		
		
		return (amp/(exp((x_mean-x[0])/sigma)+1.0) + pedestal);

	}
	
private:
	
	
	
	
};


// double function (double *x,double *par){
// 	double amp       =  par[0];
// 	double x_mean    =  par[1];
// 	double sigma     =  par[2];
// 	double pedestal  =  par[3];
// 	
// 	
// 	
// 	return (amp/(exp((x_mean-x[0])/sigma)+1.0) + pedestal);
// 
// }

#endif
