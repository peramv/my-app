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
// ^FILE   : DSTCSavingsDirectiveTrxnBuilder.hpp
// ^AUTHOR : 
// ^DATE   : 16 Nov 2005
// ^CLASS  : DSTCSavingsDirectiveTrxnBuilder
// ^INHERITS FROM :           
//
// ^CLASS DESCRIPTION : 
//
//
//******************************************************************************

#include <boost\utility.hpp>


class DSTCSavingsDirectiveTrxnBuilder : private boost::noncopyable
{
public:
   static SEVERITY buildTransactions(  DSTCWorkSession &workSession, 
													BFAbstractCBO* pObj,
                                       HostTransactionContainer* pTrCont, 
                                       BF_OBJ_ACTIVITY objActivity );

   static void buildTrxnKey( DString& strKey, SavingsDirective* pSavingsDirective );
	static int buildIndex;

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCSavingsDirectiveTrxnBuilder.hpp-arc  $
//
//   Rev 1.0   Nov 29 2005 16:59:36   AGUILAAM
//Initial revision.
// 
*/