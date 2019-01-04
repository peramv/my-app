#pragma once
#define DISABLE_MACRO_REDEFINITION_WARNINGS 1




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
//    Copyright 2000 by DST Canada, Inc.
//
//
//******************************************************************************
//
// ^FILE   : MinMaxInfoList.hpp
// ^AUTHOR : Celia Zhang
// ^DATE   : 02/15/2000
//
// ^CLASS    : MinMaxInfoList
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

class IFASTCBO_LINKAGE MinMaxInfoList : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   MinMaxInfoList( BFAbstractCBO &parent );
   virtual ~MinMaxInfoList();

   SEVERITY init( const DString& AccountNum, 
                  const DString& dstrAsofDate,
                  const DString& dstrTrack= I_("N"),
                  const DString& dstrPageName = NULL_STRING );

private:

};

///#endif

/* $Log:   Y:/VCS/BF iFAST/ifastcbo/MinMaxInfoList.hpp-arc  $
 * 
 *    Rev 1.9   Nov 14 2004 14:50:28   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.8   Mar 21 2003 18:19:08   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.7   Oct 09 2002 23:54:48   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.6   Aug 29 2002 12:53:08   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.5   22 May 2002 18:20:16   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.4   19 Mar 2002 13:18:02   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.3   03 May 2001 14:04:34   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.2   Jan 18 2001 16:12:22   YINGBAOL
 * add etrack
 * 
 *    Rev 1.1   Mar 21 2000 14:31:44   ZHANGCEL
 * Milestone check in
 * 
 *    Rev 1.0   Mar 20 2000 15:48:34   ZHANGCEL
 * Initial revision.
//
//
 *
 */