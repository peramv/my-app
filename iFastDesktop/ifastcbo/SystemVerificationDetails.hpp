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
// Copyright 2009 by International Financial Data Services, Inc.
//
//
//******************************************************************************
//
// ^FILE   : SystemVerificationDetails.hpp
// ^AUTHOR : 
// ^DATE   : Nov, 2009
//
// ^CLASS    : SystemVerificationDetails
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

class IFASTCBO_LINKAGE SystemVerificationDetails : public MFCanBFCbo, private boost::noncopyable
{
public:

   SystemVerificationDetails( BFAbstractCBO &parent );
   virtual ~SystemVerificationDetails();

   SEVERITY init( );
   SEVERITY init( const BFData& data );
                     
protected:

private:
//helpers
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
// 
// $Log:   Y:/VCS/BF iFAST/ifastcbo/SystemVerificationDetails.hpp-arc  $
//
//   Rev 1.0   Nov 16 2009 06:15:04   dchatcha
//Initial revision.
//
