//********************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2002 By International Financial Data Services.
//
//
//********************************************************************************
//
// ^FILE   : AmsMstrInfo.cpp
// ^AUTHOR : Yingbao Li
// ^DATE   : May 24,2002
//
//********************************************************************************

#include "stdafx.h"

#include "amsfundalloclist.hpp"
#include "amslmtoverride.hpp"
#include "amslmtoverridelist.hpp"
#include "amsmstrinfo.hpp"
#include "amsmstrlist.hpp"
#include "amsrebdatecalc.hpp"
#include "currency.hpp"
#include "currencylist.hpp"
#include "datevalidation.hpp"
#include "errmsgruleslist.hpp"
#include "frequency.hpp"
#include "frequencylist.hpp"
#include "funddetail.hpp"
#include "funddetaillist.hpp"
#include "fundmaster.hpp"
#include "fundmasterlist.hpp"
#include "mgmtco.hpp"
#include "mgmtcooptions.hpp"
#include "AMSDeltaAllocList.hpp"
#include "AMSDeltaAlloc.hpp"
#include <bfutil\bfdate.hpp>

#include <ifastdataimpl\dse_dstc0083_vw.hpp>
#include <ifastdataimpl\dse_dstc0149_vw.hpp>
#include <ifastdataimpl\dse_dstc0179_vw.hpp>
#include <ifastdataimpl\dse_dstc0179_req.hpp>
#include <ifastdataimpl\dse_dstc0218_vw.hpp>
#include <ifastdataimpl\dse_dstc0219_req.hpp>
#include <ifastdataimpl\dse_dstc0219_vw.hpp>
#include <ifastdataimpl\dse_dstc0483_vw.hpp>

#include "amsfundalloc.hpp"

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest AMS_MASTER_LIST;   
}

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME					 = I_( "AmsMstrInfo" );
   const I_CHAR * const AMSFUNDALLOCATIONLIST	 = I_( "AMSFundAllocList" );
   const I_CHAR * const AMSDELTAALLOCLIST        = I_( "AMSDeltaAllocList" );
   const I_CHAR * const YES							 = I_( "Y" );
   const I_CHAR * const NO								 = I_( "N" );
   const double dSmallValue							 = .0000000001;
   const I_CHAR * const REBALANCE					 = I_("RB");
   const I_CHAR * const FUND_OF_FUNDS				 = I_("FOF");
   const I_CHAR * const BUSINESS_DATE				 = I_( "3" ); 
   const I_CHAR * const AMS_LMTOVERRIDE_LIST		 = I_( "AmsLmtOverrideList" );
   const I_CHAR * const FREQ_WEEKLY				    = I_( "1" );
   const I_CHAR * const FREQ_BIWEEKLY				 = I_( "2" );
   const I_CHAR * const FREQ_OTHER					 = I_( "8" );

   const I_CHAR * const STOP_PUR					    = I_("03");  
   const I_CHAR * const STOP_TRFER_IN				 = I_("05");  
   const I_CHAR * const NOT_EXIST					 = I_( "-1" );
   const I_CHAR * const ERR_EXC_FUND_REQUIRED	 = I_( "377" );
   const I_CHAR * const ERR_ROUND_FUND_REQUIRED  = I_( "378" );
   const I_CHAR * const ERR_MFOL_NAME_REQUIRED	 = I_( "394" );

   const I_CHAR * const MIN_PURCHASE             = I_( "01" );
   const I_CHAR * const MIN_SUB_PURCHASE         = I_( "02" );
   const I_CHAR * const STOP_PURCHASE            = I_( "03" );   
   const I_CHAR * const STOP_REDEMPTION          = I_( "04" );
   const I_CHAR * const STOP_TRANSFER_IN         = I_( "05" );
   const I_CHAR * const STOP_TRANSFER_OUT        = I_( "06" );
   const I_CHAR * const MIN_PAC                  = I_( "07" );
   const I_CHAR * const STOP_PAC                 = I_( "08" );
   const I_CHAR * const STOP_SWP                 = I_( "09" );
   const I_CHAR * const STOP_AT_TRANSFER_IN      = I_( "10" );
   const I_CHAR * const STOP_AT_TRANSFER_OUT     = I_( "11" );
   const I_CHAR * const MIN_SWP                  = I_( "12" );
   const I_CHAR * const MAX_REDEMPTION           = I_( "13" ); 
   
   const I_CHAR * const DEFAULT_DATE             = I_("12319999");

   const I_CHAR * const NA_00                    = I_("00");
   const I_CHAR * const YES_01                   = I_("01");

   const I_CHAR * const MarketValueWeight = I_("M");
}

namespace IFASTERR
{
    extern CLASS_IMPORT I_CHAR * const ACCT_LVL_EFFECTIVE_DATE;
   extern CLASS_IMPORT I_CHAR * const FUND_CLASS_MUST_BE_AMS_PARENT_FUND;
}

namespace CND
{
   extern const long ERR_ENTRY_EMPTY_OR_CONTAINS_ONLY_SPACE;    
   extern const long ERR_VALUE_BETWEEN_0_AND_100;
   extern const long ERR_AMS_CODE_SET_UP;
   extern const long ERR_NO_CURRENY;
   extern const long ERR_AMS_CODE_SET_UP_0001;
   extern const long ERR_FUND_ALLOC_SET_UP;
   extern const long ERR_NO_VALID_FUND_ALLOC_RECORD;
   extern const long ERR_EFFECTIVE_DATE_BACKWARD;
   extern const long ERR_INVALID_AMS_CODE;
   extern const long ERR_FUND_NOT_EFFECTIVE;
   extern const long ERR_DOMESTIC_FUND_ONLY;
   extern const long ERR_FUND_CLASS_NOT_EFFECTIVE;
   extern const long ERR_INVALID_FUND_CLASS_CODES;
   extern const long ERR_BUSINESS_DATE_ONLY;
 //  extern const long ERR_NEXT_REB_DATE_CHANGED;
   extern const long ERR_DATE_CANNOT_EARLIER_THAN_CURRENT_BUSINESS_DATE;
   extern const long ERR_DATE_NOT_LAST_BUSINESS_DAY_OF_WEEK;
   extern const long ERR_GRAND_FATHER_DATE_BACKWARD;
   extern const long ERR_DAYOFWEEK_REQUIRED;
   extern const long ERR_DATE_CANNOT_GREATER_THAN_LAST_REB_DATE;
   extern const long ERR_GRAND_FATHER_DATE_CANNOT_EARLIER_THAN_EFFECTIVE_DATE;
   extern const long ERR_RULE_TYPE_RECORD_FOR_STOP_TRFER_IN_REQUIRED;
   extern const long AMS_LMT_ERR_GRANDFATHERED_DATE;
   extern const long ERR_NEXT_REB_DATE_CANNOT_EARLIER_THAN_EFFECTIVE_DATE;
   extern const long ERR_WARN_FOREIGN_FUND_CLASS_REQUIRED;
   extern const long ERR_FOREIGN_FUND_CLASS_REQUIRED;
   extern const long ERR_ROUND_FUND_CLASS_REQUIRED;
   extern const long ERR_WARN_ROUND_FUND_CLASS_REQUIRED;
   extern const long ERR_DATE_MUST_BE_BUSINESS_DATE;
   extern const long AMS_LMT_WARN_GRANDFATHERED_DATE;
   extern const long ERR_FUND_CLASS_NOT_IN_PORTFOLIO;
	extern const long ERR_AMS_GLOBAL_ROUNDING_FUND_CLASS_NOT_IN_AMS_MIX;
   extern const long ERR_AMS_FUND_CLASS_NOT_VALID_FOR_FOF;
   extern const long ERR_EFFECTIVE_DATE_BEFORE_CURBUSDATE;
   extern const long WARN_EFFECTIVE_DATE_BEFORE_CURBUSDATE;
   extern const long ERR_FUND_CLASS_MUST_BE_AMS_PARENT_FUND;
   extern const long WARN_FUND_CLASS_MUST_BE_AMS_PARENT_FUND;
   extern const long ERR_PARENT_FUND_CLASS_REQUIRED;
}

namespace ifds
{
	 extern CLASS_IMPORT const BFDecimalFieldId RBLThrshldDflt;
	 extern CLASS_IMPORT const BFTextFieldId    DispRBLSysThrshld;
	 extern CLASS_IMPORT const BFTextFieldId    CommonCurrency;
	 extern CLASS_IMPORT const BFDateFieldId    CurrBusDate;
	 extern CLASS_IMPORT const BFTextFieldId    RoundingFundClass;
	 extern CLASS_IMPORT const BFTextFieldId    ForeignRelFundClass;
	 extern CLASS_IMPORT const BFTextFieldId    AMSRecordOverlapCheck;
    extern CLASS_IMPORT const BFTextFieldId	  CompoundDate;
	 extern CLASS_IMPORT const BFTextFieldId    RoundingFundNum;
 	 extern CLASS_IMPORT const BFTextFieldId    ForeignRelFundNum;
	 extern CLASS_IMPORT const BFTextFieldId    Domestic;
	 extern CLASS_IMPORT const BFTextFieldId    DefaultRoundClass;
	 extern CLASS_IMPORT const BFTextFieldId    DefaultRoundFund;
	 extern CLASS_IMPORT const BFTextFieldId    DefaultRebFreq;
	 extern CLASS_IMPORT const BFTextFieldId    FieldCrossEdit1;
	 extern CLASS_IMPORT const BFTextFieldId    NextRebDateApplicable;
	 extern CLASS_IMPORT const BFTextFieldId    RBFrequency;
    extern CLASS_IMPORT const BFTextFieldId    AssocFundNum;
    extern CLASS_IMPORT const BFTextFieldId    AssocFundClass;
    extern CLASS_IMPORT const BFDateFieldId    NextProcessDate;
   extern CLASS_IMPORT const BFTextFieldId    MstrActActive;
   extern CLASS_IMPORT const BFTextFieldId    AMSModelType;
   extern CLASS_IMPORT const BFTextFieldId    ParentFundClassXEdit;
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const AMS_GLOBAL;
   extern CLASS_IMPORT I_CHAR * const UPD_NEXT_REB_DATE;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
   //  Field DD Id,					 State Flags,			         Group Flags 
   { ifds::AMSCode,			       BFCBO::REQUIRED,             0 }, 
   { ifds::AMSCodeVer,		       BFCBO::NONE,                 0 }, 
   { ifds::Amount,	   	       BFCBO::NONE,                 0 }, 
   { ifds::EffectiveDate,		    BFCBO::REQUIRED,             0 },
   { ifds::AMSType,			       BFCBO::REQUIRED,             0 }, 
   { ifds::DefaultAlloc,		    BFCBO::NONE,					   0 }, 
   { ifds::FundAlloc,			    BFCBO::NONE,                 0 }, 
   { ifds::Percentage,			    BFCBO::NONE,					   0 }, 
   { ifds::Currency,			       BFCBO::NONE,				   	0 }, 
   { ifds::EnglishShortName,	    BFCBO::REQUIRED,             0 }, 
   { ifds::EnglishLongName,	    BFCBO::REQUIRED,             0 }, 
   { ifds::EnglishName,		       BFCBO::NONE,					   0 }, 
   { ifds::FrenchShortName,	    BFCBO::REQUIRED,             0 }, 
   { ifds::FrenchLongName,		    BFCBO::REQUIRED,             0 }, 
   { ifds::FrenchName,			    BFCBO::NONE,					   0 }, 
   { ifds::ForeignRelFund,		    BFCBO::NONE,					   0 }, 
   { ifds::ForeignRelClass,	    BFCBO::NONE,					   0 }, 
   { ifds::RoundingFund,		    BFCBO::NONE,					   0 }, 
   { ifds::RoundingClass,		    BFCBO::NONE,					   0 }, 
   { ifds::NextRebDate,		       BFCBO::NONE,					   0 }, 
   { ifds::SchedSetupFreqID,	    BFCBO::NONE,					   0 }, 
   { ifds::DayOfWeek,			    BFCBO::NONE,					   0 }, 
   { ifds::GrandFatheredDate,	    BFCBO::NONE,					   0 }, 
   { ifds::LastRebDate,		       BFCBO::NONE,					   0 }, 
   { ifds::ThresholdAmt,		    BFCBO::NONE,					   0 }, 
   { ifds::WireEleg,			       BFCBO::NONE,					   0 }, 
   { ifds::LastEffectiveDate,	    BFCBO::NONE,					   0 }, 
   { ifds::GrandFatherStamped,	 BFCBO::NONE,					   0 }, 
   { ifds::VerifyPrecreate,	    BFCBO::NONE,					   0 }, 
   { ifds::ForeignRelFundClass,   BFCBO::IMMEDIATE_VALIDATION,	0 },
   { ifds::RoundingFundClass,	    BFCBO::IMMEDIATE_VALIDATION,	0 },
   { ifds::AMSRecordOverlapCheck, BFCBO::NONE,	               0 },
   { ifds::CompoundDate,		    BFCBO::IMMEDIATE_VALIDATION,	0 },
   { ifds::FieldCrossEdit1,		 BFCBO::IMMEDIATE_VALIDATION, 0 },
   { ifds::ForeignRelFundNum,     BFCBO::NONE,                 0 },
   { ifds::RoundingFundNum,       BFCBO::NONE,                 0 },
   { ifds::AssocFundNum,          BFCBO::NONE,                 0 },
   { ifds::AssocFund,             BFCBO::NONE,                 0 },
   { ifds::AssocClass,            BFCBO::NONE,                 0 },
   { ifds::AssocFundClass,        BFCBO::IMMEDIATE_VALIDATION,	0 },
   { ifds::ParentFndClsTrdg,      BFCBO::NONE,                 0 },
   { ifds::ParentFundClassXEdit,  BFCBO::NONE,                 0 },
   { ifds::RebalReq,			  BFCBO::NONE,				   0 },
   { ifds::TargetMixOption,		  BFCBO::NONE,				   0 },
   { ifds::AMSDeltaRequestUUID,   BFCBO::NONE,				   0 },
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

const BFCBO::CLASS_OBJECT_INFO classObjectInfo[] = 
{
   // Object Label,               State Flags,     Group Flags 
   { I_( "AMSFundAllocList" ),    BFCBO::NONE,     0},
};

static const int NUM_OBJECTS = sizeof( classObjectInfo ) / sizeof( BFCBO::CLASS_OBJECT_INFO );

//******************************************************************************
AmsMstrInfo::AmsMstrInfo( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
,_pFundMasterList(NULL)
,_pErrMsgRulesList(NULL)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 
		NUM_OBJECTS, (const CLASS_OBJECT_INFO *)&classObjectInfo );
   
