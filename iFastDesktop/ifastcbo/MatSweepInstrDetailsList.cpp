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
// ^FILE   : MatSweepInstrDetailsList.cpp
// ^AUTHOR : 
// ^DATE   : 
//
//********************************************************************************
#include "stdafx.h"
#include "entity.hpp"
#include "mfaccount.hpp"
//#include "giainvattriblist.hpp"
#include "fundmasterlist.hpp"
#include "MatSweepInstrDetails.hpp"
#include "MatSweepInstrDetailsList.hpp"
#include "worksessionentitylist.hpp"
#include "mgmtco.hpp"

#include <ifastdataimpl\dse_dstc0428_req.hpp> 
#include <ifastdataimpl\dse_dstc0428_vw.hpp> 
#include <ifastdataimpl\dse_dstc0428_vwrepeat_record.hpp> 


namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest CASHSWEEP_MATURITY_INSTR_DTLS_INQUIRY;
}

namespace
{
   const I_CHAR * const CLASSNAME			= I_( "MatSweepInstrDetailsList" );
   const I_CHAR * const CASH_SWEEP			= I_( "CS" );
   const I_CHAR * const CASH			    = I_( "CS" );
   const I_CHAR * const MATURITY_INTEREST	= I_( "GI,GM,GB" );
   const I_CHAR * const MATURITYINTEREST	= I_( "GB" );
   const I_CHAR * const MATURITY	        = I_( "GM" );
   const I_CHAR * const INTEREST			= I_( "GI" );
   const I_CHAR * const YES1				= I_("1");
   const I_CHAR * const PERCENT				= I_("P");
   const I_CHAR * const EFT					= I_("E");
   const I_CHAR * const CHEQUE				= I_("S");
   const I_CHAR * const SUPPRESS			= I_("X");
   const I_CHAR * const PROCESSED			= I_( "Proc" );
   const I_CHAR * const ONE					= I_( "1" );
   const I_CHAR * const MONTHLY				= I_( "M" );
   const I_CHAR * const YES					= I_("Y");
   const I_CHAR * const NO					= I_("N");

}

namespace CND
{  // Conditions used
	extern const long ERR_ONLY_ONE_GIA_FUND_ALLOWED;
	extern const long ERR_INSTR_DETAILS_MISSING;
	extern const long ERR_ONEGI_MULTIPLESEGS_ALLOWED;
	extern const long ERR_DUPLICATE_RECORD;
	extern const long ERR_SUM_OF_PERCENTAGES_NOT_100;
	extern const long ERR_ONE_REMAININGFLAG_REQUIRED;
	extern const long ERR_MULTIPLE_REMAININGFLAGS_FOUND;
	extern const long ERR_ALLOC_AMT_EXCEEDS_TRADE_AMT;
	extern const long ERR_SELAMOUNT_LESSTHAN_REQUIRED;
	extern const long WARN_SELAMOUNT_LESSTHAN_REQUIRED;
	extern const long WARN_ALLOC_AMT_EXCEEDS_INVESTMENT_MV;
	extern const long WARN_ALLOC_AMT_EXCEEDS_INVESTMENT_REMAININGPRINCIPAL;
	extern const long WARN_ALLOC_AMT_EXCEEDS_INVESTMENT_ACCRUEDINT;
	extern const long ERR_INVALID_INTERESTINST_DATA;
}

