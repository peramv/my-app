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
// ^FILE   : SettlementTotal.hpp
// ^AUTHOR : Yingbao Li
// ^DATE   : May 24,2002
//
// ^CLASS    : SettlementTotal
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


class IFASTCBO_LINKAGE SettlementTotal : public MFCanBFCbo
{
public:
   SettlementTotal( BFAbstractCBO &parent );
   virtual ~SettlementTotal();

   SEVERITY init(const BFData&  );
   SEVERITY CalculateTotal(const MFCanBFCbo* pCbo ,const BFFieldId& idField, const BFDataGroupId& idDataGroup );
   SEVERITY setAllTotal(const MFCanBFCbo* pCbo, bool bSettleAll,const BFDataGroupId& idDataGroup );

protected:

   virtual SEVERITY doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup );
   // virtual SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup );
   virtual SEVERITY doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup );

private:

   double getAdjustAmount(const MFCanBFCbo* pCbo, const BFDataGroupId& idDataGroup);
   double getCommission(const MFCanBFCbo* pCbo, const BFDataGroupId& idDataGroup);
   void   changeNetValue(const BFDataGroupId& idDataGroup );
   void   changeSettleTotal(const MFCanBFCbo* pCbo,const BFFieldId& idField, const BFDataGroupId& idDataGroup,bool bGNChange );
   void   adjustCountSettle(bool bSettle,const BFDataGroupId& idDataGroup );
   void   setDefaultValue(const BFDataGroupId& idDataGroup );

   // copy constructor
   SettlementTotal( const SettlementTotal& copy ); //not implemented
   // = Operator
   SettlementTotal& operator= ( const SettlementTotal& copy );//not implemented


};


//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/SettlementTotal.hpp-arc  $
//
//   Rev 1.8   Nov 14 2004 14:54:08   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.7   Mar 21 2003 18:24:00   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.6   Oct 09 2002 23:54:58   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.5   Aug 29 2002 12:53:38   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.4   Jun 13 2002 17:16:20   YINGBAOL
//set default value for calculate fields
//
//   Rev 1.3   Jun 11 2002 11:43:50   YINGBAOL
//more business rules added
//
//   Rev 1.2   Jun 06 2002 16:07:48   YINGBAOL
//save work
//



//