   addCrossEdit(ifds::RoundingFundClass,     ifds::RoundingFund );
   addCrossEdit(ifds::RoundingFundClass,     ifds::RoundingClass );
   addCrossEdit(ifds::ForeignRelFundClass,   ifds::ForeignRelFund );
   addCrossEdit(ifds::ForeignRelFundClass,   ifds::ForeignRelClass );
   addCrossEdit(ifds::AMSRecordOverlapCheck, ifds::AMSCode );
   addCrossEdit(ifds::AMSRecordOverlapCheck, ifds::EffectiveDate );
   addCrossEdit(ifds::CompoundDate,          ifds::EffectiveDate );
   addCrossEdit(ifds::CompoundDate,          ifds::GrandFatheredDate );
   addCrossEdit(ifds::FieldCrossEdit1,       ifds::EffectiveDate );
   addCrossEdit(ifds::FieldCrossEdit1,       ifds::NextRebDate );
   addCrossEdit(ifds::AssocFundClass,        ifds::AssocFund );
   addCrossEdit(ifds::AssocFundClass,        ifds::AssocClass );

   addCrossEdit(ifds::ParentFundClassXEdit, ifds::AssocFund );
   addCrossEdit(ifds::ParentFundClassXEdit, ifds::AssocClass );
   addCrossEdit(ifds::ParentFundClassXEdit, ifds::ParentFndClsTrdg);
}

//******************************************************************************

AmsMstrInfo::~AmsMstrInfo()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}  

//******************************************************************************
SEVERITY AmsMstrInfo::init( const BFData& data )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );
   attachDataObject(const_cast<BFData&>(data), false);  
   setFieldStates(BF::HOST);

   setFieldReadOnly( ifds::AMSCode,       BF::HOST, true );
   setFieldReadOnly( ifds::EffectiveDate, BF::HOST, true );
   setFieldReadOnly( ifds::AMSType,       BF::HOST, true );
   setFieldReadOnly( ifds::LastRebDate,   BF::HOST, true );
   
   DString dstrFundAlloc=data.getElementValue(ifds::FundAlloc);
   dstrFundAlloc.strip().upperCase();
   if (dstrFundAlloc == YES)
   {
		setFieldNoValidate(ifds::DefaultAlloc, NO, BF::HOST, false);
		setFieldReadOnly(ifds::DefaultAlloc,BF::HOST,true);
   }
   setFieldReadOnly(ifds::DefaultAlloc,BF::HOST,true);
   setFieldReadOnly(ifds::FundAlloc,BF::HOST,true);

   _initEffectiveDate   = data.getElementValue(ifds::EffectiveDate);
   _initNextRebDate     = data.getElementValue(ifds::NextRebDate);
   _initGrandFatherDate = data.getElementValue(ifds::GrandFatheredDate);
   _initFreq            = data.getElementValue(ifds::SchedSetupFreqID);

   _initFreq.strip();
   _initGrandFatherDate.strip();
   _initEffectiveDate.strip();
   _initNextRebDate.strip();
 //Input grandfather date only allowed if the AMS record has the latest effective date among all AMS master of the same AMS code.  
   DString strLastEffectiveDate = data.getElementValue(ifds::LastEffectiveDate);
   if( DSTCommonFunctions::CompareDates(strLastEffectiveDate,_initEffectiveDate ) != DSTCommonFunctions::EQUAL )
   {
       setFieldReadOnly( ifds::GrandFatheredDate,BF::HOST, true );
   }
   
   DString dstrFundCode, dstrFundNumber, dstrClassCode;
   BFCBO::getField( ifds::ForeignRelFund,  dstrFundCode, BF::HOST );
   BFCBO::getField( ifds::ForeignRelClass, dstrClassCode, BF::HOST );
   getWorkSession().GetFundNumber( dstrFundCode,dstrClassCode, dstrFundNumber );   
   setFieldNoValidate( ifds::ForeignRelFundNum, dstrFundNumber, BF::HOST, false,true, false, false  ); 

   BFCBO::getField( ifds::RoundingFund,  dstrFundCode, BF::HOST );
   BFCBO::getField( ifds::RoundingClass, dstrClassCode, BF::HOST );
   getWorkSession().GetFundNumber( dstrFundCode,dstrClassCode, dstrFundNumber );   
   setFieldNoValidate( ifds::RoundingFundNum, dstrFundNumber, BF::HOST, false,true, false, false  ); 

   BFCBO::getField( ifds::AssocFund,  dstrFundCode,  BF::HOST );
   BFCBO::getField( ifds::AssocClass, dstrClassCode, BF::HOST );
   getWorkSession().GetFundNumber( dstrFundCode, dstrClassCode, dstrFundNumber );   
   setFieldNoValidate( ifds::AssocFundNum, dstrFundNumber, BF::HOST, false,true, false, false  ); 

   //Update of Next Rebalance Date is not allowed for existing record if the original value is equal to Current Business Date.
   //update should only be allowed for existing AMS master record if the AMS master is effective as of
   //current business date or the effective date of the AMS master is future dated.
   DString dstrCurDate;
   getWorkSession().getMgmtCoOptions()->getField( ifds::CurrBusDate, dstrCurDate, BF::HOST ,false );
   if( DSTCommonFunctions::CompareDates(dstrCurDate,_initEffectiveDate ) != DSTCommonFunctions::FIRST_EARLIER 
	  || DSTCommonFunctions::CompareDates(strLastEffectiveDate,_initEffectiveDate ) != DSTCommonFunctions::EQUAL 
	  || DSTCommonFunctions::CompareDates(dstrCurDate,_initNextRebDate ) == DSTCommonFunctions::EQUAL 
	 )
   {
       setFieldReadOnly( ifds::NextRebDate,BF::HOST, true );
   }

   bool bRequired = ( _initFreq == FREQ_WEEKLY || _initFreq == FREQ_BIWEEKLY );
	if ( !bRequired )
	{
	  setFieldNoValidate(ifds::DayOfWeek, NULL_STRING, BF::HOST, false, true, true);
			
	}
	
   setFieldReadOnly(ifds::DayOfWeek,BF::HOST,!bRequired);
   
   /* Set readonly to field TargetMixOption and RebalReq. If AMSCode is 0001 (Init)*/
   DString dstrAMSCode = data.getElementValue(ifds::AMSCode);
   bool bReadOnly = (dstrAMSCode.strip() == I_("0001") ? true : false);
   setFieldReadOnly( ifds::TargetMixOption, BF::HOST, bReadOnly);
   setFieldReadOnly( ifds::RebalReq, BF::HOST, bReadOnly);

	return GETCURRENTHIGHESTSEVERITY();
}

//*******************************************************************************
void AmsMstrInfo::initNew(const BFDataGroupId& idDataGroup )
{

}

//**********************************************************************************
void AmsMstrInfo::setAMSType(const DString& dstrAMSType,const BFDataGroupId& idDataGroup)
{
	setFieldNoValidate(ifds::AMSType, dstrAMSType, idDataGroup,false);
	(( AMSMstrList *)getParent() )->setCurrentAMSType(dstrAMSType);
	setFieldUpdated( ifds::AMSType, idDataGroup, false);
}

//*********************************************************************************
void AmsMstrInfo::setFieldStates(const BFDataGroupId& idDataGroup)
{
	DString dstrDispRBL,dstrCurrency,dstrOvrdRBLThrshld;

	bool bPermit = getWorkSession().hasUpdatePermission(UAF::AMS_GLOBAL );

	getWorkSession().getMgmtCoOptions()->getField( ifds::DispRBLSysThrshld, 
				dstrDispRBL, idDataGroup ,false );	
	getWorkSession().getMgmtCoOptions()->getField( ifds::CommonCurrency, 
				dstrCurrency, idDataGroup ,false );
	getWorkSession().getMgmtCoOptions()->getField( ifds::OvrdRBLThrshld, 
				dstrOvrdRBLThrshld, idDataGroup ,false );
	dstrCurrency.strip().upperCase();
	dstrDispRBL.strip().upperCase();
	dstrOvrdRBLThrshld.strip().upperCase();

   bool bUpdate = bPermit && dstrDispRBL == YES && dstrOvrdRBLThrshld == YES;
	DString strClientAMSType,strCommonCur;
	getWorkSession().getMgmtCoOptions()->getField(ifds::ClientAMSType, strClientAMSType, idDataGroup, false);
	strClientAMSType.strip().upperCase();

	strClientAMSType += I_(',');
   int iPos =  strClientAMSType.find_first_of(I_(",") );
	int index = 0;
	bool  bRBSupport = false;
   while( iPos != DString::npos )
   {
      iPos =  strClientAMSType.find_first_of(I_(",") );
      if( iPos == DString::npos ) break;
      DString strType = strClientAMSType.left(iPos);

      strClientAMSType = strClientAMSType.right(strClientAMSType.length() - iPos  - 1);
		if(strType == REBALANCE )
		{
			bRBSupport = true;
			break;
		}
   }

	DString dstrAMSType;
	getField(ifds::AMSType,dstrAMSType,idDataGroup,false);
	dstrAMSType.strip().upperCase();

	if( bRBSupport && dstrAMSType == REBALANCE ) 
	{
		setFieldRequired( ifds::Percentage, idDataGroup, bUpdate );
      if( dstrCurrency == YES )
      {
         setFieldRequired( ifds::Currency,idDataGroup, bUpdate );
         setFieldValid( ifds::Currency,idDataGroup, !bUpdate );
      }
		setFieldValid( ifds::Percentage, idDataGroup, !bUpdate );
		setFieldRequired(ifds::NextRebDate, idDataGroup, bPermit);
		setFieldRequired(ifds::SchedSetupFreqID, idDataGroup, bPermit);
		setFieldValid(ifds::NextRebDate, idDataGroup, !bPermit);
		setFieldValid(ifds::SchedSetupFreqID, idDataGroup, !bPermit);

	}

   if ( dstrAMSType == FUND_OF_FUNDS )
   {
      setFieldRequired( ifds::AssocFund,  idDataGroup, true );
      setFieldRequired( ifds::AssocClass, idDataGroup, true );
   }

   setFieldReadOnly( ifds::Percentage,idDataGroup, !bUpdate  );
   setFieldReadOnly( ifds::ThresholdAmt,idDataGroup, !bUpdate  );
   
   bUpdate = bPermit && dstrCurrency == YES;
   // Currency only updatable during add mode
   setFieldReadOnly( ifds::Currency,idDataGroup, (idDataGroup == BF::HOST || !bUpdate ) );
   // setFieldReadOnly( ifds::Currency,idDataGroup, !bUpdate );
   setFieldReadOnly( ifds::LastRebDate, idDataGroup, true );

   //If user has no permission, NextRebalanceDate should be read only
	//Next Rebalance Date and Last Rebalance Date should be read only 
	//if generic control indicates these two fields are not applicable.
	DString dstrApplicable;	
	getWorkSession().getMgmtCoOptions()->getField( ifds::NextRebDateApplicable, 
				dstrApplicable, idDataGroup ,false );
	bUpdate = bPermit && getWorkSession().hasUpdatePermission(UAF::UPD_NEXT_REB_DATE )
			&& ( dstrApplicable == YES );
    setFieldReadOnly( ifds::NextRebDate, idDataGroup, !bUpdate );    
    setAMSFrequencySubstSet( idDataGroup );
     
	DString dstrErrValue;
	getErrMsgValue( ERR_MFOL_NAME_REQUIRED, idDataGroup, dstrErrValue );
	setFieldRequired(ifds::EnglishName, idDataGroup, dstrErrValue == I_("E"));
	setFieldRequired(ifds::FrenchName, idDataGroup, dstrErrValue == I_("E"));
}

