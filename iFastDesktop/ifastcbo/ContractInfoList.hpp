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
//    Copyright 2000 by DST Canada, Inc.
//
//
//******************************************************************************
//
// ^FILE   : ContractInfoList.hpp
// ^AUTHOR : Celia Zhang
// ^DATE   : 02/01/2000
//
// ^CLASS    : ContractInfoList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************


#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>
///#endif

class MasterContractList;
class MgmtCoOptions;
class TaxTypeRuleList;
class MFAccount;
class MFAccountHoldingList;
class ContractInfo;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE ContractInfoList : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   ContractInfoList( BFAbstractCBO &parent );
   virtual ~ContractInfoList( void );

   // Initialize function
   SEVERITY init( const BFDataGroupId& idDataGroup,
                  const DString& AccountNumber, 
                  bool bViewCall = true, 
                  const DString& dstrTrack = I_("N"),
                  const DString& dstrPageName = NULL_STRING );
   SEVERITY getMore();

   //DString &DofBirth );

   // Following functions will be used in ContractInfo.cpp
   MgmtCoOptions*        getMgmtCoOptions()      { return(pMgmtCoOptions);}
   TaxTypeRuleList*      getTaxTypeRuleList()    { return(pTaxTypeRuleList);}
   MasterContractList*   getMasterContractList() { return(pMasterContractList);}
   MFAccount*            getMFAccount()          { return(pMFAccount);}
   MFAccountHoldingList* getAccountHoldingList() { return(pAccountHoldingList);}
   SEVERITY getContractByType(ContractInfo*& _pContractInfo, const DString& dstrContractType, const BFDataGroupId& idDataGroup);

   DString              getAcctNum()             { return(dstrAcctNum);}
//   void                 SetIsAddCopy()           { bAddCopy = true ;   }
   // Below function is used by ContractInfoProcess
//   void PassDofBirthForCheck( DString &OrgKey, DString &DofBirth, const BFDataGroupId& idDataGroup );

   /* This function is used for the record copy
    * @param orgKey -- The Original record
    * @param destKey -- The destinaed record
    */
   void AddCopy(DString &orgKey, DString &destKey, const BFDataGroupId& idDataGroup);
   bool setMultiContrPerm( bool bPermMultiContract );
   //bool getDofBirth( const BFDataGroupId& idDataGroup, DString &dstrDofBirth );

protected:
   SEVERITY doCreateNewObject( BFCBO *& pBase, DString &strKey, const BFDataGroupId& idDataGroup );
   virtual SEVERITY doCreateObject( const BFData& data, BFCBO *&pObjOut );
   virtual SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup );

   SEVERITY getMasterContractList(MasterContractList*& _pMasterContractList, const BFDataGroupId& idDataGroup);
   SEVERITY ValidateTwinContracts(const BFDataGroupId& idDataGroup);

private:
   // Private function member
   void getInfoForVldandDft( const BFDataGroupId& idDataGroup );
   SEVERITY validateDateRanges( const BFDataGroupId& idDataGroup );
   //SEVERITY ValidateOldestLegalDate( DString &dsDofBirth, const BFDataGroupId& idDataGroup );

   // Private data members
   MgmtCoOptions        *pMgmtCoOptions;
   TaxTypeRuleList      *pTaxTypeRuleList;
   MasterContractList   *pMasterContractList;
   MFAccount            *pMFAccount;
   MFAccountHoldingList *pAccountHoldingList;

   DString             dstrAcctNum;
   
   BFData* pRequestData105;


};

///#endif

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/ContractInfoList.hpp-arc  $
 * 
 *    Rev 1.26   Apr 10 2012 16:21:06   if991250
 * IN 2900207 Contract Information
 * 
 *    Rev 1.25   Jan 27 2012 19:26:06   dchatcha
 * IN# 2799812 - Contract Screen issues.
 * 
 *    Rev 1.24   Dec 27 2011 00:45:54   dchatcha
 * P0186484 - FN 05 - work on Contract Information Screen
 * 
 *    Rev 1.23   May 25 2006 17:49:20   ZHANGCEL
 * PET 2102 FN01 -- Legal age related changes with new view367
 * 
 *    Rev 1.22   Nov 14 2004 14:30:00   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.21   Mar 21 2003 18:02:04   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.20   Oct 09 2002 23:54:08   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.19   Aug 29 2002 12:52:04   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.18   22 May 2002 18:21:26   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.17   19 Mar 2002 13:15:28   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.16   Nov 14 2001 11:45:48   ZHANGCEL
 * Many changes for Multiple Contracts
 * 
 *    Rev 1.15   Nov 07 2001 14:38:18   ZHANGCEL
 * Comment PassDofBirthForCheck()
 * 
 *    Rev 1.14   Jul 29 2001 12:34:58   OLTEANCR
 * unchanged
 * 
 *    Rev 1.13   Jul 16 2001 19:24:52   OLTEANCR
 * added setMultiContractPerm( )
 * 
 *    Rev 1.12   10 May 2001 11:45:40   HSUCHIN
 * Sync up with SSB
 * 
 *    Rev 1.11   May 10 2001 10:34:14   OLTEANCR
 * unchanged
 * 
 *    Rev 1.10   Jan 18 2001 16:11:48   YINGBAOL
 * add etrack
 * 
 *    Rev 1.9   Oct 19 2000 17:21:36   KOVACSRO
 * Modified PassDofBirthForCheck().
 * 
 *    Rev 1.8   Oct 13 2000 15:15:20   KOVACSRO
 * Added bViewCall parameter to init().
 * 
 *    Rev 1.7   Oct 02 2000 13:58:56   ZHANGCEL
 * Added a parameter in PassDofBirthForCheck()
 * 
 *    Rev 1.6   Jul 26 2000 11:48:16   ZHANGCEL
 * Added code for date overlap validation
 * 
 *    Rev 1.5   May 12 2000 17:51:10   ZHANGCEL
 * Deal with DofBirth checking problems
 * 
 *    Rev 1.4   Apr 20 2000 16:35:26   ZHANGCEL
 * Milestone check in
 * 
 *    Rev 1.3   Apr 14 2000 09:47:58   ZHANGCEL
 * Added functions for validation
 * 
 *    Rev 1.2   Apr 11 2000 11:49:54   ZHANGCEL
 * Set default value
 * 
 *    Rev 1.1   Mar 07 2000 10:25:06   HSUCHIN
 * changed to use new infra
// 
//    Rev 1.0   Feb 03 2000 13:29:48   ZHANGCEL
// Initial revision.
 * 
 *
 */