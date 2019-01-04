#pragma once
#define DISABLE_MACRO_REDEFINITION_WARNINGS 1




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
// ^FILE   : CommitmentProductList.hpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : CommitmentProductList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE CommitmentProductList : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   CommitmentProductList( BFAbstractCBO &parent );
   virtual ~CommitmentProductList();

   // Initialize function
   SEVERITY init();
   SEVERITY doCreateObject( const BFData& data, BFCBO *&pObjOut );
   virtual void getStrKey( DString &strKey, const BFData *data );
   SEVERITY getSubstitutionList(DString& dstrSubstitutionList, const BFDataGroupId& idDataGroup = BF::HOST);
   bool isCommitmentProductEnded(const DString& productUUID, const BFDataGroupId& idDataGroup = BF::HOST);
   SEVERITY getActiveCommitment(DString& dstrCommitUUID, const BFDataGroupId& idDataGroup);

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/CommitmentProductList.hpp-arc  $
//
//   Rev 1.2   Mar 02 2012 12:54:50   if991250
//Account Commitment in NASU
//
//   Rev 1.1   Feb 27 2012 15:34:22   if991250
//NASU, Commitment Id
//
//   Rev 1.0   Feb 24 2012 18:10:54   if991250
//Initial revision.
// 
*/

