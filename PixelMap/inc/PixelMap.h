#ifndef PIXELMAP_H
#define PIXELMAP_H
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/// Pixel Mapping class                                               ///
/// Developed by: Taylor Childers                                     ///
/// Feel free to email with questions                                 ///
/////////////////////////////////////////////////////////////////////////
/// This package was developed to provide a tool for making 2D eta    ///
/// phi plots for L1Calo monitoring and analysis.                     ///
///                                                                   ///
/// It has multiple features:                                         ///
/// You can have 2D plots with pixel size corresponding to the        ///
/// Preprocessor's trigger towers or the Jet/Energy Processor's       ///
/// jet elements.                                                     ///
///                                                                   ///
/// The class can be initialized in two ways                          ///
///    1 - PixelMap<datatype> *pm = new PixelMap<datatype>;           ///
///        pm->SetPixelSize(TrigTower or JetEl);                      ///
///    2 - PixelMap<datatype> *pm =                                   ///
///                   new PixelMap<datatype>(TrigTower or JetEl);     ///
///                                                                   ///
///    here "datatype" can be: int,unsigned int,short,double,float,etc.///
///    and just specifies the type of data you would like to          ///
///    store in the PixelMap.                                         ///
///                                                                   ///
/// If you don't set the pixel size in the constructor you need to    ///
/// set it before you begin to use the map.                           ///
/// You can also clear the map of all contents, including the pixel   ///
/// size by using the ClearPixelMap() function. This allows for easy  ///
/// reuse of the map. Just remember to set the pixel size again       ///
/// before you use it.                                                ///
///                                                                   ///
/// As an example, lets use the trigger tower pixel size.             ///
/// A trigger tower can then be set using the SetTriggerTower()       ///
/// function. This takes the trigger tower's eta/phi location,        ///
/// value to be set, and optionally the FCAL layer as parameters.     ///
///                                                                   ///
/// The eta/phi values can be any value within the trigger tower (or  ///
/// jet element). They don't have to be a certain point because I'm   ///
/// just using a series of less than, greater than statements         ///
/// to funnel the eta/phi values to the right trigger tower.          ///
///                                                                   ///
/// So if I wanted to set the trigger tower for eta=0.5 and phi=0.5   ///
/// to a value of 6. Then I would use:                                ///
///   SetTriggerTower(0.5,0.5,6);                                     ///
///                                                                   ///
/// If you are in an FCAL2/3 region you should use:                   ///
///    SetTriggerTower(-4.3, 2.4, 35, FCAL2 (or FCAL3));              ///
///                                                                   ///
/// If you do not pass the FCAL2 or FCAL3 enum members then the       ///
/// FCAL pixels are treated as one would expect the Electromagnetic   ///
/// FCAL pixels to be treated.                                        ///
///                                                                   ///
/// If you pass these FCAL2/3 values then the FCAL2 trigger towers    ///
/// will be filled in the inner two EM-like trigger towers, and the   ///
/// FCAL3 trigger towers will be filled in the outer 2 EM-like        ///
/// trigger towers.                                                   ///
///                                                                   ///
/// This means, for FCAL2, the bin that extends from eta=-4.9 to -4.0 ///
/// would be filled into the EM-like bin that goes from -4.0 to -3.6  ///
/// and the FCAL2 bin from -4.0 to -3.2 would be filled from -3.6     ///
/// to -3.2 This is then mirrored on the other side. Then for FCAL3   ///
/// the bin from eta = -4.9 to -4.0 would be filled into -4.9 to -4.4 ///
/// and from -4.0 to -3.2 would go into eta from -4.4 to -4.0         ///
///                                                                   ///
/// This just makes it so you can fit the FCAL2/3 layers on the same  ///
/// plot.                                                             ///
///                                                                   ///
///                                                                   ///
/// There is also a GetTriggerTower() method which works in a similar ///
/// way and returns the contents of the Trigger Tower.                ///
///                                                                   ///
/// If you want to increment a TT than just use the GetTriggerTower   ///
/// function to get the value, increment the value, then use          ///
/// SetTriggerTower to set the new value.                             ///
///                                                                   ///
/// Since I use C++ maps to contain all this information, I also      ///
/// provide iterators for these maps so you can easily iterate over   ///
/// all the elements in the maps. This is also useful in the case     ///
/// where you use two of my PixelMapss and want to compare the        ///
/// elements. If they were filled in the same way, then element X of  ///
/// mapA should correspond to element X in mapB.                      ///
///                                                                   ///
/// I have recently made this into a template so that you can use     ///
/// the map to hold any data type, int, unsigned int, short, etc.     ///
/// So to create a new object you do the following:                   ///
/// PixelMap<double>* pm = new PixelMap<double>;                      ///
/// and the "double" can be replaced with any data type.              ///
///                                                                   ///
/// You can then use the FillEtaPhiHistogram(TH2*) to pass a pointer  ///
/// to a TH2D,TH2I, etc. that was initialized as follows:             ///
/// TH2D("","",L1CALO_ETA_TT,-4.9,4.9,L1CALO_PHI_TT,0,2*PI)           ///
/// Use the built in GetPI() function if you don't have a PI const    ///
/// lying around.                                                     ///
///                                                                   ///
/// I think that's most of the useful information so please enjoy.    ///
///                                                                   ///
/// Update:                                                           ///
/// I've recently added the ability to do a profile plot. In order    ///
/// to use this ability just use SetProfileMode(true).                ///
/// This involves an additional function:                             ///
/// FillEtaPhiHistograms(std::vector<TH2D*>)                          ///
/// which expects two histograms initilized as described above, where ///
/// the first will hold the mean values for each trigger tower and    ///
/// the second will hold the sigma values.                            ///
/////////////////////////////////////////////////////////////////////////

#include <vector>
#include <iostream>
#include <cmath>
#include <map>
#include <typeinfo>

#include "FcalLayer.h"

#include "TH2.h"

template <class dataType = unsigned int> 
class PixelMap {
public:
   
   
   enum pixel_size{
      NO_SIZE_SET=0,
      TrigTower=1,
      JetEl=2
   };
   
	PixelMap();
	PixelMap(const pixel_size,const bool = false);
	~PixelMap();
	
	void SetPixelSize(const pixel_size ps){pixelSize=ps;};
	pixel_size GetPixelSize(void){return pixelSize;};
	
	bool SetTriggerTower(const float,const float,const dataType,const FcalLayer fcallayer=FcalLayer::FcalLayer());
	
	dataType GetTriggerTower(const float,const float,const FcalLayer fcallayer=FcalLayer::FcalLayer());
	bool GetTriggerTowerMeanAndSigma(const float,const float,double&,double&,const FcalLayer fcallayer=FcalLayer::FcalLayer());
	
	bool SetJetEl(const float,const float,const dataType);
	dataType GetJetEl(const float,const float);
	bool GetJetElMeanAndSigma(const float, const float,double&,double&);
	
	void ClearPixelMap(void);
	// Clear pixel map AND set the pixel size & profile mode
	void ClearPixelMap(const pixel_size,const bool profileMode = false); 
	
	void SetProfileMode(bool value) {useProfile = value;};
	
