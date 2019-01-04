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
// ^FILE   : JData.cpp
// ^AUTHOR : Cristina Oltean
// ^DATE   : Jan 2001
//
// ^CLASS    : JData
//
//****************************************************************************
#include <bfutil\RTRevisionDefines.hpp>
RT_SOURCE_REVISION( "$Archive:   //db3n5j11/d/scc/ifds/core/archives/bfcbo/JData.cpp-arc  $", "$Revision:   1.8  $" )

#include "jdata.hpp"
#include <bfdbrkr\bfrequest.hpp>

namespace
{
   //Trace literals
   const I_CHAR* CLASSNAME = I_( "JData" );
}


//*****************************************************************************
JData::JData( const BFRequest &rbfRequest, 
              BFData* pdataRequest, 
              BFData* pdataResponse ) : 
_rbfRequest( rbfRequest ), 
_pdataRequest( NULL ), 
_pdataResponse( NULL ), 
_blCommited( false )
{
   _pdataRequest  = pdataRequest; 
   _pdataResponse = pdataResponse;
}

//*****************************************************************************
JData::JData( DString& dstrTransId, 
              const BFRequest &rbfRequest, 
              BFData *pdataRequest, 
              BFData *pdataResponse ) : 
_rbfRequest( rbfRequest ), 
_pdataRequest( NULL ), 
_pdataResponse( NULL ), 
_blCommited( false )
{
   _pdataRequest  = pdataRequest; 
   _pdataResponse = pdataResponse;
   _dstrTransId   = dstrTransId;
}

//******************************************************************************

JData::~JData()  
{

   if( _pdataRequest )
   {
      delete _pdataRequest;
   }

   if( _pdataResponse )
   {
      delete _pdataResponse;
   }

}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   //db3n5j11/d/scc/ifds/core/archives/bfcbo/JData.cpp-arc  $
// 
//    Rev 1.8   Oct 09 2002 17:40:14   PURDYECH
// New PVCS Database
// 
//    Rev 1.7   22 May 2002 17:54:38   PURDYECH
// BFData Implementation
// 
//    Rev 1.6   03 Jul 2001 16:24:10   SMITHDAV
// Add revision constants.
// 
//    Rev 1.5   03 May 2001 14:26:40   SMITHDAV
// Removed BFBASE_DLL define. 
// 
//    Rev 1.4   Feb 13 2001 15:43:48   MCNABBGL
// added new constructor that shouldn't break anything 
// 
//    Rev 1.3   Feb 13 2001 14:11:40   BUZILAMI
// added PVCS footer
 * 
*/