//*************************************************************************************
SEVERITY AmsMstrInfo::setAMSFrequencySubstSet( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("setAMSFrequencySubstSet" ));  

   DString dstrFrequencySubstSet;
   
   FrequencyList *pFrequencyList = NULL;
   if ( getMgmtCo().getFrequencyList( pFrequencyList ) <= WARNING && 
        NULL != pFrequencyList )
   {      
      pFrequencyList->getFrequencySubstitutionSet( dstrFrequencySubstSet, idDataGroup);
   } 
   
   setFieldAllSubstituteValues( ifds::SchedSetupFreqID, idDataGroup, dstrFrequencySubstSet );      

   return GETCURRENTHIGHESTSEVERITY();
}

//*************************************************************************************
SEVERITY AmsMstrInfo::doValidateField( const BFFieldId& idField, const DString& strValue, 
												  const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateField" ));  

	if(idField == ifds::Currency )
	{
		// validate currency against view 101 but only if currency is applicable
		DString dstrCommonCurrency, dstrAMSType;
	   getField(ifds::AMSType,dstrAMSType,idDataGroup,false);
	   dstrAMSType.strip().upperCase();
		getWorkSession().getMgmtCoOptions()->getField( ifds::CommonCurrency, dstrCommonCurrency, idDataGroup ,false );
		dstrCommonCurrency.strip().upperCase();
		if ( YES == dstrCommonCurrency && REBALANCE == dstrAMSType )
		{
			CurrencyList* pCurrencyList = NULL;						
			if( getMgmtCo().getCurrencyList( pCurrencyList) <= WARNING && 
				NULL != pCurrencyList)
			{
				Currency*	pCurrency = NULL;
				if( pCurrencyList->getCurrency (strValue,pCurrency,idDataGroup ) == false)
				{
					ADDCONDITIONFROMFILE( CND::ERR_NO_CURRENY );
				}		
			}
		}
	}
	else if(idField == ifds::Percentage )
	{
		validateThreshold(strValue,idDataGroup );
	}
	else if( idField == ifds::AMSCode )
	{
		validateAMSCode(strValue,idDataGroup );
	}
	else if (idField == ifds::FundAlloc )
	{
		validateFundAlloc(strValue,idDataGroup);
	}
	else if ( idField == ifds::EffectiveDate)// && idDataGroup == BF::HOST )
	{
		validateEffectiveDate(strValue, idDataGroup);
	}
	else if ( idField == ifds::ForeignRelFund )
	{
		validateForeignRelFund(strValue, idDataGroup);
	}
   else if ( idField == ifds::AssocFund )
	{
		validateAssocFund(strValue, idDataGroup);
	}
	else if ( idField == ifds::RoundingFund )
	{
		validateRoundingFund(strValue, idDataGroup);
	}
	else if ( idField == ifds::ForeignRelFundClass )
	{
		validateRelFundClass( strValue, idDataGroup );
	}
   else if ( idField == ifds::AssocFundClass )
	{
		validateAssocFundClass( strValue, idDataGroup );
	}
	else if ( idField == ifds::RoundingFundClass )
	{
		validateRoundingFundClass( strValue, idDataGroup );
	}
	else if ( idField == ifds::NextRebDate )
	{
		validateNextRebDate( strValue, idDataGroup );
	}
	else if ( idField == ifds::GrandFatheredDate )
	{
		validateGrandFatherDate( strValue, idDataGroup );
	}
	else if ( idField == ifds::CompoundDate )
	{
		validateEffectiveGFDate( strValue, idDataGroup );
	}
	else if ( idField == ifds::AMSRecordOverlapCheck )
	{
		DupCheck4AmsRec(idDataGroup);
	}
	else if ( idField == ifds::FieldCrossEdit1 )
	{
//		validateEffectiveNextRebDate( strValue, idDataGroup );
	}
   else if( idField == ifds::ParentFundClassXEdit)
   {
      validateParentFundClassXEdit(idDataGroup);
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//***************************************************************************************
SEVERITY AmsMstrInfo::doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("doApplyRelatedChanges") );

   if( idField == ifds::AMSType )
   {
      bool bRequired = false;
      bool bReadOnly = false;

      DString dstrAMSType;
      getField( ifds::AMSType, dstrAMSType, idDataGroup );
      if ( FUND_OF_FUNDS == dstrAMSType  )
      {
         bRequired = true;
         bReadOnly = true;

         setFieldNoValidate(ifds::FundAlloc,    YES, idDataGroup, false );			
         setFieldNoValidate(ifds::DefaultAlloc, NO,  idDataGroup, false );			         
      }
      
      setFieldReadOnly(ifds::FundAlloc,    idDataGroup, bReadOnly );
      setFieldReadOnly(ifds::DefaultAlloc, idDataGroup, bReadOnly );

      setFieldRequired(ifds::AssocFund,  idDataGroup, bRequired );
      setFieldRequired(ifds::AssocClass, idDataGroup, bRequired );
   }
   if( idField == ifds::FundAlloc )
   {   
	   DString dstrFundAlloc;
		getField(ifds::FundAlloc, dstrFundAlloc, idDataGroup, false);
		if (dstrFundAlloc == YES)
		 {
			setFieldNoValidate(ifds::DefaultAlloc, NO, idDataGroup, false);
			setFieldReadOnly(ifds::DefaultAlloc,idDataGroup,true);
		 }
		 else
			setFieldReadOnly(ifds::DefaultAlloc,idDataGroup,false);
   }
   else if ( idField == ifds::SchedSetupFreqID )
   {
		doRBFreqRelatedChanges(idDataGroup);
   }
   else if ( idField == ifds::DayOfWeek || idField == ifds::EffectiveDate )
   {
      CalculateNextRebDate(idDataGroup);
   }
   else if( idField == ifds::ParentFndClsTrdg)
   {
      DString dstrParentFndClsTrdg;
      getField(ifds::ParentFndClsTrdg, dstrParentFndClsTrdg, idDataGroup, false);
      dstrParentFndClsTrdg.strip().upperCase();

      bool bReadonly = false;
      if(dstrParentFndClsTrdg == NA_00)
      {
         setFieldNoValidate(ifds::AssocFund, NULL_STRING, idDataGroup, false);
         setFieldNoValidate(ifds::AssocClass, NULL_STRING, idDataGroup, false);

         clearFieldErrors( ifds::AssocFund, idDataGroup );
         clearFieldErrors( ifds::AssocClass, idDataGroup );

         setFieldValid(ifds::AssocFund, idDataGroup, true);
         setFieldValid(ifds::AssocClass, idDataGroup, true);
      }
   }
/*   else if ( idField == ifds::Currency )
   {
		doCurrencyRelatedChanges(idDataGroup);
   }
*/
   return GETCURRENTHIGHESTSEVERITY();
}

//************************************************************************************
SEVERITY AmsMstrInfo::validateThreshold(const DString& strValue, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("validatePercentage") );
   DString strThreshold( strValue );
   strThreshold.strip();
   if( strThreshold.empty() )
   {
      ADDCONDITIONFROMFILE( CND::ERR_ENTRY_EMPTY_OR_CONTAINS_ONLY_SPACE );
      return(GETCURRENTHIGHESTSEVERITY());
   }

   double dThres = DSTCommonFunctions::convertToDouble(strThreshold);

   if( dThres<0-dSmallValue || dThres > 100+dSmallValue )
      ADDCONDITIONFROMFILE( CND::ERR_VALUE_BETWEEN_0_AND_100 );


   return GETCURRENTHIGHESTSEVERITY();
}

//****************************************************************************************
SEVERITY AmsMstrInfo::validateAMSCode(const DString& strValue, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateAMSCode") );
   DString dstrAmsCode(strValue);
	dstrAmsCode.strip().upperCase();
/*  AMS code 0001 is allowed now 	

  if( dstrAmsCode == I_("0001") &&  isNew() ) //set up AMS code 0001 not allowed
	{
		ADDCONDITIONFROMFILE( CND::ERR_AMS_CODE_SET_UP_0001 );
		return GETCURRENTHIGHESTSEVERITY();
	}
*/

	//AMS code cannot be the same as any fund code in Fund Master

	if ( !_pFundMasterList )
		getFundMasterList();

	if(  _pFundMasterList && _pFundMasterList->IsFundExist( dstrAmsCode, idDataGroup ) )
	{
		 ADDCONDITIONFROMFILE( CND::ERR_INVALID_AMS_CODE );
		 return(GETCURRENTHIGHESTSEVERITY());  
	}

	//HSBC - AMS Enhancement: RebalReq and TargetMixOption field should be read only if Code = 0001
	bool bReadOnly = ( dstrAmsCode == I_("0001") ? true : false );
	if ( bReadOnly ){
		setFieldNoValidate(ifds::TargetMixOption, I_("S"),idDataGroup,false);
		setFieldNoValidate(ifds::RebalReq, I_("N"),idDataGroup,false);
	}
	setFieldReadOnly(ifds::RebalReq,idDataGroup,bReadOnly);
	setFieldReadOnly(ifds::TargetMixOption,idDataGroup,bReadOnly);

/*
	DString dstrAMSType;
	getField(ifds::AMSType,dstrAMSType,idDataGroup,false);
	dstrAMSType.strip().upperCase();

	bool bExist = (dynamic_cast<AMSMstrList*>(getParent()) )->isAMSCodeValid(dstrAMSType,dstrAmsCode, idDataGroup,true );
    if( bExist )
	{
		ADDCONDITIONFROMFILE( CND::ERR_AMS_CODE_SET_UP );	
		return  GETCURRENTHIGHESTSEVERITY();
	}
*/
   return GETCURRENTHIGHESTSEVERITY();
}

//********************************************************************************************
SEVERITY AmsMstrInfo::getAMSFundAllocList( AmsFundAllocList *&pAmsFundAllocList,const BFDataGroupId& idDataGroup,bool bCreate )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("getAMSFundAllocList") );
   pAmsFundAllocList = NULL;

   pAmsFundAllocList = dynamic_cast<AmsFundAllocList*>(getObject( AMSFUNDALLOCATIONLIST, idDataGroup ) );
   if( pAmsFundAllocList || !bCreate )
      return(GETCURRENTHIGHESTSEVERITY());
  
  
   pAmsFundAllocList = new AmsFundAllocList( *this );
   if( isNew()  )
   {
      pAmsFundAllocList->initNew( idDataGroup);
      setObject( pAmsFundAllocList,AMSFUNDALLOCATIONLIST, OBJ_ACTIVITY_NONE, idDataGroup );
   }
   else
   {
      DString strAMSCode, dstrAMSType, dstrEffectiveDate;
      getField(ifds::AMSCode, strAMSCode, idDataGroup, false);
      getField(ifds::AMSType, dstrAMSType, idDataGroup, false );
      getField(ifds::EffectiveDate, dstrEffectiveDate, idDataGroup, false );

      pAmsFundAllocList->setField(ifds::AMSCode, strAMSCode, BF::HOST, false);
      pAmsFundAllocList->setField(ifds::AMSType, dstrAMSType, BF::HOST, false );
      pAmsFundAllocList->setField(ifds::EffectiveDate, dstrEffectiveDate, BF::HOST, false );

      if( pAmsFundAllocList->initExisting() <= WARNING )
         setObject( pAmsFundAllocList, AMSFUNDALLOCATIONLIST, OBJ_ACTIVITY_NONE, BF::HOST );
      else
      {
         delete pAmsFundAllocList;
		 pAmsFundAllocList = NULL;
      }
   }

	return(GETCURRENTHIGHESTSEVERITY());
}

