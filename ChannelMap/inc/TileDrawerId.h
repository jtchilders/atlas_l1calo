#ifndef TILEDRAWERID_H
#define TILEDRAWERID_H

#include <string>

class TileDrawerId{
public:
   enum TILE_PARTITION{
      LBA = 0,
      LBC = 1,
      EBA = 2,
      EBC = 3,
      PARTITION_NOT_SET = 4
   };
   
   
   TileDrawerId(const unsigned int id):m_id(id){};
   TileDrawerId(const TILE_PARTITION part,const unsigned int drawerNumber){SetId(part,drawerNumber);};
   TileDrawerId(void):m_id(0){};
   
   void SetId(unsigned int id){m_id = id;};
   void SetId(const TILE_PARTITION part,const unsigned int drawerNumber){
      m_id = (((unsigned int)part & 0xff) << 16) | (drawerNumber & 0xff);
   };
   
   TILE_PARTITION GetTilePartition(void) const{return (TILE_PARTITION)((m_id >> 16) & 0xff);};
   unsigned int GetDrawerNumber(void) const{return (m_id & 0xff) + 1;};
   std::string GetTilePartitionString(void) const {
      if(IsLBA()) return "LBA";
      else if(IsLBC()) return "LBC";
      else if(IsEBC()) return "EBC";
      else if(IsEBA()) return "EBA";
      return "";
   };
   
   std::string GetIdAsString(void) const{
      char temp[50];
      sprintf(temp,"%s%02d",GetTilePartitionString().c_str(),GetDrawerNumber());
      return temp;
   }
   
   bool IsLBA(void) const {if(GetTilePartition() == LBA) return true; return false;};
   bool IsLBC(void) const {if(GetTilePartition() == LBC) return true; return false;};
   bool IsEBA(void) const {if(GetTilePartition() == EBA) return true; return false;};
   bool IsEBC(void) const {if(GetTilePartition() == EBC) return true; return false;};
   
   
private:
   unsigned int m_id;
   
};

#endif

