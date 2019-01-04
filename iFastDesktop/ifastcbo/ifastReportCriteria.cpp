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
#include "grouplist.hpp"
#include "mgmtco.hpp"
#include "mgmtcooptions.hpp"
#include "brokerlist.hpp"

namespace
{
   const I_CHAR * const CLASSNAME = I_( "ifastReportCriteria" );
   const I_CHAR * const BLANK_SUBSTITUTION = I_( " = ;");    // substitution with only one element with tag = value = " " 
   const I_CHAR * const REPEAT = I_( "R" );
   const I_CHAR * const YES = I_( "Y" );
   const I_CHAR * const ALL = I_( "@" );
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
   extern CLASS_IMPORT const BFNumericFieldId AccountNum;
   extern CLASS_IMPORT const BFTextFieldId IncludeExclude;
   extern CLASS_IMPORT const BFTextFieldId rxGroupCode;
}

namespace CND
{
   extern const long ERR_INVALID_GROUP_CODE;
   extern const long ERR_BROKER_EMPTY;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
//  Field DD Id,					State Flags,	Group Flags 
   { ifds::CriteriaType,          BFCBO::REQUIRED, 0 },  
   { ifds::GroupCode,          BFCBO::NONE, 0 },  
   { ifds::Description,          BFCBO::NONE, 0 },  
   { ifds::BrokerCode,          BFCBO::NONE, 0 },  
   { ifds::RecordType,          BFCBO::NONE, 0 },  
   { ifds::IncludeExclude,          BFCBO::NONE, 0 },  
   { ifds::AccountNum,          BFCBO::NONE, 0 }
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );
//*****************************************************************************
// Constructor
//*****************************************************************************

ifastReportCriteria::ifastReportCriteria( BFAbstractCBO &parent )
:  oldCriteriaType ( NULL_STRING ),
   MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );   
   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );
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
// @param   const BFDataGroupId& idDataGroup - current data group id.
//*****************************************************************************
void ifastReportCriteria::clearFields( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "clearFields" ) );
   CLEARCONDITIONS();
   DString dstrCriteriaType, dstrOrigValue;
   getField ( ifds::CriteriaType, dstrCriteriaType, idDataGroup );
   // If the criteria type haven't changed do not clear fields
   if ( oldCriteriaType != dstrCriteriaType ) {      
      if ( oldCriteriaType != NULL_STRING ) {
         const BFFieldId& fieldId = BFFieldId::getId ( oldCriteriaType );
         getField ( fieldId, dstrOrigValue, BF::HOST );
         setFieldNoValidate ( fieldId, dstrOrigValue, idDataGroup, true, true, true, false );       
         setValidFlag ( fieldId, idDataGroup, true );      
         setFieldRequired ( fieldId, idDataGroup, false );      
         oldCriteriaType = dstrCriteriaType;
      } else {
         // store the new critiera.
         oldCriteriaType = dstrCriteriaType;
      }
      const BFFieldId& fieldId = BFFieldId::getId ( dstrCriteriaType );
      setFieldRequired ( fieldId, idDataGroup, true );
      setValidFlag ( fieldId, idDataGroup, false );
      setFieldNoValidate ( ifds::Description, NULL_STRING, idDataGroup, true, true, true, false );
   }
}