namespace ifds
{
	extern CLASS_IMPORT const BFTextFieldId SplitType;
	extern CLASS_IMPORT const BFTextFieldId ProcType;
	extern CLASS_IMPORT const BFDecimalFieldId Amount;
	extern CLASS_IMPORT const BFDecimalFieldId InvHisAcurdToDate;
	extern CLASS_IMPORT const BFIntegerFieldId InvestTerm;
	extern CLASS_IMPORT const BFTextFieldId IntCredFreq;
}
//******************************************************************************
MatSweepInstrDetailsList::MatSweepInstrDetailsList( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
, m_requestData (ifds::DSTC0428_REQ)
{
	TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
	
	setObjectAsList( );  	
}

//******************************************************************************
MatSweepInstrDetailsList::~MatSweepInstrDetailsList()
{
   TRACE_DESTRUCTOR( CLASSNAME );

   	setObjectAsList( );  	
}

//******************************************************************************
SEVERITY MatSweepInstrDetailsList::init( const DString& dstrAccountNum,
                                         const DString& dstrFund,
                                         const DString& dstrClass,                     
                                         const DString& dstrInstrType,
                                         const DString& dstrTransNum,
										 const DString& dstrEffectiveDate,
										 const DString& dstrInvestId,
										 const DString& dstrGBCD,
										 const DString& dstrTransSeq,
                                         const DString& dstrTrack,
                                         const DString& dstrPageName )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

	DString mgmtCoIdOut;

	m_requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
	m_requestData.setElementValue( ifds::Track, dstrTrack );

	m_requestData.setElementValue( ifds::AccountNum, dstrAccountNum); 
	m_requestData.setElementValue( ifds::MatSwpInstructionType, dstrInstrType );  
	m_requestData.setElementValue( ifds::Fund, dstrFund );  
	m_requestData.setElementValue( ifds::Class, dstrClass );  
	m_requestData.setElementValue( ifds::TransNum, dstrTransNum );  
	m_requestData.setElementValue( ifds::EffectiveDate, dstrEffectiveDate );  
	m_requestData.setElementValue( ifds::IntInvestId, dstrInvestId );  
	m_requestData.setElementValue( ifds::GoodBad, dstrGBCD );  
	m_requestData.setElementValue( ifds::TransSeq, dstrTransSeq );

	ReceiveData ( DSTC_REQUEST::CASHSWEEP_MATURITY_INSTR_DTLS_INQUIRY, 
				  m_requestData, 
				  ifds::DSTC0428_VW, 
				  DSTCRequestor (getSecurity()), 
				  false);

	return GETCURRENTHIGHESTSEVERITY();
}
//*************************************************************************************
SEVERITY MatSweepInstrDetailsList::doCreateObject( const BFData& data, BFCBO*& pObjOut )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );
   	
	pObjOut = new MatSweepInstrDetails( *this );
	((MatSweepInstrDetails* )pObjOut)->init(const_cast<BFData&>(data) );

	return( GETCURRENTHIGHESTSEVERITY() );
}

//**************************************************************************************
SEVERITY MatSweepInstrDetailsList::doCreateNewObject( BFCBO *&pObjOut, DString &strKey, const BFDataGroupId& idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateNewObject" ) );
   	
	pObjOut = new MatSweepInstrDetails(*this );
    ((MatSweepInstrDetails* )pObjOut)->initNew(idDataGroup );

	return( GETCURRENTHIGHESTSEVERITY() );
}

//*******************************************************************************
SEVERITY MatSweepInstrDetailsList::doValidateAll (const BFDataGroupId& idDataGroup, long lValidateGroup)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );
	
	DString dstrSplitType;

	getParent ()->getField (ifds::SplitType, dstrSplitType, idDataGroup, false);

	validateAllDetails (idDataGroup);

	validateRemainingFlag (idDataGroup);

	if (dstrSplitType == PERCENT)
		validatePercent (idDataGroup);
	else
		validateAmount (idDataGroup);

	/* TO DO: see if this works on dlg....
	validateCashSweepDetails (idDataGroup);
	validateMaturityInterstDetails (idDataGroup);
	*/
	return GETCURRENTHIGHESTSEVERITY();
}

