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
// ^FILE   : MatSweepInstrList.cpp
// ^AUTHOR : 
// ^DATE   : 
//
//********************************************************************************
#include "stdafx.h"
#include "mfaccount.hpp"
#include "matsweepinstr.hpp"
#include "matsweepinstrlist.hpp"


namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest CASHSWEEP_MATURITY_INSTR_INQUIRY;
}

namespace
{
	const I_CHAR * const CLASSNAME			= I_( "MatSweepInstrList" );
	const I_CHAR * const CASH_SWEEP_INSTR	= I_("SWP");
   	const I_CHAR * const MATURITY			= I_( "GM" );
	const I_CHAR * const INTEREST			= I_( "GI" );
	const I_CHAR * const MATURITY_INTEREST	= I_( "GB" );
}

namespace CND
{  // Conditions used
	extern const long ERR_DUPLICATE_RECORD;
	extern const long ERR_INSTR_CANNOT_COEXIST;
}

namespace ifds
{
	extern CLASS_IMPORT const BFTextFieldId MatInstrLevel;
	extern CLASS_IMPORT const BFDecimalFieldId Amount;
	extern CLASS_IMPORT const BFDecimalFieldId InvHisAcurdToDate;
	extern CLASS_IMPORT const BFTextFieldId IntInvestType;
	extern CLASS_IMPORT const BFTextFieldId IntCalcMthd;
	extern CLASS_IMPORT const BFIntegerFieldId InvestTerm;
	extern CLASS_IMPORT const BFTextFieldId IntCredFreq;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
	// Field DD Id,					State Flags,	    Group Flags 
	{ ifds::AccountNum,				BFCBO::NONE,		0 },
	{ ifds::Fund,					BFCBO::NONE,		0 },
	{ ifds::Class,					BFCBO::NONE,		0 },
	{ ifds::TransNum,				BFCBO::NONE,		0 },
	{ ifds::Amount,				    BFCBO::NONE,		0 },
	{ ifds::TransId,				BFCBO::NONE,		0 },
	{ ifds::InvHisAcurdToDate,		BFCBO::NONE,		0 },
    { ifds::IntInvestId,			BFCBO::NONE,		0 },
	// GI Attrib fields
	{ ifds::IntInvestType,			BFCBO::CALCULATED_FIELD, 0 }, 
	{ ifds::IntCalcMthd,			BFCBO::CALCULATED_FIELD, 0 }, 
	{ ifds::InvestTerm,				BFCBO::CALCULATED_FIELD, 0 }, 
	{ ifds::IntCredFreq,			BFCBO::CALCULATED_FIELD, 0 }, 
};


static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//******************************************************************************
MatSweepInstrList::MatSweepInstrList( BFAbstractCBO &parent )
: MFCanBFCbo (parent)
, m_requestData (ifds::DSTC0427_REQ)
,m_dstrMatSwp (NULL_STRING)
,m_dstrLevel (NULL_STRING)
{
	TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );		
	setObjectAsList( );  	
}

