#pragma once
//******************************************************************************
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
//
//******************************************************************************
//
// ^FILE   : PensionInfo.hpp
// ^AUTHOR : 
// ^DATE   : May 17, 2002
//
// ^CLASS    : PensionInfo
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************


#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class MFAccount;

class IFASTCBO_LINKAGE PensionInfo : public MFCanBFCbo, private boost::noncopyable
{
public:

//*****************************************************************************
// Constructor
//*****************************************************************************

   PensionInfo( BFAbstractCBO &parent );

//*****************************************************************************
// Destructor
//*****************************************************************************

   virtual ~PensionInfo();

//*****************************************************************************
// Initializes Pension Info cbo.
// @param   DString dstrTrack - Account Number used to get Account Holdings
//          DString dstrPageName - Interest, MF, MFR are the 3 different types.
//          const BFDataGroupId& idDataGroup - current datagroup.
// @returns void.
//*****************************************************************************

   SEVERITY init( const BFDataGroupId& idDataGroup, 
                  const DString& dstrTrack = I_("N"),
                  const DString& dstrPageName = NULL_STRING );

//******************************************************************************
// Calculates the Sex Distinct Portion of Current Market Value for the Pension.
//    SettleValue (Account Holdings) * SexDistinctPer / 100.
// @param   const BFDataGroupId& idDataGroup - data group id.
// @returns DString - Portion of Current Market Value formatted to 2 decimals.
//******************************************************************************

   DString getSexDistinctCurrentMarketValue ( const BFDataGroupId& idDataGroup );

//******************************************************************************
// Initializes new Pension Information.
// @param const BFDataGroupId& idDataGroup - data group id.
// @returns void.
//******************************************************************************

   void initNew ( const BFDataGroupId& idDataGroup );

//******************************************************************************
// This method will change the SexDistinct and UniSexPer accordingly to the 
// Jurisdiction set in MFAccount.
// @param const BFDataGroupId& idDataGroup - data group id.
// @returns void.
//******************************************************************************

   void refreshJurisdiction ( const BFDataGroupId& idDataGroup );

private:

//******************************************************************************
// Initializes new pension information with default values.
// @param   const BFDataGroupId& idDataGroup - data group id.
// returns  void.
//******************************************************************************

   void doInitWithDefaultValues ( const BFDataGroupId& idDataGroup );

//******************************************************************************
// Do apply related changes
//    UniSexPer - will recalculated the MktValueSexDistinct based on the new
//                UniSexPer value.
// @param   const BFFieldId& idField - field id.
//          const BFDataGroupId& idDataGroup - data group id.
// @returns SEVERITY.
//******************************************************************************

   SEVERITY doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup );   

//******************************************************************************
// Field validation
//    MinWithAge - must less than MinAge from MF Account.
//    UniSexPer - must be in between 0 and 100.
//    SexDistinctPer - must be in between 0 and 100.
// @param   const BFFieldId& idField - field id.
//          DString& strValue - value of the field
//          const BFDataGroupId& idDataGroup - data group id.
//******************************************************************************

   SEVERITY doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup );

//******************************************************************************
// validates all of Pension information
//    UniSexPer + SexDistinctPer must equal 100%
// @param   const BFDataGroupId& idDataGroup - data group id.
//          long lValidateGroup - validation group id.
// @returns SEVERITY.
//******************************************************************************

   SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup );

   MFAccount *_pMFAccount;          //Pointer to MFAccount CBO
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/PensionInfo.hpp-arc  $
//
//   Rev 1.5   Nov 14 2004 14:51:08   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.4   Mar 21 2003 18:20:12   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.3   Oct 09 2002 23:54:50   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.2   Aug 29 2002 12:53:10   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.1   Aug 09 2002 16:13:26   HSUCHIN
//added refreshJurisdiction method
//
//   Rev 1.0   May 30 2002 16:44:46   HSUCHIN
//Initial revision.
*/
