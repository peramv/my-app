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
//    Copyright 2003 by DST Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : FromFundAlloc.cpp
// ^AUTHOR : Yingbao Li
// ^DATE   : May 27,2003
//
// ^CLASS    : FromFundAlloc
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION : RRIF fund allocation
//
//******************************************************************************
#include "stdafx.h"
#include "FromFundAlloc.hpp"

#include "abstractalloclist.hpp"
#include "funddetail.hpp"
#include "mfaccount.hpp"
#include "RRIF_LIF_LRIF_Info.hpp"
#include "ToFundAllocList.hpp"
#include <ifastdataimpl\dse_dstc0068_vw.hpp>

#include <conditions\iFastLayer\iFast\ifastcbo\IFast_IFast_ifastcbo_err_parent_fund_is_not_allowed.h>
#include <conditions\iFastLayer\iFast\ifastcbo\IFast_IFast_ifastcbo_warn_parent_fund_is_not_allowed.h>

namespace
{
   const I_CHAR * const CLASSNAME              = I_( "FromFundAlloc" );
   const I_CHAR * const NO                     = I_( "N" );
   const I_CHAR * const YES                    = I_( "Y" );
   const I_CHAR * const REDEMPTION_CODE        = I_( "PW" );      // trade trans type Redemption
}

namespace CND
{  // Conditions used
   extern const long ERR_INVALID_FUND_CLASS_CODES;
   extern const long ERR_AMOUNT_EXCEED_MAX_LIMIT;
   extern const long ERR_RIF_NON_FRACTIONAL;               
   extern const long ERR_RIF_OUT_OF_LIMITS_ALLOC_AMOUNT;   
   extern const long ERR_RIF_ZERO_ALLOC_AMOUNT;            
}

namespace ifds
{  
   extern CLASS_IMPORT const BFTextFieldId FundCode;
   extern CLASS_IMPORT const BFTextFieldId ClassCode;
   extern CLASS_IMPORT const BFTextFieldId FundClass;
   extern CLASS_IMPORT const BFTextFieldId ToFundNumber;
   extern CLASS_IMPORT const BFTextFieldId AllocAmtType;
   extern CLASS_IMPORT const BFTextFieldId TransType;
   extern CLASS_IMPORT const BFDecimalFieldId AllocPercentage;
   extern CLASS_IMPORT const BFDateFieldId EffectiveDate;
   extern CLASS_IMPORT const BFDateFieldId CurrBusDate;	
   extern CLASS_IMPORT const BFDecimalFieldId Amount;
   extern CLASS_IMPORT const BFTextFieldId RRIFTransType;
   extern CLASS_IMPORT const BFTextFieldId Currency;
   extern CLASS_IMPORT const BFTextFieldId GoodBad;
}

namespace IFASTERR
{
   extern CLASS_IMPORT I_CHAR * const PARENT_FUND_IS_NOT_ALLOWED;
}

//******************************************************************************
const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//		Field DD Id,				State Flags,					      Group Flags
   { ifds::FundClass, BFCBO::IMMEDIATE_VALIDATION, 0 }
};

/*const BFCBO::CLASS_OBJECT_INFO classObjectInfo[] = {
   //  Object Label,                  State Flags,      Group Flags

};

static const int NUM_OBJECTS = sizeof( classObjectInfo ) / sizeof( BFCBO::CLASS_OBJECT_INFO );*/

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//******************************************************************************
FromFundAlloc::FromFundAlloc( BFAbstractCBO &parent ) 
: FundAlloc( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   registerMemberData( NUM_FIELDS,  (const CLASS_FIELD_INFO *)&classFieldInfo,
                       /*NUM_OBJECTS*/NULL, /*(const CLASS_OBJECT_INFO *)&classObjectInfo*/NULL);

   addCrossEdit(ifds::FundClass, ifds::FundCode);
   addCrossEdit(ifds::FundClass, ifds::ClassCode);
}

//******************************************************************************
FromFundAlloc::~FromFundAlloc( void )
{
   TRACE_DESTRUCTOR( CLASSNAME );
}
//******************************************************************************

SEVERITY FromFundAlloc::initNew( const BFDataGroupId& idDataGroup,
                                 const DString& dstrTrack ,
                                 const DString& dstrPageName )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initNew" ) );

   setObjectNew();

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

void FromFundAlloc::doInitWithDefaultValues( const BFDataGroupId& idDataGroup )
{
    FundAlloc::doInitWithDefaultValues( idDataGroup );
	 DString strStatus;
	 getTopLevelCBO()->getField(ifds::GoodBad,strStatus,idDataGroup,false); 
	 setAllocFieldsReadOnly(idDataGroup,strStatus.strip()!=YES);
}

//******************************************************************************

