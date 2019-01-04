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
//    Copyright 1999 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE     : UserDefMat.hpp
// ^CLASS    : UserDefMat
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

class MasterContractList;
class ContractInfo;

class IFASTCBO_LINKAGE UserDefMat : public MFCanBFCbo, private boost::noncopyable
{
public:

   UserDefMat( BFAbstractCBO &parent );
   virtual ~UserDefMat();
   SEVERITY init( const BFData& data, const DString &contractType );
   SEVERITY init( const BFDataGroupId& idDataGroup );
   virtual SEVERITY doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup );
   virtual SEVERITY doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup );
   SEVERITY getContractInfo(ContractInfo*& pContractInfo, MFAccount* pMFAccount, const BFDataGroupId& idDataGroup);

protected:

   void doInitWithDefaultValues( const BFDataGroupId& idDataGroup );
   bool getDofBirth( const BFDataGroupId& idDataGroup, DString &dstrDofBirth );

private:

   SEVERITY ValidateMaturityDate( const DString& strValue, const BFDataGroupId& idDataGroup );
   SEVERITY getMasterContractList(MasterContractList*& _pMasterContractList, const BFDataGroupId& idDataGroup);
   SEVERITY getMasterMinTermAndMinMaxAge( DString& dstrMinTerm, DString& dstrMinAge, DString& dstrMaxAge, 
      const BFDataGroupId& idDataGroup);
   SEVERITY getMasterContract(BFAbstractCBO*& _pMasterContract, const BFDataGroupId& idDataGroup);

};


//*****************************************************************************
//              Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/UserDefMat.hpp-arc  $
//
//   Rev 1.6   Jun 18 2012 17:34:58   if991250
//IN2937065: new CMD Based on: User Defined Mat - Transfer
//
//   Rev 1.5   May 25 2012 19:12:42   if991250
//IN#2938847 Contract Information - User defined Maturity Date validation
//
//   Rev 1.4   Feb 03 2012 18:58:22   dchatcha
//IN# 2799812 - Contract Screen Issues.
//
//   Rev 1.3   Jan 30 2012 11:19:50   dchatcha
//IN# 2799812 - Contract Screen Issues.
//
//   Rev 1.2   May 15 2005 16:42:44   hernando
//Inc 305633 - Added ContractType in init call.
//
//   Rev 1.1   Mar 20 2005 17:50:20   hernando
//PET1024 FN02 - Added doInitWithDefaultValues.
//
//   Rev 1.0   Mar 20 2005 17:12:32   hernando
//Initial revision.
