//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by Internation Financial Data Services
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2003 by Internation Financial Data Services
//
//
//******************************************************************************
//
// ^FILE   : AmsLmtOverrideList.cpp
// ^AUTHOR : May Lin
// ^DATE   : July 03, 2003
//
// ^CLASS    : AmsLmtOverrideList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "AmsLmtOverride.hpp"
#include "AmsLmtOverrideList.hpp"
#include "amsmstrlist.hpp"
#include "errmsgruleslist.hpp"
#include "mfaccount.hpp"
#include "mfaccountholdinglist.hpp"
#include "mgmtco.hpp"
#include "shareholder.hpp"

#include <ifastdataimpl\dse_dstc0004_vw.hpp>   // MFAccount
#include <ifastdataimpl\dse_dstc0020_vw.hpp>   // MFAccountHolding
#include <ifastdataimpl\dse_dstc0083_vw.hpp>
#include <ifastdataimpl\dse_dstc0149_vw.hpp>
#include <ifastdataimpl\dse_dstc0262_req.hpp>
#include <ifastdataimpl\dse_dstc0262_vw.hpp>


namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest AMS_LMT_OVERRIDE_LIST;
}

namespace
{
   //Trace literals
   const I_CHAR * const CLASSNAME             = I_( "AmsLmtOverrideList" );
   const I_CHAR * const NO                    = I_( "N" );
   const I_CHAR * const YES                   = I_( "Y" );
   const I_CHAR * const ALL                   = I_( "*" );
   const I_CHAR * const NOT_EXIST             = I_( "-1" );


   const I_CHAR * const MIN_PURCHASE            = I_("01");  
   const I_CHAR * const MIN_SUB_PURCHASE        = I_("02");  
   const I_CHAR * const STOP_PURCHASE           = I_("03");  
   const I_CHAR * const STOP_REDEMPTION                = I_("04");  
   const I_CHAR * const STOP_TRANSFER_IN              = I_("05");  
   const I_CHAR * const STOP_TRANSFER_OUT             = I_("06");  
   const I_CHAR * const MIN_PAC                = I_("07");  
   const I_CHAR * const STOP_PAC                   = I_("08");  
   const I_CHAR * const STOP_SWP                   = I_("09");  
   const I_CHAR * const STOP_AT_TRANSFER_IN                   = I_("10");  
   const I_CHAR * const STOP_AT_TRANSFER_OUT                   = I_("11");  
   const I_CHAR * const MIN_SWP                    = I_("12");  
   const I_CHAR * const MAX_REDEMPTION            = I_("13");  

   const I_CHAR * const RRSP_TAX_TYPE                    = I_( "1" );
   const I_CHAR * const RRIF_TAX_TYPE                    = I_( "2" );
   const I_CHAR * const LRIF_TAX_TYPE                    = I_( "L" );
   const I_CHAR * const PRIF_TAX_TYPE                    = I_( "R" );  
   const I_CHAR * const FAMILY_RESP_TAX_TYPE             = I_( "M" );
   const I_CHAR * const DPSP_TAX_TYPE                    = I_( "7" );
   const I_CHAR * const RPP_TAX_TYPE                     = I_( "8" );
   const I_CHAR * const INDIVIDUAL_RESP_TAX_TYPE         = I_( "9" ); 
   const I_CHAR * const LRSP_TAX_TYPE                    = I_( "U" );
   const I_CHAR * const WILL_DEFIND_TAX_TYPE             = I_( "S" ); 



}


namespace CND
{
   extern CLASS_IMPORT const long ERR_DATA_NOT_FOUND;

   extern const long AMS_LMT_ERR_STOP_PURCHASE;
   extern const long AMS_LMT_WARN_STOP_PURCHASE;
   extern const long AMS_LMT_ERR_MIN_PURCHASE;
   extern const long AMS_LMT_WARN_MIN_PURCHASE;
   extern const long AMS_LMT_ERR_MIN_SUB_PURCHASE;
   extern const long AMS_LMT_WARN_MIN_SUB_PURCHASE;
   extern const long AMS_LMT_ERR_MAX_REDEEM;
   extern const long AMS_LMT_WARN_MAX_REDEEM;
   extern const long AMS_LMT_ERR_STOP_REDEMPTION;
   extern const long AMS_LMT_WARN_STOP_REDEMPTION;
   extern const long AMS_LMT_ERR_MIN_PAC;
   extern const long AMS_LMT_WARN_MIN_PAC;
   extern const long AMS_LMT_ERR_STOP_PAC;
   extern const long AMS_LMT_WARN_STOP_PAC;
   extern const long AMS_LMT_ERR_STOP_SWP;
   extern const long AMS_LMT_WARN_STOP_SWP;
   extern const long AMS_LMT_ERR_MIN_SWP;
   extern const long AMS_LMT_WARN_MIN_SWP;
   extern const long AMS_LMT_ERR_STOP_AT_IN;
   extern const long AMS_LMT_WARN_STOP_AT_IN;
   extern const long AMS_LMT_ERR_STOP_AT_OUT;
   extern const long AMS_LMT_WARN_STOP_AT_OUT;
   extern const long AMS_LMT_ERR_STOP_TRANSFER_IN;
   extern const long AMS_LMT_WARN_STOP_TRANSFER_IN;
   extern const long AMS_LMT_ERR_STOP_TRANSFER_OUT;
   extern const long AMS_LMT_WARN_STOP_TRANSFER_OUT;   
	extern const long ERR_AMS_MKT_REBALANCING_LIMITATION_RULE_NOT_MET;
	extern const long WARN_AMS_MKT_REBALANCING_LIMITATION_RULE_NOT_MET;
}

namespace ifds
{
   extern CLASS_IMPORT const BFNumericFieldId ShrNum;
   extern CLASS_IMPORT const BFTextFieldId TaxType;
   extern CLASS_IMPORT const BFTextFieldId AcctType;
   extern CLASS_IMPORT const BFTextFieldId AcctDesignation;
   extern CLASS_IMPORT const BFTextFieldId TaxJurisCode;
   extern CLASS_IMPORT const BFTextFieldId ResProvCode;

}
//******************************************************************************
AmsLmtOverrideList::AmsLmtOverrideList( BFAbstractCBO &parent ) :
 MFCanBFCbo( parent )
,_requestData(ifds::DSTC0262_REQ)
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
   setObjectAsList( );

}


//******************************************************************************
AmsLmtOverrideList::~AmsLmtOverrideList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}


//******************************************************************************
SEVERITY AmsLmtOverrideList::init( const DString& dstrAmsCode, const DString& dstrEffectiveDate, const DString& dstrAMSType, const DString& dstrTrack,const DString& dstrPageName )

