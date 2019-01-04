//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by IFDS,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2002 by DST Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : ToFundAlloc.cpp
// ^AUTHOR : Yingbao Li
// ^DATE   : 08/06/03
//
// ^CLASS    : ToFundAlloc
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION : RRIF fund allocation
//
//******************************************************************************
#include "stdafx.h"
#include "ToFundAlloc.hpp"
#include "mfaccount.hpp"
#include "abstractalloclist.hpp"
#include "RRIF_LIF_LRIF_Info.hpp"
#include "FromFundAllocList.hpp"
#include <ifastdataimpl\dse_dstc0068_vw.hpp>

namespace
{
   const I_CHAR * const CLASSNAME              = I_( "ToFundAlloc" );
   const I_CHAR * const NO                     = I_( "N" );
   const I_CHAR * const YES                    = I_( "Y" );
   const I_CHAR * const EX_FER_IN_CODE             = I_( "XFIN" );   // trade trans type Exchange In 

}

namespace CND
{  // Conditions used                  
   //extern const long ERR_RIF_ZERO_ALLOC_AMOUNT;            


}

namespace ifds
{  
   extern CLASS_IMPORT const BFNumericFieldId AccountNum;
   extern CLASS_IMPORT const BFTextFieldId FundCode;
   extern CLASS_IMPORT const BFTextFieldId ClassCode;
   extern CLASS_IMPORT const BFTextFieldId FundClass;
   extern CLASS_IMPORT const BFTextFieldId ToFundNumber;
   extern CLASS_IMPORT const BFTextFieldId TransType;
   extern CLASS_IMPORT const BFDecimalFieldId AllocPercentage;
   extern CLASS_IMPORT const BFDateFieldId EffectiveDate;
   extern CLASS_IMPORT const BFDateFieldId CurrBusDate;
   extern CLASS_IMPORT const BFTextFieldId RRIFTransType;
   extern CLASS_IMPORT const BFTextFieldId Currency;
   extern CLASS_IMPORT const BFTextFieldId GoodBad;
   extern CLASS_IMPORT const BFNumericFieldId AccountTo;
   extern CLASS_IMPORT const BFTextFieldId ToSoftCapCheck;
}
//******************************************************************************

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//		Field DD Id,				State Flags,					      Group Flags
   { ifds::FundClass, BFCBO::IMMEDIATE_VALIDATION, 0 },
   { ifds::ToSoftCapCheck, BFCBO::IMMEDIATE_VALIDATION, 0 }
};

/*const BFCBO::CLASS_OBJECT_INFO classObjectInfo[] = {
   //  Object Label,                  State Flags,      Group Flags

};

static const int NUM_OBJECTS = sizeof( classObjectInfo ) / sizeof( BFCBO::CLASS_OBJECT_INFO );*/

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//******************************************************************************
ToFundAlloc::ToFundAlloc( BFAbstractCBO &parent ) 
: FundAlloc( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   registerMemberData( NUM_FIELDS,  (const CLASS_FIELD_INFO *)&classFieldInfo,
                       /*NUM_OBJECTS*/NULL, /*(const CLASS_OBJECT_INFO *)&classObjectInfo*/NULL);

   addCrossEdit(ifds::FundClass, ifds::FundCode);
   addCrossEdit(ifds::FundClass, ifds::ClassCode);

   addCrossEdit(ifds::ToSoftCapCheck, ifds::FundCode);
   addCrossEdit(ifds::ToSoftCapCheck, ifds::ClassCode);
}

//******************************************************************************
ToFundAlloc::~ToFundAlloc( void )
{
   TRACE_DESTRUCTOR( CLASSNAME );
}
//******************************************************************************

SEVERITY ToFundAlloc::initNew( const BFDataGroupId& idDataGroup,
                                 const DString& dstrTrack ,
                                 const DString& dstrPageName )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initNew" ) );

   setObjectNew();

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

void ToFundAlloc::doInitWithDefaultValues( const BFDataGroupId& idDataGroup )
{
   FundAlloc::doInitWithDefaultValues( idDataGroup );
   DString strStatus;
   getTopLevelCBO()->getField(ifds::GoodBad,strStatus,idDataGroup,false);
   setAllocFieldsReadOnly(idDataGroup,strStatus.strip()!=YES);
}

//******************************************************************************

SEVERITY ToFundAlloc::initExisting(const BFData &data)
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
SEVERITY ToFundAlloc::doApplyRelatedChanges(const BFFieldId& idField, const BFDataGroupId& idDataGroup)
{
    MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doApplyRelatedChanges"));

    if (FundAlloc::doApplyRelatedChanges(idField, idDataGroup) <= WARNING)
    {
        //If any fields are changed, fund/class must be revalidated against soft capped.
        setValidFlag(ifds::ToSoftCapCheck, idDataGroup, false);

        ToFundAllocList *pToFundAllocList = dynamic_cast<ToFundAllocList*>(getParent());

        if (pToFundAllocList && isFieldUpdated(idField, idDataGroup))
            pToFundAllocList->setAllAllocsFndClsValidFlag(false, idDataGroup);
    }

     return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY ToFundAlloc::doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateField" ) );
   if( FundAlloc::doValidateField( idField, strValue, idDataGroup ) > WARNING )
      return(GETCURRENTHIGHESTSEVERITY());

   if( idField == ifds::FundCode )
	{
      validateFundCodeCash( strValue, idDataGroup,false ); // cash is not valid
	}	
	else if( idField == ifds::FundClass )
	{
      validateFundClass ( idDataGroup );
	}
    else if( idField == ifds::ToSoftCapCheck )
	{
        validateToSoftCapCheck( idDataGroup );
	}
	else if( idField == ifds::AllocAmount )
	{
      validateAmount( strValue, idDataGroup );
	}	
	else if( idField == ifds::AllocPercentage )
	{
		validateFractional(strValue, idDataGroup);
	}
   return(GETCURRENTHIGHESTSEVERITY());
}


