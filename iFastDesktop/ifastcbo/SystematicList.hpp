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
//******************************************************************************
//
// ^FILE   : SystematicList.hpp
// ^AUTHOR : David Smith
// ^DATE   : Feburary 25, 1999
//
// ^CLASS  : SystematicList
// ^PARENT : ListBase
//
// ^CLASS DESCRIPTION :
//  ements a map from the STL to hold fully instantiated BFBase objects
//  that are created from Data objects stored in the inherited ListBase class
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>

//Forward Declarations
class MgmtCoOptions;
class MFAccount;
class FundMasterList;
class FundDetailList;
class GroupList;
class GroupFundList;
class CurrencyList;
class Shareholder;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE SystematicList : public MFCanBFCbo, private boost::noncopyable
{
public:
	void getEntityName( DString& EntityName );

	DString& getTransType() 
	{
		return(_dstrTransTypeParam);
	}

	void setTransType(const DString& dstrTransType) 
	{ 
		_dstrTransTypeParam = dstrTransType;
	}

	SystematicList( BFAbstractCBO &parent );
	virtual ~SystematicList();

	// Initialization method
	SEVERITY init( const DString& strAccountNumber,
					const DString &strPayType = NULL_STRING,
					const DString &strAmount = NULL_STRING ,
					const DString &strAmountType = NULL_STRING,
					const DString& dstrTrack= I_("N"),
					const DString& dstrPageName = NULL_STRING );

	MFAccount*        getMFAccount()      { return(_pMFAccount);}
	FundMasterList*   getFundMasterList() { return(_pFundMasterList);}
	FundDetailList*   getFundDetailList() { return(_pFundDetailList);}
	GroupList*        getGroupList()      { return(_pGroupList);}
	MgmtCoOptions*    getMgmtCoOptions()  { return(_pMgmtCoOption);}
	GroupFundList*    getGroupFundList()  { return(_pGroupFundList);}
	CurrencyList*     getCurrencyList()   { return(_pCurrencyList);}
	Shareholder*      getShareholder()    { return(_pShareholder);}

	SEVERITY initNew( const DString& strAccountNumber,
						const DString &strTransType,
						const DString &strAmount,
						const DString &strAmountType);
	virtual SEVERITY  doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup );
	void AddCopy( DString& orgKey, DString& destKey, const BFDataGroupId& idDataGroup );

	void setValidateAllFlag(bool bValidate) {_bValidateAll = bValidate;}
	SEVERITY doDeleteObject ( const DString&  strKey, const BFDataGroupId& idDataGroup, bool bIsObjectDestroyed );
	void checkBankCurrency( const BFDataGroupId& idDataGroup, BFAbstractCBO *pSystematic );
	bool hasGoodSWPAtDate(const BFDataGroupId& idDataGroup,const DString& dstrDate );
	bool hasNonAMSFunds(const BFDataGroupId& idDataGroup);
	bool areAllSytematicRecordsInactive (const BFDataGroupId& idDataGroup);

protected:
   void getStrKey (DString &strKey, const BFData *data);
   SEVERITY doCreateObject( const BFData& data, BFCBO *&pObjOut );
   SEVERITY doCreateNewObject(BFCBO *& pBase, DString & strKey, const BFDataGroupId& idDataGroup);
   SEVERITY getDataObjectKey( BFData &data, DString &strKey );

private:
   bool _bValidateAll;

   SEVERITY enquiryATAllocation( const DString& strAccountNumber,
                                 const DString& dstrTrack= I_("N"),
                                 const DString& dstrPageName = NULL_STRING );
   void checkSavingPlanDuplication( const BFDataGroupId& idDataGroup );

   void getInfoForValidation( const BFDataGroupId& idDataGroup );
   DString _EntityName;
   BFData  *_pSysAllocRecvData,*_pAtAllocRecvData;  

   MgmtCoOptions * _pMgmtCoOption;

   MFAccount*                 _pMFAccount;
   FundMasterList*            _pFundMasterList;
   FundDetailList*            _pFundDetailList;
   GroupList*                 _pGroupList;
   GroupFundList *_pGroupFundList;
   CurrencyList *_pCurrencyList;
   Shareholder*             _pShareholder;
   DString _dstrAccountNum;
   DString _dstrTransTypeParam;

   DString _dstrPayType;
   DString _dstrAmount;
   DString _dstrAmountType;
};

