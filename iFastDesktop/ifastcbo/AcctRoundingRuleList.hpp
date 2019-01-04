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
//    Copyright 2008 by IFDS Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : AcctRoundingRuleList.hpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : AcctRoundingRuleList
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

class AcctRoundingRule;

class IFASTCBO_LINKAGE AcctRoundingRuleList : public MFCanBFCbo, private boost::noncopyable
{
public:
    AcctRoundingRuleList( BFAbstractCBO &parent );
    virtual ~AcctRoundingRuleList(void);

    void getStrKey( DString &strKey, const BFData *data = NULL );

    virtual SEVERITY init( const DString &strAccountNumber,
                           const BFDataGroupId& idDataGroup,                           
                           const DString &strTrack     = I_( "N" ),
                           const DString &strPageName  = NULL_STRING
                         );
  
	SEVERITY initNew( const DString &strAccountNumber,
                      const BFDataGroupId& idDataGroup,
                      const DString &strTrack     = I_( "N" ),
                      const DString &strPageName  = NULL_STRING
					);

    SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, 
                            long lValidateGroup );

    SEVERITY getMore();


protected:
    virtual SEVERITY doCreateObject( const BFData& data, BFCBO *&pObjOut );
    virtual SEVERITY doCreateNewObject(BFCBO *&pObjOut, DString &strKey, const BFDataGroupId& idDataGroup );
	SEVERITY validateRoundingRule( const BFDataGroupId &idDataGroup);

private:

    void buildKey( DString &dstrKey, 
                   const DString &dstrAccountNum
                  );

protected:
    BFData m_requestData;
    DString _accountNum;
};

