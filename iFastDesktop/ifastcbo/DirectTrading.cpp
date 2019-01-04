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
//    Copyright 1999 by DST Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : DirectTrading.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : DirectTrading
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "DirectTrading.hpp"
#include "DirectTradinglist.hpp"
#include "mfaccount.hpp"
#include "mgmtcooptions.hpp"
#include "mgmtco.hpp"
#include "shareholder.hpp"

#include <ifastdataimpl\dse_dstc0265_vw.hpp>
#include <ifastdataimpl\dse_dstc0266_req.hpp>
#include <ifastdataimpl\dse_dstc0052_vw.hpp>
#include <ifastdataimpl\dse_dstc0069_vw.hpp>
#include <ifastdataimpl\dse_dstc0004_vw.hpp>
#include "taxtyperule.hpp"
#include "taxtyperulelist.hpp"

namespace CND
{  // Conditions used
	extern const long ERR_STOP_DATE_LESS_THAN_DEFF;
	extern const long ERR_DEFF_STOP_DATE_RANGE_EXISTS;
}

namespace ifds
{
	extern CLASS_IMPORT const BFNumericFieldId AccountNum;
	extern CLASS_IMPORT const BFTextFieldId DTATypeCommercial;
	extern CLASS_IMPORT const BFTextFieldId DTATypeNonCommercial;
	extern CLASS_IMPORT const BFDateFieldId CurrBusDate;
	extern CLASS_IMPORT const BFTextFieldId EffectiveStopDate;
}

namespace  
{
   const I_CHAR * const CLASSNAME      = I_( "DirectTrading" );
   const I_CHAR * const YES_STRING     = I_("Yes");
   const I_CHAR * const Y_STRING       = I_("Y");
   const I_CHAR * const N_STRING       = I_("N");
   const I_CHAR * const CORPORATE_ACCT_TYPE  = I_( "4" );
   const I_CHAR * const ASSOCIATION_ACCT_TYPE  = I_( "9" );
   const I_CHAR * const BLANK_SUBSTITUTION         = I_( " = ;");
   const I_CHAR * const IDI_CODE       = I_("CODE");  
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const ACCTDTA;
   extern CLASS_IMPORT I_CHAR * const DTA_TRADING;
}
//-------------------------------------------------------------------
const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//  Field DD Id,            State Flags,             Group Flags 
   { ifds::AccountNum,     BFCBO::REQUIRED,             0 }, 
   { ifds::DTAType,           BFCBO::REQUIRED,             0 }, 
   { ifds::EffectiveDate,     BFCBO::NONE,					0 }, 
   { ifds::HoldingTransitNo,  BFCBO::NONE,					0 }, 
   { ifds::StopDate,	       BFCBO::NONE,		            0 }, 
   { ifds::ModDate,           BFCBO::NONE,                 0 }, 
   { ifds::ModUser,           BFCBO::NONE,                 0 }, 
   { ifds::Username,          BFCBO::NONE,                 0 }, 
   { ifds::ProcessDate,       BFCBO::NONE,                 0 }, 
   { ifds::Version,	       BFCBO::NONE,                 0 }, 
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

const BFCBO::CLASS_OBJECT_INFO classObjectInfo[] = {
//  Object Label,            State Flags,           Group Flags 
   {  I_(""),        BFCBO::REQUIRED,         0}
};

static const int NUM_OBJECTS = sizeof( classObjectInfo ) / sizeof( BFCBO::CLASS_OBJECT_INFO );


DirectTrading::DirectTrading( BFAbstractCBO &parent ) 
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
   registerMemberData( NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0,
                       NULL );
}
//------------------------------------------------------------------------
DirectTrading::~DirectTrading()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}     

//---------------------------------------------------------------------  
SEVERITY DirectTrading::doValidateField( const BFFieldId& idField,
                                   const DString& strValue,
                                   const BFDataGroupId& idDataGroup )

{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateField" ) );

   SEVERITY  svrn = NO_CONDITION;

   if( idField == ifds::DTAType )
   {
		validateDTAType( idDataGroup );
   }
   else if( idField == ifds::EffectiveDate )
   {
		validateEffectiveStopDate( idDataGroup );
   }
   else if( idField == ifds::StopDate )
   {
	   validateEffectiveStopDate( idDataGroup );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//-----------------------------------------------------------------------------------------
void DirectTrading::validateEffectiveStopDate(const BFDataGroupId& idDataGroup)
{

   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateEffectiveStopDate" ) );
   DString EffectiveDate, StopDate;
   getField(ifds::StopDate, StopDate, idDataGroup);
   getField(ifds::EffectiveDate, EffectiveDate, idDataGroup);

   if( DSTCommonFunctions::CompareDates( StopDate, EffectiveDate ) 
       == DSTCommonFunctions::FIRST_EARLIER )
      ADDCONDITIONFROMFILE( CND::ERR_STOP_DATE_LESS_THAN_DEFF );

}

void DirectTrading::validateDTAType(const BFDataGroupId& idDataGroup)
{

   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateEffectiveStopDate" ) );
      
   DString dstrDTAType;   
   getField(ifds::DTAType, dstrDTAType, idDataGroup);
   if( dstrDTAType.strip() != NULL_STRING )
   {
	   //do not need validate here, the substitution set of DTA Type is baed on the account type / tax type.
   }
}

//--------------------------------------------------------------------
SEVERITY DirectTrading::init(DirectTradingList* DTAList, const BFData& InstData )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );
   _pDirectTradingList = DTAList;

   attachDataObject(const_cast<BFData&>(InstData), false, true );  //true   
   setDTATypeSubstitutionSet( BF::HOST );
   
   return(GETCURRENTHIGHESTSEVERITY());
}
//---------------------------------------------------------------------------------------

