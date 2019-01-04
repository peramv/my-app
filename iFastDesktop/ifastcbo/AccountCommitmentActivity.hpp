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
// ^FILE   : AccountCommitmentActivity.hpp
//
// ^CLASS    : AccountCommitmentActivity
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

class IFASTCBO_LINKAGE AccountCommitmentActivity : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   AccountCommitmentActivity( BFAbstractCBO &parent );
   virtual ~AccountCommitmentActivity( void );
   SEVERITY init(const BFData& data);
};

///#endif

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AccountCommitmentActivity.hpp-arc  $
//
//   Rev 1.1   Feb 22 2012 16:56:42   if991250
//Account Commitment
//
//   Rev 1.0   Feb 17 2012 10:22:20   if991250
//Initial revision.
 *
 */