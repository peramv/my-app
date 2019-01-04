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
//    Copyright 1998 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : FeeSetupTradeRulesList.hpp
// ^AUTHOR : Serban Popescu
// ^DATE   : October 2004
//
// ^CLASS    : FeeSetupTradeRulesList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>
///#endif

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE FeeSetupTradeRulesList : public MFCanBFCbo, private boost::noncopyable
{
public:
   static void buildKey ( const DString &feeCode, 
                          const DString &transType, 
                          DString &strKey
                        );
public:
   FeeSetupTradeRulesList (BFAbstractCBO &parent);
   virtual ~FeeSetupTradeRulesList ();
   SEVERITY init ( const DString &dstrTrack = I_("N"), 
                   const DString &dstrPageName = NULL_STRING
                 );
   void getFeeCodes ( const DString &transType,
                      const DString &redCode,
                      const DString &depositType,
                      const DString &indc,
                      const DString &taxJuris,
                      std::vector <DString> &feeCodes
                    );
   bool canFeeBeOverridden ( const DString &feeCode,
                             const DString &transType
                           );
protected:
   virtual void getStrKey  (DString &strKey, const BFData *data);
   virtual SEVERITY doCreateObject ( const BFData &data, 
                                     BFCBO *&pObjOut
                                   );

};

class FeeSetupTradeRules : public MFCanBFCbo, private boost::noncopyable
{
public:
   FeeSetupTradeRules (BFAbstractCBO &parent);
   SEVERITY init (const BFData &data);
};


///#endif
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/FeeSetupTradeRulesList.hpp-arc  $
//
//   Rev 1.2   Dec 09 2004 22:30:56   popescu
//PET 11717/06, fees and mod pending trades
//
//   Rev 1.1   Nov 14 2004 14:40:46   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.0   Nov 05 2004 21:20:24   popescu
//Initial revision.
//
//   Rev 1.0   Oct 29 2004 20:27:38   popescu
//Initial revision.
//
*/