SEVERITY FromFundAlloc::initExisting(const BFData &data)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initExisting" ) );

   attachDataObject( const_cast< BFData & >( data ), false, true ); 
   setFundNumber(BF::HOST);//because ToFundNumber doesn't come from the host

   loadSubstitutions(BF::HOST);
   setAllocFields(BF::HOST);

   DString strStatus,dstrEffectiveDate,dstrCurrentDate;
   getTopLevelCBO()->getField(ifds::GoodBad,strStatus,BF::HOST,false);
	getField(ifds::EffectiveDate,dstrEffectiveDate,BF::HOST,false);
	getWorkSession().getOption( ifds::CurrBusDate, dstrCurrentDate, BF::HOST, false );

	bool bReadObly = DSTCommonFunctions::compareDateYear(dstrEffectiveDate,dstrCurrentDate ) == 0
							|| strStatus.strip()!=YES;

   setAllocFieldsReadOnly(BF::HOST, bReadObly );   
	

	
	
	clearUpdatedFlags( BF::HOST );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY FromFundAlloc::doApplyRelatedChanges(const BFFieldId& idField, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges"));
   
   if (FundAlloc::doApplyRelatedChanges(idField, idDataGroup) <= WARNING)
   {
       RRIF_LIF_LRIF_Info *pRRIFInfo = NULL;
       ToFundAllocList *pToFundAllocList = NULL;

       pRRIFInfo = dynamic_cast<RRIF_LIF_LRIF_Info*>(getParent()->getParent());

       if (pRRIFInfo && isFieldUpdated(idField, idDataGroup))
       {
           pRRIFInfo->getToFundAllocList(pToFundAllocList, idDataGroup, false);

           if (pToFundAllocList)
               pToFundAllocList->setAllAllocsFndClsValidFlag(false, idDataGroup);
       }
   }
   
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY FromFundAlloc::doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateField" ) );
   if( FundAlloc::doValidateField( idField, strValue, idDataGroup ) > WARNING )
      return(GETCURRENTHIGHESTSEVERITY());

   if( idField == ifds::FundCode )
      validateFundCodeCash( strValue, idDataGroup,false );
   else if( idField == ifds::FundClass )
      validateFundClass ( idDataGroup );
   else if( idField == ifds::AllocAmount )
      validateAmount( strValue, idDataGroup );
   else if( idField == ifds::AllocPercentage )
      validateFractional(strValue, idDataGroup);
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY FromFundAlloc::validateFundClass( const BFDataGroupId& idDataGroup ) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateFundClass" ) );
   DString dstrClassCode, dstrFundCode, dstrTransNum;
   getField(ifds::FundCode, dstrFundCode, idDataGroup, false);
   getField(ifds::ClassCode, dstrClassCode, idDataGroup, false);

   DString dstrEffectiveDate;
   DString AMSCode_4;
   getField( ifds::EffectiveDate, dstrEffectiveDate, idDataGroup, false );
   dstrEffectiveDate.strip();

   DString dstrTransTypeParam = REDEMPTION_CODE;

   MFAccount *pMFAccount = NULL;

   if( getMFAccount(pMFAccount, idDataGroup)<=WARNING && pMFAccount )
   {
      pMFAccount->canTradeFundClass (dstrFundCode, dstrClassCode, dstrTransTypeParam, dstrEffectiveDate, idDataGroup);
      pMFAccount->AMSFundAllow ( dstrFundCode, dstrClassCode, idDataGroup );

      BFCBO *pGrandParent = getParent()->getParent();
      if ( pMFAccount->isAMSAccount ( idDataGroup ) && 
         getWorkSession().isMasterActWithOneChild(idDataGroup) &&
         dynamic_cast<RRIF_LIF_LRIF_Info*>(pGrandParent))
      {
         FundDetail *pFundDetail = nullptr;

         if(getFundDetail( dstrFundCode, dstrClassCode, pFundDetail ) <= WARNING &&
            pFundDetail && 
            pFundDetail->isAMSParentFund(idDataGroup))
         {
            CND::CIFast_IFast_ifastcbo_warn_parent_fund_is_not_allowed warnCond;
            CND::CIFast_IFast_ifastcbo_err_parent_fund_is_not_allowed errCond;

            MFCanBFCbo::getErrMsg (IFASTERR::PARENT_FUND_IS_NOT_ALLOWED,
                                    errCond,
                                    warnCond,
                                    idDataGroup);
         }
      }
   }


   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY FromFundAlloc::initDefault(BFAbstractCBO* pDefaultAlloc, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initDefault" ) )

   FundAlloc::initDefault(pDefaultAlloc, idDataGroup);

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
BFData * FromFundAlloc::getDataForModelOffer()
{
  return(new BFData(ifds::DSTC0068_VWRepeat_Record));
}

//******************************************************************************
SEVERITY FromFundAlloc::getSplitCommissionList ( SplitCommissionList *&pSplitCommissionList, const BFDataGroupId& idDataGroup, 
                                                 bool bCreate /*= true*/,
                                                 bool bGetDefault /*= false*/)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getSplitCommissionList" ) );

   pSplitCommissionList=NULL;//no split commissions for rrif allocations

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY FromFundAlloc::loadSubstitutions( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "loadSubstitutions" ) );

   if( DSTCommonFunctions::getMarket() == MARKET_IDS::CANADA )
      setFieldSubstituteValues( ifds::TransType, idDataGroup, ifds::RRIFTransType );

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************
SEVERITY FromFundAlloc::doPreSetField( const BFFieldId& idField, DString & strValue, const BFDataGroupId& idDataGroup, bool bFormatted )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doPreSetField" ) );
   if(   idField == ifds::FundCode ||
         idField == ifds::ClassCode ||
         idField == ifds::ToFundNumber)
   {
      strValue.strip().upperCase();
   
   }
   
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/FromFundAlloc.cpp-arc  $
// 
//    Rev 1.4   Jan 14 2009 17:16:22   wongsakw
// IN1550993 Invalid warning message when fund entered in lower case for LIF allocation
// 
//    Rev 1.3   Nov 14 2004 14:41:12   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.2   Nov 06 2004 00:40:56   popescu
// PET 1117/06, synch changes
// 
//    Rev 1.1   Jul 07 2003 11:36:48   YINGBAOL
// cosmetic changes
// 
//    Rev 1.0   Jun 09 2003 11:03:04   YINGBAOL
// Initial revision.
// 



 * 
 * 
 */