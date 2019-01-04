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
//    Copyright 1999 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : TaxTypeRuleList.hpp
// ^AUTHOR : Celia Zhang
// ^DATE   : October 19, 1999
//
// ^CLASS    : TaxTypeRuleList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION : Tax Type Rule 
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

class IFASTCBO_LINKAGE TaxTypeRuleList : public MFCanBFCbo, private boost::noncopyable
{
public:
   TaxTypeRuleList( BFAbstractCBO &parent );
   virtual ~TaxTypeRuleList(void);

   SEVERITY init( const DString& dstrTrack = I_("N"), 
                  const DString& dstrPageName = NULL_STRING 
                );
   void getStrKey (DString &strKey, const BFData* data);
   void getStrKey (DString &strKey, const DString &dstTaxType, const DString& dstTaxTypeSchedule);
   SEVERITY doCreateObject (const BFData& data, BFCBO *&pObjOut);
   void createTaxTypesList (DString &strCodesList);
   bool checkEligibleAge(const DString &taxType);
   bool getTFSAEligibleAge(const DSTCWorkSession &workSession, const DString &srcProvince, int &iElgbAge);

private:
};

///#endif

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/TaxTypeRuleList.hpp-arc  $
 * 
 *    Rev 1.14   15 Apr 2008 12:10:18   kovacsro
 * PET2255 FN47 - New Ontario LIF
 * 
 *    Rev 1.13   Nov 23 2004 16:09:34   popescu
 * Turned versioning off, removed idDataGroup from TaxTypeRuleList::createTaxTypesList
 * 
 *    Rev 1.12   Nov 14 2004 14:57:12   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.11   Mar 21 2003 18:26:28   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.10   Oct 09 2002 23:55:08   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.9   Aug 29 2002 12:53:50   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.8   22 May 2002 18:19:18   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.7   19 Mar 2002 13:18:54   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.6   11 May 2001 10:37:08   HSUCHIN
 * Sync up with SSB (1.4.1.0)
 * 
 *    Rev 1.5   03 May 2001 14:05:02   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.4   Mar 30 2001 11:11:40   OLTEANCR
 * added function getTaxTypeSubstList
 * 
 *    Rev 1.3   06 Feb 2001 11:48:24   SMITHDAV
 * Removed unused code and depenencies
 * 
 *    Rev 1.2   Jan 18 2001 16:12:50   YINGBAOL
 * add etrack
 * 
 *    Rev 1.1   May 18 2000 16:45:08   WINNIE
 * Implement TaxTypeRule and related validation
*/