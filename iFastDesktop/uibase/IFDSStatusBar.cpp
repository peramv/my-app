// IFDSStatusBar.cpp : implementation file
//

#include "stdafx.h"
#include <uibase/IFDSStatusBar.h>
#include <uibase/PopupMessageRes.h>
#include <ConfigManager.hpp>

static CBitmap* getSonicBitmap()
{
   static CBitmap* p = NULL;
   if( NULL == p ) {
      p = new CBitmap;
      p->LoadBitmap( IDB_SB_SONIC );
   }
   return p;
}

static CBitmap* getSonicRedBitmap()
{
   static CBitmap* p = NULL;
   if( NULL == p ) {
      p = new CBitmap;
      p->LoadBitmap( IDB_SB_SONIC_RED );
   }
   return p;
}

// IFDSStatusBar

IMPLEMENT_DYNAMIC(IFDSStatusBar, CStatusBar)
IFDSStatusBar::IFDSStatusBar()
: m_pArray(NULL)
, _companyCode(NULL_STRING)
{
}

IFDSStatusBar::~IFDSStatusBar()
{
   if (m_pArray)
   {
      delete[] m_pArray;
      m_pArray = NULL;
   }

   PANE_MAP_ITER iter = _paneInfo.begin();

   while( iter != _paneInfo.end() )
   {
      IFDSPaneInfo *paneInfo = (*iter).second;
      delete paneInfo;
      paneInfo = NULL;
      iter = _paneInfo.erase( iter );
   }
}


BEGIN_MESSAGE_MAP(IFDSStatusBar, CStatusBar)
//{{AFX_MSG_MAP(ListViewControl)
ON_WM_DESTROY()
ON_WM_CREATE()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//******************************************************************************

int IFDSStatusBar::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
   if( CStatusBar::OnCreate(lpCreateStruct) == -1 )
      return(-1);


   //unsigned array[ INDICATOR_COUNT ] = { 1,2,3,4,5 };

   //bool bShowConnectionPane = GetConfigValueAsBool( I_("Support"), I_("DisplayConnectionIcon") );
   //if( bShowConnectionPane ) {
   //   SetIndicators( array, INDICATOR_COUNT );
   //}
   //else {
   //   SetIndicators( array, INDICATOR_COUNT - 1 );
   //}
   //SetPaneInfo( SB_MESSAGE, GetItemID( SB_MESSAGE ), SBPS_STRETCH, NULL );
   //SetPaneInfo( SB_PROFILE, GetItemID( SB_PROFILE ), SBPS_NORMAL, 131 );
   //SetPaneInfo( SB_SYSTEM, GetItemID( SB_SYSTEM ), SBPS_NORMAL, 47 );
   //SetPaneInfo( SB_MANAGEMENTCODE, GetItemID( SB_MANAGEMENTCODE ), SBPS_NORMAL, 75 );
   //if( bShowConnectionPane ) {
   //   SetPaneInfo( SB_CONNECTION, GetItemID( SB_CONNECTION ), SBPS_OWNERDRAW, 52 );
   //}
   InitStatusPane();

// if(_Substitute) // sub list is used
//    SetImageList(m_Icons, LVSIL_SMALL);

   return(0);
}

//******************************************************************************

void IFDSStatusBar::OnDestroy()
{
   CStatusBar::OnDestroy();
}

//******************************************************************************

