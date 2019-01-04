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
//    Copyright 2002 by International Financial.
//
//
//******************************************************************************
//
// ^FILE   : FireFighterLogonInfo.cpp
// ^AUTHOR : May Lin
// ^DATE   : Feb. 2, 2003
//
// ^CLASS    : FireFighterLogonInfo 
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "FireFighterLogonInfo.hpp"

#include "firefighterlogon.hpp"
#include "version_app.hpp"
#include <ifastdbrkr\dstcsecurity.hpp>

namespace  
{
   const I_CHAR * const CLASSNAME = I_( "FireFighterLogonInfo" );  
   const I_CHAR * const YES		  = I_( "Y" );

}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId FireFighterId;
   extern CLASS_IMPORT const BFTextFieldId FireFighterPassword;
   extern CLASS_IMPORT const BFDecimalFieldId PTSNumber;
   extern CLASS_IMPORT const BFTextFieldId Description1;
   extern CLASS_IMPORT const BFTextFieldId Description2;
	extern CLASS_IMPORT const BFTextFieldId Description3;
   extern CLASS_IMPORT const BFTextFieldId Description4;
   extern CLASS_IMPORT const BFTextFieldId UpdateStatus;

}

namespace CND
{  // Conditions used
   extern const long ERR_INVALID_FIRE_FIGHTER_LOGON;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//  Field DD Id,            State Flags,     Group Flags 
   { ifds::FireFighterId,            BFCBO::REQUIRED,		0 }, 
   { ifds::FireFighterPassword,      BFCBO::REQUIRED,		0 }, 
   { ifds::PTSNumber,					 BFCBO::REQUIRED,		0 }, 
   { ifds::Description1,             BFCBO::NONE,			0 }, 
   { ifds::Description2,             BFCBO::NONE,			0 }, 
	{ ifds::Description3,             BFCBO::NONE,			0 }, 
   { ifds::Description4,             BFCBO::NONE,			0 }, 

};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//*********************************************************************************
FireFighterLogonInfo::FireFighterLogonInfo( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );

}


//*********************************************************************************
FireFighterLogonInfo::~FireFighterLogonInfo()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//*********************************************************************************
SEVERITY FireFighterLogonInfo::init(
	const BFDataGroupId& idDataGroup,
    const DString& dstrTrack,
    const DString& dstrPageName)

{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init(DString&, DString&, DString&, DString&..." ) );
 
	_dstrVersion =getSecurity()->getVersionLabel();
	_dstrVersion.upperCase();
	
	_dstrAccessId = getSecurity()->getAccessID();
	_dstrAccessId.strip().upperCase();

	_dstrUserId = getSecurity()->getUserId();
	//_dstrPassWord = 

   return(GETCURRENTHIGHESTSEVERITY());
}

//****************************************************************************************
// method SEVERITY FireFighterLogonInfo::validateLogonInfo( const BFDataGroupId& idDataGroup )
// is removed since we noe ignore the error when logoninfor cannot be saved
//****************************************************************************************

//****************************************************************************************
bool FireFighterLogonInfo::isSameVersion( const BFDataGroupId& idDataGroup )
{
	 DString dstrVersion = ifds::getAppVersion();
	 return ( dstrVersion.upperCase() == _dstrVersion );

}

//****************************************************************************************
bool FireFighterLogonInfo::isAccessIdR( const BFDataGroupId& idDataGroup )
{
	
	 return ( _dstrAccessId == I_("RRID"));

}

//****************************************************************************************
bool FireFighterLogonInfo::isAccessIdF( const BFDataGroupId& idDataGroup )
{
	
	 return ( _dstrAccessId == I_("FFID"));

}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/FireFighterLogonInfo.cpp-arc  $
// 
//    Rev 1.7   Mar 05 2010 15:56:28   yingz
// rrid ffid login support
// 
//    Rev 1.6   Jan 08 2010 11:58:12   yingz
// delay view 276 for inc#1936007
// 
//    Rev 1.5   Sep 12 2005 15:59:38   ZHANGCEL
// PET1235 - FN02 -- Apply samilar logic as RRID for FFID
// 
//    Rev 1.4   Aug 31 2005 16:06:26   ZHANGCEL
// PET1235 - FN02 -- Add logic for dealing with two fields Description3 and Description4
// 
//    Rev 1.3   Aug 22 2005 10:50:06   ZHANGCEL
// PET 1235 - FN02 -- Enhancement for Restricted Read Only Unserid 
// 
//    Rev 1.2   Nov 14 2004 14:41:06   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.1   Dec 11 2003 11:41:32   linmay
// added isSameVersion( )
// 
//    Rev 1.0   Dec 09 2003 09:06:56   linmay
// Initial Revision
// 
 */