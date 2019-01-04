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
//    Copyright 2002 by International financial data service.
//
//
//******************************************************************************
//
// ^FILE   : AcctMailingOverrideList.hpp
// ^AUTHOR : 
// ^DATE   : September, 2002
//
// ^CLASS    : AcctMailingOverrideList
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

class IFASTCBO_LINKAGE AcctMailingOverrideList : public MFCanBFCbo, private boost::noncopyable
{
public:

   // X-structors
   AcctMailingOverrideList( BFAbstractCBO &parent );
   virtual ~AcctMailingOverrideList();
   // Initialize function
   SEVERITY init( const DString& dstrAccountNum, 
				  const BFDataGroupId& idDataGroup,
                  const DString& dstrEntityType = I_("01"),
                  const DString& dstrEntityTypeSeq = I_("1"),                  
				  const DString& dstrRequestType = I_("FundGroup"),
                  const DString& dstrTrack = I_("N"),
                  const DString& dstrPageName = NULL_STRING );

   SEVERITY initNew( const DString& accountNum, 
				 const BFDataGroupId& idDataGroup,
                 const DString& entityType = I_("01"),
                 const DString& seqNumber = I_("1") );

   SEVERITY createAllPossibleRecordsInNasu( const BFDataGroupId& idDataGroup );

	virtual void getStrKey( DString &strKey, const BFData *data = NULL );
	virtual void buildKey ( const DString &dstrFundGroup, const DString &dstrDocumentType, DString &strKey);


protected:
   virtual SEVERITY doCreateObject( const BFData& data, BFCBO *&pObjOut );
   virtual SEVERITY doCreateNewObject( BFCBO *&pBase, DString &strKey, const BFDataGroupId& idDataGroup );
   virtual SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup );
  

private:
   DString _strAccountNum;

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//