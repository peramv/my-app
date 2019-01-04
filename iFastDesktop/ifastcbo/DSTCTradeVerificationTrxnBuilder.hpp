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
//    Copyright 2004 by International Financial Data Services
//
//
//******************************************************************************
//
// ^FILE   : DSTCTradeVerificationTrxnBuilder.hpp
// ^AUTHOR : Robbins Kuriakose
// ^DATE   : JuLY 22 2014
//
//********************************************************************************
#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif
//Forward declarations
class BFCBO;
class HostTransactionContainer;
class TradeVerification;


class DSTCTradeVerificationTrxnBuilder
{
public:
   static SEVERITY buildTransactions( DSTCWorkSession &workSession, 
                                      BFAbstractCBO* pBFCBO, 
                                      HostTransactionContainer* pTrxnContainer,
                                      BF_OBJ_ACTIVITY objActivity = OBJ_ACTIVITY_NONE );
  static void buildTrxnKey(DString& dstrKey, TradeVerification *pTradeVerification);

private:
   DSTCTradeVerificationTrxnBuilder()
   {};
   //no need for this class to be extended
   ~DSTCTradeVerificationTrxnBuilder()
   {};

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/DSTCTradeVerificationTrxnBuilder.hpp-arc  $
// 
//    Rev 1.0  22 July 2014
// Initial revision.
*/

