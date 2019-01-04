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
// ^FILE   : Confirmation.cpp
// ^AUTHOR : Chin Hsu
// ^DATE   : 11/09/99
//
// ^CLASS    : Confirmation
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "confirmation.hpp"
#include <ifastdataimpl\dse_dstcconf_vw.hpp>

namespace
{
   const I_CHAR * const CLASSNAME = I_( "Confirmation" );
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//  Field DD Id,            State Flags,             Group Flags 
   { ifds::Using_AWD,    BFCBO::NONE, 0 }, 
   { ifds::BusinessArea, BFCBO::NONE, 0 }, 
   { ifds::WorkType,     BFCBO::NONE, 0 }, 
   { ifds::StatusDesc,   BFCBO::NONE, 0 }, 
   { ifds::Batch,        BFCBO::NONE, 0 }, 
   { ifds::Remarks,      BFCBO::NONE, 0 }, 
   { ifds::AWDComment,   BFCBO::NONE, 0 }, 
   { ifds::Option,       BFCBO::NONE, 0 }, 
   { ifds::UpdAllNonFin, BFCBO::NONE, 0 }, 
   { ifds::AWDObjectId,  BFCBO::NONE, 0 }, 
   { ifds::AWDCrda,      BFCBO::NONE, 0 }, 
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//*****************************************************************************
Confirmation::Confirmation( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );

   registerMemberData (NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL);
}

//*****************************************************************************
Confirmation::~Confirmation()
{
   TRACE_DESTRUCTOR (CLASSNAME);
}

//*****************************************************************************
SEVERITY Confirmation::init( const BFData& data )
{
   MAKEFRAME2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ));

   attachDataObject (const_cast<BFData&>(data), false, true);
   setFieldNoValidate ( ifds::UpdAllNonFin, I_("N"), BF::HOST, false);

   return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
SEVERITY Confirmation::init()
{
   MAKEFRAME2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init(int)" ));
   setFieldNoValidate ( ifds::UpdAllNonFin, I_("N"), BF::HOST, false);

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/Confirmation.cpp-arc  $
 * 
 *    Rev 1.11   15 Nov 2007 17:45:06   popescu
 * PET 5636/01 Internal audit tracking
 * 
 *    Rev 1.10   12 Nov 2007 23:44:12   popescu
 * PET 5653/01 - Internal Audit project
 * 
 *    Rev 1.9   02 Nov 2007 17:01:40   popescu
 * Internal Audit Project passed in AWDObjectId to views that have the field
 * 
 *    Rev 1.8   17 Jul 2007 15:18:56   popescu
 * GAP 6 CIF - AIM
 * 
 *    Rev 1.7   Nov 14 2004 14:29:48   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.6   Oct 09 2002 23:54:08   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.5   Aug 29 2002 12:55:12   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.4   22 May 2002 18:26:40   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.3   03 May 2001 14:06:04   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.2   Dec 17 2000 20:22:46   OLTEANCR
 * changed to use a precompiled header
 * 
 *    Rev 1.1   Nov 07 2000 13:21:18   YINGBAOL
 * add init method and fix bug
 * 
 
 */