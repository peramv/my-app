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
// ^FILE   : CurrencyList.hpp
// ^AUTHOR : Zijian Ying
// ^DATE   : 12/09/99
//
// ^CLASS    : CurrencyList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>
///#endif

class Currency;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE CurrencyList : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   CurrencyList( BFAbstractCBO &parent );
   virtual ~CurrencyList();

   // Initialize function
   SEVERITY init( const DString& dstrTrack = I_("N"), const DString& dstrPageName = NULL_STRING );



   virtual void getStrKey( DString &strKey, const BFData *data );
   SEVERITY doCreateObject( const BFData& data, BFCBO *&pObjOut );
   bool getCurrency(DString strCurrency, Currency *&pCurrency, const BFDataGroupId& idDataGroup);

private:
   CurrencyList( const CurrencyList& copy );
   CurrencyList& operator= ( const CurrencyList& copy );
};

///#endif


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/CurrencyList.hpp-arc  $
 * 
 *    Rev 1.11   Nov 14 2004 14:30:08   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.10   Mar 21 2003 18:02:20   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.9   Oct 09 2002 23:54:10   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.8   Aug 29 2002 12:52:06   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.7   22 May 2002 18:21:28   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.6   19 Mar 2002 13:15:30   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.5   24 Jul 2001 10:04:48   KOVACSRO
 * CurrencyList is not ExchRateList ...
 * 
 *    Rev 1.4   03 May 2001 14:03:58   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.3   Jan 18 2001 16:11:48   YINGBAOL
 * add etrack
 * 
 *    Rev 1.2   Dec 20 2000 16:19:14   WINNIE
 * add getCurrency object method
 * 
 *    Rev 1.1   May 05 2000 10:32:20   WINNIE
 * Add new class Currency
 * 
 *    Rev 1.0   Feb 15 2000 10:59:04   SMITHDAV
 * Initial revision.
// 
//    Rev 1.2   Dec 14 1999 14:18:42   YINGZ
// add getStrKey
// 
//    Rev 1.1   Dec 12 1999 15:18:38   YINGZ
// ?
 * 
*/