//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 1997 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : CertificateDlg.cpp
// ^AUTHOR : Brian Hicks
// ^DATE   : 03/04/1999
//
// ----------------------------------------------------------
//
// ^CLASS    : CertificateDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  This is the code for the Certificates dialog
//
//******************************************************************************

#include "stdafx.h"

#ifndef IFASTGUI_H
   #include "MFDSTC.h"
#endif

#ifndef CERTIFICATEDLG_H
   #include "CertificateDlg.h"
#endif

#ifndef CERTIFICATEPROCESSINCLUDES_H
   #include <ifastbp\CertificateProcessIncludes.h>
#endif

#ifndef CSISESSION_H
   #include <ifastcsi\CsiSession.h>
#endif

#ifndef DSTCCSI_H
   #include <ifastcsi\ifastcsi.h>
#endif

#ifndef DSTCOMMONFUNCTION_HPP
   #include <ifastcbo\DSTCommonFunction.hpp>
#endif

#ifndef DSTCWORKSESSION_HPP
   #include <ifastcbo\DSTCWorkSession.hpp>
#endif

#ifndef DSTCFUNCS_H
   #include <uibase\DstcFuncs.h>
#endif

extern CLASS_IMPORT const I_CHAR* CMD_BPROC_ADMINDATES;
extern CLASS_IMPORT const I_CHAR* CMD_GUI_CERTIFICATE;
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< CertificateDlg > dlgCreator( CMD_GUI_CERTIFICATE );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define IS_TEXT			0
#define IS_NUMBER			1
#define IS_DATE			2

namespace
{
   // trace literals
   const I_CHAR * const CLASSNAME = I_( "CertificateDlg" );
   const I_CHAR * const LV_CERTIFICATEDETAILS = I_( "CertificateDetails" );
   const I_CHAR *NEW_LINE = I_( "\r\n" );
   const I_CHAR *ACCOUNT_NUMBER_FIELD = I_( "AccountNum" );

   const I_CHAR *MOD_USER                = I_( "ModUser" );
   const I_CHAR *MOD_DATE                = I_( "ModDate" );
   const I_CHAR *USER_NAME               = I_( "Username" );
   const I_CHAR *PROCESS_DATE            = I_( "ProcessDate" );
   const I_CHAR *FUND_NUMBER             = I_( "Baycom" );
}

namespace ifds
{
   extern CLASS_IMPORT const BFNumericFieldId LastActiveAccountNum;
   extern CLASS_IMPORT const BFNumericFieldId LastActiveShrNum;
}

namespace CND
{  // Conditions used
   extern const long GUI_ERR_UNKNOWN_EXCEPTION;
}

//******************************************************************************
// Public methods
//******************************************************************************

CertificateDlg::CertificateDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( CertificateDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   //{{AFX_DATA_INIT(CertificateDlg)
   //}}AFX_DATA_INIT
}

//******************************************************************************

void CertificateDlg::DoDataExchange(CDataExchange* pDX)
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(CertificateDlg)
   //}}AFX_DATA_MAP
}

//******************************************************************************

BEGIN_MESSAGE_MAP(CertificateDlg, BaseMainDlg)
//{{AFX_MSG_MAP(CertificateDlg)
ON_BN_CLICKED(IDC_BTN_ADM_DATES, OnBtnAdmDates)
ON_BN_CLICKED(IDC_BTN_CHANGE, OnBtnChange)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//******************************************************************************
// Message handlers
//******************************************************************************

//******************************************************************************
// Protected methods
//******************************************************************************

