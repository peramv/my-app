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
// ^FILE   : VerifySearchDlg.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : 03/10/99
//
// ----------------------------------------------------------
//
// ^CLASS    : VerifySearchDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  This is the code for a simple list selection dialog
//
//******************************************************************************
#include "stdafx.h"

#include <bfdata\bfdata.hpp>
#include "mfdstc.h"
#include <ifastbp\accdetailsprocessincludes.h>
#include <bfcbo\bfcbo.hpp>
#include <uibase\basecontrol.hpp>
#include <configmanager.hpp>
#include <uibase\dstbutton.h>
#include <uibase\dstcfuncs.h>
#include <ifastcbo\dstcommonfunction.hpp>
#include <uibase\dstlistctrl.h>
#include <ifastcbo\dstcworksession.hpp>
#include <ifastbp\entitysearchprocessincludes.h>
#include <ifastbp\tradesprocessincludes.h>
#include "verifysearchdlg.h"
#include <ifastbp\whereusedprocessincludes.h>

extern CLASS_IMPORT const I_CHAR* CMD_BPROC_WHEREUSED;
extern CLASS_IMPORT const I_CHAR* CMD_GUI_ENTITY_SEARCH;
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< VerifySearchDlg > dlgCreator( CMD_GUI_ENTITY_SEARCH );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR * const CLASSNAME            = I_( "VerifySearchDlg" );
   const I_CHAR * const COMMA                = I_( "," );
   const I_CHAR * const LFCR                 = I_( "\r\n" );
   const I_CHAR * const LV_ENTITIES          = I_( "List View Entities" );
   const I_CHAR * const LV_ENTITY_IDS        = I_( "List View Entity Ids" );
   const I_CHAR * const ONDBLCLKLVENTITIES   = I_( "OnDblclkLvEntities" );
   const I_CHAR * const ONRADIOADDRESS01     = I_( "OnRadioAddress01" );
   const I_CHAR * const ONRADIOADDRESS11     = I_( "OnRadioAddress11" );
   const I_CHAR * const SPACE2               = I_( "  " );
   const I_CHAR * const ENTITYALONE          = I_( "EntityAlone" );
   const I_CHAR * const FROM_SCR             = I_( "FromScreen" );

}

namespace CND
{
   extern const long GUI_ERR_UNKNOWN_EXCEPTION;

}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId CompCodeFlag;
   extern CLASS_IMPORT const BFTextFieldId VerifySearchSNAPHeadingSet;
   extern CLASS_IMPORT const BFTextFieldId WrapAccount;
}

//******************************************************************************
// Constructor
//******************************************************************************
VerifySearchDlg::VerifySearchDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( VerifySearchDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
, m_hAccel( 0 ) 
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   //{{AFX_DATA_INIT(VerifySearchDlg)
   //}}AFX_DATA_INIT
}

//******************************************************************************
// Destructor
//******************************************************************************
VerifySearchDlg::~VerifySearchDlg( )
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
// Called by MFC framework to exchange and validate dialog data
//******************************************************************************
void VerifySearchDlg::DoDataExchange( CDataExchange* pDX )
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(VerifySearchDlg)
   //}}AFX_DATA_MAP
}

//******************************************************************************
// doInit method is not used in this dialog
// @returns SEVERITY - NO_CONDITION
//******************************************************************************
SEVERITY VerifySearchDlg::doInit()
{
   TRACE_METHOD( CLASSNAME, DOINIT );

   DString showSameEntityMultipleTimes;

   getParent()->getParameter (FROM_SCR, _fromScreen);
   getParameter (I_("ShowSameEntityMultipleTimes"), showSameEntityMultipleTimes);
   bIgnoreFiltering = showSameEntityMultipleTimes == I_("Y");
   return NO_CONDITION;
}