   TH2* GetEtaPhiHistogram(std::string,std::string);
	void FillEtaPhiHistogram(TH2*);
   std::vector<TH2*> GetEtaPhiHistograms(std::string,std::string,std::string,std::string);
	void FillEtaPhiHistograms(std::vector<TH2D*>);
	
	unsigned int GetNumTtBins(void) {return mTtBins.size();};
	typename std::map<unsigned int,dataType>::iterator GetTtBeginItr(void) {return mTtBins.begin();};
	typename std::map<unsigned int,dataType>::iterator GetTtEndItr(void) {return mTtBins.end();};
	
	unsigned int GetNumJetElBins(void) {return mJetElBins.size();};
	typename std::map<unsigned int,dataType>::iterator GetJetElBeginItr(void) {return mJetElBins.begin();};
	typename std::map<unsigned int,dataType>::iterator GetJetElEndItr(void) {return mJetElBins.end();};
	
	unsigned int GetEtaPhiID(const unsigned int,const unsigned int);
	void GetEtaPhiFromID(const unsigned int,unsigned int&,unsigned int&);
	
	unsigned int ftoiEta(const float eta);
	float itofEta(const unsigned int eta);
	unsigned int ftoiPhi(const float phi);
	float itofPhi(const unsigned int phi);
   
   const float GetPI(void){return PI;};
	
private:
	// This represents each bin in the histogram,
	// these values will ultimately get booked into the histogram
	std::map<unsigned int,dataType> mHistoBins;
	
	// This map tells you what mHistoBins correspond to what eta/phi TT
	// for instance in the Barrel one TT = one bin, but in other regions
	// there can be more than 1 bin in a Trigger Tower.
	std::map<unsigned int,std::vector<unsigned int> > mTtPixelToBin;
	// Similar to mTtPixelToBin but Jet Elements instead
	std::map<unsigned int,std::vector<unsigned int> > mJetElPixelToBin;
	
	// This map holds the value that should be stored to each Trigger Tower
	// and mTtPixelToBin is used to set the corresponding histogram bins in
	// mHistoBins
	std::map<unsigned int,dataType> mTtBins;
	
	// If you are in Profile Mode these three maps are used to hold the
	// sum, sum squared, and number of entries in each trigger tower
	// This allows you to calculate the mean and sigma for each tower.
	std::map<unsigned int,double> mTtSum;
	std::map<unsigned int,double> mTtSum2;
	std::map<unsigned int,unsigned int> mTtN;
	
	// Similar to mTtBins
	std::map<unsigned int,dataType> mJetElBins; 
	
	// Similar to the mTtSum,mTtSum2, and mTtN
	std::map<unsigned int,double> mJetElSum;
	std::map<unsigned int,double> mJetElSum2;
	std::map<unsigned int,unsigned int> mJetElN;
	
	pixel_size pixelSize;
	
	dataType GetHistoBin(const unsigned int,const unsigned int);
	
	bool SetJetElHistoBins(const unsigned int);
	bool SetTtHistoBins(const unsigned int);
	
	bool SetTriggerTower(const unsigned int, dataType);
	
	
	bool ClearTriggerTowerStats(const unsigned int);
	bool SetTriggerTowerSum(const unsigned int,const double);
	bool SetTriggerTowerSum2(const unsigned int,const double);
	bool IncrementTriggerTowerN(const unsigned int,const unsigned int = 1);
	
	bool ClearJetElStats(const unsigned int);
	bool SetJetElSum(const unsigned int,const double);
	bool SetJetElSum2(const unsigned int,const double);
	bool IncrementJetElN(const unsigned int,const unsigned int = 1);
	
	void FillJetElMap(void);
	void FillTrigTowerMap(void);
	
	unsigned int itoiEtaTt(const unsigned int,FcalLayer fcallayer=FcalLayer::FcalLayer());
	unsigned int itoiPhiTt(const unsigned int,const unsigned int);
	unsigned int itoiEtaJetEl(const unsigned int);
	unsigned int itoiPhiJetEl(const unsigned int,const unsigned int);
	
   static const float PI;
   
   static const unsigned short int PIXELMAP_MAX_JETEL = 992;
   static const unsigned short int PIXELMAP_MAX_TT = 3584;

   static const unsigned short int L1CALO_ETA_TT = 98;
   static const unsigned short int L1CALO_PHI_TT = 64;

	bool useProfile;
};

template <class dataType>
const float PixelMap<dataType>::PI = 3.14159265;

template <class dataType>
PixelMap<dataType>::PixelMap(void){
	
	ClearPixelMap();
	
	//std::cerr << "PixelMap::PixelMap: Filling Jet Element Map\n";
	FillJetElMap();
	//std::cerr << "PixelMap::PixelMap: Filling Trigger Tower Map\n";
	FillTrigTowerMap();
	//std::cerr << "PixelMap::PixelMap: Done\n";
}

template <class dataType>
PixelMap<dataType>::PixelMap(const pixel_size ps, const bool profileMode){
	
	ClearPixelMap();
	
	//std::cerr << "PixelMap::PixelMap: Filling Jet Element Map\n";
	FillJetElMap();
	//std::cerr << "PixelMap::PixelMap: Filling Trigger Tower Map\n";
	FillTrigTowerMap();
	//std::cerr << "PixelMap::PixelMap: Done\n";
	
	SetPixelSize(ps);
	SetProfileMode(profileMode);
	
	
}

template <class dataType>
PixelMap<dataType>::~PixelMap(void){
	
}

template <class dataType>
void PixelMap<dataType>::ClearPixelMap(void){
	
	mHistoBins.clear();
	mTtBins.clear();
	mTtSum.clear();
	mTtSum2.clear();
	mTtN.clear();
	mJetElBins.clear();
	mJetElSum.clear();
	mJetElSum2.clear();
	mJetElN.clear();
	
	pixelSize = NO_SIZE_SET;
	useProfile = false;
	
}

template <class dataType>
void PixelMap<dataType>::ClearPixelMap(const pixel_size ps,const bool profileMode){
	ClearPixelMap();
	
	SetPixelSize(ps);
	SetProfileMode(profileMode);
	
}

template <class dataType>
unsigned int PixelMap<dataType>::GetEtaPhiID(const unsigned int eta,const unsigned int phi){
	return (((eta & 0xffff) << 16) | (phi & 0xffff));
}

template <class dataType>
void PixelMap<dataType>::GetEtaPhiFromID(const unsigned int etaPhiID,unsigned int& eta,unsigned int& phi){
	phi = etaPhiID & 0xffff;
	eta = etaPhiID >> 16;
}

// This fills the mJetElPixelToBin map. For each jet element eta phi coordinate
// there are corresponding histogram bins that should be related.
template <class dataType>
void PixelMap<dataType>::FillJetElMap(void){
	
	for(int i=0;i<L1CALO_ETA_TT;i++){
		for(int j=0;j<L1CALO_PHI_TT;j++){
			
			unsigned int etaPhiID = GetEtaPhiID(i,j);
			unsigned int jeEta = itoiEtaJetEl(i);
			unsigned int jePhi = itoiPhiJetEl(j,jeEta);
			unsigned int jeEtaPhiID = GetEtaPhiID(jeEta,jePhi);
			
			std::map<unsigned int,std::vector<unsigned int> >::iterator itr;
			itr = mJetElPixelToBin.find(etaPhiID);
			if(itr == mJetElPixelToBin.end()){
				std::vector<unsigned int> temp;
				temp.push_back(etaPhiID);
				mJetElPixelToBin[jeEtaPhiID] = temp;
			}
			else{
				mJetElPixelToBin[jeEtaPhiID].push_back(etaPhiID);
			}
			
		}
		
	}
	
}

