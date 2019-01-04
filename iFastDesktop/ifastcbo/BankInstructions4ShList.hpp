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
// ^FILE   : BankInstructions4ShList.hpp
// ^AUTHOR : Serban Popescu
// ^DATE   : October, 2003
//
// ^CLASS    : BankInstructions4ShList
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

class IFASTCBO_LINKAGE BankInstructions4ShList : public BankInstructionsList
{
public:
   // X-structors
   BankInstructions4ShList(BFAbstractCBO &parent);
   virtual ~BankInstructions4ShList();
   SEVERITY doValidateAll(const BFDataGroupId& idDataGroup, long lValidateGroup);
protected:
   // Initialize function
   SEVERITY initNew (const DString &shrNum, 
      const DString &bankType,
      const BFDataGroupId &idDataGroup);
   SEVERITY init (const DString &dstrShrNum, 
      const DString &bankType,
      const DString& dstrTrack = I_("N"), 
      const DString& dstrPageName = NULL_STRING);
private:
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/BankInstructions4ShList.hpp-arc  $
//
//   Rev 1.0   Nov 10 2003 14:55:02   popescu
//Initial revision.
//
//   Rev 1.1   Oct 23 2003 17:52:08   FENGYONG
//Override DoValidateAll
//
//   Rev 1.0   Oct 19 2003 19:08:34   popescu
//Initial revision.
//
 */
