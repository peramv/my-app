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
// ^FILE   : GuaranteeSummary.hpp
// ^AUTHOR : Monica Porteanu
// ^DATE   : August 2005
//
// ^CLASS    : GuaranteeSummary
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

class GuaranteeInfoList;

class IFASTCBO_LINKAGE GuaranteeSummary : public MFCanBFCbo, private boost::noncopyable
{
public:
   GuaranteeSummary( BFAbstractCBO &parent );
   virtual ~GuaranteeSummary();
   SEVERITY init( const BFData& data );     
   SEVERITY init( const BFDataGroupId& idDataGroup );     
};

//****************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/GuaranteeSummary.hpp-arc  $
//
//   Rev 1.1   Jun 05 2006 16:51:56   porteanm
//Incident 635750 - Crash when no record available.
//
//   Rev 1.0   Aug 17 2005 16:23:26   porteanm
//Initial revision.
 *  
 */