// similar to FillJetElMap above
template <class dataType>
void PixelMap<dataType>::FillTrigTowerMap(void){
	for(int i=0;i<L1CALO_ETA_TT;i++){
		
		for(int j=0;j<L1CALO_PHI_TT;j++){
			unsigned int etaPhiID = GetEtaPhiID(i,j);
			unsigned int ttEta = itoiEtaTt(i);
			unsigned int ttPhi = itoiPhiTt(j,ttEta);
			unsigned int ttEtaPhiID = GetEtaPhiID(ttEta,ttPhi);
			
			std::map<unsigned int,std::vector<unsigned int> >::iterator itr;
			itr = mTtPixelToBin.find(ttEtaPhiID);
			if(itr == mTtPixelToBin.end()){
				std::vector<unsigned int> temp;
				temp.push_back(etaPhiID);
				mTtPixelToBin[ttEtaPhiID] = temp;
			}
			else{
				mTtPixelToBin[ttEtaPhiID].push_back(etaPhiID);
			}
			
		}
		
	}
	
}

template <class dataType>
dataType PixelMap<dataType>::GetJetEl(const float eta,const float phi){
	
	if(pixelSize != JetEl){
		std::cerr << "PixelMap::GetJetEl: Pixel Size is not set for Jet Element, " << pixelSize << std::endl;
		return (dataType)999;
	}
	if(useProfile){
		std::cerr << "PixelMap::GetJetEl: Cannot use this method when using Profile Mode. Should use GetJetElMean or GetJetElSigma.\n";
		return (dataType)999;
	}
	unsigned int tempEta = ftoiEta(eta);
	unsigned int iEta = itoiEtaJetEl(tempEta);
	unsigned int tempPhi = ftoiPhi(phi);
	unsigned int iPhi = itoiPhiJetEl(tempPhi,iEta);
	
	unsigned int etaPhiID = GetEtaPhiID(iEta,iPhi);
	
	typename std::map<unsigned int,dataType>::iterator it;
	it = mJetElBins.find(etaPhiID);
	if(it == mJetElBins.end()){
		//std::cerr << "PixelMap::GetJetEl: Cannot find Jet El for eta/phi: " << iEta << "/" << iPhi << std::endl;
		// Since no jet element was found, create one and initialize it to zero.
		SetJetEl(eta,phi,0);
		return 0;
	}
	
	return it->second;
}

// Calculates the mean and sigma for the jet element corresponding to the eta/phi
// return true if values are good. If false don't use them.
template <class dataType>
bool PixelMap<dataType>::GetJetElMeanAndSigma(const float eta,const float phi, double& mean, double& sigma){
	
	if(pixelSize != JetEl){
		std::cerr << "PixelMap::GetJetElMeanAndSigma: Pixel Size is not set for Jet Element, it is: " << pixelSize << std::endl;
		return false;
	}
	if(!useProfile){
		std::cerr << "PixelMap::GetJetElMeanAndSigma: Must be in Profile Mode to use this method.\n";
		return false;
	}
	
	mean = 0.0;
	sigma = 0.0;
	
	unsigned int tempEta = ftoiEta(eta);
	unsigned int iEta = itoiEtaJetEl(tempEta);
	
	unsigned int tempPhi = ftoiPhi(phi);
	unsigned int iPhi = itoiPhiJetEl(tempPhi,iEta);
	
	unsigned int etaPhiID = GetEtaPhiID(iEta,iPhi);
	
// 	std::cerr << "      etaPhiId: " << std::hex << etaPhiID << std::dec << std::endl;
	
	typename std::map<unsigned int,double>::iterator itSum;
	typename std::map<unsigned int,double>::iterator itSum2;
	typename std::map<unsigned int,unsigned int>::iterator itN;
	
	// get jet element sum
	itSum = mJetElSum.find(etaPhiID);
	if(itSum == mJetElSum.end()){
// 		std::cerr << "    no sum entry found.";
		// Since no jet element sum was found, lets create one and initialize it to zero.
		if(!ClearJetElStats(etaPhiID))
			return false;
		
		
		return true;
	}
	else{
		// have the sum now we get the sum sqaured
		itSum2 = mJetElSum2.find(etaPhiID);
		if(itSum2 == mJetElSum2.end()){
			// didn't find sum2.
			// output error since we should always have a Sum^2 if we have a sum.
			std::cerr << "PixelMap::GetJetElMeanAndSigma: [ERROR] Found a Sum for the Jet Element, but no Sum Squared. Resetting Jet Element Statistics to Zero. eta: " << eta << " phi: " << phi << std::endl;
			
			// now I will zero the elements statistics
			if(!ClearJetElStats(etaPhiID))
				return false;
			
			
			return true;
			
		}
		else{
			// we have a sum and sum squared. Need to find the N
			itN   = mJetElN.find(etaPhiID);
			if(itN == mJetElN.end()){
				// Since no N for this jet element was found
				// output error since we should always have a N if we have a sum and sum^2.
				std::cerr << "PixelMap::GetJetElMeanAndSigma: [ERROR] Found a Sum and Sum Squared for the Jet Element, but no counter. Resetting Jet Element Statistics to Zero for eta: " << eta << " phi: " << phi << std::endl;
				
				// now I will zero the elements statistics
				if(!ClearJetElStats(etaPhiID))
					return false;
				
				return true;
			}
			else{
				// got everything we need
				mean = 0;
				sigma = 0;
				if(itN->second != 0){
					mean = ((double)itSum->second/(double)itN->second);
					sigma = (double)sqrt( (1.0/(double)itN->second)*(double)itSum2->second - mean*mean);
				}
				return true;
			}
		}
	}
	
	return false;
	
}

template <class dataType>
bool PixelMap<dataType>::SetJetEl(const float eta,const float phi,const dataType value){
	
	if(pixelSize != JetEl){
		std::cerr << "PixelMap::SetJetEl: Pixel Size is not correctly set, " << pixelSize << std::endl;
		return false;
	}
	
	unsigned int tempEta = ftoiEta(eta);
	unsigned int iEta = itoiEtaJetEl(tempEta);
	unsigned int tempPhi = ftoiPhi(phi);
	unsigned int iPhi = itoiPhiJetEl(tempPhi,iEta);
	
	unsigned int etaPhiID = GetEtaPhiID(iEta,iPhi);
	
	if(useProfile){
		typename std::map<unsigned int,double>::iterator itSum,itSum2;
		typename std::map<unsigned int,unsigned int>::iterator itN;
		
		if(!SetJetElSum(etaPhiID,(double)value)){
			return false;
		}
		
		if(!SetJetElSum2(etaPhiID,((double)value*(double)value))){
			return false;
		}
		
		if(!IncrementJetElN(etaPhiID)){
			return false;
		}
	}
	else{
		
		mJetElBins[etaPhiID] = value;
		
		if(!SetJetElHistoBins(etaPhiID)){
			return false;
		}
	}
	
	return true;
}

