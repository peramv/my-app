#pragma once
//*****************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2005 by International Financial Data Services
//
//*****************************************************************************
//
// ^FILE   : GuaranteeDetail.hpp
// ^AUTHOR : Monica Porteanu
// ^DATE   : August 2005
//
// ^CLASS    : GuaranteeDetail
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

class IFASTCBO_LINKAGE GuaranteeDetail : public MFCanBFCbo, private boost::noncopyable
{
public:
   GuaranteeDetail( BFAbstractCBO &parent );
   virtual ~GuaranteeDetail();
   SEVERITY init( const BFData& data );  
};

/* $Log:   Y:/VCS/BF iFAST/ifastcbo/GuaranteeDetail.hpp-arc  $
//
//   Rev 1.0   Aug 17 2005 16:17:10   porteanm
//Initial revision.
 *  
 */