///#endif

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/SystematicList.hpp-arc  $
 * 
 *    Rev 1.20   Nov 24 2010 18:54:32   jankovii
 * PET175778FN01 - Upstreaming Phase 2
 * 
 *    Rev 1.19   Nov 14 2004 14:56:50   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.18   Aug 11 2003 11:57:16   YINGBAOL
 * add method hasGoodSWPAtDate;
 * 
 *    Rev 1.17   Mar 21 2003 18:25:56   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.16   Oct 09 2002 23:55:06   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.15   Aug 29 2002 12:53:46   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.14   22 May 2002 18:19:52   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.13   19 Mar 2002 13:18:44   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.12   Feb 25 2002 18:54:00   PURDYECH
 * Phase 1 of BFData Rollout - Base Component Compatibility
 * 
 *    Rev 1.11   16 Jun 2001 14:30:58   YINGZ
 * check saving plan duplication
 * 
 *    Rev 1.10   11 May 2001 10:25:16   HSUCHIN
 * Sync up with SSB (1.8.1.1)
 * 
 *    Rev 1.9   03 May 2001 14:04:58   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.8   30 Mar 2001 17:09:22   BUZILAMI
 * Systematic bank changes
 * 
 *    Rev 1.7   Jan 18 2001 16:12:50   YINGBAOL
 * add etrack
 * 
 *    Rev 1.6   Nov 03 2000 11:34:02   YINGBAOL
 * use new databroker
 * 
 *    Rev 1.5   Sep 06 2000 14:50:10   YINGBAOL
 * change sync.
 * 
 *    Rev 1.4   Jun 06 2000 15:10:40   HUANGSHA
 * add setValidateFlag(bool)
 * 
 *    Rev 1.3   Apr 17 2000 17:15:32   YINGZ
 * add AddCopy function for systematic
 * 
 *    Rev 1.2   Apr 04 2000 10:46:02   YINGBAOL
 * M2 Sync.
 * 
 *    Rev 1.1   Mar 31 2000 16:21:02   YINGBAOL
 * check in for Chin to Sync.
 * 
 *    Rev 1.0   Feb 15 2000 10:59:24   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.26   Feb 09 2000 12:13:18   HUANGSHA
 * check in for release
 * 
 *    Rev 1.25   Feb 07 2000 12:30:56   BUZILA
 * fix
 * 
 *    Rev 1.24   Feb 01 2000 14:36:20   BUZILA
 * added lValidateGroup parameter to doValidateAll method
 * 
 *    Rev 1.23   Jan 25 2000 17:10:44   HUANGSHA
 * Fixed bugs
 * 
 *    Rev 1.22   Jan 18 2000 11:23:40   YINGZ
 * change getInfoForValidation
 * 
 *    Rev 1.21   Jan 14 2000 14:15:04   YINGZ
 * change init to initNew
 * 
 *    Rev 1.20   Dec 23 1999 14:29:20   YINGZ
 * release
 * 
 *    Rev 1.19   Dec 21 1999 17:24:52   YINGZ
 * add validation
 * 
 *    Rev 1.18   Dec 20 1999 16:39:02   YINGZ
 * change initNew
 * 
 *    Rev 1.17   Dec 17 1999 12:18:24   YINGZ
 * validation check in
 * 
 *    Rev 1.16   Dec 16 1999 15:10:06   YINGZ
 * check in validation
 * 
 *    Rev 1.15   Dec 14 1999 12:06:00   YINGZ
 * sync with cpp
 * 
 *    Rev 1.14   Dec 13 1999 10:02:18   YINGZ
 * for release 
 * 
 *    Rev 1.13   Dec 06 1999 14:13:38   YINGZ
 * support default entityname
 * 
 *    Rev 1.12   Dec 05 1999 18:58:26   VASILEAD
 * Friday night changes( don't be so hard on us )
 * 
 *    Rev 1.11   Dec 01 1999 12:57:14   HUANGSHA
 * check in for 2nd release
 * 
 *    Rev 1.10   Nov 25 1999 15:16:50   HUANGSHA
 * check in for the initial m2 release
 * 
 *    Rev 1.9   Nov 25 1999 10:27:06   HUANGSHA
 * check in for test
 * 
 *    Rev 1.8   Nov 24 1999 09:28:42   HUANGSHA
 * check in for test
 * 
 *    Rev 1.7   Nov 22 1999 14:07:28   YINGZ
 * add validation
 * 
 *    Rev 1.6   Nov 15 1999 14:45:42   HUANGSHA
 * temporary check in
 * 
 *    Rev 1.5   Nov 08 1999 15:25:56   YINGZ
 * check in in order to check out!
 * 
 *    Rev 1.4   Oct 22 1999 14:59:48   BUZILA
 * XchgData fix
 * 
 *    Rev 1.3   Oct 18 1999 11:38:18   BUZILA
 * Update transaction stuff
 * 
 *    Rev 1.2   Sep 14 1999 11:46:14   BUZILA
 * BFBase changes
 * 
 *    Rev 1.1   Jul 08 1999 10:02:28   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 * 
 *    Rev 1.0   Jul 07 1999 13:47:24   SMITHDAV
 * Original revision.
 *
 */