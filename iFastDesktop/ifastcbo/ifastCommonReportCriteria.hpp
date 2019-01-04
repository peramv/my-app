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
// ^FILE   : ifastCommonReportCriteria.hpp
// ^AUTHOR : 
// ^DATE   : Nov 13, 2002
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : ifastCommonReportCriteria
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************

#include "mfcancbo.hpp"
#include <boost\utility.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class ifastReportCriteriaList;
class IFASTCBO_LINKAGE ifastCommonReportCriteria : public MFCanBFCbo, private boost::noncopyable
{
   public:
   //*****************************************************************************
   // Constructor
   //*****************************************************************************
   ifastCommonReportCriteria( BFAbstractCBO &parent );

   //*****************************************************************************
   // Destructor
   //*****************************************************************************
   ~ifastCommonReportCriteria();

   //*****************************************************************************
   SEVERITY init( const BFDataGroupId& idDataGroup, 
                  const DString& dstrTrack = I_("N"), 
                  const DString& dstrPageName = NULL_STRING);

   //*****************************************************************************
   // Inits the ifastCommonReportCriteria CBO with default data.
   //    Field             Value             Description
   //    ReportName        IFAST.AMSREBAL    AMS Rebalancing
   //    ReportMode        N                 Report Mode
   //    ReportType        Y                 Online
   //    Schedule          N                 Run Now
   //    
   // RunOnDate, RunOnTime field will be marked as ReadOnly
   // @param   const BFDataGroupId& idDataGroup - Current DataGroupId.
   // @returns void.
   //*****************************************************************************
   void init( DString dstrRptName );
   void doInitWithDefaultValues( const BFDataGroupId& idDataGroup );
   //*****************************************************************************
   // This is a template class which will return a pointer to a Report based on 
   // the assignment value.  If the parameter bCreateNewList = true, a new Report 
   // pointer is returned and the old one deleted.  This should normally be the 
   // case except for when called by the transaction builder.   A private variable 
   // pReport is required to store the report _T.
   // @param  bool bCreateNewList  - True/False
   // @returns _T
   //*****************************************************************************
/*
   template < class _T >      
      _T* getCriteriaList ( _T*& pT, bool bCreate )
      {
         if ( bCreate ) {
            if ( pCriteriaList )
               delete pCriteriaList;
            pCriteriaList = new _T;
            pCriteriaList->init();

         } else
            return pCritieraList;
      }
*/

   ifastReportCriteriaList* getCriteriaList () { return _pCriteriaList; };

   SEVERITY createCriteriaList ( ifastReportCriteriaList*& pifastReportCriteriaList, const BFDataGroupId& idDataGroup );

   protected:
   //*****************************************************************************
   // Validates the field information. The following fields are validated.
   // RunOnTime - calls validateTime.
   // @param   const BFFieldId& idField - field to be validated.
   //          const DString& strValue - Value contained in field.
   //          const BFDataGroupId& idDataGroup - datagroup to be validated.
   // @returns SEVERITY.
   //*****************************************************************************
   SEVERITY doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup );

   //*****************************************************************************
   // Method which handles related changes for field ids ScheduleJob and ReportType.
   // When the fieldId is ScheduleJob - setDateTimeReadOnly is called.
   // When the fieldId is ReportType - setReportMode is called.
   // @param   const BFFieldId& idField - field id
   //          const BFDataGroupId& idDataGroup - current data group.
   // @returns SEVERITY - None.
   //*****************************************************************************
   SEVERITY doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup );

   private:

   //*****************************************************************************
   // Functions which makes a view call to get timezone from base system.
   // @param  const BFDataGroupId& idDataGroup - current data group.
   // @return void.
   //*****************************************************************************
   void getTimeZone( DString& dstrTimeZone, const BFDataGroupId& idDataGroup );

   //*****************************************************************************
   // This method will set the RunOnDate/RunOnTime as ReadOnly or not based on
   // the value of the ScheduleJob field.  If value of ScheduleJob field is Y, then
   // fields will be not Read Only and vice versa
   // @param   const BFDataGroupId& idDataGroup - current data group.
   // @returns void.
   //*****************************************************************************
   void setDateTimeReadOnly( const BFDataGroupId& idDataGroup );

   //*****************************************************************************
   // This method will set the Report Mode to Update ("Y") when the Report Type 
   // is changed to Cycle.  It will also mark the Report Mode as Read Only. When 
   // the Report Type is changed back to Online, the Report Mode will be marked as 
   // not Read Only and is updatable.
   // @param   const BFDataGroupId& idDataGroup - current data group.
   // @returns void.
   //*****************************************************************************
   void setReportMode ( const BFDataGroupId& idDataGroup );

	SEVERITY validateDate( const DString& dstrDate, const BFDataGroupId& idDataGroup );

   //*****************************************************************************
   // This method will validate the time entered.  It will check time using the 
   // format hh:mm or hhmm.
   // @param   const DString& dstrTime - Time being validated.
   //          const BFDataGroupId& idDataGroup - current data group.
   // @returns SEVERITY - ERR_INVALID_TIME 
   //                     "Invalid value for time, must be in format of 'HH:MM'"
   //*****************************************************************************
   SEVERITY validateTime ( const DString& dstrTime, const BFDataGroupId& idDataGroup );
   
   ifastReportCriteriaList* _pCriteriaList;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/ifastCommonReportCriteria.hpp-arc  $
//
//   Rev 1.4   Nov 14 2004 14:48:24   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.3   Jan 06 2004 10:08:16   VADEANUM
//PTS 10025333 - Missed AMS requirement - added validateDate().
//
//   Rev 1.2   May 28 2003 10:52:16   popescu
//Part of the cleaning of DSTCWorksession, not finalized yet, more to come....
//
//   Rev 1.1   Mar 21 2003 18:15:52   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.0   Nov 27 2002 11:40:48   HSUCHIN
//Initial Revision
*/