void IFDSStatusBar::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
   //switch(lpDrawItemStruct->itemID)
   //{
   //   case SB_CONNECTION:
   DString strKey;
   PANE_MAP_ITER iter = _paneInfo.begin();

   while( iter != _paneInfo.end() )
   {
      IFDSPaneInfo *paneInfo = (*iter).second;
      if ( lpDrawItemStruct->itemID == paneInfo->SBIndex )
      {
         strKey = paneInfo->strPaneKey;
         break;
      }
      ++iter;
   }

   bool bShowConnectionPane =
      GetConfigValueAsBool( I_("Support"), I_("DisplayConnectionIcon") );

   bool bShowClientNamePane =
      GetConfigValueAsBool( I_("Support"), I_("ShowClientNamePane") );

   //DString strKey = I_("SB_CONNECTION");
   //PANE_MAP_ITER iter = _paneInfo.find( strKey );

   //if( iter != _paneInfo.end() )
   if( strKey == I_("SB_CONNECTION") )
   {
      //IFDSPaneInfo *paneInfo = (*iter).second;

      //if ( bShowConnectionPane && ( lpDrawItemStruct->itemID == paneInfo->SBIndex ) )
      if( bShowConnectionPane )
      {
         // Attach to a CDC object
         CDC dc;
         dc.Attach(lpDrawItemStruct->hDC);

         // Get the pane rectangle and calculate text coordinates
         CRect rect(&lpDrawItemStruct->rcItem);

         CBitmap* pBitmap = NULL;

         // are we in 'support' mode?
         //   Support/ControlTextRewriter_Path != ""

         bool bRewriter = (GetConfigValueAsString( I_("Support"), I_("ControlTextRewriter_Path") ) != I_(""));
         if( bRewriter ) {
            pBitmap = getSonicRedBitmap();
         }
         else {
            pBitmap = getSonicBitmap();
         }
         CDC srcDC; // select current bitmap into a compatible CDC
         srcDC.CreateCompatibleDC(NULL);
         CBitmap* pOldBitmap = srcDC.SelectObject(pBitmap);
         dc.BitBlt(rect.left, rect.top, rect.Width(), rect.Height(),
                  &srcDC, 0, 0, SRCCOPY); // BitBlt to pane rect
         srcDC.SelectObject(pOldBitmap);

         // Detach from the CDC object, otherwise the hDC will be
         // destroyed when the CDC object goes out of scope
         dc.Detach();
      }
      return;
   }
   else if (  strKey == I_("SB_CLIENTNAME") )
   {
      if( bShowClientNamePane )
      {
         PANE_MAP_ITER iterPaneKey = _paneInfo.find( strKey );
         IFDSPaneInfo *paneInfo = (*iterPaneKey).second;

         CString strPaneText = GetPaneText(paneInfo->SBIndex);

         if ( strPaneText.IsEmpty() ) return;

         DString dstrPaneText, dstrRevPaneText,
            dstrBufferPaneText;

         dstrPaneText += strPaneText.GetBuffer();
         dstrBufferPaneText = NULL_STRING;
         dstrBufferPaneText += dstrPaneText;

         DString::size_type pos = 0;

         std::vector<DString> vecBufferPaneText;
         bool bFoundScrambledKey = false;
         do
         {
            DString dstrTemp = NULL_STRING;
            pos = dstrBufferPaneText.find (I_(" "));
            dstrTemp = dstrBufferPaneText.substr (0,pos);
            if (dstrTemp.find(I_("SCRAMBLED")) != DString::npos || 
                dstrTemp.find(I_("Scrambled")) != DString::npos){
               bFoundScrambledKey = true;
            }
            pos = pos != DString::npos && pos + 1 <= dstrBufferPaneText.length() ? pos + 1 :  DString::npos;
            if (pos != DString::npos){ 
               dstrBufferPaneText = dstrBufferPaneText.substr (pos);
            }
            else {
               dstrBufferPaneText = NULL_STRING;
            }

            if (!dstrTemp.empty()){
               vecBufferPaneText.push_back(dstrTemp.strip());
            }

         }while(!dstrBufferPaneText.empty());

         CRect rect(&lpDrawItemStruct->rcItem);

         CDC dc;
         dc.Attach(lpDrawItemStruct->hDC);

         COLORREF defTextBkColor = dc.GetBkColor();
         COLORREF defTextColor = dc.GetTextColor();

         if (bFoundScrambledKey)
         {
            //HS_BDIAGONAL   Downward hatch (left to right) at 45 degrees
            //HS_CROSS       Horizontal and vertical crosshatch
            //HS_DIAGCROSS   Crosshatch at 45 degrees
            //HS_FDIAGONAL   Upward hatch (left to right) at 45 degrees
            //HS_HORIZONTAL  Horizontal hatch
            //HS_VERTICAL    Vertical hatch

            dstrPaneText = NULL_STRING;

            for (auto& itr : vecBufferPaneText){
               DString dstrTemp = itr;
               DString dstrTempLwr = dstrTemp;
               dstrTempLwr.strip().lowerCase();

               bool bAddWord = false;
               if (dstrTempLwr.find(I_("slot")) != DString::npos){
                  bAddWord = true;
               }
               else if (!_companyCode.empty() && 
                  dstrTempLwr.find(_companyCode.lowerCase()) != DString::npos){
                  bAddWord = true;
               }
               else if (dstrTempLwr == I_("from")){
                  bAddWord = true;
               }
               else if (dstrTempLwr == I_("master")){
                  bAddWord = true;
               }
               // drop 'scrambled'
               else if (dstrTempLwr == I_("scrambled")){
                  bAddWord = false;
               }
               else {
                  bAddWord = false;
               }

               if (bAddWord){
                  dstrPaneText += dstrTemp;
                  dstrPaneText += I_(" ");
               }
            }

            {
               CBrush hatchBrush, *pOldBrush;
               hatchBrush.CreateHatchBrush(HS_BDIAGONAL, RGB(0, 0, 0));
               DWORD dwBgColor = GetSysColor(COLOR_BTNFACE);
               BYTE blue  = (BYTE)((dwBgColor & 0x00ff0000)>>16);
               BYTE green = (BYTE)((dwBgColor & 0x0000ff00)>>8);
               BYTE red   = (BYTE)((dwBgColor & 0x000000ff));
               dc.SetBkColor(RGB(red,green,blue));
               pOldBrush = dc.SelectObject(&hatchBrush);
               dc.FillRect(&rect,&hatchBrush);
            }
         }
         else
         {
            dc.SetBkMode(TRANSPARENT);
         }

         vecBufferPaneText.clear();

         strPaneText = dstrPaneText.c_str();

         //dc.DrawText(strPaneText,&rect,DT_BOTTOM | DT_LEFT | DT_SINGLELINE);
         dc.DrawText(strPaneText,&rect,DT_BOTTOM | DT_CENTER | DT_SINGLELINE);

         dc.Detach();
      }
      return;
   }

   CStatusBar::DrawItem(lpDrawItemStruct);
}

