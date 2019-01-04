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
// ^FILE   : FeeScaleSys.hpp
// ^AUTHOR : Yingbao Li, May Lin
// ^DATE   : January 08, 2002
//
// ^CLASS    : FeeScaleBase
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\FeeScaleBase.hpp>
#include <boost\utility.hpp>
class BFData;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE FeeScaleSys : public FeeScaleBase
{
public:
   FeeScaleSys( BFAbstractCBO &parent );
   virtual ~FeeScaleSys();
   SEVERITY init( const BFData& InstData, bool bDefault = false);
   SEVERITY init(const BFDataGroupId& idDataGroup ); // init new
   SEVERITY setValueFromDefault( BFCBO* pCBO, const BFDataGroupId& idDataGroup );
   bool isTheSameBusinessDate(const BFDataGroupId& idDataGroup);
   bool isScaleReadOnly(const BFDataGroupId& idDataGroup);
   SEVERITY clone(const BFDataGroupId& idDataGroup, FeeScaleSys*& pFeeScaleSys);

protected: 
   virtual SEVERITY doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup );
   virtual SEVERITY doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup );
   virtual SEVERITY validateScaleRate( const BFDataGroupId& idDataGroup ); 

   
private:
   BFData* localData;

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/FeeScaleSys.hpp-arc  $
//
//   Rev 1.8   Nov 14 2004 14:40:40   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.7   Sep 10 2004 15:51:48   FENGYONG
//PET1117 FN5 - Client Fee
//
//   Rev 1.6   Jul 21 2003 15:06:06   linmay
//PTS Ticket #10014935
//
//   Rev 1.5   Jun 20 2003 16:28:42   linmay
//PTS#10014935
//
//   Rev 1.4   Mar 21 2003 18:10:12   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.3   Jan 17 2003 17:50:48   linmay
//added doValidateField, doApplyRelatedChanges
//
//   Rev 1.2   Jan 15 2003 15:24:56   linmay
//added log comment
*/