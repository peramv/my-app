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
// ^FILE   : Advisor List.hpp
// ^AUTHOR : Yongmei Feng
// ^DATE   : Feb 18, 2000
//
// ^CLASS  : AgentList
// ^PARENT : ListBase
//
// ^CLASS DESCRIPTION :
//    Implements View 92.
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

class IFASTCBO_LINKAGE AdvisorList : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   AdvisorList( BFAbstractCBO &parent );
   virtual ~AdvisorList( void );

   // Initialize function
   SEVERITY init( const DString& dstrBrokerCode, 
                  const DString& dstrBranchCode, 
                  const DString& dstrSlsRep, 
                  const DString& Allresult = I_("false"), 
                  const DString& dstrTrack = I_("N"),
                  const DString& dstrPageName = NULL_STRING );

   SEVERITY getMore();
   SEVERITY doCreateObject( const BFData& data, BFCBO*& pObjOut );
   SEVERITY doCreateNewObject(BFCBO*& pBase, DString &strKey, const BFDataGroupId& idDataGroup );
   void buildKey( const DString& strBrokerCode, const DString& strBranchCode, const DString& strSlsRep,DString &strKey );
   void getStrKey (DString &strKey, const BFData *data);
   virtual void getTrackActivity(DString& strTrack,DString& strActivity);
private:
   BFData _requestData;
};

