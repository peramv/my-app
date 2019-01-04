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
// ^FILE   : ifastReportCriteriaList.cpp
// ^AUTHOR : 
// ^DATE   : Nov 14, 2002
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : ifastReportCriteriaList
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************

#include "stdafx.h"
#include "ifastreportcriteria.hpp"
#include "ifastreportcriterialist.hpp"

namespace
{
   const I_CHAR * const CLASSNAME = I_( "ifastReportCriteriaList" );
   const I_CHAR * const ALL = I_( "@" );
   const I_CHAR * const NO = I_( "N" );
   const I_CHAR * const YES = I_( "Y" );      
   const I_CHAR * const REPEAT = I_( "R" );
   const int MAX_CRITERIA = 40;
}

namespace CND
{
   //extern CLASS_IMPORT const long ERR_INVALID_TIME;
   extern const long ERR_CRITERIA_LIMIT_EXCEEDED;
   extern const long ERR_CRITERIA_EXCEED_LIMIT;
   extern const long ERR_DUPLICATE_CRITERIA_VALUE;
   extern const long ERR_CRITERIA_EXCEED_LIMIT;
   extern const long ERR_CRITERIA_ALL_SELECTED;
   extern const long ERR_CANNOT_DELETE_FIXED_RECORD;
   extern const long ERR_CANNOT_EXCLUDE_ALL;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId CriteriaType;
   extern CLASS_IMPORT const BFTextFieldId IncludeExclude;
   extern CLASS_IMPORT const BFTextFieldId RecordType;
}

//*****************************************************************************
// Constructor
//*****************************************************************************

ifastReportCriteriaList::ifastReportCriteriaList( BFAbstractCBO &parent )
:  MFCanBFCbo( parent ),
_pAMSHypoAllocList( NULL )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );   
   setObjectAsList();
}

//*****************************************************************************
// Destructor
//*****************************************************************************