{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   BFData *receivedData = new BFData(ifds::DSTC0262_VW);

   DString mgmtCoIdOut;
   _requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   _requestData.setElementValue( ifds::Track, dstrTrack );
   _requestData.setElementValue( ifds::Activity, dstrPageName );
   _requestData.setElementValue( ifds::AMSCode, dstrAmsCode );
   _requestData.setElementValue( ifds::EffectiveDate, dstrEffectiveDate );
   _requestData.setElementValue( ifds::AMSType, dstrAMSType );
   _dstrAMSCode = dstrAmsCode;
	_dstrAMSType = dstrAMSType;

   ReceiveData( DSTC_REQUEST::AMS_LMT_OVERRIDE_LIST, _requestData, *receivedData, DSTCRequestor( getSecurity(), false, false) );
   return(GETCURRENTHIGHESTSEVERITY());

}


//******************************************************************************
SEVERITY AmsLmtOverrideList::doCreateObject( const BFData& data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

   AmsLmtOverride * pAmsLmtOverride = new AmsLmtOverride( *this );
   pAmsLmtOverride->init( data );
   pObjOut = pAmsLmtOverride;

   return(GETCURRENTHIGHESTSEVERITY());
}

//*****************************************************************************

SEVERITY AmsLmtOverrideList::getAmsLmtOverridebyType( const DString dstrRuleType
													, AmsLmtOverride *&pAmsLmtOverride
													, const BFDataGroupId& idDataGroup
													)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("getAmsLmtOverride") );

   pAmsLmtOverride = NULL;
   DString strType;
   BFObjIter iter(*this, idDataGroup, false , BFObjIter::ITERTYPE::NON_DELETED );
   while ( !iter.end() ) 
   {
      iter.getObject()->getField( ifds::RuleType, strType, idDataGroup, false );

      // find the corresponding record by matching the rule type with the input
      if ( strType == dstrRuleType ) 
      {
			pAmsLmtOverride = dynamic_cast<AmsLmtOverride*>( iter.getObject() );  
			break;
      }
      ++iter;
   }

   return(GETCURRENTHIGHESTSEVERITY());
}


//*****************************************************************************
SEVERITY AmsLmtOverrideList::doCreateNewObject(BFCBO *& pBase, DString & strKey, const BFDataGroupId& idDataGroup )
{

   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateNewObject" ) );

   pBase = new AmsLmtOverride( *this );
   ((AmsLmtOverride* )pBase)->initNew( idDataGroup );
   return(GETCURRENTHIGHESTSEVERITY());

}


//*****************************************************************************
SEVERITY AmsLmtOverrideList::getValueByType ( const DString& dstrLimitationCode, DString &dstrFieldValue,const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("getMaxRedAmt") );

   AmsLmtOverride *pAmsLmtOverride = NULL;

   SEVERITY sevRtn = getAmsLmtOverridebyType (dstrLimitationCode, pAmsLmtOverride, idDataGroup);   
      
   if ( pAmsLmtOverride )
   {
	   BFFieldId FieldId1;

	   if(dstrLimitationCode == MAX_REDEMPTION)
	   {
		   FieldId1 = ifds::OverrideDecimal;
	   }

       pAmsLmtOverride->getField( FieldId1, dstrFieldValue, idDataGroup, false );
   }
   else
	   dstrFieldValue = NOT_EXIST;
   return(GETCURRENTHIGHESTSEVERITY());

}

//******************************************************************************
void AmsLmtOverrideList::ModelAMS(AmsLmtOverrideList *Model, const BFDataGroupId& idDataGroup)
{
   AmsLmtOverride * pAmsLmtOverride = NULL;
   BFObjectKey objKey;

   BFObjIter iterDest(*this, idDataGroup);

   for(BFObjIter Iter(*Model, idDataGroup); !Iter.end(); ++Iter)
   {
      if(iterDest.end())
      {
         pAmsLmtOverride = static_cast< AmsLmtOverride * >(getNewListItem(objKey));
         pAmsLmtOverride->ModelAMS(static_cast< AmsLmtOverride * >(Iter.getObject()), idDataGroup);
      }
      else
      {
         pAmsLmtOverride = static_cast< AmsLmtOverride * >(iterDest.getObject());
         pAmsLmtOverride->ModelAMS(static_cast< AmsLmtOverride * >(Iter.getObject()), idDataGroup);
         ++iterDest;
      }
   }
  
}
/* No longer used since there can be multiple AMS Limit Override with the same Rule Type.
//*****************************************************************************
// This method will return the AMS Limit Override cbo based on the Rule Type
// Tax Jurisdiction, Province of Residence, Account Type, Tax Type and Account
// Designation.  If any of these above criteria does not match, NULL is returned.
//*****************************************************************************
SEVERITY AmsLmtOverrideList::getAMSLmtOverride( AmsLmtOverride*& pAMSLmtOverride,
      const DString dstrRuleType, const DString& dstrTaxJuris, 
      const DString& dstrProvResid, const DString& dstrAccountType, 
      const DString& dstrTaxType, const DString& dstrAcctDesign, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("getAMSLmtOverride") );
   SEVERITY sevRtn = getAmsLmtOverridebyType ( dstrRuleType, pAMSLmtOverride, idDataGroup );
   if ( sevRtn < WARNING ) {
      if (!( (pAMSLmtOverride->isTaxJurisInList ( dstrTaxJuris, idDataGroup ) ) &&
           (pAMSLmtOverride->isAcctDesignationInList ( dstrAcctDesign, idDataGroup ) ) &&
           (pAMSLmtOverride->isAcctTypeInList ( dstrAccountType, idDataGroup ) ) &&
           (pAMSLmtOverride->isTaxTypeInList ( dstrTaxType, idDataGroup ) ) &&
           (pAMSLmtOverride->isProvResInList ( dstrProvResid, idDataGroup ) ) ) ) {
         pAMSLmtOverride = NULL;   
      }
   } else {
      pAMSLmtOverride = NULL;
   }

   return(GETCURRENTHIGHESTSEVERITY());
}
*/
//*******************************************************************************
//*******************************************************************************

bool AmsLmtOverrideList::isAMSRestrictionMet ( AmsLmtOverride*& pAMSLmtOverride,
      const DString& dstrTaxJuris, const DString& dstrProvResid, const DString& dstrAccountType, 
      const DString& dstrTaxType, const DString& dstrAcctDesign, const BFDataGroupId& idDataGroup )
{
   return ( (pAMSLmtOverride->isTaxJurisInList ( dstrTaxJuris, idDataGroup ) ) &&
        (pAMSLmtOverride->isAcctDesignationInList ( dstrAcctDesign, idDataGroup ) ) &&
        (pAMSLmtOverride->isAcctTypeInList ( dstrAccountType, idDataGroup ) ) &&
        (pAMSLmtOverride->isTaxTypeInList ( dstrTaxType, idDataGroup ) ) &&
        (pAMSLmtOverride->isProvResInList ( dstrProvResid, idDataGroup ) ) );
}