BOOL CertificateDlg::OnInitDialog() 
{
   BaseMainDlg::OnInitDialog();

   // TODO: Add extra initialization here
   DString dstrAccountNum;
   const DString &ty = getParent()->getFirstListItemKey( this, IFASTBP_PROC::CERTIFICATE_LIST );

   if( ty != NULL_STRING )
   {
      getParent()->getField( this, IFASTBP_PROC::CERTIFICATE_LIST, ifds::rxAcctNum, dstrAccountNum );
   }

   dstrAccountNum.stripLeading().stripLeading( I_CHAR( '0' ) ).stripTrailing();
   SetAccount( dstrAccountNum );
   SetAccountCaption();

   AddListControl( CLASSNAME, IDC_LV_CERTIFICATES, LV_CERTIFICATEDETAILS, ifds::CertificateHeadingSet, IFASTBP_PROC::CERTIFICATE_LIST, 0, false );
   AddControl( CTRL_EDIT, IDC_EDT_COMMENTS,  IFASTBP_PROC::CERTIFICATE_LIST, ifds::Comments, CTRLFLAG_NOT_UPDATABLE, IDC_LV_CERTIFICATES);
   AddControl( CTRL_EDIT, IDC_EDT_DEST_ADDR, IFASTBP_PROC::CERTIFICATE_LIST, ifds::AddrLine1,  CTRLFLAG_NOT_UPDATABLE, IDC_LV_CERTIFICATES);

   AddControl( CTRL_STATIC, IDC_TXT_CROSS_REF_NBR, IFASTBP_PROC::CERTIFICATE_LIST, ifds::XrefNumber, CTRLFLAG_NOT_UPDATABLE, IDC_LV_CERTIFICATES);
   AddControl( CTRL_STATIC, IDC_TXT_ISSUED_UNITS, IFASTBP_PROC::CERTIFICATE_LIST, ifds::IssuedUnits, CTRLFLAG_NOT_UPDATABLE, IDC_LV_CERTIFICATES);
   AddControl( CTRL_STATIC, IDC_TXT_UNISSUED_UNITS, IFASTBP_PROC::CERTIFICATE_LIST, ifds::UnIssuedUnits, CTRLFLAG_NOT_UPDATABLE, IDC_LV_CERTIFICATES);
   AddControl( CTRL_STATIC, IDC_TXT_TOTAL_UNITS, IFASTBP_PROC::CERTIFICATE_LIST, ifds::AcctUnits, CTRLFLAG_NOT_UPDATABLE, IDC_LV_CERTIFICATES);
   if( ty != NULL_STRING )
   {
      LoadListControl( IDC_LV_CERTIFICATES );
   }
   else
   {
      GetDlgItem( IDC_BTN_ADM_DATES )->EnableWindow( false );
      GetDlgItem( IDC_BTN_CHANGE )->EnableWindow( false );
   }

   return(TRUE);  // return TRUE unless you set the focus to a control
   // EXCEPTION: OCX Property Pages should return FALSE
}

//******************************************************************************

void CertificateDlg::OnPostInitDialog()
{
   DString dstrAccountNum( NULL_STRING ), 
   dstrShrNum( NULL_STRING), 
   dstrEntityName( NULL_STRING );

   getGlobal( WORK_GLOBAL, ifds::LastActiveAccountNum, dstrAccountNum );
   getGlobal( WORK_GLOBAL, ifds::LastActiveShrNum, dstrShrNum );
   if( !dstrAccountNum.empty() )
   {
      dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getFirstSequenced01AccountholderEntityName(getDataGroupId(), dstrAccountNum, dstrEntityName);
   }
   SetShrAcctCaption( dstrShrNum, dstrAccountNum, dstrEntityName);
}

/*
void CertificateDlg::fillDetails()
{
   DString address, dstrField;

   getParent()->getField( this, CERTIFICATE_LIST, DBR::AddrLine1, dstrField );
   DisplayAddr( address, dstrField );
   getParent()->getField( this, CERTIFICATE_LIST, DBR::AddrLine2, dstrField );
   DisplayAddr( address, dstrField );
   getParent()->getField( this, CERTIFICATE_LIST, DBR::AddrLine3, dstrField );
   DisplayAddr( address, dstrField );
   getParent()->getField( this, CERTIFICATE_LIST, DBR::AddrLine4, dstrField );
   DisplayAddr( address, dstrField );
   getParent()->getField( this, CERTIFICATE_LIST, DBR::AddrLine5, dstrField );
   DisplayAddr( address, dstrField );
   getParent()->getField( this, CERTIFICATE_LIST, DBR::PostalCode, dstrField );
   DisplayAddr( address, dstrField );
   getParent()->getField( this, CERTIFICATE_LIST, DBR::CountryName, dstrField );
   DisplayAddr( address, dstrField );
}

//******************************************************************************

void CertificateDlg::DisplayAddr(DString& str, DString& str_1)
{
  if (str_1.strip() != NULL_STRING)
     str += str_1 + NEW_LINE;
}
*/