//******************************************************************************
// MFC Message Map
//******************************************************************************
BEGIN_MESSAGE_MAP(VerifySearchDlg, BaseMainDlg)
//{{AFX_MSG_MAP(VerifySearchDlg)
ON_BN_CLICKED(IDC_BTN_MORE, OnBtnMore)
ON_NOTIFY(NM_DBLCLK, IDC_LV_ENTITIES, OnDblclkLvEntities)
ON_BN_CLICKED(IDC_RADIO_ADDRESS01, OnRadioAddress01)
ON_BN_CLICKED(IDC_RADIO_ADDRESS11, OnRadioAddress11)
ON_BN_CLICKED(IDC_BTN_WHERE_USED, OnBtnWhereUsed)
ON_COMMAND(ID_ACCEL_ENTITY, OnAccelEntity)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//******************************************************************************
// Initialization of Dialog and loading of Accelerators.
// @return true if init was successful
//******************************************************************************
BOOL VerifySearchDlg::OnInitDialog() 
{
   TRACE_METHOD( CLASSNAME, ONINITDIALOG );
   BaseMainDlg::OnInitDialog();

   DString m_dstrMarket = DSTCommonFunctions::getMarket();

   if( m_dstrMarket == MARKET_IDS::CANADA || m_dstrMarket == MARKET_IDS::LUXEMBOURG )
   {
      GetDlgItem( IDC_RADIO_ADDRESS11 )->ShowWindow( SW_HIDE );
      GetDlgItem( IDC_RADIO_ADDRESS01 )->ShowWindow( SW_HIDE );
      GetDlgItem( IDC_SADDRESS )->ShowWindow( SW_SHOW );
   }
   else if( m_dstrMarket == MARKET_IDS::JAPAN )
   {
      GetDlgItem( IDC_RADIO_ADDRESS11 )->ShowWindow( SW_SHOW );
      GetDlgItem(IDC_RADIO_ADDRESS01)->ShowWindow( SW_SHOW );
      GetDlgItem( IDC_SADDRESS )->ShowWindow( SW_HIDE );
   }
   if( !m_hAccel )
      m_hAccel = LoadAccelerators( NULL, MAKEINTRESOURCE( IDR_ACCEL_VERIFYSEARCH ) );
   return(TRUE);
}

//******************************************************************************
// Call by based architecture.  Controls are initialized.
// The More button is enable/disable based on the CBO data.
//******************************************************************************
void VerifySearchDlg::OnPostInitDialog()
{
   TRACE_METHOD( CLASSNAME, ONPOSTINITDIALOG );

   // Check SNAP support
   DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
   DString dstrCompCodeFlag;
   dstWorkSession->getOption( ifds::CompCodeFlag, dstrCompCodeFlag, getDataGroupId(), false );
   dstrCompCodeFlag.strip().upperCase();

   //  Load VerifySearchHeadingSet
   AddListControl( CLASSNAME, IDC_LV_ENTITIES, LV_ENTITIES, 
                      ifds::VerifySearchHeadingSet, IFASTBP_PROC::ENTITY_SEARCH_LIST,
                      0, true, LISTFLAG_TIMER);


   AddListControl( CLASSNAME, IDC_LV_ENTITY_IDS, LV_ENTITY_IDS, 
                   ifds::EntityIDSHeadingSet, IFASTBP_PROC::ENTITY_IDS_LIST, IDC_LV_ENTITIES, true, LISTFLAG_NOT_UPDATABLE );

   AddControl( CTRL_EDIT, IDC_EDT_ADDRESS, IFASTBP_PROC::ENTITY_SEARCH_LIST, ifds::Address1, 
               CTRLFLAG_NOT_UPDATABLE | CTRLFLAG_GUI_FIELD, (UINT)IDC_LV_ENTITIES );
   AddControl( CTRL_CHECKBOX, IDC_RADIO_ADDRESS01, CTRLFLAG_NOT_UPDATABLE | CTRLFLAG_GUI_FIELD );
   AddControl( CTRL_CHECKBOX, IDC_RADIO_ADDRESS11, CTRLFLAG_NOT_UPDATABLE | CTRLFLAG_GUI_FIELD );
   AddControl( CTRL_STATIC, IDC_BTN_WHERE_USED, CTRLFLAG_NOT_UPDATABLE | CTRLFLAG_GUI_FIELD );
   AddControl( CTRL_STATIC, IDC_BTN_MORE, CTRLFLAG_NOT_UPDATABLE | CTRLFLAG_GUI_FIELD );
 //  AddControl( CTRL_STATIC, IDOK,  CTRLFLAG_NOT_UPDATABLE | CTRLFLAG_GUI_FIELD );

   DSTButton* radio01 = dynamic_cast<DSTButton*>( GetControl( IDC_RADIO_ADDRESS01 ) );

   if( radio01 != NULL )
   {
      radio01->SetCheck( 1 );
   }
   GetDlgItem(IDOK)->EnableWindow (_fromScreen != ENTITYALONE );

   doRefresh( this, NULL_STRING );
}