// Sets the Sum/Sum2/N elements to 0 for the jet element corresponding to the etaPhiID passed
template <class dataType>
bool PixelMap<dataType>::ClearJetElStats(const unsigned int etaPhiID){
	
	if(pixelSize != JetEl){
		std::cerr << "PixelMap::ClearJetElStats: Pixel Size is not set to Jet Element, it is: " << pixelSize << std::endl;
		return false;
	}
	if(!useProfile){
		std::cerr << "PixelMap::ClearJetElStats: must be in Profile Mode to use this method.\n";
		return false;
	}
	
	std::map<unsigned int,double>::iterator itSum;
	itSum = mJetElSum.find(etaPhiID);
	if(itSum == mJetElSum.end()){
		mJetElSum[etaPhiID] = 0;
	}
	else{
		itSum->second = 0;
	}
	
	std::map<unsigned int,double>::iterator itSum2;
	itSum2 = mJetElSum2.find(etaPhiID);
	if(itSum2 == mJetElSum2.end()){
		mJetElSum2[etaPhiID] = 0;
	}
	else{
		itSum2->second = 0;
	}
	
	std::map<unsigned int,unsigned int>::iterator itN;
	itN = mJetElN.find(etaPhiID);
	if(itN == mJetElN.end()){
		mJetElN[etaPhiID] = 0;
	}
	else{
		itN->second = 0;
	}
	
	return true;
}


// If this jet element already has a value in it the passed value is added to this sum
// otherwise the jet element is set to the passed value.
template <class dataType>
bool PixelMap<dataType>::SetJetElSum(const unsigned int etaPhiID,const double value){
	
	if(pixelSize != JetEl){
		std::cerr << "PixelMap::SetJetElSum: Pixel Size is not set to Jet Element, it is: " << pixelSize << std::endl;
		return false;
	}
	if(!useProfile){
		std::cerr << "PixelMap::SetJetElSum: must be in Profile Mode to use this method.\n";
		return false;
	}
	
	std::map<unsigned int,double>::iterator itSum;
	itSum = mJetElSum.find(etaPhiID);
	if(itSum == mJetElSum.end()){
		mJetElSum[etaPhiID] = value;
		return true;
	}
	else{
		itSum->second = itSum->second + value;
		return true;
	}
	
	return false;
}

// If this jet element already has a value in it the passed valueSquared is added to this sum
// otherwise the jet element is set to the passed valueSquared.
template <class dataType>
bool PixelMap<dataType>::SetJetElSum2(const unsigned int etaPhiID,const double valueSquared){
	
	if(pixelSize != TrigTower){
		std::cerr << "PixelMap::SetJetElSum2: Pixel Size is not set to Jet Element, it is: " << pixelSize << std::endl;
		return false;
	}
	if(!useProfile){
		std::cerr << "PixelMap::SetJetElSum2: must be in Profile Mode to use this method.\n";
		return false;
	}
	
	std::map<unsigned int,double>::iterator itSum2;
	itSum2 = mJetElSum2.find(etaPhiID);
	if(itSum2 == mJetElSum2.end()){
		mJetElSum2[etaPhiID] = valueSquared;
		return true;
	}
	else{
		itSum2->second = itSum2->second + valueSquared;
		return true;
	}
	
	return false;
}

template <class dataType>
bool PixelMap<dataType>::IncrementJetElN(const unsigned int etaPhiID,const unsigned int value){
	
	if(pixelSize != TrigTower){
		std::cerr << "PixelMap::IncrementJetElN: Pixel Size is not set to Jet Element, it is: " << pixelSize << std::endl;
		return false;
	}
	if(!useProfile){
		std::cerr << "PixelMap::IncrementJetElN: must be in Profile Mode to use this method.\n";
		return false;
	}
	
	std::map<unsigned int,unsigned int>::iterator itN;
	itN = mJetElN.find(etaPhiID);
	if(itN == mJetElN.end()){
		mJetElN[etaPhiID] = value;
		return true;
	}
	else{
		itN->second = itN->second + value;
		return true;
	}
	return true;
}

template <class dataType>
dataType PixelMap<dataType>::GetTriggerTower(const float eta,const float phi,const FcalLayer fcalLayer){
	
	if(pixelSize != TrigTower){
		std::cerr << "PixelMap::GetTriggerTower: Pixel Size is not set for Trigger Tower, " << pixelSize << std::endl;
		return 999;
	}
	if(useProfile){
		std::cerr << "PixelMap::GetTriggerTower: Cannot use this method when using Profile Mode. Should use GetTriggerTowerMean or GetTriggerTowerSigma.\n";
		return 999;
	}
	
	unsigned int tempEta = ftoiEta(eta);
	unsigned int iEta = itoiEtaTt(tempEta,fcalLayer);
	
	unsigned int tempPhi = ftoiPhi(phi);
	unsigned int iPhi = itoiPhiTt(tempPhi,iEta);
	
	unsigned int etaPhiID = GetEtaPhiID(iEta,iPhi);
	
	typename std::map<unsigned int,dataType>::iterator it;
	it = mTtBins.find(etaPhiID);
	if(it == mTtBins.end()){
		// Since no trigger tower was found, lets create one and initialize it to zero.
		if(!SetTriggerTower(etaPhiID,0))
			return 999;
		else
			return 0;
	}
	
	return it->second;
}

// Calculates the mean and sigma for the trigger tower corresponding to the eta/phi/fcalLayer
template <class dataType>
bool PixelMap<dataType>::GetTriggerTowerMeanAndSigma(const float eta,const float phi,double& mean,double& sigma,const FcalLayer fcalLayer){
	
	if(pixelSize != TrigTower){
		std::cerr << "PixelMap::GetTriggerTowerMeanAndSigma: Pixel Size is not set for Trigger Tower, it is: " << pixelSize << std::endl;
		return false;
	}
	if(!useProfile){
		std::cerr << "PixelMap::GetTriggerTowerMeanAndSigma: Must be in Profile Mode to use this method.\n";
		return false;
	}
	
	unsigned int tempEta = ftoiEta(eta);
	unsigned int iEta = itoiEtaTt(tempEta,fcalLayer);
	
	unsigned int tempPhi = ftoiPhi(phi);
	unsigned int iPhi = itoiPhiTt(tempPhi,iEta);
	
	unsigned int etaPhiID = GetEtaPhiID(iEta,iPhi);
	
	typename std::map<unsigned int,double>::iterator itSum;
	typename std::map<unsigned int,double>::iterator itSum2;
	typename std::map<unsigned int,unsigned int>::iterator itN;
	
	// get trigger tower sum
	itSum = mTtSum.find(etaPhiID);
	if(itSum == mTtSum.end()){
// 		std::cerr << "    no sum entry found.";
		// Since no Trigger Tower sum was found, lets create one and initialize it to zero.
		if(!ClearTriggerTowerStats(etaPhiID))
			return false;
		
		return true;
	}
	else{
		// have the sum now we get the sum sqaured
		itSum2 = mTtSum2.find(etaPhiID);
		if(itSum2 == mTtSum2.end()){
			// didn't find sum2.
			// output error since we should always have a Sum^2 if we have a sum.
			std::cerr << "PixelMap::GetTriggerTowerMeanAndSigma: [ERROR] Found a Sum for the Trigger Tower, but no Sum Squared. Resetting Jet Element Statistics to Zero. eta: " << eta << " phi: " << phi << std::endl;
			
			// now I will zero the elements statistics
			if(!ClearTriggerTowerStats(etaPhiID))
				return false;
			
			return true;
			
		}
		else{
			// we have a sum and sum squared. Need to find the N
			itN   = mTtN.find(etaPhiID);
			if(itN == mTtN.end()){
				// Since no N for this jet element was found
				// output error since we should always have a N if we have a sum and sum^2.
				std::cerr << "PixelMap::GetTriggerTowerMeanAndSigma: [ERROR] Found a Sum and Sum Squared for the Trigger Tower, but no counter. Resetting Jet Element Statistics to Zero for eta: " << eta << " phi: " << phi << std::endl;
				
				// now I will zero the elements statistics
				if(!ClearTriggerTowerStats(etaPhiID))
					return false;
				
				return true;
			}
			else{
				// got everything we need
				mean = 0;
				sigma = 0;
				if(itN->second != 0){
					mean = ((double)itSum->second/(double)itN->second);
					sigma = (double)sqrt( (1.0/(double)itN->second)*(double)itSum2->second - mean*mean);
				}
				return true;
			}
		}
	}
	
	return false;
	
}

