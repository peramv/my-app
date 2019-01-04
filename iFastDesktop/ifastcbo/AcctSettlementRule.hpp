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
//    Copyright 2008 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : AcctSettlementRule.hpp
// ^AUTHOR : Chatchai Daecha
// ^DATE   : Febuary 2008
//
// ^CLASS    : AcctLvlSttlmntRule
// ^INHERITS FROM :           
//
// ^CLASS DESCRIPTION : 
//
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>
#include "AcctSettlementRuleList.hpp"
#include "AcctFundLevelSettleDays.hpp"
///#endif

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class ErrMsgRulesList;
class AcctSettlementRuleDuplicationCheck;
class AcctFundLevelSettleDays;

class IFASTCBO_LINKAGE AcctLvlSttlmntRule : public MFCanBFCbo, private boost::noncopyable
{
public:
    AcctLvlSttlmntRule(BFAbstractCBO &parent);
    virtual ~AcctLvlSttlmntRule(void);
    
    SEVERITY initNew( const DString& accountNum, const BFDataGroupId& idDataGroup );
    SEVERITY init( const BFData& data );

    SEVERITY getErrMsg( DString dstrErrNum, long lErrConditionId, long lWarnConditionId, 
                        const BFDataGroupId& idDataGroup, DString idiStr = NULL_STRING );
                        
    virtual void doInitWithDefaultValues(const BFDataGroupId& idDataGroup);

    void getField( const BFFieldId& idField,DString& strFieldValue,
                   const BFDataGroupId& idDataGroup,
                   bool formattedReturn = false ) const;

    void setFieldsReadOnly( const BFDataGroupId& idDataGroup, bool bReadOnly );

	SEVERITY validateTransTypePendingTrades( const DString &dstrAccountNum,
											 const DString &dstrRuleType,
											 const DString &dstrFundCode,
											 const DString &dstrClassCode,
											 const BFDataGroupId &idDataGroup); 


protected:
    virtual SEVERITY doValidateField( const BFFieldId& idField, const DString& strValue, 
                                        const BFDataGroupId& idDataGroup);
    
    virtual SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup );

    virtual SEVERITY doApplyRelatedChanges ( const BFFieldId &idField, 
                                             const BFDataGroupId &idDataGroup);

    SEVERITY commonInit( const BFDataGroupId &idDataGroup );

    SEVERITY fundClassRelatedChanges( const DString& strFundCode,
                                      const DString& strClassCode,
                                      const BFDataGroupId &idDataGroup );

    SEVERITY validateFundCode ( const DString &strFundCode, 
                                const BFDataGroupId &idDataGroup);

    SEVERITY validateClassCode( const DString& strFundCode,
                                const DString& strClassCode,
                                const BFDataGroupId &idDataGroup );

    SEVERITY validateFundClass( const DString &fundCode, 
                                const DString &classCode, 
                                const DString &accountNum, 
                                const BFDataGroupId &idDataGroup );

    SEVERITY getPurchaseRepInfoFields( DString &dstrBrokerCode, 
                                       DString &dstrBranchCode, 
                                       DString &dstrAgentCode, 
                                       const BFDataGroupId &idDataGroup );

    SEVERITY validateBrokerFund( const DString &dstrBrokerCode,
                                 const DString &dstrTransType,
                                 const DString &dstrAccountNum,
                                 const DString &dstrFundCode, 
                                 const DString &dstrClassCode, 
                                 DString &dstrBrokerPermits,
                                 const BFDataGroupId &idDataGroup );

    SEVERITY validateAgentFund ( const DString &dstrBrokerCode,
                                 const DString &dstrBranchCode,
                                 const DString &dstrAgentCode,
                                 const DString &dstrTransType,
                                 const DString &dstrAccountNum,
                                 const DString &dstrFundCode, 
                                 const DString &dstrClassCode, 
                                 const BFDataGroupId &idDataGroup );

    SEVERITY canFundTrade ( const DString &dstrBrokerCode,
                            const DString &dstrBranchCode,
                            const DString &dstrAgentCode,
                            const DString &dstrTransType,
                            const DString &dstrAccountNum,
                            const DString &dstrFundCode,
                            const DString &dstrClassCode,
                            long lErrorId,
                            long lWarnId,
                            const BFDataGroupId &idDataGroup,
                            bool bCheckBrokerPermits = false );

    bool isBrokerAllowed ( const DString &dstrTransType,
                           const DString &dstrAccountNum,
                           const DString &dstrFundCode, 
                           const DString &dstrClassCode,
                           const BFDataGroupId &idDataGroup );

    bool isAgentAllowed (const BFDataGroupId &idDataGroup);

    SEVERITY isEffectiveBroker( const DString& brokerCode, 
                                const BFDataGroupId& idDataGroup );

    SEVERITY isEffectiveBranches( const DString& branchCode, 
                                  const BFDataGroupId& idDataGroup );

    SEVERITY isEffectiveAgents( const DString& slsrepCode, 
                                const BFDataGroupId& idDataGroup );

    bool isSlsRepByBranch ( const BFDataGroupId& idDataGroup );

    SEVERITY checkDuplicate( const DString &dstrAccountNum,
                             const DString &dstrFundCode,
                             const DString &dstrClassCode,
                             const DString &dstrRuleType,
                             const DString &dstrEffectiveDate,
                             const DString &dstrStopDate,
							 const DString &dstrAcctControlsRID,
							 const DString &dstrFundGroup,
							 const BFDataGroupId& idDataGroup );

    SEVERITY validateRuleFundClass( const DString &dstrFundCode,
                                    const DString &dstrClassCode,
                                    const BFDataGroupId& idDataGroup );

    SEVERITY getDuplicationCheck( AcctSettlementRuleDuplicationCheck *&pDuplicationCheck,
                                  const DString &dstrAccountNum,
                                  const DString &dstrFundCode,
                                  const DString &dstrClassCode,
                                  const DString &dstrRuleType,
                                  const DString &dstrEffectiveDate,
                                  const DString &dstrStopDate,
                                  const DString &dstrAcctControlsRID,
								  const DString &dstrFundGroup,
                                  const BFDataGroupId& idDataGroup);

    bool isNewRecordCheck( const DString &dstrAcctControlsRID );

	SEVERITY validateFundLevelSettleDays(const BFDataGroupId& idDataGroup);
	SEVERITY getFundLevelSettleDays( const DString &dstrAccountNum,
									 const DString &dstrFundCode,
									 const DString &dstrClassCode,
		                             const DString &dstrTransType,
									 const DString &dstrSettleDays,
									 const DString &dstrStartDate,
									 const BFDataGroupId& idDataGroup);

private:
   ErrMsgRulesList* _pErrMsgRulesList;

   DString _dstrAccountNum;             // Account to which the Settlement Rule belong to.
   DString _dstrMultiCurrency;
   DString _dstrCurrentBusinessDate;

   void initSubSets(const BFDataGroupId& idDataGroup);
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AcctSettlementRule.hpp-arc  $
//
//   Rev 1.1   Apr 16 2008 18:48:04   daechach
//PET2385 FN02&07 - Modified code regarding code review.
*
*/
