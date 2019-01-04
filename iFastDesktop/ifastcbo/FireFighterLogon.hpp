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
// ^FILE   : FireFighterLogon.hpp
// ^AUTHOR :  May Lin
// ^DATE   : Feb. 2, 2003
//
// ^CLASS    : FireFighterLogon
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

class IFASTCBO_LINKAGE FireFighterLogon : public MFCanBFCbo, private boost::noncopyable
{
public:

   // X-structors
   FireFighterLogon( BFAbstractCBO &parent );
   virtual ~FireFighterLogon();
   // Initialize function
	SEVERITY init(  const DString & dstCompanyId,
					const DString& dstrFFID,
					const DString& dstrPassword, 
					const DString& dstrPTSNum,
					const DString& dstrDesc1,
					const DString& dstrDesc2,
					const DString& dstrDesc3,
					const DString& dstrDesc4,
					const DString& dstrTrack = I_("N"),
					const DString& dstrPageName = NULL_STRING);
};

/******************************************************************************
//              Revision Control Entries
//******************************************************************************
//


*/