//******************************************************************************
SEVERITY ToFundAlloc::validateFundClass( const BFDataGroupId& idDataGroup ) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateFundClass" ) );
   DString dstrClassCode, dstrFundCode, dstrTransNum;
   getField(ifds::FundCode, dstrFundCode, idDataGroup, false);
   getField(ifds::ClassCode, dstrClassCode, idDataGroup, false);

   DString dstrEffectiveDate;
   DString AMSCode_4;
   getField( ifds::EffectiveDate, dstrEffectiveDate, idDataGroup, false );
   dstrEffectiveDate.strip();

   DString dstrTransTypeParam = EX_FER_IN_CODE;

   MFAccount *pMFAccount = NULL;
	DString dstrAccount;
	getParent()->getParent()->getField(ifds::AccountTo,dstrAccount,idDataGroup,false);
	dstrAccount.strip();
   getWorkSession().getMFAccount( idDataGroup, dstrAccount, pMFAccount, I_("N"), NULL_STRING, true, true  );//validate account num
   if( pMFAccount )
   {
      pMFAccount->canTradeFundClass (dstrFundCode, dstrClassCode, dstrTransTypeParam, dstrEffectiveDate, idDataGroup);
      pMFAccount->AMSFundAllow ( dstrFundCode, dstrClassCode, idDataGroup );
   }
   
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY ToFundAlloc::validateToSoftCapCheck( const BFDataGroupId& idDataGroup ) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateToSoftCapCheck" ) );
   DString dstrClassCode, dstrFundCode, dstrTransNum;
   getField(ifds::FundCode, dstrFundCode, idDataGroup, false);
   getField(ifds::ClassCode, dstrClassCode, idDataGroup, false);

   DString dstrEffectiveDate;
   DString AMSCode_4;
   getField( ifds::EffectiveDate, dstrEffectiveDate, idDataGroup, false );
   dstrEffectiveDate.strip();

   DString dstrTransTypeParam = EX_FER_IN_CODE;

   MFAccount *pMFAccount = NULL;
   DString dstrAccount;
   getParent()->getParent()->getField(ifds::AccountTo,dstrAccount,idDataGroup,false);
   dstrAccount.strip();
   getWorkSession().getMFAccount( idDataGroup, dstrAccount, pMFAccount, I_("N"), NULL_STRING, true, true  );//validate account num

   // Soft Capped validation
   DString fromFund, fromClass, fromAccount;
   RRIF_LIF_LRIF_Info *pRRIFInfo = NULL;
   FromFundAllocList *pFromFundAllocList = NULL;

   pRRIFInfo = dynamic_cast<RRIF_LIF_LRIF_Info*>(getParent()->getParent());

   if (pRRIFInfo)
   {
       pRRIFInfo->getField(ifds::AccountNum, fromAccount, idDataGroup,false);
       pRRIFInfo->getFromFundAllocList(pFromFundAllocList, idDataGroup, false);

       if (pFromFundAllocList)
       {
           BFObjIter iterFromAllocs(*pFromFundAllocList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );

           while (!iterFromAllocs.end())
           {
               iterFromAllocs.getObject()->getField(ifds::FundCode, fromFund, idDataGroup);
               iterFromAllocs.getObject()->getField(ifds::ClassCode, fromClass, idDataGroup);

               bool isTransfer = fromAccount != dstrAccount &&
                                 !fromFund.empty() && !fromClass.empty() &&
                                 !dstrFundCode.empty() && !dstrClassCode.empty() &&
                                 fromFund == dstrFundCode && fromClass == dstrClassCode;

               if (!isTransfer)
                   getWorkSession().fundClassSoftCappedCheck(dstrAccount, dstrFundCode, dstrClassCode, I_("DD"), dstrEffectiveDate, idDataGroup);

               ++iterFromAllocs;
           }
       }
   }
   
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY ToFundAlloc::initDefault(BFAbstractCBO* pDefaultAlloc, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initDefault" ) )

   FundAlloc::initDefault(pDefaultAlloc, idDataGroup);

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

BFData * ToFundAlloc::getDataForModelOffer()
{
   return(new BFData(ifds::DSTC0068_VWRepeat_Record));
}
//******************************************************************************

SEVERITY ToFundAlloc::getSplitCommissionList ( SplitCommissionList *&pSplitCommissionList, const BFDataGroupId& idDataGroup, 
                                                 bool bCreate /*= true*/,
                                                 bool bGetDefault /*= false*/)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getSplitCommissionList" ) );

   pSplitCommissionList=NULL;//no split commissions for rrif allocations

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY ToFundAlloc::loadSubstitutions( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "loadSubstitutions" ) );
   setFieldSubstituteValues( ifds::TransType, idDataGroup, ifds::RRIFTransType );
   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************
SEVERITY ToFundAlloc::doPreSetField( const BFFieldId& idField, DString & strValue, const BFDataGroupId& idDataGroup, bool bFormatted )
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
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/ToFundAlloc.cpp-arc  $
// 
//    Rev 1.4   Jan 14 2009 17:16:16   wongsakw
// IN1550993 Invalid warning message when fund entered in lower case for LIF allocation
// 
//    Rev 1.3   Nov 14 2004 14:57:14   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.2   Nov 06 2004 00:42:34   popescu
// PET 1117/06, synch changes
// 
//    Rev 1.1   Jul 07 2003 11:36:52   YINGBAOL
// cosmetic changes
// 
//    Rev 1.0   Jun 09 2003 11:04:54   YINGBAOL
// Initial revision.

 * 
 * 
 */