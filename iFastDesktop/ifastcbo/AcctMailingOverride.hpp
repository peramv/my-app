#pragma once
#define DISABLE_MACRO_REDEFINITION_WARNINGS 1




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
//    Copyright 2002 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : AcctMailingOverride.hpp
// ^AUTHOR : 
// ^DATE   : September 2002
//
// ^CLASS    : AcctMailingOverride
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

class IFASTCBO_LINKAGE AcctMailingOverride : public MFCanBFCbo, private boost::noncopyable
{

public:
   AcctMailingOverride( BFAbstractCBO &parent );
   virtual ~AcctMailingOverride();

	SEVERITY init( const BFData& InstData );
	SEVERITY init( const BFDataGroupId& idDataGroup );
   void   setObjectAsUpdated(const DString& docType, 
                                               const DString& fundGroup,  
                                               const BFDataGroupId& idDataGroup );

protected:   

	virtual SEVERITY doValidateField( const BFFieldId& idField,
                                     const DString& strValue,
                                     const BFDataGroupId& idDataGroup );

	virtual void doInitWithDefaultValues( const BFDataGroupId& idDataGroup );

	virtual SEVERITY doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup );

	virtual SEVERITY validateAddrMail(const DString dstrValue,const BFDataGroupId& idDataGroup );
 
	virtual SEVERITY doDocTypeRelateChange( const BFDataGroupId& idDataGroup );

	virtual SEVERITY doValidateAll( const BFDataGroupId &idDataGroup, 
                                    long lValidateGroup);

   void   setEntityId(const DString& entityID );
   DString& getEntityId();
   void setMailingFieldsReadonly(const BFDataGroupId& idDataGroup);
   void setupAuthorizationList( const BFDataGroupId& idDataGroup );
   SEVERITY setDefaultHoldFlag( const BFDataGroupId& idDataGroup );

private:
   AcctMailingOverride( const AcctMailingOverride& copy ); // not i,plemented
   // = Operator
   AcctMailingOverride& operator=( const AcctMailingOverride& copy );
	SEVERITY validateDeliveryOption(const BFDataGroupId& idDataGroup );
	SEVERITY validateHold(const BFFieldId& idField,const BFDataGroupId& idDataGroup );   
   SEVERITY holdRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup );
   SEVERITY authorizRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup );
	SEVERITY validateFax(const DString dstrValue,const BFDataGroupId& idDataGroup );
	SEVERITY validateEmail(const DString dstrValue,const BFDataGroupId& idDataGroup );
	void setupSubstituteList(const BFDataGroupId& idDataGroup );
   SEVERITY validateAuthHold( const BFDataGroupId& idDataGroup );

	DString _entityID;
};

///#endif