//******************************************************************************

SEVERITY CertificateDlg::doInit()
{
   return(NO_CONDITION);
}

//*******************************************************************************************************

void CertificateDlg::OnBtnAdmDates() 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_(" OnBtnAdmDates " ) );

   CWaitCursor wait;

   DString dstrTemp;
   getParent()->getField( this, IFASTBP_PROC::CERTIFICATE_LIST, ifds::ModUser, dstrTemp );
   dstrTemp.strip();
   setParameter( MOD_USER, dstrTemp );
   getParent()->getField( this, IFASTBP_PROC::CERTIFICATE_LIST, ifds::ModDate, dstrTemp );
   dstrTemp.strip();
   setParameter( MOD_DATE, dstrTemp );
   getParent()->getField( this, IFASTBP_PROC::CERTIFICATE_LIST, ifds::ProcessDate, dstrTemp );
   dstrTemp.strip();
   setParameter( PROCESS_DATE, dstrTemp );
   getParent()->getField( this, IFASTBP_PROC::CERTIFICATE_LIST, ifds::Username, dstrTemp );
   dstrTemp.strip();
   setParameter( USER_NAME, dstrTemp );

   try
   {
      //bool bModal = false;   // Default to modeless
      bool bModal = true;
      E_COMMANDRETURN eRtn;
      SetMessageStatusBar( TXT_LOAD_ADMIN_DATES );
      eRtn = invokeCommand( getParent(), CMD_BPROC_ADMINDATES, PROC_NO_TYPE, bModal, NULL );
      SetMessageStatusBar( NULL_STRING );
      switch( eRtn )
      {
         case CMD_OK:
         case CMD_CANCEL:
         case CMD_MODELESS_INPROCESS:
            break;
         default:
            // Display error
            ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );
            break;
      }
   }
   catch( ConditionException &ce )
   {
      ConditionMessageBox( ce );
   }
   catch( ... )
   {
      DISPLAYCONDITIONFROMFILE( CND::GUI_ERR_UNKNOWN_EXCEPTION );
   }
}

//*****************************************************************************************************

void CertificateDlg::OnBtnChange()
{

   DString dstrTemp;
   getParent()->getField( this, ifds::rxAcctNum, dstrTemp );
   dstrTemp.stripLeading().stripLeading( I_CHAR( '0' ) ).stripTrailing();
   setCsiParameter( DcCsiParameters::ACCOUNT_NUMBER, DStringA(dstrTemp) );
   executeCsiProcess( DcCsiProcesses::CERTIFICATE_INFO);
}

//*****************************************************************************************************

bool CertificateDlg::GetOverrideItemString( long lSubstituteId, 
                                            const DString &dstrColumnKey, DString &dstrOut )
{
   if( lSubstituteId == ifds::CertificateHeadingSet.getId() )
   {
      if( dstrColumnKey == FUND_NUMBER )
      {
         DString dstrFundCode, dstrClassCode;
         getParent()->getField( this, IFASTBP_PROC::CERTIFICATE_LIST, ifds::rxFundCode, dstrFundCode );
         getParent()->getField( this, IFASTBP_PROC::CERTIFICATE_LIST, ifds::rxClassCode, dstrClassCode );
         dstrFundCode.strip().upperCase();
         dstrClassCode.strip().upperCase();
         dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->GetFundNumber ( dstrFundCode, dstrClassCode, dstrOut );
         return(true);
      }
   }
   return(false);
}


