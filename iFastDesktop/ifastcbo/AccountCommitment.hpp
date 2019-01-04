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
// ^FILE   : AccountCommitment.hpp
//
// ^CLASS    : AccountCommitment
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************


#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>
///#endif

class AccountCommitmentDetailsList;
class AcctCommitBankList;
class CommitmentProductList;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE AccountCommitment : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   AccountCommitment( BFAbstractCBO &parent );
   virtual ~AccountCommitment( void );

   SEVERITY init(const DString& dstrAcctNum);
   SEVERITY initNew(const BFDataGroupId& idDataGroup);
   SEVERITY getCommitmentDetails( AccountCommitmentDetailsList *&pAccountCommitmentDetailsList, const BFDataGroupId& idDataGroup);
   SEVERITY getBankInstructionsList(AcctCommitBankList *&pAcctCommitBankList, const BFDataGroupId& idDataGroup, bool bCreate = true);
   SEVERITY getCommitmentProductList(CommitmentProductList *&pCommitmentProductList);
   virtual SEVERITY doValidateField( const BFFieldId &fieldId,
                                     const DString& strValue,
                                     const BFDataGroupId& idDataGroup );

   virtual SEVERITY doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup );
   SEVERITY validateNextDrawDate( const BFDataGroupId& idDataGroup );
   SEVERITY validateEffectiveDate( const BFDataGroupId& idDataGroup);
   SEVERITY loadFileProcessor(const BFDataGroupId& idDataGroup);
   
private:
	void getNextPACLeapDate(DString &dstrNextPACLeapDate, const BFDataGroupId& idDataGroup);
	bool hasProcessedPAC(const BFDataGroupId& idDataGroup);

	DString _nextPACLeapDate;
    DString _dstrNewPACDeff;
    DString _dstrNewPACDrawDeff;
};

///#endif

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AccountCommitment.hpp-arc  $
//
//   Rev 1.5   Jun 26 2012 17:34:58   if991250
//PAC Draw Date
//
//   Rev 1.4   Mar 02 2012 12:55:14   if991250
//Account Commitment in NASU
//
//   Rev 1.3   Feb 27 2012 15:33:38   if991250
//NASU, Commitment Id
//
//   Rev 1.2   Feb 24 2012 18:40:18   if991250
//Account Commitment
//
//   Rev 1.1   Feb 17 2012 10:25:06   if991250
//Account Commitment
//
//   Rev 1.0   Feb 14 2012 13:26:22   if991250
//Initial revision.
 *
 */