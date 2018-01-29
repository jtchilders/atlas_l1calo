#ifndef TTGRAPH_H
#define TTGRAPH_H

#include <vector>
#include <iostream>

#include "TGraph.h"

class TTGraph: public TGraph{
public:
   TTGraph(std::vector<double> x,std::vector<double> y){
      const unsigned int nx = x.size();
      const unsigned int ny = y.size();
      if(nx == 0 || ny == 0){
         std::cerr << "[TTGraph::TTGraph] vector size is zero. nx = " << nx << " ny = " << ny << "\n";
         return;
      }
      
      if(nx != ny){
         std::cerr << "[TTGraph::TTGraph] vector size is not the same. nx = " << nx << " ny = " << ny << "\n";
         return;
      }
      
      TGraph::Set(nx);
      for(unsigned int i=0;i<nx;++i){
         TGraph::SetPoint(i,x[i],y[i]);
      }
   };
   
   
private:
   
};




#endif


