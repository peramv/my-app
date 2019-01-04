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
// ^FILE   : GroupFundList.hpp
// ^AUTHOR : Zijian Ying
// ^DATE   : 12/09/99
//
// ^CLASS    : GroupFundList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>
#include <bfutil\bfcritsec.hpp>
///#endif

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE GroupFundList : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   GroupFundList( BFAbstractCBO &parent );
   virtual ~GroupFundList();

   void getAllowedFunds( DString &dstList, const DString& dstGroupCode, bool bMakeUppercase = true, bool bAddBlankFund = true  );
   void getAllowedClasses( DString &dstList, const DString& dstGroupCode, const DString& dstFundCode, bool bMakeUppercase = true );

   // Initialize function
   SEVERITY init ( const DString &dstrGroupCode = NULL_STRING, 
                   const DString &dstrTrack = I_("N"), 
                   const DString &dstrPageName = NULL_STRING);
   SEVERITY initWithFund ( const DString &dstrGroupCode = NULL_STRING, 
                           const DString &dstrFundCode = NULL_STRING, 
                           const DString &dstrTrack = I_("N"), 
                           const DString &dstrPageName = NULL_STRING);

   virtual void getStrKey (DString &strKey, const BFData *data);
   void getStrKey ( DString& strKey, const DString&  dstGroupCode, const DString&  dstFundCode, const DString&  dstClassCode );
   SEVERITY doCreateObject( const BFData& data, BFCBO *&pObjOut );
   bool isESoPEligibleFundClass(const DString& strGroup, const DString& strFund, const DString& strClass);
   bool doesGroupFundClassExist( const DString& dstrGroup, const DString& dstrFund, const DString& dstrClass);

private:
   std::set <DString> fundCodes;
   BFCritSec _csFundCodes;
};

///#endif


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/GroupFundList.hpp-arc  $
 * 
 *    Rev 1.18   Sep 29 2005 09:15:42   popescu
 * Incident# 406322 - cached call to view 98
 * 
 *    Rev 1.17   Aug 31 2005 10:40:52   popescu
 * 63 - BPS performance issues. cached the 98 view call.
 * 
 *    Rev 1.16   Feb 15 2005 20:21:18   winnie
 * PTS 237768 : Get Group Fund by Fund Code to speed up the performance. New method to call view 98 with fund code.
 * 
 *    Rev 1.15   Nov 14 2004 14:43:38   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.14   Nov 04 2004 17:37:54   popescu
 * PET 1117/06, Trade processing
 * 
 *    Rev 1.13   Sep 12 2004 17:19:22   HERNANDO
 * PET1117 FN22 - Support for Group Fund List.
 * 
 *    Rev 1.12   Mar 21 2003 18:12:44   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.11   Oct 09 2002 23:54:36   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.10   Aug 29 2002 12:52:36   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.9   22 May 2002 18:21:00   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.8   19 Mar 2002 13:17:18   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.7   Nov 29 2001 16:34:44   ZHANGCEL
 * Added a new parameter dstrGroupCode in init()
 * 
 *    Rev 1.6   14 Sep 2001 16:57:12   KOVACSRO
 * Added isESoPEligibleFundClass method.
 * 
 *    Rev 1.5   03 May 2001 14:04:18   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.4   Jan 18 2001 16:12:08   YINGBAOL
 * add etrack
 * 
 *    Rev 1.3   Apr 13 2000 10:37:46   BUZILA
 * added GroupFund
 * 
 *    Rev 1.2   Apr 03 2000 08:52:44   BUZILA
 * Added    void getStrKey ( DString& strKey, const DString&  dstGroupCode, const DString&  dstFundCode, const DString&  dstClassCode )
 * 
 *    Rev 1.1   Mar 17 2000 14:24:04   BUZILA
 * added   getStrKey ( strKey, dstGroupCode, dstFundCode, dstClassCode ) method
 * 
 *    Rev 1.0   Feb 15 2000 10:59:10   SMITHDAV
 * Initial revision.
// 
//    Rev 1.2   Dec 14 1999 14:18:42   YINGZ
// add getStrKey
// 
//    Rev 1.1   Dec 12 1999 15:18:38   YINGZ
// ?
 * 
*/