//******************************************************************************
// Method to refresh dialog controls
// @param   GenericInterface *rpGICaller - pointer to the calling object
// @param   const I_CHAR *szOriginalCommand - Not used in this case, but 
//                      can be used to instruct special processing.
// @return true if the refresh occurred properly.
//******************************************************************************
bool VerifySearchDlg::doRefresh( GenericInterface *rpGICaller, 
                                 const I_CHAR *szOriginalCommand )
{ 
   TRACE_METHOD( CLASSNAME, DOREFRESH );

   ConnectControlsToData();
   LoadListControl( IDC_LV_ENTITIES );
   EnableControl( IDC_BTN_MORE, getParent()->doMoreRecordsExist( this, BF::AllContainerIds ) );
   return(true);
}

//******************************************************************************
// Method to override columns displayed
//******************************************************************************
bool VerifySearchDlg::filterListColumn(const BFFieldId &idSubstitute, const DString& dstrTag)
{
   DString dstrValue,dstrWrapAccount;

   if( ifds::VerifySearchHeadingSet == idSubstitute )
   {
      DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());

      DString dstrCompCodeFlag;
      dstWorkSession->getOption(ifds::CompCodeFlag, dstrCompCodeFlag, getDataGroupId(), false );
      dstrCompCodeFlag.strip().upperCase();

      // dstrCompCodeFlag is "N" hide AcctGroup and CompanyCode fields.
      // Otherwise display them
      if(dstrCompCodeFlag == I_("N") ) { 
         if ( dstrTag == I_("AcctGroup")) {
            return false; 
         }
         if ( dstrTag == I_("CompanyCode")) {
            return false;
         }
      }

      // If generic control Viscount is "Y" show ifds:AcctCategory, otherwise hide it     
      dstWorkSession->getOption( ifds::WrapAccount, dstrWrapAccount, getDataGroupId(), false );
      if ( dstrWrapAccount == I_("N") ) 
      {
         if ( dstrTag == I_("WrapAccount")) 
            return false;
      }

      if (!bIgnoreFiltering && dstrTag == I_("AccountNum") )
         return false;

   }
   return true;
}

//******************************************************************************
// Method to override data retrived for the control defined by the controlID 
// passed in.   In this case the Edit box IDC_EDT_ADDRESS is composed of six 
// data fields defined in the CBO ( Address1..Address5 and PostalCode ) separated 
// by the eoln character.
// @param   UINT controlID - The custom control Id
// @param   DString& strValueOut - The string to be display for the current control
// @param   bool bFormatted - Flag determining the output to be formateed by
//                            DataDictionary
// @param   int index - index of field, if it has multiple fields for control
// @returns true if override provided for the specified control, false otherwise
//******************************************************************************
bool VerifySearchDlg::GetDataForControl( UINT controlID, 
                                         DString &strValueOut, 
                                         bool bFormatted, 
                                         int index ) const
{
   bool bRtn = false;

   BFFieldId alList[12] = {
      ifds::Address1,   // Start of first list
      ifds::Address2,
      ifds::Address3,
      ifds::Address4,
      ifds::Address5,
      ifds::PostalCode,
      ifds::Addr11Line1,  // Start of second list
      ifds::Addr11Line2,
      ifds::Addr11Line3,
      ifds::Addr11Line4,
      ifds::Addr11Line5,
      ifds::PostalCode11
   };

   switch( controlID )
   {
      case IDC_EDT_ADDRESS:
         {
            DString dstrValue;
            DSTButton* radio01 = dynamic_cast<DSTButton*>( GetControl( IDC_RADIO_ADDRESS01 ) );
            DSTButton* radio11 = dynamic_cast<DSTButton*>( GetControl( IDC_RADIO_ADDRESS11 ) );

            short nIndex = -1;
            if( radio01 != NULL && radio01->GetCheck() == 1 )
               nIndex = 0;
            else if( radio11 != NULL && radio11->GetCheck() == 1 )
               nIndex = 6;

            if( nIndex != -1 )
            {
               for( short nCtr = 0; nCtr < 6; ++nCtr )
               {
                  getParent()->getField( this, IFASTBP_PROC::ENTITY_SEARCH_LIST, alList[nCtr + nIndex], dstrValue);
                  if( !dstrValue.empty() )
                  {
                     strValueOut += dstrValue.strip() + LFCR;
                  }
               }
            }

            bRtn = true;
            break;
         }
      default:
         break;
   }
   return(bRtn);
}