template <class dataType>
bool PixelMap<dataType>::SetTriggerTower(const float eta,const float phi,const dataType value,const FcalLayer fcalLayer){
	
	if(pixelSize != TrigTower){
		std::cerr << "PixelMap::SetTriggerTower: Pixel Size is not set to TrigTower, it is: " << pixelSize << std::endl;
		return false;
	}
		
	unsigned int tempEta = ftoiEta(eta);
	unsigned int iEta = itoiEtaTt(tempEta,fcalLayer);
	
	unsigned int tempPhi = ftoiPhi(phi);
	unsigned int iPhi = itoiPhiTt(tempPhi,iEta);
	
	unsigned int etaPhiID = GetEtaPhiID(iEta,iPhi);
	
// 	std::cerr << "      etaPhiId: " << std::hex << etaPhiID << std::dec << std::endl;
	
	if(useProfile){
		typename std::map<unsigned int,double>::iterator itSum,itSum2;
		typename std::map<unsigned int,unsigned int>::iterator itN;
		
		if(!SetTriggerTowerSum(etaPhiID,(double)value)){
			return false;
		}
		
		if(!SetTriggerTowerSum2(etaPhiID,((double)value*(double)value))){
			return false;
		}
		
		if(!IncrementTriggerTowerN(etaPhiID)){
			return false;
		}
	}
	else{
		
		mTtBins[etaPhiID] = value;
		
		if(!SetTtHistoBins(etaPhiID)){
			//std::cerr << "PixelMap::SetTriggerTower: input eta/phi: " << eta << "/" << phi << "; iEta/iPhi: " << iEta << "/" << iPhi << std::endl;
			
			return false;
			
		}
	}
	
	return true;
}

// This is used internally to set a trigger tower directly
template <class dataType>
bool PixelMap<dataType>::SetTriggerTower(const unsigned int etaPhiID,dataType value){
	if(pixelSize != TrigTower){
		std::cerr << "PixelMap::SetTriggerTower(unsigned int,dataType): Pixel Size is not set to TrigTower, it is: " << pixelSize << std::endl;
		return false;
	}
	if(useProfile){
		std::cerr << "PixelMap::SetTriggerTower(unsigned int,dataType): must not be in Profile Mode to use this method.\n";
		return false;
	}
	
	
	mTtBins[etaPhiID] = value;
	
	if(!SetTtHistoBins(etaPhiID)){
		return false;
	}
	
	return true;
	
}

// Sets the Sum/Sum2/N elements to 0 for the trigger tower corresponding to the etaPhiID passed
template <class dataType>
bool PixelMap<dataType>::ClearTriggerTowerStats(const unsigned int etaPhiID){
	
	if(pixelSize != JetEl){
		std::cerr << "PixelMap::ClearTriggerTowerStats: Pixel Size is not set to Trigger Tower, it is: " << pixelSize << std::endl;
		return false;
	}
	if(!useProfile){
		std::cerr << "PixelMap::ClearTriggerTowerStats: must be in Profile Mode to use this method.\n";
		return false;
	}
	
	std::map<unsigned int,double>::iterator itSum;
	itSum = mTtSum.find(etaPhiID);
	if(itSum == mTtSum.end()){
		mTtSum[etaPhiID] = 0;
	}
	else{
		itSum->second = 0;
	}
	
	std::map<unsigned int,double>::iterator itSum2;
	itSum2 = mTtSum2.find(etaPhiID);
	if(itSum2 == mTtSum2.end()){
		mTtSum2[etaPhiID] = 0;
	}
	else{
		itSum2->second = 0;
	}
	
	std::map<unsigned int,unsigned int>::iterator itN;
	itN = mTtN.find(etaPhiID);
	if(itN == mTtN.end()){
		mTtN[etaPhiID] = 0;
	}
	else{
		itN->second = 0;
	}
	
	return true;
}

// If this trigger tower already has a value in it the passed value is added to this sum
// otherwise the trigger tower is set to the passed value.
template <class dataType>
bool PixelMap<dataType>::SetTriggerTowerSum(const unsigned int etaPhiID,const double value){
	
	if(pixelSize != TrigTower){
		std::cerr << "PixelMap::SetTriggerTowerSum: Pixel Size is not correctly set, " << pixelSize << std::endl;
		return false;
	}
	if(!useProfile){
		std::cerr << "PixelMap::SetTriggerTowerSum: must be in Profile Mode to use this method.\n";
		return false;
	}
	
	std::map<unsigned int,double>::iterator itSum;
	itSum = mTtSum.find(etaPhiID);
	if(itSum == mTtSum.end()){
		mTtSum[etaPhiID] = value;
		return true;
	}
	else{
		itSum->second = itSum->second + value;
		return true;
	}
	
	return false;
}

// If this trigger tower already has a value in it the passed valueSquared is added to this sum
// otherwise the trigger tower is set to the passed valueSquared.
template <class dataType>
bool PixelMap<dataType>::SetTriggerTowerSum2(const unsigned int etaPhiID,const double valueSquared){
	
	if(pixelSize != TrigTower){
		std::cerr << "PixelMap::SetTriggerTowerSum2: Pixel Size is not correctly set, " << pixelSize << std::endl;
		return false;
	}
	if(!useProfile){
		std::cerr << "PixelMap::SetTriggerTowerSum2: must be in Profile Mode to use this method.\n";
		return false;
	}
	
	std::map<unsigned int,double>::iterator itSum2;
	itSum2 = mTtSum2.find(etaPhiID);
	if(itSum2 == mTtSum2.end()){
		mTtSum2[etaPhiID] = valueSquared;
		return true;
	}
	else{
		itSum2->second = itSum2->second + valueSquared;
		return true;
	}
	
	return false;
}

