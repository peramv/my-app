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
// ^FILE   : RecipientTypeList.hpp.
// ^AUTHOR : Celia Zhang
// ^DATE   : Nov 2000
//
// ^CLASS    : RecipientTypeList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION : The Recipient Type list
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE RecipientTypeList : public MFCanBFCbo, private boost::noncopyable
{

public:
   RecipientTypeList( BFAbstractCBO &parent );
   virtual ~RecipientTypeList();

   SEVERITY init( const DString& dstrTrack= I_("N"), 
                  const DString& dstrPageName = NULL_STRING);

   SEVERITY getRecipientType ( const DString& taxType, 
                               const DString& acctType, 
                               const DString& taxJuris, 
                               DString& strRecipientType, 
                               const BFDataGroupId &idDataGroup);
private:
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/RecipientTypeList.hpp-arc  $
//
//   Rev 1.10   08 Dec 2008 12:35:04   popescu
//Incident 1507900
//Recipient Code Changes in Base and Desktop
//
//   Rev 1.9   Nov 14 2004 14:51:26   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.8   Mar 21 2003 18:20:40   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.7   Oct 09 2002 23:54:50   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.6   Aug 29 2002 12:53:14   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.5   22 May 2002 18:20:10   PURDYECH
//BFData Implementation
//
//   Rev 1.4   19 Mar 2002 13:18:06   PURDYECH
//Use #pragma once as include guard
//Remove compile time "including..." message
//
//   Rev 1.3   03 May 2001 14:04:38   SMITHDAV
//Session management restructuring.
//
//   Rev 1.2   Jan 18 2001 16:12:24   YINGBAOL
//add etrack
//
//   Rev 1.1   Nov 24 2000 17:02:04   ZHANGCEL
//remove the override function getStrKey()
//
//   Rev 1.0   Nov 22 2000 12:09:42   ZHANGCEL
//Initial revision.
// 
//
*/