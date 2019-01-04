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
// ^FILE   : AcctSettlementRuleList.hpp
// ^AUTHOR : Chatchai Daecha
// ^DATE   : Febuary 2008
//
// ^CLASS    : AcctLvlSttlmntRuleList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>

class AcctLvlSttlmntRule;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class AcctLvlSttlmntRule;

class IFASTCBO_LINKAGE AcctLvlSttlmntRuleList : public MFCanBFCbo, private boost::noncopyable
{
public:
    AcctLvlSttlmntRuleList( BFAbstractCBO &parent );
    virtual ~AcctLvlSttlmntRuleList(void);

    void getStrKey( DString &strKey, const BFData *data = NULL );

    virtual SEVERITY init( const DString &strAccountNumber,
                           const BFDataGroupId& idDataGroup,
                           const DString &strRuleType  = NULL_STRING,
                           const DString &strFundCode  = NULL_STRING,
                           const DString &strClassCode = NULL_STRING,
                           const DString &strTrack     = I_( "N" ),
                           const DString &strPageName  = NULL_STRING
                         );

    SEVERITY getAcctLvlSttlmntRule( AcctLvlSttlmntRule *&pAcctLvlSttlmntRule, 
                                    const BFDataGroupId &idDataGroup,
                                    const DString &dstrRuleType,
                                    const DString &dstrFundCode = NULL_STRING,
                                    const DString &dstrClassCode = NULL_STRING,
                                    const DString &dstrEffectiveDate = NULL_STRING,
                                    const DString &dstrStopDate = NULL_STRING,
									const DString &dstrFundGroup = NULL_STRING ); 

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

private:

    void buildKey( DString &dstrKey, 
                   const DString &dstrAccountNum,
                   const DString &dstrRuleType,
                   const DString &dstrFundCode,
                   const DString &dstrClassCode,
                   const DString &dstrEffectiveDate,
				   const DString &dstrStopDate,
				   const DString &dstrFundGroup);

protected:
    BFData m_requestData;
    DString _accountNum;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AcctSettlementRuleList.hpp-arc  $
//
//   Rev 1.3   Apr 16 2008 18:50:04   daechach
//PET2385 FN02&07 - Modified code regarding code review.
//
//   Rev 1.2   28 Mar 2008 12:11:00   kovacsro
//PET2385FN02&07 - some more code cleanup
//
//   Rev 1.1   26 Mar 2008 15:49:00   kovacsro
//PET2385 FN02 - code review
*
*/