//******************************************************************************
// Method for processing before the doOk event.
// @return true if all goes well
//******************************************************************************
bool VerifySearchDlg::PreOk() 
{  // Get selected item and return
   MAKEFRAME2( CND::IFASTGUI_CONDITION, CLASSNAME, OK );

   DString entityID,
      accountNum,
      entityType;

   getParent()->getField (this, IFASTBP_PROC::ENTITY_SEARCH_LIST, ifds::EntityId, entityID);
   getParent()->getField (this, IFASTBP_PROC::ENTITY_SEARCH_LIST, ifds::AccountNum, accountNum);
   getParent()->getField (this, IFASTBP_PROC::ENTITY_SEARCH_LIST, ifds::EntityType, entityType, false);
   if(entityType == I_("") || entityType == I_("64")) // Registration Agent
   {
      DString dstrValidRATaxType;
      getParent()->getField (this, IFASTBP_PROC::ENTITY_SEARCH_LIST, ifds::ValidRATaxType, dstrValidRATaxType, false);
      if(dstrValidRATaxType != I_("")) // registration agent
      {
         entityType = I_("64");
         getParent()->setParameter (I_("ValidRATaxType"), dstrValidRATaxType);
      }
   }
   getParent()->setParameter (ACCDETLIT::ENTITY_ID_FIELD, entityID);
   getParent()->setParameter(MFCAN_IP_PARAM::ACCOUNT_NUM, accountNum);
   getParent()->setParameter (I_("EntityType"), entityType);

   return true;
}

//******************************************************************************
// Method for the More button event which will retrieve more entities to display
// in the entity list control.
//******************************************************************************
void VerifySearchDlg::OnBtnMore()
{
   TRACE_METHOD( CLASSNAME, ONBTNMORE );

   CWaitCursor wait;

   const DString *crtKey = &getParent()->getCurrentListItemKey( this, IFASTBP_PROC::ENTITY_SEARCH_LIST );

   SetMessageStatusBar( TXT_SEARCH_FOR_ENTITIES );
   if( getParent()->performSearch( this, BF::AllContainerIds, SEARCH_NEXT_BLOCK ) <= WARNING )
   {
      listKey.clear();
      LoadListControl( IDC_LV_ENTITIES );
      if( *crtKey != NULL_STRING )
      {
         GetList( IDC_LV_ENTITIES )->SetSelection( crtKey );
      }
      EnableControl( IDC_BTN_MORE, getParent()->doMoreRecordsExist( this, BF::AllContainerIds ) );
   }
   SetMessageStatusBar( NULL_STRING );
}

