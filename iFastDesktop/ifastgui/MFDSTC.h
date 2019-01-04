
#ifndef IFASTGUI_H
#define IFASTGUI_H
// MFDSTC.h : main header file for the MFDSTC application
//

#ifndef __AFXWIN_H__
   #error include 'stdafx.h' before including this file for PCH
#endif

#include <ifastgui\resource.h>

HICON getUserIcon();

/////////////////////////////////////////////////////////////////////////////
// MFDSTCApp:
// See MFDSTC.cpp for the implementation of this class
//

class MFDSTCApp : public CWinApp
{
public:
   MFDSTCApp();
   ~MFDSTCApp();

// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(MFDSTCApp)
public:
   virtual BOOL InitInstance();
   virtual BOOL PreTranslateMessage(MSG* pMsg);
   virtual int ExitInstance();
   virtual int Run();
   //}}AFX_VIRTUAL

// Implementation


   //{{AFX_MSG(MFDSTCApp)
   afx_msg void OnAppAbout();
   // NOTE - the ClassWizard will add and remove member functions here.
   //    DO NOT EDIT what you see in these blocks of generated code !
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()

   public:
   void setLanguage(const DString &dstrLang)
   {
      m_dstrCurrentLang = dstrLang;
   }

   DString getLanguage(void)
   {
      return m_dstrCurrentLang;
   }

   void LoadResourceDll(const DString &dstrCompId, const DString &dstrLang = NULL_STRING);
   void LoadResourceDllByLanguage(const DString &dstrCompId, const DString &dstrLang = NULL_STRING);
   void LoadResourceDllByLanguageAndMarket(const DString &dstrCompId, const DString &dstrMarket , const DString &dstrLang = NULL_STRING);

   CFont* GetNewFont(); // { return m_pNewFont; }
   CFont* GetFixedFont() { return(m_pFixedFont);}
   void SetNewFont(CFont *pFont) {m_pNewFont = pFont;}
//   void GuiConfigInit();
   BOOL SiteConfigInit( const DString&, bool );
private:
   DString   m_dstrCurrentLang, m_dstrCurrentCompId, m_dstrCurrentResourceDllName;
   HINSTANCE m_hDefaultRes;
   HINSTANCE m_hResInstance;

   DString m_dstrSysLang;
   CFont*  m_pNewFont;
   CFont*  m_pFixedFont;
   void SetLocale();
};

#endif // IFASTGUI_H

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/MFDSTC.h-arc  $
 * 
 *    Rev 1.17   Dec 22 2011 14:56:26   if991250
 * IA French resources/substitutions
 * 
 *    Rev 1.16   Oct 11 2011 11:43:20   dchatcha
 * P0186484 FN01 - INA - Desktop Seg and Desktop French Enhancements, add language DLL switching support for domestic client.
 * 
 *    Rev 1.15   Aug 23 2009 10:45:20   purdyech
 * Handle XML Parse errors
 * 
 *    Rev 1.14   06 Dec 2007 15:20:30   popescu
 * Incident 1088629 - read the ACL set-up for the web pages URL instead of the using the xml configuration file.
 * 
 *    Rev 1.13   May 14 2007 15:05:18   purdyech
 * PTS820423 - Added SiteConfigInit method.
 * 
 *    Rev 1.12   May 17 2006 13:36:20   fengyong
 * Add Gui XML configuration file 
 * 
 *    Rev 1.11   Dec 24 2004 11:59:20   purdyech
 * PTS1031333 - getUserIcon() function is now a global function which happens to reside in MFDSTC.cpp, instead of a member of MFDSTCApp
 * 
 *    Rev 1.10   Dec 22 2004 16:55:04   zhangcel
 * PTS 10031333 -- Added a new function getUserIcon()
 * 
 *    Rev 1.9   Oct 09 2002 23:55:48   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.8   Jul 05 2002 08:58:38   PURDYECH
 * Need a condition frame in CWinApp::Run to prevent a crash in infra code.  Overrode CMFDSTCApp::Run to put this in.
 * 
 *    Rev 1.7   19 Mar 2002 13:44:48   PURDYECH
 * Added #pragma once include guard
 * Removed compile time "including..." message.
 * 
 *    Rev 1.6   Dec 05 2001 14:31:04   ZHANGCEL
 * Deal with font problem
 * 
 *    Rev 1.5   29 Nov 2001 14:34:04   HSUCHIN
 * minor cleanup and removed getResourceDllName
 * 
 *    Rev 1.4   30 Jul 2001 15:49:56   YINGZ
 * auto change of resources
 * 
 *    Rev 1.3   May 29 2001 11:44:36   HUANGSHA
 * Code Cleanup
 * 
 *    Rev 1.2   Jan 29 2001 16:24:38   HUANGSHA
 * Create a fixed font for Edit box
 * 
 *    Rev 1.1   Feb 15 2000 18:59:34   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 11:01:20   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.2   04 Aug 1999 11:15:32   HUANGSHA
 * Fix the bugs for display the JAPANESE Titles on the search screen, setting Font for Japanese
 * 
 *    Rev 1.1   Jul 08 1999 10:05:34   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