//*******************************************************************************
SEVERITY AmsMstrInfo::getAMSDeltaAllocList(AMSDeltaAllocList *&pAMSDeltaAllocList,const BFDataGroupId& idDataGroup, bool bCreate)
{
  MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getAMSDeltaAllocList" ) );
	
  //pAMSDeltaAllocList = NULL;
  AmsFundAllocList* pAMSFundAllocList = dynamic_cast<AmsFundAllocList*>(getObject(AMSFUNDALLOCATIONLIST, idDataGroup));
  pAMSDeltaAllocList = dynamic_cast<AMSDeltaAllocList*>(getObject( AMSDELTAALLOCLIST, idDataGroup ));

  if(pAMSDeltaAllocList)
    return(GETCURRENTHIGHESTSEVERITY());

  DString strAMSCode, dstrEffectiveDate, dstrAMSDeltaReqUUID; 
  bool bRemoveObj = true; /*In case AMSDeltaAlloc is not found */
  if(!pAMSDeltaAllocList && bCreate)
  {
    getField(ifds::AMSCode, strAMSCode, idDataGroup, false);
    getField(ifds::EffectiveDate, dstrEffectiveDate, idDataGroup, false);
    getField(ifds::AMSDeltaRequestUUID, dstrAMSDeltaReqUUID, idDataGroup, false);
    pAMSDeltaAllocList = new AMSDeltaAllocList(*this);    
    pAMSDeltaAllocList->init(strAMSCode, dstrEffectiveDate, I_("0"), dstrAMSDeltaReqUUID);
		
    BFObjIter iter(*pAMSDeltaAllocList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
    if(!iter.end())
      bRemoveObj = false;

    if (!bRemoveObj)
    {
      BFObjIter fundAllocList(*pAMSFundAllocList,idDataGroup,false,BFObjIter::ITERTYPE::ALL);
      for(fundAllocList.begin();!fundAllocList.end();fundAllocList++)
      {
        DString fundCode,classCode,allocPrcnt,toFundNumber;
        AmsFundAlloc* pAMSFundAlloc = dynamic_cast<AmsFundAlloc*> (fundAllocList.getObject());
        pAMSFundAlloc->getField(ifds::FundCode,fundCode,idDataGroup);
        pAMSFundAlloc->getField(ifds::ClassCode,classCode,idDataGroup);
        pAMSFundAlloc->getField(ifds::ToFundNumber,toFundNumber,idDataGroup);
        pAMSFundAlloc->getField(ifds::AllocPercentage,allocPrcnt,idDataGroup);

        BFObjIter deltaAllocList(*pAMSDeltaAllocList,idDataGroup,false,BFObjIter::ITERTYPE::NON_DELETED);
        for(deltaAllocList.begin();!deltaAllocList.end();!deltaAllocList++)
        {
          DString deltaFund,deltaClass;
          AMSDeltaAlloc* pAMSDeltaAlloc = dynamic_cast<AMSDeltaAlloc*> (deltaAllocList.getObject());
          pAMSDeltaAlloc->getField(ifds::FundCode,deltaFund,idDataGroup);
          pAMSDeltaAlloc->getField(ifds::ClassCode,deltaClass,idDataGroup);

          if(fundCode == deltaFund && classCode == deltaClass)
          {
            pAMSDeltaAlloc->setField(ifds::ToFundNumber,toFundNumber,idDataGroup);
            pAMSDeltaAlloc->setField(ifds::AllocPercentage,allocPrcnt,idDataGroup);
          }
        }
      }      
      setObject(pAMSDeltaAllocList, AMSDELTAALLOCLIST, OBJ_ACTIVITY_NONE, idDataGroup);
    }
    else
    {
      pAMSDeltaAllocList = NULL;
      if(pAMSFundAllocList)
        initAMSDeltaAllocList(pAMSFundAllocList, pAMSDeltaAllocList, idDataGroup);
    }
  }
  return(GETCURRENTHIGHESTSEVERITY());
}

//*******************************************************************************
SEVERITY AmsMstrInfo::initAMSDeltaAllocList(AmsFundAllocList *pAMSFundAllocList, AMSDeltaAllocList *&pAMSDeltaAllocList, const BFDataGroupId& idDataGroup)
{
  MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initAMSDeltaAllocList" ) );
  BFObjIter iter(*pAMSFundAllocList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
  DString AMSCode, accountNum, effectiveDate, status, AMSDeltaRequestUUID;
  getField(ifds::AMSCode,AMSCode,idDataGroup,false);
  getField(ifds::AccountNum,accountNum,idDataGroup,false);
   
  DString currBusDate;
  getWorkSession().getDateInHostFormat(currBusDate, DSTCWorkSession::CURRENT_BUSINESS_DAY, idDataGroup);
   
  pAMSDeltaAllocList = new AMSDeltaAllocList(*this);
  pAMSDeltaAllocList->setField(ifds::AMSCode,AMSCode,idDataGroup);
  pAMSDeltaAllocList->setField(ifds::AccountNum,accountNum,idDataGroup);
  pAMSDeltaAllocList->setField(ifds::EffectiveDate,currBusDate,idDataGroup);

  for( iter.begin();!iter.end();iter++)
  {
    DString dstrToFundNumber,dstrFundCode,dstrClassCode,dstrAllocPrcnt;
    FundAlloc* pFundAlloc = dynamic_cast<FundAlloc*> (iter.getObject());
    pFundAlloc->getField(ifds::FundCode, dstrFundCode, idDataGroup);
    pFundAlloc->getField(ifds::ClassCode, dstrClassCode, idDataGroup);
    pFundAlloc->getField(ifds::ToFundNumber, dstrToFundNumber, idDataGroup);
    pFundAlloc->getField(ifds::AllocPercentage, dstrAllocPrcnt, idDataGroup);
    pAMSDeltaAllocList->doCopyCurrAlloc(dstrToFundNumber, dstrFundCode, dstrClassCode, dstrAllocPrcnt, idDataGroup);
  }
  setObject(pAMSDeltaAllocList, AMSDELTAALLOCLIST, OBJ_ACTIVITY_NONE, idDataGroup);
  return(GETCURRENTHIGHESTSEVERITY());
}

//*******************************************************************************
SEVERITY AmsMstrInfo::doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup )
{ 
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );

	AmsFundAllocList*	pAmsFundAllocList;
	getAMSFundAllocList( pAmsFundAllocList, idDataGroup,false );
	DString strFundAlloc;
    getField(ifds::FundAlloc, strFundAlloc, idDataGroup, false);
	if (pAmsFundAllocList)
	{
		BFObjIter iter( *pAmsFundAllocList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
		if (strFundAlloc == NO )
		{
			if (!iter.end() && !iter.isDummy() )
				ADDCONDITIONFROMFILE( CND::ERR_FUND_ALLOC_SET_UP ); 
		}
		else
		{
			if (iter.end() || iter.isDummy() )
			{
				ADDCONDITIONFROMFILE( CND::ERR_NO_VALID_FUND_ALLOC_RECORD ); 
			}
			else
			{
				pAmsFundAllocList->validateAll(idDataGroup,lValidateGroup);
			}
		}

    DString dstrTargetMixOpt;
    getField(ifds::TargetMixOption, dstrTargetMixOpt, idDataGroup, false);
    if(dstrTargetMixOpt == MarketValueWeight)
    {
      AMSDeltaAllocList* pAMSDeltaAllocList;
      getAMSDeltaAllocList(pAMSDeltaAllocList,idDataGroup);

      bool bIsAMSUpdated = isUpdated(false);
      bool bIsAMSFundUpdated = pAmsFundAllocList->isUpdated();
      if(pAMSDeltaAllocList && (bIsAMSUpdated || bIsAMSFundUpdated))
      {
        setObject(NULL, AMSDELTAALLOCLIST, OBJ_ACTIVITY_NONE, idDataGroup);
      }
    }
  }	
  return(GETCURRENTHIGHESTSEVERITY());
}

//***************************************************
SEVERITY AmsMstrInfo::validateFundAlloc(const DString& strValue, const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateFundAlloc") );
	DString dstrFundAlloc(strValue);
	dstrFundAlloc.strip().upperCase();
	if (dstrFundAlloc == NO)
	{
		AmsFundAllocList* pAmsFundAllocList;
		getAMSFundAllocList(pAmsFundAllocList,idDataGroup,false);
		if (pAmsFundAllocList) {
			BFObjIter iter( *pAmsFundAllocList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
			if (!iter.end() && !iter.isDummy())
				ADDCONDITIONFROMFILE( CND::ERR_FUND_ALLOC_SET_UP ); 
		}
	}
	return GETCURRENTHIGHESTSEVERITY();
}

//*******************************************************************************
void AmsMstrInfo::doInitWithDefaultValues( const BFDataGroupId& idDataGroup )
{
	DString dstrAMSType;
	getField(ifds::AMSType,dstrAMSType,idDataGroup,false );
	dstrAMSType.strip();
	if( dstrAMSType == NULL_STRING)
	{
		dstrAMSType = (( AMSMstrList *)getParent() )->getCurrentAMSType();
		setFieldNoValidate(ifds::AMSType,dstrAMSType,idDataGroup,false );
		setFieldNoValidate(ifds::AMSType,dstrAMSType,BF::HOST,false );

	}
	DString dstrCurDate;
   getWorkSession().getMgmtCoOptions()->getField( ifds::CurrBusDate, dstrCurDate, idDataGroup ,false );
   setFieldNoValidate( ifds::EffectiveDate, dstrCurDate, idDataGroup, false );
	
   DString dstrDispRBL;
   getWorkSession().getMgmtCoOptions()->getField( ifds::DispRBLSysThrshld, dstrDispRBL, idDataGroup ,false );
	DString defValue = I_("0.0");
	dstrDispRBL.strip();
	if(dstrDispRBL == YES )
	{
		getWorkSession().getMgmtCoOptions()->getField( ifds::RBLThrshldDflt, defValue, idDataGroup ,false );	
	}
	formatField( ifds::Percentage, defValue,  idDataGroup );
   setFieldNoValidate( ifds::Percentage, defValue, idDataGroup, true );
	setFieldStates( idDataGroup);
	setFieldNoValidate(ifds::FundAlloc, YES, idDataGroup, false);
	setFieldNoValidate(ifds::DefaultAlloc, NO, idDataGroup, false);
//	setFieldNoValidate(ifds::Name, NULL_STRING, idDataGroup, false);

	setFieldNoValidate(ifds::WireEleg, YES, idDataGroup, false);
	if ( dstrAMSType == REBALANCE )
	{
		DString dstrDefFund, dstrDefClass, dstrFreq;
		getWorkSession().getMgmtCoOptions()->getField( ifds::DefaultRoundFund, 
				dstrDefFund, idDataGroup ,false );	
		getWorkSession().getMgmtCoOptions()->getField( ifds::DefaultRoundClass, 
				dstrDefClass, idDataGroup ,false );	
		getWorkSession().getMgmtCoOptions()->getField( ifds::DefaultRebFreq, 
				dstrFreq, idDataGroup ,false );	

		setFieldNoValidate(ifds::RoundingFund, dstrDefFund, idDataGroup, false);
		setFieldNoValidate(ifds::RoundingClass, dstrDefClass, idDataGroup, false);
		setFieldNoValidate(ifds::SchedSetupFreqID, dstrFreq, idDataGroup, false);
		setFieldValid(ifds::ForeignRelFundClass, idDataGroup, false);
		setFieldValid(ifds::RoundingFundClass, idDataGroup, false);

	}
	
	DString dstrDate;
	getWorkSession().getDateInHostFormat(dstrDate, DSTCWorkSession::DATE_TYPE::DAY12319999, idDataGroup);

	setFieldNoValidate(ifds::GrandFatheredDate, dstrDate, idDataGroup, false);
   setFieldReadOnly( ifds::GrandFatheredDate, idDataGroup, true );
	setFieldNoValidate(ifds::LastRebDate, dstrDate, idDataGroup, false);

}

//*******************************************************************************
bool AmsMstrInfo::isLastBusDayOfWeek ( const DString& strValue, const BFDataGroupId& idDataGroup )
{
   DString dstrDateIn(strValue);
   BFDate::DATE_FORMAT fmt = BFDate::inferFormat( dstrDateIn.c_str() );
   assert( fmt != BFDate::DF_NULL );
   BFDate dateIn( dstrDateIn.c_str(), fmt );
   int iwd = dateIn.getWeekDay();
   if (iwd == 5)
	   return true;
   else if ( iwd == 4 )
   {
		dateIn.addDays( 1 );
		return (!isBusinessDate(dateIn.get (fmt), idDataGroup));
   }
   else
	   return false;

}

//*******************************************************************************
//Modify the Effective date to earlier then the original effective date is not allowed (existing CIBC rule) for existing record
SEVERITY AmsMstrInfo::validateEffectiveDate(const DString& strValue, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateEffectiveDate" ) );

   DString dstrEffectiveDate(strValue);
   dstrEffectiveDate.strip();
   
   DString dstrCurrBusDate;
   getWorkSession().getOption (ifds::CurrBusDate, dstrCurrBusDate, idDataGroup, false);

   if (DSTCommonFunctions::CompareDates (dstrEffectiveDate, dstrCurrBusDate) == DSTCommonFunctions::FIRST_EARLIER)
    {
		getErrMsg (IFASTERR::ACCT_LVL_EFFECTIVE_DATE,
                             CND::ERR_EFFECTIVE_DATE_BEFORE_CURBUSDATE,
                             CND::WARN_EFFECTIVE_DATE_BEFORE_CURBUSDATE,
                             idDataGroup);
    }

	return GETCURRENTHIGHESTSEVERITY();
}

//*******************************************************************************
// ForeignRelFund must be a valid fund as of the Effective date of the AMS
// ForeignRelFund must be a Domestic fund. 
SEVERITY AmsMstrInfo::validateForeignRelFund(const DString& strValue,const BFDataGroupId& idDataGroup )
{

	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateForeignRelFund" ) );

	DString dstrForeignRelFund(strValue);
	dstrForeignRelFund.strip();

	if ( validateFundCode( dstrForeignRelFund.strip(), idDataGroup ) <= WARNING  &&
		!(dstrForeignRelFund.empty()) )
	{

	   if ( !isDomesticFund(dstrForeignRelFund, idDataGroup) )
	   {
			ADDCONDITIONFROMFILE( CND::ERR_DOMESTIC_FUND_ONLY );
			return GETCURRENTHIGHESTSEVERITY();
	   }

   }
   return GETCURRENTHIGHESTSEVERITY();
}

//*******************************************************************************
SEVERITY AmsMstrInfo::validateAssocFund(const DString& strValue,const BFDataGroupId& idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateRoundingFund" ) );

	DString dstrRoundingFund(strValue);
   validateFundCode( dstrRoundingFund.strip(), idDataGroup );

	return GETCURRENTHIGHESTSEVERITY();
}

//*******************************************************************************
// RoundingFund must be a valid fund as of the Effective date of the AMS
SEVERITY AmsMstrInfo::validateRoundingFund(const DString& strValue,const BFDataGroupId& idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateRoundingFund" ) );

	DString dstrRoundingFund(strValue);
    validateFundCode( dstrRoundingFund.strip(), idDataGroup );
	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY AmsMstrInfo::validateFundClass( const DString& dstrFundCode, const DString& dstrClassCode, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateFundClass" ) );

   if ( dstrFundCode.empty() ||  dstrClassCode.empty() )
   {
		return GETCURRENTHIGHESTSEVERITY();
   }

   FundDetailList *pFundDetailList = NULL;
   if ( getMgmtCo().getFundDetailList(pFundDetailList) <= WARNING && pFundDetailList )
   {
      FundDetail *pFundDetail = NULL;
      if( pFundDetailList->getFundDetail( dstrFundCode, dstrClassCode, idDataGroup, pFundDetail ) == false )
      {
         ADDCONDITIONFROMFILE( CND::ERR_INVALID_FUND_CLASS_CODES );
      }
      else
      {
         DString dstrEffectiveDate;
         getField( ifds::EffectiveDate, dstrEffectiveDate, idDataGroup, false );
		 
		 if( pFundDetailList->IsFundValidAtDate ( dstrFundCode, dstrClassCode, dstrEffectiveDate, idDataGroup) == false )
		 {
			DString idiStr, FundCodeCopy( dstrFundCode ), ClassCodeCopy( dstrClassCode );
			addIDITagValue( idiStr, I_( "FUNDNAME" ),  FundCodeCopy.strip() );
			addIDITagValue( idiStr, I_( "CLASSNAME" ), ClassCodeCopy.strip() );
			ADDCONDITIONFROMFILEIDI( CND::ERR_FUND_CLASS_NOT_EFFECTIVE, idiStr );
		 }
	 
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());  
}

//******************************************************************************
SEVERITY AmsMstrInfo::validateFundCode( const DString& dstrFundCode, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateFundCode" ) );

	if ( dstrFundCode.empty() )
		return(GETCURRENTHIGHESTSEVERITY());

	if ( !_pFundMasterList && !getFundMasterList () )
	{
		return(GETCURRENTHIGHESTSEVERITY());  
	}

	if( _pFundMasterList->IsFundExist( dstrFundCode, idDataGroup ) == false )
	{
		 ADDCONDITIONFROMFILE( CND::ERR_INVALID_FUND_CLASS_CODES );
		 return(GETCURRENTHIGHESTSEVERITY());  
	}
	else  //if fund does exists
	{
		 DString dstrEffectiveDate;
		 getField( ifds::EffectiveDate, dstrEffectiveDate, idDataGroup, false );
		 if( _pFundMasterList->IsFundValidAtDate ( dstrFundCode, dstrEffectiveDate, idDataGroup) == false )
		 {
			DString idiStr, FundCodeCopy( dstrFundCode );
			addIDITagValue( idiStr, I_( "FUNDNAME" ),  FundCodeCopy.strip() );
			ADDCONDITIONFROMFILEIDI( CND::ERR_FUND_NOT_EFFECTIVE, idiStr );
			return(GETCURRENTHIGHESTSEVERITY());  
		 }
	}

   return(GETCURRENTHIGHESTSEVERITY());  
}


//******************************************************************************
SEVERITY AmsMstrInfo::validateRelFundClass( const DString& strValue, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateRelFundClass" ) );
   DString dstrRelFund, dstrRelClass;
   getField ( ifds::ForeignRelFund, dstrRelFund, idDataGroup, false );
   getField ( ifds::ForeignRelClass, dstrRelClass, idDataGroup, false );
   dstrRelFund.strip();
   dstrRelClass.strip().upperCase();
   if (  dstrRelFund.empty() && dstrRelClass.empty() )
   {
		DString dstrErrValue;
		getErrMsgValue( ERR_EXC_FUND_REQUIRED, idDataGroup, dstrErrValue );
		if ( dstrErrValue == I_("E") )
		{
			ADDCONDITIONFROMFILE( CND::ERR_FOREIGN_FUND_CLASS_REQUIRED );
			return GETCURRENTHIGHESTSEVERITY();
		}
		else if (dstrErrValue == I_("W") )
		{
			ADDCONDITIONFROMFILE( CND::ERR_WARN_FOREIGN_FUND_CLASS_REQUIRED );
		}

   }
   else if ( dstrRelFund.empty() || dstrRelClass.empty() )
   {	//fund/class must both blank
		ADDCONDITIONFROMFILE( CND::ERR_INVALID_FUND_CLASS_CODES );
		return(GETCURRENTHIGHESTSEVERITY());  

   }
   else
   {
      if( validateFundClass( dstrRelFund, dstrRelClass, idDataGroup ) <= WARNING ) 
      {
	      if ( !isDomesticFund( dstrRelFund, idDataGroup) )
	      {
			   ADDCONDITIONFROMFILE( CND::ERR_DOMESTIC_FUND_ONLY );
            return( GETCURRENTHIGHESTSEVERITY() );
	      }

         if( !isFundInAMS( dstrRelFund, dstrRelClass, idDataGroup ) )
         {
		      ADDCONDITIONFROMFILE( CND::ERR_FUND_CLASS_NOT_IN_PORTFOLIO );
         }
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY AmsMstrInfo::validateRoundingFundClass( const DString& strValue, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateRelFundClass" ) );
   DString dstrRoundFund, dstrRoundClass;
   getField ( ifds::RoundingFund, dstrRoundFund, idDataGroup, false );
   getField ( ifds::RoundingClass, dstrRoundClass, idDataGroup, false );
   dstrRoundFund.strip();
   dstrRoundClass.strip().upperCase();
   if (  dstrRoundFund.empty() || dstrRoundClass.empty() )
   {
		DString dstrErrValue;
		getErrMsgValue( ERR_ROUND_FUND_REQUIRED, idDataGroup, dstrErrValue );
		if ( dstrErrValue == I_("E") )
		{
			ADDCONDITIONFROMFILE( CND::ERR_ROUND_FUND_CLASS_REQUIRED );
			return GETCURRENTHIGHESTSEVERITY();
		}
		else if ( dstrErrValue == I_("I") )
		{
			return GETCURRENTHIGHESTSEVERITY();
		}
		else if (dstrErrValue == I_("W") )
		{
			ADDCONDITIONFROMFILE( CND::ERR_WARN_ROUND_FUND_CLASS_REQUIRED );
		}

   }
	
   validateFundClass( dstrRoundFund, dstrRoundClass, idDataGroup );

	DString dstrGlobalLevelAssetMixApplicable;
	getField( ifds::FundAlloc, dstrGlobalLevelAssetMixApplicable, idDataGroup );
	if ( I_( "Y" ) == dstrGlobalLevelAssetMixApplicable.strip().upperCase() &&
		  !isFundInAMS( dstrRoundFund, dstrRoundClass, idDataGroup ) )
	{
		ADDCONDITIONFROMFILE( CND::ERR_AMS_GLOBAL_ROUNDING_FUND_CLASS_NOT_IN_AMS_MIX );
	}

   return(GETCURRENTHIGHESTSEVERITY());

}

//******************************************************************************
SEVERITY AmsMstrInfo::validateAssocFundClass( const DString& strValue, 
                                              const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateAssocFundClass" ) );

   DString dstrAssocFund, dstrAssocClass;
   getField ( ifds::AssocFund,  dstrAssocFund,  idDataGroup, false );
   getField ( ifds::AssocClass, dstrAssocClass, idDataGroup, false );
   dstrAssocFund.strip();
   dstrAssocClass.strip().upperCase();

   validateFundClass( dstrAssocFund, dstrAssocClass, idDataGroup );

   // Associated Fund/Class have to be eligible for FOF
   FundDetailList *pFundDetailList = NULL;
   if ( getMgmtCo().getFundDetailList(pFundDetailList) <= WARNING && pFundDetailList )
   {
      FundDetail *pFundDetail = NULL;
      if( pFundDetailList->getFundDetail( dstrAssocFund, dstrAssocClass, idDataGroup, pFundDetail ) &&
          NULL != pFundDetail )
      {
         DString strMstrActActive, strParentFndClsTrdg, strAMSModelType;
         getWorkSession().getOption (ifds::MstrActActive, strMstrActActive, idDataGroup, false);
         getField( ifds::ParentFndClsTrdg, strParentFndClsTrdg, idDataGroup, false);
         pFundDetail->getField( ifds::AMSModelType, strAMSModelType, idDataGroup, false);

         strMstrActActive.strip().upperCase();
         strParentFndClsTrdg.strip().upperCase();
         strAMSModelType.strip().upperCase();

         if(strParentFndClsTrdg == I_("01"))
         {
            if(strAMSModelType != I_("01"))
            {
               // raise up error because, fund is not parent fund
               getErrMsg (IFASTERR::FUND_CLASS_MUST_BE_AMS_PARENT_FUND,
                          CND::ERR_FUND_CLASS_MUST_BE_AMS_PARENT_FUND,
                          CND::WARN_FUND_CLASS_MUST_BE_AMS_PARENT_FUND,
                          idDataGroup);
               //ADDCONDITIONFROMFILE( CND::ERR_FUND_CLASS_MUST_BE_AMS_PARENT_FUND );
            }
         }
         else
         {
         if ( !pFundDetailList->isFOFFund( dstrAssocFund, dstrAssocClass, idDataGroup ) )
            ADDCONDITIONFROMFILE( CND::ERR_AMS_FUND_CLASS_NOT_VALID_FOR_FOF );
      }
   }     
   }
	
	return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
bool AmsMstrInfo::isDomesticFund( const DString& dstrFundCode, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "isDomesticFund" ) );

   FundMaster *pFundMaster = NULL;
   DString dstrDomestic = NULL_STRING;
   _pFundMasterList->getFundMaster (dstrFundCode, idDataGroup, pFundMaster);
   if( pFundMaster )
   {
	   
	   pFundMaster->getField ( ifds::Domestic, dstrDomestic, idDataGroup, false );
   }
   return ( dstrDomestic == YES );

}

//******************************************************************************
bool AmsMstrInfo::getFundMasterList () 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getFundMasterList" ) );

   if( !_pFundMasterList )
   {
      getMgmtCo().getFundMasterList( _pFundMasterList );
   }

   if( _pFundMasterList )
   {
      return(true);
   }
   else
   {
      return(false);
   }
}

//*******************************************************************************
//NextRebDate must be on a business date
//Next rebalance date must be earlier than the last rebalancing date.
//Next reblance date must not be less than the current business date for existing AMS code.
//Next rebalance date must be greater than current business date if it is a new AMS code.
//Next Rebalance Date can not be earlier than the effective date of ams master record
//Edit check to provide warning if the Next rebalancing date is not the last busniess day of a week.
SEVERITY AmsMstrInfo::validateNextRebDate(const DString& strValue, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateNextRebDate" ) );

   DString dstrNextRebDate(strValue), dstrLastRebDate, dstrCurBusDate;
   dstrNextRebDate.strip();

   if ( DSTCommonFunctions::CompareDates( DEFAULT_DATE, dstrNextRebDate ) == DSTCommonFunctions::EQUAL )
		return NO_CONDITION;

   getField(ifds::LastRebDate, dstrLastRebDate, idDataGroup, false);
   dstrLastRebDate.strip();
   if ( !dstrLastRebDate.empty() && DSTCommonFunctions::CompareDates( dstrNextRebDate, dstrLastRebDate ) != DSTCommonFunctions::FIRST_EARLIER )
   {
      ADDCONDITIONFROMFILE( CND::ERR_DATE_CANNOT_GREATER_THAN_LAST_REB_DATE );
      return GETCURRENTHIGHESTSEVERITY();
   }

   DString dstrLastEffectiveDate;
   getField(ifds::LastEffectiveDate,dstrLastEffectiveDate, idDataGroup, false);
   dstrLastEffectiveDate.strip();
   getWorkSession().getOption( ifds::CurrBusDate, dstrCurBusDate, idDataGroup, false );
   if ( !dstrLastEffectiveDate.empty() )
   {
	   if ( DSTCommonFunctions::CompareDates( dstrNextRebDate, dstrCurBusDate ) == DSTCommonFunctions::FIRST_EARLIER )
	   {
		  ADDCONDITIONFROMFILE( CND::ERR_DATE_CANNOT_EARLIER_THAN_CURRENT_BUSINESS_DATE );
		  return GETCURRENTHIGHESTSEVERITY();
	   }

   }
   else
   {
	   if ( DSTCommonFunctions::CompareDates( dstrCurBusDate, dstrNextRebDate ) != DSTCommonFunctions::FIRST_EARLIER )
	   {
		  ADDCONDITIONFROMFILE( CND::ERR_DATE_CANNOT_EARLIER_THAN_CURRENT_BUSINESS_DATE );
		  return GETCURRENTHIGHESTSEVERITY();
	   }

   }

   //Next Rebalance Date can not be earlier than the effective date of ams master record
   DString dstrEffectiveDate;
   getField(ifds::EffectiveDate, dstrEffectiveDate, idDataGroup);
   if( DSTCommonFunctions::CompareDates( dstrNextRebDate, dstrEffectiveDate ) 
       != DSTCommonFunctions::SECOND_EARLIER )
   {
      ADDCONDITIONFROMFILE( CND::ERR_NEXT_REB_DATE_CANNOT_EARLIER_THAN_EFFECTIVE_DATE );
   }


   if ( !isBusinessDate(strValue, idDataGroup) )
   {
		  DString idiStr;
//		  DString dstrNextRebDate1;
//		  getField(ifds::NextRebDate,dstrNextRebDate1,idDataGroup,true);

		  addIDITagValue( idiStr, I_("FIELDNAME"), I_("Next Rebalance Date" ));
		  ADDCONDITIONFROMFILEIDI( CND::ERR_DATE_MUST_BE_BUSINESS_DATE, idiStr );  
 		  return GETCURRENTHIGHESTSEVERITY();
 

   }

   if ( !isLastBusDayOfWeek(strValue, idDataGroup))
   {
		ADDCONDITIONFROMFILE( CND::ERR_DATE_NOT_LAST_BUSINESS_DAY_OF_WEEK ); 

   }

   return GETCURRENTHIGHESTSEVERITY();
}

//***********************************************************************************************
//must be a business date
//Input grandfather date must be greater or equal to the current business date.
//User can modify the Grandfather date to future date but cannot be back dated it. 
//Input grandfather date must be greater than the effective date
SEVERITY AmsMstrInfo::validateGrandFatherDate(const DString& strValue, const BFDataGroupId& idDataGroup )
{
    MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateGrandFatherDate" ));

	DString dstrGFDate(strValue), dstrCurBusDate, dstrEffectiveDate;

	if ( DSTCommonFunctions::CompareDates( DEFAULT_DATE, dstrGFDate ) == DSTCommonFunctions::EQUAL )
		return NO_CONDITION;

    getWorkSession().getOption( ifds::CurrBusDate, dstrCurBusDate, idDataGroup, false );

    if ( DSTCommonFunctions::CompareDates( dstrCurBusDate, dstrGFDate ) == DSTCommonFunctions::SECOND_EARLIER )
    {
		  ADDCONDITIONFROMFILE( CND::ERR_DATE_CANNOT_EARLIER_THAN_CURRENT_BUSINESS_DATE );
		  return GETCURRENTHIGHESTSEVERITY();

	}
	if ( _initGrandFatherDate != NULL_STRING && 
		 DSTCommonFunctions::CompareDates(dstrGFDate,_initGrandFatherDate ) == DSTCommonFunctions::FIRST_EARLIER )
    {
		ADDCONDITIONFROMFILE( CND::ERR_GRAND_FATHER_DATE_BACKWARD ); 
		return GETCURRENTHIGHESTSEVERITY();

    }


	if ( !isBusinessDate(strValue, idDataGroup) )
	{
		  DString idiStr;
		  DString dstrGFDate1;
//		  getField(ifds::GrandFatheredDate,dstrGFDate1,idDataGroup,true);

		  addIDITagValue( idiStr, I_("DATE"), I_("GrandFather Date") );
		  ADDCONDITIONFROMFILEIDI( CND::ERR_BUSINESS_DATE_ONLY, idiStr );  
 		  return GETCURRENTHIGHESTSEVERITY();

	}

   //The below code has been commented out for the following reason.
   //PTS 10023506 - CIBC AMS EBS 1.6 (3.1.5) 
   //Disallow transfers/exchanges in. Allow a transfer from one account to another account 
   //where the other account has a grandfathered portfolio. 

	//validateAMSRuleType(strValue, idDataGroup);
	return GETCURRENTHIGHESTSEVERITY();

}

//***********************************************************************************************
//GrandFathered Date must greater than effective date of the AMS record.
SEVERITY AmsMstrInfo::validateEffectiveGFDate(const DString& strValue, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateEffectiveGFDate" ));
   DString EffectiveDate, GFDate;
   getField(ifds::EffectiveDate, EffectiveDate, idDataGroup);
   getField(ifds::GrandFatheredDate, GFDate, idDataGroup);
   if( DSTCommonFunctions::CompareDates( GFDate, EffectiveDate ) 
       != DSTCommonFunctions::SECOND_EARLIER )   
   {
      ADDCONDITIONFROMFILE( CND::ERR_GRAND_FATHER_DATE_CANNOT_EARLIER_THAN_EFFECTIVE_DATE );
   }
   
   return GETCURRENTHIGHESTSEVERITY();

}

//***********************************************************************************************
SEVERITY AmsMstrInfo::DupCheck4AmsRec( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("DupCheck4AmsRec" ));

	DString dstrAMSType, dstrAMSCode, dstrEffectiveDate;
	getField(ifds::AMSType,dstrAMSType,idDataGroup,false);
	dstrAMSType.strip().upperCase();
	getField(ifds::AMSCode,dstrAMSCode,idDataGroup,false);
	dstrAMSCode.strip();
	getField(ifds::EffectiveDate,dstrEffectiveDate,idDataGroup,false);
	dstrEffectiveDate.strip();

	bool bExist = (dynamic_cast<AMSMstrList*>(getParent()) )->isAMSCodeValid(dstrAMSType,dstrAMSCode, dstrEffectiveDate, idDataGroup, true);
	if ( bExist )
	{
		ADDCONDITIONFROMFILE( CND::ERR_AMS_CODE_SET_UP );
	}
	else
	{
		bool bEnd = (dynamic_cast<AMSMstrList*>(getParent()) )->isAMSCodeEnd(dstrAMSType,dstrAMSCode, dstrEffectiveDate, idDataGroup);
		if ( bEnd )	
		{
			ADDCONDITIONFROMFILE( CND::ERR_AMS_CODE_SET_UP );
		}

	}
	 
	return GETCURRENTHIGHESTSEVERITY();
}

//***********************************************************************************************
bool AmsMstrInfo::isBusinessDate( const DString& strValue, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("isBusinessDate" ));
   
   DateValidation* _dateValidation = new DateValidation ( *this );

   DString fundCode = NULL_STRING,classCode = NULL_STRING;
   DString effectiveDate(strValue);
   effectiveDate.stripAll();
   DString validationType(BUSINESS_DATE);
	
	SEVERITY sevRtn = _dateValidation->init(validationType,  //validationType 
														 NULL_STRING,		//tradeDate
														 NULL_STRING,		//settleDate
														 effectiveDate,	//depositDate
														 NULL_STRING,		//valueDate
														 NULL_STRING,		//transType
														 NULL_STRING,		//payType
														 NULL_STRING,		//broker
														 fundCode,			//fundCode
														 classCode,			//classCode
														 NULL_STRING,		//toFund
														 NULL_STRING,		//toClass
														 NO,					//orderType
														 NULL_STRING,		//dealDate
														 NULL_STRING,		//dealTime
														 NULL_STRING,		//settleCurrency
														 NULL_STRING,		//amount
														 NULL_STRING,		//amountType
														 NULL_STRING,     //settleInDate
														 NULL_STRING,	   //brokerTo
                                           NULL_STRING,     //accountNum,
                                           NULL_STRING,     //accountNumTo,
                                           NULL_STRING,     //fromCurrency,
                                           NULL_STRING,     //toCurrency,
                                           I_("N"),         //Track,
                                           NULL_STRING);    //PageName




  /* SEVERITY sevRtn = _dateValidation->init(	 fundCode
											,classCode
											,NULL_STRING
											,NULL_STRING
											,validationType 
											,NULL_STRING 
											,NULL_STRING
											,effectiveDate
											,NULL_STRING 
											,NULL_STRING  
											,NO 
											,NULL_STRING 
											,NULL_STRING 
											,NULL_STRING 
											,NULL_STRING  
											,NULL_STRING 
											,NULL_STRING  
											,NULL_STRING 
											 );*/
   if ( sevRtn > WARNING )
   {

      delete _dateValidation;
      return false; 
   }

   DString dstrBusDate;
   _dateValidation->getField(ifds::EffectiveDate,dstrBusDate,idDataGroup,false);
   dstrBusDate.stripAll();
   delete _dateValidation;
   return ( dstrBusDate.empty() );
}

//***********************************************************************************************
SEVERITY AmsMstrInfo::getAmsLmtOverrideList( AmsLmtOverrideList *& pAmsLmtOverrideList,
                                             const BFDataGroupId& idDataGroup,
                                             bool bInq,
                                             bool bRemObj,
                                             bool bCreateNew)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getAmsLmtOverrideList" ) );

   if( bRemObj )
   {
      setObject( NULL, AMS_LMTOVERRIDE_LIST, OBJ_ACTIVITY_NONE, BF::HOST ); 
   }

   pAmsLmtOverrideList = dynamic_cast<AmsLmtOverrideList*>(getObject( AMS_LMTOVERRIDE_LIST, idDataGroup ));
   if( !pAmsLmtOverrideList )
   {
	   if( bInq )
	   {
			DString strAmsCode, strEffectiveDate, strAmsType;
			getField(ifds::AMSCode, strAmsCode, idDataGroup, false);
			getField(ifds::EffectiveDate, strEffectiveDate, idDataGroup, false);
			getField(ifds::AMSType, strAmsType, idDataGroup, false);
         // Bug Fix - Adding a new AMS record without accessing the limitations
         // CBO.  Error showed up after confirmation from view 262 stating that
         // ams code does not exists.  AMS Record is updated properly even with error.
         // AMS Limitations view call (262) should not be called on new AMS Code.
         pAmsLmtOverrideList = new AmsLmtOverrideList( *this );
         if ( !isNew() ) {			   
            pAmsLmtOverrideList->init( strAmsCode, strEffectiveDate, strAmsType );
         }
	   }
	   if (bCreateNew)
	   {
			pAmsLmtOverrideList = new AmsLmtOverrideList( *this );
	   }

	   if( pAmsLmtOverrideList )
       {
			if( GETCURRENTHIGHESTSEVERITY() <= WARNING )
			{
          		setObject( pAmsLmtOverrideList, AMS_LMTOVERRIDE_LIST, OBJ_ACTIVITY_NONE, idDataGroup );   
			}
			else
			{
				delete pAmsLmtOverrideList;
				pAmsLmtOverrideList = NULL;
			}
		}
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//***********************************************************************************************
void AmsMstrInfo::doRBFreqRelatedChanges(const BFDataGroupId& idDataGroup)
{
      MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doRBFreqRelatedChanges" ) );

      DString dstrFreq;
      getField(ifds::SchedSetupFreqID, dstrFreq, idDataGroup, false);
      dstrFreq.strip();
	  bool bRequired = ( dstrFreq == FREQ_WEEKLY || dstrFreq == FREQ_BIWEEKLY );
	  setFieldRequired(ifds::DayOfWeek, idDataGroup, bRequired);
	  setFieldValid(ifds::DayOfWeek, idDataGroup, !bRequired);
	  if ( !bRequired )
	  {
			setFieldNoValidate(ifds::DayOfWeek, NULL_STRING, idDataGroup, false, true, true);
			
	  }
	  setFieldReadOnly(ifds::DayOfWeek,idDataGroup,!bRequired);

	 // After a valid frequency code is selected and is different from the original value,
	// automatically calculate the next rebalance date based on the last rebalance date value.
	  if ( dstrFreq != _initFreq )
	  {
			CalculateNextRebDate(idDataGroup);
	  }
	  else
	  {
			setFieldNoValidate(ifds::NextRebDate, _initNextRebDate, idDataGroup, false, true, true);

	  }
}

//***********************************************************************************************
void AmsMstrInfo::doCurrencyRelatedChanges(const BFDataGroupId& idDataGroup)
{
	DString dstrCurrency, dstrSysCurrency; 
	getField(ifds::Currency, dstrCurrency, idDataGroup, false );
	dstrCurrency.strip().upperCase();
	getWorkSession().getMgmtCoOptions()->getField( ifds::SysCurrency, dstrSysCurrency, idDataGroup ,false );
	dstrSysCurrency.strip().upperCase();
	bool bRequired = ( !dstrCurrency.empty() && dstrCurrency != dstrSysCurrency );
	setFieldRequired(ifds::ForeignRelFund, idDataGroup, bRequired);
	setFieldRequired(ifds::ForeignRelClass, idDataGroup, bRequired);
	setValidFlag(ifds::ForeignRelFund, idDataGroup, !bRequired);
	setValidFlag(ifds::ForeignRelClass, idDataGroup, !bRequired);

}

//***********************************************************************************************
// we are in the target item
void AmsMstrInfo::ModelAMS(AmsMstrInfo *Model, const BFDataGroupId& idDataGroup)
{
   BFData *tmp = new BFData(ifds::DSTC0179_VWRepeat_Record);

   BFDataFieldIter dIter( *tmp );

   DString str;

   for( ;dIter; ++dIter )
   {
      const BFFieldId& idField = dIter().getId();
	  //don't copy EffectiveDate, effectivedate should be default to current business date
	  //don't copy AmsRecId, it should be unique.
	  //don't copy Username, ModUser, ModDate, and Processdate
	  //don't copy AMSCodeInUse, LastEffectiveDate 
      if(	 idField != ifds::EffectiveDate  
		  && idField != ifds::AMSRecId 
		  && idField != ifds::Username
		  && idField != ifds::ModUser 
		  && idField != ifds::ModDate
		  && idField != ifds::ProcessDate
		  && idField != ifds::AMSCodeInUse
		  && idField != ifds::LastEffectiveDate
		  && idField != ifds::LastRebDate
		  && idField != ifds::NextRebDate
		 )
	  {
		 Model->getField( idField, str, idDataGroup, false );
		 if ( idField == ifds::DayOfWeek  && ( DSTCommonFunctions::convertToDouble( str ) == 0 ) )
			setField(idField, NULL_STRING, idDataGroup, false);
		 else
			setField(idField, str, idDataGroup, false);
	  }
   };

   delete tmp;

   getWorkSession().getDateInHostFormat(str, DSTCWorkSession::DATE_TYPE::CURRENT_BUSINESS_DAY, idDataGroup);
   setField(ifds::EffectiveDate, str, idDataGroup, false);

   AmsLmtOverrideList *pAmsLmtOverrideList, *pModelAmsLmtOverrideList;
   Model->getAmsLmtOverrideList( pModelAmsLmtOverrideList, idDataGroup);

   if( pModelAmsLmtOverrideList )
   {
      getAmsLmtOverrideList( pAmsLmtOverrideList, idDataGroup, false, false, true );
      pAmsLmtOverrideList->ModelAMS(pModelAmsLmtOverrideList, idDataGroup);
   }

}

//*******************************************************************************
SEVERITY AmsMstrInfo::canPurchase( const DString& dstrTaxJuris, const DString& dstrProvResid,
                                   const DString& dstrAccountType, const DString& dstrTaxType,
                                   const DString& dstrAcctDesign, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("canPurchase") );
   AmsLmtOverrideList* pAMSLmtOverrideList;
   getAmsLmtOverrideList ( pAMSLmtOverrideList, idDataGroup );
   if ( pAMSLmtOverrideList )
      pAMSLmtOverrideList->canPurchase ( dstrTaxJuris, dstrProvResid, dstrAccountType,
                     dstrTaxType, dstrAcctDesign, idDataGroup );
   return GETCURRENTHIGHESTSEVERITY();
}

//*******************************************************************************
SEVERITY AmsMstrInfo::minPurchase( const DString& dstrTaxJuris, const DString& dstrProvResid,
                                   const DString& dstrAccountType, const DString& dstrTaxType,
                                   const DString& dstrAcctDesign, const DString& dstrAmount,
                                   bool& bFundOverride, bool bInitialPurchase,
                                   const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("minPurchase") );
   AmsLmtOverrideList* pAMSLmtOverrideList;
   getAmsLmtOverrideList ( pAMSLmtOverrideList, idDataGroup );
   if ( pAMSLmtOverrideList )
      pAMSLmtOverrideList->minPurchase ( dstrTaxJuris, dstrProvResid, dstrAccountType,
                     dstrTaxType, dstrAcctDesign, dstrAmount, bFundOverride, bInitialPurchase, idDataGroup );

   return GETCURRENTHIGHESTSEVERITY();
}

//*******************************************************************************
SEVERITY AmsMstrInfo::maxRedeem( const DString& dstrTaxJuris, const DString& dstrProvResid,
                                   const DString& dstrAccountType, const DString& dstrTaxType,
                                   const DString& dstrAcctDesign, const double dPercent,
                                   bool& bFundOverride, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("maxRedeem") );
   AmsLmtOverrideList* pAMSLmtOverrideList;
   getAmsLmtOverrideList ( pAMSLmtOverrideList, idDataGroup );
   if ( pAMSLmtOverrideList )
      pAMSLmtOverrideList->maxRedeem ( dstrTaxJuris, dstrProvResid, dstrAccountType,
                     dstrTaxType, dstrAcctDesign, dPercent, bFundOverride, idDataGroup );
 
   return GETCURRENTHIGHESTSEVERITY();
}

//*******************************************************************************
SEVERITY AmsMstrInfo::canRedeem( const DString& dstrTaxJuris, const DString& dstrProvResid,
                                   const DString& dstrAccountType, const DString& dstrTaxType,
                                   const DString& dstrAcctDesign, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("canRedeem") );
   AmsLmtOverrideList* pAMSLmtOverrideList;
   getAmsLmtOverrideList ( pAMSLmtOverrideList, idDataGroup );
   if ( pAMSLmtOverrideList )
      pAMSLmtOverrideList->canRedeem ( dstrTaxJuris, dstrProvResid, dstrAccountType,
                     dstrTaxType, dstrAcctDesign, idDataGroup );
 
   return GETCURRENTHIGHESTSEVERITY();
}

