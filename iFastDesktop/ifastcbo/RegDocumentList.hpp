#pragma once

//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2004 by International Financial Data Services.
//
//
//******************************************************************************
//
// ^FILE   : RegDocumentList.hpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : RegDocumentList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class SettlementInstr;
class RegDocumentTypeList;

class IFASTCBO_LINKAGE RegDocumentList : public MFCanBFCbo, private boost::noncopyable
{

public:

   RegDocumentList( BFAbstractCBO &parent );
   virtual ~RegDocumentList();

   SEVERITY init ( const DString& dstrAccountNum, 
	                const DString& dstrEntityId,
	                const DString& dstrRegulatoryStandard,                     
				       const DString& dstrRule,
				       const BFDataGroupId& idDataGroup,
                   const DString& dstrTrack = I_("N"),
                   const DString& dstrPageName = NULL_STRING,
				   bool bAcctRegDocListForDeadEntity = false);

   SEVERITY initNew(const DString& dstrAccountNum,
                                  const DString& dstrEntityId,
                                  const DString& dstrRegulatoryStandard,                     
                                  const DString& dstrRule,
                                  const BFDataGroupId& idDataGroup);

   bool isAnyStatusBlank (const BFDataGroupId &idDataGroup);
   SEVERITY setDummyFlag (const BFDataGroupId &idDataGroup);
   SEVERITY setDefaultStatusForAllRegDocs(const BFDataGroupId &idDataGroup);   
   void getCurrentEntityDetails(const BFDataGroupId &idDataGroup,const DString& dstrEntityID,  DString& dstrEntityTaxJuris , DString& dstrEntityType );
   SEVERITY getMore();

protected:
	virtual SEVERITY doCreateObject( const BFData& data, BFCBO*& pObjOut );
	virtual SEVERITY doCreateNewObject(BFCBO *&pObjOut, DString &strKey, const BFDataGroupId& idDataGroup );
    SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup );
   SEVERITY  forceRegDocStatusUpdatedforNewAccounts(const BFDataGroupId &idDataGroup);  
	BFData m_requestData;

private:
   SEVERITY autoAttachDefaultCRSRegDocs(const BFDataGroupId &idDataGroup,  const DString& dstrEntityID );
   bool isDuplicateDocument( DString& dstrRegDocId, DString& dstrComplyRule, DString& dstrJurisdiction,  DString& dstrEffectiveDate, 
                             DString dstrExpireDate, const BFDataGroupId &idDataGroup );
   bool isEntityTaxJurisdictionUpdated(const BFDataGroupId &idDataGroup );
   SEVERITY getRegDocumentTypeList(const BFDataGroupId &idDataGroup, RegDocumentTypeList *&pRegDocumentTypeList );


};

/* $Log:   Y:/VCS/BF iFAST/ifastcbo/RegDocumentList.hpp-arc  $
//
//   Rev 1.10   Aug 17 2012 19:21:58   wutipong
//IN3058961 P179630FN01 FATCA - Acct Doc List and Tax Exempt Auth screens issues
//
//   Rev 1.9   Jul 23 2012 12:54:16   wutipong
//PETP0179630_FN01 FATCA Account Entity Document Tracking
//
//   Rev 1.8   Dec 09 2008 15:25:02   jankovii
//IN 1498625 - error message s/b add and specified
//
//   Rev 1.7   04 Nov 2008 13:11:50   popescu
//KYC-AML fixes after system integrated testing
//
//   Rev 1.6   31 Oct 2008 16:19:04   popescu
//KYC/AML - joint accounts feature
//
//   Rev 1.5   Oct 28 2008 08:34:08   jankovii
//PET 59888 FN03 AML KYC.
//
//   Rev 1.4   Aug 29 2008 14:35:10   jankovii
//IN 1388930.
//
//   Rev 1.3   Aug 28 2008 14:29:44   jankovii
//IN 1388930 - NASU flow does not update document list unless at least one document.
//
//   Rev 1.2   Aug 01 2008 11:44:26   jankovii
//PET 59888 FN01 AML Enhancement.
 */