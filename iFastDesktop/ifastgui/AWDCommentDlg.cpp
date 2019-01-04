//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2004 by International Financial Data Services
//
//******************************************************************************
//
// ^FILE   : AWDCommentDlg.cpp
// ^AUTHOR : Monica Vadeanu
// ^DATE   : April 2004
//
// ----------------------------------------------------------
//
// ^CLASS    : AWDCommentDlg.cpp
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  This is the code for a list selection dialog

//******************************************************************************


#include "stdafx.h"

#include "mfdstc.h"
#include "AWDCommentDlg.h"
#include "awdcommon.hpp"

#include <bfawdi\bfawdinterface.hpp>

#include <bfproc\bpglobal.h>
#include <bfproc\bpsessiontags.h>

#include <bfsessn\bfawdsession.hpp>
#include <bfsessn\bfcpsessiontags.h>

#include <configmanager.hpp>

#include <ifastawd\DSTCAWDSession.hpp>
//#include <ifastdbrkr\dstcsecurity.hpp>

#include <uibase\dstedit.h>
#include <uibase\dstcombobox.h>

#include <dataimpl\dse_dstcglob_vw.hpp>

#include <ifastcbo\dstcworksession.hpp>


#include <assert.h>

extern CLASS_IMPORT const I_CHAR* CMD_GUI_AWD_COMMENT;
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< AWDCommentDlg > dlgCreator( CMD_GUI_AWD_COMMENT );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR *CLASSNAME = I_( "AWDCommentDlg" );
   const I_CHAR *POSTOK    = I_( "PostOk" );
}

namespace ifds
{  
   extern CLASS_IMPORT const BFTextFieldId AWDRemark;	
	extern CLASS_IMPORT const BFTextFieldId BusinessArea;
	extern CLASS_IMPORT const BFTextFieldId WorkType;
	extern CLASS_IMPORT const BFTextFieldId StatusDesc;
}

//*****************************************************************************
AWDCommentDlg::AWDCommentDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, 
									   GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( AWDCommentDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
//, m_pAwdInterface( NULL )
, m_pAwdSession( NULL )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   //{{AFX_DATA_INIT(AWDCommentDlg)
   //}}AFX_DATA_INIT
}

//*****************************************************************************
void AWDCommentDlg::DoDataExchange( CDataExchange* pDX )
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(AWDCommentDlg)
   //}}AFX_DATA_MAP
}

//*****************************************************************************
BEGIN_MESSAGE_MAP(AWDCommentDlg, BaseMainDlg)
//{{AFX_MSG_MAP(AWDCommentDlg)
ON_CBN_SELCHANGE(IDC_CB_WU_UNIT, OnSelchangeCbWuUnit)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//*****************************************************************************
// Message handlers
//*****************************************************************************
BOOL AWDCommentDlg::OnInitDialog() 
{
   TRACE_METHOD( CLASSNAME, ONINITDIALOG );
   BaseMainDlg::OnInitDialog();
   return(TRUE);
}

//*****************************************************************************
void AWDCommentDlg::OnPostInitDialog()
{
   TRACE_METHOD( CLASSNAME, ONPOSTINITDIALOG );
   	
   AddControl( CTRL_EDIT, IDC_EDT_COMMENT,  BF::NullContainerId, ifds::AWDRemark,    CTRLFLAG_FIELDS_FROM_SUB_LIST | CTRLFLAG_WORD_WRAP | CTRLFLAG_GUI_FIELD );
	AddControl( CTRL_COMBO, IDC_CB_WU_UNIT,  BF::NullContainerId, ifds::BusinessArea, CTRLFLAG_NOT_UPDATABLE | CTRLFLAG_GUI_FIELD );	
	AddControl( CTRL_COMBO, IDC_CB_WU_WRKT,  BF::NullContainerId, ifds::WorkType,     CTRLFLAG_NOT_UPDATABLE | CTRLFLAG_GUI_FIELD );
   AddControl( CTRL_COMBO, IDC_CB_WU_STAT,  BF::NullContainerId, ifds::StatusDesc,   CTRLFLAG_NOT_UPDATABLE | CTRLFLAG_GUI_FIELD );
   
   // Ok and Cancel buttons
   AddControl( CTRL_STATIC, IDOK,     CTRLFLAG_NOT_UPDATABLE | CTRLFLAG_GUI_FIELD );
   AddControl( CTRL_STATIC, IDCANCEL, CTRLFLAG_NOT_UPDATABLE | CTRLFLAG_GUI_FIELD );

   DSTEdit *pDSTEditAWDComment = dynamic_cast<DSTEdit*>( GetControl( IDC_EDT_COMMENT ) );
   if( pDSTEditAWDComment != NULL )
   {
      pDSTEditAWDComment->SetMaxCharNum( 50 );		
		pDSTEditAWDComment->setNumLine();
   }

   if( BFCPSession::usingAwd() && getSession() != NULL )
   {
      m_pAwdSession = getSession()->getAwdSession();
      if( m_pAwdSession != NULL )
      {
         (void) m_pAwdSession->getProcessWork();
      }
   }

   ConfigureAWDControls();	
}

