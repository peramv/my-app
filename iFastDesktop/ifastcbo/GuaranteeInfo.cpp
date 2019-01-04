//*****************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2005 by International Financial Data Services
//
//*****************************************************************************
//
// ^FILE   : GuaranteeInfo.cpp
// ^AUTHOR : Celia Zhang
// ^DATE   : 09/03/2000
//
// ^CLASS    : GuaranteeInfo
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "guaranteeinfo.hpp"
#include "guaranteedetaillist.hpp"
#include <ifastdataimpl\dse_dstc0106_vw.hpp>

namespace
{
   const I_CHAR * const CLASSNAME = I_( "GuaranteeInfo" );
}

//****************************************************************************
GuaranteeInfo::GuaranteeInfo( BFAbstractCBO &parent ) :
MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
}

//****************************************************************************
GuaranteeInfo::~GuaranteeInfo()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//****************************************************************************
SEVERITY GuaranteeInfo::init( const BFData& data )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   attachDataObject( const_cast<BFData&>(data), false, true );
   return(GETCURRENTHIGHESTSEVERITY());
}

//****************************************************************************
SEVERITY GuaranteeInfo::getGuaranteeDetailList( const BFDataGroupId& idDataGroup,
											               GuaranteeDetailList *&pGuaranteeDetailList,												 
                                                const DString& dstrTrack,
                                                const DString& dstrPageName )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getGuaranteeDetailList" ) );
   
   pGuaranteeDetailList = NULL;
   DString dstrGuarRecId;
   getField( ifds::GuarRecId, dstrGuarRecId, idDataGroup );

   DString dstrkey = I_("GuaranteeDetailList") + dstrGuarRecId;
   BFObjectKey objKey( dstrkey, idDataGroup, OBJ_ACTIVITY_NONE, I_( "pGuaranteeDetailList" ) );
   pGuaranteeDetailList = dynamic_cast<GuaranteeDetailList*>( findObject( objKey ) );

   if( !pGuaranteeDetailList )
   {
      pGuaranteeDetailList = new GuaranteeDetailList( *this );

      if( pGuaranteeDetailList->init (idDataGroup, dstrGuarRecId, dstrTrack, dstrPageName) <= WARNING)
      {
         setObject( objKey, pGuaranteeDetailList );   
      }
      else
      {         
         delete pGuaranteeDetailList;
         pGuaranteeDetailList = NULL;
      }
   }   
   return GETCURRENTHIGHESTSEVERITY();
}

//***************************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/GuaranteeInfo.cpp-arc  $
// 
//    Rev 1.1   Jun 29 2006 17:21:34   popescu
// Incident# 655992 - restricted the call to view 351 - GuaranteeInfoDetail to only certain trans types.
// 
//    Rev 1.0   Aug 17 2005 16:17:48   porteanm
// Initial revision.
 * 
 *    Rev 1.11   Nov 14 2004 14:43:50   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.10   Oct 09 2002 23:54:36   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.9   Aug 29 2002 12:56:00   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.8   22 May 2002 18:28:50   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.7   Jul 29 2001 12:57:16   OLTEANCR
 * added PolicyTerm
 * 
 *    Rev 1.6   Jul 16 2001 19:18:24   OLTEANCR
 * added two new fields
 * 
 *    Rev 1.5   11 May 2001 12:54:22   HSUCHIN
 * Session management restructuring
 * 
 *    Rev 1.4   May 11 2001 11:55:14   OLTEANCR
 * unchanged
 * 
 *    Rev 1.3   Jan 10 2001 17:28:58   ZHANGCEL
 * Added the $Log
 * 
 */
