//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2004 by International Financial Data Services.
//
//
//******************************************************************************
//
// ^FILE   : RESPBeneficiaryAllocation.cpp
// ^AUTHOR : 
// ^DATE   : February, 2010
//
// ^CLASS    : RESPBeneficiaryAllocation
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "respbeneficiaryallocation.hpp"
#include "respbeneficiaryallocationlist.hpp"
#include "respbeneficiaryvalidation.hpp"

#include <ifastdataimpl\dse_dstc0402_req.hpp>
#include <ifastdataimpl\dse_dstc0402_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0403_req.hpp>
#include <ifastdataimpl\dse_dstc0050_vwrepeat_record.hpp>

#include "mgmtco.hpp"

namespace
{
   const I_CHAR * const CLASSNAME		= I_("RESPBeneficiaryAllocation");
   const I_CHAR * RESP_BENEFICIARY		= I_( "50" ); 
   const I_CHAR * CALL_TYPE_VALIDATION  = I_( "V" ); 
   const I_CHAR * const BENEF_NAME		= I_("BENNAME");
   const I_CHAR * const PENDPROC		= I_("PENDPROC");
   const I_CHAR * const TRANSNUM		= I_("TRANSNUM");
   const I_CHAR * const PROCESSED      = I_( "Proc" );

   const double dSmallValue       = .0000000001;
}

namespace ifds
{   
	extern CLASS_IMPORT const BFTextFieldId RecordType;
	extern CLASS_IMPORT const BFTextFieldId RecId;
	extern CLASS_IMPORT const BFTextFieldId AllocEntityType;
	extern CLASS_IMPORT const BFDecimalFieldId AllocEntityTypeSeq;
   extern CLASS_IMPORT const BFDecimalFieldId Amount;
   extern CLASS_IMPORT const BFTextFieldId AllowManualDelete;
}

namespace CND
{  
	extern const long ERR_BENEFICIARY_NOT_EFFECTIVE;
	extern const long WARN_ASSOCIATED_GRANT_TRADE;
	extern const long WARN_GRANT_TRADE_DETAILS;
	extern const long WARN_CREATE_ESCROW ;
   extern const long ERR_ALLOCAMOUNT_GREATER_THAN_TOTAL;
	extern const long ERR_VALUE_CANNOT_BE_ZERO;
   extern const long ERR_VALUE_BETWEEN_0_AND_100;
}

//-------------------------------------------------------------------
const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
//	Field DD Id,				State Flags,	Group Flags    

    {ifds::RESPBenefId,			BFCBO::NONE,	0 },
    {ifds::RESPAllocAmt,		BFCBO::NONE,	0 },
    {ifds::RESPAllocPrcnt,		BFCBO::NONE,	0 },
    {ifds::BenefDofB,			BFCBO::NONE,	0 },
    {ifds::HRDCRelateCode,		BFCBO::NONE,	0 },
    {ifds::TaxJuris,			BFCBO::NONE,	0 },
    {ifds::RESPContrDetlVer,	BFCBO::NONE,	0 },
    {ifds::PendGrantExists,		BFCBO::NONE,	0 },
    {ifds::ProcGrantExists,		BFCBO::NONE,	0 },
    {ifds::EffectiveDate,		BFCBO::NONE,	0 },
    {ifds::RecordType,			BFCBO::NONE,	0 },
    {ifds::AllocEntityType,		BFCBO::NONE,	0 },
    {ifds::AllocEntityTypeSeq,	BFCBO::NONE,	0 },
    {ifds::TransId,				BFCBO::NONE,	0 },
    {ifds::ReAllocated,			BFCBO::NONE,	0 },
   {ifds::CreateEscrow,       BFCBO::NONE,	0 },
   {ifds::AllowManualDelete,  BFCBO::NOT_ON_HOST,	0 }
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//******************************************************************************************
RESPBeneficiaryAllocation::RESPBeneficiaryAllocation (BFAbstractCBO &parent) : 
MFCanBFCbo (parent),
m_bSettingAmountField (false),
m_bSettingPercentField (false)
{
	TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
	registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );
}
//******************************************************************************************
RESPBeneficiaryAllocation::~RESPBeneficiaryAllocation()
{
	TRACE_DESTRUCTOR( CLASSNAME );
}     

