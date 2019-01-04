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
// ^FILE   : BFObjectKey.cpp
// ^AUTHOR : 
// ^DATE   : May 1999
//
// ----------------------------------------------------------
//
// ^CLASS : BFObjectKey
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************
#include <bfutil\RTRevisionDefines.hpp>
RT_SOURCE_REVISION( "$Archive:   Y:/VCS/BF Core/bfcbo/BFObjectKey.cpp-arc  $", "$Revision:   1.5  $" )

#include "bfobjectkey.hpp"

//******************************************************************************
BFObjectKey::BFObjectKey( const DString& strKey, const BFDataGroupId& idDataGroup, BF_OBJ_ACTIVITY activity, BF_OBJ_TYPE type ) 
: idDataGroup_( idDataGroup )
, activity_( activity )
, type_( type )
, dstrKey_( strKey )
{
}

//******************************************************************************
BFObjectKey::BFObjectKey( const BFObjectKey& rhs )
: idDataGroup_( rhs.idDataGroup_ )
{
   *this = rhs;
}

//******************************************************************************
BFObjectKey& BFObjectKey::operator=( const BFObjectKey& rhs )
{
   if( this != &rhs )
   {
      idDataGroup_ = rhs.idDataGroup_;
      activity_ = rhs.activity_;
      type_ = rhs.type_;
      dstrKey_ = rhs.dstrKey_;
   }
   return( *this );
}

//******************************************************************************
bool BFObjectKey::operator ==(const BFObjectKey &rhs ) const
{
   if( getDataGroupId() == rhs.getDataGroupId() && 
       getActivity() == rhs.getActivity() && 
       getType() == rhs.getType() && 
       getStringKey() == rhs.getStringKey() )
   {
      return(true);
   }
   else
   {
      return(false);
   }
}

