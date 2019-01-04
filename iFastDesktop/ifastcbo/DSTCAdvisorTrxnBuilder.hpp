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
// ^FILE   : DSTCAdvisorTrxnBuilder.hpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : DSTCAdvisorTrxnBuilder
// ^INHERITS FROM :           
//
// ^CLASS DESCRIPTION : 
//
//
//******************************************************************************

#include <boost\utility.hpp>

//Forward declarations
class BFAbstractCBO;
class BFData;
class HostTransactionContainer;
class Advisor;
class AdvisorList;

class DSTCAdvisorTrxnBuilder : private boost::noncopyable
{
public:
   static SEVERITY buildTransactions( DSTCWorkSession &workSession, 
                                      BFAbstractCBO* pBFBase, 
                                      HostTransactionContainer* pTrxnContainer,
                                      BF_OBJ_ACTIVITY objActivity = OBJ_ACTIVITY_NONE );

private:
   static void fillingData( const BFAbstractCBO* pObj, BFData* data, const BFFieldId fields[], int numFields );
};