// IFDSStatusBar message handlers

//******************************************************************************

void IFDSStatusBar::SetManagementCodeStatusBar( const I_CHAR *mgmtCd )
{
   SetPaneText( SB_MANAGEMENTCODE, mgmtCd );
   UpdateWindow();
}

//******************************************************************************

void IFDSStatusBar::SetMessageStatusBar( const I_CHAR *msg )
{
   SetPaneText( SB_MESSAGE, msg );
   UpdateWindow();
}

//******************************************************************************
void IFDSStatusBar::SetMessageStatusBar( const int nId )
{
   CString cStrMsg;
   DString strMsg;

   cStrMsg.LoadString( nId );
   strMsg = (LPCTSTR)cStrMsg;
   SetPaneText( SB_MESSAGE, strMsg.c_str() );
   UpdateWindow();
}

//******************************************************************************

void IFDSStatusBar::SetSystemStatusBar( const I_CHAR *sys )
{
   SetPaneText( SB_SYSTEM, sys );
   UpdateWindow();
}

//******************************************************************************

void IFDSStatusBar::SetProfileStatusBar( const I_CHAR *profile )
{
   SetPaneText( SB_PROFILE, profile );
   UpdateWindow();
}

//******************************************************************************

void IFDSStatusBar::SetClientNameStatusBar( const I_CHAR *keyword )
{
   bool bShowClientNamePane =
      GetConfigValueAsBool( I_("Support"), I_("ShowClientNamePane") );

   DString strKey = I_("SB_CLIENTNAME");
   PANE_MAP_ITER iter = _paneInfo.find( strKey );

   if ( bShowClientNamePane && iter != _paneInfo.end() )
   {
      IFDSPaneInfo *paneInfo = (*iter).second;
      SetPaneText( paneInfo->SBIndex, keyword );
      UpdateWindow();
   }
}

//******************************************************************************
BOOL IFDSStatusBar::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
   // TODO: Add your specialized code here and/or call the base class
   LPNMHDR pNmhdr = (LPNMHDR)lParam;
   if( pNmhdr->code == UM_IFDSSTATUSBARCHANGE )
   {
      *pResult = 0;

      InitStatusPane();

      return TRUE;
   }
   else
   {
      return CStatusBar::OnNotify(wParam, lParam, pResult);
   }
}

