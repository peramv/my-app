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
// ^FILE   : FeeParamSysList.hpp
// ^AUTHOR :  Yingbao Li, May Lin
// ^DATE   : January 11, 2003
//
// ^CLASS    : FeeParamSysList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************


#include <boost\utility.hpp>

// Forward references

#include "FeeParamBaseList.hpp"
class FeeParamSys;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif



class IFASTCBO_LINKAGE FeeParamSysList : public FeeParamBaseList
{
public:

   // X-structors
   FeeParamSysList( BFAbstractCBO &parent );
   virtual ~FeeParamSysList();
   // Initialize function
   SEVERITY init(	const BFDataGroupId& idDataGroup, bool bDefault = false, 
                  const DString& dstrFeeCode = NULL_STRING,
                  const DString& dstrTrack = I_("N"),
                  const DString& dstrPageName = NULL_STRING  );
	SEVERITY getMore();
	void InitNew(const BFDataGroupId& idDataGroup){ }
	SEVERITY getDefaultFeeParamRecord(
										 FeeParamSys *&pFeeParamSys, 
										 const DString strFeeCode, 
										 const DString strFundCode, 
										 const DString strClassCode, 
										 const DString strFundGroup, 
										 const BFDataGroupId& idDataGroup,
                               const bool bCompFundGroup,
                               const bool bCompFundClass = true
                                
									);
   SEVERITY copyItem(const DString &strKey, const BFDataGroupId& idDataGroup, DString &newKey);

   SEVERITY initForDefault( const BFDataGroupId& idDataGroup );
   DString& getFromFeeModelCode(){return m_dstrFromFeeModelCode;};
   void setFromFeeModelCode(const DString& dstrFromFeeModelCode){m_dstrFromFeeModelCode = dstrFromFeeModelCode;};
protected:
	virtual SEVERITY doCreateObject( const BFData& data, BFCBO *&pObjOut );
	virtual SEVERITY doCreateNewObject( BFCBO *&pBase, DString &strKey, const BFDataGroupId& idDataGroup );
    virtual SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup );
	


private:
   BFData *requestData230;
   bool bDefault_;
   DString m_dstrFromFeeModelCode;
};

