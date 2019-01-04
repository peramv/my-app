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
// ^FILE   : AccountDistributionList.hpp
// ^AUTHOR : Zijian Ying+ yingbao for M2
// ^DATE   : 04/22/99
//
// ^CLASS    : AccountDistributionList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>

class AccountDistribution;

enum DISTRIBUTION_LEVEL
{
   UNDEFINED_LEVEL, ACCOUNT_LEVEL, FUND_CLASS_LEVEL
};

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE AccountDistributionList : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   AccountDistributionList( BFAbstractCBO &parent );
   virtual ~AccountDistributionList( void );

   // Initialization functions
   SEVERITY init( bool bRetrieveFromHost, 
                  const BFDataGroupId& idDataGroup,
                  const DString& dstrAccountNum,
                  const DString& dstrShareholderNum,
                  DISTRIBUTION_LEVEL level,
                  BFData *distributionData = NULL,
                  const DString& dstrFundCode = NULL_STRING, 
                  const DString& dstrClassCode = NULL_STRING,
                  const DString& dstrEffectiveDate = NULL_STRING,
                  const DString& dstrTransType = NULL_STRING,
                  const DString& dstrTrack = I_("N"),
                  const DString& dstrPageName = NULL_STRING );

   void getStrKey( DString &strKey, const BFData *data = NULL );
   void getTotalDistribRate( const BFDataGroupId& idDataGroup, 
							 double& dTotalDistribRate, 
							 const DString& strKey = NULL_STRING );
   void setTotalDistribRate( const BFDataGroupId& idDataGroup, double& dTotalDistribRate );
   void recalculatePercentages( const BFDataGroupId& idDataGroup, 
								bool bVerificationEnabled,
								const DString& strKey = NULL_STRING );
   void roundOffLastPercent( const BFDataGroupId& idDataGroup, double& dTotalPercent);
   void setAllAllocsFndClsValidFlag(bool isValid, const BFDataGroupId& idDataGroup);

   SEVERITY getMore();

protected:
   SEVERITY doCreateObject( const BFData& data, BFCBO *&pObjOut );
   SEVERITY doCreateNewObject( BFCBO *&pBase, DString &dstrKey, 
                               const BFDataGroupId& idDataGroup );
   virtual SEVERITY  doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup );
   void setObjectFlags( const BFObjectKey & objKey, long& lStateFlags , long& lGroupFlags );

   SEVERITY initDistributionData(const BFData*  distributionData,
                                 const BFDataGroupId& idDataGroup,
                                 const DString& dstrAccountNum,
                                 const DString& dstrShareholderNum,
                                 const DString& dstrFundCode = NULL_STRING, 
                                 const DString& dstrClassCode = NULL_STRING,
                                 const DString& dstrEffectiveDate = NULL_STRING,
                                 const DString& dstrTransType = NULL_STRING,
                                 const DString& dstrTrack = I_("N"),
                                 const DString& dstrPageName = NULL_STRING );

   virtual SEVERITY doDeleteObject ( const DString & strKey, 
                                     const BFDataGroupId& idDataGroup, 
                                     bool bIsObjectDestroyed );
   SEVERITY validateDeletedRecord( const BFDataGroupId& idDataGroup );

   bool isDistributionBankList;

private:  
   AccountDistributionList( const AccountDistributionList& copy );
   // = Operator
   AccountDistributionList& operator= ( const AccountDistributionList& copy );
   SEVERITY setFundMastDetailList(AccountDistribution* pAcct);

   DISTRIBUTION_LEVEL _level;
   DString _dstrAccountNum;
   DString _dstrShareholderNum;

   BFData _requestData0016;
   BFData *_pResponseData0016;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AccountDistributionList.hpp-arc  $
 * 
 *    Rev 1.19   Feb 08 2010 22:11:18   dchatcha
 * IN# 1988872 - R97_Static Data_Cannot add Distrib Option identical to unverified deleted one.
 * 
 *    Rev 1.18   Feb 06 2010 17:19:22   dchatcha
 * Restored 1.16
 * 
 *    Rev 1.17   Feb 03 2010 19:00:22   dchatcha
 * IN# 1988872 - R97_Static Data_Cannot add Distrib Option identical to unverified deleted one.
 * 
 *    Rev 1.16   Dec 03 2009 03:14:44   dchatcha
 * PET0166583 FN02 FN03 - Static Verification Phase 2.
 * 
 *    Rev 1.15   Jan 30 2009 09:31:34   daechach
 * Revision Control Entries
 * 
 */

