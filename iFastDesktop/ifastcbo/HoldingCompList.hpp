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
// ^FILE   : HoldingCompList.hpp
// ^AUTHOR :  
// ^DATE   : Jan 28 , 2013
//
// ^CLASS    : HoldingCompList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************


#include <boost\utility.hpp>

// Forward references

class HoldingComp;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE HoldingCompList : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   HoldingCompList( BFAbstractCBO &parent, const DString& dstrHoldingCompCode, const DString& dstrHoldingCompName, 
   const DString& dstrAll, const DString& dstrEffDate);
   virtual ~HoldingCompList();
   // Initialize function
   SEVERITY init (const BFDataGroupId& idDataGroup, 
	               const DString& dstrTrack = I_("N"),
                  const DString& dstrPageName = NULL_STRING,
                  bool ignoreFoundDeletedError = true);


	SEVERITY getMore();
	void InitNew(const BFDataGroupId& idDataGroup){ }
   SEVERITY validateOverlapping( BFCBO *pCBO, const BFDataGroupId& idDataGroup );
   int isValidHoldingCompCode( const BFDataGroupId& idDataGroup, const DString& dstrHoldingCompCode, const DString& dstrDate);
   void getDescByHoldingCompCode (const BFDataGroupId &idDataGroup, const DString &dstrHoldingCompCode, DString &dstrDesc);
   SEVERITY getHoldingComp (const DString &dstrHoldingCompCode, HoldingComp *&pHoldingComp, const BFDataGroupId &idDataGroup);
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

   const DString m_HoldingCompCode;
   const DString m_HoldingCompName;
   const DString m_SearchAll;
   const DString m_AsofDate;

   BFData * m_RequestData448;

};

