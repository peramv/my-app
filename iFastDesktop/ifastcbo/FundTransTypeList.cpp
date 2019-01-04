//*****************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2002 by Internation Finanical Data Services Inc.
//
//*****************************************************************************
//
// ^FILE   : FundTransTypeList.cpp
// ^AUTHOR : Winnie Shiu
// ^DATE   : January 9, 2002
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : FundTransTypeList
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************
#include "stdafx.h"
#include "FundTransType.hpp"
#include "FundTransTypeList.hpp"

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest FUNDTRANSTYPE_LIST;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId FundCode;
   extern CLASS_IMPORT const BFTextFieldId ClassCode;
};

namespace
{
   const I_CHAR * const CLASSNAME = I_( "FundTransTypeList" );
}

//*****************************************************************************
FundTransTypeList::FundTransTypeList( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList( );
}

//*****************************************************************************
FundTransTypeList::~FundTransTypeList()
{
   TRACE_DESTRUCTOR( CLASSNAME );

}

//*****************************************************************************
SEVERITY FundTransTypeList::init( )
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));   
   return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************
SEVERITY FundTransTypeList::getFundTransType ( const DString &transType, 
                                               FundTransType *&pFundTransType, 
                                               const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("getFundTransType"));

   pFundTransType = NULL;
   pFundTransType = dynamic_cast<FundTransType*> (BFCBO::getObject (transType, idDataGroup));
   if (!pFundTransType)
   {      
      DString fundCode, 
         classCode;

      getParent()->getField (ifds::FundCode, fundCode, idDataGroup, false);
      getParent()->getField (ifds::ClassCode, classCode, idDataGroup, false);
      fundCode.strip().upperCase();
      classCode.strip().upperCase();
//first time being asked for            
      pFundTransType = new FundTransType (*this);
      if (pFundTransType->init (transType, fundCode, classCode, idDataGroup) <= WARNING)
      {
         setObject (pFundTransType, transType, OBJ_ACTIVITY_NONE, idDataGroup);
      }
      else
      {
         delete pFundTransType;
         pFundTransType = NULL;
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/FundTransTypeList.cpp-arc  $
// 
//    Rev 1.8   24 Jul 2007 20:13:14   popescu
// GAP 20 -22 AIM
// 
//    Rev 1.7   Nov 14 2004 14:43:26   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.6   Nov 04 2004 17:37:50   popescu
// PET 1117/06, Trade processing
// 
//    Rev 1.5   Jun 25 2004 16:38:28   popescu
// PST 10031525, fund limitation override issues
// 
//    Rev 1.4   Mar 21 2003 19:51:38   PURDYECH
// Sync 1.2.1.0 back  to trunk
// 
//    Rev 1.2.1.0   Mar 21 2003 18:12:24   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.2   Mar 18 2003 21:10:34   popescu
// Exchange out fee work
// 
//    Rev 1.1   Jan 21 2003 18:33:08   WINNIE
// pass data group id
// 
//    Rev 1.0   Jan 12 2003 16:05:44   WINNIE
// Initial revision.
 // 
*/