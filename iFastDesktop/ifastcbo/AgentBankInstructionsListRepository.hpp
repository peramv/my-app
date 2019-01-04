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
// ^FILE   : AgentBankInstructionsListRepository.hpp
// ^AUTHOR : Robbins Kuriakose
// ^DATE   : Feb, 2010
//
// ^CLASS    : AgentBankInstructionsListRepository
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <boost\utility.hpp>
#include <ifastcbo\mfcancbo.hpp>
#include <ifastdataimpl\dse_dstc0052_req.hpp>

class RegAgentBankInstructionsList;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE AgentBankInstructionsListRepository : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   AgentBankInstructionsListRepository(BFAbstractCBO &parent);
   virtual ~AgentBankInstructionsListRepository();

   // Initialize function
   SEVERITY init (const BFDataGroupId &idDataGroup = BF::HOST, 
                  const DString& dstrTrack = I_("N"), 
                  const DString& dstrPageName = NULL_STRING);

   SEVERITY getRegAgentBankInstructionsList(const DString& dstrRegAgent, 
                                            RegAgentBankInstructionsList *&pRegAgentBankInstructionsList, 
                                            const BFDataGroupId &idDataGroup, 
                                            const DString& dstrTrack = I_("N"), 
                                            const DString& dstrPageName = NULL_STRING);
private:
   void buildKeyRegAgent( const DString& dstrRegAgentCode,DString& dstrKey);

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AgentBankInstructionsListRepository.hpp-arc  $
//
//   Rev 1.0   Apr 03 2012 21:31:34   wp040039
//Initial revision.

//
 */
