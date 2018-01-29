#ifndef LANDGAUS_H
#define LANDGAUS_H

///---------------
/// Declaring a functor for the Fermi fit function
///---------------

#include <cmath>

class LandGaussFunc{
public:
	double operator() (double *x,double *par){
		double x_max   =  par[0];
		double ampl    =  par[1];
		double sigma_g =  par[2];
		double sigma_l =  par[3];
		double pedestal = par[4];
	
		
	
		if( x[0]<= par[0])
		{
			return(( ampl * exp(((-0.5)*(x[0]-x_max)*(x[0]-x_max)/((sigma_g)*(sigma_g) ) ) -0.5) ) + pedestal);
		}
		else if(x[0]> par[0] )
		{
			return(( ampl * exp((-0.5)*(((x[0]-x_max)/sigma_l)+(exp(-(x[0]-x_max)/ sigma_l) ) ) ) ) + pedestal);
		}
	
}
	
private:
	
	
	
	
};

#endif


double LandGausFitFunc(double *x,double *par){
	double x_max   =  par[0];
	double ampl    =  par[1];
	double sigma_g =  par[2];
	double sigma_l =  par[3];
	double pedestal = par[4];

	

	if( x[0]<= par[0])
	{
		
		return(( ampl * exp(((-0.5)*(x[0]-x_max)*(x[0]-x_max)/((sigma_g)*(sigma_g) ) ) -0.5) ) + pedestal);
	}
	else if(x[0]> par[0] )
	{
		return(( ampl * exp((-0.5)*(((x[0]-x_max)/sigma_l)+(exp(-(x[0]-x_max)/ sigma_l) ) ) ) ) + pedestal);
	}
}

