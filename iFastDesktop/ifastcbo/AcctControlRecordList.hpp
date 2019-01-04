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
// ^FILE   : AcctControlRecordList.hpp
// ^AUTHOR : 
// ^DATE   : Dec 2010
//
// ^CLASS    : AcctControlRecordList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>

class AcctControlRecord;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class AcctControlRecord;

class IFASTCBO_LINKAGE AcctControlRecordList : public MFCanBFCbo, private boost::noncopyable
{
public:
    AcctControlRecordList( BFAbstractCBO &parent );
    virtual ~AcctControlRecordList(void);

    virtual SEVERITY init( const DString &strAccountNumber,
                           const BFDataGroupId& idDataGroup,
                           const DString &strEffectiveDate,
                           const DString &strStopDate,
						   const DString &strInquiryType,
                           const DString &strRuleType  = NULL_STRING,
                           const DString &strFundCode  = NULL_STRING,
                           const DString &strClassCode = NULL_STRING,
                           const DString &strTrack     = I_( "N" ),
                           const DString &strPageName  = NULL_STRING );

    SEVERITY getMore();

protected:
    virtual SEVERITY doCreateObject( const BFData& data, BFCBO *&pObjOut );

private:

protected:
    BFData m_requestData;
    DString _accountNum;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
// $Log:   Y:/VCS/BF iFAST/ifastcbo/AcctControlRecordList.hpp-arc  $
//
//   Rev 1.0   Jan 31 2011 14:09:00   dchatcha
//Initial revision.
//