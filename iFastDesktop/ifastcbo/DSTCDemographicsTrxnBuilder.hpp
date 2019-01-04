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
// ^FILE   : DSTCDemographicsTrxnBuilder.hpp
// ^AUTHOR : Winnie Shiu
// ^DATE   : October 1999
// ^CLASS  : DSTCDemographicsTrxnBuilder
// ^INHERITS FROM :           
//
// ^CLASS DESCRIPTION : 
//
//
//******************************************************************************

#include <boost\utility.hpp>

class BFAbstractCBO;
class Demographics;
class MFAccount;
class Entity;
class HostTransactionContainer;

class DSTCDemographicsTrxnBuilder : private boost::noncopyable
{
public:
   static SEVERITY buildTransactions( DSTCWorkSession &workSession, 
                                      BFAbstractCBO* pBFBase, 
                                      HostTransactionContainer* pTrCont,
                                      BF_OBJ_ACTIVITY objActivity = OBJ_ACTIVITY_NONE );

   static void buildTrxnKey( DString &strKey, MFAccount *pMFAccount, Demographics *pDemographics );

   static SEVERITY buildTransactions1( DSTCWorkSession &workSession, 
                                       BFAbstractCBO* pBFBase, 
                                       HostTransactionContainer* pTrCont,
                                       BF_OBJ_ACTIVITY objActivity = OBJ_ACTIVITY_NONE );

   static void buildTrxnKey1( DString &strKey, Entity *pEntity, Demographics *pDemographics );

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCDemographicsTrxnBuilder.hpp-arc  $
 * 
 *    Rev 1.9   Sep 12 2008 06:18:34   daechach
 * PET0128026 - KYC Phase 2
 *
 */

