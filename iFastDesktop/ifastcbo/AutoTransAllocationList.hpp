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
//    Copyright 1997 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : AutoTransAllocationList.hpp
// ^AUTHOR : Yingbao Li	
// ^DATE   : March 27, 2000
//
// ^CLASS  : AutoTransAllocationList
// ^PARENT : BFBase
//
// ^CLASS DESCRIPTION :
//
//
//******************************************************************************


#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>

class Systematic;
class AutoAcctTransAllocation;


#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif


class IFASTCBO_LINKAGE AutoTransAllocationList : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   AutoTransAllocationList( BFAbstractCBO &parent );
   virtual ~AutoTransAllocationList();
   // Initialization method
   SEVERITY init();
   SEVERITY init(AutoAcctTransAllocation*,
      const BFDataGroupId& idDataGroup, const DString& strPacSwpId,
      const DString&, const BFData &data, bool bHasAcct = true);
   SEVERITY initNew(AutoAcctTransAllocation*, const BFDataGroupId& idDataGroup);
   virtual SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup );
   Systematic* getSystematicPtr()
   {
      return(_pSystematic);
   };
   void setSystematicPtr(Systematic* pSystematic)
   {
      _pSystematic = pSystematic;
   };
   void ModelOffer( AutoTransAllocationList * Model, const BFDataGroupId& idDataGroup );
   void getTotal ( const BFFieldId& idField, DString& dstrTotal, const BFDataGroupId& idDataGroup);
   void GetSplitCommFlag ( const BFDataGroupId& idDataGroup, DString& dstrSplitComm );
   void GetDefaultSplitComm ( const BFDataGroupId& idDataGroup );
   int getNbrOfAllocInList( const BFDataGroupId& idDataGroup );
   SEVERITY setCurrency( const DString& dstrFundCode, 
                         const DString& dstrClassCode, 
                         const BFDataGroupId& idDataGroup ); 
   bool hasCappedFund ( const BFDataGroupId& idDataGroup );
   void setAllAllocsFndClsValidFlag(bool isValid, const BFDataGroupId& idDataGroup);

protected:
   SEVERITY doCreateObject(const BFData& data, BFCBO *&pObjOut);
   SEVERITY doCreateNewObject(BFCBO *&pBase, DString &strKey,const BFDataGroupId& idDataGroup);
private:
   Systematic* _pSystematic;
   AutoAcctTransAllocation* _pAtAcctTransAllocation;

   void setAtAcctTransAlloc(AutoAcctTransAllocation* pAtTrans) 
   {
      _pAtAcctTransAllocation = pAtTrans; 
   }
   AutoAcctTransAllocation* getAtAcctTransAlloc()
   {
      return(_pAtAcctTransAllocation);
   }
   DString _dstrMultiCurrency;
   bool _bAddCopy;
   DString _dstrAddCopyKey;
   DString _strPacSwpId;
   DString _strAccount;
   bool _bHasAcct;
};