//*******************************************************************************
SEVERITY AmsMstrInfo::minPAC( const DString& dstrTaxJuris, const DString& dstrProvResid,
                                   const DString& dstrAccountType, const DString& dstrTaxType,
                                   const DString& dstrAcctDesign, const DString& dstrAmount,
                                   bool& bFundOverride, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("minPAC") );
   AmsLmtOverrideList* pAMSLmtOverrideList;
   getAmsLmtOverrideList ( pAMSLmtOverrideList, idDataGroup );
   if ( pAMSLmtOverrideList )
       pAMSLmtOverrideList->minPAC ( dstrTaxJuris, dstrProvResid, dstrAccountType,
                     dstrTaxType, dstrAcctDesign, dstrAmount, bFundOverride, idDataGroup );
 
   return GETCURRENTHIGHESTSEVERITY();
}

//*******************************************************************************
SEVERITY AmsMstrInfo::canPAC( const DString& dstrTaxJuris, const DString& dstrProvResid,
                                   const DString& dstrAccountType, const DString& dstrTaxType,
                                   const DString& dstrAcctDesign, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("canPAC") );
   AmsLmtOverrideList* pAMSLmtOverrideList;
   getAmsLmtOverrideList ( pAMSLmtOverrideList, idDataGroup );
   if ( pAMSLmtOverrideList )
       pAMSLmtOverrideList->canPAC ( dstrTaxJuris, dstrProvResid, dstrAccountType,
                     dstrTaxType, dstrAcctDesign, idDataGroup );

   return GETCURRENTHIGHESTSEVERITY();
}

