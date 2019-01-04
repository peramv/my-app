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
// ^FILE   : EntityAddressmailingInfo.hpp
// ^AUTHOR : Yingbao Li	
// ^DATE   : September 2002
//
// ^CLASS    : EntityList
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

#include "AcctMailingOverride.hpp"
class IFASTCBO_LINKAGE EntityAddressMailingInfo : public AcctMailingOverride
{

public:
   EntityAddressMailingInfo( BFAbstractCBO &parent );
   virtual ~EntityAddressMailingInfo();

	SEVERITY init( const BFData& InstData );
	SEVERITY init( const BFDataGroupId& idDataGroup );


protected:   

	virtual SEVERITY doValidateField( const BFFieldId& idField,
                                     const DString& strValue,
                                     const BFDataGroupId& idDataGroup );

	virtual void doInitWithDefaultValues( const BFDataGroupId& idDataGroup );

	virtual SEVERITY doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup );

   virtual SEVERITY validateAddrMail(const DString dstrValue,const BFDataGroupId& idDataGroup );
	virtual SEVERITY doDocTypeRelateChange( const BFDataGroupId& idDataGroup );

private:
   EntityAddressMailingInfo( const EntityAddressMailingInfo& copy ); // not implemented
   // = Operator
   EntityAddressMailingInfo& operator=( const EntityAddressMailingInfo& copy );
	void setupSubstituteList(const BFDataGroupId& idDataGroup );
	SEVERITY validateDeliveryOption(const BFDataGroupId& idDataGroup );
	SEVERITY validateHold(const BFFieldId& idField,const BFDataGroupId& idDataGroup );

};

///#endif