template <class dataType>
bool PixelMap<dataType>::IncrementTriggerTowerN(const unsigned int etaPhiID,const unsigned int value){
	
	if(pixelSize != TrigTower){
		std::cerr << "PixelMap::IncrementTriggerTowerN: Pixel Size is not correctly set, " << pixelSize << std::endl;
		return false;
	}
	if(!useProfile){
		std::cerr << "PixelMap::IncrementTriggerTowerN: must be in Profile Mode to use this method.\n";
		return false;
	}
	
	std::map<unsigned int,unsigned int>::iterator itN;
	itN = mTtN.find(etaPhiID);
	if(itN == mTtN.end()){
		mTtN[etaPhiID] = value;
		return true;
	}
	else{
		itN->second = itN->second + value;
		return true;
	}
	return true;
}

// This returns the histogram bin value for the given eta phi coordinate
template <class dataType>
dataType PixelMap<dataType>::GetHistoBin(const unsigned int eta,const unsigned int phi){
	unsigned int etaPhiID = GetEtaPhiID(eta,phi);
	typename std::map<unsigned int,dataType>::iterator it;
	it = mHistoBins.find(etaPhiID);
	if(it == mHistoBins.end()){
		//std::cerr << "PixelMap::GetHistoBin: eta phi ID, " << std::hex << etaPhiID << std::dec << ", not found in Histogram Bin map.\n";
		return 999;
	}
	
	return it->second;
}

// Get the eta/phi histograms
template <class dataType>
TH2* PixelMap<dataType>::GetEtaPhiHistogram(std::string name,std::string title){
   
   if(typeid(dataType) == typeid(int) || typeid(dataType) == typeid(unsigned int)){
      TH2I *th2i = new TH2I(name.c_str(),title.c_str(),L1CALO_ETA_TT,-4.9,4.9,L1CALO_PHI_TT,0,2*PI);
      FillEtaPhiHistogram(th2i);
      return th2i;
   }
   else if(typeid(dataType) == typeid(short int) || typeid(dataType) == typeid(unsigned short int)){
      TH2S *th2s = new TH2S(name.c_str(),title.c_str(),L1CALO_ETA_TT,-4.9,4.9,L1CALO_PHI_TT,0,2*PI);
      FillEtaPhiHistogram(th2s);
      return th2s;
   }
   else if(typeid(dataType) == typeid(char) || typeid(dataType) == typeid(unsigned char)){
      TH2C *th2c = new TH2C(name.c_str(),title.c_str(),L1CALO_ETA_TT,-4.9,4.9,L1CALO_PHI_TT,0,2*PI);
      FillEtaPhiHistogram(th2c);
      return th2c;
   }
   else if(typeid(dataType) == typeid(float)){
      TH2F *th2f = new TH2F(name.c_str(),title.c_str(),L1CALO_ETA_TT,-4.9,4.9,L1CALO_PHI_TT,0,2*PI);
      FillEtaPhiHistogram(th2f);
      return th2f;
   }
   else if(typeid(dataType) == typeid(double)){
      TH2D *th2d = new TH2D(name.c_str(),title.c_str(),L1CALO_ETA_TT,-4.9,4.9,L1CALO_PHI_TT,0,2*PI);
      FillEtaPhiHistogram(th2d);
      return th2d;
   }
   else{
      TH2D *th2d = new TH2D(name.c_str(),title.c_str(),L1CALO_ETA_TT,-4.9,4.9,L1CALO_PHI_TT,0,2*PI);
      FillEtaPhiHistogram(th2d);
      return th2d;
   }
   
   return (TH2*)0;
}

// Fills the passed TH2 histogram with the mHistoBins map values
// Expecting histogram like this:
// TH2D("","",L1CALO_ETA_TT,-4.9,4.9,L1CALO_PHI_TT,0,2*pi); pi = 3.14159265
template <class dataType>
void PixelMap<dataType>::FillEtaPhiHistogram(TH2* histo){
	
	dataType value=0;
	for(int i=0;i<L1CALO_ETA_TT;i++) for(int j=0;j<L1CALO_PHI_TT;j++){
		value = GetHistoBin(i,j);
		if((unsigned int)value == 999) continue; // no value set for this TT
		
		histo->Fill((double)(itofEta(i)+0.02),(double)(itofPhi(j)+0.02),(double)value);
	
		//std::cerr << i << ":" << j << " / " << itofEta(i) << ":" << itofPhi(j) << " ++++ " << pixel[i][j] << std::endl;
	}
	
}

// Get the eta/phi histograms
template <class dataType>
std::vector<TH2*> PixelMap<dataType>::GetEtaPhiHistograms(std::string nameMean,std::string titleMean,std::string nameSigma,std::string titleSigma){
   
   std::vector<TH2*> out;
   
   if(typeid(dataType) == typeid(int) || typeid(dataType) == typeid(unsigned int)){
      TH2I *mean = new TH2I(nameMean.c_str(),titleMean.c_str(),L1CALO_ETA_TT,-4.9,4.9,L1CALO_PHI_TT,0,2*PI);
      TH2I *sigma = new TH2I(nameSigma.c_str(),titleSigma.c_str(),L1CALO_ETA_TT,-4.9,4.9,L1CALO_PHI_TT,0,2*PI);
      out.push_back(mean);
      out.push_back(sigma);
      FillEtaPhiHistograms(out);
      return out;
   }
   else if(typeid(dataType) == typeid(short int) || typeid(dataType) == typeid(unsigned short int)){
      TH2S *mean = new TH2S(nameMean.c_str(),titleMean.c_str(),L1CALO_ETA_TT,-4.9,4.9,L1CALO_PHI_TT,0,2*PI);
      TH2S *sigma = new TH2S(nameSigma.c_str(),titleSigma.c_str(),L1CALO_ETA_TT,-4.9,4.9,L1CALO_PHI_TT,0,2*PI);
      out.push_back(mean);
      out.push_back(sigma);
      FillEtaPhiHistograms(out);
      return out;
   }
   else if(typeid(dataType) == typeid(char) || typeid(dataType) == typeid(unsigned char)){
      TH2C *mean = new TH2C(nameMean.c_str(),titleMean.c_str(),L1CALO_ETA_TT,-4.9,4.9,L1CALO_PHI_TT,0,2*PI);
      TH2C *sigma = new TH2C(nameSigma.c_str(),titleSigma.c_str(),L1CALO_ETA_TT,-4.9,4.9,L1CALO_PHI_TT,0,2*PI);
      out.push_back(mean);
      out.push_back(sigma);
      FillEtaPhiHistograms(out);
      return out;
   }
   else if(typeid(dataType) == typeid(float)){
      TH2F *mean = new TH2F(nameMean.c_str(),titleMean.c_str(),L1CALO_ETA_TT,-4.9,4.9,L1CALO_PHI_TT,0,2*PI);
      TH2F *sigma = new TH2F(nameSigma.c_str(),titleSigma.c_str(),L1CALO_ETA_TT,-4.9,4.9,L1CALO_PHI_TT,0,2*PI);
      out.push_back(mean);
      out.push_back(sigma);
      FillEtaPhiHistograms(out);
      return out;
   }
   else if(typeid(dataType) == typeid(double)){
      TH2D *mean = new TH2D(nameMean.c_str(),titleMean.c_str(),L1CALO_ETA_TT,-4.9,4.9,L1CALO_PHI_TT,0,2*PI);
      TH2D *sigma = new TH2D(nameSigma.c_str(),titleSigma.c_str(),L1CALO_ETA_TT,-4.9,4.9,L1CALO_PHI_TT,0,2*PI);
      out.push_back(mean);
      out.push_back(sigma);
      FillEtaPhiHistograms(out);
      return out;
   }
   else{
      TH2D *mean = new TH2D(nameMean.c_str(),titleMean.c_str(),L1CALO_ETA_TT,-4.9,4.9,L1CALO_PHI_TT,0,2*PI);
      TH2D *sigma = new TH2D(nameSigma.c_str(),titleSigma.c_str(),L1CALO_ETA_TT,-4.9,4.9,L1CALO_PHI_TT,0,2*PI);
      out.push_back(mean);
      out.push_back(sigma);
      FillEtaPhiHistograms(out);
      return out;
   }
   
   return out;
}

