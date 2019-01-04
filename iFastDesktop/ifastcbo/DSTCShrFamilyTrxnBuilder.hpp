//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use orsuch information
//    may result in civil liabilities. disclosure of 
//
//    Copyright 1999 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : DSTCShareholderShrFamilyTrxnBuilder.h
// ^AUTHOR : Claudio Sanchez
// ^DATE   : January 10, 2003
//
// ----------------------------------------------------------
//
// ^CLASS : DSTCSHAREHOLDERREMARKSTRXNBUILDER
//
// ^MEMBER VARIABLES :  
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
// ^FILE   : DSTCShareholderShrFamilyTrxnBuilder.hpp
// ^AUTHOR : Claudio Sanchez
// ^DATE   : January 11, 2003
//
// ^CLASS    : DSTCShareholderRemarksTrxnBuilder
// ^INHERITS FROM :           
//
// ^CLASS DESCRIPTION : 
//
//
//******************************************************************************

#include <boost\utility.hpp>

class BFAbstractCBO;
class HostTransactionContainer;

class DSTCShhrFamilyTrxnBuilder : private boost::noncopyable
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
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCShrFamilyTrxnBuilder.hpp-arc  $
//
//   Rev 1.3   Nov 14 2004 14:33:42   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.2   Jan 14 2003 17:39:36   sanchez
//added  Revision Control Entries
 */