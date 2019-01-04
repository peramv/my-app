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
// ^FILE   : AMSRebDateCalc.hpp
// ^AUTHOR : May Lin
// ^DATE   : July 24, 2003
//
// ^CLASS    : AMSRebDateCalc
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
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

class IFASTCBO_LINKAGE AMSRebDateCalc : public MFCanBFCbo, private boost::noncopyable
{
public:

   // X-structors
   AMSRebDateCalc( BFAbstractCBO &parent );
   virtual ~AMSRebDateCalc();
   // Initialize function
	SEVERITY init( const DString& dstrEffectiveDate, 
                  const DString& dstrRebFreq,
                  const DString& dstrTrack = I_("N"),
                  const DString& dstrPageName = NULL_STRING);
};

/******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AMSRebDateCalc.hpp-arc  $
//
//   Rev 1.3   Jul 19 2007 14:23:20   smithdav
//PET2360 FN02 - Fix NextRebalanceDate recalc.
//
//   Rev 1.2   Oct 03 2003 15:47:44   linmay
//PTS Ticket#10022366, schema change
//
//   Rev 1.1   Jul 31 2003 13:56:44   linmay
//added amstype
//
//   Rev 1.0   Jul 28 2003 11:18:26   linmay
//Initial Revision
//
*/
