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
//    Copyright 2002 by International Financial, Inc.
//
//
//******************************************************************************
//
// ^FILE   : ifastReportTrxnBuilder.hpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : ifastReportTrxnBuilder
// ^INHERITS FROM :           
//
// ^CLASS DESCRIPTION : 
//
//
//******************************************************************************

#include <boost\utility.hpp>

class BFAbstractCBO;
class HostTransactionContainer;
class ifastCommonReportCriteria;

class ifastReportTrxnBuilder : private boost::noncopyable
{
   public:
   static SEVERITY buildTransactions( DSTCWorkSession &workSession, 
                                      BFAbstractCBO* pBFBase, 
                                      HostTransactionContainer* pTrCont);

   static void buildTrxnKey( DString& strKey, ifastCommonReportCriteria* pifastCommonReportCriteria );

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastrptcbo/ifastReportTrxnBuilder.hpp-arc  $ 
//
//   Rev 1.0   Nov 19 2002 11:28:20   HSUCHIN
//Initial Revision
*/