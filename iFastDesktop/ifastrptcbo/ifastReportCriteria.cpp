//*****************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2002 by International Financial, Inc.
//
//*****************************************************************************
//
// ^FILE   : ifastReportCriteria.cpp
// ^AUTHOR : 
// ^DATE   : Nov 15, 2002
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : ifastReportCriteria
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************

#include "stdafx.h"
#include "ifastreportcriteria.hpp"
#include <ifastcbo\grouplist.hpp>
#include <ifastcbo\mgmtco.hpp>
#include <ifastcbo\mgmtcooptions.hpp>
#include <ifastcbo\brokerlist.hpp>

namespace
{
   const I_CHAR * const CLASSNAME = I_( "ifastReportCriteria" );
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId CriteriaType;
   extern CLASS_IMPORT const BFTextFieldId rxGroupCode;
   extern CLASS_IMPORT const BFTextFieldId GroupName;
   extern CLASS_IMPORT const BFTextFieldId Description;
   extern CLASS_IMPORT const BFTextFieldId BrokerName;
   extern CLASS_IMPORT const BFTextFieldId BrokerCode;
   extern CLASS_IMPORT const BFTextFieldId GroupCode;
   extern CLASS_IMPORT const BFDateFieldId StopDate;
   extern CLASS_IMPORT const BFDateFieldId CurrBusDate;
   extern CLASS_IMPORT const BFTextFieldId RecordType;
}

//*****************************************************************************
// Constructor
//*****************************************************************************

ifastReportCriteria::ifastReportCriteria( BFAbstractCBO &parent )
:  oldCriteriaType ( NULL_STRING ),
   MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );      
}

//*****************************************************************************
// Destructor
//*****************************************************************************

ifastReportCriteria::~ifastReportCriteria()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//*****************************************************************************
// This method will clear the criteria value field when the criteria type has
// changed to a new criteria type.
// @param   long lDataGroupId - current data group id.
//*****************************************************************************
void ifastReportCriteria::clearFields( long lDataGroupId )
{
   DString dstrCriteriaType, dstrOrigValue;
   getField ( ifds::CriteriaType, dstrCriteriaType, lDataGroupId );
   // If the criteria type haven't changed do not clear fields
   if ( oldCriteriaType != dstrCriteriaType ) {      
      // store the new critiera.
      oldCriteriaType = dstrCriteriaType;
      BFFieldId fieldId = BFFieldId::getId ( dstrCriteriaType );
      getField ( fieldId, dstrOrigValue, BF::HOST );
      setFieldNoValidate ( fieldId, dstrOrigValue, lDataGroupId, true, true, true, false ); 
   }
}

