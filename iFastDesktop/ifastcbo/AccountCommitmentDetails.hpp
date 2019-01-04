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
//    Copyright 2000 by DST Canada, Inc.
//
//
//******************************************************************************
//
// ^FILE   : AccountCommitmentDetails.hpp
//
// ^CLASS    : AccountCommitmentDetails
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************


#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>
///#endif


#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class AccountCommitmentActivityList;

class IFASTCBO_LINKAGE AccountCommitmentDetails : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   AccountCommitmentDetails( BFAbstractCBO &parent );
   virtual ~AccountCommitmentDetails( void );
   SEVERITY init(const BFData& data);
   SEVERITY getAccountCommitmentActivityList(AccountCommitmentActivityList *&pAccountCommitmentActivityList);
};

///#endif

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AccountCommitmentDetails.hpp-arc  $
//
//   Rev 1.1   Feb 22 2012 16:57:22   if991250
//Account Commitment
//
//   Rev 1.0   Feb 17 2012 10:22:48   if991250
//Initial revision.
 *
 */