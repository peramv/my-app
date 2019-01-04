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
// ^FILE   : DSTCAggregateOrderTrxnBuilder.hpp
// ^AUTHOR : Celia Zhang
// ^DATE   : Dec 9, 2004
//
// ^CLASS    : DSTCAggregateOrderTrxnBuilder
// ^INHERITS FROM :           
//
// ^CLASS DESCRIPTION : 
//
//
//******************************************************************************

//Forward declarations
class BFCBO;
class HostTransactionContainer;
class AggregatedOrder;
class AggregatedOrderList;
struct FieldPair;

class DSTCAggregateOrderTrxnBuilder
{
public:
   static SEVERITY buildTransactions( DSTCWorkSession &workSession, 
                                      BFAbstractCBO* pBFCBO, 
                                      HostTransactionContainer* pTrxnContainer,
                                      BF_OBJ_ACTIVITY objActivity = OBJ_ACTIVITY_NONE );

private:
   DSTCAggregateOrderTrxnBuilder()
   {};
   //no need for this class to be extended
   ~DSTCAggregateOrderTrxnBuilder()
   {};

   static void fillingData( BFCBO* pObj, BFData* data, FieldPair fields[], int numFields );

};