//************************************************************************************
SEVERITY RESPBeneficiaryAllocation::initNew (const BFDataGroupId &idDataGroup, 
                                             bool bSetFieldsReadOnly)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("initNew"));  	
 
	setFieldNoValidate (ifds::ReAllocated, I_("N"), idDataGroup, false);
	commonInit (bSetFieldsReadOnly, idDataGroup); 
      
	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************************
SEVERITY RESPBeneficiaryAllocation::init (const BFData& data,
                                          bool bSetFieldsReadOnly /*=false*/)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));

	attachDataObject (const_cast<BFData&>(data), false);
	
   commonInit (bSetFieldsReadOnly, BF::HOST);
   setFieldReadOnly (ifds::RESPBenefId, BF::HOST, true);

   DString dstrRESPAllocPrcnt, dstrPendGrantExists, dstrProcGrantExists;
   getField(ifds::RESPAllocPrcnt,dstrRESPAllocPrcnt,BF::HOST,false);
   getField(ifds::PendGrantExists,dstrPendGrantExists,BF::HOST,false);
   getField(ifds::ProcGrantExists,dstrProcGrantExists,BF::HOST,false);
   dstrRESPAllocPrcnt.strip().upperCase();
   dstrPendGrantExists.strip().upperCase();
   dstrProcGrantExists.strip().upperCase();

   bool bGrantReceived = dstrPendGrantExists == I_("Y") || dstrProcGrantExists == I_("Y");

   BigDecimal bdZero(I_("0"));
   BigDecimal bdRESPAllocPrcnt(dstrRESPAllocPrcnt);

   if(bdRESPAllocPrcnt == bdZero && !bGrantReceived)
   {
      setFieldNoValidate (ifds::AllowManualDelete, I_("N"), BF::HOST, false);
   }
   else
   {
      setFieldNoValidate (ifds::AllowManualDelete, I_("Y"), BF::HOST, false);
   }

	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
void RESPBeneficiaryAllocation::doInitWithDefaultValues (const BFDataGroupId& idDataGroup)
{  
}

////***********************************************************************************
SEVERITY RESPBeneficiaryAllocation::commonInit (bool bSetFieldsReadOnly, 
                                                const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("commonInit"));
   
	DString substList;

	setFieldNoValidate (ifds::RecordType, I_("EntityAlloc"), idDataGroup, false);
	setFieldNoValidate (ifds::AllocEntityType, RESP_BENEFICIARY, idDataGroup, false);
	setFieldNoValidate (ifds::CreateEscrow, I_("N"), idDataGroup, false);

	setFieldReadOnly (ifds::ReAllocated, idDataGroup, true);
	
	RESPBeneficiaryAllocationList *pRESPBeneficiaryAllocationList = dynamic_cast<RESPBeneficiaryAllocationList*>( getParent( ) );      

	if (pRESPBeneficiaryAllocationList)
	{
		DString dstrEntityId,
         dstAllocEntityTypeSeq;

		getField (ifds::RESPBenefId, dstrEntityId, idDataGroup, false);

      pRESPBeneficiaryAllocationList->getBeneficiaryMasterList (substList, idDataGroup);	
		pRESPBeneficiaryAllocationList->getEntitySeqNumber (dstrEntityId, idDataGroup, dstAllocEntityTypeSeq);
		setFieldNoValidate (ifds::AllocEntityTypeSeq, dstAllocEntityTypeSeq, idDataGroup, false);				 
	}
	
	setFieldAllSubstituteValues (ifds::RESPBenefId, idDataGroup, substList ); 

	if (bSetFieldsReadOnly)
	{
	   for (int i = 0; i < NUM_FIELDS; i++)
	   {
	      BFCBO::CLASS_FIELD_INFO fieldInfo = classFieldInfo [i];     
	      const BFFieldId &fieldId = fieldInfo.getFieldId();

	      setFieldReadOnly (fieldId, idDataGroup, true);
	   }
	}
	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
