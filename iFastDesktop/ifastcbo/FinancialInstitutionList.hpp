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
// ^FILE   : FinancialInstitutionList.hpp
// ^AUTHOR : Serban Popescu
// ^DATE   : October, 2003
//
// ^CLASS    : FinancialInstitutionList
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

class FinancialInstitution;

class IFASTCBO_LINKAGE FinancialInstitutionList : 
   public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   FinancialInstitutionList (BFAbstractCBO &parent, bool noDataIsErrorCondition = false);
   virtual ~FinancialInstitutionList (void);

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
   SEVERITY init (
      const DString &dstrCategory,
      const DString &dstrType,
      const DString &dstrCode,
      const DString &dstrTrack = I_("N"), 
      const DString &dstrPageName = NULL_STRING);
   SEVERITY getMore();
   SEVERITY checkDuplicate (
      const FinancialInstitution *pFinancialInstitutionToCheck,
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
	  const DString &dstrTransitCode);
   SEVERITY initHelper(
      const DString &dstrSearchType,
      const DString &dstrName,
      const DString &dstrCategory,
      const DString &dstrType,
      const DString &dstrCode,
      const DString &dstrTrack /*= I_("N")*/, 
      const DString &dstrPageName /*= NULL_STRING*/);
   BFData *_pRequestData;
   DString _institutionCategoryList,
         _initCategory, _initType;
   bool _noDataIsErrorCondition;
};


/******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/FinancialInstitutionList.hpp-arc  $
//
//   Rev 1.4   May 12 2005 11:52:42   porteanm
//Incident 265740 - Bank search.
//
//   Rev 1.3   Nov 14 2004 14:40:54   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.2   Oct 27 2003 19:48:42   popescu
//CIBC PET809, FN 13, added Transit Search by name
//
//   Rev 1.1   Oct 24 2003 17:19:38   popescu
//CIBC PET 809, FN 13
//
//   Rev 1.0   Oct 04 2003 16:08:46   popescu
//Initial revision.
 
*/