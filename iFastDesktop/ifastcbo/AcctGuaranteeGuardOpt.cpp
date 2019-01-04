//******************************************************************************
//
// COPYRIGHT:
//
// The computer systems, procedures, data bases and
// programs created and maintained by International Financial Data Services,
// are proprietary in nature and as such are confIdential.
// Any unauthorized use or disclosure of such information
// may result in civil liabilities.
//
// Copyright 2010 by International Financial Data Services.
//
//
//******************************************************************************
//
// ^FILE   : AcctGuaranteeGuardOpt.cpp
// ^AUTHOR : 
// ^DATE   : Aug, 2010
//
// ^CLASS    : AcctGuaranteeGuardOpt
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "AcctGuaranteeGuardOpt.hpp"
#include "translationtable.hpp" 
#include "MgmtCo.hpp"
#include "Broker.hpp"
#include "MFAccount.hpp"
#include <ifastdataimpl\dse_dstc0004_vw.hpp>

#include <ifastdataimpl\dse_dstc0412_req.hpp>
#include <ifastdataimpl\dse_dstc0412_vw.hpp>
#include <ifastdataimpl\dse_dstc0412_vwrepeat_record.hpp>

namespace
{
   const I_CHAR * const CLASSNAME               = I_( "AcctGuaranteeGuardOpt" );
   const I_CHAR * const NO                      = I_( "N" );
   const I_CHAR * const YES                     = I_( "Y" );
   const I_CHAR * const ACCTDESIG_CLIENT        = I_( "1" );
   const I_CHAR * const ACCTDESIG_NOMINEE       = I_( "2" );
   const I_CHAR * const ACCTDESIG_INTERMEDIARY  = I_( "3" );
}

namespace ifds
{
	extern CLASS_IMPORT const BFNumericFieldId AccountNum;
	extern CLASS_IMPORT const BFTextFieldId GuardOptCurrent;
	extern CLASS_IMPORT const BFTextFieldId GuardOptAfter;
	extern CLASS_IMPORT const BFDateFieldId DeffUntil;
	extern CLASS_IMPORT const BFTextFieldId BrokGuardOptClt;
	extern CLASS_IMPORT const BFTextFieldId BrokGuardOptNom;
	extern CLASS_IMPORT const BFTextFieldId BrokGuardOptINT;
	extern CLASS_IMPORT const BFDateFieldId CurrBusDate;
}

namespace CND
{  // Conditions used
   extern const long ERR_DEFF_UNTIL_CANNOT_BE_LESS_THAN_TODAY;
   extern const long ERR_INVALID_GUARD_OPTION;
}

namespace IFASTERR
{
}

//******************************************************************************************
const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
   // Field DD Id,                     State Flags,          Group Flags
   { ifds::AccountNum                  , BFCBO::NONE,                0 },
   { ifds::GuardOptCurrent             , BFCBO::NONE,                0 },
   { ifds::GuardOptAfter               , BFCBO::NONE,                0 },
   { ifds::DeffUntil                   , BFCBO::NONE,                0 },
   { ifds::GBCD                        , BFCBO::NONE,                0 },
   { ifds::SEGGuarGuardID              , BFCBO::NONE,                0 },
   { ifds::CreatedBy                   , BFCBO::NONE,                0 },
   { ifds::CreatedOn                   , BFCBO::NONE,                0 },
   { ifds::ModDate                     , BFCBO::NONE,                0 },
   { ifds::ModUser                     , BFCBO::NONE,                0 },
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//******************************************************************************************
AcctGuaranteeGuardOpt::AcctGuaranteeGuardOpt( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   registerMemberData( NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0,
                       NULL );
}