void RESPBeneficiaryAllocation::getField( const BFFieldId& idField, 
                                          DString &strValue, 
                                          const BFDataGroupId& idDataGroup, 
                                          bool formattedReturn ) const
{
   if (idField == ifds::RESPAllocAmt && formattedReturn)
   {
      getField (idField, strValue, idDataGroup, false);
      
      RESPBeneficiaryAllocationList *pRESPBeneficiaryAllocationList =         
         dynamic_cast <RESPBeneficiaryAllocationList *> 
            (const_cast<RESPBeneficiaryAllocation*>(this)->getParent());

      if (pRESPBeneficiaryAllocationList)
      {
         pRESPBeneficiaryAllocationList->getFormattedAmount (idDataGroup, strValue);
      }
   }
   else
   {
     BFCBO::getField (idField, strValue, idDataGroup, formattedReturn);
   }
}


//***********************************************************************************
SEVERITY RESPBeneficiaryAllocation::doValidateField( const BFFieldId &idField,
                                                     const DString &strValue,
                                                     const BFDataGroupId &idDataGroup)

{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateField"));

	if (idField == ifds::RESPBenefId)
	{
		validateBeneficiary (strValue, idDataGroup);
	}
   else if (idField == ifds::RESPAllocPrcnt)
   {
      validatePercentage (strValue, idDataGroup);
   }
   else if (idField == ifds::RESPAllocAmt)
   {
      validateAmount (strValue, idDataGroup);
   }	
	return GETCURRENTHIGHESTSEVERITY();
}


