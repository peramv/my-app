// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "MFDSTC_Config.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "DString.hpp"
#include "QuickRegistry.h"
#include <vector>

#define ID_LOADREGISTRY WM_USER + 1


class CMyReg : public CRegistry {
public:
	CMyReg(HKEY hKey = HKEY_LOCAL_MACHINE)
	: CRegistry(hKey)
   , bCandidate_(false)
   {}
private:
	virtual BOOL	OnValueHit(
						LPCTSTR Key,
						LPCTSTR ValueName,
  						const CRegVal & Value,
                  USHORT Depth ) {
// cout << "Hit value on path \"" << Key << "\": \"" << ValueName << "\" (depth: " << Depth << ")" << endl;
      if( bCandidate_ && (_tcsicmp(ValueName,I_("Path")) == 0) ) {
         I_CHAR sz[256] = {0};
		 int j=0;
		 int i=0;
         for( j=0,i=13;Key[i] != 0x00 && Key[i] != '\\'; ++i,++j ) {
            sz[j] = Key[i];
         }
         sz[j] = 0;
         
         DString dstrKey = sz;
         aConfig.push_back(dstrKey);
      }
      return TRUE;	// continue walk
   }

   virtual BOOL OnKeyHit( LPCTSTR Key, USHORT Depth ) {
// cout << "Hit key \"" << Key << "\" (depth: " << Depth << ")" << endl; 
      if( _tcsicmp(Key,I_("MFDSTC")) == 0 ) {
         bCandidate_ = true;
      }
      else {
         bCandidate_ = false;
      }
      return TRUE;   // continue walk
   }
private:
   bool bCandidate_;
   std::string strCandidate_;
};

// FindMenuItem() will find a menu item string from the specified
// popup menu and returns its position (0-based) in the specified 
// popup menu. It returns -1 if no such menu item string is found.
int FindMenuItem(CMenu* Menu, LPCTSTR MenuString)
{
   ASSERT(Menu);
   ASSERT(::IsMenu(Menu->GetSafeHmenu()));

   int count = Menu->GetMenuItemCount();
   for (int i = 0; i < count; i++)
   {
      CString str;
      if (Menu->GetMenuString(i, str, MF_BYPOSITION) &&
         (i_stricmp(str, MenuString) == 0))
         return i;
   }

   return -1;
}
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};


// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	// TODO: Delete these three lines if you don't want the toolbar to be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	CMyReg reg;
	reg.RegistryTreeWalk(TEXT("Software\\DST"));
   // update menu
   CMenu* mmenu = GetMenu();
   int pos = FindMenuItem(mmenu,I_("&File"));
   if( pos != -1 ) {
      CMenu* fmenu = mmenu->GetSubMenu(pos);
      int pos = FindMenuItem(fmenu,I_("Load From Registry"));
      if( pos != -1 ) {
         CMenu* smenu = fmenu->GetSubMenu(pos);
         pos = FindMenuItem(smenu, I_("Placeholder"));
         if( pos != -1 ) {
            smenu->RemoveMenu(pos,MF_BYPOSITION);
            
            for( CONFIG_VECTOR_ITER iter = aConfig.begin(); iter != aConfig.end(); ++iter, ++pos ) {
               DString value = (*iter);
               int id = WM_USER + pos;
               smenu->AppendMenu(MF_STRING | MF_ENABLED, id, value.c_str());
            }

         }
      }
   }


	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}


// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG


// CMainFrame message handlers

