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
// ^FILE      : BankInstructionsEx.hpp
// ^AUTHOR    : Serban Popescu
// ^DATE      : 01/08/2003
//
// ^CLASS     : BankInstructionsEx
// ^SUBCLASS  :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <boost\utility.hpp>
#include <ifastcbo\mfcancbo.hpp>
#include <ifastdataimpl\dse_dstc0052_vw.hpp>
#include <ifastcbo\bankinstructions.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

//class used in expanding specific non-banking objects (i.e.RRIF), 
//into banking objects
typedef class _bankFieldMappingInfo
{
public:
   const BFFieldId _cboSpecificFieldId;
   const BFFieldId _bankInstructionsFieldId;
   bool _isBankField;

} BANKFIELDMAPPINGINFO, *PBANKFIELDMAPPINGINFO;

class IFASTCBO_LINKAGE BankInstructionsEx : public BankInstructions
{
public:
   BankInstructionsEx(BFAbstractCBO &parent, const DString &dstrBankType,
      const BANKFIELDMAPPINGINFO *pBankFieldMappingInfo, int mappingInfoSize);
   virtual ~BankInstructionsEx();

	SEVERITY initBeforeCloning (const BFDataGroupId &idDataGroup);
   SEVERITY initNew (const BFDataGroupId &idDataGroup, bool cloned = false);
   SEVERITY init (const BFData &parentData, const BFDataGroupId &idDataGroup);
   //copies bank instructions information into specific CBO's
   SEVERITY copyToSpecificCBO(const BFDataGroupId& idDataGroup);      
   virtual SEVERITY setField  (
               const BFFieldId &fieldId,
               const DString& strValue,
               const BFDataGroupId& idDataGroup, 
               bool lFormatted = true,
               bool lSideEffect = false,
               bool bCheckCurrentValue = true);
protected:
   virtual SEVERITY postInit(const BFDataGroupId& idDataGroup);
   virtual void doReset(const BFDataGroupId& idDataGroup);
   virtual SEVERITY doInitBeforeCloning (const BFDataGroupId &idDataGroup) = 0;
   virtual SEVERITY doApplyRelatedChanges( const BFFieldId &idField, 
                                           const BFDataGroupId &idDataGroup);
   virtual SEVERITY doValidateField ( const BFFieldId &idField, 
                                      const DString &strValue, 
                                      const BFDataGroupId &idDataGroup);
   virtual SEVERITY getParentCurrency ( DString &currency,
                                        DString &description,
                                        const BFDataGroupId &idDataGroup) = 0;
   virtual SEVERITY getParentProcessDate ( DString &processDate, 
                                           const BFDataGroupId &idDataGroup) = 0;
   virtual BFAbstractCBO * getParentCBO ();
   virtual SEVERITY doValidateAll (const BFDataGroupId &idDataGroup, long lValidateGroup);
private:
   //methods used in copying info back & forth between the parent object
   //and the bank instructions object for the bank list that do not
   //exist on HOST
   void fromSpecificCBOToBankInstructions ( const BFData &bfData, 
                                            const BANKFIELDMAPPINGINFO *pBankFieldMappingInfo, 
                                            int mappingInfoSize, 
                                            const BFDataGroupId& idDataGroup, 
                                            bool copyOnlyNonBankItems = false);
   void fromSpecificCBOToBankInstructions ( const BFAbstractCBO *bfCBO, 
                                            const BANKFIELDMAPPINGINFO *pBankFieldMappingInfo, 
                                            int mappingInfoSize, 
                                            const BFDataGroupId& idDataGroup, 
                                            bool copyOnlyNonBankItems = false);
   void fromBankInstructionsToSpecificCBO ( BFAbstractCBO *bfCBO, 
                                            const BANKFIELDMAPPINGINFO *pBankFieldMappingInfo, 
                                            int mappingInfoSize, 
                                            const BFDataGroupId& idDataGroup);
   const BANKFIELDMAPPINGINFO *_pCBO_bankFieldMappingInfo;
   DString _dstrBankType;
   int _mappingInfoSize;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/BankInstructionsEx.hpp-arc  $
//
//   Rev 1.11   Mar 08 2010 12:14:26   popescu
//Incident 2039534 - fixed the issue where unverified banking instruction are not copied with the proper value of the verify status field. they get reset to verified, if they are un-verified
//
//   Rev 1.10   Jan 12 2010 15:36:22   jankovii
//IN 1964321 & 1964324 - Static data issues.
//
//   Rev 1.9   09 Mar 2009 11:12:18   kovacsro
//IN#1609264 - PET155543R92 Bank name not display in acct level distrib instruction
//
//   Rev 1.8   Sep 10 2006 17:58:34   popescu
//STP 2192/12
//
//   Rev 1.7   Sep 29 2005 18:57:18   popescu
//Incident# 405610 - added new validation when a bank is cloned. User should not be able to copy a bank if the process date of the transaction (i.e. trade date, systematic effective date), is not between effective date and stop date of the bank instructions record. Also, the process date has to be in the last EFT bank instructions dates range.
//
//   Rev 1.6   Nov 14 2004 14:28:18   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.5   Nov 04 2004 17:37:16   popescu
//PET 1117/06, Trade processing
//
//   Rev 1.4   Sep 23 2004 10:10:04   popescu
//PET 1094 FN4 - Activest Bank File Interface, remove file processor from shareholder banking
//
//   Rev 1.3   Sep 09 2004 13:18:58   popescu
//PET 1094 FN4 - Activest Bank File Interface, before cloning a bank object copy the TransType from the object parent (i.e. Systematic, Distribution) so the file processor values can be retrieved. Made BankInstrucitonEx class pure virtual, so everybody should implement initialization before cloning.
//
//   Rev 1.2   May 04 2004 10:31:18   FENGYONG
//PTS 10029835, settlementtrade banking
//
//   Rev 1.1   Oct 19 2003 16:43:36   popescu
//CIBC, PET809, FN 13 banking work
//
//   Rev 1.0   Oct 04 2003 16:08:38   popescu
//Initial revision.
//
//   Rev 1.2   Jun 18 2003 17:45:04   popescu
//RRIF Banking Enhancement , business rules, bug fixes 
//
//   Rev 1.1   Jun 05 2003 10:42:18   popescu
//business rules work for banking
//
//   Rev 1.0   Jun 03 2003 21:00:56   popescu
//Initial revision.
//
//
 */