//*****************************************************************************************
SEVERITY RESPBeneficiaryAllocation::doApplyRelatedChanges (const BFFieldId &idField, 
                                                           const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges"));

	if (idField == ifds::RESPBenefId)
	{
		DString dstrEntityId;

		getField (ifds::RESPBenefId, dstrEntityId, idDataGroup, false);

		RESPBeneficiaryAllocationList *pRESPBeneficiaryAllocationList = dynamic_cast<RESPBeneficiaryAllocationList*>( getParent( ) );      

		if (pRESPBeneficiaryAllocationList)
		{
			DString	dstrRESPAllocAmt,
			   dstrRESPAllocPrcnt,
			   dstrBenefDofBirth,
			   dstrHRDCRelateCode,
			   dstrTaxJuris,
			   dstrEffectiveDate,
            dstAllocEntityTypeSeq;

			m_bChoosingBenef = true;

			pRESPBeneficiaryAllocationList->getRESPEntityInfo (dstrEntityId,  idDataGroup, 
                                                               dstrRESPAllocPrcnt, dstrBenefDofBirth, 
                                                               dstrHRDCRelateCode, dstrTaxJuris, 
                                                               dstrEffectiveDate);		

			setFieldNoValidate (ifds::RESPAllocPrcnt, dstrRESPAllocPrcnt, idDataGroup, false, false, true, false ); 
			setFieldNoValidate (ifds::HRDCRelateCode, dstrHRDCRelateCode, idDataGroup, false, false, true, false ); 
			setFieldNoValidate (ifds::TaxJuris, dstrTaxJuris, idDataGroup, false, false, true, false); 
			setFieldNoValidate (ifds::EffectiveDate, dstrEffectiveDate, idDataGroup, false, false, true, false); 
			setFieldNoValidate (ifds::BenefDofB, dstrBenefDofBirth, idDataGroup, false, false, true, false); 

			pRESPBeneficiaryAllocationList->getEntitySeqNumber (dstrEntityId, idDataGroup, dstAllocEntityTypeSeq);
			setFieldNoValidate (ifds::AllocEntityTypeSeq, dstAllocEntityTypeSeq, idDataGroup, false);

			setAmount (idDataGroup);
			m_bChoosingBenef = false;
		}
	}
	else if (idField == ifds::RESPAllocPrcnt)
	{
		setAmount (idDataGroup);

      DString dstrRESPAllocPrcnt, dstrPendGrantExists, dstrProcGrantExists;
      getField(ifds::RESPAllocPrcnt,dstrRESPAllocPrcnt,BF::HOST,false);
      getField(ifds::PendGrantExists,dstrPendGrantExists,BF::HOST,false);
      getField(ifds::ProcGrantExists,dstrProcGrantExists,BF::HOST,false);
      dstrRESPAllocPrcnt.strip().upperCase();
      dstrPendGrantExists.strip().upperCase();
      dstrProcGrantExists.strip().upperCase();

      bool bGrantReceived = dstrPendGrantExists == I_("Y") || dstrProcGrantExists == I_("Y");

      BigDecimal bdZero(I_("0"));
      BigDecimal bdRESPAllocPrcnt(dstrRESPAllocPrcnt);

      if(bdRESPAllocPrcnt == bdZero && !bGrantReceived)
      {
         setFieldNoValidate (ifds::AllowManualDelete, I_("N"), idDataGroup, false);
      }
      else
      {
         setFieldNoValidate (ifds::AllowManualDelete, I_("Y"), idDataGroup, false);
      }
	}
	else if (idField == ifds::RESPAllocAmt)
	{
		setPercentage (idDataGroup);
	}
    
	return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************************
SEVERITY RESPBeneficiaryAllocation::getBeneficiaryValidation ( RESPBeneficiaryValidation *&pRESPBeneficiaryValidation,
                                                               const BFDataGroupId &idDataGroup)
{

	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("getBeneficiaryValidation"));

	pRESPBeneficiaryValidation = NULL;

  	DString dstrEntityType,  
           dstrRESPBenefId, 
           dstrRESPBenefName, 
           dstrRESPAllocAmount, 
           dstrRESPAllocPercent,
           dstrRESPContrDetlVer,
		     dstrTradeAmount,
		     dstrTradeDate,
           dstrAccountNum,
           dstrTradeType,
           dstrTransId,
           dstAllocEntityTypeSeq;

	getField (ifds::RESPBenefId, dstrRESPBenefId, idDataGroup);
	getField (ifds::RESPBenefId, dstrRESPBenefName, idDataGroup, true);
	getField (ifds::RESPAllocAmt, dstrRESPAllocAmount, idDataGroup);
	getField (ifds::RESPAllocPrcnt, dstrRESPAllocPercent, idDataGroup);
	getField (ifds::RESPContrDetlVer, dstrRESPContrDetlVer, idDataGroup);
   getField (ifds::AllocEntityTypeSeq, dstAllocEntityTypeSeq, idDataGroup);


	dstrEntityType = RESP_BENEFICIARY;

	dstrEntityType.strip().upperCase();
	dstrRESPBenefId.strip();
	dstrRESPAllocAmount.strip();
	dstrRESPAllocPercent.strip();
	dstrRESPContrDetlVer.strip ();
	
	
	RESPBeneficiaryAllocationList *pRESPBeneficiaryAllocationList = 
      dynamic_cast<RESPBeneficiaryAllocationList*>( getParent( ) );      

	if (pRESPBeneficiaryAllocationList)
	{
		pRESPBeneficiaryAllocationList->getField (ifds::Amount, dstrTradeAmount, idDataGroup);
      pRESPBeneficiaryAllocationList->getField (ifds::EffectiveDate, dstrTradeDate, idDataGroup);
      pRESPBeneficiaryAllocationList->getField (ifds::AccountNum, dstrAccountNum, idDataGroup);
      pRESPBeneficiaryAllocationList->getField (ifds::TradeType, dstrTradeType, idDataGroup);
      pRESPBeneficiaryAllocationList->getField (ifds::TransId, dstrTransId, idDataGroup);
	}

	DString strKey;

	RESPBeneficiaryValidation::buildKey ( dstrTransId,
		                                   dstrEntityType, 
                                         dstAllocEntityTypeSeq, 
                                         dstrRESPBenefId,
                                         dstrRESPAllocAmount, 
                                         dstrRESPAllocPercent,
						                       strKey);

	pRESPBeneficiaryValidation =  dynamic_cast<RESPBeneficiaryValidation *> (BFCBO::getObject (strKey, idDataGroup));

	if (!pRESPBeneficiaryValidation)
	{
		pRESPBeneficiaryValidation = new RESPBeneficiaryValidation (*this);
			
		if (pRESPBeneficiaryValidation->init ( dstrTransId,
			                                    dstrAccountNum,
                                             dstrTradeType,
                                             dstrTradeDate,
                                             dstrTradeAmount,
                                             dstrEntityType, 
                                             dstAllocEntityTypeSeq, 
                                             dstrRESPBenefId,
                                             dstrRESPBenefName,
                                             dstrRESPAllocAmount, 
                                             dstrRESPAllocPercent, 
                                             dstrRESPContrDetlVer,
                                             CALL_TYPE_VALIDATION,
                                             I_("N")) <= WARNING)
		{
			setObject (pRESPBeneficiaryValidation, strKey, OBJ_ACTIVITY_NONE, idDataGroup);
		}
		else
		{
			delete pRESPBeneficiaryValidation;
			pRESPBeneficiaryValidation = NULL;
		}
	}
	
	return GETCURRENTHIGHESTSEVERITY ();
}
//***********************************************************************************
SEVERITY RESPBeneficiaryAllocation::validateBeneficiary (const DString &dstrBenefId, const BFDataGroupId &idDataGroup)

