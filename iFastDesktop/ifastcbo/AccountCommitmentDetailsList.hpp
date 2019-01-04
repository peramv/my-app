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
// ^FILE   : AccountCommitmentDetailsList.hpp
//
// ^CLASS    : AccountCommitmentDetailsList
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

class IFASTCBO_LINKAGE AccountCommitmentDetailsList : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   AccountCommitmentDetailsList( BFAbstractCBO &parent );
   virtual ~AccountCommitmentDetailsList( void );

   SEVERITY init(const DString& dstrdstrAcctCommitMstrUUID);
   virtual SEVERITY doCreateObject( const BFData& data, BFCBO *&pObjOut );
   virtual void AccountCommitmentDetailsList::getStrKey( DString &strKey, const BFData *data = NULL );
};

///#endif

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AccountCommitmentDetailsList.hpp-arc  $
//
//   Rev 1.1   Feb 22 2012 16:57:44   if991250
//Account Commitment
//
//   Rev 1.0   Feb 17 2012 10:23:02   if991250
//Initial revision.
 *
 */