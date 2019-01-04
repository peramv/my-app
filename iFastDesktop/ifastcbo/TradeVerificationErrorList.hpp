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
// ^FILE   : TradeVerificationErrorList.hpp
// ^AUTHOR : Robbins Kuriakose
// ^DATE   : Aug-2014
//
// ^CLASS    : TradeVerificationErrorList
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

class TradeVerificationError;

class IFASTCBO_LINKAGE TradeVerificationErrorList : public MFCanBFCbo, private boost::noncopyable
{
public:
    TradeVerificationErrorList( BFAbstractCBO &parent );
    virtual ~TradeVerificationErrorList( void );
	bool getTradeVerificationError( DString dstrTransNum, TradeVerificationError*& pTradeVerificationError);
    SEVERITY init (const BFDataGroupId& idDataGroup,
				   const DString& dstrTrack = I_("N"), 
                   const DString& dstrPageName = NULL_STRING );
protected:

	SEVERITY doCreateObject( const BFData& data, BFCBO *&pObjOut );
	static void buildKey (const TradeVerificationError * pTradeVerificationError,  DString& dstrOutKey);
	void getStrKey ( DString& strKey, const BFData* data );	 

private:
    
    BFData   m_respData; 
};
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/TradeVerificationErrorList.hpp-arc  $  

*/