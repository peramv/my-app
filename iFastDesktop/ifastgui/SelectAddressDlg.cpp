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
//    Copyright 2002 by International Financial Data Services.
//
//******************************************************************************
//
// ^FILE   : SettlementDlg.cpp
// ^AUTHOR : Yingbao Li
// ^DATE   : June 10, 2002
//
// ----------------------------------------------------------
//
// ^CLASS    : SelectAddressDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  This is the code for a list selection dialog
//
//******************************************************************************



#include "stdafx.h"
#include "mfdstc.h"

#include "SelectAddressDlg.h"
#include <ifastbp\addressprocessincludes.h>

#ifndef DSTLISTCTRL_H
   #include <uibase\DSTListCtrl.h>
#endif

#include <ifastdataimpl\dse_dstc0043_vw.hpp>
#include <ifastdataimpl\dse_dstc0042_vw.hpp>
#include <ifastcbo\dstcommonfunction.hpp>


extern CLASS_IMPORT const I_CHAR* CMD_GUI_ADDRESS_SELECTION;
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< SelectAddressDlg > dlgCreator( CMD_GUI_ADDRESS_SELECTION );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR * const CLASSNAME = I_( "SelectAddressDlg" );
   const I_CHAR * const LV_ADDRESS_LIST = I_( "AddressList" );
   const I_CHAR *ADDRESS         = I_("Address");
   const I_CHAR *ADDRESSCODE       = I_("AddrCode");
   const I_CHAR *ADDRESSCODEDESC       = I_("AddrCodeDesc");
   const I_CHAR *ADDRESSLINE       = I_( "AddressLine" );
   const I_CHAR *STATUS        = I_( "AddrStatus" );

   const I_CHAR *SPACE_STRING        = I_( " " );

}

namespace CND
{  // Conditions used
   extern CLASS_IMPORT const long GUI_ERR_UNKNOWN_EXCEPTION;
}

/////////////////////////////////////////////////////////////////////////////
// SelectAddressDlg dialog

//******************************SelectAddressDlg()****************************
SelectAddressDlg::SelectAddressDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( SelectAddressDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
{
   //{{AFX_DATA_INIT(SelectAddressDlg)
   // NOTE: the ClassWizard will add member initialization here
   //}}AFX_DATA_INIT
}

//**********************************************************
void SelectAddressDlg::DoDataExchange(CDataExchange* pDX)
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(SelectAddressDlg)
   // NOTE: the ClassWizard will add DDX and DDV calls here

   //}}AFX_DATA_MAP
}

//*******************************************************
BEGIN_MESSAGE_MAP(SelectAddressDlg, BaseMainDlg)
//{{AFX_MSG_MAP(SelectAddressDlg)
ON_NOTIFY( NM_DBLCLK, IDC_ADDRESS_LIST, OnDblclkAddressList )

//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SelectAddressDlg message handlers

/*************************************************************************/
SEVERITY SelectAddressDlg::doInit()
{
   getParameter( ADDRLIT::SHAREHOLDER_NUM, _dstrShrNum ); 
   _dstrShrNum.stripLeading('0');

   return(NO_CONDITION);
}

//****************************************************************/
void SelectAddressDlg::OnPostInitDialog()
{
   AddListControl( CLASSNAME, IDC_ADDRESS_LIST, LV_ADDRESS_LIST, ifds::ShareholderAddressHeadingSet, IFASTBP_PROC::ADDRESSES_LIST ); 
   LoadListControl( IDC_ADDRESS_LIST );

   DString dstrEntityName, dstrAccountNum( NULL_STRING );

   // Get Entity Name
   DString dstrValue;
   getParent()->getField(this,IFASTBP_PROC::SHAREHOLDER_LIST,ifds::Name1,dstrValue);
   dstrValue.strip();
   dstrEntityName += dstrValue;
   getParent()->getField(this,IFASTBP_PROC::SHAREHOLDER_LIST,ifds::Name2,dstrValue);
   dstrValue.strip();
   dstrEntityName += I_(" ") + dstrValue;

   SetShrAcctCaption(_dstrShrNum, dstrAccountNum, dstrEntityName);
}

//**********************************************************************
void SelectAddressDlg::OnDblclkAddressList( NMHDR* pNMHDR, LRESULT* pResult ) 
{
   PostMessage( WM_COMMAND, IDOK );
   *pResult = 0;
}


