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
//    Copyright 2004 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : BrokerRemark.hpp
// ^AUTHOR : Yingbao  Li
// ^DATE   : 
//
// ^CLASS    : BrokerRemark
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

class IFASTCBO_LINKAGE BrokerRemark : public MFCanBFCbo, private boost::noncopyable
{
public:


   BrokerRemark( BFAbstractCBO &parent );
   virtual ~BrokerRemark();
   SEVERITY init( const BFData& InstData );
	SEVERITY initNew( const BFDataGroupId& idDataGroup );
 
protected:

	virtual void doInitWithDefaultValues( const BFDataGroupId& idDataGroup );
   virtual SEVERITY doValidateField( const BFFieldId& idField,
                                   const DString& strValue,
                                   const BFDataGroupId& idDataGroup );


private:



 
};

