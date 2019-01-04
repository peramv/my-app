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
// ^FILE   : FeeParamList.hpp
// ^AUTHOR :  Yingbao Li
// ^DATE   : January 24, 2002
//
// ^CLASS    : FeeParamList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>

// Forward references
class AccountFee;
class FeeParamConfig;
class ErrMsgRulesList;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif
class FeeParam;
class IFASTCBO_LINKAGE FeeParamList : public MFCanBFCbo, private boost::noncopyable
{
public:

   // X-structors
   FeeParamList( BFAbstractCBO &parent );
   virtual ~FeeParamList();
   // Initialize function
   SEVERITY init( const DString& accountNum, 
                  const BFDataGroupId& idDataGroup,
                  bool bMore = false,
                  const DString& dstrTrack = I_("N"),
                  const DString& dstrPageName = NULL_STRING );

   SEVERITY initNew( const DString& shareholderNum, const BFDataGroupId& idDataGroup );
	bool FindDeletedOverlapRecord(const FeeParam* pFeeParam,const BFDataGroupId& idDataGroup,
		const DString& dstrExClFeeCode,BFObjIter::ITERTYPE itertype );

protected:

   virtual void getStrKey( DString &strKey, const BFData *data = NULL );
   virtual SEVERITY doCreateObject( const BFData& data, BFCBO *&pObjOut );
   virtual SEVERITY doCreateNewObject( BFCBO *&pBase, DString &strKey, const BFDataGroupId& idDataGroup );
   virtual SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup );
   virtual bool canDeleteObject    ( const DString&  strKey,   const BFDataGroupId& idDataGroup );

private:
   SEVERITY validateManagementFee( const BFDataGroupId& idDataGroup );
   SEVERITY getFeeParamConfigByFeeCode(const DString dstrFeeCode, FeeParamConfig *&pFeeParamConfig, const BFDataGroupId& idDataGroup);
   SEVERITY getFundGroupListByFeeCode(const DString dstrFeeCode, DString &dstrList, const BFDataGroupId& idDataGroup);
   void getErrMsgValue( DString dstrErrNum,       
                         const BFDataGroupId& idDataGroup, 
                         DString& dstrErrValue );

   ErrMsgRulesList* _pErrMsgRulesList;

   DString _strAccountNum;
   BFData *_pAcctFeeScaleData;
   BFData *requestData194;
   BFData *requestData195;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//