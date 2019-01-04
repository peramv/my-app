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
// ^FILE   : DSTCRegDocumentListTrxnBuilder.hpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : DSTCRegDocumentListTrxnBuilder
// ^INHERITS FROM :           
//
// ^CLASS DESCRIPTION : 
//
//
//******************************************************************************

#include <boost\utility.hpp>

namespace ifds 
{
   extern CLASS_IMPORT const BFTextFieldId RunMode;
}

class BFAbstractCBO;
class HostTransactionContainer;

class DSTCRegDocumentListTrxnBuilder : private boost::noncopyable
{
public:
   static SEVERITY buildTransactions( DSTCWorkSession &workSession, 
                                      BFAbstractCBO* pBFBase, 
                                      HostTransactionContainer* pTrCont,
                                      BF_OBJ_ACTIVITY objActivity = OBJ_ACTIVITY_NONE);

   static SEVERITY buildEachTransaction(
                                       DSTCWorkSession &workSession,
                                       HostTransactionContainer* pTrCont,
                                       BF_OBJ_ACTIVITY objActivity,
                                       MFAccount* pMFAccount,
                                       Entity *pEntity,
                                       const DString& regStandard4Key,
                                       const DString& complyRule);
};