//*******************************************************************************
SEVERITY MatSweepInstrDetailsList::validateCashSweepDetails (const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateCashSweepInstructions" ) );

	BFObjIter iter( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED );

	MatSweepInstrDetails	*pMatSweepInstrDetails;
	DString					dstrInstrType;
	int						numfOfGIAFunds = 0;
	int						numfOfSEGFunds = 0;
	int						numTargetFunds = 0;
	bool					bcaughtError = false;
   
	getParent ()->getField (ifds::MatSwpInstructionType, dstrInstrType, idDataGroup, false);

	if (dstrInstrType != CASH_SWEEP)
		return GETCURRENTHIGHESTSEVERITY();

	while (!iter.end())
	{
		pMatSweepInstrDetails = dynamic_cast<MatSweepInstrDetails*>(iter.getObject());

		if (pMatSweepInstrDetails)
		{
			DString dstrFund;
			bool	bIsGIAFund = false;
			bool	bIsSEGFund = false;

			pMatSweepInstrDetails->getField (ifds::FundTo, dstrFund, idDataGroup, false);
			pMatSweepInstrDetails->isGIAFund (dstrFund, bIsGIAFund, idDataGroup);
			pMatSweepInstrDetails->isSEGFund (dstrFund, bIsSEGFund, idDataGroup);

			if (bIsGIAFund)
			{
				numfOfGIAFunds++;
			}

			if (bIsSEGFund)
			{
				numfOfSEGFunds++;
			}
		}
		++iter;
		numTargetFunds++;
	}
   
	if(numfOfGIAFunds > 1)
	{ 
		ADDCONDITIONFROMFILE (CND::ERR_ONLY_ONE_GIA_FUND_ALLOWED); 
		bcaughtError = true;
	}

	if (numfOfSEGFunds > 0 && numfOfGIAFunds >= 1)
	{
		ADDCONDITIONFROMFILE (CND::ERR_ONEGI_MULTIPLESEGS_ALLOWED); 
		bcaughtError = true;
	}

	if (numfOfGIAFunds >= 1 && numTargetFunds > 1 && !bcaughtError)
	{ 
		ADDCONDITIONFROMFILE (CND::ERR_ONLY_ONE_GIA_FUND_ALLOWED); 
	}

	return GETCURRENTHIGHESTSEVERITY();
}
//*******************************************************************************
SEVERITY MatSweepInstrDetailsList::validateMaturityInterstDetails (const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateMaturityInterstInstructions" ) );

	DString					dstrInstrType;
	
	getParent ()->	getField (ifds::MatSwpInstructionType, dstrInstrType, idDataGroup, false);

	if (dstrInstrType == CASH_SWEEP)
		return GETCURRENTHIGHESTSEVERITY();
	
	return GETCURRENTHIGHESTSEVERITY();
}
//*******************************************************************************
SEVERITY MatSweepInstrDetailsList::validateAllDetails (const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateAllDetails" ) );

    BFObjIter iter( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED );

	int nItems = iter.getNumberOfItemsInList();

    if (nItems == 0) 
    {
        ADDCONDITIONFROMFILE (CND::ERR_INSTR_DETAILS_MISSING);
    }
	
	return GETCURRENTHIGHESTSEVERITY();
}
 
//*********************************************************************************************
SEVERITY MatSweepInstrDetailsList::checkDuplicate ( const DString &dstrRollOverType, const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_( "checkDuplicate" ) );   	
	
	int		numfOfEFTs = 0;
	int		numfOfSupress = 0;
	int		numfOfChqs = 0;

	// check only for CASH funds
	if (dstrRollOverType != CASH)
		return GETCURRENTHIGHESTSEVERITY();
	
	//check first whether in the list (in memory) we have a duplicate
	BFObjIter iter( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED );
	iter.begin();	

	while (!iter.end())
	{
		MatSweepInstrDetails *pMatSweepInstrDetails = dynamic_cast<MatSweepInstrDetails*>(iter.getObject());
		DString dstrPayType;

		pMatSweepInstrDetails->getField( ifds::PayType, dstrPayType, idDataGroup);

		if (dstrPayType == EFT)
		{
			++numfOfEFTs;
		}
		else if (dstrPayType == CHEQUE)
		{
			++numfOfChqs;
		}
		else if (dstrPayType == SUPPRESS)
		{
			++numfOfSupress;
		}

		++iter;
	}

	if ( numfOfEFTs > 1 ||  numfOfChqs > 1 || numfOfSupress > 1)
	{
		ADDCONDITIONFROMFILE(CND::ERR_DUPLICATE_RECORD);
	}

	return GETCURRENTHIGHESTSEVERITY();
}