//******************************************************************************
void IFDSStatusBar::InitStatusPane(void)
{
   bool bShowConnectionPane = GetConfigValueAsBool( I_("Support"), I_("DisplayConnectionIcon") );
   bool bShowClientNamePane = GetConfigValueAsBool( I_("Support"), I_("ShowClientNamePane") );

   {
      if (m_pArray)
      {
         delete[] m_pArray;
         m_pArray = NULL;
      }

      PANE_MAP_ITER iter = _paneInfo.begin();

      while( iter != _paneInfo.end() )
      {
         IFDSPaneInfo *paneInfo = (*iter).second;
         delete paneInfo;
         paneInfo = NULL;
         iter = _paneInfo.erase( iter );
      }
   }

   int iCurIndex = 0;
   DString strPaneKey;

   // message
   {
      IFDSPaneInfo *paneInfo = new IFDSPaneInfo;
      paneInfo->SBIndex = iCurIndex;
      paneInfo->SBPos = paneInfo->SBIndex + 1;
      paneInfo->SBPaneFlag = SBPS_STRETCH;
      paneInfo->SBPaneSize = 0;
      strPaneKey = I_("SB_MESSAGE");
      paneInfo->strPaneKey = strPaneKey;
      _paneInfo.insert( PANE_MAP_VALUE_TYPE( strPaneKey, paneInfo ) );
      iCurIndex++;
   }

   // AWD profile
   {
      IFDSPaneInfo *paneInfo = new IFDSPaneInfo;
      paneInfo->SBIndex = iCurIndex;
      paneInfo->SBPos = paneInfo->SBIndex + 1;
      paneInfo->SBPaneFlag = SBPS_NORMAL;
      paneInfo->SBPaneSize = 131;
      strPaneKey = I_("SB_PROFILE");
      paneInfo->strPaneKey = strPaneKey;
      _paneInfo.insert( PANE_MAP_VALUE_TYPE( strPaneKey, paneInfo ) );
      iCurIndex++;
   }

   // system login id
   {
      IFDSPaneInfo *paneInfo = new IFDSPaneInfo;
      paneInfo->SBIndex = iCurIndex;
      paneInfo->SBPos = paneInfo->SBIndex + 1;
      paneInfo->SBPaneFlag = SBPS_NORMAL;
      paneInfo->SBPaneSize = 75;
      strPaneKey = I_("SB_SYSTEM");
      paneInfo->strPaneKey = strPaneKey;
      _paneInfo.insert( PANE_MAP_VALUE_TYPE( strPaneKey, paneInfo ) );
      iCurIndex++;
   }

   // management company code
   {
      IFDSPaneInfo *paneInfo = new IFDSPaneInfo;
      paneInfo->SBIndex = iCurIndex;
      paneInfo->SBPos = paneInfo->SBIndex + 1;
      paneInfo->SBPaneFlag = SBPS_NORMAL;
      paneInfo->SBPaneSize = 47;
      strPaneKey = I_("SB_MANAGEMENTCODE");
      paneInfo->strPaneKey = strPaneKey;
      _paneInfo.insert( PANE_MAP_VALUE_TYPE( strPaneKey, paneInfo ) );
      iCurIndex++;
   }

   if ( bShowClientNamePane )
   {
      IFDSPaneInfo *paneInfo = new IFDSPaneInfo;
      paneInfo->SBIndex = iCurIndex;
      paneInfo->SBPos = paneInfo->SBIndex + 1;
      paneInfo->SBPaneFlag = SBPS_OWNERDRAW;
      paneInfo->SBPaneSize = 211;
      strPaneKey = I_("SB_CLIENTNAME");
      paneInfo->strPaneKey = strPaneKey;
      _paneInfo.insert( PANE_MAP_VALUE_TYPE( strPaneKey, paneInfo ) );
      iCurIndex++;
   }

   if ( bShowConnectionPane )
   {
      IFDSPaneInfo *paneInfo = new IFDSPaneInfo;
      paneInfo->SBIndex = iCurIndex;
      paneInfo->SBPos = paneInfo->SBIndex + 1;
      paneInfo->SBPaneFlag = SBPS_OWNERDRAW;
      paneInfo->SBPaneSize = 52;
      strPaneKey = I_("SB_CONNECTION");
      paneInfo->strPaneKey = strPaneKey;
      _paneInfo.insert( PANE_MAP_VALUE_TYPE( strPaneKey, paneInfo ) );
      iCurIndex++;
   }

   m_pArray = new unsigned int[_paneInfo.size()];

   // fill up array of pane id
   PANE_MAP_ITER iter = _paneInfo.begin();

   while( iter != _paneInfo.end() )
   {
      IFDSPaneInfo *paneInfo = (*iter).second;
      *(m_pArray+paneInfo->SBIndex) = paneInfo->SBPos;
      ++iter;
   }

   SetIndicators( m_pArray, iCurIndex );

   iter = _paneInfo.begin();

   while( iter != _paneInfo.end() )
   {
      IFDSPaneInfo *paneInfo = (*iter).second;
      SetPaneInfo( paneInfo->SBIndex,
                  GetItemID( paneInfo->SBIndex ),
                  paneInfo->SBPaneFlag,
                  paneInfo->SBPaneSize );
      ++iter;
   }
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/uibase/IFDSStatusBar.cpp-arc  $
// 
//    Rev 1.5   Dec 05 2011 09:01:28   purdyech
// ControlTextRewriter Logic
//
//    Rev 1.4   Dec 22 2009 19:41:38   dchatcha
// IN# 1952546 - Indicator to show that the database DSK is connected to is scrambled. Change registry key name to be more explanative.
//
//    Rev 1.3   Dec 22 2009 05:35:32   dchatcha
// IN# 1952546 - Indicator to show that the database DSK is connected to is scrambled.
 *
 */

