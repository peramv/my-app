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
//    Copyright 2000 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : RESPInfoBeneficiary.hpp
// ^AUTHOR : Dan Petolescu
// ^DATE   : 11/01/2000
//
// ^CLASS    : RESPInfoBeneficiary
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************


#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>
///#endif

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE RESPInfoBeneficiary : public MFCanBFCbo, private boost::noncopyable
{
public:
   //TODO: enter specific field enumerations
   enum FIELD
   {
      UNUSED_FIELD,
      MAX_FIELDS
   };

   //TODO: enter specific contained object enumerations
   enum OBJECT
   {
      UNUSED_OBJECT,
      MAX_OBJECTS
   };

   RESPInfoBeneficiary( BFAbstractCBO &parent );
   virtual ~RESPInfoBeneficiary();

   SEVERITY init( const BFData& InstData );
   SEVERITY doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup );

private:
};

///#endif

/******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/RESPInfoBeneficiary.hpp-arc  $
 * 
 *    Rev 1.7   Nov 14 2004 14:52:22   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.6   Mar 21 2003 18:22:10   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.5   Oct 09 2002 23:54:52   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.4   Aug 29 2002 12:53:18   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.3   22 May 2002 18:20:14   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.2   19 Mar 2002 13:18:12   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.1   03 May 2001 14:04:44   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.0   Mar 22 2000 09:04:52   PETOLESC
 * Initial revision.
// 
//    Rev 1.0   Feb 18 2000 15:23:04   PETOLESC
// Initial revision.
 *
 * 
 *
 */