void DirectTrading::init( DirectTradingList* DTAList, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) ); 
   _pDirectTradingList = DTAList;
   setDTATypeSubstitutionSet( idDataGroup );
}

//-------------------------------------------------------------------------------------
void  DirectTrading::validateCodeEffectStop( DString strAcctNumber, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateCodeEffectStop" ) );

   if( IsDTADuplicated(strAcctNumber,idDataGroup) )
   {
      DString strTemp;
      addIDITagValue( strTemp, IDI_CODE, strAcctNumber.asInteger() );

      ADDCONDITIONFROMFILEIDI( CND::ERR_DEFF_STOP_DATE_RANGE_EXISTS, strTemp);
   }
}

//-------------------------------------------------------------------------------------
bool DirectTrading::IsDTADuplicated( const DString& strAcctNumber, const BFDataGroupId& idDataGroup )
{
   TRACE_METHOD( CLASSNAME, I_( "IsAddrCodeDuplicated" ) );
   bool _bRet = false;
   BFObjIter iterDTAlist( *_pDirectTradingList, idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED );


   DString  dstrAccountNumber,StopDate;
   while( !iterDTAlist.end() )
   {
      iterDTAlist.getObject( )->getField(ifds::AccountNum, dstrAccountNumber, idDataGroup );
      if( this != iterDTAlist.getObject() )
      {
         if( (strAcctNumber == dstrAccountNumber) )
         {
            DString efftDate1,stopDate1,efftDate2,stopDate2;
            iterDTAlist.getObject( )->getField(ifds::StopDate, stopDate1, idDataGroup );
            iterDTAlist.getObject( )->getField(ifds::EffectiveDate, efftDate1, idDataGroup );
            getField(ifds::EffectiveDate, efftDate2, idDataGroup );
            getField(ifds::StopDate, stopDate2, idDataGroup );
            if( DSTCommonFunctions::dateRangesOverlap(efftDate1,stopDate1,efftDate2,stopDate2) )
            {
               _bRet = true;
               break;
            }
         }
      }
      ++iterDTAlist;
   }
   return(_bRet);
}

//-------------------------------------------------------------------------
SEVERITY DirectTrading::doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges" ) );

   return(GETCURRENTHIGHESTSEVERITY());
}
//--------------------------------------------------------------------
void DirectTrading::SetDefault(const BFDataGroupId& idDataGroup)
{
   DString strValue;
   getWorkSession().getMgmtCoOptions()->getField( ifds::CurrBusDate, strValue, BF::HOST,false );

   DString dstrEffecDate( strValue );
   setFieldNoValidate( ifds::EffectiveDate, dstrEffecDate, idDataGroup, false, true, true );

   getWorkSession().getDateInHostFormat(strValue, DSTCWorkSession::DATE_TYPE::DAY12319999, idDataGroup);
   setFieldNoValidate( ifds::StopDate, strValue, idDataGroup, false  );

   setFieldValid( ifds::EffectiveStopDate, idDataGroup, true );
   setDTATypeSubstitutionSet( idDataGroup );

}

//---------------------------------------------------------------------------
void DirectTrading::doInitWithDefaultValues( const BFDataGroupId& idDataGroup )
{
   SetDefault(idDataGroup);
}

//---------------------------------------------------------------------------
void DirectTrading::setDTATypeSubstitutionSet( const BFDataGroupId& idDataGroup )
{
   DString dstrAcctType, dstrAccountNumber, dstrTaxType, dstrExclAcctType;

   //get MFAccount, find taxtype, account type, set substitution set of DTAType
   getParent()->getParent()->getField( ifds::AccountNum, dstrAccountNumber, idDataGroup );
   //getField(ifds::AccountNum, dstrAccountNumber, idDataGroup);
   dstrAccountNumber.stripLeading( '0' ).strip();
   if (!dstrAccountNumber.strip().empty() )
   {
	  MFAccount *pMFAccount = NULL;
	  if (getWorkSession().getMFAccount(idDataGroup, dstrAccountNumber, 
			pMFAccount) <= WARNING && pMFAccount)
	  {
			if( pMFAccount->isAcctDTAEligible( idDataGroup ) )
			{
				pMFAccount->getField(ifds::AcctType, dstrAcctType, idDataGroup, false);
				if( dstrAcctType == CORPORATE_ACCT_TYPE || dstrAcctType == ASSOCIATION_ACCT_TYPE)
					setFieldSubstituteValues( ifds::DTAType, idDataGroup, ifds::DTATypeCommercial );
				else 
				{
					setFieldSubstituteValues( ifds::DTAType, idDataGroup, ifds::DTATypeNonCommercial );	
				}
			}
			else
			{
				setFieldAllSubstituteValues( ifds::DTAType, idDataGroup, BLANK_SUBSTITUTION );
			}
	  }
   }
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DirectTrading.cpp-arc  $
// 
//    Rev 1.3   Nov 14 2004 14:30:38   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.2   Oct 23 2003 17:52:54   FENGYONG
// Add HoldingTransitNo field
// 
//    Rev 1.1   Oct 16 2003 12:17:56   FENGYONG
// PET809 FN08 Direct Trading enhancement
// 
//    Rev 1.0   Oct 07 2003 10:15:58   FENGYONG
// Initial Revision
 * 
 */