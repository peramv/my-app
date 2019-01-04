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
// ^FILE   : FundBrokerSettlementInstr.hpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : FundBrokerSettlementInstr
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>
#include <ifastcbo\settlementinstr.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE FundBrokerSettlementInstr : public SettlementInstr
{
public:

   FundBrokerSettlementInstr( BFAbstractCBO &parent );
   virtual ~FundBrokerSettlementInstr();
   
protected:

   // virtual void doInitWithDefaultValues( const BFDataGroupId& idDataGroup );
   // SEVERITY doInit();

private:
      
};


//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
