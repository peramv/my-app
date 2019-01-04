// CsiScreenReader.h: interface for the CsiScreenReader class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_CSISCREENREADER_H__INCLUDED_)
   #define _CSISCREENREADER_H__INCLUDED_

   #include <ifastcsi\xplatform.h>
   #include <string>

class D_LINKAGE CsiScreenReader  
{
public:
   CsiScreenReader();
   virtual ~CsiScreenReader();

   virtual int getProperty(const std::string &name, int defualt=0) = 0;
   virtual long getProperty(const std::string &name, long defualt=0L) = 0;
   virtual const std::string &getProperty(const std::string &name, const std::string &defualt="") = 0;

//   virtual const std::string getComponent();

};

#endif // !defined(_CSISCREENREADER_H__INCLUDED_)
