//*****************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 1999 by DST Systems, Inc.
//
//*****************************************************************************
//
// ^FILE   : AcctCategoryList.cpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : January 21, 2003
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : AcctCategoryList
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************
#include "stdafx.h"
#include "acctcategorylist.hpp"
#include "acctcategory.hpp"
#include "mfaccount.hpp"
#include "mgmtco.hpp"
#include "errmsgruleslist.hpp"
#include <ifastdataimpl\dse_dstc0245_req.hpp>
#include <ifastdataimpl\dse_dstc0245_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0245_vw.hpp>

#include <conditions\iFastLayer\iFast\ifastcbo\IFast_IFast_ifastcbo_err_acct_category_not_co_exist.h>

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "AcctCategoryList" );
   const I_CHAR * const WRAP              = I_( "04" );
   const I_CHAR * const CUSTODY_CLIENT    = I_( "06" );
   const I_CHAR * const TRADING_CLIENT    = I_( "07" );
   const I_CHAR * const INVESTRO_CAPABLE  = I_( "08" );
   const I_CHAR * const PUEV_CAPABLE      = I_( "09" );
   const I_CHAR * const OLD_APP           = I_( "32" );
   const I_CHAR * const NEW_APP           = I_( "33" );
   const I_CHAR * const EPA_APP           = I_( "57" );
   const I_CHAR * const ROUTING_CLIENT    = I_( "60" );
}

namespace ACCOUNT_CATEGORY
{
   extern CLASS_EXPORT I_CHAR * const GARS1;
   extern CLASS_EXPORT I_CHAR * const GARS2;
   extern CLASS_EXPORT I_CHAR * const GARS3;
   extern CLASS_EXPORT I_CHAR * const GARSDA;
}

//namespace AGGREGATION_TYPE
//{
//  const I_CHAR * const REGULAR     = I_("REG");
//  const I_CHAR * const IMMEDIATE   = I_("IMM");
//  const I_CHAR * const CONTINUOUS  = I_("CON");
//}
namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest ACCT_CATEGORY_LIST;
}

namespace CND
{
   extern const long ERR_ONLY_ONE_CATEGORY;
   extern const long ERR_EITHER_CUSTODY_TRADING_REQUIRED;
   extern const long WARN_EITHER_CUSTODY_TRADING_REQUIRED;
   extern const long ERR_CUSTODY_TRADING_CANNOT_COEXIST;
   extern const long WARN__MISSING;
   extern const long ERR_PUEV_ENTRY_REQUIRED;
   extern const long ERR_ALTACCT_REQUIRED_FOR_PUEV_INVESTRO;
   extern const long WARN_ACCT_CATEG_PUEV_SHOULD_BE_SETUP_BASED_ON_CLEARINGID;
   extern const long WARN_ACCT_CATEG_NAV_SHARE_LOTS_DELETED_PENDING_TRADES_EXIST;
   extern const long WARN_ACCT_CATEG_NAV_SHARE_LOTS_ADDED_PENDING_TRADES_EXIST;
   extern const long ERR_ACCT_CATEGORY_NOT_CO_EXIST;
}


namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId WrapAccount;
   extern CLASS_IMPORT const BFTextFieldId AltAccount;
   extern CLASS_IMPORT const BFTextFieldId ClearingID;
   extern CLASS_IMPORT const BFTextFieldId PendingTrade;
   extern CLASS_IMPORT const BFTextFieldId AggregationType;
   extern CLASS_IMPORT const BFTextFieldId AggActive; 
   extern CLASS_IMPORT const BFTextFieldId AggActCatgry;
   extern CLASS_IMPORT const BFTextFieldId AggDefAggMod;
}

//******************************************************************************
AcctCategoryList::AcctCategoryList( BFAbstractCBO &parent ) 
: MFCanBFCbo( parent ), _pErrMsgRulesList (NULL)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList( );

}

