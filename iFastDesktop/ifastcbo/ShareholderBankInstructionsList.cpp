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
// ^FILE   : ShareholderBankInstructionsList.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : May, 2003
//
// ^CLASS    : ShareholderBankInstructionsList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "shareholderbankinstructionslist.hpp"
#include "BankInstructions4ShList.hpp"
#include "Shareholder.hpp"

namespace
{
   // Trace literals
   const I_CHAR *  CLASSNAME = I_ ("ShareholderBankInstructionsList");
}

namespace BANKENTITY
{
   extern CLASS_IMPORT I_CHAR * const SHAREHOLDER;
   extern CLASS_IMPORT I_CHAR * const ACCOUNT;
}
namespace BANKTYPE
{
   extern CLASS_IMPORT I_CHAR * const SHAREHOLDER;
   extern CLASS_IMPORT I_CHAR * const ACCOUNT;
}
namespace BANKINGLEVEL
{
   extern CLASS_IMPORT I_CHAR *  const SHAREHOLDER_LEVEL ;
   extern CLASS_IMPORT I_CHAR *  const ACCOUNT_LEVEL ;
   extern CLASS_IMPORT I_CHAR *  const SHAREHOLDER_AND_ACCOUNT_LEVEL ;
}

namespace ifds
{
 extern CLASS_IMPORT const BFTextFieldId BankingLevel;
 extern CLASS_IMPORT const  BFNumericFieldId AccountNum;
}
//******************************************************************************
ShareholderBankInstructionsList::ShareholderBankInstructionsList (BFAbstractCBO &parent)
: BankInstructions4ShList (parent)
{
   TRACE_CONSTRUCTOR (CLASSNAME, NULL_STRING);
   setObjectAsList ();
}

//******************************************************************************
ShareholderBankInstructionsList::~ShareholderBankInstructionsList ()
{
   TRACE_DESTRUCTOR (CLASSNAME);
}

//******************************************************************************
SEVERITY ShareholderBankInstructionsList::initNew (const DString& dstrNum, 
                                                   const BFDataGroupId& idDataGroup,
                                                   const DString& dstrBankEntity /*= SHAREHOLDER*/)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("init"));
  
   if( BANKENTITY::SHAREHOLDER ==  dstrBankEntity)
       BankInstructions4ShList::initNew (dstrNum, BANKTYPE::SHAREHOLDER, idDataGroup);
   else if( BANKENTITY::ACCOUNT ==  dstrBankEntity)
       BankInstructions4ShList::initNew (dstrNum, BANKTYPE::ACCOUNT, idDataGroup);  
   return GETCURRENTHIGHESTSEVERITY ();
}
//******************************************************************************
SEVERITY ShareholderBankInstructionsList::init (const DString& dstrNum, 
                                                const DString& dstrTrack /*= I_ ("N")*/, 
                                                const DString& dstrPageName /*= NULL_STRING*/,
                                                const DString& dstrBankEntity /*= SHAREHOLDER*/ )
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("init"));
   if( BANKENTITY::SHAREHOLDER ==  dstrBankEntity)
       BankInstructions4ShList::init (dstrNum, BANKTYPE::SHAREHOLDER, dstrTrack, dstrPageName);
   else if( BANKENTITY::ACCOUNT ==  dstrBankEntity)
       BankInstructions4ShList::init (dstrNum, BANKTYPE::ACCOUNT, dstrTrack, dstrPageName);
   return GETCURRENTHIGHESTSEVERITY ();
}
//******************************************************************************
void ShareholderBankInstructionsList::getBankingConfiguration(DString& dstrBankingLevel, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("getBankingConfiguration"));

   DString dstrBankEntity;
   getWorkSession ().getOption ( ifds::BankingLevel, dstrBankingLevel, BF::HOST, false);
   if(dstrBankingLevel.empty())
      dstrBankingLevel = BANKINGLEVEL::SHAREHOLDER_LEVEL;//if no anking present use shareholder
}
//******************************************************************************
void ShareholderBankInstructionsList::insertToAccountBankingInstrMap(const DString& dstrAcctNum )
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("insertToAccountBankingInstrMap"));

   m_AccountBankingInstListMap.insert(ACCT_BANKING_INSTR(dstrAcctNum,dstrAcctNum));
}
//******************************************************************************
bool ShareholderBankInstructionsList::isNotInAccountBankingInstrMap(const DString& dstrAcctNum, const BFDataGroupId& idDataGroup)
{
  MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("isNotInAccountBankingInstrMap"));

  AccountBankingInstListMapIter iter = m_AccountBankingInstListMap.find(dstrAcctNum);
  return (iter == m_AccountBankingInstListMap.end());
} 

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/ShareholderBankInstructionsList.cpp-arc  $
// 
//    Rev 1.5   Nov 14 2004 14:55:26   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.4   Nov 10 2003 14:53:02   popescu
// Revised the names of the suppporting objects based on Desktop's naming standards
// 
//    Rev 1.3   Oct 19 2003 16:44:54   popescu
// CIBC, PET809, FN 13 banking work
// 
//    Rev 1.2   Oct 06 2003 12:44:24   popescu
// Added banking support for DirectTrading enhancement
// 
//    Rev 1.1   May 31 2003 20:30:52   popescu
// RRIF work part ||
// 
//    Rev 1.0   May 31 2003 12:01:00   popescu
// Initial revision.
 */