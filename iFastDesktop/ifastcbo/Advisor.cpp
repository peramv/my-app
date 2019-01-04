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
// ^FILE   : Advisor.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : Advisor
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "advisor.hpp"
#include "advisorlist.hpp"
#include <ifastdataimpl\dse_dstc0092_vw.hpp>

namespace CND
{  // Conditions used
   extern const long ERR_EMAIL_ALREADY_EXIST;
   extern const long ERR_PHONENUM_ALREADY_EXIST;
   extern const long ERR_BROKER_OR_SLSREP_NOT_FOUND;
   extern const long ERR_INVALID_CHAR;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId BrokerCode;
}

namespace  
{
   const I_CHAR * const CLASSNAME      = I_( "Advisor" );
   const I_CHAR * const EMPTY_STR      = I_("");
   const I_CHAR * const PHONE_ALLOWED_CHARS = I_( "0123456789-" );
}
//-------------------------------------------------------------------
const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//  Field DD Id,            State Flags,             Group Flags 
   { ifds::PhoneNumber, BFCBO::NONE, 0 }, 
   { ifds::Email,       BFCBO::NONE, 0 }, 
   { ifds::BrokerCode,  BFCBO::NONE, 0 }, 
   { ifds::BranchCode,  BFCBO::NONE, 0 }, 
   { ifds::Slsrep,      BFCBO::NONE, 0 }, 
   { ifds::SlsRepCntry, BFCBO::NONE, 0 }, 
   { ifds::SlsRepArea,  BFCBO::NONE, 0 }, 
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );
const BFCBO::CLASS_OBJECT_INFO classObjectInfo[] = {
//  Object Label,            State Flags,           Group Flags 
   {  I_(""),        BFCBO::REQUIRED,         0}
};

Advisor::Advisor( BFAbstractCBO &parent ) 
: MFCanBFCbo( parent )
, pAdvisorList_( NULL )
, strEmail( NULL_STRING )
, strPhonenum( NULL_STRING )
{

   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );

   registerMemberData( NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0,
                       (const CLASS_OBJECT_INFO *)0 );
}

//---------------------------------------------------------------------
Advisor::~Advisor()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}     

//---------------------------------------------------------------------  
SEVERITY Advisor::doValidateField( const BFFieldId& idField,
                                   const DString& strValue,
                                   const BFDataGroupId& idDataGroup )

{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateField" ) );

   SEVERITY  svrn = NO_CONDITION;

   if( idField == ifds::Email )
   {
      DString tmp;

      if( strValue != EMPTY_STR )
      {
         //ADDCONDITIONFROMFILE( CND::ALREADY_HAVE_EMAIL );
      }
   }
   if( idField == ifds::PhoneNumber )
   {
      bool rte = true;
      DString allowchars = PHONE_ALLOWED_CHARS;
      for( DString::size_type i = 0; i < strValue.length(); ++i )
         if( allowchars.find( strValue[ i ] ) == -1 )
         {
            rte = false;
            break;
         }
         //if(strValue == NULL_STRING || strValue.strip() == NULL_STRING)
         //rte = false;

      if( !rte )
      {
         ADDCONDITIONFROMFILE( CND::ERR_INVALID_CHAR);
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}


SEVERITY  Advisor::doPreSetField( const BFFieldId& idField, DString & strValue, const BFDataGroupId& idDataGroup, bool bFormatted )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doPreSetField" ) );

   return(GETCURRENTHIGHESTSEVERITY());

}
//--------------------------------------------------------------------
SEVERITY Advisor::init( AdvisorList* advisorList, const BFData& InstData )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   pAdvisorList_ = advisorList;
   attachDataObject(const_cast<BFData&>(InstData), false, true );  

   return(GETCURRENTHIGHESTSEVERITY());
}

SEVERITY Advisor::init( AdvisorList* advisorList, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init(int,long)" ) );
   pAdvisorList_ = advisorList;

   setDefault();

   return(GETCURRENTHIGHESTSEVERITY());
}