ifastReportCriteriaList::~ifastReportCriteriaList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//*****************************************************************************
// Validates all the ifastReportCriteria stored in the list.  Ensures there is no 
// duplicate CriteriaType+Value.  If one of the criteria is with the value all.  
// Additional include of it will result in an error.  Criteria with all + same 
// critieria with exlclude is accepted except exclude all.  Include and Exclude 
// criteria with same value will also result in error.
// @param const BFDataGroupId& idDataGroup - Current Data Group Id.
// @param long lValidateGroup - Current Validation Group.
// @returns SEVERITY - "Duplicate rebalancing criteria %CRITERIATYPE% - %CRITERIAVALUE%."
//                     "%CRITERIATYPE% has all selected. Cannot Include more of the same criteria."
//*****************************************************************************
SEVERITY ifastReportCriteriaList::doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );   
   std::map < DString, unsigned int > mapNumCriteriaType;
   std::map < DString, DString > mapCriteriaTypeDesc;
   std::map < DString, unsigned int >::iterator mapiter;
   std::map < DString, unsigned int >::iterator mapiter2;
   std::set < DString > dupCriteriaValueSet;
   std::set < DString > cannotIncludeSet;
   BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
   DString dstr, dstrCriteriaType, dstrCriteriaValue, dstrCriteriaTypeDesc;   
   BFFieldId curFieldId;
   int iNumCriterias = 0;
   while( !iter.end() )
   {  
      ++iNumCriterias;      
      iter.getObject()->getField ( ifds::CriteriaType, dstrCriteriaType, idDataGroup );
      if ( iter.isDummy() ) {
         ++iter;
         continue;
      }
	  if ( dstrCriteriaType == I_("GlobalLevelRebal") || dstrCriteriaType == I_("AccountLevelRebal") || dstrCriteriaType == NULL_STRING)
	  {
		++iter;
		continue;
	  }
      iter.getObject()->getField ( ifds::CriteriaType, dstrCriteriaTypeDesc, idDataGroup, true );

      // Store Description for error display.
      mapCriteriaTypeDesc.insert ( std::make_pair ( dstrCriteriaType, dstrCriteriaTypeDesc ));

      curFieldId = BFFieldId::getId ( dstrCriteriaType );
      iter.getObject()->getField ( curFieldId, dstrCriteriaValue, idDataGroup );
      mapiter = mapNumCriteriaType.find ( dstrCriteriaType );
      // If it is not in map, add it to the map
      if ( mapiter == mapNumCriteriaType.end()  ) {
         mapNumCriteriaType.insert ( std::make_pair ( dstrCriteriaType, 1 ) );
	mapiter->second = 1;
      } else {
         mapiter->second = ++mapiter->second;
      }
      dstr = dstrCriteriaType + dstrCriteriaValue;
      if( !dupCriteriaValueSet.insert(dstr).second )
      {
         //"Duplicate criteria (%CRITERIA%) with value (%VALUE%)."
         DString error;
         addIDITagValue( error, I_("CRITERIA"), dstrCriteriaTypeDesc );
         //format the description
         iter.getObject()->getField ( curFieldId, dstrCriteriaValue, idDataGroup, true );
         addIDITagValue( error, I_("VALUE"), dstrCriteriaValue);
         ADDCONDITIONFROMFILEIDI ( CND::ERR_DUPLICATE_CRITERIA_VALUE, error );         
         return(GETCURRENTHIGHESTSEVERITY());
      }

      // If the CriteriaValue is All for Criteria Type
      // We will inserted into a set 
      DString dstrInclude;
      if ( dstrCriteriaValue == ALL ) {
         cannotIncludeSet.insert ( dstrCriteriaType );
         iter.getObject()->getField ( ifds::IncludeExclude, dstrInclude, idDataGroup );
         if ( dstrInclude == NO ) {
            DString error;
            addIDITagValue( error, I_("CRITERIA"), dstrCriteriaTypeDesc );            
            ADDCONDITIONFROMFILEIDI ( CND::ERR_CANNOT_EXCLUDE_ALL, error );
            return(GETCURRENTHIGHESTSEVERITY());
         }
         if ( mapiter->second && mapiter->second > 1 ) {
            DString error;
            addIDITagValue( error, I_("CRITERIA"), dstrCriteriaTypeDesc );            
            ADDCONDITIONFROMFILEIDI ( CND::ERR_CRITERIA_ALL_SELECTED, error );
            return(GETCURRENTHIGHESTSEVERITY());
         }
      } else {
         iter.getObject()->getField ( ifds::IncludeExclude, dstrInclude, idDataGroup );
         if (( dstrInclude == YES ) && ( cannotIncludeSet.find( dstrCriteriaType ) != cannotIncludeSet.end())) {
            //"Criteria (%CRITERIA%) has All selected. Cannot Include more of the same type."
            DString error;
            addIDITagValue( error, I_("CRITERIA"), dstrCriteriaTypeDesc );            
            ADDCONDITIONFROMFILEIDI ( CND::ERR_CRITERIA_ALL_SELECTED, error );
            return(GETCURRENTHIGHESTSEVERITY());
         }
      }
      ++iter;
   }   
   if ( iNumCriterias > MAX_CRITERIA ) {
      //"The number of criterias entered exceed maximum limit."
      ADDCONDITIONFROMFILE ( CND::ERR_CRITERIA_EXCEED_LIMIT );
      return(GETCURRENTHIGHESTSEVERITY());
   }

   mapiter = mapNumCriteriaType.begin();
   while ( mapiter != mapNumCriteriaType.end() ) {
      if ( !withinCardinality ( mapiter->first, mapiter->second ) ) {
         std::map < DString, MinMax >::iterator carditer = _mapfieldCardinality.find ( mapiter->first );
         if ( carditer == _mapfieldCardinality.end() )
            //All critiera type cardinality must be defined in dervied class.
            assert (0); 
         unsigned int  max = 0;        
         max = carditer->second.max;
         std::map < DString, DString >::iterator desciter = mapCriteriaTypeDesc.find ( mapiter->first );
         //"The criteria  %CRITERIA% cannot occured more than %MAX% times."
         DString error;
         addIDITagValue( error, I_("CRITERIA"), desciter->second );
         addIDITagValue( error, I_("MAX"), DString::asString( max ));
         ADDCONDITIONFROMFILEIDI ( CND::ERR_CRITERIA_LIMIT_EXCEEDED, error );
         return(GETCURRENTHIGHESTSEVERITY());
      }
      ++mapiter;
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//*****************************************************************************
// Set up the cardinality map for the fields.
// @param   DString dstrCriteriaType - Criteria Type.
//          int min - Minimum occurance of this Criteria Type.
//          int max - Maxmimu occurance of this Criteria Type.
//*****************************************************************************
void ifastReportCriteriaList::addFieldCardinality ( DString& dstrCriteriaType, unsigned int imin, unsigned int imax )
{
   MinMax mm;
   mm.min = imin;
   mm.max = imax;
   // Insert Criteria into field cardinality map.
   _mapfieldCardinality.insert ( std::make_pair ( dstrCriteriaType, mm ) );
}

//*****************************************************************************
// Checks the Cardinality of value passed in with table setup by
// addFieldCardinality.  If the field is not setup in the map, the method will
// assert.  The deveried class must setup all possible criteria types in this
// map.
// @param   const DString& dstrCriteriaType - CritieraType to check.
//          unsigend int - number of time this criteria type has occurred.
// @returns true - if it is in the map and within the min/max limits
//          false - otherwise.
//*****************************************************************************
bool ifastReportCriteriaList::withinCardinality ( const DString& dstrCriteriaType, unsigned int inum )
{
   // Look for the criteria type in the fieldCardinality map defined by the deveried class.
   std::map < DString, MinMax >::iterator mapiter = _mapfieldCardinality.find ( dstrCriteriaType );
   if ( mapiter == _mapfieldCardinality.end() )
      //All critiera type cardinality must be defined in dervied class.
      assert (0); 
   if (( inum >= mapiter->second.min ) && ( inum <= mapiter->second.max ))
      return true;
   else
      return false;   
}

//*****************************************************************************
// When the ReportType is F, it means the criteria is a required criteria. 
// All required criterias cannot be deleted.
// @param   const BFDataGroupId& idDataGroup - current data group.
// @returns bool - true when the criteria is not required and false otherwise
//*****************************************************************************
bool ifastReportCriteriaList::canDeleteObject( const DString&  strKey, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "canDeleteObject" ) );
   ifastReportCriteria* pifastReportCriteria = dynamic_cast<ifastReportCriteria* > ( getObject(strKey, idDataGroup) );
   DString dstrRecordType;
   pifastReportCriteria->getField ( ifds::RecordType, dstrRecordType, idDataGroup );
   if ( dstrRecordType != REPEAT ) {
      //Cannot delete a fixed record.
      ADDCONDITIONFROMFILE ( CND::ERR_CANNOT_DELETE_FIXED_RECORD );
   }
   return  ( dstrRecordType == REPEAT );
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/ifastReportCriteriaList.cpp-arc  $
// 
//    Rev 1.7   Dec 08 2006 15:00:24   ZHANGCEL
// Incident #735187 -- Fix bug in doValidateAll
// 
//    Rev 1.6   Nov 14 2004 14:48:30   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.5   Jun 16 2003 15:00:14   HSUCHIN
// PTS 10018375 - Bug with validate all.
// 
//    Rev 1.4   Mar 21 2003 18:16:06   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.3   Mar 10 2003 09:52:54   HSUCHIN
// PST 10014576 - fixes another bug where all was selected second and no error showed up.
// 
//    Rev 1.2   Mar 10 2003 08:49:06   HSUCHIN
// PTS 10014576 - prevent exclude all.
// 
//    Rev 1.1   Jan 28 2003 13:52:38   HSUCHIN
// ignore the dummy items
// 
//    Rev 1.0   Nov 27 2002 11:39:10   HSUCHIN
// Initial Revision
*/
