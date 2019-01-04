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
//    Copyright 1997 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : AutoAcctTransAllocationList.hpp
// ^AUTHOR : Yingbao Li	
// ^DATE   : March 27, 2000
//
// ^CLASS  : AutoAcctTransAllocationList
// ^PARENT : BFBase
//
// ^CLASS DESCRIPTION :
//
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>

class Systematic;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE AutoAcctTransAllocationList : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   AutoAcctTransAllocationList( BFAbstractCBO &parent );
   virtual ~AutoAcctTransAllocationList();

   // Initialization method
   SEVERITY init();
   SEVERITY init(const BFDataGroupId& idDataGroup, const DString& strPacSwpId, const BFData &data, bool bAcctFlag);
   SEVERITY initNew(const BFDataGroupId& idDataGroup);
   virtual SEVERITY doValidateAll(const BFDataGroupId& idDataGroup, long lValidateGroup);
   Systematic* getSystematicPtr(){ return(_pSystematic);};
   void setSystematicPtr(Systematic* pSystematic){ _pSystematic = pSystematic;};
   void ModelOffer( AutoAcctTransAllocationList * Model, const BFDataGroupId& idDataGroup );
   void GetSplitCommFlag ( const BFDataGroupId& idDataGroup, DString &dstrSplitComm );
   void GetDefaultSplitComm ( const BFDataGroupId& idDataGroup );
   SEVERITY initWithDefaultAllocations(const BFDataGroupId& idDataGroup, 
                       const DString& dstrTransTypeIn, const DString& dstrAcctNumIn, 
                       const DString& dstrCurrency, const DString& dstrAmount, const DString& dstrEffectiveDate);
protected:
   SEVERITY doCreateNewObject(BFCBO *&pBase, DString &strKey,const BFDataGroupId& idDataGroup);
   SEVERITY doCreateObject(const BFData& data, BFCBO *&pObjOut);
private:
   SEVERITY getAMSDefAllocList(MFCanBFCbo* &pDefaultAllocationList, const BFDataGroupId& idDataGroup, 
                                 const DString& strAccountNum, const DString& dstrEffectiveDate);
   // keep systematic pointer inside
   Systematic* _pSystematic;
   DString _dstrAddCopyKey;
   DString _strPacSwpId;
   bool _bAddCopy;
   bool _bHasAcct;
   const BFData* _allocationData;
};

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/AutoAcctTransAllocationList.hpp-arc  $
//
//   Rev 1.14   Aug 15 2003 15:22:46   HSUCHIN
//added method to init with default ams allocation.  Currently not used.
//
//   Rev 1.13   Jun 11 2003 13:18:14   popescu
//Removed unecessary GEtSplitCommissionList from the AutAccTransAllocationList level
//
//   Rev 1.12   May 13 2003 17:06:58   popescu
//Split commission re-work, part II
//
//   Rev 1.11   Mar 21 2003 17:59:36   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.10   Oct 09 2002 23:54:02   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.9   Aug 29 2002 12:51:48   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.8   22 May 2002 18:21:46   PURDYECH
//BFData Implementation
//
