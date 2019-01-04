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
// ^FILE   : FundSponsorBankInstructionsList.hpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : 
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

class IFASTCBO_LINKAGE FundSponsorBankInstructionsList : public BankInstructionsList
{
public:

   FundSponsorBankInstructionsList (BFAbstractCBO &parent);
   virtual ~FundSponsorBankInstructionsList();

   SEVERITY init( const DString& fundSponsor, 
                  const BFDataGroupId &idDataGroup,
                  const DString &dstrTrack = I_("N"), 
                  const DString &dstrPageName = NULL_STRING);
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
