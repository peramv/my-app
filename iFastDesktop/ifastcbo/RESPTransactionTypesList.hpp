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
//
//******************************************************************************
//
// ^FILE   : RESPTransactionTypesList.hpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : RESPTransactionTypesList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION : The associated accounts for the selected entity
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

//Forward declarations
class WhereUsed;

class IFASTCBO_LINKAGE RESPTransactionTypesList : public MFCanBFCbo, private boost::noncopyable
{
public:
   RESPTransactionTypesList( BFAbstractCBO &parent );

   virtual ~RESPTransactionTypesList();

   SEVERITY init( const DString& dstrAccountNum,
			      const DString& dstrTransId,
				  const DString& dstrHistoryPending,
                  const DString& dstrTrack= I_("N"),
                  const DString& dstrPageName = NULL_STRING);

   SEVERITY init( const BFData& data );

   void getSubstitionList(DString& transTypeSubList, const BFDataGroupId& idDataGroup);
   SEVERITY getTransTypeInfo(const DString& dstrTransId, 
						     DString &dstrTransType,
						     DString &dstrRedCode,
						     DString &dstrDepositType,
						     const BFDataGroupId& idDataGroup);

   void getDescStatHRDCInfo (DString& transTypeDesc,
				             DString& transferStatus,
				             DString& repHRDC,
				             const BFDataGroupId& idDataGroup);


   SEVERITY isTransferStatusApplicable (const DString& dstrTransId, 
						                DString &dstrApplicable,
										const BFDataGroupId& idDataGroup);


protected:
   virtual SEVERITY doCreateObject(const BFData& data, BFCBO *&pObjOut);
   virtual SEVERITY doCreateNewObject(BFCBO *& pBase, DString & strKey, const BFDataGroupId& idDataGroup );


private:
 
   BFData	_requestData;
};

