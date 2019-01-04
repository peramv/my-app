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
//
//******************************************************************************
//
// ^FILE   : SysAllocation.hpp
// ^AUTHOR : Chin Hsu
// ^DATE   : Feburary 25, 1999
//
// ^CLASS    : SysAllocation
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************


#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>

class SplitCommissionList;
class Systematic;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE SysAllocation : public MFCanBFCbo, private boost::noncopyable
{
public:
   //TODO: remove public default constructor if using repository
   SysAllocation( BFAbstractCBO &parent );
   virtual ~SysAllocation();
   SEVERITY init();
   SEVERITY init(const BFData &viewData);
   void getField( const BFFieldId& idField, 
      DString& strFieldValue, const BFDataGroupId& idDataGroup, bool formattedReturn = false ) const;
   SEVERITY setField( const BFFieldId& idField, const DString& dstrValue, 
      const BFDataGroupId& idDataGroup, bool bFormatted = true, bool bSideEffect = false, 
      bool  bCheckCurrentValue = true );
   SEVERITY doValidateField(const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup);
   virtual void doInitWithDefaultValues( const BFDataGroupId& idDataGroup );
   virtual SEVERITY doApplyRelatedChanges( const BFFieldId& idField,const BFDataGroupId& idDataGroup );                                      

   void ModelOffer( SysAllocation * Model, const BFDataGroupId& idDataGroup );
   SEVERITY getSplitCommissionList(SplitCommissionList *&rpSplitCommissionList, const BFDataGroupId& idDataGroup);
   void GetDefaultSplitComm ( const BFDataGroupId& idDataGroup );
   SEVERITY setTransTypePACIdFromSystematic(const BFDataGroupId& idDataGroup );
   //const Systematic*& getSystematicPtr() const;
private:
   SEVERITY getMaxFeeRate(SplitCommissionList *&rpSplitCommissionList,const BFDataGroupId& idDataGroup);
   SEVERITY fetchSplitCommisionListUsingSystematicParent(SplitCommissionList *&rpSplitCommissionList, 
      const BFDataGroupId& idDataGroup);
   void validateAmount(const DString& Amount, const BFDataGroupId& idDataGroup );
   void validatePercentage( const DString& strValue, const BFDataGroupId& idDataGroup ) const;
   void validateFundClass(const BFDataGroupId& idDataGroup );
   SEVERITY validateFundClassSoftCapped(const BFDataGroupId& idDataGroup);
   SEVERITY validateFundClassPayout(const BFDataGroupId& idDataGroup);
   void setFundClassCode( const BFFieldId& idField,const BFDataGroupId& idDataGroup);
   void setFundNumber( const BFFieldId& idField,const BFDataGroupId& idDataGroup);
   SEVERITY validateFundCode( const DString& dstrfundCode, const BFDataGroupId& idDataGroup );
   SEVERITY validateClassCode( const DString& dstrfundCode, const DString& dstrClassCode, const BFDataGroupId& idDataGroup );
   SEVERITY validateAllocCurrency( const BFDataGroupId& idDataGroup );
	SEVERITY validateFundClassAccNumDate ( const BFDataGroupId& idDataGroup );

   bool _bInitialSplitComm;
   bool splitCommActive ( const BFDataGroupId& idDataGroup );
};

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/SysAllocation.hpp-arc  $
 * 
 *    Rev 1.24   Jul 31 2012 14:27:52   wp040027
 * IN# 3006862-CPF-Enable Fee in PAC/Corrected default Fee in PAC and Trade screen/Max Fee Validation
 * 
 *    Rev 1.23   Sep 28 2005 16:22:16   ZHANGCEL
 * PET1244 - FN01 - Seg Fund Evolution enhancement
 * 
 *    Rev 1.22   Nov 14 2004 14:56:18   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.21   Apr 29 2003 17:13:58   popescu
 * PTS 10016204
 * 
 *    Rev 1.20   Mar 21 2003 18:25:24   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.19   Oct 09 2002 23:55:04   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.18   Aug 29 2002 12:53:44   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.17   Jun 04 2002 17:29:42   ZHANGCEL
 * PTS 10008333: bug fix for the persentage and AllocAmount calculate problem -- added a override function setField()
 * 
 *    Rev 1.16   22 May 2002 22:22:24   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.15   22 May 2002 18:19:42   PURDYECH
 * BFData Implementation
 */
