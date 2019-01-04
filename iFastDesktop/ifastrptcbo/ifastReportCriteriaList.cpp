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
#include "ifastreportcriterialist.hpp"

namespace
{
   const I_CHAR * const CLASSNAME = I_( "ifastReportCriteriaList" );
   const I_CHAR * const ALL = I_( "@" );
   const I_CHAR * const NO = I_( "N" );
   const I_CHAR * const YES = I_( "Y" );      
   const int MAX_CRITERIA = 40;
}

namespace CND
{
   //extern CLASS_IMPORT const long ERR_INVALID_TIME;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId CriteriaType;
   extern CLASS_IMPORT const BFTextFieldId IncludeExclude;
}

//*****************************************************************************
// Constructor
//*****************************************************************************

ifastReportCriteriaList::ifastReportCriteriaList( BFAbstractCBO &parent )
:  MFCanBFCbo( parent )
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
// @param long lDataGroupId - Current Data Group Id.
// @param long lValidateGroup - Current Validation Group.
// @returns SEVERITY - "Duplicate rebalancing criteria %CRITERIATYPE% - %CRITERIAVALUE%."
//                     "%CRITERIATYPE% has all selected. Cannot Include more of the same criteria."
//*****************************************************************************
SEVERITY ifastReportCriteriaList::doValidateAll( long lGroupId, long lValidateGroup )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );
   std::map < DString, unsigned int > mapNumCriteriaType;
   std::map < DString, unsigned int >::iterator mapiter;
   std::set < DString > dupCriteriaValueSet;
   std::set < DString > cannotIncludeSet;
   BFObjIter iter( *this, lGroupId, false, BFObjIter::ITERTYPE::NON_DELETED );
   DString dstr, dstrCriteriaType, dstrCriteriaValue;
   BFFieldId curFieldId;
   int iNumCriterias = 0;
   while( !iter.end() )
   {  
      ++iNumCriterias;
      iter.getObject()->getField ( ifds::CriteriaType, dstrCriteriaType, lGroupId );
      curFieldId = BFFieldId::getId ( dstrCriteriaType );
      iter.getObject()->getField ( curFieldId, dstrCriteriaValue, lGroupId );
      mapiter = mapNumCriteriaType.find ( dstrCriteriaType );
      // If it is not in map, add it to the map
      if ( mapiter == mapNumCriteriaType.end()  ) {
         mapNumCriteriaType.insert ( std::make_pair ( dstrCriteriaType, 1 ) );
      } else {
         mapiter->second = ++mapiter->second;
      }
      dstr = dstrCriteriaType + dstrCriteriaValue;
      if( !dupCriteriaValueSet.insert(dstr).second )
      {
         // Raise condition "Duplicate criteria and value."
         return(GETCURRENTHIGHESTSEVERITY());
      }

      // If the CriteriaValue is All for Criteria Type
      // We will inserted into a set 
      DString dstrInclude;
      if ( dstrCriteriaValue == ALL )
         cannotIncludeSet.insert ( dstrCriteriaType );
      else {
         iter.getObject()->getField ( ifds::IncludeExclude, dstrInclude, lGroupId );
         if (( dstrInclude == YES ) && ( !cannotIncludeSet.insert(dstrCriteriaType).second )) {
            // Raise condition "Criteria has All selected."
         }
      }
   }   
   if ( iNumCriterias > MAX_CRITERIA ) {
      //Raise condition. "Criterias exceed limit."
   }

   mapiter = mapNumCriteriaType.begin();
   while ( mapiter != mapNumCriteriaType.end() ) {
      if ( !withinCardinality ( mapiter->first, mapiter->second ) ) {
         //Raise condition "The criteria %CRITERIA% cannot occured more than %MAX% times."
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

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastrptcbo/ifastReportCriteriaList.cpp-arc  $
// 
//    Rev 1.0   Nov 19 2002 11:28:18   HSUCHIN
// Initial Revision
*/
