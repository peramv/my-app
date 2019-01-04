#pragma once
#define DISABLE_MACRO_REDEFINITION_WARNINGS 1
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
//    Copyright 1999 by DST Canada, Inc.
//
//
//******************************************************************************
//
// ^FILE   : TradeOverideRuleWarningsList.hpp
// ^AUTHOR : Robbins Kuriakose
// ^DATE   : Aug-2014
//
// ^CLASS    : TradeOverideRuleWarningsList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :	Used to get the defualt values for multiple keys
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

class IFASTCBO_LINKAGE TradeOverideRuleWarningsList : public MFCanBFCbo, private boost::noncopyable
{
public:
    TradeOverideRuleWarningsList( BFAbstractCBO &parent );
    virtual ~TradeOverideRuleWarningsList( void );
    SEVERITY init (const BFDataGroupId& idDataGroup,
				   const DString& dstrTrack = I_("N"), 
                   const DString& dstrPageName = NULL_STRING );
    void buildErrorMessage(DString& dstrErrorMessage, const BFDataGroupId& idDataGroup);
    SEVERITY init( DString dstrTransNum, const BFDataGroupId& idDataGroup = BF::HOST, bool bCreate = true );
    void  getTransNum ( DString& dstrTransNum){ dstrTransNum = m_dstrTransNum ; }
    void  setTransNum (  DString& dstrTransNum) { m_dstrTransNum = dstrTransNum; }

protected:

	SEVERITY doCreateObject( const BFData& data, BFCBO *&pObjOut );
	//static void buildKey (const TradeVerificationError * pTradeVerificationError,  DString& dstrOutKey);
	void getStrKey ( DString& strKey, const BFData* data );	 

private:
    
    BFData _requestData;
    DString m_dstrTrack;
    DString m_dstrPageName;
    DString m_dstrTransNum;
};
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/TradeOverideRuleWarningsList.hpp-arc  $  

*/