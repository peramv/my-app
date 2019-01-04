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
//    Copyright 1997 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : RDRAdvice.hpp
// ^AUTHOR : Shashi Kant
// ^DATE   : July, 2012
//
// ^CLASS    : RDRAdvice
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <SrcPrag.h>
#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE RDRAdvice : public MFCanBFCbo, private boost::noncopyable
{
public:

   RDRAdvice( BFAbstractCBO &parent );
   virtual ~RDRAdvice();
   SEVERITY init( const DString &strAccountNum, 
                  const DString &strFundCode, 
                  const DString &strClassCode, 
                  const DString &strTransType, 
                  const DString &strEffectiveDate, 
                  const DString &dstrBrokerCode, 
				  const DString &dstrBranchCode, 
                  const DString &dstrSalesRepCode);   

};

//*************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/RDRAdvice.hpp-arc  $
//
//   Rev 1.0   Jul 24 2012 13:47:32   wp040027
//Initial revision.
// 
