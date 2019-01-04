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
//    Copyright 2003 by International Financial.
//
//
//******************************************************************************
//
// ^FILE   : DSTCFeeParamSysTxnBuilder.hpp
// ^AUTHOR : Yingbao Li
// ^DATE   : January 16, 2003
//
// ^CLASS    : DSTCFeeParamSysTxnBuilder
// ^INHERITS FROM :           
//
// ^CLASS DESCRIPTION : 
//
//
//******************************************************************************

#include <boost\utility.hpp>

class BFCBO;
class HostTransactionContainer;
class FeeParamSys;

class DSTCFeeParamSysTxnBuilder : private boost::noncopyable
{
public:
   static SEVERITY buildTransactions( DSTCWorkSession &workSession, 
                                      BFAbstractCBO* pBFBase, 
                                      HostTransactionContainer* pTrCont,
                                      BF_OBJ_ACTIVITY objActivity = OBJ_ACTIVITY_NONE );


   static void buildTrxnKey( DString& strKey, FeeParamSys* pFeeParam );

private:
	static int buildIndex;

};
