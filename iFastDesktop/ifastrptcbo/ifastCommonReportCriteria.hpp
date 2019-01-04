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

#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>

#undef IFASTRPTCBO_LINKAGE
#ifdef IFASTRPTCBO_DLL
   #define IFASTRPTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTRPTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTRPTCBO_LINKAGE ifastCommonReportCriteria : public MFCanBFCbo, private boost::noncopyable
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
   // Inits the ifastCommonReportCriteria CBO with default data.
   //    Field             Value             Description
   //    ReportName        IFAST.AMSREBAL    AMS Rebalancing
   //    ReportMode        N                 Report Mode
   //    ReportType        Y                 Online
   //    Schedule          N                 Run Now
   //    
   // RunOnDate, RunOnTime field will be marked as ReadOnly
   // @param   long lDataGroupId - Current DataGroupId.
   // @returns void.
   //*****************************************************************************
   void init( );

   //*****************************************************************************
   // This is a template class which will return a pointer to a Report based on 
   // the assignment value.  If the parameter bCreateNewList = true, a new Report 
   // pointer is returned and the old one deleted.  This should normally be the 
   // case except for when called by the transaction builder.   A private variable 
   // pReport is required to store the report T.
   // @param  bool bCreateNewList  - True/False
   // @returns T
   //*****************************************************************************

   template < class T >      
      T* getCriteriaList ( bool bCreate )
      {
         if ( bCreate ) {
            if ( pCriteriaList )
               delete pCriteriaList;
            pCriteriaList = new T;
            pCriteriaList.init();

         } else
            return <T*>pCritieraList;
      }
   
   protected:
   //*****************************************************************************
   // Validates the field information. The following fields are validated.
   // RunOnTime - calls validateTime.
   // @param   const BFFieldId &idField - field to be validated.
   //          const DString &strValue - Value contained in field.
   //          long lDataGroupId - datagroup to be validated.
   // @returns SEVERITY.
   //*****************************************************************************
   SEVERITY doValidateField( const BFFieldId &idField, const DString& strValue, long  lDataGroupId );

   //*****************************************************************************
   // Method which handles related changes for field ids ScheduleJob and ReportType.
   // When the fieldId is ScheduleJob - setDateTimeReadOnly is called.
   // When the fieldId is ReportType - setReportMode is called.
   // @param   const BFFieldId &idField - field id
   //          long lDataGroupId - current data group.
   // @returns SEVERITY - None.
   //*****************************************************************************
   SEVERITY doApplyRelatedChanges( const BFFieldId &idField, long lDataGroupId );

   private:

   //*****************************************************************************
   // Functions which makes a view call to get timezone from base system.
   // @param   long lDataGroupId - current data group.
   // @retursn SEVERITY.
   //*****************************************************************************
   SEVERITY getTimeZone(long lDataGroupId);

   //*****************************************************************************
   // This method will set the RunOnDate/RunOnTime as ReadOnly or not based on
   // the value of the ScheduleJob field.  If value of ScheduleJob field is Y, then
   // fields will be not Read Only and vice versa
   // @param   long lDataGroupId - current data group.
   // @returns void.
   //*****************************************************************************
   void setDateTimeReadOnly( long lDataGroupId );

   //*****************************************************************************
   // This method will set the Report Mode to Update ("Y") when the Report Type 
   // is changed to Cycle.  It will also mark the Report Mode as Read Only. When 
   // the Report Type is changed back to Online, the Report Mode will be marked as 
   // not Read Only and is updatable.
   // @param   long lDataGroupId - current data group.
   // @returns void.
   //*****************************************************************************
   void setReportMode ( long lDataGroupId );

   //*****************************************************************************
   // This method will validate the time entered.  It will check time using the 
   // format hh:mm or hhmm.
   // @param   const DString& dstrTime - Time being validated.
   //          long lDataGroupId - current data group.
   // @returns SEVERITY - ERR_INVALID_TIME 
   //                     "Invalid value for time, must be in format of 'HH:MM'"
   //*****************************************************************************
   SEVERITY validateTime ( const DString& dstrTime, long lDataGroupId );
   
   BFAbstractCBO* pCriteriaList;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastrptcbo/ifastCommonReportCriteria.hpp-arc  $
//
//   Rev 1.0   Nov 14 2002 15:21:48   HSUCHIN
//Initial Revision
*/
