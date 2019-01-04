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
//    Copyright 2003 by International Financial, Inc.
//
//*****************************************************************************
//
// ^FILE   : ResetInstrCriteria.hpp
// ^AUTHOR : 
// ^DATE   : Jan 15, 2003
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : ResetInstrCriteria
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

class ResetInstrList;
class IFASTCBO_LINKAGE ResetInstrCriteria : public MFCanBFCbo, private boost::noncopyable
{
   public:

   //*****************************************************************************
   // Constructor
   //*****************************************************************************
   ResetInstrCriteria( BFAbstractCBO &parent );

   //*****************************************************************************
   // Destructor
   //*****************************************************************************
   ~ResetInstrCriteria();

   //*****************************************************************************
   // This method will init the field ResetInstrUsing to AccountNum
   // @param   const BFDataGroupId& idDataGroup - current data group id.
   // @returns SEVERITY. "Invalid Account Number."
   //*****************************************************************************
   SEVERITY init( DString& dstrAccountNum, const BFDataGroupId& idDataGroup );

   protected:

   //*****************************************************************************
   // doValidateFields will validate the AccountNum and TradeDate.  It will call
   // the helper methods validateAccountNum and validateTradeDate to do the
   // validation.
   // @param   const BFFieldId& idField - current field id validated.
   //          const DString& strValue - value associated to field id.
   //          const BFDataGroupId& idDataGroup - current group id.
   //*****************************************************************************
   SEVERITY doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup );

   private:

   //*****************************************************************************
   // This method will check to see if the account number passed in is validate 
   // or not by issuing a call to WorkSession::getMFAccount.
   // @param   const DString& dstrAccountNum - Account Number to validate.
   //          const BFDataGroupId& idDataGroup - current data group id.
   // @returns SEVERITY. "Invalid Account Number."
   //*****************************************************************************
   SEVERITY validateAccountNum( const DString& dstrAccountNum, const BFDataGroupId& idDataGroup );

   //*****************************************************************************
   // Validates the Trade Date passed in is before the current business date.
   // @param   const DString& dstrTradeDate - Trade Date to check
   //          const BFDataGroupId& idDataGroup - current data group id.
   //*****************************************************************************
   SEVERITY validateTradeDate( const DString& dstrTradeDate, const BFDataGroupId& idDataGroup );

   DString _dstrOldResetUsingType;
};
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/ResetInstrCriteria.hpp-arc  $
//
//   Rev 1.5   Nov 14 2004 14:52:16   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.4   Mar 21 2003 18:21:52   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.3   Feb 04 2003 11:47:16   HSUCHIN
//added new condition and removed ResetInstrList retrieval methods
//
//   Rev 1.2   Jan 26 2003 16:04:12   HSUCHIN
//changed the way reset instr list is init
//
//   Rev 1.1   Jan 25 2003 17:36:32   HSUCHIN
//more enhancements
//
//   Rev 1.0   Jan 24 2003 10:19:32   HSUCHIN
//Initial Revision
*/
