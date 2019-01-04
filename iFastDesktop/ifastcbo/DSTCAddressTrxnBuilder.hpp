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
// ^FILE   : DSTCAddressTrxnBuilder.hpp
// ^AUTHOR : Winnie Shiu
// ^DATE   : Demember 1999
//
// ^CLASS    : DSTCAddressTrxnBuilder
// ^INHERITS FROM :           
//
// ^CLASS DESCRIPTION : 
//
//
//******************************************************************************

//Forward declaration
class BFBase;
class Shareholder;
class HostTransactionContainer;
class Address;
class AddressList;

class DSTCAddressTrxnBuilder
{
public:
   static SEVERITY buildTransactions( DSTCWorkSession &workSession, 
                                      BFAbstractCBO* pObj, 
                                      HostTransactionContainer* pTrCont,
                                      BF_OBJ_ACTIVITY objActivity = OBJ_ACTIVITY_NONE );

   static void buildTrxnKey( DString &strKey, Shareholder* pshareholder );

   static SEVERITY buildAddressRepeat( DSTCWorkSession &workSession, 
                                       Shareholder *pShareholder, 
                                       Address* address, 
                                       AddressList *addressList,
                                       HostTransactionContainer *pTrCont, 
                                       int &count /*no of repeats*/, 
                                       BF_OBJ_ACTIVITY objActivity = OBJ_ACTIVITY_NONE );
private:
   DSTCAddressTrxnBuilder()
   {};
   //no need for this class to be extended
   ~DSTCAddressTrxnBuilder()
   {};
};

