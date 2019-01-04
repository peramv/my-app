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
// ^FILE   : RedCodeByTaxType.hpp
// ^AUTHOR : Zijian Ying
// ^DATE   : 04/20/2000
//
// ^CLASS    : RedCodeByTaxType
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************


#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>
///#endif

class MgmtCoOptions;
class BankList;
class RedCodeByTaxTypeList;
class GroupFundList;
class CurrencyList;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE RedCodeByTaxType : public MFCanBFCbo, private boost::noncopyable
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

   RedCodeByTaxType( BFAbstractCBO &parent );
   virtual ~RedCodeByTaxType();

   SEVERITY init( const BFData& data );
};

///#endif

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/RedCodeByTaxType.hpp-arc  $
// 
//    Rev 1.7   Nov 14 2004 14:51:28   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.6   Oct 09 2002 23:54:50   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.5   Aug 29 2002 12:53:14   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.4   22 May 2002 18:20:10   PURDYECH
// BFData Implementation
// 
//    Rev 1.3   19 Mar 2002 13:18:06   PURDYECH
// Use #pragma once as include guard
// Remove compile time "including..." message
// 
//    Rev 1.2   03 May 2001 14:04:38   SMITHDAV
// Session management restructuring.
// 
//    Rev 1.1   May 09 2000 11:35:00   YINGZ
// intial revision
*/