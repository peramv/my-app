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
// ^FILE   : RegAgentBankInstructionsList.hpp
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


class IFASTCBO_LINKAGE RegAgentBankInstructionsList : public BankInstructionsList
{
public:

   RegAgentBankInstructionsList (BFAbstractCBO &parent);
   virtual ~RegAgentBankInstructionsList();

   SEVERITY init( const DString& regAgent, 
                  const BFDataGroupId &idDataGroup,
                  const DString &dstrTrack = I_("N"), 
                  const DString &dstrPageName = NULL_STRING);
};
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/RegAgentBankInstructionsList.hpp-arc  $
//
//   Rev 1.1   Apr 03 2012 21:52:52   wp040039
//PETP0187485-Registartion Agent  Banking
//Implementing code review comments.
//

