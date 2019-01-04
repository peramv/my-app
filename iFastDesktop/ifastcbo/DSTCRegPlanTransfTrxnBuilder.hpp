#pragma once 

//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confIdential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2012 by International Financial Data Services.
//
//
//******************************************************************************
//
// ^FILE   : DSTCRegPlanTransfTrxnBuilder.hpp
// ^AUTHOR : Mihai Buzila
// ^DATE   : Nov 2016
//
// ^CLASS  : DSTCRegPlanTransfTrxnBuilder
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

class DSTCRegPlanTransfTrxnBuilder
{
public:
   static SEVERITY buildTransactions (DSTCWorkSession &workSession, 
                                      BFAbstractCBO* pObj, 
                                      HostTransactionContainer* pTrCont,
                                      BF_OBJ_ACTIVITY objActivity = OBJ_ACTIVITY_NONE);

   static void buildTrxnKey ( DString& dstrKey, BFAbstractCBO *pObj) ;

private:
   DSTCRegPlanTransfTrxnBuilder()   {};
   //no need for this class to be extended
   ~DSTCRegPlanTransfTrxnBuilder()
   {};
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCRegPlanTransfTrxnBuilder.hpp-arc  $
//