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
// ^FILE   : MsgProcessCBOList.hpp
// ^CLASS  : MsgProcessCBOList
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE MsgProcessCBOList : public MFCanBFCbo
{
public:

   MsgProcessCBOList( BFAbstractCBO &parent );
   virtual ~MsgProcessCBOList();

      SEVERITY init(             const DString& dstrTrack,
                                 const DString& dstrPageName,
                                 const DString& EnvelopeID,
                                 const DString& TransNum, const DString& AggrOrderNum, 
                                 const DString& ActivityID, const DString& SenderRefNum, 
                                 const DString& NetworkID, const DString& StartDate,
                                 const DString& EndDate, const DString ProcessType, 
                                 const DString& ProcessCategory, const DString& ProcessStatus,
                                 const DString& MsgSearchType
                                 );
   SEVERITY getMore();

protected:

   virtual SEVERITY doCreateObject( const BFData& data, BFCBO*& pObjOut );
//	virtual void  getStrKey( DString &strKey, const BFData *data  );

   BFData m_requestData;
};


//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/MsgProcessCBOList.hpp-arc  $
//
//   Rev 1.1   Apr 06 2005 18:25:42   hernando
//Incident #281643 - Removed getStrKey.
//
//   Rev 1.0   Feb 21 2005 11:14:22   hernando
//Initial revision.
