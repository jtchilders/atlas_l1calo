////////////////////////////////////////////////////////////////
/// Tree Package: used to defind read/write acces mode        //
/// Developed by: Taylor Childers                             //
/// Feel free to email with questions                         //
////////////////////////////////////////////////////////////////
#ifndef ACCESSMODE_H
#define ACCESSMODE_H

#include <string>

class AccessMode{
public:
   enum ACCESS_MODE{
      READ = 0,
      WRITE = 1
   };
   
   AccessMode(ACCESS_MODE mode){m_mode = mode;};
   AccessMode(void){SetReadMode();};
   AccessMode(const AccessMode& mode){m_mode = mode.GetMode();};
   ~AccessMode(void){};
   
   void operator=(const AccessMode& rhs){m_mode = rhs.GetMode();};
   
   void SetReadMode(void){m_mode = READ;};
   void SetWriteMode(void){m_mode = WRITE;};
   ACCESS_MODE GetMode(void) const {return m_mode;};
   
   std::string GetString(void) const {
      if(m_mode == READ) return "READ";
      else if(m_mode == WRITE) return "WRITE";
      return "NOT_SET";
   }
   
   bool IsReadMode(void){if(m_mode == READ) return true;return false;};
   bool IsWriteMode(void){if(m_mode == WRITE) return true;return false;};
   
private:
   ACCESS_MODE m_mode;
};


#endif