//*******************************************************************************
SEVERITY AmsMstrInfo::canSWP( const DString& dstrTaxJuris, const DString& dstrProvResid,
                                   const DString& dstrAccountType, const DString& dstrTaxType,
                                   const DString& dstrAcctDesign, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("canSWP") );
   AmsLmtOverrideList* pAMSLmtOverrideList;
   getAmsLmtOverrideList ( pAMSLmtOverrideList, idDataGroup );
   if ( pAMSLmtOverrideList )
       pAMSLmtOverrideList->canSWP ( dstrTaxJuris, dstrProvResid, dstrAccountType,
                     dstrTaxType, dstrAcctDesign, idDataGroup );

   return GETCURRENTHIGHESTSEVERITY();
}

//*******************************************************************************
SEVERITY AmsMstrInfo::minSWP( const DString& dstrTaxJuris, const DString& dstrProvResid,
                                   const DString& dstrAccountType, const DString& dstrTaxType,
                                   const DString& dstrAcctDesign, const DString& dstrSWPAmt,
                                   bool& bFundOverride, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("minSWP") );
   AmsLmtOverrideList* pAMSLmtOverrideList;
   getAmsLmtOverrideList ( pAMSLmtOverrideList, idDataGroup );
   if ( pAMSLmtOverrideList )
       pAMSLmtOverrideList->minSWP ( dstrTaxJuris, dstrProvResid, dstrAccountType,
                     dstrTaxType, dstrAcctDesign, dstrSWPAmt, bFundOverride, idDataGroup );

   return GETCURRENTHIGHESTSEVERITY();
}