SEVERITY Advisor::setDefault()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setDefault" ) );

   return(GETCURRENTHIGHESTSEVERITY());
}
//*******************************************************************

void Advisor::doInitWithDefaultValues( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doPreValidateAll" ) );

   setUpdatedFlag(ifds::PhoneNumber,idDataGroup,true);
   setUpdatedFlag(ifds::Email,idDataGroup,true);
   return;
}

SEVERITY Advisor:: doPreValidateAll( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doPreValidateAll" ) );

   bool havebrokerslsrep = false;
   DString brokercode, branchcode,slsrep;
   getField(ifds::BrokerCode, brokercode, idDataGroup);
   //getField(ifds::BranchCode, branchcode, idDataGroup);
   getField(ifds::Slsrep, slsrep, idDataGroup);
   //loop the parent list check if already have Email or phone number
   BFObjIter iterAdvisorlist( *pAdvisorList_, idDataGroup );
   while( !iterAdvisorlist.end() )
   {
      if( isNew() )
         ++iterAdvisorlist;
      if( !iterAdvisorlist.end() )
      {
         Advisor * pAdvisor = (Advisor *)iterAdvisorlist.getObject();
         DString strBrokerCode,strBranchCode,strSlsrep;
         pAdvisor->getField(ifds::BrokerCode, strBrokerCode, idDataGroup );
         //iterAdvisorlist.getObject( )->getField(ifds::BranchCode, strBranchCode, idDataGroup );
         pAdvisor->getField(ifds::Slsrep, strSlsrep, idDataGroup );
         if( strBrokerCode == brokercode && strSlsrep == slsrep )
         {
            havebrokerslsrep = true;
            pAdvisor->getField(ifds::Email, strEmail, idDataGroup );
            pAdvisor->getField(ifds::PhoneNumber, strPhonenum, idDataGroup );
            break;
         }
      }
   }

   if( !havebrokerslsrep )
   {
      ADDCONDITIONFROMFILE( CND::ERR_BROKER_OR_SLSREP_NOT_FOUND );
   }
   DString iEmail,iPhoneNumber;
   getField(ifds::Email, iEmail, idDataGroup);
   getField(ifds::PhoneNumber, iPhoneNumber, idDataGroup);
   if( iEmail != NULL_STRING )
   {
      setUpdatedFlag(ifds::Email,idDataGroup,true);
   }
   if( iPhoneNumber != NULL_STRING )
   {
      setUpdatedFlag(ifds::PhoneNumber,idDataGroup,true);
   }

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/Advisor.cpp-arc  $
// 
//    Rev 1.16   Nov 17 2004 15:02:12   PURDYECH
// PET910 - .NET Conversion:  Fixed compiler warning messages
// 
//    Rev 1.15   Nov 14 2004 14:25:40   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.14   Mar 21 2003 17:56:40   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.13   Feb 03 2003 16:58:20   FENGYONG
// code clean up
// 
//    Rev 1.12   Oct 09 2002 23:54:00   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.11   Aug 29 2002 12:55:00   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.10   24 May 2002 15:06:38   KOVACSRO
// doPresetField changes.
// 
//    Rev 1.9   22 May 2002 18:26:22   PURDYECH
// BFData Implementation
// 
//    Rev 1.8   Feb 22 2002 13:49:36   FENGYONG
// Add phone validation
// 
//    Rev 1.6   Jan 25 2002 13:15:28   FENGYONG
// setupdate flag
// 
//    Rev 1.5   Jan 17 2002 14:55:06   FENGYONG
// Add condition check key
// 
//    Rev 1.4   Jan 14 2002 16:13:06   FENGYONG
// remove email/phone validation by new ebs
// 
//    Rev 1.3   Jan 11 2002 15:06:16   FENGYONG
// Add validation for brokerCode and slsrepcode
// 
//    Rev 1.2   Jan 07 2002 14:48:42   FENGYONG
// Add cnd 
// 
//    Rev 1.1   Jan 04 2002 17:37:26   FENGYONG
// Add condition 
// 
//    Rev 1.0   Jan 04 2002 10:09:20   FENGYONG
// Initial revision.
 * 
 */