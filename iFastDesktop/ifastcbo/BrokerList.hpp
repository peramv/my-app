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
// ^FILE   : BrokerList.hpp
// ^AUTHOR : Yakov Prager
// ^DATE   : November 07, 1999
//
// ^CLASS  : BrokerList
// ^PARENT : ListBase
//
// ^CLASS DESCRIPTION :
//    Implements View 90.
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

class Broker;

class IFASTCBO_LINKAGE BrokerList : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   BrokerList( BFAbstractCBO &parent );
   virtual ~BrokerList( void );

   SEVERITY doCreateObject( const BFData& data, BFCBO*& pObjOut );
   SEVERITY getBroker(DString strBrokerCode, Broker*& pBroker);
   void getStrKey( DString &strKey, const BFData *data );
   SEVERITY getMore();

  SEVERITY init(const BFDataGroupId& idDataGroup, 
      const DString& dstrTrack = I_("N"), 
      const DString& dstrPageName = NULL_STRING);
   // Initialize function
   SEVERITY init( const DString& dstrBrokerCode, 
                  const DString& dstrSrchBrokerName, 
                  const DString& dstrRequestType, 
                  const DString& dstrTrack = I_("N"),
                  const DString& dstrPageName = NULL_STRING,
                  bool  allResults = true );           

   SEVERITY init2( const DString& dstrBrokerCode, 
                  const DString& dstrSrchBrokerName, 
                  const DString& dstrRequestType, 
                  const DString& dstrAccountNum,
                  const DString& dstrValidateType,
                  const DString& dstrTrack = I_("N"),
                  const DString& dstrPageName = NULL_STRING,
                  bool  allResults = true );           


   SEVERITY initFundAllowed( const DString& dstrBrokerCode, 
                             const DString& dstrFundCode, 
                             const DString& dstrClassCode,
                             const DString& dstrAccountNum,
                             const DString& dstrTransType = NULL_STRING,
                             const DString& dstrValidateType = I_( "Trade" ),
                             const DString& dstrTrack = I_("N"),
                             const DString& dstrPageName = NULL_STRING );

	SEVERITY initNSCC(const DString&  dstrBrokerCode, 
							const DString& dstrSrchBrokerName, 
							const DString& dstrRequestType, 
							const DString& dstrAccountNum, 
							const DString& dstrValidateType,
							const DString& dstrClearingFirmBroker, 
							const DString& dstrRelationType = NULL_STRING,
							const DString& dstrTrack = I_("N"), 
							const DString& dstrPageName = NULL_STRING );
private:
BFData * requestData90;							
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/BrokerList.hpp-arc  $
 * 
 *    Rev 1.19   Apr 07 2009 01:08:34   kitticha
 * IN#1588682 - Small Enhancement - Feature search screen for Fund Broker Search. - additional code changes for More button
 * 
 *    Rev 1.18   Apr 06 2009 04:32:36   kitticha
 * IN#1588682 - Small Enhancement - Feature search screen for Fund Broker Search. - additional code changes for More button
 * 
 *    Rev 1.17   Jul 06 2005 10:58:32   ZHANGCEL
 * PET1141 - FN05 -- NSCC Broker enhancement
 * 
 *    Rev 1.16   Nov 14 2004 14:29:28   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.15   May 27 2003 18:29:32   popescu
 * due to several memory leaks found in some list getters at the DSTCWorkSession level caused by copy/paste, I've created a common template function to retrieve the dependent objects
 * 
 *    Rev 1.14   Jan 12 2003 15:30:44   WINNIE
 * Replace initFundAllow2 with initFundAllow and adjust order of parameters; add default value for validation type
 * 
 *    Rev 1.13   Jan 03 2003 09:37:12   HSUCHIN
 * created init2/initFundAllowed2 to support dynamic
*/