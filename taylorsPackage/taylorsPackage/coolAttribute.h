#ifndef COOLATTRIBUTE_H
#define COOLATTRIBUTE_H

#include <string>
#include <vector>
#include <iostream>
#include <cmath>

#include "taylorsPackage/coolAttributeSinglet.h"

#include "CoolKernel/StorageType.h"

#include "TH1D.h"
#include "TH1S.h"
#include "TH1I.h"
#include "TH1F.h"
#include "TH1C.h"
#include "TDatime.h"
// #include "TCanvas.h"
// #include "TF1.h"

template <class dataType = uint>
class coolAttribute{
public:
	coolAttribute(){m_makeHisto=true;m_sum=0;m_sum2=0;m_n=0;};
	coolAttribute(std::string name,cool::StorageType::TypeId type)
		{m_name = name;m_type=type;};
	~coolAttribute(){};
	
	std::string* GetName(void){return &m_name;};
	void SetName(std::string name){m_name = name;};
	
	cool::StorageType::TypeId GetStorageType(void){return m_type;};
	void SetStorageType(cool::StorageType::TypeId type){m_type = type;};
	
	void push_back(coolAttributeSinglet<dataType> attr);
	
	coolAttributeSinglet<dataType>* operator [] (uint i) {return &m_attrList[i];};
	uint GetEntries(void){return m_attrList.size();};
	
	coolAttributeSinglet<dataType>* front(void){ return &m_attrList.front();};
	coolAttributeSinglet<dataType>* back(void){ return &m_attrList.back();};
	
	void SetCoolId(uint id){m_coolId=id;};
	uint GetCoolId(void){return m_coolId;};
	
	TH1* GetHistogram(void);
	
	double GetMean(void){return m_sum/(double)m_n;};
	double GetSigma(void){double mean = GetMean();
		return sqrt((1.0/(double)m_n)*m_sum2 - mean*mean);};
	
	double GetSum(void){return m_sum;};
	double GetSum2(void){return m_sum2;};
	uint GetN(void){return m_n;};
	
	double GetLinearConstant(void){return m_linearConst;};
	double GetLinearSlope(void){return m_linearSlope;};
	double GetLinearChisquared(void){return m_linearChisquared;};
private:
	
	std::string               m_name;
	cool::StorageType::TypeId m_type;
	
	std::vector<coolAttributeSinglet<dataType> > m_attrList;
	
	TH1* m_timeDepHisto;
	bool m_makeHisto;
	
	uint m_coolId;
	
	double m_sum;
	double m_sum2;
	uint   m_n;
	
	double m_linearConst;
	double m_linearSlope;
	double m_linearChisquared;
	
};

// add a value to this cool attribute
template <class dataType>
void coolAttribute<dataType>::push_back(coolAttributeSinglet<dataType> attr){
	m_attrList.push_back(attr);
	m_makeHisto=true;
	if(!attr.IsDisabled()){
		m_sum+=attr.GetValue();
		m_sum2+=attr.GetValue()*attr.GetValue();
		m_n++;
	}
}

// produce a 1D histogram with time on x axis
template <class dataType>
TH1* coolAttribute<dataType>::GetHistogram(void){
	
	if(m_makeHisto){
		const uint maxBins = 200;
		double* binLowEdge = new double [maxBins];
		
		TDatime firstStartTime(m_attrList[0].GetStartIOV());
		
		uint timeEntries=0;
		for(;timeEntries<m_attrList.size() && timeEntries < maxBins;timeEntries++){
			TDatime startTime(m_attrList[timeEntries].GetStartIOV());
			
			binLowEdge[timeEntries] = (startTime.Convert() - firstStartTime.Convert());
		}
		
		// End the bin list with the last end time
		TDatime lastTime(m_attrList.back().GetEndIOV());
		binLowEdge[timeEntries] = lastTime.Convert() - firstStartTime.Convert();
		
		// linear fit for histogram
// 		TF1* line = new TF1("line","pol1",binLowEdge[0],binLowEdge[timeEntries]);
// 		line->SetParameters(GetMean(),0.001);
// 		
		char name[100];
		sprintf(name,"%s_timeDep_%08x",m_name.c_str(),m_coolId);
		char title[100];
		sprintf(title,"%s: Time Dependence for CoolId %08x",m_name.c_str(),m_coolId);
		
		TH1* histo = 0;
		switch(m_type){
		case cool::StorageType::Int32:
		{
			TH1I* temp = new TH1I(name,title,timeEntries,binLowEdge);
			histo = dynamic_cast<TH1*>(temp);
			break;
		}
		case cool::StorageType::UInt32:
		{
			TH1I* temp = new TH1I(name,title,timeEntries,binLowEdge);
			histo = dynamic_cast<TH1*>(temp);
			break;
		}
		case cool::StorageType::Int16:
		{
			TH1S* temp = new TH1S(name,title,timeEntries,binLowEdge);
			histo = dynamic_cast<TH1*>(temp);
			break;
		}
		case cool::StorageType::UInt16:
		{
			TH1S* temp = new TH1S(name,title,timeEntries,binLowEdge);
			histo = dynamic_cast<TH1*>(temp);
			break;
		}
		case cool::StorageType::UChar:
		{
			TH1C* temp = new TH1C(name,title,timeEntries,binLowEdge);
			histo = dynamic_cast<TH1*>(temp);
			break;
		}
		case cool::StorageType::Float:
		{
			TH1F* temp = new TH1F(name,title,timeEntries,binLowEdge);
			histo = dynamic_cast<TH1*>(temp);
			break;
		}
		case cool::StorageType::Double:
		{
			TH1D* temp = new TH1D(name,title,timeEntries,binLowEdge);
			histo = dynamic_cast<TH1*>(temp);
			break;
		}
		default:
			std::cerr << "[coolAttribute::GetHistogram] Error: Incorrect Data Type.\n";
			break;
		}
		
		for(uint entry=0;entry<m_attrList.size();entry++){
			if(!m_attrList[entry].IsDisabled())
				histo->SetBinContent(entry+1,m_attrList[entry].GetValue());
		}
		
		m_timeDepHisto = histo;
		m_makeHisto = false;
		
		m_timeDepHisto->GetXaxis()->SetTimeDisplay(1);
		m_timeDepHisto->GetXaxis()->SetTimeOffset(firstStartTime.Convert());
		m_timeDepHisto->GetXaxis()->SetTimeFormat("%d-%m-%Y");
		m_timeDepHisto->SetBarWidth(0.90);
		m_timeDepHisto->SetLineColor(kBlack);
		m_timeDepHisto->SetFillColor(kWhite);
		char yTitle[100];
		sprintf(yTitle,"DacOffset (mean = %f +/- %f)",GetMean(),GetSigma());
		m_timeDepHisto->GetYaxis()->SetTitle(yTitle);
		
// 		m_timeDepHisto->Fit(line,"rq");
// 		
// 		m_linearConst = line->GetParameter(0);
// 		m_linearSlope = line->GetParameter(1);
// 		m_linearChisquared = line->GetChisquare();
// 		
// 		std::cerr << "y = " << m_linearSlope << "x + " << m_linearConst << " : " << m_linearChisquared << std::endl;
		
// 		TCanvas canvas("canvas","canvas",0,0,800,600);
// 		m_timeDepHisto->Draw();
// 		canvas.Update();
// 		std::cin.get();
		
	}
	
	return m_timeDepHisto;
}



#endif

