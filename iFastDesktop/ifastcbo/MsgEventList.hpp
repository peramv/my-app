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
//    Copyright 2005, By International Financial Data Service
//
//
//******************************************************************************
//
// ^FILE   : MsgEventList.hpp
// ^CLASS    : MsgEventList
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE MsgEventList : public MFCanBFCbo
{
public:

   MsgEventList( BFAbstractCBO &parent );
   virtual ~MsgEventList();

   SEVERITY initExisting(const DString& dstrTrack = I_("N"),
					          const DString& dstrPageName = NULL_STRING,
                         const DString& dstrActivity = NULL_STRING,
								 const DString& dstrEnvelope = NULL_STRING
                         );

protected:

   virtual SEVERITY doCreateObject( const BFData& data, BFCBO*& pObjOut );
	virtual void  getStrKey( DString &strKey, const BFData *data  );

   BFData m_requestData;
};


//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/MsgEventList.hpp-arc  $
//
//   Rev 1.1   Feb 24 2005 17:33:16   ZHANGCEL
//PET1117- FN66-68 - Added parameter EnvelopeID in function initExist()
//
//   Rev 1.0   Feb 21 2005 11:14:10   hernando
//Initial revision.