//*********************************************************************************************
SEVERITY MatSweepInstrDetailsList::validatePercent (const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validatePercent" ) );   	

	double dTotalPercentage = 0;

	BFObjIter iter( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED );
	iter.begin();
	
	while (!iter.end())
	{
		MatSweepInstrDetails *pMatSweepInstrDetails = dynamic_cast<MatSweepInstrDetails*>(iter.getObject());
		// Don't check against itself
		if (pMatSweepInstrDetails)
		{
			DString dstrPercent;

			pMatSweepInstrDetails->getField( ifds::Percentage, dstrPercent, idDataGroup );
			dstrPercent.strip().stripAll(I_CHAR(','));

			I_CHAR *stopstring;
			double dPercentage = wcstod(dstrPercent.c_str(), &stopstring); 
			dTotalPercentage += dPercentage;
		}
		++iter;
	}

	if (fabs(dTotalPercentage) != 100 )
    { 
		ADDCONDITIONFROMFILE( CND::ERR_SUM_OF_PERCENTAGES_NOT_100 );
	}

	return GETCURRENTHIGHESTSEVERITY();
}
//*********************************************************************************************
SEVERITY MatSweepInstrDetailsList::validateRemainingFlag (const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateRemainingFlag" ) );   	

	bool bFound = false;
	int  iFlags = 0;
	DString dstrSplitType;

	getParent ()->getField (ifds::SplitType, dstrSplitType, idDataGroup );

	if (dstrSplitType == PERCENT)
		return GETCURRENTHIGHESTSEVERITY();

	BFObjIter iter( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED );
	iter.begin();
	
	while (!iter.end())
	{
		MatSweepInstrDetails *pMatSweepInstrDetails = dynamic_cast<MatSweepInstrDetails*>(iter.getObject());
		
		if (pMatSweepInstrDetails)
		{
			DString dstrRemainingFlag;

			pMatSweepInstrDetails->getField( ifds::RemainingFleg, dstrRemainingFlag, idDataGroup );

			if (dstrRemainingFlag == YES1)
			{
				bFound = true;
				++iFlags;
			}
		}
		++iter;
	}

	if (!bFound)
    { 
		// one flag is required to be yes if split type is Amount
		ADDCONDITIONFROMFILE( CND::ERR_ONE_REMAININGFLAG_REQUIRED );
	}
	else if (iFlags > 1)
	{
		// found more then one remaining flag set to yes.
		ADDCONDITIONFROMFILE(CND::ERR_MULTIPLE_REMAININGFLAGS_FOUND);
	}

	return GETCURRENTHIGHESTSEVERITY();
}

