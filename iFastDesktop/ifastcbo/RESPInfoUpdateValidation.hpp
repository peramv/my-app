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
// ^FILE   : RESPInfoUpdateValidation.hpp
// ^AUTHOR : 
// ^DATE   : Oct, 2010
//
// ^CLASS    : RESPInfoUpdateValidation
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

class IFASTCBO_LINKAGE RESPInfoUpdateValidation : public MFCanBFCbo, private boost::noncopyable
{
public:

   RESPInfoUpdateValidation( BFAbstractCBO &parent );
   virtual ~RESPInfoUpdateValidation();

   SEVERITY init(const BFData& data);
   SEVERITY displayRESPError(const BFDataGroupId &idDataGroup);

protected:

private:
                                       
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
// 
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/RESPInfoUpdateValidation.hpp-arc  $
//
//   Rev 1.1   Nov 23 2010 08:56:16   kitticha
//PET165541_FN03_QESI_Phase3_Non_Finance - revise.
//
//   Rev 1.0   Oct 29 2010 03:55:48   kitticha
//Initial revision.
//
*/