//******************************************************************************
// Double click event of the Entity List control which will post a OK event 
// message closing the screen and launching the details dialog.
// @param   NMHDR* pNMHDR - pointer to notification message
// @param   LRESULT* pResult - A 32-bit value returned from a window procedure or callback function.
//******************************************************************************
void VerifySearchDlg::OnDblclkLvEntities( NMHDR* pNMHDR, 
                                          LRESULT* pResult ) 
{
   TRACE_METHOD( CLASSNAME, ONDBLCLKLVENTITIES );

   *pResult = 0;

   // doesn't support double click on list of searching entity
   if( _fromScreen != ENTITYALONE  )
   {
      if( GetList( IDC_LV_ENTITIES )->GetNextSelection() >= 0 )// There is an entity selected
      {
         PostMessage( WM_COMMAND, IDOK );
      }
   }
}

//******************************************************************************
// This radio button will only show up in the Japan Market.  It will reload the
// Address edit box with the Kanji address.
//******************************************************************************
void VerifySearchDlg::OnRadioAddress01()
{
   TRACE_METHOD( CLASSNAME, ONRADIOADDRESS01 );

   LoadControl( IDC_EDT_ADDRESS );
}

//******************************************************************************
// This radio button will only show up in the Japan Market.  It will reload the
// Address edit box with the Kana address.
//******************************************************************************
void VerifySearchDlg::OnRadioAddress11() 
{
   TRACE_METHOD( CLASSNAME, ONRADIOADDRESS11 );

   LoadControl( IDC_EDT_ADDRESS );
}

//******************************************************************************
// Method which lauches the WhereUsed process when the Where used button is 
// clicked on.
//******************************************************************************
void VerifySearchDlg::OnBtnWhereUsed() 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnWhereUsed()" ) );

   CWaitCursor wait;
   DString last_name;
   DString first_name;

   getParent()->getField( this, IFASTBP_PROC::ENTITY_SEARCH_LIST, ifds::LastName, last_name );
   getParent()->getField( this, IFASTBP_PROC::ENTITY_SEARCH_LIST, ifds::FirstName, first_name );

   DString dstrEntityName = last_name.strip() + COMMA + SPACE2 + first_name.strip();

   getParent()->setParameter( WHEREUSEDPROC::ENTITY_NAME, dstrEntityName );
   getParent()->getField( this, IFASTBP_PROC::ENTITY_SEARCH_LIST, ifds::BirthLastName, last_name );
   getParent()->getField( this, IFASTBP_PROC::ENTITY_SEARCH_LIST, ifds::BirthFirstName, first_name );
   dstrEntityName = last_name.strip() + I_(" , ") + first_name.strip();
   getParent()->setParameter( WHEREUSEDPROC::BIRTHENTITY_NAME, dstrEntityName );

   DString dstrEntityId;

   getParent()->getField( this, IFASTBP_PROC::ENTITY_SEARCH_LIST, ifds::EntityId, dstrEntityId );
   getParent()->setParameter( WHEREUSEDPROC::ENTITY_ID,dstrEntityId ); 

   SetMessageStatusBar( TXT_LOAD_WHERE_USED );
   try
   {
      E_COMMANDRETURN rtn = CMD_FAILURE;

      rtn = invokeCommand( getParent(), CMD_BPROC_WHEREUSED, PROC_NO_TYPE, isModal(), NULL );
      switch( rtn )
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
   SetMessageStatusBar( NULL_STRING );
}

//******************************************************************************
// Method which handles the acclerator ID_ACCEL_ENTITY.  Sets focus to the
// Entity List Control
//******************************************************************************
void VerifySearchDlg::OnAccelEntity() 
{
   // TODO: Add your command handler code here
   GetList( IDC_LV_ENTITIES )->SetFocus();
}

//******************************************************************************
// Called by the base architecture framework to intercept windows messages such
// as accelerators.
// @return true if windows message is intercepted, false otherwise
//******************************************************************************
BOOL VerifySearchDlg::PreTranslateMessage( MSG* pMsg ) 
{
   BOOL isTranslated = FALSE;

   // make certain accelerator keys are processed correctly
   if( m_hAccel != NULL )
   {
      isTranslated = ::TranslateAccelerator( m_hWnd, m_hAccel, pMsg );
   }
   if( !isTranslated )
   {
      // pass message down the chain
      isTranslated = BaseMainDlg::PreTranslateMessage( pMsg );
   }
   return(isTranslated);
}

