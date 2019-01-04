//*****************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2005 by DST Systems, Inc.
//
//*****************************************************************************
//
// ^FILE   : MsgSearchCriteria.cpp
// ^CLASS  : MsgSearchCriteria
//
//*****************************************************************************
#include "stdafx.h"
#include "MsgSearchCriteria.hpp"
#include "mgmtco.hpp"
#include "mgmtcooptions.hpp"

#include <ifastdataimpl\dse_dstc0333_req.hpp>

namespace 
{
   const I_CHAR * CLASSNAME = I_("MsgSearchCriteria");
}

namespace CND
{
   extern const long ERR_MISSING_NETWORKID;
   extern const long ERR_MISSING_MSGPROCESSTYPE;
   extern const long ERR_MISSING_STARTDATE;
   extern const long ERR_MISSING_ENDDATE;
   extern const long ERR_MISSING_MSGPROCESSSTATUS;
   extern const long ERR_MISSING_SENDREFNUM;
   extern const long ERR_MISSING_TRANSNUM;
   extern const long ERR_MISSING_AGGRORDNUM;
   extern const long ERR_MISSING_ACTIVITYID;
   extern const long ERR_MISSING_MSGPROCESSCATEGORY;
   extern const long ERR_INVALID_EARLY_END_DATE;   // Existing Condition.
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId CrossEditDates;
   extern CLASS_IMPORT const BFTextFieldId SearchUsing;
   extern CLASS_IMPORT const BFDateFieldId CurrBusDate;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
   //  Field DD Id,        State Flags,       Group Flags 
   { ifds::MsgSearchType,           BFCBO::REQUIRED,  0 }, 
   { ifds::NetworkID,               BFCBO::NONE,  0 }, 
   { ifds::MsgProcessType,          BFCBO::NONE,  0 }, 
   { ifds::StartDate,               BFCBO::NONE,  0 }, 
   { ifds::EndDate,                 BFCBO::NONE,  0 }, 
   { ifds::MsgProcessStatus,        BFCBO::NONE,  0 }, 
   { ifds::SendRefNum,              BFCBO::NONE,  0 }, 
   { ifds::TransNum,                BFCBO::NONE,  0 }, 
	{ ifds::OmnibusID,               BFCBO::NONE,  0 }, 
   { ifds::ActivityID,              BFCBO::NONE,  0 }, 
   { ifds::MsgProcessCategory,      BFCBO::NONE,  0 }, 
   { ifds::SearchUsing,             BFCBO::NONE,  0 },  // generic val
   { ifds::CrossEditDates,          BFCBO::IMMEDIATE_VALIDATION, 0 },

};

static const int NUM_FIELDS = sizeof ( classFieldInfo ) / sizeof ( BFCBO::CLASS_FIELD_INFO );

//******************************************************************************
MsgSearchCriteria::MsgSearchCriteria (BFAbstractCBO &parent) 
: MFCanBFCbo (parent)
{
   TRACE_CONSTRUCTOR ( CLASSNAME , NULL_STRING );
   registerMemberData (NUM_FIELDS,
                      (const CLASS_FIELD_INFO *)&classFieldInfo,
                      0,
                      NULL);

   addCrossEdit( ifds::CrossEditDates, ifds::StartDate );
   addCrossEdit( ifds::CrossEditDates, ifds::EndDate );
}

//******************************************************************************
MsgSearchCriteria::~MsgSearchCriteria()
{
   TRACE_DESTRUCTOR ( CLASSNAME );
}

