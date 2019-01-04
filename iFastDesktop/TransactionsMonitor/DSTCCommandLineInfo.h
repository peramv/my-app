
#ifndef DSTCCOMMANDLINEINFO_H
#define DSTCCOMMANDLINEINFO_H

//#include <commonport.h>
#include <dstring.hpp>
//#include <dstringa.hpp>
//#include <stringfunctions.hpp>



// DSTCCommandLine.h : interface of the DSTCCommandLine class
//
/////////////////////////////////////////////////////////////////////////////

class DSTCCommandLineInfo : public CCommandLineInfo
{
public:
   DSTCCommandLineInfo();
   virtual ~DSTCCommandLineInfo();
   const DString& getHost() const { return _dstrHost; }
   bool directConnect() const { return _bRTS; }
   bool doesSiteXmlOverride() const { return _bSiteXmlOverrides; }
   const DString& getSiteXml() const { return _dstrSiteXml; }

   const DString& getUserName() const { return _dstrUserName; }
   const DString& getPassword() const { return _dstrPassword; }
   const DString& getClient() const { return _dstrClient; }

protected:
   virtual void ParseParam( LPCTSTR lpszParam, BOOL bFlag, BOOL bLast );

private:
   DString _dstrHost;
   bool _bRTS;
   DString _dstrSiteXml;
   bool _bSiteXmlOverrides;
   I_CHAR lastFlag_;
   DString _dstrUserName;
   DString _dstrPassword;
   DString _dstrClient;

   void setSiteXmlOverrides( bool v ) { _bSiteXmlOverrides = v; }
};

#endif // DSTCCOMMANDLINE_H
