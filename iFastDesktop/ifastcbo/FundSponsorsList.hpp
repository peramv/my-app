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
//    Copyright 2000 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : FundSponsorsList.hpp
// ^AUTHOR : Adrian Vasile
// ^DATE   : Nov 18, 2000
//
// ^CLASS    : FundSponsorsList
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


class IFASTCBO_LINKAGE FundSponsorsList : public MFCanBFCbo, private boost::noncopyable
{
public:
   FundSponsorsList( BFAbstractCBO &parent );
   virtual ~FundSponsorsList();

   SEVERITY init( const DString& dstrTrack=I_("N"), const DString& dstrPageName = NULL_STRING );
   virtual void getStrKey ( DString &strKey, const BFData *data );
   void getStrKey( DString& dstKey, const DString& dstFromFund );

	SEVERITY getFundSponsorSubstitutionList( DString &dstrFundSponsorSubstList,bool bMatch = true );
	SEVERITY getFundSponsorCodeSubstList( DString &dstrFundSponsorCodeSubstList );
	SEVERITY getFundSponsor( const DString &dstrFundGroup, BFAbstractCBO *&pFundSponsor );

private:
};

///#endif

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/FundSponsorsList.hpp-arc  $
//
//   Rev 1.11   Nov 14 2004 14:43:16   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.10   Jul 27 2004 15:29:16   VADEANUM
//PET1117 FN01 - Added getFundSponsorCodeSubstList().
//
//   Rev 1.9   Jul 27 2004 09:25:32   YINGBAOL
//PET1117:change getFundSponsorSubstitution list method
//
//   Rev 1.8   Jul 13 2004 16:32:24   VADEANUM
//PET1117 FN01 - Build substitution set and retrieve a specific record.
//
//   Rev 1.7   Mar 21 2003 18:12:10   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.6   Oct 09 2002 23:54:34   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.5   Aug 29 2002 12:52:34   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.4   22 May 2002 18:20:58   PURDYECH
//BFData Implementation
//
//   Rev 1.3   19 Mar 2002 13:17:12   PURDYECH
//Use #pragma once as include guard
//Remove compile time "including..." message
//
//   Rev 1.2   03 May 2001 14:04:16   SMITHDAV
//Session management restructuring.
//
//   Rev 1.1   Jan 18 2001 16:12:08   YINGBAOL
//add etrack
//
//   Rev 1.0   Nov 20 2000 17:54:10   VASILEAD
//Initial revision.
//
//   Rev 1.0   Apr 03 2000 08:50:16   BUZILA
//Initial revision.
 * 
*/