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
// ^FILE   : FinancialInstitutionListRepository.hpp
// ^AUTHOR : Serban Popescu
// ^DATE   : October, 2003
//
// ^CLASS    : FinancialInstitutionListRepository
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <boost\utility.hpp>
#include <ifastcbo\mfcancbo.hpp>


class FinancialInstitutionList;
class FinancialInstitutionTransitList;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE FinancialInstitutionListRepository : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   FinancialInstitutionListRepository (BFAbstractCBO &parent);
   virtual ~FinancialInstitutionListRepository();

   // Initialize function
   SEVERITY init (const BFDataGroupId &idDataGroup = BF::HOST, 
      const DString& dstrTrack = I_("N"), 
      const DString& dstrPageName = NULL_STRING);
//this method is used to search for all institutions
   SEVERITY getFinancialInstitutionList(
      FinancialInstitutionList *&pFinancialInstitutionList, 
      const BFDataGroupId &idDataGroup, 
      const DString& dstrTrack = I_("N"), 
      const DString& dstrPageName = NULL_STRING);
   SEVERITY getFinancialInstitutionList(
      const DString &dstrName,
      FinancialInstitutionList *&pFinancialInstitutionList, 
      const BFDataGroupId &idDataGroup, 
      const DString& dstrTrack = I_("N"), 
      const DString& dstrPageName = NULL_STRING);
   SEVERITY getFinancialInstitutionList(
      const DString &dstrCategory,
      const DString &dstrType,
      const DString &dstrCode,
      FinancialInstitutionList *&pFinancialInstitutionList, 
      const BFDataGroupId &idDataGroup, 
      const DString& dstrTrack = I_("N"), 
      const DString& dstrPageName = NULL_STRING);
//this method is used to search for all transits
   SEVERITY getTransits (
      FinancialInstitutionTransitList *&pFinancialInstitutionTransitList, 
      const BFDataGroupId &idDataGroup, 
      const DString& dstrTrack = I_("N"), 
      const DString& dstrPageName = NULL_STRING);
   SEVERITY getTransits (
      const DString &dstrName,
      FinancialInstitutionTransitList *&pFinancialInstitutionTransitList, 
      const BFDataGroupId &idDataGroup, 
      const DString& dstrTrack = I_("N"), 
      const DString& dstrPageName = NULL_STRING);
   SEVERITY getTransits (
      const DString &category,
      const DString &bankIdType, 
      const DString &bankIdNum,
      FinancialInstitutionTransitList *&pFinancialInstitutionTransitList,
      const BFDataGroupId &idDataGroup,
      const DString& dstrTrack = I_("N"), 
      const DString& dstrPageName = NULL_STRING);
private:
   void buildFIKey (DString &dstrKey);
   void buildFITKey (DString &dstrKey);
   void buildFITKey (DString &dstrKey, 
      const DString &dstrCategory, const DString &dstrBankType, 
      const DString &dstrInstCode);
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/FinancialInstitutionListRepository.hpp-arc  $
//
//   Rev 1.3   Nov 14 2004 14:40:56   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.2   Oct 27 2003 19:48:44   popescu
//CIBC PET809, FN 13, added Transit Search by name
//
//   Rev 1.1   Oct 24 2003 17:19:42   popescu
//CIBC PET 809, FN 13
//
//   Rev 1.0   Oct 04 2003 16:08:48   popescu
//Initial revision.
//
 */
