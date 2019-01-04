#pragma once
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

#include "mfcancbo.hpp"
#include <boost\utility.hpp>
#include "AMSHypoAllocList.hpp"
#include "FundAllocList.hpp"

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE ifastReportCriteriaList : public MFCanBFCbo, private boost::noncopyable
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

   //*****************************************************************************
   // Interface for dervied class to setup default criterias.
   // @param   const BFDataGroupId& idDataGroup - current data group id.
   //*****************************************************************************

   virtual void init( const BFDataGroupId& idDataGroup ) = 0;
   virtual void initWithRptName ( const BFDataGroupId& idDataGroup, DString dstrRptName ) = 0;
   //*****************************************************************************
   // This interface is used by the ifastCommonReportCriteria on doApplyRelatedChange
   // for Report Type and On init of ifastReportCriteriaList.  It is used to
   // apply rules to the criteria list when the report type changes from Online 
   // or cycle mode.
   // @param   bool bOnline - boolean to indicate whether the report type is online.
   //          const BFDataGroupId& idDataGroup - current data group id.
   //*****************************************************************************
   virtual void doReportTypeRelatedChanges ( bool bOnline, const BFDataGroupId& idDataGroup ) = 0;

	virtual SEVERITY doAllReportModeRelatedChanges ( const BFDataGroupId& idDataGroup ) = 0;

	virtual SEVERITY doInitPendingModeRelatedChanges ( const BFDataGroupId& idDataGroup ) = 0;
	
	virtual SEVERITY doAllReportNameRelatedChanges (const BFDataGroupId& idDataGroup ) = 0;

	virtual SEVERITY createAMSHypoAllocList ( AMSHypoAllocList*& pAMSHypoAllocList, 
											  DString identifyType,
											  DString identifyCode,
										      FundAllocList* pAMSFundAllocList, 
											  const BFDataGroupId& idDataGroup ) = 0;

    virtual AMSHypoAllocList* getAMSHypoAllocList(const BFDataGroupId& idDataGroup ) = 0;

	virtual SEVERITY deleteAMSHypoAllocList ( const BFDataGroupId& idDataGroup ) = 0;

   protected:

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
   virtual SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup );
   
   //*****************************************************************************
   // Set up the cardinality map for the fields.
   // @param   DString dstrCriteriaType - Criteria Type.
   //          int min - Minimum occurance of this Criteria Type.
   //          int max - Maxmimu occurance of this Criteria Type.
   //*****************************************************************************
   void addFieldCardinality ( DString& dstrCriteriaType, unsigned int min, unsigned int max );   

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

   
   //*****************************************************************************
   // When the ReportType is F, it means the criteria is a required criteria. 
   // All required criterias cannot be deleted.
   // @param   const BFDataGroupId& idDataGroup - current data group.
   // @returns bool - true when the criteria is not required and false otherwise
   //*****************************************************************************
   virtual bool canDeleteObject( const DString&  strKey, const BFDataGroupId& idDataGroup );


   private:

      struct MinMax
      {
         unsigned int min;
         unsigned int max;       //use -1 to represent *
      };
      std::map< DString, MinMax > _mapfieldCardinality;  

	  AMSHypoAllocList* _pAMSHypoAllocList;
};
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/ifastReportCriteriaList.hpp-arc  $
//
//   Rev 1.5   Nov 14 2004 14:48:32   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.4   Jun 21 2004 12:28:18   VADEANUM
//PTS 10031151 - InclPending validation.
//
//   Rev 1.3   Jun 21 2004 10:43:28   VADEANUM
//PTS 10031437 - Excluded the edit check for error number 405 and 406 when user is running the option in 'Report' mode. 
//
//   Rev 1.2   Mar 21 2003 18:16:08   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.1   Dec 08 2002 21:52:30   HSUCHIN
//added doReportTypeRelatedChanges interface
//
//   Rev 1.0   Nov 27 2002 11:40:50   HSUCHIN
//Initial Revision
*/
