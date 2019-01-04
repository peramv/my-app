#pragma once

//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 1999 by DST Canada, Inc.
//
//
//******************************************************************************
//
// ^FILE   : TaxJurisLimitList.hpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : TaxJurisLimitList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************


#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>
///#endif

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE TaxJurisLimitList : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   TaxJurisLimitList( BFAbstractCBO &parent );
   virtual ~TaxJurisLimitList( void );

   // Initialize function
   SEVERITY init( DString& TaxType,  
                  const DString &strTaxTypeSchedule,
                  bool bIgnoreDataNotFound = true, 
                  bool bIgnoreUnknAcct = false, 
                  const DString& dstrTrack = I_("N"),
                  const DString& dstrPageName = NULL_STRING);

   SEVERITY init( const BFData& data );
   SEVERITY doCreateObject( const BFData& data, BFCBO *&pObjOut );

   // Business functions
   bool isValidAge( const DString& dstrAge, const DString& dstrJurisdiction, const BFDataGroupId& idDataGroup );
   bool isValidMinimumAge( const DString& dstrAge, const DString& dstrJurisdiction, const BFDataGroupId& idDataGroup );
   bool isValidMaximumAge( const DString& dstrAge, const DString& dstrJurisdiction, const BFDataGroupId& idDataGroup );
   bool isValidMinimumAgeForWithdrawl( const DString& dstrAge, const DString& dstrJurisdiction, const BFDataGroupId& idDataGroup );
   bool isValidPensionJurisdiction( const DString& dstrJurisdiction, const BFDataGroupId& idDataGroup );
   bool canUseSpousesAge( const DString& dstrJurisdiction, const BFDataGroupId& idDataGroup );
   bool getAgeCalcBasedOn(int& ageCalcBasedOn, const DString& dstrJurisdiction, const BFDataGroupId& idDataGroup );


//******************************************************************************
// This method returns the value based on the field id and jurisdiction passed in.
// @param - const BFFieldId& idField - Field Id to returned
//          DString &dstrJurisdiction - Jurisdiction to look for.
//          const BFDataGroupId& idDataGroup - datagroup id.
//******************************************************************************
   DString getJurisLimitField( const BFFieldId& idField, const DString& dstrJurisdiction, 
      const BFDataGroupId& idDataGroup, bool blFormatted = false );

   bool isCarryForwardUnusedMaxApplic( const DString& dstrJurisdiction, 
                                       const BFDataGroupId& idDataGroup );

private:
   DString _strTaxTypeSchedule;

};

///#endif

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/TaxJurisLimitList.hpp-arc  $
//
//   Rev 1.12   Feb 20 2009 14:35:32   jankovii
//IN  1557042 - Accountholder less than 55 but no warning on Desktop and a/c created
//
//   Rev 1.11   Nov 28 2008 13:47:12   jankovii
//PET 142196 FN01 Federal Restricted LIF and LIRA.
//
//   Rev 1.10   Jul 29 2008 14:26:16   daechach
//Appended Revision Control Entries.
*/


