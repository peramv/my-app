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
// ^FILE   : FeeModelList.hpp
// ^AUTHOR :  
// ^DATE   : July 21, 2004
//
// ^CLASS    : FeeModelList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************


#include <boost\utility.hpp>
#include <ifastcbo\MFCanCbo.hpp>

// Forward references

class FeeModel;
class FeeModelCopyToGroupList;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE FeeModelList : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   FeeModelList( BFAbstractCBO &parent );
   virtual ~FeeModelList();
   // Initialize function
   SEVERITY init (const BFDataGroupId& idDataGroup,
                  const DString& dstrTrack = I_("N"),
                  const DString& dstrPageName = NULL_STRING, 
                  const DString& dstrHoldingCompCode = I_(""),
                  const DString& dstrHoldingCompName = I_(""),
                  const DString& dstrFeeModelCode = I_(""),
                  const DString& dstrFeeModelDesc = I_(""),
                  const DString& dstrSearchAll = I_("Y"),
                  const DString& dstrAsofDate = I_("12319999"),
                  bool bRetrieveAll = true);

   SEVERITY init (const DString &dstrFeeModelCode,
                  const BFDataGroupId& idDataGroup, 
                  const DString& dstrTrack = I_("N"),
                  const DString& dstrPageName = NULL_STRING  );

   SEVERITY initForCloneToGroupModel();

   SEVERITY getMore();
   void InitNew(const BFDataGroupId& idDataGroup){ }
   SEVERITY validateOverlapping( BFCBO *pCBO, const BFDataGroupId& idDataGroup );
   int isValidFeeModelCode( const BFDataGroupId& idDataGroup, const DString& dstrFeeModelCode, const DString& dstrDate);
   void getDescByFeeModelCode (const BFDataGroupId &idDataGroup, const DString &dstrFeeModelCode, DString &dstrDesc);
   SEVERITY getFeeModel (const DString &dstrFeeModelCode, FeeModel *&pFeeModel, const BFDataGroupId &idDataGroup);
   DString& getFromHoldingCompanyCode(){return m_dstrFromHoldingComp;};
   void setFromHoldingCompany(const DString& dstrHoldingCompCode, const BFDataGroupId& idDataGroup);
   bool isAllFeeModels() {return m_bAllFeeModels;};
   void setAllFeeModels(bool isAllFeeModels) {m_bAllFeeModels = isAllFeeModels;};
   SEVERITY copyFeeModelToNewGroup(FeeModelCopyToGroupList* pCopyable,
                                   FeeModelList* pSrcModelList,
                                   const BFDataGroupId& idDataGroup);

protected:
   virtual SEVERITY doCreateObject( const BFData& data, BFCBO *&pObjOut );
   virtual SEVERITY doCreateNewObject( BFCBO *&pBase, DString &strKey, const BFDataGroupId& idDataGroup );
   virtual SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup );   
   void getStrKey ( DString& strKey, const BFData* data );
   void getStrKeyForNewItem(DString & strKey);
   bool canDeleteObject( const DString& strKey, const BFDataGroupId& idDataGroup );

private:
   int m_intKey;
   int m_intNewKey;
   bool m_bRetrieveAll;
   BFData * requestData305;
   DString m_dstrFromHoldingComp;
   bool m_bAllFeeModels;

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/FeeModelList.hpp-arc  $
// 