//*******************************************************************************
SEVERITY AmsMstrInfo::canATIn( const DString& dstrTaxJuris, const DString& dstrProvResid,
                                   const DString& dstrAccountType, const DString& dstrTaxType,
                                   const DString& dstrAcctDesign, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("canATIn") );
   AmsLmtOverrideList* pAMSLmtOverrideList;
   getAmsLmtOverrideList ( pAMSLmtOverrideList, idDataGroup );
   if ( pAMSLmtOverrideList )
       pAMSLmtOverrideList->canATIn ( dstrTaxJuris, dstrProvResid, dstrAccountType,
                     dstrTaxType, dstrAcctDesign, idDataGroup );

   return GETCURRENTHIGHESTSEVERITY();
}

//*******************************************************************************
SEVERITY AmsMstrInfo::canATOut( const DString& dstrTaxJuris, const DString& dstrProvResid,
                                   const DString& dstrAccountType, const DString& dstrTaxType,
                                   const DString& dstrAcctDesign, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("canATOut") );
   AmsLmtOverrideList* pAMSLmtOverrideList;
   getAmsLmtOverrideList ( pAMSLmtOverrideList, idDataGroup );
   if ( pAMSLmtOverrideList )
       pAMSLmtOverrideList->canATOut ( dstrTaxJuris, dstrProvResid, dstrAccountType,
                     dstrTaxType, dstrAcctDesign, idDataGroup );
 
   return GETCURRENTHIGHESTSEVERITY();
}

//*******************************************************************************
SEVERITY AmsMstrInfo::canTransferIn( const DString& dstrTaxJuris, const DString& dstrProvResid,
                                   const DString& dstrAccountType, const DString& dstrTaxType,
                                   const DString& dstrAcctDesign, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("canTransferIn") );
   AmsLmtOverrideList* pAMSLmtOverrideList;
   getAmsLmtOverrideList ( pAMSLmtOverrideList, idDataGroup );
   if ( pAMSLmtOverrideList )
       pAMSLmtOverrideList->canTransferIn ( dstrTaxJuris, dstrProvResid, dstrAccountType,
                     dstrTaxType, dstrAcctDesign, idDataGroup );

   return GETCURRENTHIGHESTSEVERITY();
}

//*******************************************************************************
SEVERITY AmsMstrInfo::canTransferOut( const DString& dstrTaxJuris, const DString& dstrProvResid,
                                   const DString& dstrAccountType, const DString& dstrTaxType,
                                   const DString& dstrAcctDesign, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("canTransferOut") );
   AmsLmtOverrideList* pAMSLmtOverrideList;
   getAmsLmtOverrideList ( pAMSLmtOverrideList, idDataGroup );
   if ( pAMSLmtOverrideList )
       pAMSLmtOverrideList->canTransferOut ( dstrTaxJuris, dstrProvResid, dstrAccountType,
                     dstrTaxType, dstrAcctDesign, idDataGroup );

   return GETCURRENTHIGHESTSEVERITY();
}

