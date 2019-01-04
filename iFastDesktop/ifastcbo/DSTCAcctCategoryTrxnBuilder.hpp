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
// ^FILE   : DSTCAcctCategoryTrxnBuilder.hpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : January 21, 2003
//
// ^CLASS    : DSTCAcctCategoryTrxnBuilder
// ^INHERITS FROM :           
//
// ^CLASS DESCRIPTION : 
//
//
//******************************************************************************

#include <boost\utility.hpp>

class BFAbstractCBO;
class HostTransactionContainer;

class DSTCAcctCategoryTrxnBuilder : private boost::noncopyable
{
public:
   static SEVERITY buildTransactions( DSTCWorkSession &workSession, 
                                      BFAbstractCBO* pBFBase, 
                                      HostTransactionContainer* pTrCont,
                                      BF_OBJ_ACTIVITY objActivity = OBJ_ACTIVITY_NONE );
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCAcctCategoryTrxnBuilder.hpp-arc  $
//
//   Rev 1.1   Nov 14 2004 14:31:14   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.0   Jan 21 2003 14:26:28   KOVACSRO
//Initial revision.

 */