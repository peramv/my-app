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
// ^FILE   : AcctRoundingRule.hpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS  : AcctRoundingRule
// ^INHERITS FROM :           
//
// ^CLASS DESCRIPTION : 
//
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>
#include "AcctRoundingRuleList.hpp"
///#endif

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class ErrMsgRulesList;

class IFASTCBO_LINKAGE AcctRoundingRule : public MFCanBFCbo, private boost::noncopyable
{
public:
    AcctRoundingRule(BFAbstractCBO &parent);
    virtual ~AcctRoundingRule(void);
    
    SEVERITY initNew( const DString& accountNum, const BFDataGroupId& idDataGroup );
    SEVERITY init( const BFData& data );

    SEVERITY getErrMsg( DString dstrErrNum, long lErrConditionId, long lWarnConditionId, 
                        const BFDataGroupId& idDataGroup, DString idiStr = NULL_STRING );
                        
    virtual void doInitWithDefaultValues(const BFDataGroupId& idDataGroup);

    void getField( const BFFieldId& idField,DString& strFieldValue,
                   const BFDataGroupId& idDataGroup,
                   bool formattedReturn = false ) const;   

	SEVERITY validateAccountRoundingRule( const BFDataGroupId &idDataGroup );

	SEVERITY validatePendingOrProcessedTrades( const DString &dstrAccountNum,
											   const BFDataGroupId &idDataGroup); 

protected:
    virtual SEVERITY doValidateField( const BFFieldId& idField, const DString& strValue, 
                                      const BFDataGroupId& idDataGroup);
    
    virtual SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup );

    virtual SEVERITY doApplyRelatedChanges ( const BFFieldId &idField, 
                                             const BFDataGroupId &idDataGroup);

    SEVERITY commonInit( const BFDataGroupId &idDataGroup );           

private:
   ErrMsgRulesList* _pErrMsgRulesList;

   DString _dstrAccountNum;
   DString _dstrCurrentBusinessDate;

   SEVERITY addBlankToSubSet(const BFFieldId &idField ,const BFDataGroupId &idDataGroup, bool dstrUseNotApplicableAsDesc = false );
};