//******************************************************************************************
AcctGuaranteeGuardOpt::~AcctGuaranteeGuardOpt()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************************
SEVERITY AcctGuaranteeGuardOpt::init(const BFData& data)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   initGuaranteeGuardOptList(BF::HOST);

   attachDataObject( const_cast< BFData& >( data ), false, true );

   DString dstrAccountNum;
   getParent()->getParent()->getField(ifds::AccountNum, dstrAccountNum, BF::HOST, false);
   setFieldNoValidate(ifds::AccountNum, dstrAccountNum, BF::HOST, false, true, true, false);

   DString dstrGBCD;
   getField(ifds::GBCD, dstrGBCD, BF::HOST, false);
   dstrGBCD.strip().upperCase();
   
   if(dstrGBCD == NO)
   {
	  setFieldReadOnly (ifds::GuardOptCurrent, BF::HOST, true);   
	  setFieldReadOnly (ifds::DeffUntil, BF::HOST, true);   
      setFieldReadOnly (ifds::GuardOptAfter, BF::HOST, true);   
   }
   else
   {
	   DString dstrDeffUntil;
	   getField(ifds::DeffUntil, dstrDeffUntil, BF::HOST, false);
	   
	   if( DSTCommonFunctions::CompareDates( dstrDeffUntil, I_("12319999") ) == DSTCommonFunctions::EQUAL )
	      setFieldReadOnly (ifds::GuardOptAfter, BF::HOST, true);
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************************
SEVERITY AcctGuaranteeGuardOpt::initNew(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initNew" ) );

   commonInit(idDataGroup);
   setObjectNew();

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY AcctGuaranteeGuardOpt::commonInit(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initNew" ) );

    DString dstrAccountNum;
    getParent()->getParent()->getField(ifds::AccountNum, dstrAccountNum, idDataGroup, false);
    setFieldNoValidate(ifds::AccountNum, dstrAccountNum, idDataGroup, false, true, true);
    // init sub list
    initGuaranteeGuardOptList(idDataGroup);

	DString dstrGuardOptCurrentDefault, dstrBrokerCode;
	// getField from MFAccount
	getParent()-> getParent()-> getField(ifds::BrokerCode, dstrBrokerCode, idDataGroup, false);
	dstrBrokerCode.strip().upperCase();
	
	Broker *pBroker = NULL;
	dynamic_cast < MFAccount * > ( getParent()-> getParent() )-> getBroker(pBroker, dstrBrokerCode, idDataGroup);
	if(pBroker)
	{
		DString dstrAcctDesignation;
		getParent()-> getParent()-> getField(ifds::AcctDesignation, dstrAcctDesignation, idDataGroup, false);
		dstrAcctDesignation.strip();
		
		BFFieldId fieldId;
		if(dstrAcctDesignation == ACCTDESIG_CLIENT)
			fieldId = ifds::BrokGuardOptClt;
		else if(dstrAcctDesignation == ACCTDESIG_NOMINEE)
			fieldId = ifds::BrokGuardOptNom;
		else if(dstrAcctDesignation == ACCTDESIG_INTERMEDIARY)
			fieldId = ifds::BrokGuardOptINT;

		pBroker->getField(fieldId, dstrGuardOptCurrentDefault, idDataGroup, false);	
		dstrGuardOptCurrentDefault.strip();
		
		setFieldNoValidate(ifds::GuardOptCurrent, dstrGuardOptCurrentDefault, idDataGroup, false, false, true);
	
	}
	
	DString dstrDate12319999;
	getWorkSession().getDateInHostFormat (dstrDate12319999, DSTCWorkSession::DATE_TYPE::DAY12319999, idDataGroup);
    dstrDate12319999.strip();

	setFieldNoValidate(ifds::DeffUntil, dstrDate12319999, idDataGroup, false, false, true);
	setFieldNoValidate(ifds::GuardOptAfter, I_("00"), idDataGroup, false, false, true);
	setFieldReadOnly (ifds::GuardOptAfter, idDataGroup, true);
	// for reset purpose
	setFieldReadOnly (ifds::GuardOptAfter, BF::HOST, true);

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
void AcctGuaranteeGuardOpt::doInitWithDefaultValues( const BFDataGroupId& idDataGroup )
{
   TRACE_METHOD( CLASSNAME, I_( "doInitWithDefaultValues" ) );

   commonInit(idDataGroup);
   setNonDummyFlag();
}

//******************************************************************************************
SEVERITY AcctGuaranteeGuardOpt::initGuaranteeGuardOptList(const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initGuaranteeGuardOptList" ) );

	initializeSubstitutionList (ifds::GuardOptCurrent, I_("GG"), idDataGroup);
	initializeSubstitutionList (ifds::GuardOptAfter, I_("GG"), idDataGroup);

	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
void AcctGuaranteeGuardOpt::initializeSubstitutionList( const BFFieldId& idField, 
														const DString &dstrGroupCode, 
														const BFDataGroupId& idDataGroup)
{
   TranslationTable* pTranslationTable = NULL;
   DString dstrSubstitutionList;
   
   getMgmtCo().getTranslationTable (dstrGroupCode, pTranslationTable);
  
   if (pTranslationTable)
   {
      pTranslationTable->getSubstitutionList(dstrSubstitutionList, true);
      setFieldAllSubstituteValues (idField, idDataGroup, dstrSubstitutionList);
   
	  BFProperties *pBFIdValueProperties = getFieldProperties( idField, idDataGroup );
	  pBFIdValueProperties->setSubstituteValues(NULL);
   }
}

//******************************************************************************
SEVERITY AcctGuaranteeGuardOpt::doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateField" ) );

   if (idField == ifds::GuardOptCurrent)
   {
      if(strValue == I_("00"))
      {
	     ADDCONDITIONFROMFILE (CND::ERR_INVALID_GUARD_OPTION);
	  }	
   }
   if (idField == ifds::DeffUntil)
   {
      DString dstrCurrBusDate;
	  getWorkSession().getOption( ifds::CurrBusDate, dstrCurrBusDate, idDataGroup, false );
	
	  if( DSTCommonFunctions::CompareDates( strValue, dstrCurrBusDate ) == DSTCommonFunctions::FIRST_EARLIER )
	  {
	     ADDCONDITIONFROMFILE (CND::ERR_DEFF_UNTIL_CANNOT_BE_LESS_THAN_TODAY);
	  }   
   }
   if (idField == ifds::GuardOptAfter)
   {
      DString dstrDeffUntil, date12319999;
	  getField(ifds::DeffUntil, dstrDeffUntil, idDataGroup, false);
      getWorkSession().getDateInHostFormat (date12319999, DSTCWorkSession::DATE_TYPE::DAY12319999, idDataGroup);
      dstrDeffUntil.strip();
      date12319999.strip();
	  
      DString strGuardOptAfter(strValue);
      strGuardOptAfter.strip().upperCase();

      if( DSTCommonFunctions::CompareDates( dstrDeffUntil, date12319999 ) == DSTCommonFunctions::EQUAL || dstrDeffUntil.empty() )
	  {    	
         if(strGuardOptAfter != I_("00"))
         {
            ADDCONDITIONFROMFILE (CND::ERR_INVALID_GUARD_OPTION);
         }
      }
      else if (DSTCommonFunctions::CompareDates( dstrDeffUntil, date12319999 ) == DSTCommonFunctions::FIRST_EARLIER && !dstrDeffUntil.empty())
      {
         if(strGuardOptAfter == I_("00"))
		 {
	        ADDCONDITIONFROMFILE (CND::ERR_INVALID_GUARD_OPTION);
		 }
	  }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY AcctGuaranteeGuardOpt::doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges" ) );

   if (idField == ifds::DeffUntil)
   {
      DString dstrDeffUntil, date12319999;
	  
	  initGuaranteeGuardOptList (idDataGroup);
	  getField(idField, dstrDeffUntil, idDataGroup, false);
      getWorkSession().getDateInHostFormat (date12319999, DSTCWorkSession::DATE_TYPE::DAY12319999, idDataGroup);

      if( DSTCommonFunctions::CompareDates( dstrDeffUntil, date12319999 ) == DSTCommonFunctions::FIRST_EARLIER && 
		  !dstrDeffUntil.empty())
	  {
	     setFieldReadOnly (ifds::GuardOptAfter, idDataGroup, false);
	  }
      else 
      {
         // date equals to 31 Dec 9999
         setFieldNoValidate(ifds::GuardOptAfter, I_("00"), idDataGroup, false, false, true);
         setFieldReadOnly (ifds::GuardOptAfter, idDataGroup, true);
      }   
      setFieldValid (ifds::GuardOptAfter, idDataGroup, false);
	  
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
void AcctGuaranteeGuardOpt::setUpdateStatus( const BFDataGroupId& idDataGroup, bool bStatus )
{
   setUpdatedFlag( ifds::GuardOptCurrent    , idDataGroup, bStatus );
   setUpdatedFlag( ifds::GuardOptAfter      , idDataGroup, bStatus );
   setUpdatedFlag( ifds::DeffUntil          , idDataGroup, bStatus );
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/AcctGuaranteeGuardOpt.cpp-arc  $
// 
//    Rev 1.0   Sep 17 2010 03:37:28   kitticha
// Initial revision.
// 
//