//******************************************************************************
AcctCategoryList::~AcctCategoryList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY AcctCategoryList::initNew(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("initNew") );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY AcctCategoryList::init( const DString& dstrTrack,
                              const DString& dstrPageName )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("init") );

   DString strAcctNum, mgmtCoIdOut;
   getParent()->getField(ifds::AccountNum, strAcctNum, BF::HOST, false);

   BFData queryData(ifds::DSTC0245_REQ);

   queryData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   queryData.setElementValue( ifds::AccountNum,  strAcctNum.strip(), false, false );
   queryData.setElementValue( ifds::Track, dstrTrack );
   queryData.setElementValue( ifds::Activity, dstrPageName );

   ReceiveData(DSTC_REQUEST::ACCT_CATEGORY_LIST, queryData, ifds::DSTC0245_VW, DSTCRequestor( getSecurity() ) );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY AcctCategoryList::doCreateNewObject( BFCBO *& pBase, DString &strKey, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateNewObject" ) );

   AcctCategory *pAcctCategory = new AcctCategory( *this );
   pAcctCategory->initNew( idDataGroup );
   pBase = pAcctCategory;
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY AcctCategoryList::doCreateObject( const BFData& data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

   pObjOut = new AcctCategory( *this );
   ( ( AcctCategory* ) ( pObjOut ) )->init( data );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY AcctCategoryList::doValidateAll(const BFDataGroupId& idDataGroup, 
                                         long lValidateGroup ) // csc who calls tis func??
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );

   DString dstrMarket = DSTCommonFunctions::getMarket();

   DString dstrPendingTradeExist;
   MFAccount* pMFAccount = dynamic_cast <MFAccount*> (getParent());
   if ( NULL != pMFAccount )
	   pMFAccount->getField( ifds::PendingTrade, dstrPendingTradeExist, idDataGroup );   

   dstrPendingTradeExist.strip().upperCase();
   
   if ( I_( "Y" ) == dstrPendingTradeExist )
   {	
		BFObjIter iterDeleted( *this, idDataGroup, false, BFObjIter::ITERTYPE::DELETED );
		iterDeleted.begin();
		while( !iterDeleted.end() )
		{
			DString dstrCategory;
			iterDeleted.getObject()->getField(ifds::AcctCategory, dstrCategory, idDataGroup, false);

			if ( I_( "11" ) == dstrCategory.strip() )
			{
				// Nav Share lots Account Category deleted. Pending Trades exist.
				ADDCONDITIONFROMFILE( CND::WARN_ACCT_CATEG_NAV_SHARE_LOTS_DELETED_PENDING_TRADES_EXIST );	
				break;
			}
			
			++iterDeleted; 
		}		
   }	

   std::set< DString > setCharacteristic;
   BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
   iter.begin();
   while( !iter.end() )
   {
      DString strCategoryType;
      iter.getObject()->getField(ifds::AcctCategory, strCategoryType, idDataGroup, false);

      if( !setCharacteristic.insert( strCategoryType.strip().upperCase() ).second )
      {
         ADDCONDITIONFROMFILE( CND::ERR_ONLY_ONE_CATEGORY );
         break;
      }

	  AcctCategory* pAcctCategory = dynamic_cast <AcctCategory*> (iter.getObject());

      //If the current account category item is wrap and is newly added we will ask 
      //mfaccount to set the default values for viscount, otherwise we won't do anything.
      if ( strCategoryType == WRAP ) {         
         if ( pAcctCategory->isNew() ) 
         {
            MFAccount* pMFAccount = dynamic_cast <MFAccount*> (getParent());

            DString dstrWrapOption;

            //see whether wrap defaults is active or not
            getWorkSession().getOption(ifds::WrapAccount, 
               dstrWrapOption, idDataGroup, false);
            
            pMFAccount->setWRAPAcctDefaults (dstrWrapOption == I_("Y"), idDataGroup);			
         }		 
      }

	  if ( I_( "Y" ) == dstrPendingTradeExist &&
		   I_( "11" ) == strCategoryType.strip() &&
		   NULL != pAcctCategory &&
		   pAcctCategory->isNew() )
	  {								
		// Nav Share lots Account Category added. Pending Trades exist.
		ADDCONDITIONFROMFILE( CND::WARN_ACCT_CATEG_NAV_SHARE_LOTS_ADDED_PENDING_TRADES_EXIST );			
	  }	

      ++iter; 
   }

   
   
    // Account should be either a CUSTODY_CLIENT or TRADING_CLIENT
   if (!isCategoryExist( idDataGroup, CUSTODY_CLIENT) && !isCategoryExist( idDataGroup, TRADING_CLIENT) 
	   && !isCategoryExist( idDataGroup, ROUTING_CLIENT) ) 
   {
      DString dstrErrValue; 
      getErrMsgValue (I_ ("416"), idDataGroup, dstrErrValue);

      if (dstrErrValue == I_("E"))
      {
        ADDCONDITIONFROMFILE( CND::ERR_EITHER_CUSTODY_TRADING_REQUIRED ); 
      }
      else if (dstrErrValue == I_("W"))
      {
         ADDCONDITIONFROMFILE( CND::WARN_EITHER_CUSTODY_TRADING_REQUIRED );
      }
   
   }

   // Account cannot be both CUSTODY_CLIENT and TRADING_CLIENT
   if ( (isCategoryExist( idDataGroup, CUSTODY_CLIENT) && isCategoryExist( idDataGroup, TRADING_CLIENT))
	   || (isCategoryExist( idDataGroup, CUSTODY_CLIENT) && isCategoryExist( idDataGroup, ROUTING_CLIENT))
	   || (isCategoryExist( idDataGroup, ROUTING_CLIENT) && isCategoryExist( idDataGroup, TRADING_CLIENT)))
   {
      ADDCONDITIONFROMFILE( CND::ERR_CUSTODY_TRADING_CANNOT_COEXIST );
   }

   // If account is either PUEV_CAPABLE or INVESTRO_CAPABLE, then AltAccountNum is required
   if (isCategoryExist( idDataGroup, PUEV_CAPABLE) || isCategoryExist( idDataGroup, INVESTRO_CAPABLE) )
   {

      MFAccount* pMFAccount = dynamic_cast <MFAccount*> (getParent());

      DString dstrAltAccountNum;
      pMFAccount->getField( ifds::AltAccount, dstrAltAccountNum, idDataGroup, false );
      if (dstrAltAccountNum == NULL_STRING)
      {
         ADDCONDITIONFROMFILE( CND::ERR_ALTACCT_REQUIRED_FOR_PUEV_INVESTRO );
      }
   }

   /* If account is INVESTRO_CAPABLE, it should also be PUEV_CAPABLE; the reverse is not true, i.e., if account is PUEV_CAPABLE, it doesn't have
    to be INVESTRO_CAPABLE  */

   if (isCategoryExist( idDataGroup, INVESTRO_CAPABLE))
   {
      if (!isCategoryExist( idDataGroup, PUEV_CAPABLE) )
      {
         ADDCONDITIONFROMFILE( CND::ERR_PUEV_ENTRY_REQUIRED );
      }
   }
     
   // if MFAccount.clearingId = PUEV, and account is not PUEV_Capable, raise warning

   DString dstrClearingId;
      
   pMFAccount->getField( ifds::ClearingID, dstrClearingId, idDataGroup, false );

   if (dstrClearingId == I_("P" )
      && !(isCategoryExist( idDataGroup, PUEV_CAPABLE) )  )
   {
         ADDCONDITIONFROMFILE( CND::WARN_ACCT_CATEG_PUEV_SHOULD_BE_SETUP_BASED_ON_CLEARINGID );
   }

   if ( ( isCategoryExist( idDataGroup, OLD_APP) && isCategoryExist( idDataGroup, NEW_APP)) ||
        ( isCategoryExist( idDataGroup, OLD_APP) && isCategoryExist( idDataGroup, EPA_APP)) ||
        ( isCategoryExist( idDataGroup, NEW_APP) && isCategoryExist( idDataGroup, EPA_APP)) )
   {
      //ADDCONDITIONFROMFILE( CND::ERR_ACCT_CATEGORY_NOT_CO_EXIST );
   }

   if ( ( isCategoryExist( idDataGroup, ACCOUNT_CATEGORY::GARS1) && isCategoryExist( idDataGroup, ACCOUNT_CATEGORY::GARS2))  ||
        ( isCategoryExist( idDataGroup, ACCOUNT_CATEGORY::GARS1) && isCategoryExist( idDataGroup, ACCOUNT_CATEGORY::GARS3))  ||
        ( isCategoryExist( idDataGroup, ACCOUNT_CATEGORY::GARS1) && isCategoryExist( idDataGroup, ACCOUNT_CATEGORY::GARSDA)) ||
        ( isCategoryExist( idDataGroup, ACCOUNT_CATEGORY::GARS2) && isCategoryExist( idDataGroup, ACCOUNT_CATEGORY::GARS3))  ||
        ( isCategoryExist( idDataGroup, ACCOUNT_CATEGORY::GARS2) && isCategoryExist( idDataGroup, ACCOUNT_CATEGORY::GARSDA)) ||
        ( isCategoryExist( idDataGroup, ACCOUNT_CATEGORY::GARS3) && isCategoryExist( idDataGroup, ACCOUNT_CATEGORY::GARSDA)) )
   {
      // validation logic has been taken out until get confirmation from client
      // that whether it is only one GARS attached to the account or not

      //CND::CIFast_IFast_ifastcbo_err_acct_category_not_co_exist errCond;
      //ADDCONDITIONFROMOBJECT(errCond);
   }

   //let all the validation for catogoery sucessfully pass and then set account default for AggregationType
   if( GETCURRENTHIGHESTSEVERITY() <= WARNING) 
       setAggregationType( idDataGroup );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
bool AcctCategoryList::isCategoryExist( const BFDataGroupId& idDataGroup, const DString& dstrCategoryType )
{
   DString strCategTypeIn(dstrCategoryType);
   strCategTypeIn.strip();
   BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
   while( !iter.end() )
   {
      DString strCategoryType;
      iter.getObject()->getField(ifds::AcctCategory, strCategoryType, idDataGroup, false);

      if( strCategoryType.strip() == strCategTypeIn)
      {
         return true;
      }
      ++iter; 
   }
   return false;
}

//******************************************************************************
// This method will execute when a CBO item is deleted from the list.   It will 
// check to see if the deleted CBO has a AcctCategory of WRAP (04).  If it is
// WRAP, it will call MFAccount::setWRAPAcctDefaults (false,idDataGroup) to reset
// the defaults set when the WRAP category was added.
// @param   const DSTring& strKey - key of CBO being deleted.
//          const BFDataGroupId& idDataGroup - current data group id.
//          bool bIsObjectDestroyed - is object being destroyed?
// @returns SEVERITY - should always be NO_CONDITION
//******************************************************************************

SEVERITY AcctCategoryList::doDeleteObject (const DString&  strKey, 
   const BFDataGroupId& idDataGroup, bool bIsObjectDestroyed )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doDeleteObject" ) );
   DString dstrAcctCategory;
   BFObjIter iter( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);
   iter.setKeyFilter( strKey );
   if ( !iter.end() ) {
      iter.getObject()->getField ( ifds::AcctCategory, dstrAcctCategory, idDataGroup );
      //If the deleted object was an WRAP account then undo default values on MFAccount for WRAP accounts.
      if ( dstrAcctCategory == WRAP ) {
         MFAccount* pMFAccount = dynamic_cast <MFAccount*> ( getParent() );
         pMFAccount->setWRAPAcctDefaults ( false, idDataGroup );
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}


//************************************************************************************
SEVERITY AcctCategoryList::getErrMsgValue( DString dstrErrNum,       
								  const BFDataGroupId& idDataGroup, 
								  DString& dstrErrValue 
								)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getErrMsgValue" ) );
   if( _pErrMsgRulesList == NULL )
   {
      SEVERITY sevRtn = getMgmtCo().getErrMsgRulesList( _pErrMsgRulesList );
   }

   if( _pErrMsgRulesList )
   {	   
      _pErrMsgRulesList->getEWIValue( dstrErrNum, idDataGroup, dstrErrValue);
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

void AcctCategoryList::getDescriptions( const BFDataGroupId& idDataGroup, DString &dstrDescriptions )
{
   DString dstrValueOut;
   BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
   while( !iter.end() )
   {
      DString dstrAcctCategory;
      iter.getObject()->getField(ifds::AcctCategory, dstrAcctCategory, idDataGroup, true );

      if( !dstrValueOut.empty() )
      {
         dstrValueOut += I_(";");
      }
      dstrValueOut += dstrAcctCategory;
      ++iter; 
   }
   dstrDescriptions = dstrValueOut;
   return;
}

//******************************************************************************
void AcctCategoryList::setAggregationType( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setAggregationType" ) );
   
   DString dstraggrActiveAtEnv;
   MFAccount* pMFAccount = dynamic_cast <MFAccount*> (getParent());

   getWorkSession().getOption( ifds::AggActive, dstraggrActiveAtEnv, idDataGroup, false); 
   dstraggrActiveAtEnv.upperCase();
   if( I_("Y") != dstraggrActiveAtEnv )
   {
      pMFAccount->setFieldReadOnly( ifds::AggregationType, idDataGroup, true);
      return;
   }    
  
   if( pMFAccount )
   {
      
      //FOR DELETED CATEGORY
      // It is user procedure to handle the deletion of category as insited by the Business requirement.
      //so commenting the code to handle deletion.

      //BFObjIter iterCatDel( *this, idDataGroup, false, BFObjIter::ITERTYPE::DELETED );
      //iterCatDel.begin();
      //while( !iterCatDel.end() )
      //{
      //   AcctCategory* pAcctCategory = dynamic_cast <AcctCategory*> (iterCatDel.getObject());
      //   if( pAcctCategory )
      //   {
      //      DString dstrAcctCategory, dstrDefaultAggrMod;
      //      pAcctCategory->getField(ifds::AcctCategory, dstrAcctCategory, idDataGroup );
      //      getDefaultAggregationType( dstrAcctCategory,  dstrDefaultAggrMod, idDataGroup); 
      //      if(!dstrDefaultAggrMod.stripAll().empty())  // a default value existed, make NULL_STRING
      //          pMFAccount->setDefaultAggregationType( NULL_STRING, idDataGroup);
      //      //if( TRADING_CLIENT == dstrAcctCategory || CUSTODY_CLIENT == dstrAcctCategory || 
      //      //    ROUTING_CLIENT == dstrAcctCategory )
      //      //    pMFAccount->setDefaultAggregationType(NULL_STRING, idDataGroup);
      //   }
      //    ++iterCatDel;       
      //}

      //FOR NEWLY ADDED CATEGORY

      BFObjIter iterCatAdd( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
      iterCatAdd.begin();
      while( !iterCatAdd.end() )
      {
         DString dstrOldAggrTypeValue;
         AcctCategory* pAcctCategory = dynamic_cast <AcctCategory*> (iterCatAdd.getObject());
         pMFAccount->getFieldBeforeImage(ifds::AggregationType, dstrOldAggrTypeValue, false);
         //if default alreday set don't overide it.
         //User procedure to overide this manually.
         if( !dstrOldAggrTypeValue.empty() )
             break;
         if( pAcctCategory && pAcctCategory->isNew() ) 
         {
            DString dstrAcctCategory, dstrDefaultAggrMod;
            pAcctCategory->getField(ifds::AcctCategory, dstrAcctCategory, idDataGroup );
            getDefaultAggregationType( dstrAcctCategory,  dstrDefaultAggrMod, idDataGroup);
            pMFAccount->setDefaultAggregationType(dstrDefaultAggrMod, idDataGroup);
            if(!dstrDefaultAggrMod.empty())
               break;
            //if( TRADING_CLIENT == dstrAcctCategory || CUSTODY_CLIENT == dstrAcctCategory )
            //    pMFAccount->setDefaultAggregationType(AGGREGATION_TYPE::REGULAR, idDataGroup);
            //if( ROUTING_CLIENT == dstrAcctCategory )
            //    pMFAccount->setDefaultAggregationType(AGGREGATION_TYPE::IMMEDIATE, idDataGroup);
         }
          ++iterCatAdd;       
      }
      DString dstrAggrType;
      pMFAccount->getField( ifds::AggregationType, dstrAggrType, idDataGroup);
      pMFAccount->setFieldReadOnly( ifds::AggregationType, idDataGroup, dstrAggrType.stripAll().empty());
      
      //bAggregationTypeAppl = isCategoryExist( idDataGroup, CUSTODY_CLIENT) ||
      //                       isCategoryExist( idDataGroup, TRADING_CLIENT) ||
      //                       isCategoryExist( idDataGroup, ROUTING_CLIENT);   
 
      //pMFAccount->setFieldReadOnly( ifds::AggregationType, idDataGroup, !bAggregationTypeAppl);
  }
}

//******************************************************************************
void AcctCategoryList::getDefaultAggregationType( const DString& dstrCurrCategory, DString& dstrDefaultAggrMod ,
                                                  const BFDataGroupId& idDataGroup )
{

    MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getDefaultAggregationType" ) );
    DString dstrAggrAcctCatList, dstrDefAggModList, dstrCategory;
    getWorkSession().getOption( ifds::AggActCatgry, dstrAggrAcctCatList, idDataGroup, false); 
    getWorkSession().getOption( ifds::AggDefAggMod, dstrDefAggModList, idDataGroup, false); 

    dstrDefaultAggrMod == NULL_STRING;
    //start chopping the string
    do
    {
        DString::size_type pos = 0;
        EXTRACT_VALUE(dstrAggrAcctCatList, dstrCategory)
        if (dstrCategory == dstrCurrCategory) //found the transaction type
        {
            EXTRACT_VALUE (dstrDefAggModList, dstrDefaultAggrMod)
            break;
        }
        else //cut the string
        {
            CHOP_STRING (dstrAggrAcctCatList)
            CHOP_STRING (dstrDefAggModList)
        }
    }
    while (dstrAggrAcctCatList != NULL_STRING);  
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AcctCategoryList.cpp-arc  $
// 
//    Rev 1.14   Aug 03 2011 11:22:30   wp040027
// P0186774 - Mutual Fund Order Processing
// 
//    Rev 1.13   Dec 01 2010 06:23:16   dchatcha
// P0175716 FN02 - Client Name Redemption - EPA Auto Settlement.
// 
//    Rev 1.12   May 26 2005 13:58:44   porteanm
// PET1203 FN05 - Class B NAV Share Lots - cleanup.
// 
//    Rev 1.11   May 26 2005 13:56:42   porteanm
// PET1203 FN05 - Class B NAV Share Lots - warning when adding/deleting NAV Share category when pending trades exist.
// 
//    Rev 1.10   Nov 07 2004 16:10:24   popescu
// PET 1117/56, minor compilation/link errors
// 
//    Rev 1.9   Nov 05 2004 17:34:26   AGUILAAM
// PET1170_FN21: settlement instructions enhancement
// 
//    Rev 1.8   Sep 23 2004 09:55:26   AGUILAAM
// PET1117_FN02: account, custody, puev-, or investro-cabable checking will be applied to all markets; error and generic control setting will take care of error handling.
// 
//    Rev 1.7   Sep 12 2004 15:09:02   HERNANDO
// PET1117 FN02 - Display account categories in the Trade Cautions combo box change.  Added fn. to retrieve a comma-delimited list of category descriptions.
// 
//    Rev 1.6   Aug 12 2004 10:34:44   AGUILAAM
// PET1117_FN02: Acct Static_ changed initialization of errmsgrules
// 
//    Rev 1.5   Aug 11 2004 11:59:58   AGUILAAM
// PET1117_FN02:  Account Static enhancement for SSBG - added new acct categories, and contact person, registrationinfo fields
// 
//    Rev 1.4   Jun 05 2003 16:20:30   popescu
// when setting the defaulst for a wrap account look whether the WrapAccount option from managemant company option is set to Y
// 
//    Rev 1.3   Mar 21 2003 17:55:54   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.2   Feb 06 2003 15:03:28   HSUCHIN
// added doDeleteObject to reset MFAccount default values for WRAP accounts and changed validateAll to set MFAccount defaults for WRAP accounts.
// 
//    Rev 1.1   Jan 25 2003 17:01:18   KOVACSRO
// Added isCategoryExist
// 
//    Rev 1.0   Jan 21 2003 14:26:22   KOVACSRO
// Initial revision.

 */