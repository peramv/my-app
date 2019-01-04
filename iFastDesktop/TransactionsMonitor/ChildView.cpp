
// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "TransactionsMonitor.h"
#include "ChildView.h"

#include <ifastcbo\DSTCUserSession.hpp>
#include <ifastcbo\DSTCGlobalSession.hpp>
#include <ifastcbo\DSTCWorkSession.hpp>

#include <ifastcbo\MgmtCoOptions2.hpp>
#include <ifastbp\persistentusersession.hpp>

#include <ifastdbrkr\DSTCHost.hpp>

#include <ifdscore\conditionmanager.hpp>

#include <ifdscore\configmanager.hpp>
#include <ifdscore\conditionmigrate.hpp>


namespace 
{
   const I_CHAR * const CLASSNAME = I_( "CChildView" );
}

namespace CND
{  // Conditions used
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId CompanyUrl;
}




//namespace CND
//{  // Conditions used
//   extern CLASS_IMPORT const I_CHAR *IFASTDBRKR_CONDITION;
//   extern CLASS_IMPORT const long BP_ERR_NO_FIELD_MATCH;
//   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
//   extern CLASS_IMPORT const long BP_ERR_USER_CHANGE_PASSWORD;
//   extern CLASS_IMPORT const long BP_NO_OF_DAYS_PRIOR_TO_CHANGE_PASSWORD;
//   extern CLASS_IMPORT const long ERR_AD_TOO_MANY_FAILED_LOGONS;
//}



#ifdef _DEBUG
#define new DEBUG_NEW
#endif




// CChildView

CChildView::CChildView()
{
	_strUserName = I_("");
	_strPassword = I_("");
	_strClient = I_("");

	_dstcUserSession = NULL;
	_dstcWorkSession = NULL;
   errCode = 0;
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	// Do not call CWnd::OnPaint() for painting messages
}

void CChildView::InitInputParameters()
{
	CTransactionsMonitorApp* pApp = (CTransactionsMonitorApp*)AfxGetApp();

	if (pApp != NULL)
	{
		_strUserName = pApp->GetUserNameEx();
		_strPassword = pApp->GetPassword();
		_strClient = pApp->GetClient();
	}
}

void CChildView::Initialize()
{
   MAKEFRAMEAUTOPROMOTE2(I_( "IFAST_TM" ), CLASSNAME, I_("Logon"));

   InitInputParameters();

	Logon();

   if(!errCode)
      CallView(_strClient);

   if(!errCode)
      CallSmartView();

   Logoff();
   
   PostQuitMessage(errCode);

}

SEVERITY CChildView::Logon()
{
   MAKEFRAMEAUTOPROMOTE2(I_( "IFAST_TM" ), CLASSNAME, I_("Logon"));
	SEVERITY severity = NO_CONDITION;

	try
	{  
		DSTCUserSession* pPUS = PersistentUserSession::getInstance();
		if( NULL != pPUS )
		{
			// there is a PersistentUserSession ... we can use its GlobalSession as the GlobalSession
			// of the new UserSession.
			_dstcUserSession = new DSTCUserSession( dynamic_cast< DSTCGlobalSession& >( pPUS->getGlobalSession() ) );
		}
		else
		{
			_dstcUserSession = new DSTCUserSession;
		}

		SEVERITY severity = _dstcUserSession->logon(DSTCHost::getPrimaryHost(), _strUserName, _strPassword);
      if(severity > WARNING)
         errCode = 1;

	}
	catch( ConditionException &ce )
	{
		SETCONDITIONFROMEXCEPTION( ce );
      errCode = 1;
	}
	catch( ... )
	{
      errCode = 1;
		assert( 0 );
		THROWFROMFILE2(I_( "IFAST_TM" ), CLASSNAME, I_("Logon"), CND::BP_ERR_UNKNOWN_EXCEPTION );
	}

	return (GETCURRENTHIGHESTSEVERITY());
}

SEVERITY CChildView::CallView(const DString& mgmtCoName)
{
   MAKEFRAMEAUTOPROMOTE2(I_( "IFAST_TM" ), CLASSNAME, I_("CallView"));
   SEVERITY severity = NO_CONDITION;

	try
	{  
      MgmtCoOptions2 *pMgmtCo = new MgmtCoOptions2(*_dstcUserSession);
      if( pMgmtCo->initSynch(mgmtCoName, NULL_STRING , NULL_STRING) > WARNING )
      {
            errCode = 2;
      }
	}
	catch( ConditionException &ce )
	{
      errCode = 2;
		SETCONDITIONFROMEXCEPTION( ce );
	}
	catch( ... )
	{
      errCode = 2;
		assert( 0 );
		THROWFROMFILE2(I_( "IFAST_TM" ), CLASSNAME, I_("CallView"), CND::BP_ERR_UNKNOWN_EXCEPTION );
	}

	return (GETCURRENTHIGHESTSEVERITY());
}

SEVERITY CChildView::CallSmartView()
{
   MAKEFRAMEAUTOPROMOTE2(I_( "IFAST_TM" ), CLASSNAME, I_("CallSmartView"));
   SEVERITY severity = NO_CONDITION;

	try
	{  
      if(_dstcUserSession != NULL && _dstcWorkSession != NULL)
      {
         MgmtCo & mgmtCo = _dstcWorkSession->getMgmtCo();
         
         DString dWebURL;
         _dstcWorkSession->getOption(ifds::CompanyUrl, dWebURL, BF::HOST, false);
         
         IStream*    pStream = NULL;

         URLOpenBlockingStream(0, dWebURL.c_str(), &pStream, 0, 0);

         if (pStream)
         {
            char data[2000];
            ULONG readBytes = 0;
            HRESULT readResult = pStream->Read(data, sizeof(data), &readBytes);

            pStream->Release(); // <-- release it immediately, we don't need the data
         }
         else
         {
            errCode = 3;
         }

      }
	}
	catch( ConditionException &ce )
	{
      errCode = 3;
		SETCONDITIONFROMEXCEPTION( ce );
	}
	catch( ... )
	{
      errCode = 3;
		assert( 0 );
		THROWFROMFILE2(I_( "IFAST_TM" ), CLASSNAME, I_("CallSmartView"), CND::BP_ERR_UNKNOWN_EXCEPTION );
	}
   

   return (GETCURRENTHIGHESTSEVERITY());
}

SEVERITY CChildView::Logoff()
{
   MAKEFRAMEAUTOPROMOTE2(I_( "IFAST_TM" ), CLASSNAME, I_("CallView"));
	SEVERITY severity = NO_CONDITION;

	try
	{  
		DString logoutMessage;
		//Logoff because either changing the password failed or something else happened
		if(_dstcUserSession)
      {
         SEVERITY severity = _dstcUserSession->logoff( DSTCHost::getPrimaryHost(), logoutMessage);
      }
	}
	catch( ConditionException &ce )
	{
		//SETCONDITIONFROMEXCEPTION( ce );
	}
	catch( ... )
	{
		assert( 0 );
		THROWFROMFILE2(I_( "IFAST_TM" ), CLASSNAME, I_("Logoff"), CND::BP_ERR_UNKNOWN_EXCEPTION );
	}

	return (GETCURRENTHIGHESTSEVERITY());
}
