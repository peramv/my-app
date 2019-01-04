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
//    Copyright 1999 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : Demographics.hpp
// ^AUTHOR : Yakov Prager
// ^DATE   : 2/23/1999
//
// ^CLASS    : Demographics
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
class ErrMsgRulesList;
class RegulatoryStandardList;
class DefaultRegulatoryStandard;
class DemographicsChildList;

class IFASTCBO_LINKAGE Demographics : public MFCanBFCbo, private boost::noncopyable
{
public:
   Demographics( BFAbstractCBO &parent );
   virtual ~Demographics();

   SEVERITY initNew(const DString& accountNum, const BFDataGroupId& idDataGroup = BF::HOST);

   SEVERITY init( const DString& accountNum, 
                  const DString& entityId, 
                  const BFDataGroupId& idDataGroup = BF::HOST, 
                  const DString& dstrTrack = I_("N"),
                  const DString& dstrPageName = NULL_STRING );

   SEVERITY SetMandatoryField(const BFDataGroupId& idDataGroup);
   SEVERITY getErrMsg( DString dstrErrNum, long lErrConditionId, long lWarnConditionId, 
                       const BFDataGroupId& idDataGroup, DString idiStr = NULL_STRING );
   virtual void doInitWithDefaultValues(const BFDataGroupId& idDataGroup);
   SEVERITY getDemographicsChildList(DemographicsChildList*& pDemographicsChildList,
                                     //const DString& dstrAccountNum,
                                     //const DString& dstrEntityId,
                                     const BFDataGroupId& idDataGroup);

protected:
   virtual SEVERITY doValidateField( const BFFieldId& idField, const DString& strValue, 
                                     const BFDataGroupId& idDataGroup);
   SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup );
   SEVERITY fieldIsBlank( DString fieldName, const BFDataGroupId& idDataGroup );
   bool     isShareHolderLevelKYC(const BFDataGroupId& idDataGroup);
   virtual  SEVERITY doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup );

   SEVERITY getRegulatoryStandardsList ( RegulatoryStandardList*& pRegulatoryStandardList, 
                                         const DString& dstrTypeOfInvestor,
                                         const DString& dstrInvsetOnBehalf,
                                         const DString& dstrAcctEffDate,
                                         const BFDataGroupId& idDataGroup );

   SEVERITY getDefaultRegulatoryStandard(DefaultRegulatoryStandard *&pDefaultRegulatoryStandard,
                                         const BFDataGroupId &idDataGroup);

   virtual void doReset( const BFDataGroupId& idDataGroup );

   SEVERITY loadSourceOfPayment(const BFDataGroupId &idDataGroup);
   SEVERITY updateSourceOfPayment(const DString& code, 
                                  const DString& status,
                                  const DString& desc,
                                  const BFDataGroupId &idDataGroup);

private:
   SEVERITY validateBranch( const DString& dstrBranchCode, const BFDataGroupId& idDataGroup );
   SEVERITY validateSlsRep( const DString& dstrSlsRepCode, const BFDataGroupId& idDataGroup );
   void setupHouseBroker( const BFDataGroupId& idDataGroup );
   SEVERITY setFieldsForValidation( const BFDataGroupId& idDataGroup );
   SEVERITY setFieldsReadOnlyForShrLevel( const BFDataGroupId& idDataGroup );
   SEVERITY getRegulatoryStandards( const DString& tyoeOfInvestor, const DString& investingOnBehalf, 
                                    const DString& dstrAcctEffDate,
                                    const BFDataGroupId& idDataGroup );
   SEVERITY validateRegDocsStatus (const BFDataGroupId& idDataGroup);
   SEVERITY initKYCIndustrySubstitutionList(const BFDataGroupId &idDataGroup);
   SEVERITY initKYCOccupationSubstitutionList(const BFDataGroupId &idDataGroup);
   SEVERITY initKYCBusinessTypeSubstitutionList(const BFDataGroupId &idDataGroup);
   SEVERITY initKYCLegalFormSubstitutionList(const BFDataGroupId &idDataGroup);
   void removeInactiveOccupationsFromSublist(const BFDataGroupId &idDataGroup);
   void removeInactiveBusinessTypeFromSublist(const BFDataGroupId &idDataGroup);
   SEVERITY commonInit(const BFDataGroupId &idDataGroup);

   DString _initEffectiveDate;
   ErrMsgRulesList* _pErrMsgRulesList;
   DString _dstrAccountNum; // Account to which the demographics belong to.
   RegulatoryStandardList* pRegulatoryStandardList;
   DString _dstrResidenceCode; 
   bool _bRegStandardExist;

   std::map<BFFieldId,DString> _fieldRecordMap;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/Demographics.hpp-arc  $
 * 
 *    Rev 1.23   Oct 17 2011 03:25:02   kitticha
 * PETP0186486 FN14 IN2698689 - KYC Risk Tolerance issues.
 * 
 *    Rev 1.22   Sep 12 2008 06:24:24   daechach
 * PET0128026 - KYC Phase 2
 * 
 *    Rev 1.21   Aug 28 2008 14:30:10   jankovii
 * IN 1388930 - NASU flow does not update document list unless at least one document.
 * 
 *    Rev 1.20   Jul 25 2008 14:30:42   jankovii
 * PET 59888 - AML Enhancement.
 * 
 *    Rev 1.19   Jul 16 2008 16:05:12   jankovii
 * PET 59888 - AML Enhancement.
 * 
 *    Rev 1.18   Feb 08 2008 10:33:16   daechach
 * in# 1148522 - No value on Specialty Code in iFast - Strip leading zero of KYCLevel.
 * 
 *    Rev 1.17   Aug 06 2007 16:17:46   kovacsro
 * PET2372 FN02 - FDP-AIM KYC
 * 
 *    Rev 1.16   Jul 27 2007 16:52:34   kovacsro
 * PET 2372 FN02 FDP-AIM KYC - added fieldIsBlank
 * 
 *    Rev 1.15   Nov 14 2004 14:30:38   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.14   Jan 19 2004 13:54:22   FENGYONG
 * PTS 10024375, Add dovalidateall function 
 * 
 *    Rev 1.13   Sep 18 2003 14:15:38   FENGYONG
 * Change the parameter tax from shrNum to AccountNum
 * 
 *    Rev 1.12   Aug 19 2003 15:55:20   HSUCHIN
 * added branchcode/agent code fields/validation
*/