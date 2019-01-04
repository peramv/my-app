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
//    Copyright 2004, By International Financial Data Service
//
//
//******************************************************************************
//
// ^FILE   : RegDocument.hpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : RegDocument
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

class RegDocumentTypeList;

class IFASTCBO_LINKAGE RegDocument : public MFCanBFCbo
{
public:

   RegDocument( BFAbstractCBO &parent );
   virtual ~RegDocument();

   SEVERITY init( const BFData& data );
   SEVERITY init(const BFDataGroupId& idDataGroup );
   SEVERITY initNew( const BFDataGroupId& idDataGroup );

   bool isTaxExempAuthUpdateNeeded(const BFDataGroupId& idDataGroup );
   bool isTaxImpactTaxPayerStatus(const BFDataGroupId& idDataGroup );  
   SEVERITY getRegDocumentTypeList(const BFDataGroupId &idDataGroup, RegDocumentTypeList *&pRegDocumentTypeList, const DString &complyRules = NULL_STRING);
      
protected:

	virtual SEVERITY doValidateField( const BFFieldId& idField, 
		                               const DString& strValue, 
												 const BFDataGroupId& idDataGroup );   
	virtual void doInitWithDefaultValues( const BFDataGroupId& idDataGroup );
	virtual SEVERITY doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup );

	SEVERITY commInit (const BFDataGroupId& idDataGroup);
	SEVERITY setDocIdSubstitution(const BFDataGroupId& idDataGroup);
	virtual SEVERITY doValidateAll(const BFDataGroupId &idDataGroup, long lValidateGroup);
   
private:
    
};

/* $Log:   Y:/VCS/BF iFAST/ifastcbo/RegDocument.hpp-arc  $
//
//   Rev 1.3   Aug 17 2012 19:21:46   wutipong
//IN3058961 P179630FN01 FATCA - Acct Doc List and Tax Exempt Auth screens issues
//
//   Rev 1.2   Aug 01 2008 09:28:20   jankovii
//PET 59888 FN01 AML Enhancement.
 */