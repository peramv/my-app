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
//    Copyright 2003 by International Financial, Inc.
//
//*****************************************************************************
//
// ^FILE   : ResetInstr.hpp
// ^AUTHOR : 
// ^DATE   : Jan 23, 2002
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : ResetInstr
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

class FundClassRules;
class ProtectedFundList;
class IFASTCBO_LINKAGE ResetInstr : public MFCanBFCbo, private boost::noncopyable
{
	public:

	//*****************************************************************************
	// Constructor
	//*****************************************************************************
	ResetInstr( BFAbstractCBO &parent );

	//*****************************************************************************
	// Destructor
	//*****************************************************************************
	~ResetInstr();

   SEVERITY init( const BFData& data, bool bBaseDelete = false );
	SEVERITY init( const BFDataGroupId& idDataGroup );

   void Reversal( ResetInstr* pResetInstr, const BFDataGroupId& idDataGroup );

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
   //*****************************************************************************
   void doInitWithDefaultValues( const BFDataGroupId& idDataGroup );        

   private:

   //*****************************************************************************
   // Makes a view call to get the Batch information.
   // @param   const BFDataGroupId& idDataGroup - current group id.
   //*****************************************************************************
   SEVERITY getBatchInfo( const BFDataGroupId& idDataGroup );

	//*****************************************************************************
	// This method will check to see if the account number passed in is validate 
	// or not by issuing a call to WorkSession::getMFAccount.
	// @param   const DString& dstrAccountNum - Account Number to validate.
	//          const BFDataGroupId& idDataGroup - current data group id.
	// @returns SEVERITY. "Invalid Account Number."
	//*****************************************************************************
   SEVERITY validateAccountNum( const DString& strValue, const BFDataGroupId& idDataGroup );

   //*****************************************************************************
   // Validates the Effective Date passed in is before the current business date.  If 
   // the instruction code is not 02 (Death Reset), the Effective Date cannot not be 
   // changed.
   // @param   const DString& dstrEffectiveDate - Effective Date to check
   //          const BFDataGroupId& idDataGroup - current data group id.
   //*****************************************************************************
   SEVERITY validateEffectiveDate( const DString& dstrEffectiveDate, const BFDataGroupId& idDataGroup );

   SEVERITY validateFundClass( const BFDataGroupId& idDataGroup );
   SEVERITY isFundClassInProtectedList( const BFDataGroupId& idDataGroup );
   SEVERITY isFundClassInHoldings( const BFDataGroupId& idDataGroup );
   void setAllFieldsReadOnly( const BFDataGroupId& idDataGroup );
   SEVERITY isResetAllowed ( const BFDataGroupId& idDataGroup );

   FundClassRules* _pFundClassRules;
   ProtectedFundList* _pProtectedFundList;
};
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/ResetInstr.hpp-arc  $
//
//   Rev 1.6   Aug 02 2005 16:39:18   AGUILAAM
//IN 329838 : call getBatchInfo within (new) init procedure only; 'no active batch' error from getBatchInfo when called from  doInitWithDefaultValues was causing Desktop to crash.
//
//   Rev 1.5   Nov 14 2004 14:52:14   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.4   Mar 21 2003 18:21:48   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.3   Feb 06 2003 15:05:04   HSUCHIN
//added method isResetAllowed to check if the current cbo is allowed to be reset
//
//   Rev 1.2   Jan 29 2003 12:16:00   HSUCHIN
//add bus rule to mark all field readonly when the reset instr has been completed
//
//   Rev 1.1   Jan 27 2003 07:41:26   HSUCHIN
//added support for reversal
//
//   Rev 1.0   Jan 24 2003 10:19:24   HSUCHIN
//Initial Revision
*/