//*****************************************************************************
void AWDCommentDlg::ConfigureAWDControls( )
{
   DSTCAWDSession* pDSTCAWDSession = dynamic_cast<DSTCAWDSession* >(getSession() );
   if( pDSTCAWDSession )
   {
      // Populate Business Area list
      CComboBox *pCmb = (CComboBox*) GetDlgItem( IDC_CB_WU_UNIT );
		string_vector list = pDSTCAWDSession->getAwdBusinessAreaList() ;      
      string_vector_const_iterator iter;
      for( iter = list.begin(); iter != list.end(); ++iter )
      {
         pCmb->AddString(( *iter ).c_str() );	  
      }   

      // Populate Status list      
		pCmb = (CComboBox*) GetDlgItem( IDC_CB_WU_STAT );
      list = pDSTCAWDSession->getAwdStatusList();
      for( iter = list.begin(); iter != list.end(); ++iter)
      {
         pCmb->AddString(( *iter ).c_str() );	  
      } 
      pCmb->SelectString( 0, I_("PROCESSED") );

      if( !(pDSTCAWDSession->isContainerEmpty() ) && !(pDSTCAWDSession->isCallStarted() ) )  
      {
         // Select Business Area
         DString dstrCompanyId, dstrBusinessArea;
         pDSTCAWDSession->getAwdField( ifds::BusinessArea, dstrBusinessArea );
         pCmb = (CComboBox*) GetDlgItem( IDC_CB_WU_UNIT );
         pCmb->SelectString( 0, dstrBusinessArea.strip().c_str() );

         // Select Work Type
         OnSelchangeCbWuUnit();         
      }
   }
}

//******************************************************************************
bool AWDCommentDlg::doRefresh( GenericInterface * rpGICaller, const I_CHAR * szOriginalCommand )
{  
   return(true);
}

//*****************************************************************************
bool AWDCommentDlg::PreOk()
{
   TRACE_METHOD( CLASSNAME, PREOK );

   bool bReturn = true;

	bool bFoundEmpty = false;
   CString cstrValue;
   GetDlgItemText( IDC_CB_WU_UNIT, cstrValue );
   bFoundEmpty = ( cstrValue.IsEmpty() == TRUE );

	cstrValue = _T( "" );
   GetDlgItemText( IDC_CB_WU_WRKT, cstrValue );
   bFoundEmpty |= ( cstrValue.IsEmpty() == TRUE );

	cstrValue = _T( "" );
   GetDlgItemText( IDC_CB_WU_STAT, cstrValue );
   bFoundEmpty |= ( cstrValue.IsEmpty() == TRUE );

   if( bFoundEmpty )
   {
		AfxMessageBox( TXT_AWD_VALUES_REQUIRED, MB_OK | MB_ICONSTOP );
      bReturn = false;
   }

   GetDlgItem( IDOK )->EnableWindow( FALSE );
   GetDlgItem( IDCANCEL )->EnableWindow( FALSE );
   if( bReturn )
   {
      bReturn = UpdateAWDObject();
   }
   if( bReturn ) 
   {
      GetDlgItem( IDOK )->EnableWindow( TRUE );
      GetDlgItem( IDCANCEL )->EnableWindow( TRUE );
   }

   return( bReturn );
}

//*****************************************************************************
void AWDCommentDlg::PostOk( bool bOK )
{
   TRACE_METHOD( CLASSNAME, POSTOK );
   GetDlgItem( IDOK )->EnableWindow( TRUE );
   GetDlgItem( IDCANCEL )->EnableWindow( TRUE );
}

