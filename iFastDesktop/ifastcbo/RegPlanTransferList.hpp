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
//    Copyright 1999 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : RegPlanTransferList.hpp
// ^AUTHOR : Mihai Buzila
// ^DATE   : November 4, 2016
//
// ^CLASS  : RegPlanTransferList
// ^PARENT : MFCanBFCbo
//
// ^CLASS DESCRIPTION :
//  ements a map from the STL to hold fully instantiated BFBase objects
//  that are created from Data objects stored in the inherited ListBase class
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>

//Forward Declarations

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE RegPlanTransferList : public MFCanBFCbo, private boost::noncopyable
{
public:


	RegPlanTransferList( BFAbstractCBO &parent );
	virtual ~RegPlanTransferList();

	// Initialization method
   SEVERITY init( const BFDataGroupId& idDataGroup, const DString& strAccountNumber,
                  const DString& dstrTrack= I_("N"), const DString& dstrPageName = NULL_STRING,
                  const DString& dstrSrchBroker = NULL_STRING, 
                  const DString& dstrSrchBranch = NULL_STRING, 
                  const DString& dstrSrchSlsrep = NULL_STRING, 
                  const DString& dstrSrchExtInst = NULL_STRING, 
                  const DString& dstrSrchExtInstName = NULL_STRING, 
                  const DString& dstrSrchExtInstAcct = NULL_STRING);


	SEVERITY initNew( const DString& strAccountNumber);
	virtual SEVERITY  doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup );
   SEVERITY getNext();
   bool areAllRecordsInactive (const BFDataGroupId& idDataGroup);
   void CopyData(const BFDataGroupId& idDataGroup, const DString &fromKey, const DString &toKey);


protected:
   void getStrKey (DString &strKey, const BFData *data);
   SEVERITY doCreateObject( const BFData& data, BFCBO *&pObjOut );
   SEVERITY doCreateNewObject(BFCBO *& pBase, DString & strKey, const BFDataGroupId& idDataGroup);
   SEVERITY getDataObjectKey( BFData &data, DString &strKey );
   virtual void getStrKeyForNewItem( DString & strKey );

private:

   DString _dstrAccountNum;
   BFData* pRequestData;

};

///#endif
