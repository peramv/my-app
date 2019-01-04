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
// ^FILE   : SegTrxValidation.hpp
// ^AUTHOR : 
// ^DATE   : Aug, 2010
//
// ^CLASS    : SegTrxValidation
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

class IFASTCBO_LINKAGE SegTrxValidation : public MFCanBFCbo, private boost::noncopyable
{
public:

   SegTrxValidation( BFAbstractCBO &parent );
   virtual ~SegTrxValidation();

   SEVERITY init(const BFData& data);

protected:

private:
                                       
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
// 
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/SegTrxValidation.hpp-arc  $
//
//   Rev 1.0   Sep 17 2010 03:55:20   kitticha
//Initial revision.
//
*/
