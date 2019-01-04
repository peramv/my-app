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
//
//******************************************************************************
//
// ^FILE   : AutoTransAllocation.hpp
// ^AUTHOR : Yingbao Li
// ^DATE   : March 27, 2000
//
// ^CLASS    : AutoTransAllocation
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************


#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>
///#endif

class Systematic;
class SplitCommissionList;
class AutoAcctTransAllocation;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif


class IFASTCBO_LINKAGE AutoTransAllocation : public MFCanBFCbo, private boost::noncopyable
{
public:
   AutoTransAllocation(BFAbstractCBO &parent);
   virtual ~AutoTransAllocation();
   SEVERITY init();
   SEVERITY init(const BFData &viewData);
   void getField( const BFFieldId& idField, DString& strFieldValue, 
      const BFDataGroupId& idDataGroup, bool formattedReturn = false ) const;
   SEVERITY doValidateField(const BFFieldId& idField, const DString& strValue, 
      const BFDataGroupId& idDataGroup) ;
   virtual SEVERITY doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup );
   //eventually the below two methods should be removed
   Systematic* getSystematicPtr() const 
   {
      return(_pSystematic);
   };
   void setSystematicPtr(Systematic* pSystematic)
   {
      _pSystematic = pSystematic;
   };
   void ModelOffer(AutoTransAllocation * Model, const BFDataGroupId& idDataGroup);
   void setAutoAcctTransAllocation(AutoAcctTransAllocation* pAlloc)
   {
      _pAutoAcctTransAllocation = pAlloc;
   }
   AutoAcctTransAllocation* getAutoAcctTransAllocation()
   {
      return(_pAutoAcctTransAllocation);
   }
   void setParameter(DString&, DString&, DString&, DString&);

	void parentFieldChangeNotify(const BFFieldId& fieldId,
				const BFDataGroupId& idDataGroup, 
				DString& dstrValue,
				bool bFormat);
   SEVERITY getSplitCommissionList(SplitCommissionList *&rpSplitCommissionList, const BFDataGroupId& idDataGroup);
   void GetDefaultSplitComm (const BFDataGroupId& idDataGroup);
   void GetSplitCommFlag (const BFDataGroupId& idDataGroup, DString &dstrSplitComm);
   bool splitCommActive (const BFDataGroupId& idDataGroup);
   SEVERITY validateToFundClassSoftCapped(const BFDataGroupId& idDataGroup);
   SEVERITY doValidateAll(const BFDataGroupId& idDataGroup, long lValidateGroup);

private:
   bool _bInitialSplitComm;
   //should be removed
   Systematic *_pSystematic;
   AutoAcctTransAllocation *_pAutoAcctTransAllocation;

   SEVERITY validateAllocCurrency( DString dstrFundCode, DString dstrClassCode, const BFDataGroupId& idDataGroup );
   void validateFundClass(const BFDataGroupId& idDataGroup);
   void validateFundCode (const DString& strValue, const BFDataGroupId& idDataGroup) ;
   void validateClassCode (const DString& strValue, const BFDataGroupId& idDataGroup) ;
   void validatePercentage (const DString& strValue, const BFDataGroupId& idDataGroup) const;
   void setFundClassCode (const BFFieldId& idField, const BFDataGroupId& idDataGroup);
   void setFundNumber (const BFFieldId& idField, const BFDataGroupId& idDataGroup);
   SEVERITY fetchSplitCommisionListUsingSystematicParent(SplitCommissionList *&rpSplitCommissionList, 
      const BFDataGroupId& idDataGroup);
	SEVERITY validateFundClassAccNumDate ( const BFDataGroupId& idDataGroup );
};

///#endif
