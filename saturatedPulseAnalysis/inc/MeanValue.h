#ifndef MEANVALUE_H
#define MEANVALUE_H

#include <cmath>

class MeanValue{
public:
   MeanValue(void){Clear();};
   ~MeanValue(void){};
   
   void Clear(void){sum=0.0;sum2=0.0;n=0;
      mean=0.0;sigma=0.0;
      withErrors=false;keepHistory=false;
      hist_mean.clear();hist_sigma.clear();
   };
   
   void AddEntry(float entry){ 
      AddSum(entry);AddSum2(entry);Increment();
      CalculateMean();CalculateSigma();
   };
   void AddEntry(float entry, float error){
      AddSum(entry,error);Increment();
      CalculateMean();CalculateSigma();
   }
   
   int GetIntegerMean(void){
      if(mean > 0.){
         if(mean - floor(mean) > 0.5) return (int)mean + 1;
         else return (int)mean;
      }
      else{
         if(mean - floor(mean) > 0.5) return (int)mean;
         else return (int)mean + 1;
      }
   }
   
   int GetIntegerSigma(void){
      if(sigma > 0.){
         if(sigma - floor(sigma) > 0.5) return (int)sigma + 1;
         else return (int)sigma;
      }
      else{
         if(sigma - floor(sigma) > 0.5) return (int)sigma;
         else return (int)sigma + 1;
      }
   }
   
   float GetMean(void){return mean;};
   float GetSigma(void){return sigma;};
   
   void WithErrors(bool value){withErrors=value;};
   bool WithErrors(void){return withErrors;};
   
   void KeepHistory(bool value){keepHistory=value;};
   bool KeepHistory(void){return keepHistory;};
   
   std::vector<float>* GetMeanHistory(void){return &hist_mean;};
   std::vector<float>* GetSigmaHistory(void){return &hist_sigma;};
   
   float GetSum(void){return sum;};
   float GetSum2(void){return sum2;};
   unsigned int GetN(void){return n;};
   
private:
   float sum;
   float sum_error;
   float sum2;
   unsigned int n;
   
   bool withErrors;
   bool keepHistory;
   std::vector<float> hist_mean;
   std::vector<float> hist_sigma;
   
   float mean;
   float sigma;
   
   void CalculateMean(void){
      mean = (n == 0) ? 0 : sum/(float)n;
      if(keepHistory) hist_mean.push_back(mean);
   };
   
   void CalculateSigma(void){
      if(withErrors)
         sigma = (n == 0) ? 0 : sum_error/n;
      else
         sigma = (n <= 1)? 0 : sqrt((1.0/(float)n)*sum2 - mean*mean);
      
      if(keepHistory) hist_sigma.push_back(sigma);
   };
   
   void AddSum(float entry){sum+=entry;};
   void AddSum(float entry,float error){sum+=entry;sum_error+=error;};
   void AddSum2(float entry){sum2+=entry*entry;};
   void Increment(void){n++;};
   
   
   
};


#endif
