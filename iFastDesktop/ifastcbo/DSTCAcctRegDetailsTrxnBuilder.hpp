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
// ^FILE   : DSTCAcctRegDetailsTrxnBuilder.hpp
// ^AUTHOR : Aurkarn Mongkonrat
// ^DATE   : 14 June 2013
//
// ^CLASS    : DSTCAcctRegDetailsTrxnBuilder
// ^INHERITS FROM :           
//
// ^CLASS DESCRIPTION : 
//
//
//******************************************************************************

//Forward declaration
#include <boost\utility.hpp>

class BFAbstractCBO;
class HostTransactionContainer;
class MFAccount;

class DSTCAcctRegDetailsTrxnBuilder
{
public:
	static SEVERITY buildTransactions (
		DSTCWorkSession &workSession, 
		BFAbstractCBO* pObj, 
		HostTransactionContainer* pTrCont,
		BF_OBJ_ACTIVITY objActivity = OBJ_ACTIVITY_NONE );

	static void buildTrxnKey (DString &strKey, MFAccount *pMFAccount);

private:
	DSTCAcctRegDetailsTrxnBuilder(){};
	~DSTCAcctRegDetailsTrxnBuilder(){};
};