//*******************************************************************************
SEVERITY AmsMstrInfo::checkGrandfatheredDate (const DString& dstrTradeDate, const BFDataGroupId& idDataGroup, bool bError )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("checkGrandfatheredDate") );
   DString dstrGrandFatherDate;
   getField ( ifds::GrandFatheredDate, dstrGrandFatherDate, idDataGroup );
   //AMS %CODE% has a Grandfathered date of %DATE%
   //PTS 10023506 - Grandfather day is effective as of the date indicated and not the next business date.
   if (!( DSTCommonFunctions::CompareDates ( dstrGrandFatherDate, dstrTradeDate ) == DSTCommonFunctions::SECOND_EARLIER )) {
      DString dstrAMSCode, dstr;
      getField ( ifds::AMSCode, dstrAMSCode, idDataGroup );
      addIDITagValue( dstr, I_("CODE"), dstrAMSCode );    
      //Fix formatting bug.  Date will be shown 01/10/2003, not 01102003.
      getField ( ifds::GrandFatheredDate, dstrGrandFatherDate, idDataGroup, true );
      addIDITagValue( dstr, I_("DATE"), dstrGrandFatherDate );
      if ( bError ) {
         ADDCONDITIONFROMFILEIDI( CND::AMS_LMT_ERR_GRANDFATHERED_DATE, dstr );
      } else {
         ADDCONDITIONFROMFILEIDI( CND::AMS_LMT_WARN_GRANDFATHERED_DATE, dstr );
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//***********************************************************************************************
void AmsMstrInfo::getErrMsgValue( DString dstrErrNum,       
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

}

//***********************************************************************************************
//Next Rebalance Date can not be earlier than the effective date of ams master record
SEVERITY AmsMstrInfo::validateEffectiveNextRebDate(const DString& strValue, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateEffectiveGFDate" ));

   DString EffectiveDate, NextRebDate;
   getField(ifds::EffectiveDate, EffectiveDate, idDataGroup);
   getField(ifds::NextRebDate, NextRebDate, idDataGroup);
   if( DSTCommonFunctions::CompareDates( NextRebDate, EffectiveDate ) 
       != DSTCommonFunctions::SECOND_EARLIER )
   {
      ADDCONDITIONFROMFILE( CND::ERR_NEXT_REB_DATE_CANNOT_EARLIER_THAN_EFFECTIVE_DATE );
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//***********************************************************************************************
SEVERITY AmsMstrInfo::validateAMSRuleType(const DString& strValue, const BFDataGroupId& idDataGroup )
{
    MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateAMSRuleType" ));

	AmsLmtOverrideList *pAmsLmtOverrideList = NULL;
	if ( getAmsLmtOverrideList(pAmsLmtOverrideList, idDataGroup) <= WARNING && pAmsLmtOverrideList )
	{
		DString dstrValue;
		pAmsLmtOverrideList->getValueByType( STOP_TRFER_IN, dstrValue, idDataGroup );
		if ( dstrValue == NOT_EXIST || dstrValue == NO )
		{
			ADDCONDITIONFROMFILE( CND::ERR_RULE_TYPE_RECORD_FOR_STOP_TRFER_IN_REQUIRED ); 

		}
	}
	return GETCURRENTHIGHESTSEVERITY();
}

//**************************************************************************
bool   AmsMstrInfo::isGrandFatherDateStamped(const BFDataGroupId& idDataGroup)
{
	DString dstrDateStamped;
	getField( ifds::GrandFatherStamped, dstrDateStamped, idDataGroup, false );
	dstrDateStamped.strip().upperCase();
	return dstrDateStamped == YES;

}
//****************************************************************************
// uErrCode:  0x0000: no error
//            0x0001: Account Type does not match
//            0x0002: Tax Type does not match
//            0x0004: Account Designation does not match
//            0x0008: Tax Jurisdiction does not match
//            0x0010: Province of Resident does not match
bool AmsMstrInfo:: canAMSCodeSetUpForAccount( const DString& dstrAccountNum,
										const BFDataGroupId& idDataGroup,unsigned int& uErrCode )
{
	bool bRet = false;
   AmsLmtOverrideList* pAMSLmtOverrideList = NULL;
   getAmsLmtOverrideList ( pAMSLmtOverrideList, idDataGroup );
   if ( pAMSLmtOverrideList )
	{
      bRet = pAMSLmtOverrideList->canAMSCodeSetUpForAccount ( dstrAccountNum, idDataGroup, uErrCode );
	}
	return bRet;
}

//*****************************************************************************
bool AmsMstrInfo::isFundInAMS ( const DString& dstrFundCode, const DString dstrClassCode, const BFDataGroupId& idDataGroup )
{
   DString dstrFund( dstrFundCode ), dstrClass( dstrClassCode );
   dstrFund.upperCase().strip();
   dstrClass.upperCase().strip();
   AmsFundAllocList *pAMSFundAllocList = NULL;
   getAMSFundAllocList( pAMSFundAllocList,idDataGroup );
   if ( pAMSFundAllocList ) {
      BFObjIter iter( *pAMSFundAllocList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
      DString dstrCmpFundCode, dstrCmpClassCode;
      AmsFundAlloc *pAMSFundAlloc = NULL;
      while ( !iter.end () ) {
         pAMSFundAlloc = dynamic_cast <AmsFundAlloc*> ( iter.getObject() );
         pAMSFundAlloc->getField ( ifds::FundCode, dstrCmpFundCode, idDataGroup );
         pAMSFundAlloc->getField ( ifds::ClassCode, dstrCmpClassCode, idDataGroup );
         if ( ( dstrCmpFundCode.upperCase().strip() == dstrFund ) && ( dstrCmpClassCode.upperCase().strip() == dstrClass ) )
            return true;
         ++iter;
      }
      return false;
   } else {
      return false;
   }
}

//*****************************************************************************
void AmsMstrInfo::CalculateNextRebDate(const BFDataGroupId& idDataGroup)
{

    MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "CalculateNextRebDate" ) );

	DString dstrAMSCode, dstrEffectiveDate, dstrFreq;

	getField(ifds::EffectiveDate,dstrEffectiveDate,idDataGroup,false);
	getField(ifds::SchedSetupFreqID, dstrFreq, idDataGroup, false);
	dstrFreq.strip();
	dstrEffectiveDate.strip();

   if ( !dstrFreq.empty() && dstrFreq!=I_("0") ) {
	   AMSRebDateCalc *pAMSRebDateCalc = new AMSRebDateCalc(*this);
	   if( pAMSRebDateCalc->init( dstrEffectiveDate ,dstrFreq) <= WARNING ) {
		   DString dstrNextRebDate;
		   pAMSRebDateCalc->getField(ifds::NextProcessDate,dstrNextRebDate,idDataGroup,false);
		   setFieldNoValidate(ifds::NextRebDate, dstrNextRebDate, idDataGroup, false, true, true);
	   } else {
		   CLEARCONDITIONS();
	   } 
      
      if (pAMSRebDateCalc)  {
		   delete pAMSRebDateCalc;
		   pAMSRebDateCalc =NULL;       
	   }
   } else {
	   DString dstrNextRebDate;
	   DSTCommonFunctions::getFormat12319999Date(dstrNextRebDate);
	   setFieldNoValidate(ifds::NextRebDate, dstrNextRebDate, idDataGroup, false, true, true); 	
   }

}

//*****************************************************************************
bool AmsMstrInfo::isAMSC(const BFDataGroupId& idDataGroup)
{
	DString dstrParentFndClsTrdg, dstrGlobalLevelAssetMixApplicable;

	getField(ifds::ParentFndClsTrdg, dstrParentFndClsTrdg, idDataGroup, false);
	getField(ifds::FundAlloc, dstrGlobalLevelAssetMixApplicable, idDataGroup, false);

	// For AMS Model C, Trade via Parent Fund/Class is 'Y'
	return (dstrParentFndClsTrdg.upperCase() == YES_01) && (dstrGlobalLevelAssetMixApplicable.strip().upperCase() == YES);
}

//*****************************************************************************
SEVERITY AmsMstrInfo::validateParentFundClassXEdit(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateParentFundClassXEdit" ) );

   DString dstrAMSType, dstrAssocFund, dstrAssocClass, dstrParentFndClsTrdg;

   getField(ifds::AMSType, dstrAMSType, idDataGroup, false );
   getField(ifds::AssocFund, dstrAssocFund,  idDataGroup, false );
   getField(ifds::AssocClass, dstrAssocClass, idDataGroup, false );
   getField(ifds::ParentFndClsTrdg, dstrParentFndClsTrdg, idDataGroup, false);
   dstrAMSType.strip().upperCase();
   dstrParentFndClsTrdg.strip().upperCase();
   dstrAssocFund.strip().upperCase();
   dstrAssocClass.strip().upperCase();

   if ( dstrAMSType == REBALANCE && dstrParentFndClsTrdg == YES_01)
   {
      if( dstrAssocFund.empty() || dstrAssocClass.empty())
      {
         ADDCONDITIONFROMFILE( CND::ERR_PARENT_FUND_CLASS_REQUIRED );
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/amsmstrinfo.cpp-arc  $
// 
//    Rev 1.57   Sep 17 2009 16:11:02   wutipong
// INC#1720999 - more fix (date must not be ealier than current bus date issue).
// 
//    Rev 1.56   Aug 10 2009 11:03:04   wutipong
// In#1720999 - add missing fields to classfieldinfo[ ]. 
// 
//    Rev 1.55   Aug 10 2009 20:31:10   wutipong
// INC#1720999 Can not change an AMS in Desktop
// 
//    Rev 1.54   Feb 20 2009 16:13:32   jankovii
// IN 1543838 - AMS Rebalancing - AMS Mstr Setup -R91 - QA Testing
// 
//    Rev 1.53   11 Jun 2008 10:30:04   popescu
// in#1283327 - Trade created with invalid settlement date, Code review regarding modification of Trade and DateValidation CBO.
// 
//    Rev 1.52   Jul 27 2007 15:35:32   smithdav
// PET2360 FN02 - Only do Currency validation for RB
// 
//    Rev 1.51   Jul 27 2007 11:30:26   smithdav
// Cleanup commented code.
// 
//    Rev 1.50   Jul 19 2007 14:23:40   smithdav
// PET2360 FN02 - Fix NextRebalanceDate recalc.
// 
//    Rev 1.49   Jun 25 2007 11:58:20   porteanm
// PET 2360 FN02 - AMS - frequency.
// 
//    Rev 1.48   Jun 22 2007 14:19:22   porteanm
// PET 2360 FN02 - AMS - work in progress.
// 
//    Rev 1.47   Jun 18 2007 14:32:48   porteanm
// PET2360 FN02 - AIM AMS - Syst level.
// 
//    Rev 1.46   Mar 21 2007 13:22:54   jankovii
// PET 2292 FN01 - Switch Settlement.
// 
//    Rev 1.45   Sep 16 2005 11:33:14   fengyong
// #405536 - Do not validate round fund and class when error 378 is I and round fund and class all empty
// 
//    Rev 1.44   Mar 22 2005 16:46:42   ZHANGCEL
// Incident #269682 -- Change the order of parameters to match the method defination
// 
//    Rev 1.43   Feb 09 2005 11:54:42   porteanm
// Incident235084 WO17703 - Error encountered when Currency is not applicable.
// 
//    Rev 1.42   Dec 03 2004 16:34:26   hernando
// Added Field Info for ForeignRelFundNum and RoundingFundNum.
// 
//    Rev 1.41   Nov 14 2004 14:25:58   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.40   Aug 19 2004 10:24:46   VADEANUM
// PTS 10033236 - Round/Class validation should fire up only for Global Levele AMS
// 
//    Rev 1.39   Jun 24 2004 14:35:40   VADEANUM
// PTS 10031722 - AMS Global - Round Fund/Class validation.
// 
//    Rev 1.38   Feb 23 2004 10:48:22   HERNANDO
// PTS10026642 - Removed check in doValidateAll; no longer necessary.
// 
//    Rev 1.37   Feb 22 2004 19:12:44   HERNANDO
// PTS10026642 - Improved checking the Excess Foreign Fund.
// 
//    Rev 1.36   Feb 10 2004 14:19:14   HERNANDO
// PTS10026642 - Check to ensure that 'Exc Foreign Fund' is in the portfolio (allocation).  An error will be displayed if it's not.
// 
//    Rev 1.35   Dec 03 2003 14:00:58   HSUCHIN
// PTS 10023506 - bug fix with grandfather date ams
// 
//    Rev 1.34   Oct 28 2003 13:27:46   linmay
// PTS Ticket # 10023244,  MFOL Name is mandatory for CIBC.
// 
//    Rev 1.33   Oct 17 2003 11:28:50   linmay
// PTS Ticket #10023033, remove the logic to force foreign currency rebalance
// 
//    Rev 1.32   Oct 03 2003 15:54:50   linmay
// PTS Ticket#10022366, schema change for view 260
// 
//    Rev 1.31   Sep 17 2003 11:07:50   linmay
// PTS Ticket #10021838, #10021835.
// Correct error code value for RoundingFund, ForeignRelFund.
// 
//    Rev 1.30   Sep 05 2003 11:37:30   HSUCHIN
// bug fix to new ams code showing error on update.
// 
//    Rev 1.29   Aug 25 2003 11:53:00   linmay
// modified doInit()
// 
//    Rev 1.28   Aug 16 2003 11:20:44   HSUCHIN
// added method isFundInAMS to check if fund/class passed in is in the AMS fund allocation list.
// 
//    Rev 1.27   Aug 14 2003 13:03:24   HSUCHIN
// Change the fund override from pass by copy to pass by reference.
// 
//    Rev 1.26   Aug 13 2003 11:16:08   HERNANDO
// PTS 10020412 - Currency Required if Currency Generic Control is set.
// 
//    Rev 1.25   Aug 13 2003 09:53:44   linmay
// Sync with 1.22.1.1
// 
//    Rev 1.24   Aug 12 2003 10:23:34   HSUCHIN
// change checkGrandfatheredDate to have an additional parameter which determines whether or not a Error or warning message is raised.  Code cleanup
// 
//    Rev 1.23   Aug 11 2003 09:41:46   linmay
// fix bug
// 
//    Rev 1.22   Aug 05 2003 11:26:26   linmay
// fix bug
// 
//    Rev 1.20   Jul 25 2003 17:05:42   HSUCHIN
// added support for limit override checks such as stop purchase, stop PAC etc. etc.
// 
//    Rev 1.19   Jul 23 2003 10:58:20   linmay
// modified for cibc
// 
//    Rev 1.18   Jul 18 2003 11:34:56   linmay
// modified for CIBC AMS
// 
//    Rev 1.17   Jun 06 2003 15:24:58   YINGBAOL
// PTS10018006
// 
//    Rev 1.16   Jun 06 2003 11:25:34   YINGBAOL
// add doinitwithdefaultvalue
// 
//    Rev 1.15   Apr 21 2003 09:43:38   YINGBAOL
// reimpement AMSType logic.
// 
//    Rev 1.14   Apr 04 2003 16:58:34   PURDYECH
// Sync 1.11.1.0 back to trunk
// 
//    Rev 1.13   Apr 02 2003 17:27:24   HERNANDO
// Added AMSType for the request.  View has changed in pre-51 to require AMSType besides AMS Code for the request.
// 
//    Rev 1.12   Mar 21 2003 17:59:12   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.11   Mar 11 2003 10:34:50   YINGBAOL
// fix Percentage format issue
// 
//    Rev 1.10   Jan 15 2003 13:05:44   YINGBAOL
// allow user to create AMS Code 0001
// 
//    Rev 1.9   Jan 06 2003 16:35:02   linmay
// modified doValidateAll and added new condition ERR_NO_VALID_FUND_ALLOC_RECORD
// 
//    Rev 1.8   Jan 06 2003 11:12:26   linmay
// modified validateFundAlloc
// 
//    Rev 1.7   Jan 03 2003 14:45:40   linmay
// modified InitNew, validateFundAlloc(), add view83, 
// 
//    Rev 1.6   Jan 03 2003 09:25:48   linmay
// modified init function
// 
//    Rev 1.5   Jan 02 2003 15:13:08   linmay
// added getAMSFundAllocList
// 
//    Rev 1.4   Dec 27 2002 11:30:40   linmay
// added AMSType and AMSCodeDesc
// 
//    Rev 1.3   Dec 02 2002 16:24:08   KOVACSRO
// fixed initialization problem (set AMSCode field)
// 
//    Rev 1.2   Nov 27 2002 11:48:36   YINGBAOL
// remove somecode to list level
// 
//    Rev 1.1   Nov 19 2002 13:29:34   YINGBAOL
// added more business rules
// 
//    Rev 1.0   Nov 13 2002 10:00:12   YINGBAOL
// Initial Revision
// 



//