{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateBeneficiary"));

	RESPBeneficiaryAllocationList *pRESPBeneficiaryAllocationList = dynamic_cast<RESPBeneficiaryAllocationList*>( getParent( ) );      

	if (pRESPBeneficiaryAllocationList)
	{
		// Duplicate check
		pRESPBeneficiaryAllocationList->checkDuplicate (this, idDataGroup);

		// is beneficiary effective:
		DString	dstrRESPAllocAmt,
		   dstrRESPAllocPrcnt,
		   dstrBenefDofBirth,
		   dstrHRDCRelateCode,
		   dstrTaxJuris,
		   dstrEffectiveDate,
		   dstrTradeDate;

		pRESPBeneficiaryAllocationList->getRESPEntityInfo ( dstrBenefId, 
                                                          idDataGroup, 
                                                          dstrRESPAllocPrcnt, 
                                                          dstrBenefDofBirth, 
                                                          dstrHRDCRelateCode,
							                                     dstrTaxJuris, 
                                                          dstrEffectiveDate);	

		pRESPBeneficiaryAllocationList->getField (ifds::EffectiveDate, dstrTradeDate, idDataGroup);
		if (DSTCommonFunctions::CompareDates (dstrTradeDate, dstrEffectiveDate) == DSTCommonFunctions::FIRST_EARLIER)
		{
			DString idiStr = I_("");
			DString dstrBenName;

			getField( ifds::RESPBenefId, dstrBenName, idDataGroup, true );
			addIDITagValue (idiStr, BENEF_NAME, dstrBenName );
	        
			if (!dstrBenName.empty ())
			{
				ADDCONDITIONFROMFILEIDI (CND::ERR_BENEFICIARY_NOT_EFFECTIVE, idiStr);
			}
		}
	}
	
	//setFieldReadOnly (ifds::RESPBenefId, idDataGroup, true);
	
	return GETCURRENTHIGHESTSEVERITY();
}

//***********************************************************************************
SEVERITY RESPBeneficiaryAllocation::validateBeneficiary (const BFDataGroupId &idDataGroup)

{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateBeneficiary"));

	DString dstrTradeType;

   RESPBeneficiaryAllocationList *pRESPBeneficiaryAllocationList = 
      dynamic_cast<RESPBeneficiaryAllocationList*>( getParent( ) );      

	if (pRESPBeneficiaryAllocationList)
   {
      pRESPBeneficiaryAllocationList->getField (ifds::TradeType, dstrTradeType, idDataGroup);
   }
	
   RESPBeneficiaryValidation *pRESPBeneficiaryValidation (NULL);

	if ( getBeneficiaryValidation (pRESPBeneficiaryValidation, idDataGroup) <= WARNING  && 
        pRESPBeneficiaryValidation)
	{
		pRESPBeneficiaryValidation->validateBeneficiary (idDataGroup);
	}

	return GETCURRENTHIGHESTSEVERITY();
}