// For a profile plot, this takes a vector with two histograms and fills the first
// with the means for each pixel and the second with the sigma for each pixel.
// Expecting histogram like this:
// TH2D("","",L1CALO_ETA_TT,-4.9,4.9,L1CALO_PHI_TT,0,2*pi); pi = 3.14159265
template <class dataType>
void PixelMap<dataType>::FillEtaPhiHistograms(std::vector<TH2D*> histo){
	
	if(!useProfile){
		std::cerr << "PixelMap::FillEtaPhiHistograms: Must be in profile mode to use this method.\n";
		return;
	}
   
   if(histo.size() != 2){
      std::cerr << "PixelMap::FillEtaPhiHistograms: vector passed has invalid number of histograms: " << histo.size() << std::endl;
      return;
   }
	
	// Expecting histogram like above, but an array of 2
	// the first will be Mean
	// the second will be Sigma
	{
		typename std::map<unsigned int,double>::iterator itSum,itSum2;
		typename std::map<unsigned int,unsigned int>::iterator itN;
		
		itSum  = mTtSum.begin();
		itSum2 = mTtSum2.begin();
		itN    = mTtN.begin();
		
		// Loop over sum/sum2/n and calculate mean
		// fill each trigger tower with that mean and set the histogram
		// bins appropriately
		for(;itSum != mTtSum.end() && itSum2 != mTtSum2.end() && itN != mTtN.end()
				;itSum++,itSum2++,itN++){
			
			const unsigned int etaPhiID = itSum->first;
			
			double mean = 0;
			if(itN->second != 0)
				mean = (itSum->second/(double)itN->second);
			
			mTtBins[etaPhiID] = (dataType)mean;
			
			SetTtHistoBins(etaPhiID);
		}
		
		FillEtaPhiHistogram(histo[0]);
	}
	
	// now calculate sigma
	{
		typename std::map<unsigned int,double>::iterator itSum,itSum2;
		typename std::map<unsigned int,unsigned int>::iterator  itN;
		
		itSum  = mTtSum.begin();
		itSum2 = mTtSum2.begin();
		itN    = mTtN.begin();
		
		for(;itSum != mTtSum.end() && itSum2 != mTtSum2.end() && itN != mTtN.end();
				itSum++,itSum2++,itN++){
			
			unsigned int etaPhiID = itSum->first;
			
			double mean = 0;
			if(itN->second != 0)
				mean = (itSum->second/(double)itN->second);
			
			double sigma = 0;
			if(itN->second != 0)
				sigma = (double)sqrt( (1.0/(double)itN->second)*itSum2->second - mean*mean);
			
			mTtBins[etaPhiID] = (dataType)sigma;
			
			SetTtHistoBins(etaPhiID);
		}
		
		FillEtaPhiHistogram(histo[1]);
	}
	
	
}


template <class dataType>
bool PixelMap<dataType>::SetJetElHistoBins(const unsigned int etaPhiID){
	typename std::map<unsigned int,std::vector<unsigned int> >::iterator itJetElTrans;
	itJetElTrans = mJetElPixelToBin.find(etaPhiID);
	if(itJetElTrans == mJetElPixelToBin.end()){
		std::cerr << "PixelMap::SetJetElHistoBins: eta phi ID, " << std::hex << etaPhiID << std::dec << ", not found in Jet Elment Pixel to Bin map.\n";
		return false;
	}
	
	typename std::map<unsigned int,dataType>::iterator itJetElValue;
	itJetElValue = mJetElBins.find(etaPhiID);
	if(itJetElValue == mJetElBins.end()){
		std::cerr << "PixelMap::SetJetElHistoBins: eta phi ID, " << std::hex << etaPhiID << std::dec << ", not found in Jet Elment Bin map.\n";
		return false;
	}
	
	for(unsigned int i=0;i<itJetElTrans->second.size();i++){
		mHistoBins[itJetElTrans->second[i]] = itJetElValue->second;
	}
	
	return true;
	
}

template <class dataType>
bool PixelMap<dataType>::SetTtHistoBins(const unsigned int etaPhiID){
	typename std::map<unsigned int,std::vector<unsigned int> >::iterator itTtTrans;
	itTtTrans = mTtPixelToBin.find(etaPhiID);
	if(itTtTrans == mTtPixelToBin.end()){
		unsigned int eta,phi; GetEtaPhiFromID(etaPhiID,eta,phi);
		std::cerr << "PixelMap::SetTtHistoBins: eta phi ID, " << std::hex << etaPhiID << std::dec << " (" << (int)(eta-49) << "/" << phi << "), not found in Trigger Tower Pixel to Bin map.\n";
		return false;
	}
	
	typename std::map<unsigned int,dataType>::iterator itTtValue;
	itTtValue = mTtBins.find(etaPhiID);
	if(itTtValue == mTtBins.end()){
		unsigned int eta,phi; GetEtaPhiFromID(etaPhiID,eta,phi);
		std::cerr << "PixelMap::SetTtHistoBins: eta phi ID, " << std::hex << etaPhiID << std::dec <<  " (" << (int)(eta-49) << "/" << phi << "), not found in Trigger Tower Bin map.\n";
		return false;
	}
	
	for(unsigned int i=0;i<itTtTrans->second.size();i++){
		mHistoBins[itTtTrans->second[i]] = itTtValue->second;
	}
	
	return true;
	
}

template <class dataType>
unsigned int PixelMap<dataType>::ftoiEta(float eta)
{
	
	float shiftedEta = eta + 4.9;
	unsigned int iEta = (unsigned int)floor(shiftedEta*10.0);
	
	if(fabs(shiftedEta*10.0 - (unsigned int)(iEta+1)) < 0.01) iEta++;
	if(fabs(shiftedEta) < 0.01) iEta = 0;
	
// 	std::cerr << "eta: " << eta << "; iEta: " << iEta << std::endl;
	
	return iEta;
}

