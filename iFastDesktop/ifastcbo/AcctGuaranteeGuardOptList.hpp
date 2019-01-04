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
// ^FILE   : AcctGuaranteeGuardOptList.hpp
// ^AUTHOR : 
// ^DATE   : Aug, 2010
//
// ^CLASS    : AcctGuaranteeGuardOptList
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

class IFASTCBO_LINKAGE AcctGuaranteeGuardOptList : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   AcctGuaranteeGuardOptList( BFAbstractCBO &parent );
   virtual ~AcctGuaranteeGuardOptList(void);

// Initialize function
   SEVERITY initNew( const BFDataGroupId& idDataGroup );
   SEVERITY init( const DString &accountNum,
                  const BFDataGroupId& idDataGroup,
                  const DString &dstrTrack     = I_( "N" ),
                  const DString &dstrPageName  = NULL_STRING);

   SEVERITY getMore();

protected:
   virtual SEVERITY doCreateObject( const BFData& data, BFCBO *&pObjOut );
   virtual SEVERITY doCreateNewObject (BFCBO *& pBase, 
                                       DString &strKey, 
                                       const BFDataGroupId& idDataGroup );

private:
   BFData* requestData412;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/AcctGuaranteeGuardOptList.hpp-arc  $
//
//   Rev 1.0   Sep 17 2010 03:47:48   kitticha
//Initial revision.
//
//