//******************************************************************************
MatSweepInstrList::~MatSweepInstrList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY MatSweepInstrList::init( const DString& dstrAccountNum,
                                  const DString& dstrInstructionType,
								  const DString& dstrFund,
								  const DString& dstrClass,
								  const DString& dstrTransNum,
								  const DString& dstrTransId,
								  const DString& dstrIntInvestId,
								  const DString& dstrLevel,
								  const DString& dstrAmount,
								  const DString& dstrAccuredAmount,
								  const BFDataGroupId& idDataGroup,
                                  const DString& dstrTrack,
                                  const DString& dstrPageName)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ));	

	m_dstrMatSwp = dstrInstructionType;
	m_dstrLevel = dstrLevel;
   setFieldNoValidate (ifds::AccountNum, dstrAccountNum, idDataGroup);
   setFieldNoValidate (ifds::Fund, dstrFund, idDataGroup);
   setFieldNoValidate (ifds::Class, dstrClass, idDataGroup);
   setFieldNoValidate (ifds::TransNum, dstrTransNum, idDataGroup);
   setFieldNoValidate (ifds::Amount, dstrAmount, idDataGroup);
   setFieldNoValidate (ifds::TransId, dstrTransId, idDataGroup);
   setFieldNoValidate (ifds::InvHisAcurdToDate, dstrAccuredAmount, idDataGroup);
   setFieldNoValidate (ifds::IntInvestId, dstrIntInvestId, idDataGroup);
   
   m_requestData.setElementValue (ifds::AccountNum, dstrAccountNum);
	m_requestData.setElementValue (ifds::InstrType, dstrInstructionType);
	m_requestData.setElementValue (ifds::Fund, dstrFund);
	m_requestData.setElementValue (ifds::Class, dstrClass);
	m_requestData.setElementValue (ifds::TransNum, dstrTransNum);
	m_requestData.setElementValue (ifds::TransId, dstrTransId);
	m_requestData.setElementValue (ifds::IntInvestId, dstrIntInvestId);
	//m_requestData.setElementValue (ifds::NextKey, NULL_STRING);
	m_requestData.setElementValue (ifds::Track, dstrTrack);
  
	DString mgmtCoIdOut;
	m_requestData.setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut));
	
	ReceiveData ( DSTC_REQUEST::CASHSWEEP_MATURITY_INSTR_INQUIRY,  
                 m_requestData, 
                 ifds::DSTC0427_VW, 
                 DSTCRequestor (getSecurity(), true));
	return GETCURRENTHIGHESTSEVERITY();
}

//*************************************************************************************
SEVERITY MatSweepInstrList::doCreateObject (const BFData& data, BFCBO*& pObjOut)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );
   	
	pObjOut = new MatSweepInstr( *this );
	((MatSweepInstr* )pObjOut)->init (const_cast<BFData&>(data), m_dstrMatSwp, m_dstrLevel);

	return GETCURRENTHIGHESTSEVERITY ();
}

//**************************************************************************************
SEVERITY MatSweepInstrList::doCreateNewObject ( BFCBO *&pObjOut, DString &strKey, const BFDataGroupId& idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("doCreateNewObject"));
   	
   pObjOut = new MatSweepInstr(*this );

   DString accountNum;
   getField (ifds::AccountNum, accountNum, idDataGroup, false);
   ((MatSweepInstr* )pObjOut)->initNew (accountNum, m_dstrMatSwp, m_dstrLevel, idDataGroup);

	return GETCURRENTHIGHESTSEVERITY();
}

//*******************************************************************************
SEVERITY MatSweepInstrList::doValidateAll (const BFDataGroupId& idDataGroup, long lValidateGroup)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateAll" ));

	
	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY MatSweepInstrList::clone ( const DString& objectKey, 
                                    const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("clone" ));
   
   if (!objectKey.empty()) //the object key is the key of the object that should be cloned...
   {
      BFObjIter iter (*this, idDataGroup, true);
      
      iter.positionByKey (objectKey);
      if (!iter.end())
      {
         MatSweepInstr *pMatSweepInstrToBeCloned = dynamic_cast <MatSweepInstr*> (iter.getObject ());

         BFObjectKey objKey (NULL_STRING, idDataGroup);
         MatSweepInstr *pMatSweepInstrClone = dynamic_cast <MatSweepInstr*> (getNewListItem (objKey));

         if (pMatSweepInstrClone)
         {
            pMatSweepInstrClone->initClone (pMatSweepInstrToBeCloned, idDataGroup);
			pMatSweepInstrClone->setFieldUpdated (ifds::MatInstrLevel, idDataGroup, true); //set the obj dirty
         }
      }
   }
	return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
