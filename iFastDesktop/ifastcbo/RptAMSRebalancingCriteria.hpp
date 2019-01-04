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
// ^FILE   : RptAMSRebalancingCriteria.hpp
// ^AUTHOR : 
// ^DATE   : Nov 15, 2002
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : RptAMSRebalancingCriteria
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************

#include "mfcancbo.hpp"
#include <boost\utility.hpp>
#include "ifastreportcriteria.hpp"

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE RptAMSRebalancingCriteria : public ifastReportCriteria
{
	public:

	//*****************************************************************************
	// Constructor
	//*****************************************************************************
	RptAMSRebalancingCriteria( BFAbstractCBO &parent );
	RptAMSRebalancingCriteria( DString dstrRptName, BFAbstractCBO &parent, const BFDataGroupId& idDataGroup );
	//*****************************************************************************
	// Destructor
	//*****************************************************************************
	~RptAMSRebalancingCriteria();

   //*****************************************************************************
   // This method will make the fieldId passed in, required, readonly and initialize
   // with default values.   Currently the fieldIds StartDate / InclPending are
   // processed as required, all others ignored.
   // @param   BFFieldId fieldId - field Id to setup as required.
   // @returns SEVERITY.
   //*****************************************************************************
   SEVERITY setupRequiredRecord( BFFieldId fieldId, const BFDataGroupId& idDataGroup );

   //*****************************************************************************
   // This method will make a view call 223 to validate the account number.  View
   // 223 will return valid for AMS accounts only, error otherwise.  When the 
   // view is successfull the Description field will be populated with the 
   // shareholder name, NULL_STRING otherwise.
   // @param   const DString& dstrBrokerCode - broker code to check
   //          const BFDataGroupId& idDataGroup - current data group id.
   // @returns SEVERITY - Error from view call.
   //*****************************************************************************
   SEVERITY validateAccountNum( const DString& strValue, const BFDataGroupId& idDataGroup );

   SEVERITY doReportModeRelatedChanges ( BFFieldId fieldId, const BFDataGroupId& idDataGroup );

   protected:
   //*****************************************************************************
   // doValidateField will validate the AccountNum and AMSCode.  It will call
   // the helper methods validateAMSCode and validateAccountNum to do the
   // validation.
   // @param   const BFFieldId& idField - current field id validated.
   //          const DString& strValue - value associated to field id.
   //          const BFDataGroupId& idDataGroup - current group id.
   //*****************************************************************************
   SEVERITY doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup );   
   
   //*****************************************************************************
   // doGetCriteriaList will validate all criteria list on screen and return 
   // substitution list based on criteria type.
   //*****************************************************************************
   SEVERITY doGetCriteriaList( DString &dstrCriteriaList, BFFieldId& bfCriteriaField, const BFDataGroupId& idDataGroup );

   //*****************************************************************************
   void doInitWithDefaultValues( const BFDataGroupId& idDataGroup );  

   SEVERITY doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup );

   private:
   //*****************************************************************************
   // This method will blank out the Description field and validate the AMSCode
   // entered for the AMS Code criteria type.   The validation is successful upon
   // a successful creation of the AMSMstrList.  
   // @param   const DString& dstrBrokerCode - broker code to check
   //          const BFDataGroupId& idDataGroup - current data group id.
   // @returns SEVERITY - Error from creation of AMSMstrList.
   //*****************************************************************************
   SEVERITY validateAMSCode( const DString& strValue, const DString& dstrAMSType, const BFDataGroupId& idDataGroup );

};
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/RptAMSRebalancingCriteria.hpp-arc  $
//
//   Rev 1.7   May 10 2007 10:10:48   porteanm
//Incident 774181 - Display name for account held by nominees/intermediaries.
//
//   Rev 1.6   Nov 14 2004 14:53:10   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.5   Jun 21 2004 10:14:34   VADEANUM
//PTS 10031437 - Exclude the edit check for error number 405 and 406 when user is running the option in 'Report' mode.
//
//   Rev 1.4   Mar 21 2003 18:22:28   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.3   Jan 02 2003 13:44:38   HSUCHIN
//bug fix for dovalidatefield
//
//   Rev 1.2   Dec 27 2002 11:32:02   linmay
//modified doValidateField and ValidateAMSCode function
//
//   Rev 1.1   Nov 29 2002 14:19:30   HSUCHIN
//rename cbo name
//
//   Rev 1.0   Nov 29 2002 13:38:34   HSUCHIN
//Initial revision.
//
//   Rev 1.0   Nov 27 2002 11:40:50   HSUCHIN
//Initial Revision
*/