//******************************************************************************
// This method filters out duplicate entity ids from the entity id list
// @param   long lSubstituteId - The list substitution set to use for filter
// @returns true if the item will be shown and false otherwise
//******************************************************************************
bool VerifySearchDlg::ListViewControlFilter( long lSubstituteId, const DString * )
{
   if (!bIgnoreFiltering)
   {
      DString str;

      if ( lSubstituteId == ifds::VerifySearchHeadingSet.getId() || 
           lSubstituteId == ifds::VerifySearchSNAPHeadingSet.getId())
      {
         getParent()->getField (this, IFASTBP_PROC::ENTITY_SEARCH_LIST, ifds::EntityId, str);
         return listKey.insert (str).second != NULL;
      }
   }
   return true;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/VerifySearchDlg.cpp-arc  $
 * 
 *    Rev 1.33   May 17 2012 17:31:48   if991250
 * CPF - Picking up ValidRATaxType even when vw3 returns an entity type
 * 
 *    Rev 1.32   May 01 2012 09:25:40   if991250
 * CPF - validating that the Registration agent has the appropriate tax type for the CPF account
 * 
 *    Rev 1.31   Apr 27 2012 16:31:24   if991250
 * CPF search for Reg agents
 * 
 *    Rev 1.30   Jan 18 2012 13:41:40   yingz
 * fix 2810792: making entity type list not updatable
 * 
 *    Rev 1.29   Sep 28 2009 08:34:32   dchatcha
 * P0163546 FN01 TA Automate Fund Transfer.
 * 
 *    Rev 1.28   27 Jun 2007 16:48:02   popescu
 * Incident# 929895 - enable search button and create a new entity if this is used.
 * 
 *    Rev 1.27   Sep 15 2005 15:16:16   popescu
 * Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
 * 
 *    Rev 1.26   Apr 21 2005 16:25:16   aguilaam
 * IN 262507 - display accountnum column if ok to display multiple records same entity owner
 * 
 *    Rev 1.25   Apr 14 2005 11:07:10   popescu
 * Incident #262507, Multiple a/c with same alternate a/c
 * 
 *    Rev 1.24   Mar 09 2005 14:39:00   yingbaol
 * PET1171,FN01:EU saving, disable OK button if it is from All Entity screen.
 * 
 *    Rev 1.23   Nov 07 2004 14:56:52   popescu
 * PET 1117/06, synch changes
 * 
 *    Rev 1.22   Apr 15 2003 12:31:08   sanchez
 * Sync up with version 1.20.1.0
 * 
 *    Rev 1.21   Mar 21 2003 18:42:04   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.20   Jan 27 2003 10:47:00   KOVACSRO
 * Changed SocialCode field into WrapAccount
 * 
 *    Rev 1.19   Jan 20 2003 10:43:24   KOVACSRO
 * back to 1.17 
 * 
 *    Rev 1.17   Dec 19 2002 13:50:20   sanchez
 * Modified OnPostInitDialog().  Change logic to load fds::VerifySubstitutionSet, and NOT ifds::VerifySNAPSubstitutionSet.
 * 
 *    Rev 1.16   Oct 09 2002 23:56:18   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.15   Sep 30 2002 11:01:46   PURDYECH
 * BFFieldId no longer has operator long(), so explicit getId() calls are needed in places.
 * 
 *    Rev 1.14   Aug 29 2002 12:57:30   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.13   Jul 30 2002 10:03:02   YINGBAOL
 * dealing with LUXEMBOURG
 * 
 *    Rev 1.12   22 May 2002 19:16:34   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.11   08 May 2002 17:11:18   KOVACSRO
 * Added a timer for the list control.
 * 
 *    Rev 1.10   27 Mar 2002 20:01:30   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.9   Mar 07 2002 18:06:16   HERNANDO
 * Change Address display -- removed blank lines.
 * 
 *    Rev 1.8   07 Mar 2002 09:51:44   WINNIE
 * Fix compilation
 * 
 *    Rev 1.7   Mar 06 2002 17:28:26   HERNANDO
 * Alternate heading set based on System Options flag; adds AcctGroup and CompanyCode.  SNAP implementation.
 * 
 *    Rev 1.6   Sep 06 2001 14:11:22   ZHANGCEL
 * Added second parameter in ListViewControlFilter()
 * 
 *    Rev 1.5   20 Aug 2001 16:53:30   HSUCHIN
 * bug fix
 * 
 *    Rev 1.4   20 Aug 2001 16:51:22   HSUCHIN
 * added comments and fix Market problem
 * 
 *    Rev 1.3   20 Aug 2001 15:08:56   HSUCHIN
 * beautify source
 * 
 *    Rev 1.2   Apr 10 2001 16:02:32   YINGZ
 * fix multiple entity problem
 * 
 *    Rev 1.1   Aug 16 2000 15:01:44   YINGBAOL
 * implement function "Search for Trade"
 * 
 *    Rev 1.0   Feb 15 2000 11:01:28   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.24   Jan 28 2000 12:27:04   POPESCUS
 * fixes for more button
 * 
 *    Rev 1.23   Jan 14 2000 09:10:18   POPESCUS
 * updated VerifySearch to the new control model
 * 
 *    Rev 1.22   Jan 13 2000 13:49:12   POPESCUS
 * dispaly conditions for where used
 * 
 *    Rev 1.21   Jan 11 2000 14:35:46   VASILEAD
 * Fixed entity background search
 * 
 *    Rev 1.20   Nov 30 1999 09:31:46   POPESCUS
 * Fixed the appearance of Ids
 * 
 *    Rev 1.19   Nov 22 1999 10:33:50   ZHANGCEL
 * Change WhereUseDlg invoking type form modaless to modal
 * 
 *    Rev 1.18   Nov 14 1999 12:57:06   VASILEAD
 * fixed dbl clck issue
 * 
 *    Rev 1.17   Nov 13 1999 19:42:00   VASILEAD
 * Fixed dbl click on a entity
 * 
 *    Rev 1.16   Nov 10 1999 16:32:22   ZHANGCEL
 * modify code for launching WhereUsed Dialog
 * 
 *    Rev 1.15   Nov 09 1999 16:53:40   VASILEAD
 * Changed to AccountEntityXref
 * 
 *    Rev 1.14   Oct 04 1999 16:31:24   HSUCHIN
 * Added Alt-L Acceleartor to put focus on search results.
 * 
 *    Rev 1.13   Oct 04 1999 16:20:44   ZHANGCEL
 * Add WhereUsed Dialog access 
 * 
 *    Rev 1.12   Sep 24 1999 17:25:36   HSUCHIN
 * minor bug fix
 * 
 *    Rev 1.11   Sep 20 1999 13:51:26   HSUCHIN
 * bug fix.
 * 
 *    Rev 1.10   Sep 17 1999 14:56:18   HSUCHIN
 * Minor fix to make M2 work
 * 
 *    Rev 1.9   Sep 16 1999 14:53:42   HSUCHIN
 * Added code for C1, added SIN to ID Types and changed Column Headings
 * 
 *    Rev 1.8   13 Sep 1999 13:53:02   HUANGSHA
 * Synchronize with M1's changes
 * 
 *    Rev 1.7   Aug 17 1999 17:18:50   DT24433
 * changed getFieldForCurrentListItem to getField
 * 
 *    Rev 1.6   Aug 09 1999 15:51:10   POPESCUS
 * Fixed a double-click issue
 * 
 *    Rev 1.5   Jul 28 1999 13:16:08   POPESCUS
 * Added a new process for entity search
 * 
 *    Rev 1.4   Jul 28 1999 11:05:36   POPESCUS
 * Changed to new strings
 * 
 *    Rev 1.3   Jul 20 1999 11:19:40   VASILEAD
 * New conditions update
 * 
 *    Rev 1.2   Jul 14 1999 11:45:44   POPESCUS
 * Fixed redirecting: where used hllapi 
 * 
 *    Rev 1.1   Jul 08 1999 10:06:02   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */


