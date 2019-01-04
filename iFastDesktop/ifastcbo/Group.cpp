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
//    Copyright 1999 by DST Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : Group.cpp
// ^AUTHOR : Celia Zhang
// ^DATE   : 09/03/2000
//
// ^CLASS    : Group
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "group.hpp"
#include "groupfundlist.hpp"
#include <ifastdataimpl\dse_dstc0088_vw.hpp>

namespace
{
   const I_CHAR * const CLASSNAME = I_( "Group" );
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId GroupCode;
   extern CLASS_IMPORT const BFTextFieldId FundCode;
   extern CLASS_IMPORT const BFTextFieldId ClassCode;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//  Field DD Id,            State Flags,             Group Flags 
   { ifds::GroupName,   BFCBO::NONE, 0 }, 
   { ifds::rxGroupCode, BFCBO::NONE, 0 }, 
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//****************************************************************************
Group::Group( BFAbstractCBO &parent ) :
MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );

   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );
}

//****************************************************************************
Group::~Group()
{
   TRACE_DESTRUCTOR (CLASSNAME);
   if (_pGroupFundList != NULL)
   {
      delete _pGroupFundList;
      _pGroupFundList = NULL;
   }
}

//****************************************************************************
SEVERITY Group::init (const BFData& data)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   attachDataObject( const_cast<BFData&>(data), false, true );
   _pGroupFundList = NULL;
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY Group::getGroupFundList (GroupFundList *&pGroupFundList)
{

   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getGroupFundList" ) );
   if( !_pGroupFundList )
   {
      DString dstrGroupCode;

      getField(ifds::rxGroupCode, dstrGroupCode, BF::HOST, false );
      _pGroupFundList = new GroupFundList( *this );
      if( _pGroupFundList->init( dstrGroupCode ) >= SEVERE_ERROR )
      {
         delete _pGroupFundList;
         _pGroupFundList = NULL;
      }
   }

   pGroupFundList = _pGroupFundList;

   return GETCURRENTHIGHESTSEVERITY();
}


//******************************************************************************
SEVERITY Group::getGroupFundListByFund ( GroupFundList *&pGroupFundList, 
                                         const DString &fundCode)
{

   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("getGroupFundListForFund"));

   DString strKey (I_("GroupFundList")),
      groupCode;

   getField (ifds::rxGroupCode, groupCode, BF::HOST, false);

//look for the list
   pGroupFundList = dynamic_cast <GroupFundList*> (getObject ( strKey, 
                                                               BF::HOST));
   bool bSetObject = !pGroupFundList;
   if (bSetObject)
   {
      pGroupFundList = new GroupFundList (*this);
   }
   if (pGroupFundList->initWithFund (groupCode, fundCode) <= WARNING)
   {
      if (bSetObject) //do not set it twice
      {
         setObject ( pGroupFundList,
                     strKey,
                     OBJ_ACTIVITY_NONE,
                     BF::HOST);
      }
   }            
   else 
   {
      if (bSetObject) //first time it is allowed to delete
      {
         delete pGroupFundList;
         pGroupFundList = NULL;
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}



//***************************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/Group.cpp-arc  $
// 
//    Rev 1.10   Sep 29 2005 09:15:28   popescu
// Incident# 406322 - cached call to view 98
// 
//    Rev 1.9   Aug 31 2005 10:40:30   popescu
// 63 - BPS performance issues. cached the 98 view call.
// 
//    Rev 1.8   Aug 30 2005 17:37:30   popescu
// 63 - BPS performance issues fixes
// 1. Cached call to view 120 - account number validation  (trade.cpp/hpp)
// 2. called the isHouseBroker method in Purchase::validateBorrowedFunds;
// 3. AgentList/BranchList - called sorting only if agent/branch code are empty (search for all)
// 4. Fixed 'reset' of trade (moved one line from Trade::firstLineInInit to doInit (idatagroup)
// 5. Fixed Group.cpp/MFAccount.cpp - cached view call to 98.
// 6. MFAccount::initDefaultAddress01 checked if shareholder in either nominee or intermediary, to skip a call to view 43
// 
//    Rev 1.7   Mar 13 2005 17:15:12   winnie
// Restore the previous version. No longer have a pointer in Group object for GroupFundList but instead have the object which create it delete the GroupFundList as soon as finish using it.
// 
//    Rev 1.6   Mar 11 2005 14:08:48   smithdav
// Fixed bug in Group::getGroupFundListByFund function where BPS threads clashed the function call concurrently.
//
//    Rev 1.5   Feb 15 2005 20:19:10   winnie
// PTS 237768 : Get Group Fund by Fund Code to speed up the performance.
// 
//    Rev 1.4   Nov 14 2004 14:43:30   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.3   Oct 09 2002 23:54:34   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.2   Aug 29 2002 12:55:58   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.1   22 May 2002 18:28:48   PURDYECH
// BFData Implementation
// 
//    Rev 1.0   Nov 29 2001 16:43:58   ZHANGCEL
// Initial revision.
 * 
 */