//***********************************************************************************
SEVERITY RESPBeneficiaryAllocation::validateIfGrantExists (const BFDataGroupId &idDataGroup)

{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateIfGrantExists"));

	DString dstrPendGrantExists;
	DString dstrProcGrantExists;
	DString dstrTransNumList;

	getField (ifds::PendGrantExists, dstrPendGrantExists, idDataGroup, false);
	getField (ifds::ProcGrantExists, dstrProcGrantExists, idDataGroup, false);
	getField (ifds::GrantTransNumList, dstrTransNumList, idDataGroup, false);

	if (dstrPendGrantExists == I_("Y"))
	{
		DString idiStr1, idiStr2;
		setFieldNoValidate (ifds::CreateEscrow, I_("Y"), idDataGroup, false);

	
		addIDITagValue (idiStr1, PENDPROC, I_("pending"));
		addIDITagValue (idiStr2, TRANSNUM, dstrTransNumList);

		ADDCONDITIONFROMFILEIDI (CND::WARN_ASSOCIATED_GRANT_TRADE, idiStr1);
		ADDCONDITIONFROMFILEIDI (CND::WARN_GRANT_TRADE_DETAILS, idiStr2);
		ADDCONDITIONFROMFILE (CND::WARN_CREATE_ESCROW);
	}

	if (dstrProcGrantExists == I_("Y"))
	{
		DString idiStr1, idiStr2;

		setFieldNoValidate (ifds::CreateEscrow, I_("Y"), idDataGroup, false);

		addIDITagValue (idiStr1, PENDPROC, I_("processed"));
		addIDITagValue (idiStr2, TRANSNUM, dstrTransNumList);

		ADDCONDITIONFROMFILEIDI (CND::WARN_ASSOCIATED_GRANT_TRADE, idiStr1);
		//ADDCONDITIONFROMFILEIDI (CND::WARN_GRANT_TRADE_DETAILS, idiStr2);
		ADDCONDITIONFROMFILE (CND::WARN_CREATE_ESCROW);
	}

	return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************************
SEVERITY RESPBeneficiaryAllocation::doValidateAll (const BFDataGroupId &idDataGroup, 
                                                      long lValidateGroup)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateAll"));
	
	validateBeneficiary (idDataGroup);

	validateIfGrantExists (idDataGroup);

	return GETCURRENTHIGHESTSEVERITY();
}

