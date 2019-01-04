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
// ^FILE   : DSTCTradesTrxnBuilder.hpp
// ^AUTHOR : 
// ^DATE   : March 20, 2000
//
// ^CLASS    : DSTCTradesTrxnBuilder
// ^INHERITS FROM :           
//
// ^CLASS DESCRIPTION : 
//
//
//******************************************************************************

//Forward declarations
class BFCBO;
class MFAccount;
class HostTransactionContainer;
class Trade;
class WorksessionTradesList;
struct FieldPair;

class DSTCTradesTrxnBuilder
{
public:
   static SEVERITY buildTransactions( DSTCWorkSession &workSession, 
                                      BFAbstractCBO* pBFCBO, 
                                      HostTransactionContainer* pTrxnContainer,
                                      BF_OBJ_ACTIVITY objActivity = OBJ_ACTIVITY_NONE );

private:
   DSTCTradesTrxnBuilder()
   {};
   //no need for this class to be extended
   ~DSTCTradesTrxnBuilder()
   {};

   static void fillingData( BFCBO* pObj, BFData* data, FieldPair fields[], int numFields );
   static bool changeObjectActivity(Trade* pTrade,BF_OBJ_ACTIVITY& ObjActivity );


};

