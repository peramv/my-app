#pragma once
//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 1999 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : BrokerAMSList.hpp
// ^AUTHOR : Yongmei Feng
// ^DATE   : Feb 18, 2000
//
//
//******************************************************************************
#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>

class BrokerAMS;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE BrokerAMSList : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   BrokerAMSList( BFAbstractCBO &parent );
   virtual ~BrokerAMSList( void );

   // Initialize function
   SEVERITY init( const DString& dstrBrokerCode, 
                  const DString& dstrAMSCode,  
                  const bool Allresult = false, 
                  const DString& dstrTrack = I_("N"),
                  const DString& dstrPageName = NULL_STRING );

   SEVERITY getMore();
   SEVERITY doCreateObject( const BFData& data, BFCBO*& pObjOut );
   SEVERITY doCreateNewObject(BFCBO*& pBase, DString &strKey, const BFDataGroupId& idDataGroup );
   void buildKey( const DString& strGoodBad,const DString& strAMSCode, DString &strKey );
   void getStrKey (DString &strKey, const BFData *data);
   virtual void getTrackActivity(DString& strTrack,DString& strActivity);
   SEVERITY initExisting(const DString& dstrBrokerCode, 
                            const DString& dstrAMSCode, 
                            const bool Allresult,
							const DString& dstrTrack = I_("N"),
							const DString& dstrPageName = NULL_STRING);

	virtual SEVERITY setField( const BFFieldId& idField, const DString& dstrValue, const BFDataGroupId& idDataGroup, 
                              bool bFormatted = true, bool bSideEffect = false, bool bCheckCurrentValue = true);   
   bool isAMSCodeValid( DString& dstrAMSCode,const BFDataGroupId& idDataGroup, bool bValid0001 ); //public method, will be used by other objects

	SEVERITY getBrokerAMS( const DString &dstrAMSCode, 
		                    const DString &dstrGoodBad,
		                    const BFDataGroupId& idDataGroup,
								  BrokerAMS *&pBrokerAMS );

private:
   BFData _requestData;
   DString _dstrBrokerCode;
   bool isAmsCodeExistAtbackEnd(const DString& dstrAmsCode, const BFDataGroupId& idDataGroup );

};