//*****************************************************************************
void AWDCommentDlg::OnSelchangeCbWuUnit() 
{
   // TODO: Add your control notification handler code here

   CString cstrBusArea;

   GetDlgItemText ( IDC_CB_WU_UNIT, cstrBusArea );
   if( !cstrBusArea.IsEmpty() )
   {      
		DSTCAWDSession* pDSTCAWDSession = dynamic_cast<DSTCAWDSession* >(getSession() );
		if( pDSTCAWDSession )
		{
			string_vector listWorkType = pDSTCAWDSession->getWorkTypeList( (DString) cstrBusArea );
			CComboBox *pCmbWT = (CComboBox*) GetDlgItem(IDC_CB_WU_WRKT);
			pCmbWT->ResetContent();
			string_vector_const_iterator iter = listWorkType.begin();
			while( iter != listWorkType.end() )
			{
			  pCmbWT->AddString(( *iter ).c_str());
			  iter++;
			}

			// Select Work Type same as the work object			
			DString dstrTemp = pDSTCAWDSession->getCurrentWork();
			pCmbWT->SelectString( 0, dstrTemp.strip().c_str() );

			// Select Status 
			CComboBox *pCmbST = (CComboBox*) GetDlgItem( IDC_CB_WU_STAT );
			dstrTemp =	pDSTCAWDSession->getCurrentStatus();
			pCmbST->SelectString( 0,dstrTemp.strip().c_str() );
		}
   }
}

//*****************************************************************************
bool AWDCommentDlg::UpdateAWDObject()
{
   MAKEFRAME2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("UpdateAWDObject") );
   bool bReturn = true;

   DSTCAWDSession* pDSTCAWDSession = dynamic_cast<DSTCAWDSession* >(getSession() );
   if( pDSTCAWDSession && m_pAwdSession )
   {
      CString cstr;
      GetDlgItemText( IDC_CB_WU_UNIT, cstr );
      pDSTCAWDSession->setAwdField(ifds::BusinessArea,LPCTSTR( cstr ) ); 
		
		cstr = _T( "" );
      GetDlgItemText( IDC_CB_WU_WRKT, cstr );
      pDSTCAWDSession->setAwdField(ifds::WorkType,LPCTSTR( cstr ) ); 
		
		cstr = _T( "" );
      GetDlgItemText( IDC_CB_WU_STAT, cstr );
      pDSTCAWDSession->setAwdField(ifds::StatusDesc,LPCTSTR( cstr ) ); 

      pDSTCAWDSession->setAwdField(SessionTags::AWD_COMMENT, NULL_STRING );
		cstr = _T( "" );
      GetDlgItemText( IDC_EDT_COMMENT, cstr );
      pDSTCAWDSession->setAwdField(SessionTags::AWD_COMMENT,LPCTSTR( cstr ) ); 		
      
		DString dstrUpdateWork( SessionTags::UPDATE_WORK );

      SEVERITY sev = NO_CONDITION;
      sev = pDSTCAWDSession->validateDirectCommentToAWD( LPCTSTR( cstr ), getDataGroupId() );
      if( sev >= WARNING )
      {
         int iReturn = ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );
         if( sev != WARNING || (sev == WARNING && iReturn == IDCANCEL) )
         {
            bReturn = false;
         }
      }
      else
      {
         if( pDSTCAWDSession->addDirectCommentToAWD( LPCTSTR( cstr ), getDataGroupId() ) >= WARNING )
         {
            ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );
            bReturn = false;
         }
      }
   }
   return( bReturn );
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/AWDCommentDlg.cpp-arc  $
// 
//    Rev 1.8   Sep 15 2005 15:10:34   popescu
// Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
// 
//    Rev 1.7   Jan 21 2005 11:19:58   hernando
// PET910 - .NET/AWD Testing - Store AWD Comment if validation is alright.
// 
//    Rev 1.6   Aug 19 2004 16:10:56   HERNANDO
// PTS 10033149 - Changed the way Warning messages are handled.
// 
//    Rev 1.5   Jul 08 2004 12:29:10   HERNANDO
// PTS 10031546 - Disabled OK and Cancel button on Ok.
// 
//    Rev 1.4   Jun 24 2004 11:22:26   HERNANDO
// PTS10031673 - Moved UpdateAWDObject call to PreOk.
// 
//    Rev 1.3   May 26 2004 15:38:58   HERNANDO
// PET1017 FN01 - Additional enhancement - Display error or warning message based on environment (ErrMsgRuleList #415).  Removed empty comment check in PreOk.
// 
//    Rev 1.2   May 10 2004 12:19:12   VADEANUM
// PET1017 - AWD Comments - Limit Comment to 250 characters.
// 
//    Rev 1.1   May 07 2004 18:36:48   VADEANUM
// PET1017 - AWD Comments - use addDirectCommentToAWD() instead of CallInquiry... and added soft edit if Comments are blank.
// 
//    Rev 1.0   May 06 2004 16:40:22   VADEANUM
// Initial revision.
 */