//*****************************************************************************
// This method will check to see if the group code passed in can be found in
// the group list cbo.  If the group code exists in the group list cbo, the 
// group name will be extract and set to the field Description, otherwise 
// NULL_STRING.
// @param   const DString& dstrGroupCode - group code to validate.
//          long lDataGroupId - current data group id.
// @returns SEVERITY. "Invalid Group Code."
//*****************************************************************************
SEVERITY ifastReportCriteria::validateGroupCode( const DString& dstrGroupCode, long lDataGroupId )
{    
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateGroupCode" ) );
   GroupList* pGroupList = NULL;
   DString dstrGroupName;
   if( getMgmtCo().getGroupList( pGroupList ) <= WARNING ) {
      BFObjIter iter( *pGroupList, lDataGroupId );
      for( iter.begin(); !iter.end(); ++iter ) {
         DString iterGroupCode;
         iter.getObject()->getField( ifds::rxGroupCode, iterGroupCode, lDataGroupId );
         if( dstrGroupCode == iterGroupCode ) {
            iter.getObject()->getField( ifds::GroupName, dstrGroupName, lDataGroupId );
            setFieldNoValidate( ifds::Description, dstrGroupName, lDataGroupId, true, true, true, false );
         } else {
            // Raise condition.. invalid group code.
         }
      }
   } else {
      setFieldNoValidate( ifds::Description, dstrGroupName, lDataGroupId, true, true, true, false );
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************
// Validates the broker code passed in by creating a broker list cbo with
// the broker passed in.   If the init of the broker list cbo failed, then
// the SEVERITY returned is passed back.  If the broker code is valid, then
// the Description field will be set to the broker name, otherwise NULL_STRING.
// @param   const DString& dstrBrokerCode - broker code to check
//          long lDataGroupId - current data group id.
//*****************************************************************************
SEVERITY ifastReportCriteria::validateBrokerCode( const DString& dstrBrokerCode, long lDataGroupId )
{

   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateBrokerCode" ) );

   BrokerList brokerList ( *this );

   if( dstrBrokerCode != NULL_STRING && 
       brokerList.init( dstrBrokerCode, NULL_STRING, I_( "L" ) ) <= WARNING )
   {
      BFObjIter bfIter( brokerList, lDataGroupId );
      DString dstrBrokerName;
      bfIter.begin();
      if( !bfIter.end() )
      {
         //Is this business rule necessary??
         DString dstrStopDate, dstrReportDate;
         bfIter.getObject()->getField ( ifds::StopDate, dstrStopDate, lDataGroupId, false );         
         dstrReportDate = getReportDate ( lDataGroupId );
         if ( DSTCommonFunctions::CompareDates( dstrStopDate, dstrReportDate )
            == DSTCommonFunctions::FIRST_EARLIER ) {
            //Condition - "Broker inactive as of start date for Report."
         }
         bfIter.getObject()->getField( ifds::BrokerName, dstrBrokerName, lDataGroupId );
         setFieldNoValidate ( ifds::Description, dstrBrokerName, lDataGroupId, true, true, true, false ); 
      }
   }
   else
   {
      setFieldNoValidate ( ifds::Description, NULL_STRING, lDataGroupId, true, true, true, false ); 
   }
   
   return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************
// This method will return the current business date unless the dervied class
// overrides doGetReportDate to return the date of the report.  This is 
// mainly used for checks such as status of broker whether the broker is active
// or inactive.
// @param   long lDataGroupId - current data group.
// @returns DString - Current business Date or date returned by derveried class.
//*****************************************************************************
DString ifastReportCriteria::getReportDate( long lDataGroupId )
{
   DString dstrReportDate;
   //If the dervied class did not override doGetReportDate then
   //Current business date is used.
   dstrReportDate = doGetReportDate ( lDataGroupId );
   if ( dstrReportDate == NULL_STRING ) {
      getWorkSession().getMgmtCoOptions()->getField( ifds::CurrBusDate, dstrReportDate, lDataGroupId, false );      
   }
   return dstrReportDate;
}

//*****************************************************************************
// doValidateFields will validate the BrokerCode and GroupCode.  It will call
// the helper methods validateGroupCode and validateBrokerCode to do the
// validation.
// @param   const BFFieldId& idField - current field id validated.
//          const DString& strValue - value associated to field id.
//          long lDataGroupId - current group id.
//*****************************************************************************
SEVERITY ifastReportCriteria::doValidateFields( const BFFieldId &idField, const DString& strValue, long  lDataGroupId )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateFields" ) );
   if ( idField == ifds::BrokerCode ) {
      validateBrokerCode ( strValue, lDataGroupId );
   } else if ( idField == ifds::GroupCode ) {
      validateGroupCode ( strValue, lDataGroupId );
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************
// The base doApplyRelatedChanges will call clearFields to clear out the 
// Criteria value field whent the criteria type changes.
// @param   const BFFieldId &idField - current field id changed.
//          long lDataGroupId - current data group id.
// @returns SEVERITY - NO_CONDITION in general.
//*****************************************************************************
SEVERITY ifastReportCriteria::doApplyRelatedChanges( const BFFieldId &idField, long lDataGroupId )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges" ) );
   if ( idField == ifds::CriteriaType ) {
      clearFields( lDataGroupId );
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************
// When the ReportType is F, it means the criteria is a required criteria. 
// All required criterias cannot be deleted.
// @param   long lDataGroupId - current data group.
// @returns bool - true when the criteria is not required and false otherwise
//*****************************************************************************
bool ifastReportCriteria::canDeleteObject( long lDataGroupId )
{
   DString dstrRecordType;
   getField ( ifds::RecordType, dstrRecordType, lDataGroupId );
   return  ( dstrRecordType == I_("R") );
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastrptcbo/ifastReportCriteria.cpp-arc  $
// 
//    Rev 1.0   Nov 19 2002 11:28:16   HSUCHIN
// Initial Revision
*/
