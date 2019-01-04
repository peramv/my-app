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
// Copyright 2010 by International Financial Data Services, Inc.
//
//
//******************************************************************************
//
// ^FILE   : RESPTradeValidation.hpp
// ^AUTHOR : 
// ^DATE   : Aprl, 2010
//
// ^CLASS    : RESPTradeValidation
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

class IFASTCBO_LINKAGE RESPTradeValidation : public MFCanBFCbo, private boost::noncopyable
{
public:

   RESPTradeValidation( BFAbstractCBO &parent );
   virtual ~RESPTradeValidation();

   SEVERITY init (const BFData& data );

protected:

private:
                                       
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
// 
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/RESPTradeValidation.hpp-arc  $
//
//   Rev 1.0   Apr 21 2010 23:25:48   dchatcha
//Initial revision.
//
*/
