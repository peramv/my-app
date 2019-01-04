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
// ^FILE   : FireFighterLogonInfo.hpp
// ^AUTHOR :  May Lin
// ^DATE   : Feb. 2, 2003
//
// ^CLASS    : FireFighterLogonInfo
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

class IFASTCBO_LINKAGE FireFighterLogonInfo : public MFCanBFCbo, private boost::noncopyable
{
public:

   // X-structors
   FireFighterLogonInfo( BFAbstractCBO &parent );
   virtual ~FireFighterLogonInfo();
   // Initialize function
	SEVERITY init(  const BFDataGroupId& idDataGroup,
					const DString& dstrTrack = I_("N"),
					const DString& dstrPageName = NULL_STRING);
	bool isSameVersion( const BFDataGroupId& idDataGroup );
	bool isAccessIdR( const BFDataGroupId& idDataGroup );
	bool isAccessIdF( const BFDataGroupId& idDataGroup );



private:
	DString _dstrVersion;
	DString _dstrAccessId;
	DString _dstrUserId;

};

/******************************************************************************
//              Revision Control Entries
//******************************************************************************
//


*/