//*********************************************************************************************
SEVERITY MatSweepInstrDetailsList::validateAmount (const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateAmount" ) );   	

	DString dstrAmount;
	DString dstrInstrType;
	DString dstrProcType;
	bool    bInvestmentMatIntInstr = false;
	bool    bInvestmentMatInstr = false;
	bool    bInvestmentIntInstr = false;

	double dTotalAmount = 0;
	double dAmount = 0;

	I_CHAR *stopstring;

	getParent ()->getField (ifds::MatSwpInstructionType, dstrInstrType, idDataGroup, false);
	getParent ()->getField (ifds::ProcType, dstrProcType, idDataGroup, false);
	
	if (dstrInstrType == INTEREST)
	{
		// brand new trade, no validation
		if (dstrProcType != PROCESSED)
		{
			return GETCURRENTHIGHESTSEVERITY();
		}

		getParent ()->getParent ()->getField (ifds::InvHisAcurdToDate, dstrAmount, idDataGroup );
		dstrAmount.strip().stripAll(I_CHAR(','));

		double dInterestAmount= wcstod(dstrAmount.c_str(), &stopstring);

		// if there is no acured interes do not display error
		if (dInterestAmount == 0)
		{
			return GETCURRENTHIGHESTSEVERITY();
		}
		else
		{
			dstrAmount.strip().stripAll(I_CHAR(','));
			dAmount= wcstod(dstrAmount.c_str(), &stopstring);
			bInvestmentIntInstr = true;
		}
	}
	else if (dstrInstrType == MATURITY)
	{
		if (dstrProcType != PROCESSED)
		{
			// trade amount..
			getParent ()->getParent ()->getField (ifds::Amount, dstrAmount, idDataGroup );
			dstrAmount.strip().stripAll(I_CHAR(','));
			dAmount= wcstod(dstrAmount.c_str(), &stopstring);
		}
		else
		{
			// processed trade, remaining principal
			// Remaining Principal = Mareket Value -Accured Intest
			DString dstrAcuredInterest;
			DString dstrMarketValue;

			getParent ()->getParent ()->getField (ifds::InvHisAcurdToDate, dstrAcuredInterest, idDataGroup );
			getParent ()->getParent ()->getField (ifds::Amount, dstrMarketValue, idDataGroup );

			dstrAcuredInterest.strip().stripAll(I_CHAR(','));
			dstrMarketValue.strip().stripAll(I_CHAR(','));

			double dAcuredInterest = wcstod(dstrAcuredInterest.c_str(), &stopstring);
			double dMarketValue= wcstod(dstrMarketValue.c_str(), &stopstring);

			dAmount = dMarketValue - dAcuredInterest;

			bInvestmentMatInstr = true;
		}
	}
	else if (dstrInstrType == MATURITYINTEREST)
	{
		// looking into makret value 
		// for brand new investment it is trade amount
		// for processed investment it is market value
		getParent ()->getParent ()->getField (ifds::Amount, dstrAmount, idDataGroup );
		dstrAmount.strip().stripAll(I_CHAR(','));
		dAmount= wcstod(dstrAmount.c_str(), &stopstring);

		bInvestmentMatIntInstr = dstrProcType == PROCESSED ? true : false;
	}

	BFObjIter iter( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED );
	iter.begin();
	
	while (!iter.end())
	{
		MatSweepInstrDetails *pMatSweepInstrDetails = dynamic_cast<MatSweepInstrDetails*>(iter.getObject());
		// Don't check against itself
		if (pMatSweepInstrDetails)
		{
			DString dstrAllocAmount;

			pMatSweepInstrDetails->getField( ifds::Percentage, dstrAllocAmount, idDataGroup );
			dstrAllocAmount.strip().stripAll(I_CHAR(','));

			I_CHAR *stopstring;
			double dAllocAmount = wcstod(dstrAllocAmount.c_str(), &stopstring); 
			dTotalAmount += dAllocAmount;
		}
		++iter;
	}

	
	if (dTotalAmount > dAmount)
    { 
		if (bInvestmentMatIntInstr)
		{
			ADDCONDITIONFROMFILE( CND::WARN_ALLOC_AMT_EXCEEDS_INVESTMENT_MV );
		}
		else if (bInvestmentMatInstr)
		{
			ADDCONDITIONFROMFILE( CND::WARN_ALLOC_AMT_EXCEEDS_INVESTMENT_REMAININGPRINCIPAL );
		}
		else if (bInvestmentIntInstr)
		{
			ADDCONDITIONFROMFILE( CND::WARN_ALLOC_AMT_EXCEEDS_INVESTMENT_ACCRUEDINT );
		}
		else
		{
			ADDCONDITIONFROMFILE( CND::ERR_ALLOC_AMT_EXCEEDS_TRADE_AMT );
		}
	}

	return GETCURRENTHIGHESTSEVERITY();
}
//*******************************************************************************
SEVERITY MatSweepInstrDetailsList::clone (MatSweepInstrDetailsList *pMatSweepInstrDetailsList, const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("clone" ));
    BFObjIter iter (*this, idDataGroup, true);
   
   while (!iter.end())
   {
      MatSweepInstrDetails *pMatSweepInstrDetailsToBeCloned = 
         dynamic_cast <MatSweepInstrDetails*> (iter.getObject ());

      BFObjectKey objKey (NULL_STRING, idDataGroup);
      MatSweepInstrDetails *pMatSweepInstrDetailsClone = dynamic_cast <MatSweepInstrDetails*> (pMatSweepInstrDetailsList->getNewListItem (objKey));
      if (pMatSweepInstrDetailsToBeCloned)
      {
         pMatSweepInstrDetailsClone->initClone (pMatSweepInstrDetailsToBeCloned, idDataGroup);
		 pMatSweepInstrDetailsClone->setFieldUpdated (ifds::RolloverType, idDataGroup, true); //set the obj dirty
      }
	  ++iter;
   }
	return GETCURRENTHIGHESTSEVERITY();
}

//*******************************************************************************
SEVERITY MatSweepInstrDetailsList::resetRemainingFlag (const DString &dstrSplitType, const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("resetRemainingFlag" ));
    
	BFObjIter iter (*this, idDataGroup, true);
   
	while (!iter.end())
	{
		MatSweepInstrDetails *pMatSweepInstrDetails = dynamic_cast <MatSweepInstrDetails*> (iter.getObject ());

		if (pMatSweepInstrDetails)
		{
			pMatSweepInstrDetails->resetRemainingFlag (dstrSplitType, idDataGroup);

		}
		++iter;
	}
	
	return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************
