////////////////////////////////////////////////////////////////
/// L1Calo Channel Mapping Tool
/// J Taylor Childers III
/// Heidelberg Universitaet
///
/// 
///
////////////////////////////////////////////////////////////////

#ifndef CALODIVISION_H
#define CALODIVISION_H

#include <string>

class CaloDivision{
public:
   
   enum  CaloDivisionEnum {
      LArFCAL1C = 0, 
      LArEMECC = 1, 
      LArOverlapC = 2, 
      LArEMBC = 3,
      LArEMBA = 4, 
      LArOverlapA = 5, 
      LArEMECA = 6, 
      LArFCAL1A = 7,
      LArFCAL23C = 8, 
      LArHECC = 9, 
      TileEBC = 10, 
      TileLBC = 11,
      TileLBA = 12, 
      TileEBA = 13, 
      LArHECA = 14, 
      LArFCAL23A = 15,
      NUM_DIVISIONS = 16,
      Invalid = 17
   };
   
   CaloDivision(CaloDivisionEnum division):m_division(division){};
   CaloDivision(void):m_division(Invalid){};
   ~CaloDivision(void){};
   
   void SetDivision(CaloDivisionEnum division){m_division = division;};
   CaloDivisionEnum GetDivision(void) const {return m_division;};
   
   std::string GetString(void) const {
      switch(m_division){
      case LArFCAL1C:
         return "LArFCAL1C";
      case LArEMECC:
         return "LArEMECC";
      case LArOverlapC:
         return "LArOverlapC";
      case LArEMBC:
         return "LArEMBC";
      case LArEMBA:
         return "LArEMBA";
      case LArOverlapA:
         return "LArOverlapA";
      case LArEMECA:
         return "LArEMECA";
      case LArFCAL1A:
         return "LArFCAL1A";
      case LArFCAL23C:
         return "LArFCAL23C";
      case LArHECC:
         return "LArHECC";
      case TileEBC:
         return "TileEBC";
      case TileLBC:
         return "TileLBC";
      case TileLBA:
         return "TileLBA";
      case TileEBA:
         return "TileEBA";
      case LArHECA:
         return "LArHECA";
      case LArFCAL23A:
         return "LArFCAL23A";
      case NUM_DIVISIONS:
         return "NUM_DIVISIONS";
      case Invalid:
      default:
         return "Invalid";
      }
      return "Invalid";
   };
   
   bool IsSet(void) const {return (m_division == Invalid) ? false : true;};
   bool IsLArFCAL1C(void) const {if(m_division == LArFCAL1C) return true; return false;};
   bool IsLArFCAL1A(void) const {if(m_division == LArFCAL1A) return true; return false;};
   bool IsLArFCAL23C(void) const {if(m_division == LArFCAL23C) return true; return false;};
   bool IsLArFCAL23A(void) const {if(m_division == LArFCAL23A) return true; return false;};
   bool IsLArEMECC(void) const {if(m_division == LArEMECC) return true; return false;};
   bool IsLArEMECA(void) const {if(m_division == LArEMECA) return true; return false;};
   bool IsLArOverlapC(void) const {if(m_division == LArOverlapC) return true; return false;};
   bool IsLArOverlapA(void) const {if(m_division == LArOverlapA) return true; return false;};
   bool IsLArEMBC(void) const {if(m_division == LArEMBC) return true; return false;};
   bool IsLArEMBA(void) const {if(m_division == LArEMBA) return true; return false;};
   bool IsLArHECC(void) const {if(m_division == LArHECC) return true; return false;};
   bool IsLArHECA(void) const {if(m_division == LArHECA) return true; return false;};
   bool IsTileEBC(void) const {if(m_division == TileEBC) return true; return false;};
   bool IsTileEBA(void) const {if(m_division == TileEBA) return true; return false;};
   bool IsTileLBC(void) const {if(m_division == TileLBC) return true; return false;};
   bool IsTileLBA(void) const {if(m_division == TileLBA) return true; return false;};
   
   bool IsEM(void) const {if(IsLArFCAL1C() || IsLArFCAL1A() || IsLArEMECC() || IsLArEMECA() || IsLArOverlapC() || IsLArOverlapA() || IsLArEMBC() || IsLArEMBA()) return true; return false;};
   bool IsHAD(void) const {if(IsLArFCAL23C() || IsLArFCAL23A() || IsLArHECC() || IsLArHECA() || IsTileEBC() || IsTileEBA() || IsTileLBC() || IsTileLBA()) return true; return false;};
   
   bool IsLAr(void) const {if(IsEM() || IsLArFCAL23C() || IsLArFCAL23A() || IsLArHECC() || IsLArHECA()) return true; return false;};
   bool IsTile(void) const {if( IsHAD() && !IsLAr() ) return true; return false;};
   
   void SetLArFCAL1C(void){m_division = LArFCAL1C;};
   void SetLArFCAL1A(void){m_division = LArFCAL1A;};
   void SetLArFCAL23C(void){m_division = LArFCAL23C;};
   void SetLArFCAL23A(void){m_division = LArFCAL23A;};
   void SetLArEMECC(void){m_division = LArEMECC;};
   void SetLArEMECA(void){m_division = LArEMECA;};
   void SetLArOverlapC(void){m_division = LArOverlapC;};
   void SetLArOverlapA(void){m_division = LArOverlapA;};
   void SetLArEMBC(void){m_division = LArEMBC;};
   void SetLArEMBA(void){m_division = LArEMBA;};
   void SetLArHECC(void){m_division = LArHECC;};
   void SetLArHECA(void){m_division = LArHECA;};
   void SetTileEBC(void){m_division = TileEBC;};
   void SetTileEBA(void){m_division = TileEBA;};
   void SetTileLBC(void){m_division = TileLBC;};
   void SetTileLBA(void){m_division = TileLBA;};
   
   void Clear(void){m_division = Invalid;};
   
   bool operator==(const CaloDivision& division) const {if(division.GetDivision() == m_division) return true; return false;};
   bool operator!=(const CaloDivision& division) const {if(division.GetDivision() != m_division) return true; return false;};
private:
   CaloDivisionEnum m_division;
   
};

#endif

