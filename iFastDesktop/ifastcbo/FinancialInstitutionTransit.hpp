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
//    Copyright 2000 by DST Canada, Inc.
//
//
//******************************************************************************
//
// ^FILE      : FinancialInstitutionTransit.hpp
// ^AUTHOR    : Serban Popescu
// ^DATE      : October 2003
//
// ^CLASS     : FinancialInstitutionTransit
// ^SUBCLASS  :
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

class FinancialInstitutionList;

class IFASTCBO_LINKAGE FinancialInstitutionTransit : public MFCanBFCbo, private boost::noncopyable
{
public:
   //Constructor
   FinancialInstitutionTransit (BFAbstractCBO &parent);
   //Destructor
   virtual ~FinancialInstitutionTransit ();

   SEVERITY init (
      const DString &category, 
      const DString &type, 
      const DString &code, 
      const BFDataGroupId& idDataGroup);
   SEVERITY init (const BFData &viewData);
protected:
   SEVERITY doValidateField (const BFFieldId& idField, 
      const DString& strValue, const BFDataGroupId& idDataGroup);
   SEVERITY doApplyRelatedChanges (const BFFieldId& idField, 
      const BFDataGroupId& idDataGroup);
   void doInitWithDefaultValues (const BFDataGroupId &idDataGroup);
   virtual void doReset (const BFDataGroupId& idDataGroup);
private:
   SEVERITY commonInit (const BFDataGroupId &idDataGroup);
   SEVERITY assignInstCodeLabel (const BFDataGroupId &idDataGroup);
   SEVERITY filterType (const BFDataGroupId &idDataGroup);
   bool _readOnlyTransitsCategory;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/FinancialInstitutionTransit.hpp-arc  $
//
//   Rev 1.2   Nov 14 2004 14:40:58   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.1   Oct 27 2003 19:48:48   popescu
//CIBC PET809, FN 13, added Transit Search by name
//
//   Rev 1.0   Oct 24 2003 17:21:16   popescu
//Initial revision.
//
//   Rev 1.0   Oct 04 2003 16:08:42   popescu
//Initial revision.
 */