//***********************************************************************************
SEVERITY RESPBeneficiaryAllocation::setBeneficiaryAmountInvalid( const BFDataGroupId& idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setSettleLocAmountInvalid" ) );

	// when amount is invalid, must be recalculated based on the percent.
	setValidFlag (ifds::RESPAllocAmt,   idDataGroup, false);
	setUpdatedFlag (ifds::RESPAllocAmt, idDataGroup, true);
	setAmount (idDataGroup);
	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY RESPBeneficiaryAllocation::validatePercentage ( const DString& strValue, 
                                                         const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validatePercentage"));

   double dec_percent = DSTCommonFunctions::convertToDouble (strValue);

   if (dec_percent == 0)
   {  //P0185010.FN03.R03.00 - RESP Beneficiary Re-Allocations
      DString dstrTradeType;
      DString dstrHRDCReported;
      
      RESPBeneficiaryAllocationList *pRESPBeneficiaryAllocationList =
         dynamic_cast <RESPBeneficiaryAllocationList *> (getParent());

      if (pRESPBeneficiaryAllocationList)
      {
         pRESPBeneficiaryAllocationList->getField(ifds::TradeType, dstrTradeType, idDataGroup, false); 
         
         if (isNew())
         {//copy HRDCReported from another benef. This field is at account level
            pRESPBeneficiaryAllocationList->getOtherBenefsField (ifds::HRDCReported, dstrHRDCReported, idDataGroup, this);
         }
         else
         {
            getField(ifds::HRDCReported, dstrHRDCReported, idDataGroup, false);        
         }
      }      
      dstrHRDCReported.stripAll();
      
      if( dstrTradeType == I_( "New" ) || 
         ( dstrTradeType == PROCESSED && dstrHRDCReported == I_("N")))
      {
         ADDCONDITIONFROMFILE (CND::ERR_VALUE_CANNOT_BE_ZERO);
      }

   }
   else
   {
      if (dec_percent < 0 - dSmallValue || dec_percent > 100 + dSmallValue)
      {
         ADDCONDITIONFROMFILE (CND::ERR_VALUE_BETWEEN_0_AND_100);
      }	
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//*******************************************************************************
SEVERITY RESPBeneficiaryAllocation::validateAmount (const DString& strAmount, 
                                                    const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateAmount" ) );

   DString strTotalAmount;
   RESPBeneficiaryAllocationList *pRESPBeneficiaryAllocationList =         
      dynamic_cast <RESPBeneficiaryAllocationList *> (getParent());
   
   pRESPBeneficiaryAllocationList->getField(ifds::Amount, strTotalAmount, idDataGroup, false);
   
   double dTotalAmount = DSTCommonFunctions::convertToDouble(strTotalAmount);
   double dAllocAmount = DSTCommonFunctions::convertToDouble(strAmount);
   
   if (dAllocAmount - dTotalAmount > dSmallValue)
   {
      ADDCONDITIONFROMFILE (CND::ERR_ALLOCAMOUNT_GREATER_THAN_TOTAL);
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//*****************************************************************************************
SEVERITY RESPBeneficiaryAllocation::setAmount (const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "calculateAmount" ) );

   DString strParentAmount, 
      strAllocPercentage, 
      strAllocAmount, 
      strTotalAllocPercentage;
   
   RESPBeneficiaryAllocationList *pRESPBeneficiaryAllocationList =         
      dynamic_cast <RESPBeneficiaryAllocationList *> (getParent());

   pRESPBeneficiaryAllocationList-> getField (ifds::Amount, strParentAmount, idDataGroup, false);
   getField (ifds::RESPAllocPrcnt, strAllocPercentage, idDataGroup, false);

   if (!m_bSettingPercentField && !strParentAmount.strip().empty() && !strAllocPercentage.strip().empty())
   {
      pRESPBeneficiaryAllocationList->getTotalPercentage (strTotalAllocPercentage, idDataGroup);
      double dTotalAllocPercentage = DSTCommonFunctions::convertToDouble (strTotalAllocPercentage);
      double dParentAmount = DSTCommonFunctions::convertToDouble (strParentAmount);
      double dAllocPercentage = DSTCommonFunctions::convertToDouble (strAllocPercentage);
      double dAllocAmount = 0.0;
      if (fabs (dTotalAllocPercentage - 100) < dSmallValue)
      {
         //if this is the last allocation, because of the roundings:
         DString strOtherAllocTotalAmount;
         pRESPBeneficiaryAllocationList->getOtherAllocTotalAmount (strOtherAllocTotalAmount, idDataGroup, true, this);
         double dOtherAllocTotalAmount = DSTCommonFunctions::convertToDouble(strOtherAllocTotalAmount);
         dAllocAmount = dParentAmount - dOtherAllocTotalAmount;
         //if something went wrong, just don't do the roundings
         double dTemp = dParentAmount * dAllocPercentage / 100.0;
         if (fabs(dTemp - dAllocAmount) > 0.1)
         {
            dAllocAmount = int (dTemp);
         }
      }
      else
      {
         dAllocAmount = dParentAmount * dAllocPercentage / 100.0;
      }
      strAllocAmount = DSTCommonFunctions::doubleToDString (ifds::RESPAllocAmt, dAllocAmount);  
      pRESPBeneficiaryAllocationList->getFormattedAmount (idDataGroup, strAllocAmount);
      m_bSettingAmountField = true;
      setField (ifds::RESPAllocAmt, strAllocAmount, idDataGroup, true, true );
      m_bSettingAmountField = false;
   }
	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY RESPBeneficiaryAllocation::setPercentage (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("setPercentage"));

   DString strParentAmount, 
      strAllocPercentage, 
      strAllocAmount, 
      strTotalAllocAmount;

   RESPBeneficiaryAllocationList *pRESPBeneficiaryAllocationList =
      dynamic_cast <RESPBeneficiaryAllocationList *> (getParent());

   
   pRESPBeneficiaryAllocationList->getField (ifds::Amount, strParentAmount, idDataGroup, false);
   getField (ifds::RESPAllocAmt, strAllocAmount, idDataGroup, false);
   
   if (!m_bSettingAmountField && !strParentAmount.strip().empty() && !strAllocAmount.strip().empty())
   {
      double dParentAmount = DSTCommonFunctions::convertToDouble(strParentAmount);
      double dAllocAmount = DSTCommonFunctions::convertToDouble(strAllocAmount);
      if( fabs (dAllocAmount) > dSmallValue && fabs (dParentAmount) > dSmallValue )//if both total amount and alloc amount are not zero, set the alloc percentage
      {
         double dAllocPercentage = 0;
         pRESPBeneficiaryAllocationList->getTotalAmount (strTotalAllocAmount, idDataGroup);
         double dTotalAllocAmount = DSTCommonFunctions::convertToDouble(strTotalAllocAmount);
         if (fabs (dParentAmount - dTotalAllocAmount) < dSmallValue)
         {
            //if this is the last allocation, because of the roundings:
            DString strOtherAllocTotalPercent;
            pRESPBeneficiaryAllocationList->getOtherAllocTotalPercentage (strOtherAllocTotalPercent, idDataGroup, false, this);
            double dOtherAllocTotalPercent = DSTCommonFunctions::convertToDouble(strOtherAllocTotalPercent);
            dAllocPercentage = 100.0 - dOtherAllocTotalPercent;
            //if something went wrong, just don't do the roundings
            double dTemp = dAllocAmount / dParentAmount * 100.0;
            if (fabs (dTemp - dAllocPercentage) > 0.1)
            {
               dAllocPercentage = dTemp;
            }
         }
         else
         {
            dAllocPercentage = dAllocAmount / dParentAmount * 100.0;
         }

         strAllocPercentage = DSTCommonFunctions::doubleToDString (ifds::RESPAllocPrcnt, dAllocPercentage);  
         m_bSettingPercentField = true;
         setField (ifds::RESPAllocPrcnt, strAllocPercentage, idDataGroup, true, true);
         m_bSettingPercentField = false;
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/RESPBeneficiaryAllocation.cpp-arc  $
// 
//    Rev 1.14   Oct 13 2011 18:29:16   popescu
// P0185010.FN03.R03.00 - RESP Beneficiary Re-Allocations
// 
//    Rev 1.13   Oct 13 2011 04:35:46   panatcha
// P0185010.FN03.R03.00 - RESP Beneficiary Re-Allocations
// 
//    Rev 1.11   Oct 06 2011 10:29:14   panatcha
// P0185010FN01 - Beneficiary Allocations, EAP, LLP Withdrawals
// 
//    Rev 1.10   Jun 09 2010 15:31:28   jankovii
// IN 2143804 - QESI - #165541 - RESP TRansaction History
// 
//    Rev 1.9   Apr 09 2010 14:44:08   popescu
// PET165541_FN01_QESI - RESP Gap_Dsk_Trading - RESP Trading History Dialog - fixed refresh issue when updating allocations
// 
//    Rev 1.8   Apr 01 2010 09:43:16   jankovii
// PET165541_FN01_QESI - RESP Gap_Dsk_Trading
// 
//    Rev 1.7   Mar 30 2010 18:59:48   popescu
// PET165541_FN01_QESI - RESP Gap_Dsk_Trading
// 
//    Rev 1.6   Mar 30 2010 16:32:22   jankovii
// PET165541_FN01_QESI - RESP Gap_Dsk_Trading
// 
//    Rev 1.5   Mar 29 2010 22:59:22   popescu
// PET165541_FN01_QESI - RESP Gap_Dsk_Trading
// 
 */