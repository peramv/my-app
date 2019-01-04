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
//    Copyright 2002, By International Financial Data Service
//
//
//******************************************************************************
//
// ^FILE   : DSTCSettlementTrxnBuilder.hpp
// ^AUTHOR : Adrian Vasile
// ^DATE   : June 3,2002
//
// ^CLASS    : DSTCSettlementTrxnBuilder
// ^INHERITS FROM :           
//
// ^CLASS DESCRIPTION : 
//
//
//******************************************************************************

#include <boost\utility.hpp>

class BFAbstractCBO;
class SettlementTrade;
class HostTransactionContainer;

class DSTCSettlementTrxnBuilder : private boost::noncopyable
{
public:
   static SEVERITY buildTransactions( DSTCWorkSession &workSession, 
                                      BFAbstractCBO* pBFBase, 
                                      HostTransactionContainer* pTrCont,
                                      BF_OBJ_ACTIVITY objActivity = OBJ_ACTIVITY_NONE );

   static void buildTrxnKeyForChangedTrades( DSTCWorkSession &workSession, 
                                             DString& strKey, 
                                             SettlementTrade* settlement );
   static void buildTrxnKeyForUnchangedTrades( DSTCWorkSession &workSession, 
                                               DString& strKey, 
                                               SettlementTrade* settlement );
private:

  static DString  getNetSettlement(DString& dstrSearchType, 
                             Settlement* pSettlement );


};