SEVERITY MatSweepInstrDetailsList::validateFundClassMinAmount (const DString &dstrCashSweepMinAmount,
												               const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateFundClassMinAmount" ));
    
	DString dstrFundMinAmount;
	DString dstrEWI;
	I_CHAR *stopstring;
	double dCashSweepMinAmount = wcstod(dstrCashSweepMinAmount.c_str(), &stopstring); 

	BFObjIter iter (*this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);
   
	while (!iter.end())
	{
		MatSweepInstrDetails *pMatSweepInstrDetails = dynamic_cast <MatSweepInstrDetails*> (iter.getObject ());

		if (pMatSweepInstrDetails)
		{
			DString dstrFund;
			DString dstrClass;
			DString dstrFundMinAmount;
			DString dstrPercent;

			pMatSweepInstrDetails->getField (ifds::FundTo, dstrFund, idDataGroup, false);
			pMatSweepInstrDetails->getField (ifds::ClassTo, dstrClass, idDataGroup, false);
			pMatSweepInstrDetails->getField (ifds::Percentage, dstrPercent, idDataGroup, false);

			pMatSweepInstrDetails->getFundClassMinAmount (dstrFund, dstrClass, dstrFundMinAmount, dstrEWI, idDataGroup);
			
			double dFundMinAmount = wcstod(dstrFundMinAmount.c_str(), &stopstring); 
			double dPercent = wcstod(dstrPercent.c_str(), &stopstring);
			double dAllowedAmount = dFundMinAmount * dPercent / 100;

			dstrEWI.upperCase ();

			if (dCashSweepMinAmount < dAllowedAmount)
			{
				if (dstrEWI == I_("E"))
				{
					ADDCONDITIONFROMFILE (CND::ERR_SELAMOUNT_LESSTHAN_REQUIRED);
				}
				else if (dstrEWI == I_("W"))
				{
					ADDCONDITIONFROMFILE (CND::WARN_SELAMOUNT_LESSTHAN_REQUIRED);
				}
			}
		}
		++iter;
	}

	return GETCURRENTHIGHESTSEVERITY ();
}

//*****************************************************************************
SEVERITY MatSweepInstrDetailsList::validateInterestInstruction (const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateInterestInstruction"));
	
	DString dstrFund;
	DString dstrClass;
	DString	dstrEffectiveDate;
	DString dstrInstrType;
	DString dstrCashOnly = NO;

	GIAInvAttribList *pGIAInvAttribList = NULL;

	getParent ()->getField (ifds::Fund, dstrFund, idDataGroup, false);
	getParent ()->getField (ifds::Class, dstrClass, idDataGroup, false);
	getParent ()->getField (ifds::EffectiveDate, dstrEffectiveDate, idDataGroup, false);
	getParent ()->getField (ifds::MatSwpInstructionType, dstrInstrType, idDataGroup, false);

	if (dstrInstrType != INTEREST)
	{
		return GETCURRENTHIGHESTSEVERITY ();
	}


    if (!dstrFund.empty() && !dstrClass.empty())
	{
		DString dstrTerm;
		DString dstrFrequency;

		FundMasterList *pFundMasterList; 

		if (getMgmtCo().getFundMasterList (pFundMasterList) && 
			pFundMasterList)
		{
			if (!pFundMasterList->isGIAFund (dstrFund))
			{
				return GETCURRENTHIGHESTSEVERITY ();
			}
		}

		getParent ()->getParent ()->getField(ifds::InvestTerm, dstrTerm, idDataGroup, false );
		getParent ()->getParent ()->getField(ifds::IntCredFreq, dstrFrequency, idDataGroup, false );

		dstrTerm.stripAll ();
		dstrCashOnly = dstrTerm != ONE && dstrFrequency == MONTHLY ? YES : NO;

		if (dstrCashOnly == YES)
		{
			ADDCONDITIONFROMFILE (CND::ERR_INVALID_INTERESTINST_DATA);
		}
	}
  
	return GETCURRENTHIGHESTSEVERITY ();
}
//*******************************************************************************
/* $Log::   
//    Rev 1.2   Dec 14 2011 16:55:42   popescu
// P0186477 FN03- GIA Maturity/Cash Sweep Instructions
 **/