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
//    Copyright 2002, By International Financial Data Service
//
//
//******************************************************************************
//
// ^FILE   : AmsMstrList.hpp
// ^AUTHOR : Yingbao Li
// ^DATE   : Nov. 6,2002
//
// ^CLASS    : AmsMstrList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class AmsMstrInfo;
class IFASTCBO_LINKAGE AMSMstrList : public MFCanBFCbo
{
public:
   AMSMstrList( BFAbstractCBO &parent );
   virtual ~AMSMstrList();

   SEVERITY init(	const DString& dstrAmsType,
					const DString& dstrAmsCode,
					const DString& dstrEffectiveDate,
					const BFDataGroupId& idDataGroup,
					bool bDupCheck = false,
					bool ignoreDataNotFound = false,
					const DString& dstrTrack = I_("N"),
					const DString& dstrPageName = NULL_STRING 
				);
   SEVERITY init2(	const DString& dstrAmsType,
					const DString& dstrAmsCode,
					bool  bExactMatch,
					const DString& dstrEffectiveDate = NULL_STRING,
					const DString& dstrTrack = I_("N"),
					const DString& dstrPageName = NULL_STRING );
   SEVERITY reInit();
   SEVERITY getMore();
	const DString getCurrentAMSType()
	{
		return _dstrAmsType;
	}
	void setCurrentAMSType(const DString& dstrAMSType)
	{
		_dstrAmsType = dstrAMSType;
	
	}
   bool isAMSCodeValid( DString& dstrAMSType, DString& dstrAMSCode, const DString& dstrEffectiveDate,  const BFDataGroupId& idDataGroup, bool bValid0001); //public method, will be used by other objects

   void getFieldByAMSCode(const DString& dstrAMSType,const DString& dstrAMSCode, const DString& dstrEffectiveDate, const BFFieldId& idField,DString& strValue,const BFDataGroupId& idDataGroup,bool bFormat);
   void AddCopy(
					 DString &orgKey
					,DString &destKey
					,const BFDataGroupId& idDataGroup
				);
   bool isAMSCodeEnd(DString& dstrAMSType, DString& dstrAMSCode, const DString& dstrEffectiveDate, const BFDataGroupId& idDataGroup);

	void getAMSMstrInfo ( const DString& dstrAMSType,const DString& dstrAMSCode, const DString& dstrInquiryDate,
      AmsMstrInfo*& pAMSMstrInfo, const BFDataGroupId& idDataGroup );

protected:

   virtual SEVERITY doCreateObject( const BFData& data, BFCBO*& pObjOut );
   virtual SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup );
	virtual SEVERITY doCreateNewObject(BFCBO *&pObjOut, DString &strKey, const BFDataGroupId& idDataGroup );
   virtual bool canDeleteObject( const DString& strKey, const BFDataGroupId& idDataGroup );
	virtual void  getStrKey( DString &strKey, const BFData *data  );
private:
	bool isAmsCodeExistAtbackEnd(const DString& dstrAMSType, const DString& dstrAmsCode, const DString& dstrEffectiveDate, const BFDataGroupId& idDataGroup );

   BFData _requestData;

   DString _dstrAmsCode;
   DString _dstrAmsType;
   DString _dstrEffectiveDate;
   std::set<DString> setDate;



};


//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/AmsmstrList.hpp-arc  $
//
//   Rev 1.13   Aug 09 2003 12:28:56   YINGBAOL
//change getAMSMstrInfo
//
//   Rev 1.12   Jul 25 2003 17:05:52   HSUCHIN
//added support for limit override checks such as stop purchase, stop PAC etc. etc.
//
//   Rev 1.11   Jul 23 2003 11:00:06   linmay
//modified for cibc
//
//   Rev 1.10   Jul 18 2003 11:29:30   linmay
//modified for CIBC AMS
//
//   Rev 1.9   Jun 06 2003 11:23:34   YINGBAOL
//add set and get currenct AMSType
//
//   Rev 1.8   May 27 2003 16:37:52   popescu
//NASU flow AMS :data not found issue fix and removed some memory leaks 
//
//   Rev 1.7   Apr 21 2003 09:45:10   YINGBAOL
//view side return us record even if AMSType does not match, the change will fix the issue.
//
//   Rev 1.6   Apr 15 2003 10:44:28   linmay
//Sync up with 1.4.1.0
//
//   Rev 1.5   Mar 21 2003 17:59:20   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.4   Jan 15 2003 17:34:34   KOVACSRO
//Added init2
//
//   Rev 1.3   Jan 08 2003 16:28:22   sanchez
//Rebalancing Target Mix :function prototype for function getFieldByAMSCode()
//
//   Rev 1.2   Dec 27 2002 11:32:58   linmay
//added AMSType
//
//   Rev 1.1   Nov 27 2002 11:51:14   YINGBAOL
//add isAMSCodeExitAtBackEnd
//
//   Rev 1.0   Nov 13 2002 10:01:54   YINGBAOL
//Initial Revision
//




//