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
//******************************************************************************
//
// ^FILE   : SysAllocationList.hpp
// ^AUTHOR : Chin Hsu
// ^DATE   : Feburary 25, 1999
//
// ^CLASS  : SysAllocationList
// ^PARENT : ListBase
//
// ^CLASS DESCRIPTION :
//
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE SysAllocationList : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   SysAllocationList( BFAbstractCBO &parent );
   virtual ~SysAllocationList();
   // Initialization method
   SEVERITY init( const BFDataGroupId& idDataGroup, const DString& strPacSwpId, const BFData &data);
   SEVERITY initNew( const BFDataGroupId& idDataGroup );

   virtual SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup );
   void ModelOffer( SysAllocationList * Model, const BFDataGroupId& idDataGroup );

   SEVERITY initWithDefaultAllocations( const BFDataGroupId& idDataGroup, 
                                        const DString& dstrTransTypeIn, 
                                        const DString& dstrAcctNumIn, 
                                        const DString& dstrCurrency,
                                        const DString& dstrAmount,
                                        const DString& dstrEffectiveDate,
                                        bool bDummyAllocations = false );

   void getTotal ( const BFFieldId& idField, DString &dstrTotal, const BFDataGroupId& idDataGroup);
   void getTotalAllocAmountPercent(const BFDataGroupId& idDataGroup, double &dTotalAmount, double &dTotalPercentage);
   void GetDefaultSplitComm ( const BFDataGroupId& idDataGroup );
   void GetSplitCommFlag ( const BFDataGroupId& idDataGroup, DString &dstrSplitComm );
   void GetSplitCommList ( const BFDataGroupId& idDataGroup );
   int getNbrOfAllocInList(const BFDataGroupId& idDataGroup);
   SEVERITY setCurrency( const DString dstrFundCode, const DString dstrClassCode, 
                         const BFDataGroupId& idDataGroup );

   void GetAccountLevelInfo(DString& strVer,DString& strRid);
   bool hasCappedFund ( const BFDataGroupId& idDataGroup );
   void setAllAllocsFndClsValidFlag(bool isValid, const BFDataGroupId& idDataGroup);

protected:
   SEVERITY doCreateObject(const BFData& data, BFCBO *&pObjOut);
   SEVERITY doCreateNewObject (BFCBO *&pBase, DString &strKey, const BFDataGroupId& idDataGroup);
   SEVERITY doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup );

private:

   //gets the default allocation list using shareholder default allocations for the specified TransType
   SEVERITY getShrDefAllocList(MFCanBFCbo* &pDefaultAllocationList, const BFDataGroupId& idDataGroup,
      const DString& dstrTransTypeIn, const DString& dstrAcctNumIn);
   //gets the default allocation list using shareholder default allocations for AMS rebalancing TransType
   SEVERITY getRebalDefAllocList(MFCanBFCbo* &pDefaultAllocationList, const BFDataGroupId& idDataGroup, 
      const DString& strAccountNum);
   //gets the default allocation list using account AMS allocations
   SEVERITY getAMSDefAllocList(MFCanBFCbo* &pDefaultAllocationList, const BFDataGroupId& idDataGroup, 
      const DString& strAccountNum, const DString& dstrEffectiveDate);

   DString _dstrAddCopy;
   DString _dstrMultiCurrency;
   bool    _bAddCopy;
   DString _dstrAcctLvlVer;
   DString _dstrAcctLvlRid;
   DString _strPacSwpId;
};

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/SysAllocationList.hpp-arc  $
 * 
 *    Rev 1.23   Nov 14 2004 14:56:20   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.22   Sep 04 2003 17:26:26   HSUCHIN
 * PTS 10021181 - bug fix for capped fund rule for normal Allocations
 * Added method hasCappedFund to check allocations for capped fund.
 * 
 *    Rev 1.21   Aug 25 2003 15:42:42   HSUCHIN
 * fixed bug with systematic updating for AMS accounts when nothing has changed.
 * 
 *    Rev 1.20   Aug 15 2003 15:29:50   HSUCHIN
 * AMS Restriction enhancement to default allocation.  Change the way the AMS Fund list is retrieved.
 * 
 *    Rev 1.19   May 06 2003 11:19:14   popescu
 * PTS 10016243, fix of the internal problem issue
 * 
 *    Rev 1.18   Mar 21 2003 18:25:30   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.17   Dec 03 2002 14:23:40   KOVACSRO
 * Added AMS allocations
 * 
 *    Rev 1.16   Oct 09 2002 23:55:04   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.15   Aug 29 2002 12:53:44   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.14   Jun 04 2002 17:31:12   ZHANGCEL
 * PTS 10008333: bug fix for the persentage and AllocAmount calculate problem -- added a new function: getTotalAllocAmountPercent()
 * 
 *    Rev 1.13   22 May 2002 22:22:24   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.12   22 May 2002 18:19:42   PURDYECH
 * BFData Implementation
 */
