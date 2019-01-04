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
// ^FILE   : TradeAuthorization.hpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : TradeAuthorization
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

class IFASTCBO_LINKAGE TradeAuthorization : public MFCanBFCbo
{
public:

   TradeAuthorization( BFAbstractCBO &parent );
   virtual ~TradeAuthorization();

   SEVERITY init(const BFData& data );
   
   SEVERITY init(const DString &recordType,
	             const DString &transNum,
				 const DString &transId,
				 const DString &authorization,
				 const BFDataGroupId& idDataGroup );

   SEVERITY initNew( const BFDataGroupId& idDataGroup );

protected:

	virtual SEVERITY doValidateField( const BFFieldId& idField, 
		                               const DString& strValue, 
												 const BFDataGroupId& idDataGroup );   
	virtual void doInitWithDefaultValues( const BFDataGroupId& idDataGroup );

private:

	DString	m_dstrPendProcRecordType;
};

/* $Log::   
 */