//*************************************************************
bool SelectAddressDlg::GetOverrideItemString(long lSubstituteId, const DString &ColumnKey, DString &strOut)
{
   DString str;  

   if( lSubstituteId == ifds::ShareholderAddressHeadingSet.getId() )
   {
      if( ColumnKey== ADDRESS )
      {
         DString strPostalCode;
         getParent()->getField( this, IFASTBP_PROC::ADDRESSES_LIST, ifds::PostalCode, strPostalCode );
         strPostalCode.strip();

         getParent()->getField( this, IFASTBP_PROC::ADDRESSES_LIST, ifds::AddrLine1, str );
         str.strip();
         strOut = str+SPACE_STRING ;//reset the old value
         getParent()->getField( this, IFASTBP_PROC::ADDRESSES_LIST, ifds::AddrLine2, str );
         str.strip();
         strOut += str+SPACE_STRING;
         getParent()->getField( this, IFASTBP_PROC::ADDRESSES_LIST, ifds::AddrLine3, str );
         str.strip();
         strOut += str+SPACE_STRING;
         getParent()->getField( this, IFASTBP_PROC::ADDRESSES_LIST, ifds::AddrLine4, str );
         str.strip();
         strOut += str+SPACE_STRING;
         getParent()->getField( this, IFASTBP_PROC::ADDRESSES_LIST, ifds::AddrLine5, str );
         str.strip();
         strOut += str+SPACE_STRING;
         getParent()->getField( this, IFASTBP_PROC::ADDRESSES_LIST, ifds::kAddrLine1, str );
         str.strip();
         strOut += str+SPACE_STRING;
         getParent()->getField( this, IFASTBP_PROC::ADDRESSES_LIST, ifds::kAddrLine2, str );
         str.strip();
         strOut += str+SPACE_STRING;
         getParent()->getField( this, IFASTBP_PROC::ADDRESSES_LIST, ifds::kAddrLine3, str );
         str.strip();
         strOut += str+SPACE_STRING;
         getParent()->getField( this, IFASTBP_PROC::ADDRESSES_LIST, ifds::kAddrLine4, str );
         str.strip();
         strOut += str+SPACE_STRING;
         getParent()->getField( this, IFASTBP_PROC::ADDRESSES_LIST, ifds::kAddrLine5, str );
         str.strip();
         strOut += str;

         DString strMarket = DSTCommonFunctions::getMarket();
         if( strMarket == MARKET_IDS::JAPAN )
         {
            //put the postal code first
            strPostalCode += SPACE_STRING;
            strOut = strPostalCode + strOut;
         }
         else if( strMarket == MARKET_IDS::CANADA || strMarket == MARKET_IDS::LUXEMBOURG )
         {
            //put postal code at the end
            strOut += SPACE_STRING;
            strOut += strPostalCode;
         }
         return(true);
      }
      else if( ColumnKey == ADDRESSCODE )
      {
         getParent()->getField( this, IFASTBP_PROC::ADDRESSES_LIST, ifds::AddrCode, strOut,false );
         strOut.strip();

         return(true);
      }
      else if( ColumnKey == ADDRESSCODEDESC )
      {

         DString strTemp1,strTemp2,strTemp3;
         getParent()->getField(this,IFASTBP_PROC::ADDRESSES_LIST,ifds::AddrCode,strTemp1,false);
         strTemp1.strip();
         getParent()->getField(this,IFASTBP_PROC::ADDRESSES_LIST,ifds::AddrCode,strTemp2);
         strTemp2.strip();
         if( strTemp1 == strTemp2 ) strOut = I_("");
         else   strOut = strTemp2;
         return(true);  
      }
      else if( ColumnKey == STATUS )
      {
         getParent()->getField(this,IFASTBP_PROC::ADDRESSES_LIST,ifds::AddrStatus,strOut,true);
         return(true);        
      }
   }

   return(false);
}
//------------------------------------------------------




//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/SelectAddressDlg.cpp-arc  $
// 
//    Rev 1.6   Sep 15 2005 15:15:04   popescu
// Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
// 
//    Rev 1.5   Jun 25 2003 17:50:20   HERNANDO
// Revised title display.
// 
//    Rev 1.4   Mar 21 2003 18:40:42   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.3   Oct 09 2002 23:56:12   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.2   Sep 30 2002 11:01:42   PURDYECH
// BFFieldId no longer has operator long(), so explicit getId() calls are needed in places.
// 
//    Rev 1.1   Jun 14 2002 14:43:28   YINGBAOL
// show title
// 
//    Rev 1.0   Jun 11 2002 11:48:22   YINGBAOL
// Initial revision.
 * 

 
*/