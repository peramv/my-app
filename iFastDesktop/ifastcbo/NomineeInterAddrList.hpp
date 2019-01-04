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
//    Copyright 2000 by DST Canada, Inc.
//
//
//******************************************************************************
//
// ^FILE   : NomineeInterAddrList.hpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : 04/08/2000
//
// ^CLASS    : NomineeInterAddrList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************


#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>

class NomineeInterAddr;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE NomineeInterAddrList : 
   public MFCanBFCbo, private boost::noncopyable
{
public:
   static void buildKey (
      const DString &regAddrCode, 
      const DString &taxType, 
      DString &strKey);
public:
   // X-structors
   NomineeInterAddrList (BFAbstractCBO &parent);
   virtual ~NomineeInterAddrList (void);

   // Initialize functions
   SEVERITY init (
         const DString &brokerInterCode,
         const DString &dstrTrack = I_("N"),
         const DString &dstrPageName = NULL_STRING);
   bool getNomineeAddressByTaxType (
         NomineeInterAddr *&pAddress, 
         const DString &taxType,
         const BFDataGroupId &idDataGroup);
   bool getNomineeAddressByAddrCodeTaxType (
         NomineeInterAddr *&pAddress,
			const DString &regAddrCode,
			const DString &taxType,
         const BFDataGroupId &idDataGroup);
protected:
   virtual void getStrKey (
         DString &strKey, 
         const BFData *data);
   virtual SEVERITY doCreateObject (
         const BFData &data, 
         BFCBO *&pObjOut);
private:
   SEVERITY getDefault (
         NomineeInterAddr *&pNomineeAddress, 
         const BFDataGroupId &idDataGroup);
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/NomineeInterAddrList.hpp-arc  $
//
//   Rev 1.13   Nov 14 2004 14:50:50   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.12   May 20 2004 14:17:06   popescu
//PTS 10026123, address 01, for nominee and intermediary accounts by tax type and reg address code
 // 
 * 
 */
