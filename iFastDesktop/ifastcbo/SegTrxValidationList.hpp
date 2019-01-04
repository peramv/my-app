#pragma once

//******************************************************************************
//
// COPYRIGHT:
//
// The computer systems, procedures, data bases and
// programs created and maintained by International Financial Data Services,
// are proprietary in nature and as such are confIdential.
// Any unauthorized use or disclosure of such information
// may result in civil liabilities.
//
// Copyright 2010 by International Financial Data Services.
//
//
//******************************************************************************
//
// ^FILE   : SegTrxValidationList.hpp
// ^AUTHOR : 
// ^DATE   : Aug, 2010
//
// ^CLASS    : SegTrxValidationList
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

class IFASTCBO_LINKAGE SegTrxValidationList : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   SegTrxValidationList( BFAbstractCBO &parent );
   virtual ~SegTrxValidationList(void);

// Initialize function
   SEVERITY initNew( const BFDataGroupId& idDataGroup );
   SEVERITY init(const DString& strAccountNum,
                 const DString& strFund,
                 const DString& strClass,
                 const DString& strAccountTo,
                 const DString& strFundTo,
                 const DString& strClassTo,
                 const DString& strTransType,
                 const DString& strRedCode,
                 const DString& strTradeAmount,
                 const DString& strDeff,
                 const DString& strSettleDate,
                 const DString& strPUD,
                 const DString& strTransNum,
                 const BFDataGroupId& idDataGroup,
                 const DString& strTrack = I_( "N" ),
                 const DString& strPageName = NULL_STRING);

protected:
   virtual SEVERITY doCreateObject( const BFData& data, BFCBO *&pObjOut );
   virtual SEVERITY doCreateNewObject (BFCBO *& pBase, 
                                       DString &strKey, 
                                       const BFDataGroupId& idDataGroup );

private:

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/SegTrxValidationList.hpp-arc  $
//
//   Rev 1.0   Sep 17 2010 03:56:50   kitticha
//Initial revision.
//
//
