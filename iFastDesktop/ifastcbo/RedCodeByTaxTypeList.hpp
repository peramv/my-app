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
// ^FILE   : RedCodeByTaxTypeList.hpp
// ^AUTHOR : Zijian Ying
// ^DATE   : 04/20/2000
//
// ^CLASS    : RedCodeByTaxTypeList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************


#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>

class RedCodeByTaxType;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif


class IFASTCBO_LINKAGE RedCodeByTaxTypeList : public MFCanBFCbo, private boost::noncopyable
{
public:
   //declare field enumerations

   // X-structors
   RedCodeByTaxTypeList( BFAbstractCBO &parent );
   virtual ~RedCodeByTaxTypeList();

   // Initialize function
   SEVERITY init( DString& TaxType, 
                  DString& CodeType, 
                  const DString& dstrTrack= I_("N"),
                  const DString& dstrPageName = NULL_STRING );

   void getStrKey ( DString& strKey, const BFData* data );
   SEVERITY doCreateObject( const BFData& data, BFCBO *&pObjOut );
   bool getRedCodeByTaxType( DString dstrTaxType, RedCodeByTaxType *&pRedCodeByTaxType, const BFDataGroupId& idDataGroup );

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/RedCodeByTaxTypeList.hpp-arc  $
// 
//    Rev 1.11   Nov 14 2004 14:51:32   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.10   Mar 21 2003 18:21:06   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.9   Oct 09 2002 23:54:50   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.8   Aug 29 2002 12:53:14   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.7   22 May 2002 18:20:10   PURDYECH
// BFData Implementation
// 
//    Rev 1.6   19 Mar 2002 13:18:08   PURDYECH
// Use #pragma once as include guard
// Remove compile time "including..." message
// 
//    Rev 1.5   Mar 12 2002 16:02:34   JANKAREN
// Added getRedCodeByTaxType()
// 
//    Rev 1.4   03 May 2001 14:04:40   SMITHDAV
// Session management restructuring.
// 
//    Rev 1.3   Jan 18 2001 16:12:24   YINGBAOL
// add etrack
// 
//    Rev 1.2   Oct 27 2000 10:18:56   KOVACSRO
// Added doCreateObject() and getStrKey().
// 
//    Rev 1.1   May 09 2000 11:35:00   YINGZ
// intial revision
*/
