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
//    Copyright 2000 by International Financial Data Services
//
//******************************************************************************
//
// ^FILE   : InterClassSwitch.hpp
// ^AUTHOR : 
// ^DATE   : June 2016
// ^CLASS  : InterClassSwitch
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION : 
//******************************************************************************
#include <ifastcbo\Exchange.hpp>
#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif 

//Forward declarations   
class IFASTCBO_LINKAGE InterClassSwitch : public Exchange
{
public:
   InterClassSwitch (BFAbstractCBO &parent);
   virtual ~InterClassSwitch();        

protected:
   virtual SEVERITY doInit(const BFDataGroupId &idDataGroup);
   virtual SEVERITY doInit(const BFData &datap);
   virtual void doInitWithDefaultValues(const BFDataGroupId &idDataGroup);

private:         
};