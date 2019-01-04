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
//    Copyright 2000 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : FeeInfo.hpp
// ^AUTHOR : 
// ^DATE   : 29/08/2000
//
// ^CLASS    : FeeInfo
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

class IFASTCBO_LINKAGE FeeInfo : public MFCanBFCbo, private boost::noncopyable
{
public:
   //TODO: enter specific field enumerations
   FeeInfo( BFAbstractCBO &parent );
   virtual ~FeeInfo();
   SEVERITY init( const BFData& InstData );
   virtual void getField( const BFFieldId& idField, DString & strValue, const BFDataGroupId& idDataGroup, bool formattedReturn = false ) const;
private:
};

///#endif
