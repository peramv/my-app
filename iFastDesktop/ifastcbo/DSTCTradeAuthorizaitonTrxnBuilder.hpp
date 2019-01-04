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
// ^FILE   : DSTCTradeAuthorizaitonTrxnBuilder.hpp
// ^AUTHOR : 
// ^DATE   : 
// ^CLASS  : DSTCTradeAuthorizaitonTrxnBuilder
// ^INHERITS FROM :           
//
// ^CLASS DESCRIPTION : 
//
//
//******************************************************************************

#include <boost\utility.hpp>

class BFAbstractCBO;
class TradeAuthorization;
class HostTransactionContainer;

class DSTCTradeAuthorizaitonTrxnBuilder : private boost::noncopyable
{
	public:
		static SEVERITY buildTransactions (DSTCWorkSession &workSession, 
                                           BFAbstractCBO* pBFBase, 
                                           HostTransactionContainer* pTrCont,
                                           BF_OBJ_ACTIVITY objActivity = OBJ_ACTIVITY_NONE);

		static void buildTrxnKey (DString &strKey, TradeAuthorization *pTradeAuthorization);

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log::
 */

