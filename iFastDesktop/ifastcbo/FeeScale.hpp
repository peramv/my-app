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
// ^FILE   : FeeScale.hpp
// ^AUTHOR : Yingbao Li
// ^DATE   : January 24, 2002
//
// ^CLASS    : FeeScale
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>
class BFData;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE FeeScale : public MFCanBFCbo, private boost::noncopyable
{
public:
   FeeScale( BFAbstractCBO &parent );
   virtual ~FeeScale();
   SEVERITY init( const BFData& InstData );
   SEVERITY init(const BFDataGroupId& idDataGroup ); // init new

   void setValidFlagDerive( const BFFieldId& idField,const BFDataGroupId& idDataGroup,bool bValid ) // temp will be moved after base support
   {
      BFCBO::setValidFlag( idField,idDataGroup,bValid );
   }

   SEVERITY ChangeLevel(  const int idLevel,const BFDataGroupId& idDataGroup );

protected:
   virtual SEVERITY doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup );
   virtual SEVERITY doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup );
   virtual void doInitWithDefaultValues( const BFDataGroupId& idDataGroup );

private:
   SEVERITY validateLUBound(const BFDataGroupId& idDataGroup );
   SEVERITY validateScaleRate( const BFDataGroupId& idDataGroup );  

   BFData* localData;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/FeeScale.hpp-arc  $
//
//   Rev 1.9   Nov 14 2004 14:40:30   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.8   Mar 21 2003 18:09:52   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.7   Oct 09 2002 23:54:30   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.6   Aug 29 2002 12:52:26   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.5   22 May 2002 18:21:06   PURDYECH
//BFData Implementation
//
//   Rev 1.4   05 Apr 2002 15:16:52   YINGBAOL
//add change level
//
//   Rev 1.3   Mar 05 2002 14:10:08   YINGBAOL
//add ValidateScaleRate etc.
//
//   Rev 1.2   Feb 28 2002 12:49:26   YINGBAOL
//add more function
//
//   Rev 1.1   Feb 22 2002 14:20:40   YINGBAOL
//more function added
 * 
 
*/

