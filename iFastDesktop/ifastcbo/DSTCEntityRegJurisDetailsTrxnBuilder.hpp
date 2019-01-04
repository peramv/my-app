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
// ^FILE   : DSTCEntityRegJurisDetailsTrxnBuilder.hpp
// ^AUTHOR : 
// ^DATE   : January 15, 2014
//
// ^CLASS    : DSTCEntityRegJurisDetailsTrxnBuilder
// ^INHERITS FROM :           
//
// ^CLASS DESCRIPTION : 
//
//
//******************************************************************************

//Forward declarations

class DSTCEntityRegJurisDetailsTrxnBuilder
{
public:
   static SEVERITY buildTransactions( DSTCWorkSession &workSession,
	 							      BFAbstractCBO *pObj, 
									  HostTransactionContainer *pTrCont, 
									  BF_OBJ_ACTIVITY objActivity /*= OBJ_ACTIVITY_NONE*/);
   
   static void buildTrxnKey(DString& dstrKey, 
							const DString &accNum, 
							const DString &entityId);

private:
   DSTCEntityRegJurisDetailsTrxnBuilder()
   {};
   //no need for this class to be extended
   ~DSTCEntityRegJurisDetailsTrxnBuilder()
   {};

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCEntityRegJurisDetailsTrxnBuilder.hpp-arc  $
//
//   
//
 * 
 * 
 * 
*/