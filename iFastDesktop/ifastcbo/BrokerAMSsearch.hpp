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
//    Copyright 2002, By International Financial Data Service
//
//
//******************************************************************************
//
// ^FILE   : BrokerAMSsearch.hpp
// ^AUTHOR : 
// ^DATE   : May 24,2002
//
// ^CLASS    : BrokerAMSsearch
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

class BrokerAMSList;


class IFASTCBO_LINKAGE BrokerAMSsearch : public MFCanBFCbo
{
public:
   BrokerAMSsearch( BFAbstractCBO &parent );
   virtual ~BrokerAMSsearch();

   SEVERITY init( const BFDataGroupId& idDataGroup,
      const DString& dstrTrack = I_("N"), 
      const DString& dstrPageName = NULL_STRING);
   SEVERITY getBrokerAMSList( BrokerAMSList*& pBrokerAMSlist,const BFDataGroupId& idDataGroup,bool bInq = true,bool bRemObj = true );
   SEVERITY BrokerAMSsearch::getBrokerAMSList( BrokerAMSList*& pBrokerAMSlist, 
                                             const BFDataGroupId& idDataGroup,DString dstrBrokerCode, DString dstrAMSCode = NULL_STRING);
protected:

   virtual SEVERITY doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup );
   //virtual SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup );
   virtual SEVERITY doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup );
   virtual SEVERITY setField( const BFFieldId& idField,
                              const DString& strValue,
                              const BFDataGroupId& idDataGroup, 
                              bool  lFormatted = true,
                              bool  lSideEffect = false,
                              bool  bCheckCurrentValue = true);
   SEVERITY BrokerCodeRelatedChanges( const BFDataGroupId& idDataGroup );
private:

   SEVERITY validateBrokerCode( const DString& dstrValue,  const BFDataGroupId& idDataGroup  );
   SEVERITY validateAMSCode(const DString& dstrValue, const BFDataGroupId& idDataGroup);
   // copy constructor
   BrokerAMSsearch( const BrokerAMSsearch& copy ); //not implemented
   // = Operator
   BrokerAMSsearch& operator= ( const BrokerAMSsearch& copy );//not implemented
};


//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
//



//