//******************************************************************************
SEVERITY MsgSearchCriteria::init (
   const DString &MsgSearchType, 
   const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));

   //set the defaults
   setFieldNoValidate (ifds::MsgSearchType, MsgSearchType, idDataGroup, false, true, false);

   // Start Date and End Date should be set to current business date.
   MgmtCoOptions *pMgmtCoOptions = NULL;
	getMgmtCo().getMgmtCoOptions( pMgmtCoOptions );
   DString dstrCurrBusDate;
   if( pMgmtCoOptions )
   {
      pMgmtCoOptions->getField( ifds::CurrBusDate, dstrCurrBusDate, BF::HOST, false );
   }
   dstrCurrBusDate.stripAll();
   setFieldNoValidate(ifds::StartDate, dstrCurrBusDate, idDataGroup, false, true, true);
   setFieldNoValidate(ifds::EndDate,   dstrCurrBusDate, idDataGroup, false, true, true);

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY MsgSearchCriteria::doApplyRelatedChanges (
   const BFFieldId &idField, 
   const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("doApplyRelatedChanges"));
   if( idField == ifds::MsgSearchType )
   {
      DString MsgSearchType;
      getField( ifds::MsgSearchType, MsgSearchType, idDataGroup, false );

      // Set all fields to not required except MsgSearchType
      setFieldRequired( ifds::NetworkID, idDataGroup, false );
      setFieldRequired( ifds::MsgProcessType, idDataGroup, false );
      setFieldRequired( ifds::StartDate, idDataGroup, false );
      setFieldRequired( ifds::EndDate, idDataGroup, false );
      setFieldRequired( ifds::MsgProcessStatus, idDataGroup, false );
      setFieldRequired( ifds::SendRefNum, idDataGroup, false );
      setFieldRequired( ifds::TransNum, idDataGroup, false );
      setFieldRequired( ifds::OmnibusID, idDataGroup, false );
      setFieldRequired( ifds::ActivityID, idDataGroup, false );
      setFieldRequired( ifds::MsgProcessCategory, idDataGroup, false );
      setAllFieldsValid( idDataGroup );

      if( MsgSearchType == I_("TransNum") )
      {
         setFieldRequired( ifds::TransNum, idDataGroup, true );
         setFieldValid( ifds::TransNum, idDataGroup, false );
      }
      else if( MsgSearchType == I_("AggrOrdRefNum") )
      {
         setFieldRequired( ifds::OmnibusID, idDataGroup, true );
         setFieldValid( ifds::OmnibusID, idDataGroup, false );
      }
      else if( MsgSearchType == I_("ActivityID") )
      {
         setFieldRequired( ifds::ActivityID, idDataGroup, true );
         setFieldValid( ifds::ActivityID, idDataGroup, false );
      }
      else if( MsgSearchType == I_("SendersRefNum") )
      {
         setFieldRequired( ifds::SendRefNum, idDataGroup, true );
         setFieldRequired( ifds::NetworkID, idDataGroup, true );
         setFieldValid( ifds::SendRefNum, idDataGroup, false );
         setFieldValid( ifds::NetworkID, idDataGroup, false );
      }
      else if( MsgSearchType == I_("NetworkID") )
      {
         setFieldRequired( ifds::NetworkID, idDataGroup, true );
         setFieldRequired( ifds::StartDate, idDataGroup, true );
         setFieldRequired( ifds::EndDate, idDataGroup, true );
         setFieldValid( ifds::NetworkID, idDataGroup, false );
         setFieldValid( ifds::StartDate, idDataGroup, false );
         setFieldValid( ifds::EndDate, idDataGroup, false );
      }
      else if( MsgSearchType == I_("ProcessType") )
      {
         setFieldRequired( ifds::MsgProcessType, idDataGroup, true );
         setFieldRequired( ifds::StartDate, idDataGroup, true );
         setFieldRequired( ifds::EndDate, idDataGroup, true );
         setFieldValid( ifds::MsgProcessType, idDataGroup, false );
         setFieldValid( ifds::StartDate, idDataGroup, false );
         setFieldValid( ifds::EndDate, idDataGroup, false );
      }
      else if( MsgSearchType == I_("ProcessCategory") )
      {
         setFieldRequired( ifds::MsgProcessCategory, idDataGroup, true );
         setFieldRequired( ifds::StartDate, idDataGroup, true );
         setFieldRequired( ifds::EndDate, idDataGroup, true );
         setFieldValid( ifds::MsgProcessCategory, idDataGroup, false );
         setFieldValid( ifds::StartDate, idDataGroup, false );
         setFieldValid( ifds::EndDate, idDataGroup, false );
      }
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY MsgSearchCriteria::doValidateField (const BFFieldId& idField, 
   const DString& strValue, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateField"));

   if( idField == ifds::SendRefNum )
   {
      if( strValue.empty() )
      {
         ADDCONDITIONFROMFILE( CND::ERR_MISSING_SENDREFNUM );
      }
   }
   else if( idField == ifds::TransNum )
   {
      if( strValue.empty() )
      {
         ADDCONDITIONFROMFILE( CND::ERR_MISSING_TRANSNUM );
      }
   }
   else if( idField == ifds::OmnibusID )
   {
      if( strValue.empty() )
      {
         ADDCONDITIONFROMFILE( CND::ERR_MISSING_AGGRORDNUM );
      }
   }
   else if( idField == ifds::ActivityID )
   {
      if( strValue.empty() )
      {
         ADDCONDITIONFROMFILE( CND::ERR_MISSING_ACTIVITYID );
      }
   }
   else if( idField == ifds::MsgProcessType )
   {
      if( strValue.empty() )
      {
         ADDCONDITIONFROMFILE( CND::ERR_MISSING_MSGPROCESSTYPE );
      }
   }
   else if( idField == ifds::MsgProcessCategory )
   {
      if( strValue.empty() )
      {
         ADDCONDITIONFROMFILE( CND::ERR_MISSING_MSGPROCESSCATEGORY );
      }
   }
   else if( idField == ifds::NetworkID )
   {
      if( strValue.empty() )
      {
         ADDCONDITIONFROMFILE( CND::ERR_MISSING_NETWORKID );
      }
   }
   else if( idField == ifds::MsgProcessStatus )
   {
      if( strValue.empty() )
      {
         ADDCONDITIONFROMFILE( CND::ERR_MISSING_MSGPROCESSSTATUS );
      }
   }
   else if( idField == ifds::StartDate )
   {
      if( strValue.empty() )
      {
         ADDCONDITIONFROMFILE( CND::ERR_MISSING_STARTDATE );
      }
   }
   else if( idField == ifds::EndDate )
   {
      if( strValue.empty() )
      {
         ADDCONDITIONFROMFILE( CND::ERR_MISSING_ENDDATE );
      }
   }
   else if( idField == ifds::CrossEditDates )
   {
      // Compare Start Date and End Date
      // Use ERR CND 1105 if End is < Start.
      DString StartDate, EndDate;
      getField( ifds::StartDate, StartDate, idDataGroup, false );
      getField( ifds::EndDate, EndDate, idDataGroup, false );

      if( DSTCommonFunctions::CompareDates( EndDate, StartDate ) 
          == DSTCommonFunctions::FIRST_EARLIER )
      {
         ADDCONDITIONFROMFILE( CND::ERR_INVALID_EARLY_END_DATE );
      }
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/MsgSearchCriteria.cpp-arc  $
// 
//    Rev 1.2   Mar 16 2005 10:01:06   hernando
// Incident #264500 - Set the default Start Date and End Date to the current business day.
// 
//    Rev 1.1   Feb 22 2005 16:53:14   hernando
// PET1117 FN66-68 - Replaced setFieldValids to setAllFieldValid.
// 
//    Rev 1.0   Feb 21 2005 11:14:24   hernando
// Initial revision.
