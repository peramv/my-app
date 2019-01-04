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
// ^FILE   : DistributorBankInstructionsList.hpp
// ^AUTHOR : Serban Popescu
// ^DATE   : May, 2003
//
// ^CLASS    : DistributorBankInstructionsList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <boost\utility.hpp>
#include <ifastcbo\mfcancbo.hpp>
#include <ifastcbo\bankinstructionslist.hpp>


#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE DistributorBankInstructionsList : public BankInstructionsList
{
public:
   // X-structors
   DistributorBankInstructionsList(BFAbstractCBO &parent);
   virtual ~DistributorBankInstructionsList();

   // Initialize function
   SEVERITY init( const DString &dstrBrokerCode,  
                  const DString &dstrBranchCode, 
		            const DString &dstrSlsRepCode,
                  const BFDataGroupId &idDataGroup,
                  const DString &dstrTrack = I_("N"), 
                  const DString &dstrPageName = NULL_STRING);
   void setPayInstructionsAsParentCBO  (BFAbstractCBO * payInstructionsParent);
   BFAbstractCBO * getPayInstructionsParentCBO  ();
protected:
   SEVERITY doCreateNewObject ( BFCBO*& pBase, 
                                DString& strKey, 
                                const BFDataGroupId& idDataGroup);
private:
   DString _bankType;
   BFAbstractCBO *_parentCBO;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DistributorBankInstructionsList.hpp-arc  $
//
//   Rev 1.4   Sep 10 2006 17:59:00   popescu
//STP 2192/12
//
//   Rev 1.3   Jul 31 2006 15:34:40   ZHANGCEL
//PET2192 FN11 -- MgmtCo Banking related changes
//
//   Rev 1.2   Nov 14 2004 14:30:58   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.1   Aug 17 2003 16:16:52   popescu
//Use DistributorBankInstructions objects as children objects 
//
//   Rev 1.0   May 31 2003 12:00:46   popescu
//Initial revision.
//
 */
