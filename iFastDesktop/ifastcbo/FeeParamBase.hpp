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
// ^FILE   : FeeParamBase.hpp
// ^AUTHOR : Yingbao Li, May Lin
// ^DATE   : January 07, 2003
//
// ^CLASS    : FeeParamBase
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>
#include "FundClassRules.hpp"

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class FeeScaleBaseList;
class FeeParamSys;

class IFASTCBO_LINKAGE FeeParamBase : public MFCanBFCbo, private boost::noncopyable
{
public:
   FeeParamBase( BFAbstractCBO &parent );
   virtual ~FeeParamBase();


   virtual SEVERITY InitNew( const BFDataGroupId& idDataGroup )=0; //for creating new object

   virtual SEVERITY getFeeScaleList( FeeScaleBaseList* &pFeeScaleList, const BFDataGroupId& idDataGroup,bool bInquire = true, bool bDefault = false, bool bRemObj = false, bool bDelete = false)=0;

   bool isTheSameBusinessDate(const BFDataGroupId& idDataGroup);
   SEVERITY validateFeeScaleList(const BFDataGroupId& idDataGroup);
   SEVERITY getFeeParamSysDef( FeeParamSys *&pFeeParamSys, const BFDataGroupId& idDataGroup );
   bool canUpdateObject(const BFDataGroupId& idDataGroup);
   bool allowNegRate(const BFDataGroupId &idDataGroup);

protected:
   virtual void doFeeCodeRelatedChanges( const BFDataGroupId& idDataGroup );
   virtual void doParamFeeTypeRelatedChanges( const BFDataGroupId& idDataGroup );
   virtual void doEffectiveDateRelatedChanges( const BFDataGroupId& idDataGroup );
   virtual void doCommGroupRelatedChanges( const BFDataGroupId& idDataGroup );
   virtual void doFundLevelFeeRelatedChanges( const BFDataGroupId& idDataGroup );
   virtual SEVERITY doValidateField( const BFFieldId& idField,
                                    const DString& strValue,
                                    const BFDataGroupId& idDataGroup );

   virtual void setFieldsReadOnly(const BFDataGroupId& idDataGroup, bool bReadOnly); 
   virtual SEVERITY doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup );
   SEVERITY validateMinMax( const BFDataGroupId& idDataGroup );
   virtual SEVERITY validateScaleRate( const BFDataGroupId& idDataGroup );
   SEVERITY ValidateEffectiveStopDate( const BFDataGroupId& idDataGroup );
   SEVERITY validateGroupFundXEdit( const BFDataGroupId& idDataGroup );
   SEVERITY validateMax(const DString &strValue, const BFDataGroupId &idDataGroup);
   SEVERITY validateMin(const DString &strValue, const BFDataGroupId &idDataGroup);

private:

   SEVERITY validateFundCode( const BFDataGroupId& idDataGroup );
   SEVERITY validateClassCode( const BFDataGroupId& idDataGroup );
   SEVERITY validateFundClassCommGroup(const BFDataGroupId& idDataGroup );

   FundClassRules m_FundClassRules;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/FeeParamBase.hpp-arc  $
//
//   Rev 1.20   Feb 21 2011 14:58:30   dchatcha
//IN# 2420424 - Cannot add MF & MFR HST Override Rates at Fund Level., recheck in for R11.4
//
//   Rev 1.19   Feb 21 2011 14:52:02   dchatcha
//IN# 2420424 - Cannot add MF & MFR HST Override Rates at Fund Level., restore 1.17, code promoteion was move to R11.4
//
//   Rev 1.18   Feb 10 2011 15:29:04   dchatcha
//IN# 2420424 - Cannot add MF & MFR HST Override Rates at Fund Level.
//
//   Rev 1.17   Nov 14 2004 14:40:12   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.16   Sep 02 2004 12:30:54   FENGYONG
//Add Conditions for PET1117 FN5
//
//   Rev 1.15   Aug 10 2004 11:24:08   FENGYONG
//PET 1117 FN 5 - Client condition Fee
//
//   Rev 1.14   Jul 21 2003 14:52:08   linmay
//PTS Ticeket #10014935
//
//   Rev 1.13   Jun 26 2003 10:08:24   linmay
//modified getFeeScaleList
//
//   Rev 1.12   Jun 20 2003 16:22:48   linmay
//modified getFeescalelist
//
//   Rev 1.11   Mar 21 2003 18:09:10   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.10   Feb 17 2003 10:18:28   YINGBAOL
//clean FundFeeList
//
//   Rev 1.9   Jan 28 2003 15:58:00   linmay
//modified setFieldsReadOnly()
//
//   Rev 1.8   Jan 27 2003 15:20:20   linmay
//added validateMinMax(const BFDataGroupId& idDataGroup )
//
//   Rev 1.7   Jan 22 2003 09:59:26   YINGBAOL
//make isSameBussinessDate public
//
//   Rev 1.6   Jan 21 2003 11:43:20   YINGBAOL
//do applyrelated changes should be protected 
//
//   Rev 1.5   Jan 20 2003 15:09:14   linmay
//modified setfieldsreadonly
//
//   Rev 1.4   Jan 18 2003 17:24:02   YINGBAOL
//Add dovalidateField and change FeeType to FeeParamType
//
//   Rev 1.3   Jan 17 2003 17:56:40   linmay
//added validatefundclasscommgroup()
//
//   Rev 1.2   Jan 15 2003 15:22:32   linmay
//added log comment
*/
