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

#include "mfcancbo.hpp"
#include <boost\utility.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE ifastReportCriteria : public MFCanBFCbo, private boost::noncopyable
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
   //          const BFDataGroupId& idDataGroup - current group id.
   // @returns SEVERITY - severity from validateBrokerCode and validateGroupCode.
   //*****************************************************************************
   SEVERITY doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup );

   //*****************************************************************************
   // The base doApplyRelatedChanges will call clearFields to clear out the 
   // Criteria value field whent the criteria type changes.
   // @param   const BFFieldId& idField - current field id changed.
   //          const BFDataGroupId& idDataGroup - current data group id.
   // @returns SEVERITY - NO_CONDITION in general.
   //*****************************************************************************
   SEVERITY doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup );

   //*****************************************************************************
   // Implement by dervied class, otherwise getReportDate will return current
   // business day.
   // @param   const BFDataGroupId& idDataGroup - current data group.
   // @returns DString - Date determined by dervied class.
   //*****************************************************************************
   virtual DString doGetReportDate( const BFDataGroupId& idDataGroup ) {
      return NULL_STRING;
   };

   virtual void doInitWithDefaultValues( const BFDataGroupId& idDataGroup );

   private:

   //*****************************************************************************
   // This method will clear the criteria value field when the criteria type has
   // changed to a new criteria type.
   // @param   const BFDataGroupId& idDataGroup - current data group id.
   //*****************************************************************************
   void clearFields( const BFDataGroupId& idDataGroup );

   //*****************************************************************************
   // This method will check to see if the group code passed in can be found in
   // the group list cbo.  If the group code exists in the group list cbo, the 
   // group name will be extract and set to the field Description, otherwise 
   // NULL_STRING.
   // @param   const DString& dstrGroupCode - group code to validate.
   //          const BFDataGroupId& idDataGroup - current data group id.
   // @returns SEVERITY. "Invalid Group Code."
   //*****************************************************************************
   SEVERITY validateGroupCode( const DString& dstrGroupCode, const BFDataGroupId& idDataGroup );

   //*****************************************************************************
   // Validates the broker code passed in by creating a broker list cbo with
   // the broker passed in.   If the init of the broker list cbo failed, then
   // the SEVERITY returned is passed back.  If the broker code is valid, then
   // the Description field will be set to the broker name, otherwise NULL_STRING.
   // @param   const DString& dstrBrokerCode - broker code to check
   //          const BFDataGroupId& idDataGroup - current data group id.
   // @returns SEVERITY - "Invalid Broker Code."
   //*****************************************************************************
   SEVERITY validateBrokerCode( const DString& dstrBrokerCode, const BFDataGroupId& idDataGroup );

   //*****************************************************************************
   // This method will return the current business date unless the dervied class
   // overrides doGetReportDate to return the date of the report.  This is 
   // mainly used for checks such as status of broker whether the broker is active
   // or inactive.
   // @param   const BFDataGroupId& idDataGroup - current data group.
   // @returns DString - Current business Date or date returned by derveried class.
   //*****************************************************************************
   DString getReportDate( const BFDataGroupId& idDataGroup );

   SEVERITY setupSubList( const BFDataGroupId& idDataGroup );

   //*****************************************************************************
   // This method will take a list object, the of a field and convert it to a
   // substitution set.
   // @param   const BFCBO*& pBFCBO - Cbo list.
   //          BFField& idField - Field to convert into a sub list.
   //          DString& dstrSubList - Substitution list returned.
   //          const BFDataGroupId& idDataGroup - current data group id.
   // @returns void.   Substitution list or NULL_STRING stored in dstrSubList.
   //*****************************************************************************
   void createSubList( BFCBO* pBFCBO, BFFieldId idField, DString& dstrSubList, const BFDataGroupId& idDataGroup );

   DString oldCriteriaType;
};
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/ifastReportCriteria.hpp-arc  $
//
//   Rev 1.2   Nov 14 2004 14:48:30   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.1   Mar 21 2003 18:16:04   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.0   Nov 27 2002 11:40:48   HSUCHIN
//Initial Revision
*/