template <class dataType>
unsigned int PixelMap<dataType>::itoiEtaJetEl(unsigned int eta){

        unsigned int iEta=999;
        if( (eta < -32 + 49) ){
                iEta = -49 + 49;
        }
        else if( (-32 + 49 <= eta && eta < -29 + 49) ){
                iEta = -32 + 49;
        }
        else if( (-29 + 49 <= eta && eta < -27 + 49) ){
                iEta = -29 + 49;
        }
        else if( (-27 + 49 <= eta && eta < -24 + 49) ){
                iEta = -27 + 49;
        }
        else if( (-24 + 49 <= eta && eta < 24 + 49) ){
                iEta = eta - ((eta-1) % 2);
        }
        else if( (24 + 49 <= eta && eta < 27 + 49) ){
                iEta = 24 + 49;
        }
        else if( (27 + 49 <= eta && eta < 29 + 49) ){
                iEta = 27 + 49;
        }
        else if( (29 + 49 <= eta && eta < 32 + 49) ){
                iEta = 29 + 49;
        }
        else if( (32 + 49 <= eta && eta < 49 + 49) ){
                iEta = 32 + 49;
        }

        return iEta;
}

template <class dataType>
unsigned int PixelMap<dataType>::itoiEtaTt(unsigned int eta, FcalLayer fcalLayer){

        unsigned int iEta=999;
        if( (eta < -32 + 49) ){
		if(fcalLayer.GetFcalLayer() == FcalLayer::FCAL2){ // want to remap to FCAL2 Layer
			if(eta < -40 + 49)
				iEta = -40 + 49; // Want -4.9 to -4.0 FCAL2 bin to be the -4.0 to -3.6 bin
			else if(-40 + 49 <= eta && eta < -32 + 49)
				iEta = -36 + 49; // Want -4.0 to -3.2 FCAL2 bin to be the -3.6 to -3.2 bin
		}
		else if(fcalLayer.GetFcalLayer() == FcalLayer::FCAL3){ // want to remap to FCAL3 Layer
			if(eta < -40 + 49)
				iEta = -49 + 49; // Want -4.9 to -4.0 FCAL3 bin to be the -4.9 to -4.4 bin
			else if(-40 + 49 <= eta && eta < -32 + 49)
				iEta = -44 + 49; // Want -4.0 to -3.2 FCAL3 bin to be the -4.4 to -4.0 bin
		}
		else{ // No mapping required
		
			if( (eta < -44 + 49) ){
				iEta = -49 + 49;
			}
			else if( (-44 + 49 <= eta && eta < -40 + 49)){
				iEta = -44 + 49;
			}
			else if( (-40 + 49 <= eta && eta < -36 + 49)){
				iEta = -40 + 49;
			}
			else if( (-36 + 49 <= eta && eta < -32 + 49)){
				iEta = -36 + 49;
			}
		}	
        }
        else if( (-32 + 49 <= eta && eta < -31 + 49) ){
                iEta = -32 + 49;
        }
        else if( (-31 + 49 <= eta && eta < -25 + 49) ){
                if( (-31 + 49 <= eta && eta < -29 + 49) ){
                        iEta = -31 + 49;
                }
                else if( (-29 + 49 <= eta && eta < -27 + 49) ){
                        iEta = -29 + 49;
                }
                else if( (-27 + 49 <= eta && eta < -25 + 49) ){
                        iEta = -27 + 49;
                }
        }
	else if( (-25 + 49 <= eta && eta < 25 + 49) ){
                iEta = eta;
        }
        else if( (25 + 49 <= eta && eta < 31 + 49) ){
                if( (25 + 49 <= eta && eta < 27 + 49) ){
                        iEta = 25 + 49;
                }
                else if( (27 + 49 <= eta && eta < 29 + 49) ){
                        iEta = 27 + 49;
                }
                else if( (29 + 49 <= eta && eta < 31 + 49) ){
                        iEta = 29 + 49;
                }

        }
        else if( (31 + 49 <= eta && eta < 32 + 49) ){
                iEta = 31 + 49;
        }
        else if( (32 + 49 <= eta && eta < 49 + 49) ){
		if(fcalLayer.GetFcalLayer() == FcalLayer::FCAL2){ // want to remap to FCAL2 Layer
			if(32 + 49 <= eta && eta < 40 + 49)
				iEta = 32 + 49; // Want 3.2 to 4.0 FCAL2 bin to be the 3.2 to 3.6 bin
			else if(40 + 49 <= eta && eta < 49 + 49)
				iEta = 36 + 49; // Want 4.0 to 4.9 FCAL2 bin to be the 3.6 to 4.0 bin
		}
		else if(fcalLayer.GetFcalLayer() == FcalLayer::FCAL3){ // want to remap to FCAL3 Layer
			if(32 + 49 <= eta && eta < 40 + 49)
				iEta = 40 + 49; // Want 3.2 to 4.0 FCAL3 bin to be the 4.0 to 4.4 bin
			else if(40 + 49 <= eta && eta < 49 + 49)
				iEta = 44 + 49; // Want 4.0 to 4.9 FCAL3 bin to be the 4.4 to 4.9 bin
		}
		else{ // No mapping required
			if( (32 + 49 <= eta && eta < 36 + 49) ){
				iEta = 32 + 49;
			}
			else if( (36 + 49 <= eta && eta < 40 + 49)){
				iEta = 36 + 49;
			}
			else if( (40 + 49 <= eta && eta < 44 + 49)){
				iEta = 40 + 49;
			}
			else if( (44 + 49 <= eta && eta < 49 + 49)){
				iEta = 44 + 49;
			}
		}	
        }
	
	//if(iEta == 999) std::cerr << "PixelMap::itoiEtaTt: Returning 999\n";
	
        return iEta;
}

template <class dataType>
float PixelMap<dataType>::itofEta(unsigned int eta)
{
	if(eta == 49) return 0.0;
	else return (float)eta/10.0 - 4.9;
}

template <class dataType>
unsigned int PixelMap<dataType>::ftoiPhi(float phi)
{
	
	float tempPhi = phi/(2.0*PI/64.0);
	unsigned int iPhi = (unsigned int)floor(tempPhi);
	if(fabs(tempPhi - ((int)tempPhi+1)) < 0.01) iPhi++;
	return iPhi;
}

template <class dataType>
unsigned int PixelMap<dataType>::itoiPhiJetEl(unsigned int phi, unsigned int eta){

        unsigned int iPhi=999;
        if( (eta < -32 + 49) ){
                iPhi = phi - (phi % 4);
        }
        else if( (-32 + 49 <= eta && eta < 32 + 49) ){
                iPhi = phi - (phi % 2);
        }
        else if( (32 + 49 <= eta && eta < 49 + 49) ){
                iPhi = phi - (phi % 4);
        }

        return iPhi;
}

template <class dataType>
unsigned int PixelMap<dataType>::itoiPhiTt(unsigned int phi,unsigned int eta){
        unsigned int iPhi=999;
        if( (eta < -32 + 49) ){
                iPhi = phi - (phi % 4);
        }
        else if( (-32 + 49 <= eta && eta < -25 + 49) ){
                iPhi = phi - (phi % 2);
        }
        else if( (-25 + 49 <= eta && eta < 25 + 49) ){
                iPhi = phi;
        }
        else if( (25 + 49 <= eta && eta < 32 + 49) ){
                iPhi = phi - (phi % 2);
        }
        else if( (32 + 49 <= eta && eta < 49 + 49) ){
                iPhi = phi - (phi % 4);
        }

        return iPhi;
}

template <class dataType>
float PixelMap<dataType>::itofPhi(unsigned int phi)
{
	return phi*(2.0*PI/64.0);
}



#endif


