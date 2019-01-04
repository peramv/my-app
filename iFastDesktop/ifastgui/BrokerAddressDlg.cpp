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
//    Copyright 2003 by International Financial Data Services.
//
//******************************************************************************
//
// ^FILE   : BrokerAddressDlg.cpp
// ^AUTHOR : Yingbao Li
// ^DATE   : March 31, 2003
//
// ----------------------------------------------------------
//
// ^CLASS    : BrokerAddressDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  This is the code for  BrokerAddress dialog
//
//******************************************************************************



#include "stdafx.h"
#include "mfdstc.h"

#include "BrokerAddressDlg.h"
#include <ifastbp\BrokerAddressProcessincludes.h>
#include <ifastcbo\dstcommonfunction.hpp>


extern CLASS_IMPORT const I_CHAR* CMD_GUI_BROKER_ADDRESS;
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< BrokerAddressDlg > dlgCreator( CMD_GUI_BROKER_ADDRESS );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR * const CLASSNAME = I_( "BrokerAddressDlg" );
   const I_CHAR * const LV_ADDRESS_LIST = I_( "AddressList" );
   const I_CHAR *ADDRESS         = I_("Address");
   const I_CHAR *ADDRESSCODE       = I_("AddressCode");
   const I_CHAR *TAXTYPE        = I_( "TaxType" );
   const I_CHAR *SPACE_STRING        = I_( " " );
}

namespace CND
{  // Conditions used
   extern CLASS_IMPORT const long GUI_ERR_UNKNOWN_EXCEPTION;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId BrokerAddressHeadingSet;

}


/////////////////////////////////////////////////////////////////////////////
// BrokerAddressDlg dialog

//******************************BrokerAddressDlg()****************************
BrokerAddressDlg::BrokerAddressDlg( CWnd *pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
:BaseMainDlg( BrokerAddressDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
{
   //{{AFX_DATA_INIT(BrokerAddressDlg)
   // NOTE: the ClassWizard will add member initialization here
   //}}AFX_DATA_INIT
}

//**********************************************************
void BrokerAddressDlg::DoDataExchange(CDataExchange* pDX)
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(BrokerAddressDlg)
   // NOTE: the ClassWizard will add DDX and DDV calls here

   //}}AFX_DATA_MAP
}

//*******************************************************
BEGIN_MESSAGE_MAP(BrokerAddressDlg, BaseMainDlg)
//{{AFX_MSG_MAP(BrokerAddressDlg)
ON_NOTIFY( NM_DBLCLK, IDC_ADDRESS_LIST, OnDblclkAddressList )

//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// BrokerAddressDlg message handlers

/*************************************************************************/
SEVERITY BrokerAddressDlg::doInit()
{

   return(NO_CONDITION);
}

//****************************************************************/
void BrokerAddressDlg::OnPostInitDialog()
{
   AddListControl( CLASSNAME, IDC_BROKER_ADDRESS_LIST, LV_ADDRESS_LIST, ifds::BrokerAddressHeadingSet, IFASTBP_PROC::BROKER_ADDRESS_LIST ); 
   LoadListControl( IDC_BROKER_ADDRESS_LIST );

}

//**********************************************************************
void BrokerAddressDlg::OnDblclkAddressList( NMHDR* pNMHDR, LRESULT* pResult ) 
{
   PostMessage( WM_COMMAND, IDOK );
   *pResult = 0;
}


//*************************************************************
bool BrokerAddressDlg::GetOverrideItemString(long lSubstituteId, const DString &ColumnKey, DString &strOut)
{
   DString str;  

   if( lSubstituteId == ifds::BrokerAddressHeadingSet.getId() )
   {
      if( ColumnKey== ADDRESS )
      {
         DString strPostalCode;
         getParent()->getField( this, IFASTBP_PROC::BROKER_ADDRESS_LIST, ifds::PostalCode, strPostalCode );
         strPostalCode.strip();

         getParent()->getField( this, IFASTBP_PROC::BROKER_ADDRESS_LIST, ifds::Addr11Line1, str );
         str.strip();
         strOut = str+SPACE_STRING ;//reset the old value
         getParent()->getField( this, IFASTBP_PROC::BROKER_ADDRESS_LIST, ifds::Addr11Line2, str );
         str.strip();
         strOut += str+SPACE_STRING;
         getParent()->getField( this, IFASTBP_PROC::BROKER_ADDRESS_LIST, ifds::Addr11Line3, str );
         str.strip();
         strOut += str+SPACE_STRING;
         getParent()->getField( this, IFASTBP_PROC::BROKER_ADDRESS_LIST, ifds::Addr11Line4, str );
         str.strip();
         strOut += str+SPACE_STRING;
         getParent()->getField( this, IFASTBP_PROC::BROKER_ADDRESS_LIST, ifds::Addr11Line5, str );
         str.strip();
         strOut += str+SPACE_STRING;
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
         getParent()->getField( this, IFASTBP_PROC::BROKER_ADDRESS_LIST, ifds::RegAddrCode, strOut,false );
         strOut.strip();

         return(true);
      }
   }

   return(false);
}




//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/BrokerAddressDlg.cpp-arc  $
// 
//    Rev 1.2   Sep 15 2005 15:10:50   popescu
// Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
// 
//    Rev 1.1   Apr 03 2003 15:46:12   YINGBAOL
// put TaxType in
// 
//    Rev 1.0   Apr 03 2003 09:39:14   YINGBAOL
// Initial revision.
// 

 
*/