//*****************************************************************************
// This method will check to see if the group code passed in can be found in
// the group list cbo.  If the group code exists in the group list cbo, the 
// group name will be extract and set to the field Description, otherwise 
// NULL_STRING.
// @param   const DString& dstrGroupCode - group code to validate.
//          const BFDataGroupId& idDataGroup - current data group id.
// @returns SEVERITY. "Invalid Group Code."
//*****************************************************************************
SEVERITY ifastReportCriteria::validateGroupCode( const DString& dstrGroupCode, const BFDataGroupId& idDataGroup )
{    
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateGroupCode" ) );
   if ( dstrGroupCode == ALL ) {
      setFieldNoValidate( ifds::Description, NULL_STRING, idDataGroup, true, true, true, false );
      return GETCURRENTHIGHESTSEVERITY();
   }

   GroupList* pGroupList = NULL;
   DString dstrGroupName;
   if( getMgmtCo().getGroupList( pGroupList ) <= WARNING ) {
      BFObjIter iter( *pGroupList, idDataGroup );
      for( iter.begin(); !iter.end(); ++iter ) {
         DString iterGroupCode;
         iter.getObject()->getField( ifds::rxGroupCode, iterGroupCode, idDataGroup );
         if( dstrGroupCode == iterGroupCode ) {
            iter.getObject()->getField( ifds::GroupName, dstrGroupName, idDataGroup );
            setFieldNoValidate( ifds::Description, dstrGroupName, idDataGroup, true, true, true, false );
            return GETCURRENTHIGHESTSEVERITY();
         }
      }
      // "Invalid group code."
      ADDCONDITIONFROMFILE ( CND::ERR_INVALID_GROUP_CODE );
   }
   setFieldNoValidate( ifds::Description, NULL_STRING, idDataGroup, true, true, true, false );
   return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************
// Validates the broker code passed in by creating a broker list cbo with
// the broker passed in.   If the init of the broker list cbo failed, then
// the SEVERITY returned is passed back.  If the broker code is valid, then
// the Description field will be set to the broker name, otherwise NULL_STRING.
// @param   const DString& dstrBrokerCode - broker code to check
//          const BFDataGroupId& idDataGroup - current data group id.
//*****************************************************************************
SEVERITY ifastReportCriteria::validateBrokerCode( const DString& dstrBrokerCode, const BFDataGroupId& idDataGroup )
{

   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateBrokerCode" ) );

   DString dstrCriteriaType;
   getField ( ifds::CriteriaType, dstrCriteriaType, idDataGroup );
   const BFFieldId& fieldId = BFFieldId::getId ( dstrCriteriaType );
   if (( fieldId == ifds::BrokerCode ) && ( dstrBrokerCode == NULL_STRING )) {
      //"Broker cannot be blank."
      ADDCONDITIONFROMFILE ( CND::ERR_BROKER_EMPTY );
   }
   BrokerList brokerList ( *this );

   if( dstrBrokerCode != NULL_STRING && 
       brokerList.init( dstrBrokerCode, NULL_STRING, I_( "L" ) ) <= WARNING )
   {
      BFObjIter bfIter( brokerList, idDataGroup );
      DString dstrBrokerName;
      bfIter.begin();
      if( !bfIter.end() )
      {         
         bfIter.getObject()->getField( ifds::BrokerName, dstrBrokerName, idDataGroup );
         setFieldNoValidate ( ifds::Description, dstrBrokerName, idDataGroup, true, true, true, false ); 
      }
   }
   else
   {
      setFieldNoValidate ( ifds::Description, NULL_STRING, idDataGroup, true, true, true, false ); 
   }
   
   return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************
// This method will return the current business date unless the dervied class
// overrides doGetReportDate to return the date of the report.  This is 
// mainly used for checks such as status of broker whether the broker is active
// or inactive.
// @param   const BFDataGroupId& idDataGroup - current data group.
// @returns DString - Current business Date or date returned by derveried class.
//*****************************************************************************
DString ifastReportCriteria::getReportDate( const BFDataGroupId& idDataGroup )
{
   DString dstrReportDate;
   //If the dervied class did not override doGetReportDate then
   //Current business date is used.
   dstrReportDate = doGetReportDate ( idDataGroup );
   if ( dstrReportDate == NULL_STRING ) {
      getWorkSession().getMgmtCoOptions()->getField( ifds::CurrBusDate, dstrReportDate, idDataGroup, false );      
   }
   return dstrReportDate;
}

//*****************************************************************************
// doValidateFields will validate the BrokerCode and GroupCode.  It will call
// the helper methods validateGroupCode and validateBrokerCode to do the
// validation.
// @param   const BFFieldId& idField - current field id validated.
//          const DString& strValue - value associated to field id.
//          const BFDataGroupId& idDataGroup - current group id.
//*****************************************************************************
SEVERITY ifastReportCriteria::doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateFields" ) );
   if ( idField == ifds::BrokerCode ) {
      validateBrokerCode ( strValue, idDataGroup );
   } else if ( idField == ifds::GroupCode ) {
      validateGroupCode ( strValue, idDataGroup );
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************
// The base doApplyRelatedChanges will call clearFields to clear out the 
// Criteria value field whent the criteria type changes.
// @param   const BFFieldId& idField - current field id changed.
//          const BFDataGroupId& idDataGroup - current data group id.
// @returns SEVERITY - NO_CONDITION in general.
//*****************************************************************************
SEVERITY ifastReportCriteria::doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges" ) );
   if ( idField == ifds::CriteriaType ) {
      clearFields( idDataGroup );      
      setupSubList ( idDataGroup );
   } 
   return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************
//*****************************************************************************
SEVERITY ifastReportCriteria::setupSubList( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setupSubList" ) );
   DString dstrCriteriaType, dstrSubList;
   getField ( ifds::CriteriaType, dstrCriteriaType, idDataGroup );
   const BFFieldId& fieldId = BFFieldId::getId ( dstrCriteriaType );
   if ( fieldId == ifds::GroupCode ) {
      GroupList* pGroupList = NULL;            
      if( getMgmtCo().getGroupList( pGroupList ) <= WARNING ) {
         pGroupList->getGroupSubstList ( dstrSubList,true );
         if ( dstrSubList != NULL_STRING ) {
            // Add All as an Option.
            dstrSubList = I_("@=All;") + dstrSubList;
            setFieldAllSubstituteValues( fieldId, idDataGroup, dstrSubList ); 
         }
         else { //Severity
            setFieldAllSubstituteValues( fieldId, idDataGroup, BLANK_SUBSTITUTION ); 
         }
      }
   }         
   return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************
// This method will take a list object, the of a field and convert it to a
// substitution set.
// @param   const BFCBO*& pBFCBO - Cbo list.
//          BFField& idField - Field to convert into a sub list.
//          DString& dstrSubList - Substitution list returned.
//          const BFDataGroupId& idDataGroup - current data group id.
// @returns void.   Substitution list or NULL_STRING stored in dstrSubList.
//*****************************************************************************
void ifastReportCriteria::createSubList( BFCBO* pBFCBO, BFFieldId idField, DString& dstrSubList, const BFDataGroupId& idDataGroup )
{
   dstrSubList = NULL_STRING;

   DString dstrSubValue;
   BFObjIter iter( *pBFCBO, BF::HOST, true );
   iter.begin();

   while( !iter.end() )
   {
      iter.getObject()->getField( idField, dstrSubValue, idDataGroup );
      dstrSubValue.strip().upperCase();
      dstrSubList += dstrSubValue ;
      dstrSubList += I_(",");
      ++iter;
   }

   //delete the last ","
   if( !dstrSubList.empty() )
      dstrSubList.erase( dstrSubList.length() - 1, 1 );
}

//*****************************************************************************
//*****************************************************************************
void ifastReportCriteria::doInitWithDefaultValues( const BFDataGroupId& idDataGroup )
{
   setFieldNoValidate ( ifds::RecordType, REPEAT, idDataGroup, true, true, true, false );   
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/ifastReportCriteria.cpp-arc  $
// 
//    Rev 1.4   Nov 14 2004 14:48:28   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.3   Mar 21 2003 18:16:00   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.2   Dec 08 2002 21:52:54   HSUCHIN
// bug fix to clear out Description
// 
//    Rev 1.1   Nov 29 2002 13:14:50   HSUCHIN
// buf fix for All and clearFields
// 
//    Rev 1.0   Nov 27 2002 11:39:10   HSUCHIN
// Initial Revision
*/
