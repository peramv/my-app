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
// ^FILE   : AMSRebalancingCriteria.hpp
// ^AUTHOR : 
// ^DATE   : Nov 15, 2002
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : AMSRebalancingCriteria
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************

#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>
#include "ifastreportcriteria.hpp"

#undef IFASTRPTCBO_LINKAGE
#ifdef IFASTRPTCBO_DLL
   #define IFASTRPTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTRPTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTRPTCBO_LINKAGE AMSRebalancingCriteria : public ifastReportCriteria
{
	public:

	//*****************************************************************************
	// Constructor
	//*****************************************************************************
	AMSRebalancingCriteria( BFAbstractCBO &parent );

	//*****************************************************************************
	// Destructor
	//*****************************************************************************
	~AMSRebalancingCriteria();

   protected:
   //*****************************************************************************
   // doValidateFields will validate the AccountNum and AMSCode.  It will call
   // the helper methods validateAMSCode and validateAccountNum to do the
   // validation.
   // @param   const BFFieldId& idField - current field id validated.
   //          const DString& strValue - value associated to field id.
   //          long lDataGroupId - current group id.
   //*****************************************************************************
   SEVERITY doValidateFields( const BFFieldId &idField, const DString& strValue, long  lDataGroupId );

   private:
   //*****************************************************************************
   // This method will blank out the Description field and validate the AMSCode
   // entered for the AMS Code criteria type.   The validation is successful upon
   // a successful creation of the AMSMstrList.  
   // @param   const DString& dstrBrokerCode - broker code to check
   //          long lDataGroupId - current data group id.
   // @returns SEVERITY - Error from creation of AMSMstrList.
   //*****************************************************************************
   SEVERITY validateAMSCode( const DString& strValue, long  lDataGroupId );

   //*****************************************************************************
   // This method will make a view call 223 to validate the account number.  View
   // 223 will return valid for AMS accounts only, error otherwise.  When the 
   // view is successfull the Description field will be populated with the 
   // shareholder name, NULL_STRING otherwise.
   // @param   const DString& dstrBrokerCode - broker code to check
   //          long lDataGroupId - current data group id.
   // @returns SEVERITY - Error from view call.
   //*****************************************************************************
   SEVERITY validateAccountNum( const DString& strValue, long  lDataGroupId );

};
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastrptcbo/AMSRebalancingCriteria.hpp-arc  $
//
//   Rev 1.0   Nov 19 2002 11:28:14   HSUCHIN
//Initial Revision
*/
