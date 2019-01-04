// MFDSTC_ConfigDoc.cpp : implementation of the CMFDSTC_ConfigDoc class
//

#include "stdafx.h"
#include "MFDSTC_Config.h"
#include "QuickRegistry.h"
#include "MFDSTC_ConfigDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include <ifastgui\SiteConfig.h>
#include ".\mfdstc_configdoc.h"

// CMFDSTC_ConfigDoc

IMPLEMENT_DYNCREATE(CMFDSTC_ConfigDoc, CDocument)

BEGIN_MESSAGE_MAP(CMFDSTC_ConfigDoc, CDocument)
   ON_COMMAND(ID_FILE_SAVE, OnFileSave)
   ON_COMMAND(ID_FILE_SAVE_AS, OnFileSaveAs)
   ON_COMMAND_RANGE(WM_USER,WM_USER + 100, OnLoadRegistry)

END_MESSAGE_MAP()


// CMFDSTC_ConfigDoc construction/destruction

CMFDSTC_ConfigDoc::CMFDSTC_ConfigDoc()
: pSiteConfig_( NULL )
{
	// TODO: add one-time construction code here
}

CMFDSTC_ConfigDoc::~CMFDSTC_ConfigDoc()
{
}

BOOL CMFDSTC_ConfigDoc::OnNewDocument()
{
	if (!CDocument::  OnNewDocument())
		return FALSE;

   delete pSiteConfig_;
   pSiteConfig_ = new site::SiteConfig;
   pSiteConfig_->init("", NULL);
   UpdateAllViews(NULL,0,(CObject*)pSiteConfig_);

	return TRUE;
}




// CMFDSTC_ConfigDoc serialization

void CMFDSTC_ConfigDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
      
      ar.Write(pSiteConfig_->asString().c_str(),pSiteConfig_->asString().size());
	}
	else
	{
		// TODO: add loading code here
	}
}


// CMFDSTC_ConfigDoc diagnostics

#ifdef _DEBUG
void CMFDSTC_ConfigDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMFDSTC_ConfigDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMFDSTC_ConfigDoc commands


BOOL CMFDSTC_ConfigDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
   if (!CDocument::OnOpenDocument(lpszPathName))
      return FALSE;

   delete pSiteConfig_;
   pSiteConfig_ = new site::SiteConfig;
   DString dStr(lpszPathName);
   pSiteConfig_->init(DStringA(dStr).getImp(), NULL);

   return TRUE;
}

CMFDSTC_ConfigDoc* CMFDSTC_ConfigDoc::getDoc(void)
{
   CFrameWnd * pFrame = (CFrameWnd *)(AfxGetApp()->m_pMainWnd);
   return (CMFDSTC_ConfigDoc *) pFrame->GetActiveDocument();
}

BOOL CMFDSTC_ConfigDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
   BOOL bRc = CDocument::OnSaveDocument(lpszPathName);
   if( TRUE == bRc ) {
      UpdateAllViews(NULL,0,(CObject*)pSiteConfig_);
   }
   return( bRc );
}

void CMFDSTC_ConfigDoc::OnFileSave()
{
   UpdateAllViews(NULL,1,(CObject*)pSiteConfig_);
   CDocument::OnFileSave();
}

void CMFDSTC_ConfigDoc::OnFileSaveAs()
{
   UpdateAllViews(NULL,1,(CObject*)pSiteConfig_);
   CDocument::OnFileSaveAs();
}

BOOL CMFDSTC_ConfigDoc::DoSave(LPCTSTR lpszPathName, BOOL bReplace)
{
   BOOL bRc = CDocument::DoSave( lpszPathName, bReplace );
   return( bRc );
}

