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
//    Copyright 1999 by DST Canada, Inc.
//
//
//******************************************************************************
//
// ^FILE   : ChequeList.hpp
// ^AUTHOR : Mihai Virgil Buzila
// ^DATE   : 16/04/99
//
// ^CLASS    : ChequeList
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

class Cheque;

class IFASTCBO_LINKAGE ChequeList : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   ChequeList( BFAbstractCBO &parent );
   virtual ~ChequeList( void );

   // Initialize function
   SEVERITY init( DString& TransId,  
                  DString& AccountNum, 
                  DString& InCheqNum, 
				  DString& Broker, 
                  DString& Status, 
                  bool bIgnoreDataNotFound = true, 
                  bool bIgnoreUnknAcct = false, 
                  const DString& dstrTrack = I_("N"),
                  const DString& dstrPageName = NULL_STRING);  
   SEVERITY init( const BFData& data );

   SEVERITY doCreateObject( const BFData& data, BFCBO *&pObjOut );

   SEVERITY	getMore();
   SEVERITY getCheque( Cheque*& pCheque, const DString& dstrRefNumber, const DString& dstrPrintDate, const BFDataGroupId& idDataGroup );

protected:
	void  getStrKey( DString &strKey, const BFData *data  );


private:
   BFData _requestData;
   void  buildKey( DString &strKey, const DString &strRefNum, const DString &strPrintDate  );


};


