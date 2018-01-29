#ifndef SATURATEDBCID_H
#define SATURATEDBCID_H


class SaturatedBcid{
public:
   SaturatedBcid(void){Clear();};
   SaturatedBcid(const unsigned short lowThreshold,const unsigned short highThreshold,const unsigned short satLevel){
      SetValues(lowThreshold,highThreshold,satLevel);};
   
   void Clear(void){SetLowThreshold(0);SetHighThreshold(0);SetSaturationLevel(0);};
   
   void SetValues(const unsigned short lowThreshold,
                  const unsigned short highThreshold,
                  const unsigned short satLevel){
      SetLowThreshold(lowThreshold);
      SetHighThreshold(highThreshold);
      SetSaturationLevel(satLevel);
   };
   
   void SetLowThreshold(const unsigned short threshold){m_satLow = threshold;};
   unsigned short GetLowThreshold(void) const {return m_satLow;};
   void SetHighThreshold(const unsigned short threshold){m_satHigh = threshold;};
   unsigned short GetHighThreshold(void) const {return m_satHigh;};
   void SetSaturationLevel(const unsigned short level){m_satLevel = level;};
   unsigned short GetSaturationLevel(void) const {return m_satLevel;};
   
private:
   unsigned short int m_satLow;
   unsigned short int m_satHigh;
   unsigned short int m_satLevel;
};


#endif

