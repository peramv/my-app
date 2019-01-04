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
//    Copyright 2002 by International Financial.
//
//
//******************************************************************************
//
// ^FILE   : DSTCFeeParamTrxnBuilder.hpp
// ^AUTHOR : Yingbao Li
// ^DATE   : January 30, 2002
//
// ^CLASS    : DSTCFeeParamTrxnBuilder
// ^INHERITS FROM :           
//
// ^CLASS DESCRIPTION : 
//
//
//******************************************************************************

#include <boost\utility.hpp>

class BFCBO;
class HostTransactionContainer;
class FeeParam;

class DSTCFeeParamTrxnBuilder : private boost::noncopyable
{
public:
   static SEVERITY buildTransactions( DSTCWorkSession &workSession, 
                                      BFCBO* pObj, 
                                      HostTransactionContainer* pTrCont);

   static void buildTrxnKey( DString& strKey, FeeParam* pFeeParam, MFAccount* mfAccount );

};

