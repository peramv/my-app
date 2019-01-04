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
// ^FILE   : HistoricalInfoList.hpp
// ^AUTHOR : Serban Popescu
// ^DATE   : January 2003
//
// ^CLASS    : HistoricalInfoList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>
#include <ifastbp\ifasthistoricalparameters.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

struct HistoricalData {
public:
   BFData *pQueryData;
   bool bMoreAvailable;
};

typedef std::vector< HistoricalData > HISTORICAL_DATA_VECTOR;


class IFASTCBO_LINKAGE HistoricalInfoList : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   HistoricalInfoList( BFAbstractCBO &parent );
   virtual ~HistoricalInfoList();

   // Initialize function
   // init for single DB Audit call.
   SEVERITY init(const DString& recId, const DString& tableId, const DString& keys = NULL_STRING,
      const DString& dstrTrack = I_("N"), const DString& dstrPageName = NULL_STRING);
   // init for Multiple DB Audit (View 249) calls.
   SEVERITY init(HISTORICAL_VECTOR *,
      const DString& dstrTrack = I_("N"), const DString& dstrPageName = NULL_STRING);
   // init for View 288 call (Shareholder Information)
   SEVERITY initShareholderInfo(const DString& dstrShareholder, 
      const DString& dstrTrack = I_("N"), const DString& dstrPageName = NULL_STRING);
   // init for View 288, View 289, View 110 (Shareholder Information + Acct KYC)
   SEVERITY initKYC(const DString& 
      dstrHistoricalType, 
      const DString& dstrShareholder, 
      const DString& dstrAccountNum,
      const DString& dstrTrack = I_("N"), 
      const DString& dstrPageName = NULL_STRING);
   // init for View 249/View 110
   SEVERITY initMail(const DString& recId, const DString& tableId, const DString& keys, const DString& dstrAccountNum,
      const DString& dstrTrack = I_("N"), const DString& dstrPageName = NULL_STRING);
   SEVERITY initAcct(const DString& dstrAccountNum,
      const DString& dstrTrack = I_("N"), const DString& dstrPageName = NULL_STRING);

   SEVERITY initAcctControl(const DString& dstrAccountNum,
      const DString& dstrTrack = I_("N"), const DString& dstrPageName = NULL_STRING);

   SEVERITY initAcctRoundingRule(HISTORICAL_VECTOR *, const DString& dstrAccountNum,
      const DString& dstrTrack = I_("N"), const DString& dstrPageName = NULL_STRING);

   SEVERITY doCreateObject( const BFData& data, BFCBO *&pObjOut );
   SEVERITY getMore();

   bool doMoreHistoricalRecordsExist();

private:

	BFData* _pQueryData, *_pQueryDataShr, *_pQueryDataAcctKYC, *_pQueryDataAcctHistInq;
	BFData* _pQueryDataAcctControlHistInq, *_pQueryDataAcctRoundingRuleHistInq;

	HISTORICAL_DATA_VECTOR m_vectorHistoricalData;

	bool m_bMoreRecordsFromViewsExist;
	bool m_bMoreRecordsForAccountKYC;
	bool m_bMoreRecordsForAccountHistInq;
	bool m_bMoreRecordsForShareholderKYC;
	bool m_bMoreRecordsForMail;
	bool m_bMoreRecordsForAccountControl;	
	bool m_bMoreRecordsForAcctRoundingRule;
	bool m_bMoreRecordsForAcctRoundingRuleHistInq;

	DString m_dstrHistoricalType;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/HistoricalInfoList.hpp-arc  $
//
//   Rev 1.12   Apr 16 2008 18:53:42   daechach
//PET2385 FN02&07 - Modified code regarding code review.
//
//   Rev 1.11   Mar 11 2008 20:11:14   daechach
//PET2385FN02&07 - Account Level Settlement Periods and Currency Holiday - Check in for Build.
//
//   Rev 1.10   Nov 14 2004 14:44:02   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.9   Mar 15 2004 17:53:24   HERNANDO
//PET965 FN11 - Change initKYC; added Historical Type.
//
//   Rev 1.8   Mar 03 2004 17:29:12   HERNANDO
//PET965 FN11 - Added initAcct.
//
//   Rev 1.7   Feb 28 2004 15:58:42   HERNANDO
//PET965 FN11 - Additional historical enhancement.
//
//   Rev 1.6   Mar 21 2003 18:13:24   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.5   Feb 03 2003 11:54:10   popescu
//Changes to support the KeyString field of view 249
//
//   Rev 1.4   Jan 29 2003 14:58:16   popescu
//FIxes related to view layout change and error reporting
//
//   Rev 1.3   Jan 28 2003 16:56:38   popescu
//Fixes for the More button in the Historical Info dialog
//
//   Rev 1.2   Jan 28 2003 13:16:24   popescu
//Historical Info feature implementation
//
//   Rev 1.1   Jan 26 2003 16:10:48   popescu
//List and CBO object for the Historical Info feature
//
//   Rev 1.0   Jan 26 2003 15:53:04   popescu
//Initial Revision
 *
 */