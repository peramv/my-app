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
// ^FILE   : CotLegalAge.hpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : CotLegalAge
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\trade.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif


class IFASTCBO_LINKAGE CotLegalAge : public MFCanBFCbo
{
public:
   CotLegalAge( BFAbstractCBO &parent );
   virtual ~CotLegalAge();

   SEVERITY init (const DString& dstrContractType, const DString& dstrTaxType, 
	              const DString& dstrProvReg, const DString& dstrEffectiveDate,
				  const DString& dstrTrack= I_("N"),
                  const DString& dstrPageName = NULL_STRING);

protected:
};

