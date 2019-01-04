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
//    Copyright 2014 by International Financial Data Services
//
//
//******************************************************************************
//
// ^FILE   : SEGFundValidationRules.hpp
// ^AUTHOR : 
// ^DATE   : Aug 2014
//
// ^CLASS    : 
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>
///#endif

#include <ifastdataimpl\dse_dstc0420_req.hpp>
#include <ifastdataimpl\dse_dstc0420_vw.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
#define IFASTCBO_LINKAGE CLASS_EXPORT
#else
#define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE SEGFundValidationRules : public MFCanBFCbo, private boost::noncopyable
{
public:
   SEGFundValidationRules( BFAbstractCBO &parent );
   virtual ~SEGFundValidationRules();
                                    
   SEVERITY init( const DString &strAccountNum,
                  const DString &fundCode,
                  const DString &classCode,
                  const DString &strEventTransType,
                  const DString &strContractType,
                  const DString &dstrContractTypeId,
                  const DString &strEffectiveDate,
                  const DString &dstrTrack = I_( "N" ),
                  const DString &dstrPageName = NULL_STRING);
protected:

private:

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
// $Log:   Y:/VCS/BF iFAST/ifastcbo/SEGFundValidationRules.hpp-arc  $
//
