#ifndef SIGNALSHAPESIM_H
#define SIGNALSHAPESIM_H

#include <cmath>

class SignalShapeSim{
public:
	double operator() (double *x,double *par){
		double x_max   =  par[0];
		double ampl    =  par[1];
		double sigma_g =  par[2];
		double sigma_l =  par[3];
		double pedestal = par[4];
		
		double analogueSat = 1230.;
		
		// saturated analogue pulse
		if(ampl > analogueSat){
			double lower_x = x_max -  sqrt(-sigma_g*sigma_g*(1.+2.*log((analogueSat-pedestal)/ampl)));
			
			
			if(x[0] > lower_x)
				return analogueSat;
			else if(x[0] <= lower_x)
				return (analogueSat-pedetal)*exp( (-0.5)*(x[0]-lower_x)/sigma_g) + pedestal;
			
		}
		// Normal pulse
		else{
		
			if( x[0]<= x_max)
			{
				return(( ampl * exp(((-0.5)*(x[0]-x_max)*(x[0]-x_max)/((sigma_g)*(sigma_g) ) ) -0.5) ) + pedestal);
			}
			else if(x[0]> x_max )
			{
				return(( ampl * exp((-0.5)*(((x[0]-x_max)/sigma_l)+(exp(-(x[0]-x_max)/ sigma_l) ) ) ) ) + pedestal);
			}
		}
		
	}
	
private:
	
	
	
	
};

#endif


double function(double *x,double *par){
	double x_max   =  par[0];
	double amp    =  par[1];
	double sigma_g =  par[2];
	double sigma_l =  par[3];
	double pedestal = par[4];
	double analogSat = par[5];
	
	// saturated analogue pulse
	if(amp > analogSat){
		double offset = sqrt(-2*sigma_g*sigma_g*log(analogSat/amp));
		double tempMean = x_max - offset;
		cerr << offset << " " << tempMean << endl;
		
		if(x[0] > tempMean)
			return analogSat+pedestal;
		else if(x[0] <= tempMean){
			double gaussian = analogSat*exp((-0.5) * ((x[0]-tempMean)/sigma_g) * ((x[0]-tempMean)/sigma_g));
			
			return gaussian + pedestal;
			
		}
		
	}
	// Normal pulse
	else{
	
		if( x[0]<= x_max)
		{
			double gaussian = amp*exp((-0.5) * ((x[0]-x_max)/sigma_g) * ((x[0]-x_max)/sigma_g));
			return gaussian + pedestal;
		}
		else if(x[0]> x_max )
		{
			double landau = amp*exp(0.5) * exp((-0.5) * (((x[0]-x_max)/sigma_l) + exp(-(x[0]-x_max)/ sigma_l) ) );
			return landau + pedestal ;
		}
	}
	
}