SEVERITY MatSweepInstrList::checkDuplicate (const MatSweepInstr *pMatSweepInstrToCheck, 
											const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_( "checkDuplicate" ) );   	
	
	DString dstrFundToCheck, dstrClassToCheck, dstrInstrTypeToCheck, dstrGoodBadToCheck, dstrLevelToCheck;
	
	pMatSweepInstrToCheck->getField( ifds::Fund, dstrFundToCheck, idDataGroup );
	pMatSweepInstrToCheck->getField( ifds::Class, dstrClassToCheck, idDataGroup );
	pMatSweepInstrToCheck->getField( ifds::MatSwpInstructionType, dstrInstrTypeToCheck, idDataGroup );
	pMatSweepInstrToCheck->getField( ifds::GoodBad, dstrGoodBadToCheck, idDataGroup );
	pMatSweepInstrToCheck->getField( ifds::MatInstrLevel, dstrLevelToCheck, idDataGroup );

	dstrFundToCheck.strip ();
	dstrClassToCheck.strip().upperCase();
	dstrInstrTypeToCheck.strip();
	dstrGoodBadToCheck.strip ();

	bool bHasDuplicate = false;
	
	//check first whether in the list (in memory) we have a duplicate
	BFObjIter iter( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED );
	iter.begin();
	
	while (!iter.end())
	{
		MatSweepInstr *pMatSweepInstr = dynamic_cast<MatSweepInstr*>(iter.getObject());
		// Don't check against itself
		if ( pMatSweepInstr != pMatSweepInstrToCheck )
		{
			DString dstrFund, dstrClass, dstrInstrType, dstrGoodBad, dstrLevel;

			pMatSweepInstr->getField( ifds::Fund, dstrFund, idDataGroup );
			pMatSweepInstr->getField( ifds::Class, dstrClass, idDataGroup );
			pMatSweepInstr->getField( ifds::MatSwpInstructionType, dstrInstrType, idDataGroup );
			pMatSweepInstr->getField( ifds::GoodBad, dstrGoodBad, idDataGroup );
			pMatSweepInstr->getField( ifds::MatInstrLevel, dstrLevel, idDataGroup );


			dstrFund.strip ();
			dstrClass.strip().upperCase();
			dstrInstrType.strip();
			dstrGoodBad.strip ().upperCase ();

			if (dstrGoodBad == I_("N"))
			{
				++iter;
				continue;
			}

			if ( dstrFund  == dstrFundToCheck &&
				dstrClass == dstrClassToCheck &&
				dstrInstrType == dstrInstrTypeToCheck &&
				dstrGoodBad == dstrGoodBadToCheck &&
				dstrLevel == dstrLevelToCheck)
			{
				bHasDuplicate = true;
				break;
			}
		}
		++iter;
	}

	if (bHasDuplicate)
	{
		ADDCONDITIONFROMFILE(CND::ERR_DUPLICATE_RECORD);
	}

	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************

