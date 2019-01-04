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
// ^FILE   : Broker.hpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : 29/08/2000
//
// ^CLASS    : Broker
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************



#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>

class NomineeInterAddrList;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE Broker : public MFCanBFCbo, private boost::noncopyable
{
public:
   //TODO: enter specific field enumerations
   enum FIELD
   {
      UNUSED_FIELD,
      MAX_FIELDS
   };

   //TODO: enter specific contained object enumerations
   enum OBJECT
   {
      UNUSED_OBJECT,
      MAX_OBJECTS
   };

   Broker( BFAbstractCBO &parent );
   virtual ~Broker();
   void doPopulateField( const BFFieldId& idField, DString & strValue, bool formattedReturn );
   SEVERITY getNomineeInterAddressList( const BFDataGroupId& idDataGroup, NomineeInterAddrList *&pNomInterAddressList);
   SEVERITY init( const BFData& InstData );
   SEVERITY init( const DString& strBrokerCode, bool bForceViewCall = false );
   SEVERITY checkEffective( const DString& dstrAsOfDate, const BFDataGroupId& idDataGroup );
   bool isHouseBroker( const BFDataGroupId& idDataGroup );

private:

   void getResponseData(BFData*& pResponse);
   BFData* _pResponseData;

};

