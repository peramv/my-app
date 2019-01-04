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
// ^FILE   : ifastReportCriteriaList.hpp
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

#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>

#undef IFASTRPTCBO_LINKAGE
#ifdef IFASTRPTCBO_DLL
   #define IFASTRPTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTRPTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTRPTCBO_LINKAGE ifastReportCriteriaList : public MFCanBFCbo, private boost::noncopyable
{
   public:

   //*****************************************************************************
   // Constructor
   //*****************************************************************************
   ifastReportCriteriaList( BFAbstractCBO &parent );

   //*****************************************************************************
   // Destructor
   //*****************************************************************************
   ~ifastReportCriteriaList();

   protected:

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
   SEVERITY doValidateAll( long lGroupId, long lValidateGroup );

   //*****************************************************************************
   // Set up the cardinality map for the fields.
   // @param   DString dstrCriteriaType - Criteria Type.
   //          int min - Minimum occurance of this Criteria Type.
   //          int max - Maxmimu occurance of this Criteria Type.
   //*****************************************************************************
   void addFieldCardinality ( DString& dstrCriteriaType, unsigned int min, unsigned int max );

   private:

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
   bool withinCardinality ( const DString& dstrCriteriaType, unsigned int inum );

      struct MinMax
      {
         unsigned int min;
         unsigned int max;       //use -1 to represent *
      };
      std::map< DString, MinMax > _mapfieldCardinality;      
};
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastrptcbo/ifastReportCriteriaList.hpp-arc  $
//
//   Rev 1.0   Nov 19 2002 11:28:18   HSUCHIN
//Initial Revision
*/