//*******************************************************************************
//*******************************************************************************
SEVERITY AmsLmtOverrideList::canPurchase( const DString& dstrTaxJuris, const DString& dstrProvResid,
                                   const DString& dstrAccountType, const DString& dstrTaxType,
                                   const DString& dstrAcctDesign, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("canPurchase") );

   BFObjIter iter(*this, idDataGroup, false , BFObjIter::ITERTYPE::NON_DELETED );
   AmsLmtOverride* pAMSLmtOverride = NULL;
   DString dstrRuleType;
   while ( !iter.end() ) {
      pAMSLmtOverride = dynamic_cast<AmsLmtOverride*>( iter.getObject() );      
      if ( pAMSLmtOverride ) {
         pAMSLmtOverride->getField( ifds::RuleType, dstrRuleType, idDataGroup, false );
         // find the corresponding record by matching the rule type with the input
         if ( dstrRuleType == STOP_PURCHASE ){			         
            // AMS %CODE% has purchase stop flag turned on
            if ( isAMSRestrictionMet (pAMSLmtOverride, dstrTaxJuris, dstrProvResid, dstrAccountType,
                     dstrTaxType, dstrAcctDesign, idDataGroup) ) {
               DString dstrLmtLogical;
               pAMSLmtOverride->getLogicalField ( dstrLmtLogical, idDataGroup );
               if ( dstrLmtLogical == YES ) {
                  DString dstr;                  
                  addIDITagValue( dstr, I_("CODE"), _dstrAMSCode );
                  if ( pAMSLmtOverride->isError( idDataGroup ) ) {
                     ADDCONDITIONFROMFILEIDI( CND::AMS_LMT_ERR_STOP_PURCHASE, dstr );
                     //We do not want multiple errors, so return now.
                     return GETCURRENTHIGHESTSEVERITY();
                  } else if ( pAMSLmtOverride->isWarning( idDataGroup ) ) {                    
                     ADDCONDITIONFROMFILEIDI( CND::AMS_LMT_WARN_STOP_PURCHASE, dstr );
                     //We do not want multiple errors, so return now.
                     return GETCURRENTHIGHESTSEVERITY();
                  }
               }
            }
         }
      }
      ++iter;
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//*******************************************************************************
//*******************************************************************************
SEVERITY AmsLmtOverrideList::minPurchase( const DString& dstrTaxJuris, const DString& dstrProvResid,
                                   const DString& dstrAccountType, const DString& dstrTaxType,
                                   const DString& dstrAcctDesign, const DString& dstrAmount,
                                   bool& bFundOverride, bool bInitialPurchase,
                                   const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("minPurchase") );

   BFObjIter iter(*this, idDataGroup, false , BFObjIter::ITERTYPE::NON_DELETED );
   AmsLmtOverride* pAMSLmtOverride = NULL;
   DString dstrRuleType;
   while ( !iter.end() ) {
      pAMSLmtOverride = dynamic_cast<AmsLmtOverride*>( iter.getObject() );      
      if ( pAMSLmtOverride ) {
         pAMSLmtOverride->getField( ifds::RuleType, dstrRuleType, idDataGroup, false );
         // find the corresponding record by matching the rule type with the input
         if ( dstrRuleType == (bInitialPurchase?MIN_PURCHASE:MIN_SUB_PURCHASE )){	
            if ( isAMSRestrictionMet (pAMSLmtOverride, dstrTaxJuris, dstrProvResid, dstrAccountType,
                     dstrTaxType, dstrAcctDesign, idDataGroup) ) {
               DString dstrAmountLmt;
               double dAmount, dAmountLmt;
               pAMSLmtOverride->getDecimalField ( dstrAmountLmt, idDataGroup );               
               dAmount = DSTCommonFunctions::convertToDouble ( dstrAmount );
               dAmountLmt = DSTCommonFunctions::convertToDouble ( dstrAmountLmt );
               if ( dAmount < dAmountLmt ) {
                  DString dstr;                  
                  addIDITagValue( dstr, I_("CODE"), _dstrAMSCode );         
                  addIDITagValue( dstr, I_("AMOUNT"), dstrAmountLmt );         
                  long lErrorMsg, lWarningMsg;
                  if ( bInitialPurchase ) {
                     //AMS %CODE% has a minimum Purchase of %AMOUNT%
                     lErrorMsg = CND::AMS_LMT_ERR_MIN_PURCHASE;
                     lWarningMsg = CND::AMS_LMT_WARN_MIN_PURCHASE;
                  } else {
                     //AMS %CODE% has a minimum subsequent Purchase of %AMOUNT%
                     lErrorMsg = CND::AMS_LMT_ERR_MIN_SUB_PURCHASE;
                     lWarningMsg = CND::AMS_LMT_WARN_MIN_SUB_PURCHASE;   
                  }
                  if ( pAMSLmtOverride->isError( idDataGroup ) ) {   
                     //Return the fund override flag only if a limit was found.
                     pAMSLmtOverride->getFundOverride( bFundOverride, idDataGroup );
                     ADDCONDITIONFROMFILEIDI( lErrorMsg, dstr );
                     //We do not want multiple errors, so return now.
                     return GETCURRENTHIGHESTSEVERITY();
                  } else if ( pAMSLmtOverride->isWarning( idDataGroup ) ) {
                     pAMSLmtOverride->getFundOverride( bFundOverride, idDataGroup );
                     ADDCONDITIONFROMFILEIDI( lWarningMsg, dstr );
                     //We do not want multiple errors, so return now.
                     return GETCURRENTHIGHESTSEVERITY();
                  }
               }
            }
         }
      }
      ++iter;
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//*******************************************************************************
//*******************************************************************************
SEVERITY AmsLmtOverrideList::maxRedeem( const DString& dstrTaxJuris, const DString& dstrProvResid,
                                   const DString& dstrAccountType, const DString& dstrTaxType,
                                   const DString& dstrAcctDesign, const double dPercent,
                                   bool& bFundOverride, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("maxRedeem") );

   BFObjIter iter(*this, idDataGroup, false , BFObjIter::ITERTYPE::NON_DELETED );
   AmsLmtOverride* pAMSLmtOverride = NULL;
   DString dstrRuleType;
   while ( !iter.end() ) {
      pAMSLmtOverride = dynamic_cast<AmsLmtOverride*>( iter.getObject() );      
      if ( pAMSLmtOverride ) {
         pAMSLmtOverride->getField( ifds::RuleType, dstrRuleType, idDataGroup, false );
         // find the corresponding record by matching the rule type with the input
         if ( dstrRuleType == MAX_REDEMPTION){	
            if ( isAMSRestrictionMet (pAMSLmtOverride, dstrTaxJuris, dstrProvResid, dstrAccountType,
                     dstrTaxType, dstrAcctDesign, idDataGroup) ) {
               DString dstrMaxRedemPercent;
               double dMaxRedemPercent;
               pAMSLmtOverride->getDecimalField ( dstrMaxRedemPercent, idDataGroup );
               dMaxRedemPercent = DSTCommonFunctions::convertToDouble ( dstrMaxRedemPercent );
               pAMSLmtOverride->getFundOverride( bFundOverride, idDataGroup ); 
               //What level of percision should we take this to??
               if ( dPercent > dMaxRedemPercent ) {                       
                  DString dstr;     
				  DSTCommonFunctions::DisplayFormat( dstrMaxRedemPercent, ifds::OverrideDecimal );
                  addIDITagValue( dstr, I_("CODE"), _dstrAMSCode );      
                  addIDITagValue( dstr, I_("AMOUNT"), dstrMaxRedemPercent );      
                  if ( pAMSLmtOverride->isError( idDataGroup ) ) {         
                     //AMS %CODE% has a maximum redemption % of %AMOUNT%
                     ADDCONDITIONFROMFILEIDI( CND::AMS_LMT_ERR_MAX_REDEEM, dstr );
                     //We do not want multiple errors, so return now.
                     return GETCURRENTHIGHESTSEVERITY();
                  } else if ( pAMSLmtOverride->isWarning( idDataGroup ) ) {
                     ADDCONDITIONFROMFILEIDI( CND::AMS_LMT_WARN_MAX_REDEEM, dstr );
                     //We do not want multiple errors, so return now.
                     return GETCURRENTHIGHESTSEVERITY();
                  }
               }            
            }
         }      
      }
      ++iter;      
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//*******************************************************************************
//*******************************************************************************
SEVERITY AmsLmtOverrideList::canRedeem( const DString& dstrTaxJuris, const DString& dstrProvResid,
                                   const DString& dstrAccountType, const DString& dstrTaxType,
                                   const DString& dstrAcctDesign, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("canRedeem") );

   BFObjIter iter(*this, idDataGroup, false , BFObjIter::ITERTYPE::NON_DELETED );
   AmsLmtOverride* pAMSLmtOverride = NULL;
   DString dstrRuleType;
   while ( !iter.end() ) {
      pAMSLmtOverride = dynamic_cast<AmsLmtOverride*>( iter.getObject() );      
      if ( pAMSLmtOverride ) {
         pAMSLmtOverride->getField( ifds::RuleType, dstrRuleType, idDataGroup, false );
         // find the corresponding record by matching the rule type with the input
         if ( dstrRuleType == STOP_REDEMPTION ){			         
            // AMS %CODE% has redemption stop flag turned on
            if ( isAMSRestrictionMet (pAMSLmtOverride, dstrTaxJuris, dstrProvResid, dstrAccountType,
                     dstrTaxType, dstrAcctDesign, idDataGroup) ) {
               DString dstrLmtLogical;
               pAMSLmtOverride->getLogicalField ( dstrLmtLogical, idDataGroup );
               if ( dstrLmtLogical == YES ) {
                  DString dstr;                  
                  addIDITagValue( dstr, I_("CODE"), _dstrAMSCode );
                  if ( pAMSLmtOverride->isError( idDataGroup ) ) {
                     ADDCONDITIONFROMFILEIDI( CND::AMS_LMT_ERR_STOP_REDEMPTION, dstr );
                     //We do not want multiple errors, so return now.
                     return GETCURRENTHIGHESTSEVERITY();
                  } else if ( pAMSLmtOverride->isWarning( idDataGroup ) ) {                    
                     ADDCONDITIONFROMFILEIDI( CND::AMS_LMT_WARN_STOP_REDEMPTION, dstr );
                     //We do not want multiple errors, so return now.
                     return GETCURRENTHIGHESTSEVERITY();
                  }
               }
            }
         }
      }
      ++iter;
   }
   return GETCURRENTHIGHESTSEVERITY();
}


//*******************************************************************************
//*******************************************************************************
SEVERITY AmsLmtOverrideList::minPAC( const DString& dstrTaxJuris, const DString& dstrProvResid,
                                   const DString& dstrAccountType, const DString& dstrTaxType,
                                   const DString& dstrAcctDesign, const DString& dstrAmount,
                                   bool& bFundOverride, const BFDataGroupId& idDataGroup )
{

   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("minPAC") );
   BFObjIter iter(*this, idDataGroup, false , BFObjIter::ITERTYPE::NON_DELETED );
   AmsLmtOverride* pAMSLmtOverride = NULL;
   DString dstrRuleType;
   while ( !iter.end() ) {
      pAMSLmtOverride = dynamic_cast<AmsLmtOverride*>( iter.getObject() );      
      if ( pAMSLmtOverride ) {
         pAMSLmtOverride->getField( ifds::RuleType, dstrRuleType, idDataGroup, false );
         // find the corresponding record by matching the rule type with the input
         if ( dstrRuleType == MIN_PAC){	
            if ( isAMSRestrictionMet (pAMSLmtOverride, dstrTaxJuris, dstrProvResid, dstrAccountType,
                     dstrTaxType, dstrAcctDesign, idDataGroup) ) {
               DString dstrPACMin;
               pAMSLmtOverride->getDecimalField ( dstrPACMin, idDataGroup );
               double dAmount, dMinPAC;
               dAmount = DSTCommonFunctions::convertToDouble ( dstrAmount );
               dMinPAC = DSTCommonFunctions::convertToDouble ( dstrPACMin );
               pAMSLmtOverride->getFundOverride( bFundOverride, idDataGroup ); 
               if ( dAmount < dMinPAC ) {
                  // AMS %CODE% has a minimum PAC of %AMOUNT%
                  DString dstr; 
				  DSTCommonFunctions::DisplayFormat( dstrPACMin, ifds::OverrideDecimal );
                  addIDITagValue( dstr, I_("CODE"), _dstrAMSCode );          
                  addIDITagValue( dstr, I_("AMOUNT"), dstrPACMin );          
                  if ( pAMSLmtOverride->isError( idDataGroup ) ) {                              
                     //We do not want multiple errors, so return now.
                     ADDCONDITIONFROMFILEIDI( CND::AMS_LMT_ERR_MIN_PAC, dstr );
                     return GETCURRENTHIGHESTSEVERITY();
                  } else if ( pAMSLmtOverride->isWarning( idDataGroup ) ) {
                     //We do not want multiple errors, so return now.
                     ADDCONDITIONFROMFILEIDI( CND::AMS_LMT_WARN_MIN_PAC, dstr );
                     return GETCURRENTHIGHESTSEVERITY();
                  }
               }
            }
         }      
      }
      ++iter;      
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//*******************************************************************************
//*******************************************************************************
SEVERITY AmsLmtOverrideList::canPAC( const DString& dstrTaxJuris, const DString& dstrProvResid,
                                   const DString& dstrAccountType, const DString& dstrTaxType,
                                   const DString& dstrAcctDesign, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("canPAC") );
   BFObjIter iter(*this, idDataGroup, false , BFObjIter::ITERTYPE::NON_DELETED );
   AmsLmtOverride* pAMSLmtOverride = NULL;
   DString dstrRuleType;
   while ( !iter.end() ) {
      pAMSLmtOverride = dynamic_cast<AmsLmtOverride*>( iter.getObject() );      
      if ( pAMSLmtOverride ) {
         pAMSLmtOverride->getField( ifds::RuleType, dstrRuleType, idDataGroup, false );
         // find the corresponding record by matching the rule type with the input
         if ( dstrRuleType == STOP_PAC){	
            if ( isAMSRestrictionMet (pAMSLmtOverride, dstrTaxJuris, dstrProvResid, dstrAccountType,
                     dstrTaxType, dstrAcctDesign, idDataGroup) ) {
               // AMS %CODE% has PAC stop flag turned on
               DString dstrLmtLogical;
               pAMSLmtOverride->getLogicalField ( dstrLmtLogical, idDataGroup );         
               if ( dstrLmtLogical == YES ) {
                  DString dstr;                  
                  addIDITagValue( dstr, I_("CODE"), _dstrAMSCode );                      
                  if ( pAMSLmtOverride->isError( idDataGroup ) ) {         
                     ADDCONDITIONFROMFILEIDI( CND::AMS_LMT_ERR_STOP_PAC, dstr );
                     //We do not want multiple errors, so return now.
                     return GETCURRENTHIGHESTSEVERITY();
                  } else if ( pAMSLmtOverride->isWarning( idDataGroup ) ) {
                     ADDCONDITIONFROMFILEIDI( CND::AMS_LMT_WARN_STOP_PAC, dstr );
                     //We do not want multiple errors, so return now.
                     return GETCURRENTHIGHESTSEVERITY();
                  }
               }
            }
         }
      }
      ++iter;
   }
      
   return GETCURRENTHIGHESTSEVERITY();
}

//*******************************************************************************
//*******************************************************************************
SEVERITY AmsLmtOverrideList::canSWP( const DString& dstrTaxJuris, const DString& dstrProvResid,
                                   const DString& dstrAccountType, const DString& dstrTaxType,
                                   const DString& dstrAcctDesign, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("canSWP") );
   BFObjIter iter(*this, idDataGroup, false , BFObjIter::ITERTYPE::NON_DELETED );
   AmsLmtOverride* pAMSLmtOverride = NULL;
   DString dstrRuleType;
   while ( !iter.end() ) {
      pAMSLmtOverride = dynamic_cast<AmsLmtOverride*>( iter.getObject() );      
      if ( pAMSLmtOverride ) {
         pAMSLmtOverride->getField( ifds::RuleType, dstrRuleType, idDataGroup, false );
         // find the corresponding record by matching the rule type with the input
         if ( dstrRuleType == STOP_SWP){	
            if ( isAMSRestrictionMet (pAMSLmtOverride, dstrTaxJuris, dstrProvResid, dstrAccountType,
                     dstrTaxType, dstrAcctDesign, idDataGroup) ) {
               // AMS %CODE% has SWP stop flag turned on
               DString dstrLmtLogical;
               pAMSLmtOverride->getLogicalField ( dstrLmtLogical, idDataGroup );         
               if ( dstrLmtLogical == YES ) {
                  DString dstr;                  
                  addIDITagValue( dstr, I_("CODE"), _dstrAMSCode );                      
                  if ( pAMSLmtOverride->isError( idDataGroup ) ) {         
                     ADDCONDITIONFROMFILEIDI( CND::AMS_LMT_ERR_STOP_SWP, dstr );
                     //We do not want multiple errors, so return now.
                     return GETCURRENTHIGHESTSEVERITY();
                  } else if ( pAMSLmtOverride->isWarning( idDataGroup ) ) {
                     ADDCONDITIONFROMFILEIDI( CND::AMS_LMT_WARN_STOP_SWP, dstr );
                     //We do not want multiple errors, so return now.
                     return GETCURRENTHIGHESTSEVERITY();
                  }
               }
            }
         }
      }
      ++iter;
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//*******************************************************************************
//*******************************************************************************
SEVERITY AmsLmtOverrideList::minSWP( const DString& dstrTaxJuris, const DString& dstrProvResid,
                                   const DString& dstrAccountType, const DString& dstrTaxType,
                                   const DString& dstrAcctDesign, const DString& dstrSWPAmt,
                                   bool& bFundOverride, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("minSWP") );
   BFObjIter iter(*this, idDataGroup, false , BFObjIter::ITERTYPE::NON_DELETED );
   AmsLmtOverride* pAMSLmtOverride = NULL;
   DString dstrRuleType;
   while ( !iter.end() ) {
      pAMSLmtOverride = dynamic_cast<AmsLmtOverride*>( iter.getObject() );      
      if ( pAMSLmtOverride ) {
         pAMSLmtOverride->getField( ifds::RuleType, dstrRuleType, idDataGroup, false );
         // find the corresponding record by matching the rule type with the input
         if ( dstrRuleType == MIN_SWP){	            
            if ( isAMSRestrictionMet (pAMSLmtOverride, dstrTaxJuris, dstrProvResid, dstrAccountType,
                     dstrTaxType, dstrAcctDesign, idDataGroup) ) {
               // AMS %CODE% has a minimum SWP of %AMOUNT%
               DString dstrMinSWPBal;
               pAMSLmtOverride->getDecimalField ( dstrMinSWPBal, idDataGroup );
               double dSWPAmt, dMinSWPBal;
               dSWPAmt = DSTCommonFunctions::convertToDouble ( dstrSWPAmt );
               dMinSWPBal = DSTCommonFunctions::convertToDouble ( dstrMinSWPBal );
               pAMSLmtOverride->getFundOverride( bFundOverride, idDataGroup ); 
               if ( dSWPAmt < dMinSWPBal ) {
                  DString dstr;          
				  DSTCommonFunctions::DisplayFormat( dstrMinSWPBal, ifds::OverrideDecimal );
                  addIDITagValue( dstr, I_("CODE"), _dstrAMSCode );          
                  addIDITagValue( dstr, I_("AMOUNT"), dstrMinSWPBal );          
                  if ( pAMSLmtOverride->isError( idDataGroup ) ) {         
                     ADDCONDITIONFROMFILEIDI( CND::AMS_LMT_ERR_MIN_SWP, dstr );
                     //We do not want multiple errors, so return now.
                     return GETCURRENTHIGHESTSEVERITY();
                  } else if ( pAMSLmtOverride->isWarning( idDataGroup) ) {
                     ADDCONDITIONFROMFILEIDI( CND::AMS_LMT_WARN_MIN_SWP, dstr );
                     //We do not want multiple errors, so return now.
                     return GETCURRENTHIGHESTSEVERITY();
                  }
               }
            }
         }
      }
      ++iter;
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//*******************************************************************************
//*******************************************************************************
SEVERITY AmsLmtOverrideList::canATIn( const DString& dstrTaxJuris, const DString& dstrProvResid,
                                   const DString& dstrAccountType, const DString& dstrTaxType,
                                   const DString& dstrAcctDesign, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("canATIn") );
   BFObjIter iter(*this, idDataGroup, false , BFObjIter::ITERTYPE::NON_DELETED );
   AmsLmtOverride* pAMSLmtOverride = NULL;
   DString dstrRuleType;
   while ( !iter.end() ) {
      pAMSLmtOverride = dynamic_cast<AmsLmtOverride*>( iter.getObject() );      
      if ( pAMSLmtOverride ) {
         pAMSLmtOverride->getField( ifds::RuleType, dstrRuleType, idDataGroup, false );
         // find the corresponding record by matching the rule type with the input
         if ( dstrRuleType == STOP_AT_TRANSFER_IN){	            
            if ( isAMSRestrictionMet (pAMSLmtOverride, dstrTaxJuris, dstrProvResid, dstrAccountType,
                     dstrTaxType, dstrAcctDesign, idDataGroup) ) {
               // AMS %CODE% has Auto Transfer In stop flag turned on
               DString dstrLmtLogical;
               pAMSLmtOverride->getLogicalField ( dstrLmtLogical, idDataGroup );         
               if ( dstrLmtLogical == YES ) {
                  DString dstr;                  
                  addIDITagValue( dstr, I_("CODE"), _dstrAMSCode );                      
                  if ( pAMSLmtOverride->isError( idDataGroup ) ) {         
                     ADDCONDITIONFROMFILEIDI( CND::AMS_LMT_ERR_STOP_AT_IN, dstr );
                     //We do not want multiple errors, so return now.
                     return GETCURRENTHIGHESTSEVERITY();
                  } else if ( pAMSLmtOverride->isWarning( idDataGroup ) ) {
                     ADDCONDITIONFROMFILEIDI( CND::AMS_LMT_WARN_STOP_AT_IN, dstr );
                     //We do not want multiple errors, so return now.
                     return GETCURRENTHIGHESTSEVERITY();
                  }
               }
            }
         }
      }
      ++iter;
   }
   return GETCURRENTHIGHESTSEVERITY();
}


//*******************************************************************************
//*******************************************************************************
SEVERITY AmsLmtOverrideList::canATOut( const DString& dstrTaxJuris, const DString& dstrProvResid,
                                   const DString& dstrAccountType, const DString& dstrTaxType,
                                   const DString& dstrAcctDesign, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("canATOut") );

   BFObjIter iter(*this, idDataGroup, false , BFObjIter::ITERTYPE::NON_DELETED );
   AmsLmtOverride* pAMSLmtOverride = NULL;
   DString dstrRuleType;
   while ( !iter.end() ) {
      pAMSLmtOverride = dynamic_cast<AmsLmtOverride*>( iter.getObject() );      
      if ( pAMSLmtOverride ) {
         pAMSLmtOverride->getField( ifds::RuleType, dstrRuleType, idDataGroup, false );
         // find the corresponding record by matching the rule type with the input
         if ( dstrRuleType == STOP_AT_TRANSFER_OUT){	            
            if ( isAMSRestrictionMet (pAMSLmtOverride, dstrTaxJuris, dstrProvResid, dstrAccountType,
                     dstrTaxType, dstrAcctDesign, idDataGroup) ) {
               // AMS %CODE% has Auto Transfer Out stop flag turned on
               DString dstrLmtLogical;
               pAMSLmtOverride->getLogicalField ( dstrLmtLogical, idDataGroup );         
               if ( dstrLmtLogical == YES ) {
                  DString dstr;                  
                  addIDITagValue( dstr, I_("CODE"), _dstrAMSCode );                      
                  if ( pAMSLmtOverride->isError( idDataGroup ) ) {         
                     ADDCONDITIONFROMFILEIDI( CND::AMS_LMT_ERR_STOP_AT_OUT, dstr );
                     //We do not want multiple errors, so return now.
                     return GETCURRENTHIGHESTSEVERITY();
                  } else if ( pAMSLmtOverride->isWarning( idDataGroup ) ) {
                     ADDCONDITIONFROMFILEIDI( CND::AMS_LMT_WARN_STOP_AT_OUT, dstr );
                     //We do not want multiple errors, so return now.
                     return GETCURRENTHIGHESTSEVERITY();
                  }
               }
            }
         }
      }
      ++iter;
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//*******************************************************************************
//*******************************************************************************
SEVERITY AmsLmtOverrideList::canTransferIn( const DString& dstrTaxJuris, const DString& dstrProvResid,
                                   const DString& dstrAccountType, const DString& dstrTaxType,
                                   const DString& dstrAcctDesign, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("canTransferIn") );

   BFObjIter iter(*this, idDataGroup, false , BFObjIter::ITERTYPE::NON_DELETED );
   AmsLmtOverride* pAMSLmtOverride = NULL;
   DString dstrRuleType;
   while ( !iter.end() ) {
      pAMSLmtOverride = dynamic_cast<AmsLmtOverride*>( iter.getObject() );      
      if ( pAMSLmtOverride ) {
         pAMSLmtOverride->getField( ifds::RuleType, dstrRuleType, idDataGroup, false );
         // find the corresponding record by matching the rule type with the input
         if ( dstrRuleType == STOP_TRANSFER_IN){	            
            if ( isAMSRestrictionMet (pAMSLmtOverride, dstrTaxJuris, dstrProvResid, dstrAccountType,
                     dstrTaxType, dstrAcctDesign, idDataGroup) ) {
               // AMS %CODE% has transfer in stop flag turned on
               DString dstrLmtLogical;
               pAMSLmtOverride->getLogicalField ( dstrLmtLogical, idDataGroup );         
               if ( dstrLmtLogical == YES ) {
                  DString dstr;                  
                  addIDITagValue( dstr, I_("CODE"), _dstrAMSCode );                      
                  if ( pAMSLmtOverride->isError( idDataGroup ) ) {         
                     ADDCONDITIONFROMFILEIDI( CND::AMS_LMT_ERR_STOP_TRANSFER_IN, dstr );
                     //We do not want multiple errors, so return now.
                     return GETCURRENTHIGHESTSEVERITY();
                  } else if ( pAMSLmtOverride->isWarning( idDataGroup ) ) {
                     ADDCONDITIONFROMFILEIDI( CND::AMS_LMT_WARN_STOP_TRANSFER_IN, dstr );
                     //We do not want multiple errors, so return now.
                     return GETCURRENTHIGHESTSEVERITY();
                  }
               }
            }
         }
      }
      ++iter;
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//*******************************************************************************
//*******************************************************************************
SEVERITY AmsLmtOverrideList::canTransferOut( const DString& dstrTaxJuris, const DString& dstrProvResid,
                                   const DString& dstrAccountType, const DString& dstrTaxType,
                                   const DString& dstrAcctDesign, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("canTransferOut") );
   BFObjIter iter(*this, idDataGroup, false , BFObjIter::ITERTYPE::NON_DELETED );
   AmsLmtOverride* pAMSLmtOverride = NULL;
   DString dstrRuleType;
   while ( !iter.end() ) {
      pAMSLmtOverride = dynamic_cast<AmsLmtOverride*>( iter.getObject() );      
      if ( pAMSLmtOverride ) {
         pAMSLmtOverride->getField( ifds::RuleType, dstrRuleType, idDataGroup, false );
         // find the corresponding record by matching the rule type with the input
         if ( dstrRuleType == STOP_TRANSFER_OUT){	            
            if ( isAMSRestrictionMet (pAMSLmtOverride, dstrTaxJuris, dstrProvResid, dstrAccountType,
                     dstrTaxType, dstrAcctDesign, idDataGroup) ) {
               // AMS %CODE% has transfer out stop flag turned on
               DString dstrLmtLogical;
               pAMSLmtOverride->getLogicalField ( dstrLmtLogical, idDataGroup );         
               if ( dstrLmtLogical == YES ) {
                  DString dstr;                  
                  addIDITagValue( dstr, I_("CODE"), _dstrAMSCode );                      
                  if ( pAMSLmtOverride->isError( idDataGroup ) ) {         
                     ADDCONDITIONFROMFILEIDI( CND::AMS_LMT_ERR_STOP_TRANSFER_OUT, dstr );
                     //We do not want multiple errors, so return now.
                     return GETCURRENTHIGHESTSEVERITY();
                  } else if ( pAMSLmtOverride->isWarning( idDataGroup ) ) {
                     ADDCONDITIONFROMFILEIDI( CND::AMS_LMT_WARN_STOP_TRANSFER_OUT, dstr );
                     //We do not want multiple errors, so return now.
                     return GETCURRENTHIGHESTSEVERITY();
                  }
               }
            }
         }
      }
      ++iter;
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY AmsLmtOverrideList::getMore()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getMore" ) );

   if( doMoreRecordsExist() )
   {
      const DSTCSecurity* security = dynamic_cast<const DSTCSecurity *> ( getSecurity() );
      ReceiveData(DSTC_REQUEST::AMS_LMT_OVERRIDE_LIST, _requestData, ifds::DSTC0262_VW, DSTCRequestor(getSecurity(), false) );

   }

   return(GETCURRENTHIGHESTSEVERITY());

}

//**************************************************************************************
SEVERITY AmsLmtOverrideList::doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup )
{ 
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );
	
   return(GETCURRENTHIGHESTSEVERITY());
}

//********************************************************************************
// The method assume that the list has already been pull down from data base
// uErrCode:  0x0000: no error
//            0x0001: Account Type does not match
//            0x0002: Tax Type does not match
//            0x0004: Account Designation does not match
//            0x0008: Tax Jurisdiction does not match
//            0x0010: Province of Resident does not match

bool AmsLmtOverrideList:: canAMSCodeSetUpForAccount( const DString& dstrAccountNum,
										const BFDataGroupId& idDataGroup,unsigned int& uErrCode )
{
	bool bRet = false;
	uErrCode = 0x0000;
	DString dstrAcctType,dstrTaxType, dstrAcctDes,dstrTaxJuris,dstrResProv,dstrShrNum;
   MFAccount *pMFAccount =  NULL;
	getWorkSession().getMFAccount( idDataGroup,dstrAccountNum,pMFAccount );
   if( pMFAccount )
	{
		pMFAccount->getField(ifds::AcctType,dstrAcctType,idDataGroup,false );
		dstrAcctType.strip().upperCase();
		pMFAccount->getField(ifds::TaxType,dstrTaxType,idDataGroup,false );
		dstrTaxType.strip().upperCase();
		pMFAccount->getField(ifds::AcctDesignation,dstrAcctDes,idDataGroup,false );
		dstrAcctDes.strip().upperCase();
		pMFAccount->getField(ifds::ShrNum,dstrShrNum,idDataGroup,false );
		dstrShrNum.strip();
		Shareholder* pShaholder = NULL;
		getWorkSession().getShareholder( idDataGroup, dstrShrNum,pShaholder );
		if( pShaholder )
		{
			pShaholder->getField(ifds::TaxJurisCode,dstrTaxJuris,idDataGroup,false );
			dstrTaxJuris.strip().upperCase();
			pShaholder->getField(ifds::ResProvCode,dstrResProv,idDataGroup,false );
			dstrResProv.strip().upperCase();			
		}
	}
	BFObjIter iter(*this, idDataGroup, false , BFObjIter::ITERTYPE::NON_DELETED );
   AmsLmtOverride* pAMSLmtOverride = NULL;
	while( !iter.end() )
	{
		pAMSLmtOverride = dynamic_cast<AmsLmtOverride* >( iter.getObject() );
		if( pAMSLmtOverride )
		{
			if( !pAMSLmtOverride->isAcctTypeInList ( dstrAcctType, idDataGroup ) )
			{
				uErrCode |= 0x0001;
			}
			if( !pAMSLmtOverride->isTaxTypeInList ( dstrTaxType, idDataGroup ) )
			{
				uErrCode |= 0x0002;			
			}
			if( !pAMSLmtOverride->isAcctDesignationInList ( dstrAcctDes, idDataGroup ) )
			{
				uErrCode |= 0x0004;			
			}
			if( !pAMSLmtOverride->isTaxJurisInList ( dstrTaxJuris, idDataGroup ) )
			{
				uErrCode |= 0x0008;			
			}
			if( !pAMSLmtOverride->isProvResInList ( dstrResProv, idDataGroup ) )
			{
				uErrCode |= 0x0010;			
			}
		}

	  ++iter;
	}
	if( uErrCode == 0x0000 ) bRet = true;

   return bRet;
}

//**************************************************************************************
SEVERITY AmsLmtOverrideList::canRebalanceAccount( const DString &dstrAccountNum, 
																  const BFDataGroupId &idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION,
                          CLASSNAME,
                          I_( "canRebalanceAccount( const DString &, BFDataGroupId & )" ) );

	double dblOverrideDecimal = 0, dblAccountBalance = 0;
	AmsLmtOverride *pAMSLmtOverride = NULL;
	DString dstrEffectiveDate;		
	getWorkSession().getDateInHostFormat( dstrEffectiveDate, 
		                                   DSTCWorkSession::DATE_TYPE::CURRENT_BUSINESS_DAY, 
													  idDataGroup );   

	// Get AMS rule currency
	DString dstrAMSCurrency, dstrCommonCurrency;
	getWorkSession().getOption( ifds::CommonCurrency, dstrCommonCurrency, idDataGroup, false); 
	if ( I_( "N" ) == dstrCommonCurrency.strip().upperCase() )
	{
		getWorkSession().getOption( ifds::SysCurrency, dstrAMSCurrency, idDataGroup, false); 
	}
	else
	{
		// AMSCurrency will be given by AMS global currency						
		AMSMstrList *pAMSMstrList = NULL;
		if ( getWorkSession().getAMSMstrList( pAMSMstrList, 
			                                   _dstrAMSType, 
														  _dstrAMSCode, 
														  dstrEffectiveDate, 
														  idDataGroup, 
														  true ) <= WARNING &&
			  NULL != pAMSMstrList )
		{
			pAMSMstrList->getFieldByAMSCode( _dstrAMSType, 
				                              _dstrAMSCode, 
														dstrEffectiveDate, 
														ifds::Currency, 
														dstrAMSCurrency, 
														idDataGroup,
														false );				
		}
	}

   MFAccount *pMFAccount =  NULL;
	if ( getWorkSession().getMFAccount( idDataGroup, dstrAccountNum, pMFAccount ) <= WARNING &&
		  NULL != pMFAccount )
	{
		DString dstrAccountType, dstrTaxType, dstrAcctDes, dstrTaxJuris, dstrResProv;
		pMFAccount->getField( ifds::AcctType,        dstrAccountType, idDataGroup, false );		
		pMFAccount->getField( ifds::TaxType,         dstrTaxType,     idDataGroup, false );		
		pMFAccount->getField( ifds::AcctDesignation, dstrAcctDes,     idDataGroup, false );		

		DString dstrShrNum;
		pMFAccount->getField( ifds::ShrNum, dstrShrNum, idDataGroup, false );
		dstrShrNum.strip();
		Shareholder* pShaholder = NULL;
		if ( getWorkSession().getShareholder( idDataGroup, dstrShrNum, pShaholder ) <= WARNING &&
		     NULL != pShaholder )
		{
			pShaholder->getField( ifds::TaxJurisCode, dstrTaxJuris, idDataGroup, false );			
			pShaholder->getField( ifds::ResProvCode,  dstrResProv,  idDataGroup, false );
		}			

		dstrAccountType.strip().upperCase();
		dstrTaxType.strip().upperCase();
		dstrAcctDes.strip().upperCase();
		dstrTaxJuris.strip().upperCase();
		dstrResProv.strip().upperCase();

		BFObjIter iter( *this, idDataGroup, false , BFObjIter::ITERTYPE::NON_DELETED );
		iter.begin();
		while( !iter.end() )
		{
			pAMSLmtOverride = dynamic_cast<AmsLmtOverride* >( iter.getObject() );			
			if( NULL != pAMSLmtOverride )
			{
				DString dstrRuleType;
				pAMSLmtOverride->getField( ifds::RuleType, dstrRuleType, idDataGroup );				
				
				if( I_( "14" ) == dstrRuleType.strip() && 
					 pAMSLmtOverride->isAcctTypeInList ( dstrAccountType, idDataGroup ) &&
				    pAMSLmtOverride->isTaxTypeInList ( dstrTaxType, idDataGroup ) &&
				    pAMSLmtOverride->isAcctDesignationInList ( dstrAcctDes, idDataGroup ) &&
				    pAMSLmtOverride->isTaxJurisInList ( dstrTaxJuris, idDataGroup ) &&
				    pAMSLmtOverride->isProvResInList ( dstrResProv, idDataGroup ) )
				{
					DString dstrOverrideDecimal;
					pAMSLmtOverride->getField( ifds::OverrideDecimal, dstrOverrideDecimal, idDataGroup );
					dblOverrideDecimal = DSTCommonFunctions::convertToDouble ( dstrOverrideDecimal );
							
					break;
				}
			}

		  ++iter;
		}
		
		MFAccountHoldingList *pMFAccountHoldingList = NULL;
		if ( pMFAccount->getAccountHoldingList( pMFAccountHoldingList, 
			                                     idDataGroup, 
															 true ) <= WARNING &&  //inquire the database based on 
															                       // CurrBusDate   
			  NULL != pMFAccountHoldingList )
		{			
			DString dstrAccountBalance;
			pMFAccountHoldingList->getField( ifds::AccountBalance, dstrAccountBalance, idDataGroup );

			dblAccountBalance = DSTCommonFunctions::convertToDouble( dstrAccountBalance );
		}

		// If the Account Currency and the AMS rule currency are not the same, then
		// get the exchange rate and re-calculate the account balance in AMS currency
		DString dstrAccountCurrency;
		pMFAccount->getField( ifds::Currency, dstrAccountCurrency, idDataGroup );		
		if ( dstrAMSCurrency.strip().upperCase() != dstrAccountCurrency.strip().upperCase() )
		{
			dblAccountBalance = dblAccountBalance * getWorkSession().getExchRate( dstrAMSCurrency,   // to currency
				                                                                   dstrEffectiveDate, 
																										 idDataGroup );
		}
	}

	if ( dblOverrideDecimal > dblAccountBalance )
	{		
		if ( pAMSLmtOverride->isError( idDataGroup ) ) 
		{
			// Limitation rule, AMS market value rebalancing minimum is not met					
			ADDCONDITIONFROMFILE( CND::ERR_AMS_MKT_REBALANCING_LIMITATION_RULE_NOT_MET );
      } 
		else if ( pAMSLmtOverride->isWarning( idDataGroup ) ) 
		{                    
			// Limitation rule, AMS market value rebalancing minimum is not met						
			ADDCONDITIONFROMFILE( CND::WARN_AMS_MKT_REBALANCING_LIMITATION_RULE_NOT_MET );
      }
	}

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AmsLmtOverrideList.cpp-arc  $
// 
//    Rev 1.15   Nov 25 2008 11:13:48   jankovii
// PET 142196 FN01 Federal Restricted LIF and LIRA.
// 
//    Rev 1.14   Oct 08 2007 12:15:56   smithdav
// IN  1005517,1020252 - LRSP logic
// 
//    Rev 1.13   Jul 11 2005 17:22:22   Fengyong
// PET1250FN02 - European numeric enahncement - conditions
// decimal format 
// 
//    Rev 1.12   Apr 09 2004 10:04:12   VADEANUM
// PET1005 Fn11 - AMS Gaps.
// 
//    Rev 1.11   Feb 20 2004 13:54:46   FENGYONG
// PTS 10027039, AMSLMTOverride stop SWP and PAC
// 
//    Rev 1.10   Aug 14 2003 13:03:18   HSUCHIN
// Change the fund override from pass by copy to pass by reference.
// 
//    Rev 1.9   Aug 13 2003 10:21:24   linmay
// added TaxType .. fields
// 
//    Rev 1.8   Aug 12 2003 10:21:26   HSUCHIN
// change error message to use private variable _dstrAMSCode to display AMS Code
// 
//    Rev 1.7   Aug 11 2003 11:53:08   YINGBAOL
// fix typing error
// 
//    Rev 1.6   Aug 11 2003 09:49:56   YINGBAOL
// add canAMSCodeSetUpForAccount method
// 
//    Rev 1.5   Aug 11 2003 09:40:14   linmay
// fix bug
// 
//    Rev 1.4   Aug 05 2003 11:27:48   linmay
// fix bug
// 
//    Rev 1.3   Jul 30 2003 14:15:44   linmay
// change view to 262
// 
//    Rev 1.2   Jul 25 2003 17:05:34   HSUCHIN
// added support for limit override checks such as stop purchase, stop PAC etc. etc.
// 
//    Rev 1.1   Jul 23 2003 11:08:42   linmay
// check in for chin
// 
//    Rev 1.0   Jul 23 2003 09:22:22   linmay
// Initial Revision
// 
*/