SEVERITY MatSweepInstrList::checkActiveDuplicate (const MatSweepInstr *pMatSweepInstrToCheck, 
							                      DString &dstrHasDuplicate,
							                      const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_( "checkActiveDuplicate" ) );   	
	
	DString dstrFundToCheck, dstrClassToCheck, dstrInstrTypeToCheck, dstrGoodBadToCheck, dstrLevelToCheck;
	
	pMatSweepInstrToCheck->getField( ifds::Fund, dstrFundToCheck, idDataGroup );
	pMatSweepInstrToCheck->getField( ifds::Class, dstrClassToCheck, idDataGroup );
	pMatSweepInstrToCheck->getField( ifds::MatSwpInstructionType, dstrInstrTypeToCheck, idDataGroup );
	pMatSweepInstrToCheck->getField( ifds::GoodBad, dstrGoodBadToCheck, idDataGroup );
	//pMatSweepInstrToCheck->getField( ifds::MatInstrLevel, dstrLevelToCheck, idDataGroup );

	dstrFundToCheck.strip ();
	dstrClassToCheck.strip().upperCase();
	dstrInstrTypeToCheck.strip();
	dstrGoodBadToCheck.strip ();

	dstrHasDuplicate = I_("N");
	
	//check first whether in the list (in memory) we have a duplicate
	BFObjIter iter( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED );
	iter.begin();
	
	while (!iter.end())
	{
		MatSweepInstr *pMatSweepInstr = dynamic_cast<MatSweepInstr*>(iter.getObject());
		// Don't check against itself
		if ( pMatSweepInstr != pMatSweepInstrToCheck )
		{
			DString dstrFund, dstrClass, dstrInstrType, dstrGoodBad, dstrLevel;

			pMatSweepInstr->getField( ifds::Fund, dstrFund, idDataGroup );
			pMatSweepInstr->getField( ifds::Class, dstrClass, idDataGroup );
			pMatSweepInstr->getField( ifds::MatSwpInstructionType, dstrInstrType, idDataGroup );
			pMatSweepInstr->getField( ifds::GoodBad, dstrGoodBad, idDataGroup );
			//pMatSweepInstr->getField( ifds::MatInstrLevel, dstrLevel, idDataGroup );


			dstrFund.strip ();
			dstrClass.strip().upperCase();
			dstrInstrType.strip();
			dstrGoodBad.strip ().upperCase ();

			if (dstrGoodBad == I_("N"))
			{
				++iter;
				continue;
			}

			if ( dstrFund  == dstrFundToCheck &&
				dstrClass == dstrClassToCheck &&
				dstrInstrType == dstrInstrTypeToCheck &&
				dstrGoodBad == dstrGoodBadToCheck /*&&
				dstrLevel == dstrLevelToCheck*/)
			{
				dstrHasDuplicate = I_("Y");
				break;
			}
		}
		++iter;
	}

	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY MatSweepInstrList::validateMaturityInterestInstr (const MatSweepInstr *pMatSweepInstrToCheck, const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateMaturityInterestInstr" ) );   	
	
	DString dstrFundToCheck, dstrClassToCheck, dstrInstrTypeToCheck, dstrGoodBadToCheck, dstrLevelToCheck;
	int iMaturity = 0;
	int iInterest = 0;
	int iMaturityInterest = 0;
	
	pMatSweepInstrToCheck->getField( ifds::Fund, dstrFundToCheck, idDataGroup );
	pMatSweepInstrToCheck->getField( ifds::Class, dstrClassToCheck, idDataGroup );
	pMatSweepInstrToCheck->getField( ifds::MatSwpInstructionType, dstrInstrTypeToCheck, idDataGroup );
	pMatSweepInstrToCheck->getField( ifds::MatInstrLevel, dstrLevelToCheck, idDataGroup );

	dstrFundToCheck.strip ().upperCase ();
	dstrClassToCheck.strip().upperCase();

	if (dstrInstrTypeToCheck == MATURITY) 
	{
		iMaturity++;
	}
	else if (dstrInstrTypeToCheck == INTEREST)
	{
		iInterest++;
	}
	else if (dstrInstrTypeToCheck == MATURITY_INTEREST)
	{
		iMaturityInterest++;
	}
	
	//check first whether in the list (in memory) we have a duplicate
	BFObjIter iter( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED );
	iter.begin();
	
	while (!iter.end())
	{
		MatSweepInstr *pMatSweepInstr = dynamic_cast<MatSweepInstr*>(iter.getObject());
		// Don't check against itself
		if ( pMatSweepInstr != pMatSweepInstrToCheck )
		{
			DString dstrFund, dstrClass, dstrInstrType, dstrGoodBad, dstrLevel;

			pMatSweepInstr->getField( ifds::Fund, dstrFund, idDataGroup );
			pMatSweepInstr->getField( ifds::Class, dstrClass, idDataGroup );
			pMatSweepInstr->getField( ifds::MatSwpInstructionType, dstrInstrType, idDataGroup );
			pMatSweepInstr->getField( ifds::GoodBad, dstrGoodBad, idDataGroup );
			pMatSweepInstr->getField( ifds::MatInstrLevel, dstrLevel, idDataGroup );


			dstrFund.strip ().upperCase ();
			dstrClass.strip().upperCase();
			dstrGoodBad.strip ().upperCase ();

			if (dstrGoodBad == I_("N"))
			{
				++iter;
				continue;
			}

			if ( dstrFund  == dstrFundToCheck &&
				dstrClass == dstrClassToCheck && 
				dstrLevel == dstrLevelToCheck)
			{
				if (dstrInstrType == MATURITY) 
				{
					iMaturity++;
				}
				else if (dstrInstrType == INTEREST)
				{
					iInterest++;
				}
				else if (dstrInstrType == MATURITY_INTEREST)
				{
					iMaturityInterest++;
				}
			}
		}
		++iter;
	}

	if ((iMaturity > 0 || iInterest > 0) && iMaturityInterest > 0)
	{
		ADDCONDITIONFROMFILE(CND::ERR_INSTR_CANNOT_COEXIST);
	}

	return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
SEVERITY MatSweepInstrList::setTransId (const DString &dstrTransId, const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setTransId" ) );   	
	
	BFObjIter iter( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED );
	iter.begin();
	
	while (!iter.end())
	{
		MatSweepInstr *pMatSweepInstr = dynamic_cast<MatSweepInstr*>(iter.getObject());
		
		if (pMatSweepInstr)
		{
			pMatSweepInstr->setField (ifds::TransId, dstrTransId, idDataGroup );
		}
		++iter;
	}

	return GETCURRENTHIGHESTSEVERITY();
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/MatSweepInstrList.cpp-arc  $
// 
//    Rev 1.17   Jun 08 2012 14:11:14   jankovii
// IN 2957854 - P0186477_FN05_03_Same transno. in distrib-delt to be used & changes to misc-info
// 
//    Rev 1.16   Apr 05 2012 14:16:08   jankovii
// IN 2904085 - Automatin Instructions - For reinvestment, the destination fileds s/s pre-popula
// 
//    Rev 1.15   Mar 28 2012 15:27:34   jankovii
// IN 2889383 - P0186477_FN05_Maturity Processing Dsktp issues_LIST 1_Seg_intrnl errr_min issues
// 
//    Rev 1.14   Mar 07 2012 14:18:14   jankovii
// IN 2873354 - P0186477FN03- Deleting Instruction on Processed Investments
// 
//    Rev 1.13   Mar 05 2012 11:22:30   jankovii
// IN 2859411 - P0186477_FN02_Interest Instruction-Err displayed on split type 'Amount' instrctn
// 
//    Rev 1.12   Feb 06 2012 10:55:24   jankovii
// IN 2835682 - P0186477FN03 -Database error when accessing Maturity/ Interest Screen
// 
//    Rev 1.11   Feb 01 2012 16:52:06   jankovii
// IN 2826242- Maturity/Interest Instruction on Trading Screen
// 
//    Rev 1.10   Jan 31 2012 19:14:52   jankovii
// IN 2826242- Maturity/Interest Instruction on Trading Screen
// 
//    Rev 1.9   Jan 20 2012 09:47:44   jankovii
// IN 2813487 - P0186477FN03 - Cash Sweep DSK Issues
// 
//    Rev 1.8   Jan 11 2012 16:00:44   jankovii
// P0186477 FN03- GIA Maturity/Cash Sweep Instructions
// 
//    Rev 1.7   Jan 06 2012 12:28:14   jankovii
// P0186477 FN03- GIA Maturity/Cash Sweep Instructions
// 
//    Rev 1.6   Dec 26 2011 09:43:38   kitticha
// P0186477 FN03- GIA Maturity/Cash Sweep Instructions - Removed NextKey logic.
// 
//    Rev 1.5   Dec 20 2011 17:39:28   popescu
// P0186477 FN03- GIA Maturity/Cash Sweep Instructions
// 
//    Rev 1.4   Dec 19 2011 20:33:28   jankovii
// P0186477 FN03- GIA Maturity/Cash Sweep Instructions
// 
//    Rev 1.3   Dec 16 2011 15:50:12   popescu
// P0186477 FN03- GIA Maturity/Cash Sweep Instructions
// 
//    Rev 1.2   Dec 14 2011 16:55:26   popescu
// P0186477 FN03- GIA Maturity/Cash Sweep Instructions
 * 
 * 
 */
