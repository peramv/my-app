
#ifndef DSTCCOMMANDLINEINFO_H
#define DSTCCOMMANDLINEINFO_H

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

protected:
   virtual void ParseParam( LPCTSTR lpszParam, BOOL bFlag, BOOL bLast );

private:
   DString _dstrHost;
   bool _bRTS;
   DString _dstrSiteXml;
   bool _bSiteXmlOverrides;
   I_CHAR lastFlag_;

   void setSiteXmlOverrides( bool v ) { _bSiteXmlOverrides = v; }
};

#endif // DSTCCOMMANDLINE_H
