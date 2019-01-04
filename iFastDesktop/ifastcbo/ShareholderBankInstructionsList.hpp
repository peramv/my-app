#pragma once

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
//    Copyright 1999 by DST Canada, Inc.
//
//
//******************************************************************************
//
// ^FILE   : ShareholderBankInstructionsList.hpp
// ^AUTHOR : Serban Popescu
// ^DATE   : May, 2003
//
// ^CLASS    : ShareholderBankInstructionsList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <boost\utility.hpp>
#include <ifastcbo\mfcancbo.hpp>
#include <ifastcbo\bankinstructions4shlist.hpp>


#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

typedef std::map<DString, DString> AccountBankingInstListMap; 
typedef AccountBankingInstListMap::iterator AccountBankingInstListMapIter;
typedef AccountBankingInstListMap::value_type ACCT_BANKING_INSTR;

namespace BANKENTITY
{
   extern CLASS_IMPORT I_CHAR * const SHAREHOLDER;
   extern CLASS_IMPORT I_CHAR * const ACCOUNT;
}

class IFASTCBO_LINKAGE ShareholderBankInstructionsList : 
   public BankInstructions4ShList
{
public:
   // X-structors
   ShareholderBankInstructionsList(BFAbstractCBO &parent);
   virtual ~ShareholderBankInstructionsList();

   // Initialize function
   SEVERITY initNew (const DString& dstrNum, 
                     const BFDataGroupId& idDataGroup,
                     const DString& dstrBankEntity = BANKENTITY::SHAREHOLDER );
   SEVERITY init (const DString& dstrNum, 
                  const DString& dstrTrack = I_("N"), 
                  const DString& dstrPageName = NULL_STRING,
                  const DString& dstrBankEntity = BANKENTITY::SHAREHOLDER );
   void getBankingConfiguration(DString& dstrBankingLevel, const BFDataGroupId& idDataGroup);
   void insertToAccountBankingInstrMap(const DString& dstrAcctNum );
   bool ShareholderBankInstructionsList::isNotInAccountBankingInstrMap(const DString& dstrAcctNum, const BFDataGroupId& idDataGroup);

private:

   DString m_dstrAcctNum;
   AccountBankingInstListMap m_AccountBankingInstListMap;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/ShareholderBankInstructionsList.hpp-arc  $
//
//   Rev 1.4   Nov 14 2004 14:55:26   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.3   Nov 10 2003 14:53:06   popescu
//Revised the names of the suppporting objects based on Desktop's naming standards
//
//   Rev 1.2   Oct 19 2003 16:44:54   popescu
//CIBC, PET809, FN 13 banking work
//
//   Rev 1.1   Oct 06 2003 12:44:28   popescu
//Added banking support for DirectTrading enhancement
//
//   Rev 1.0   May 31 2003 12:01:00   popescu
//Initial revision.
//
 */
