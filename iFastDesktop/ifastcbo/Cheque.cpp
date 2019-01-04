//********************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2004 By International Financial Data Services.
//
//
//********************************************************************************
//
// ^FILE   : Cheque.cpp
// ^AUTHOR : 
// ^DATE   : 
//
//********************************************************************************
#include "stdafx.h"
#include "Cheque.hpp"
#include "ChequeDetailsList.hpp"

#include <ifastdataimpl\dse_dstc0021_vwrepeat_record.hpp>

namespace
{
   const I_CHAR * const CLASSNAME            = I_( "Cheque" );
   const I_CHAR * const ASSIGNED_BY_USER     = I_( "User" );

   const I_CHAR * const OUTSTANDING          = I_( "OUT" );
   const I_CHAR * const RECONCILED           = I_( "REC" );
   const I_CHAR * const REPLACED             = I_( "REP" );
   const I_CHAR * const STALED               = I_( "STLD" );
   const I_CHAR * const STOPPED              = I_( "STOP" );
   const I_CHAR * const UNMATCHED            = I_( "UNM" );
   const I_CHAR * const VOIDED               = I_( "VOID" );
   const I_CHAR * const REMITTED             = I_( "RMTD" );
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
   // Field DD Id,            State Flags,      Group Flags 
   { ifds::PrintDate,         BFCBO::NONE,           0 },
   { ifds::StageStampDate,    BFCBO::NONE,           0 },
   { ifds::RemittanceDate,    BFCBO::NONE,	         0 },
   { ifds::ChqStage,          BFCBO::NONE,           0 },
   { ifds::ChqStatus,         BFCBO::NONE,           0 },
   { ifds::ChqComments,       BFCBO::NONE,           0 },
   { ifds::StageAssignBy,     BFCBO::NONE,           0 },
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//******************************************************************************
Cheque::Cheque( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );	
}

//******************************************************************************
Cheque::~Cheque()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//*******************************************************************************
SEVERITY Cheque::init(const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY Cheque::init( const BFData& data )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   DString strChqStatus;
   strChqStatus = data.getElementValue( ifds::ChqStatus );
   strChqStatus.strip().upperCase();
   const_cast<BFData&>(data).setElementValue( ifds::ChqStatus, strChqStatus );

   attachDataObject(const_cast<BFData&>(data), false); 

   DString chequeSubstList = removeItemFromSubtList (ifds::ChqStatus, I_("ALL"), BF::HOST);

   setFieldAllSubstituteValues (ifds::ChqStatus, BF::HOST, chequeSubstList);

   setFieldReadOnly ( ifds::PrintDate, BF::HOST, true );
   setFieldReadOnly ( ifds::StageStampDate, BF::HOST, true );
   //setFieldReadOnly ( ifds::RemittanceDate, BF::HOST, true );
   setFieldReadOnly ( ifds::StageAssignBy, BF::HOST, true );

   getField (ifds::ChqStatus, m_dstrCheque, BF::HOST);
   
   bool bReadOnly =  m_dstrCheque == OUTSTANDING || m_dstrCheque == UNMATCHED || m_dstrCheque == STALED || m_dstrCheque == NULL_STRING ? false : true; 

   setChequeSubstitionList (m_dstrCheque, BF::HOST);

   setFieldReadOnly ( ifds::ChqStatus, BF::HOST, bReadOnly );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY Cheque::doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   MAKEFRAME2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges" ) );

   if (idField == ifds::ChqStage)
   {
      setFieldNoValidate (ifds::StageAssignBy, ASSIGNED_BY_USER, idDataGroup, false);
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//*********************************************************************************
SEVERITY Cheque::setChequeSubstitionList (const DString &dstrCheque, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("setChequeSubstitionList" ));

   if (dstrCheque == OUTSTANDING || dstrCheque == UNMATCHED || dstrCheque == STALED || dstrCheque == NULL_STRING)
   {
      DString chequeSubList = NULL_STRING;

      BFProperties *pBFProperties = getFieldProperties (ifds::ChqStatus, idDataGroup);

      pBFProperties->getAllSubstituteValues (chequeSubList);

      if (dstrCheque == OUTSTANDING || dstrCheque == NULL_STRING)
      {
         chequeSubList = removeItemFromSubtList (chequeSubList, STALED);
		 chequeSubList = removeItemFromSubtList (chequeSubList, REPLACED);
		 chequeSubList = removeItemFromSubtList (chequeSubList, REMITTED);
		 
		 if( dstrCheque == NULL_STRING )
		 {
			 chequeSubList = removeItemFromSubtList (chequeSubList, OUTSTANDING);
			 chequeSubList = I_(" = ;") + chequeSubList;
		 }
      }
      else if (dstrCheque == UNMATCHED)
      {
         chequeSubList = removeItemFromSubtList (chequeSubList, OUTSTANDING);
         chequeSubList = removeItemFromSubtList (chequeSubList, STALED);
		 chequeSubList = removeItemFromSubtList (chequeSubList, REPLACED);
		 chequeSubList = removeItemFromSubtList (chequeSubList, REMITTED);
      }
      else if (dstrCheque == STALED)
      {
         chequeSubList = removeItemFromSubtList (chequeSubList, RECONCILED);
         chequeSubList = removeItemFromSubtList (chequeSubList, REPLACED);
         chequeSubList = removeItemFromSubtList (chequeSubList, UNMATCHED);
		 chequeSubList = removeItemFromSubtList (chequeSubList, REMITTED);
      }

      setFieldAllSubstituteValues (ifds::ChqStatus, idDataGroup, chequeSubList);
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//*********************************************************************************
SEVERITY Cheque::getDetailsList( ChequeDetailsList *&pDetailsList, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("getDetailsList" ));   
   //check cbobase to see if we've already built it
   //otherwise, create and store with base

   pDetailsList = dynamic_cast<ChequeDetailsList*>(getObject( I_( "ChequeDetailsList" ), idDataGroup ) );

   if (!pDetailsList)
   {
      pDetailsList = new ChequeDetailsList (*this);

      if( pDetailsList->init() <= WARNING )
      {
         setObject (pDetailsList, I_("ChequeDetailsList"), OBJ_ACTIVITY_NONE, idDataGroup);
      }
      else
      {
         delete pDetailsList;
         pDetailsList = NULL;
      }
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/Cheque.cpp-arc  $
// 
//    Rev 1.8   Oct 14 2009 10:33:22   yingz
// change for incident 1641175. the remittance date is now not mandatory
// 
//    Rev 1.7   Aug 04 2009 22:05:42   dchatcha
// IN#1746156 - VT0000000022139 - R93- Missing 3 CHQ status in iFAST Desktop.
// 
