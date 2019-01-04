#pragma once

//******************************************************************************
//
// COPYRIGHT:
//
// The computer systems, procedures, data bases and
// programs created and maintained by International Financial Data Services, Inc.,
// are proprietary in nature and as such are confIdential.
// Any unauthorized use or disclosure of such information
// may result in civil liabilities.
//
// Copyright 2012 by International Financial Data Services, Inc.
//
//
//******************************************************************************
//
// ^FILE   : EventCommissionInq.hpp
// ^AUTHOR : 
// ^DATE   : Aug, 2012
//
// ^CLASS    : EventCommissionInq
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <boost\utility.hpp>
#include <ifastcbo\mfcancbo.hpp>


#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE EventCommissionInq : public MFCanBFCbo, private boost::noncopyable
{
public:

   EventCommissionInq( BFAbstractCBO &parent );
   virtual ~EventCommissionInq();

   SEVERITY init (const DString& acctNum,
                  const DString& acctTo,
                  const DString& redCode,
                  const BFDataGroupId& idDataGroup);

protected:

private:

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
// 
// $Log:   Y:/VCS/BF iFAST/ifastcbo/EventCommissionInq.hpp-arc  $
//
//   Rev 1.0   Aug 15 2012 14:59:28   dchatcha
//Initial revision.
//
