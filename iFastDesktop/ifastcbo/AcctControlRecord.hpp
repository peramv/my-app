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
//    Copyright 2010 by IFDS Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : AcctControlRecord.hpp
// ^AUTHOR : 
// ^DATE   : Dec 2010
//
// ^CLASS    : AcctControlRecord
// ^INHERITS FROM :           
//
// ^CLASS DESCRIPTION : 
//
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

class IFASTCBO_LINKAGE AcctControlRecord : public MFCanBFCbo, private boost::noncopyable
{
public:
    AcctControlRecord(BFAbstractCBO &parent);
    virtual ~AcctControlRecord(void);
    
    SEVERITY initNew( const DString& accountNum, const BFDataGroupId& idDataGroup );
    SEVERITY init( const BFData& data );

protected:

private:

   DString _dstrAccountNum;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
// $Log:   Y:/VCS/BF iFAST/ifastcbo/AcctControlRecord.hpp-arc  $
//
//   Rev 1.1   Feb 01 2011 10:06:52   dchatcha
//P0179308 FN01 - Multi Manager Subscription and Direct Debit Payment, take out getErrMsg, due to no need to override this method.
//
//   Rev 1.0   Jan 31 2011 14:09:46   dchatcha
//Initial revision.
//