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
// ^FILE   : FinancialInstitutionTransitList.hpp
// ^AUTHOR : Serban Popescu
// ^DATE   : October, 2003
//
// ^CLASS    : FinancialInstitutionTransitList
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

class FinancialInstitutionTransit;

class IFASTCBO_LINKAGE FinancialInstitutionTransitList : 
   public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   FinancialInstitutionTransitList (BFAbstractCBO &parent,
      bool noDataIsErrorCondition = false);
   virtual ~FinancialInstitutionTransitList (void);

   // Initialize functions
   // for usage see the comments in the implementation file
   SEVERITY initAll (
      const DString &dstrTrack = I_("N"), 
      const DString &dstrPageName = NULL_STRING);
   SEVERITY initAllForName (
      const DString &dstrName,
      const DString &dstrTrack = I_("N"), 
      const DString &dstrPageName = NULL_STRING);
   SEVERITY initForNameCategoryType (
      const DString &dstrCategory, 
      const DString &dstrType, 
      const DString &dstrName,
      const DString &dstrTrack = I_("N"), 
      const DString &dstrPageName = NULL_STRING);
   SEVERITY initForNameCategoryTypeInstitutionCode (
      const DString &dstrCategory, 
      const DString &dstrType, 
      const DString &dstrInstCode, 
      const DString &dstrName,
      const DString &dstrTrack = I_("N"), 
      const DString &dstrPageName = NULL_STRING);
   SEVERITY init (
      const DString &dstrCategory,
      const DString &dstrType,
      const DString &dstrCode,
      const DString &transitCode,
      const DString &dstrTrack = I_("N"), 
      const DString &dstrPageName = NULL_STRING);
   SEVERITY getMore();
   SEVERITY checkDuplicate (
      const FinancialInstitutionTransit *pFinancialInstitutionTransitToCheck,
      const BFDataGroupId &idDataGroup);
protected:
   void getStrKey (DString &strKey, const BFData *data);
   SEVERITY doCreateNewObject (
      BFCBO* &pBase, 
      DString &strKey, 
      const BFDataGroupId &idDataGroup);
   SEVERITY doCreateObject (
      const BFData &data, 
      BFCBO *&pObjOut);
private:
   //builds a unique key for this list
   void buildKey (DString &dstrKey, 
      const DString &dstrBankType,
      const DString &dstrInstCode,
      const DString &dstrTransitNo);
   BFData *_pRequestData;
   DString _transitsCategoryList,
      _category,
      _type,
      _instCode;
   bool _noDataIsErrorCondition;
};


/******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/FinancialInstitutionTransitList.hpp-arc  $
//
//   Rev 1.2   Nov 14 2004 14:41:02   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.1   Jan 12 2004 17:55:18   popescu
//PTS 10020577, added F4 institution search and F4 transit search on banking instriuctions screen, for corresponding edit fields
//
//   Rev 1.0   Oct 24 2003 17:21:20   popescu
//Initial revision.
//
//   Rev 1.0   Oct 04 2003 16:08:46   popescu
//Initial revision.
 
*/