void CMFDSTC_ConfigDoc::OnLoadRegistry(UINT nID)
{
	if (!CDocument::  OnNewDocument())
		return;

   DString strKey = aConfig[nID - WM_USER];
   DString root = I_("SOFTWARE\\DST\\");
   root += strKey;
   root += I_("\\");

   delete pSiteConfig_;
   pSiteConfig_ = new site::SiteConfig;
   initFromRegistry(root);
   
   UpdateAllViews(NULL,2,(CObject*)pSiteConfig_);
   


}
void CMFDSTC_ConfigDoc::initFromRegistry( const DString& dstrHive )
{
   CRegistry reg;
   CRegVal data;

   pSiteConfig_->init("",NULL);

   DString dstr(I_("Loaded from Registry HKLM\\"));
   dstr += dstrHive;
   pSiteConfig_->setTextForPath(I_("Description"),dstr.c_str());


   reg.LoadKey((dstrHive+I_("Config\\DataPath")).c_str(),I_("Path"),data.SetValue(I_("")));
   pSiteConfig_->setTextForPath(I_("DataPath/Path"),data.asString().getImp());
   reg.LoadKey((dstrHive+I_("Config\\DataPath")).c_str(),I_("FYIfile"),data.SetValue(I_("")));
   pSiteConfig_->setTextForPath(I_("DataPath/FYIfile"),data.asString().getImp());
   reg.LoadKey((dstrHive+I_("Config\\DataPath")).c_str(),I_("SysLoadPath"),data.SetValue(I_("")));
   pSiteConfig_->setTextForPath(I_("DataPath/SysLoadPath"),data.asString().getImp());
   reg.LoadKey((dstrHive+I_("Config\\DataPath")).c_str(),I_("RepositorySource"),data.SetValue(I_("")));
   pSiteConfig_->setTextForPath(I_("DataPath/RepositorySource"),data.asString().getImp());

   reg.LoadKey((dstrHive+I_("Config\\Market")).c_str(),I_("Market"),data.SetValue(I_("")));
   pSiteConfig_->setTextForPath(I_("Market/Market"),data.asString().getImp());

   reg.LoadKey((dstrHive+I_("Config\\RTSHost")).c_str(),I_("RTSHostIP"),data.SetValue(I_("")));
   pSiteConfig_->setTextForPath(I_("RTSHost/RTSHostIP"),data.asString().getImp());
   reg.LoadKey((dstrHive+I_("Config\\RTSHost")).c_str(),I_("RTSHostPort"),data.SetValue(I_("")));
   pSiteConfig_->setTextForPath(I_("RTSHost/RTSHostPort"),data.asString().getImp());
   reg.LoadKey((dstrHive+I_("Config\\RTSHost")).c_str(),I_("PersistentConnections"),data.SetValue(I_("")));
   pSiteConfig_->setTextForPath(I_("RTSHost/PersistentConnections"),data.asString().getImp());
   reg.LoadKey((dstrHive+I_("Config\\RTSHost")).c_str(),I_("RecycleInterval"),data.SetValue(I_("")));
   pSiteConfig_->setTextForPath(I_("RTSHost/RecycleInterval"),data.asString().getImp());
   reg.LoadKey((dstrHive+I_("Config\\RTSHost")).c_str(),I_("UseSonicMQ"),data.SetValue(I_("")));
   pSiteConfig_->setTextForPath(I_("RTSHost/UseSonicMQ"),data.asString().getImp());
   reg.LoadKey((dstrHive+I_("Config\\RTSHost")).c_str(),I_("SMQBrokerURLs"),data.SetValue(I_("")));
   pSiteConfig_->setTextForPath(I_("RTSHost/SMQBrokerURLs"),data.asString().getImp());
   reg.LoadKey((dstrHive+I_("Config\\RTSHost")).c_str(),I_("SMQSingleQueue"),data.SetValue(I_("")));
   pSiteConfig_->setTextForPath(I_("RTSHost/SMQSingleQueue"),data.asString().getImp());
   reg.LoadKey((dstrHive+I_("Config\\RTSHost")).c_str(),I_("SMQMultiQueue"),data.SetValue(I_("")));
   pSiteConfig_->setTextForPath(I_("RTSHost/SMQMultiQueue"),data.asString().getImp());
   reg.LoadKey((dstrHive+I_("Config\\RTSHost")).c_str(),I_("SMQLDAPQueue"),data.SetValue(I_("")));
   pSiteConfig_->setTextForPath(I_("RTSHost/SMQLDAPQueue"),data.asString().getImp());
   reg.LoadKey((dstrHive+I_("Config\\RTSHost")).c_str(),I_("SMQUser"),data.SetValue(I_("")));
   pSiteConfig_->setTextForPath(I_("RTSHost/SMQUser"),data.asString().getImp());
   reg.LoadKey((dstrHive+I_("Config\\RTSHost")).c_str(),I_("SMQPassword"),data.SetValue(I_("")));
   pSiteConfig_->setTextForPath(I_("RTSHost/SMQPassword"),data.asString().getImp());
   reg.LoadKey((dstrHive+I_("Config\\RTSHost")).c_str(),I_("SMQWaitTimeout"),data.SetValue(I_("")));
   pSiteConfig_->setTextForPath(I_("RTSHost/SMQWaitTimeout"),data.asString().getImp());
   reg.LoadKey((dstrHive+I_("Config\\RTSHost")).c_str(),I_("LDAPUserNS"),data.SetValue(I_("")));
   pSiteConfig_->setTextForPath(I_("RTSHost/LDAPUserNS"),data.asString().getImp());

   reg.LoadKey((dstrHive+I_("Config\\Csi")).c_str(),I_("Host"),data.SetValue(I_("")));
   pSiteConfig_->setTextForPath(I_("Csi/Host"),data.asString().getImp());
   reg.LoadKey((dstrHive+I_("Config\\Csi")).c_str(),I_("Type"),data.SetValue(I_("")));
   pSiteConfig_->setTextForPath(I_("Csi/Type"),data.asString().getImp());
   reg.LoadKey((dstrHive+I_("Config\\Csi")).c_str(),I_("Param"),data.SetValue(I_("")));
   pSiteConfig_->setTextForPath(I_("Csi/Param"),data.asString().getImp());

   reg.LoadKey((dstrHive+I_("Config\\AwdType")).c_str(),I_("AutoLogon"),data.SetValue(I_("")));
   pSiteConfig_->setTextForPath(I_("AwdType/AutoLogon"),data.asString().getImp());
   reg.LoadKey((dstrHive+I_("Config\\AwdType")).c_str(),I_("InterfaceDll"),data.SetValue(I_("")));
   pSiteConfig_->setTextForPath(I_("AwdType/InterfaceDll"),data.asString().getImp());

   reg.LoadKey((dstrHive+I_("Config\\Support")).c_str(),I_("DisplayConnectionIcon"),data.SetValue(I_("")));
   pSiteConfig_->setTextForPath(I_("Support/DisplayConnectionIcon"),data.asString().getImp());
}
