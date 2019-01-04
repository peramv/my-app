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
// ^FILE   : AccountReview.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : AccountReview
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "accountreview.hpp"
#include "AccountReviewList.hpp"
#include <ifastdataimpl\dse_dstc0204_vwrepeat_record.hpp>

namespace
{
   const I_CHAR * const CLASSNAME = I_( "AccountReview" );
}

namespace CND
{
    extern const long ERR_INVALID_DATE;
}
const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//  Field DD Id,            State Flags,             Group Flags 
   { ifds::AcctReviewRId,    BFCBO::NONE,                                    0 }, 
   { ifds::SchedReviewDate,  BFCBO::NONE,                                    0 }, 
   { ifds::ActualReviewDate, BFCBO::NONE,                                    0 }, 
   { ifds::SchedReviewDate,  BFCBO::READ_ONLY,                               0 }, 
   { ifds::ActualReviewDate, BFCBO::IMMEDIATE_VALIDATION | BFCBO::READ_ONLY, 0 }, 
   { ifds::Comments1,        BFCBO::NONE,                                    0 }, 
   { ifds::Comments2,        BFCBO::NONE,                                    0 }, 
   { ifds::Comments3,        BFCBO::NONE,                                    0 }, 
   { ifds::Overriden,        BFCBO::NONE,                                    0 }, 
   { ifds::ProcessDate,      BFCBO::NONE,                                    0 }, 
   { ifds::Username,         BFCBO::NONE,                                    0 }, 
   { ifds::ModDate,          BFCBO::NONE,                                    0 }, 
   { ifds::ModUser,          BFCBO::NONE,                                    0 }, 
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//****************************************************************************
AccountReview::AccountReview( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );

   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );
}

//****************************************************************************

AccountReview::~AccountReview()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//****************************************************************************

SEVERITY AccountReview::init( const BFData& data )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init(const BFData&)" ) );

   attachDataObject( const_cast<BFData&>(data), false, true );
   setFieldReadOnly( ifds::SchedReviewDate, BF::HOST, true );
   setFieldReadOnly( ifds::ActualReviewDate, BF::HOST, true );
   return(GETCURRENTHIGHESTSEVERITY());
}

//****************************************************************************

SEVERITY AccountReview::init( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init(long)" ) );
   setFieldReadOnly( ifds::SchedReviewDate, idDataGroup, true );
   setFieldReadOnly( ifds::ActualReviewDate, idDataGroup, true );
   return(GETCURRENTHIGHESTSEVERITY());
}

//****************************************************************************

SEVERITY AccountReview::doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateField" ) );

   if( idField == ifds::ActualReviewDate )
   {
      checkActualReviewDate(strValue, idDataGroup);

   }
   else if( idField == ifds::SchedReviewDate )
   {
      AccountReviewList *pAccountReviewList = (AccountReviewList *) getParent();
      pAccountReviewList->validateScheduledReviewDate( strValue, idDataGroup );
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//****************************************************************************

SEVERITY AccountReview::checkActualReviewDate(const DString& dstrActualReviewDate, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "checkActualReviewDate" ) );

   if ( dstrActualReviewDate.find( I_("9999") ) != DString::npos )
   {
      ADDCONDITIONFROMFILE( CND::ERR_INVALID_DATE );
      return(GETCURRENTHIGHESTSEVERITY());
   }
      ;
   AccountReviewList *pAccountReviewList = (AccountReviewList *) getParent();
   pAccountReviewList->validateActualReviewDate( this, dstrActualReviewDate, idDataGroup );

   return(GETCURRENTHIGHESTSEVERITY());
}
//****************************************************************************

SEVERITY AccountReview::doApplyRelatedChanges(const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges" ) );

   if( idField == ifds::ActualReviewDate )
   {
      AccountReviewList *pAccountReviewList = (AccountReviewList *) getParent();
      pAccountReviewList->applyScheduleReviewDateChange( this, idField, idDataGroup );
      pAccountReviewList->setReadOnlyFieldsBasedOnRules( idDataGroup );
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AccountReview.cpp-arc  $
// 
//    Rev 1.8   Mar 18 2005 11:42:46   aguilaam
// IN_234826: additional fix/ clean-up for account review screen
// 
//    Rev 1.7   Mar 17 2005 11:59:30   aguilaam
// IN_234826 : year of 9999 is invalid actual review date
// 
//    Rev 1.6   Nov 14 2004 14:24:46   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.5   Mar 21 2003 17:55:04   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.4   Oct 09 2002 23:53:54   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.3   Aug 29 2002 12:54:54   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.2   31 May 2002 14:05:30   HERNANDO
// Revised for Rel47.
// 
//    Rev 1.1   22 May 2002 18:26:14   PURDYECH
// BFData Implementation
// 
//    Rev 1.0   08 May 2002 18:58:40   HERNANDO
// Initial revision.
 * 
 */