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
// ^FILE   : DSTCEntityIdsTrxnBuilder.hpp
// ^AUTHOR : Winnie Shiu
// ^DATE   : November 1999
//
// ^CLASS    : DSTCEntityIdsTrxnBuilder
// ^INHERITS FROM :           
//
// ^CLASS DESCRIPTION : 
//
//
//******************************************************************************

#include <boost\utility.hpp>

//Forward declaration
class BFAbstractCBO;
class Entity;
class HostTransactionContainer;

class DSTCEntityIdsTrxnBuilder : private boost::noncopyable
{
public:
   static SEVERITY buildTransactions( DSTCWorkSession &workSession, 
                                      BFAbstractCBO* pBFBase, 
                                      HostTransactionContainer* pTrCont,
                                      BF_OBJ_ACTIVITY objActivity = OBJ_ACTIVITY_NONE );

   static SEVERITY buildTrxnKey( DSTCWorkSession &workSession, 
                             DString& strKey, 
                             Entity* entity );
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCEntityIdsTrxnBuilder.hpp-arc  $
 * 
 *    Rev 1.8   Nov 14 2004 14:32:18   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.7   15 Oct 2004 17:13:28   YINGBAOL
 * PTS10034771: desktop sends temp entityID to back end.
 * 


  */