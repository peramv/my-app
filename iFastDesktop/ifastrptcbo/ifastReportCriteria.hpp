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
// ^FILE   : ifastReportCriteria.hpp
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

#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>

#undef IFASTRPTCBO_LINKAGE
#ifdef IFASTRPTCBO_DLL
   #define IFASTRPTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTRPTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTRPTCBO_LINKAGE ifastReportCriteria : public MFCanBFCbo, private boost::noncopyable
{
   public:

   //*****************************************************************************
   // Constructor
   //*****************************************************************************
   ifastReportCriteria( BFAbstractCBO &parent );

   //*****************************************************************************
   // Destructor
   //*****************************************************************************
   ~ifastReportCriteria();

   protected:

   //*****************************************************************************
   // doValidateFields will validate the BrokerCode and GroupCode.  It will call
   // the helper methods validateGroupCode and validateBrokerCode to do the
   // validation.
   // @param   const BFFieldId& idField - current field id validated.
   //          const DString& strValue - value associated to field id.
   //          long lDataGroupId - current group id.
   // @returns SEVERITY - severity from validateBrokerCode and validateGroupCode.
   //*****************************************************************************
   SEVERITY doValidateFields( const BFFieldId &idField, const DString& strValue, long  lDataGroupId );

   //*****************************************************************************
   // The base doApplyRelatedChanges will call clearFields to clear out the 
   // Criteria value field whent the criteria type changes.
   // @param   const BFFieldId &idField - current field id changed.
   //          long lDataGroupId - current data group id.
   // @returns SEVERITY - NO_CONDITION in general.
   //*****************************************************************************
   SEVERITY doApplyRelatedChanges( const BFFieldId &idField, long lDataGroupId );

   //*****************************************************************************
   // When the ReportType is F, it means the criteria is a required criteria. 
   // All required criterias cannot be deleted.
   // @param   long lDataGroupId - current data group.
   // @returns bool - true when the criteria is not required and false otherwise
   //*****************************************************************************
   bool canDeleteObject( long lDataGroupId );

   //*****************************************************************************
   // Implement by dervied class, otherwise getReportDate will return current
   // business day.
   // @param   long lDataGroupId - current data group.
   // @returns DString - Date determined by dervied class.
   //*****************************************************************************
   virtual DString doGetReportDate( long lDataGroupId ) {
      return NULL_STRING;
   };

   private:

   //*****************************************************************************
   // This method will clear the criteria value field when the criteria type has
   // changed to a new criteria type.
   // @param   long lDataGroupId - current data group id.
   //*****************************************************************************
   void clearFields( long lDataGroupId );

   //*****************************************************************************
   // This method will check to see if the group code passed in can be found in
   // the group list cbo.  If the group code exists in the group list cbo, the 
   // group name will be extract and set to the field Description, otherwise 
   // NULL_STRING.
   // @param   const DString& dstrGroupCode - group code to validate.
   //          long lDataGroupId - current data group id.
   // @returns SEVERITY. "Invalid Group Code."
   //*****************************************************************************
   SEVERITY validateGroupCode( const DString& dstrGroupCode, long lDataGroupId );

   //*****************************************************************************
   // Validates the broker code passed in by creating a broker list cbo with
   // the broker passed in.   If the init of the broker list cbo failed, then
   // the SEVERITY returned is passed back.  If the broker code is valid, then
   // the Description field will be set to the broker name, otherwise NULL_STRING.
   // @param   const DString& dstrBrokerCode - broker code to check
   //          long lDataGroupId - current data group id.
   // @returns SEVERITY - "Invalid Broker Code."
   //*****************************************************************************
   SEVERITY validateBrokerCode( const DString& dstrBrokerCode, long lDataGroupId );

   //*****************************************************************************
   // This method will return the current business date unless the dervied class
   // overrides doGetReportDate to return the date of the report.  This is 
   // mainly used for checks such as status of broker whether the broker is active
   // or inactive.
   // @param   long lDataGroupId - current data group.
   // @returns DString - Current business Date or date returned by derveried class.
   //*****************************************************************************
   DString getReportDate( long lDataGroupId );

   DString oldCriteriaType;
};
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastrptcbo/ifastReportCriteria.hpp-arc  $
//
//   Rev 1.0   Nov 19 2002 11:28:18   HSUCHIN
//Initial Revision
*/