//*************************************************************************************
bool CertificateDlg::GetDataForControl(
                                 UINT controlID,
                                 DString &strValueOut,
                                 bool bFormatted,
                                 int index
                                 ) const
{
	if( controlID == IDC_EDT_DEST_ADDR )
	{
		DString address, dstrField;

		getParent()->getField( this, IFASTBP_PROC::CERTIFICATE_LIST, ifds::AddrLine1, dstrField );
 		strValueOut += dstrField + NEW_LINE;
		getParent()->getField( this, IFASTBP_PROC::CERTIFICATE_LIST, ifds::AddrLine2, dstrField );
		strValueOut += dstrField + NEW_LINE;
		getParent()->getField( this, IFASTBP_PROC::CERTIFICATE_LIST, ifds::AddrLine3, dstrField );
 		strValueOut += dstrField + NEW_LINE;
		getParent()->getField( this, IFASTBP_PROC::CERTIFICATE_LIST, ifds::AddrLine4, dstrField );
		strValueOut += dstrField + NEW_LINE;
		getParent()->getField( this, IFASTBP_PROC::CERTIFICATE_LIST, ifds::AddrLine5, dstrField );
		strValueOut += dstrField + NEW_LINE;
		getParent()->getField( this, IFASTBP_PROC::CERTIFICATE_LIST, ifds::PostalCode, dstrField );
 		strValueOut += dstrField + NEW_LINE;
		getParent()->getField( this, IFASTBP_PROC::CERTIFICATE_LIST, ifds::CountryName, dstrField );		
 		strValueOut += dstrField ;
		return true;
	}
	return false;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/CertificateDlg.cpp-arc  $
 * 
 *    Rev 1.14   Sep 15 2005 15:10:58   popescu
 * Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
 * 
 *    Rev 1.13   Apr 29 2003 15:02:20   YINGBAOL
 * PTS 10016369 sync. to truck
 * 
 *    Rev 1.12   Mar 21 2003 18:34:06   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.11   Oct 09 2002 23:55:34   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.10   Sep 30 2002 11:01:36   PURDYECH
 * BFFieldId no longer has operator long(), so explicit getId() calls are needed in places.
 * 
 *    Rev 1.9   22 May 2002 19:15:52   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.8   27 Mar 2002 20:01:00   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.7   Jan 28 2002 11:27:28   YINGBAOL
 * HLLAPI Change
 * 
 *    Rev 1.6   Jun 20 2001 15:53:34   HERNANDO
 * Changed caption.  Removed unused functions.
 * 
 *    Rev 1.5   03 May 2001 14:07:26   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.4   Oct 18 2000 13:54:56   ZHANGCEL
 * Crash fixed
 * 
 *    Rev 1.3   Jun 06 2000 08:39:48   BUZILA
 * finished M3 syncup
 * 
 *    Rev 1.2   Mar 20 2000 14:15:56   HSUCHIN
 * changed GetfundNumber to use the one in dstcommonfunctions.  Code cleanup
 * 
 *    Rev 1.1   Mar 13 2000 17:28:36   HSUCHIN
 * C2 sync up
 * 
 *    Rev 1.0   Feb 15 2000 11:01:10   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.9   Jan 17 2000 15:22:04   YINGBAOL
 * hllapi change sync
 * 
 *    Rev 1.8   Dec 22 1999 11:27:52   YINGBAOL
 * Hllpai Change sync.
 * 
 *    Rev 1.7   26 Sep 1999 19:07:58   HICKSBR
 * Add HLLAPI Logic for new Change button
 * 
 *    Rev 1.6   13 Sep 1999 13:52:48   HUANGSHA
 * Synchronize with M1's changes
 * 
 *    Rev 1.5   Aug 17 1999 15:19:46   DT24433
 * changed getFieldForCurrentListItem to getField
 * 
 *    Rev 1.4   Jul 20 1999 14:23:52   YINGZ
 * add hour glass
 * 
 *    Rev 1.3   Jul 20 1999 11:18:26   VASILEAD
 * New conditions update
 * 
 *    Rev 1.2   Jul 16 1999 10:43:48   VASILEAD
 * correct IssuedDate format
 * 
 *    Rev 1.1   Jul 08 1999 10:04:46   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
