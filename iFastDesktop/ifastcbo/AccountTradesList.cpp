#define IFASTCBO_DLL

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
//    Copyright 2000 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : AccountTradesList.cpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : February 02, 2001
//
// ^CLASS    : AccountTradesList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "accounttradeslist.hpp"

#include "trade.hpp"
#include "worksessiontradeslist.hpp"

namespace
{
   //Trace literals
   const I_CHAR * const CLASSNAME = I_ ("AccountTradesList");
}


namespace ifds
{
}

//******************************************************************************
AccountTradesList::AccountTradesList (BFAbstractCBO &parent) : MFCanBFCbo (parent)
{
   TRACE_CONSTRUCTOR (CLASSNAME, NULL_STRING);
   setObjectAsList ();
}

//******************************************************************************
AccountTradesList::~AccountTradesList ()
{
   TRACE_DESTRUCTOR (CLASSNAME);
}

//******************************************************************************
SEVERITY AccountTradesList::init ( const DString &accountNum,
                                   const BFDataGroupId &idDataGroup,
                                   const DString &dstrTrack /*= I_ ("N")*/,
                                   const DString &dstrPageName /*= NULL_STRING*/
                                 )
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("init"));

   if (!accountNum.empty())
   {
      WorksessionTradesList *pWorksessionTradesList = NULL;

      if ( getWorkSession().getTradesList ( pWorksessionTradesList, 
                                            idDataGroup
                                          ) <= WARNING &&
           pWorksessionTradesList
         )
      {
   //check the trading list
         BFObjIter iter ( *this, 
                          idDataGroup
                        );
         while (!iter.end ())
         {
            DString accountNum_;
            Trade *pTrade = dynamic_cast <Trade*> (iter.getObject ());
         
            pTrade->getField (ifds::AccountNum, accountNum_, idDataGroup);
            if (accountNum_ == accountNum)
            {
               setObject ( pTrade, 
                           iter.getStringKey(), 
                           OBJ_ACTIVITY_NONE, 
                           idDataGroup, 
                           OBJ_TYPE_NONE,
                           BFCBO::OBJ_DELETE::NO_DELETE_ON_DTOR //this list does not own the objects
                         );               
            }
            ++iter;
         }
      }     
   }
   return GETCURRENTHIGHESTSEVERITY ();
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AccountTradesList.cpp-arc  $
// 
//    Rev 1.23   Nov 06 2004 00:39:30   popescu
// PET 1117/06, synch changes
// 
//    Rev 1.22   Sep 08 2004 17:53:02   ZHANGCEL
// PET1094-FN8 -- AdminFee related changes
// 
//    Rev 1.21   Jun 01 2004 13:32:22   FENGYONG
// 10030671, Modify pending trade fix
// 
//    Rev 1.20   May 09 2004 20:09:14   popescu
// PET 985, FN 01, LSIF Trade Entry
// 
//    Rev 1.19   May 06 2004 18:37:22   popescu
// PET 985, fn01, Trade Entry LSIF
// 
//    Rev 1.18   Mar 21 2003 19:40:42   PURDYECH
// Sync 1.16.1.0 back to trunk
// 
//    Rev 1.16.1.0   Mar 21 2003 17:55:18   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.16   Oct 09 2002 23:53:54   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.15   Aug 29 2002 12:54:54   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.14   22 May 2002 18:26:14   PURDYECH
// BFData Implementation
// 
//    Rev 1.13   Apr 16 2002 10:16:56   YINGBAOL
// added AllTransfer
// 
//    Rev 1.12   18 Mar 2002 17:25:08   KOVACSRO
// some data group fixes (PTS 10006915)
// 
//    Rev 1.11   08 Mar 2002 16:50:50   KOVACSRO
// Rebook trades should act as a new trade, rather than an existing one.
// 
//    Rev 1.10   04 Feb 2002 15:14:50   KOVACSRO
// Rebook and MgmtFee changes.
// 
//    Rev 1.9   Jul 23 2001 15:30:34   YINGBAOL
// sync up version 1.6.1.1
// 
//    Rev 1.8   09 May 2001 11:37:46   HSUCHIN
// Sync up with SSB
// 
//    Rev 1.7   03 May 2001 14:05:54   SMITHDAV
// Session management restructuring.
// 
//    Rev 1.6   29 Mar 2001 17:36:14   KOVACSRO
// code clean up.
// 
//    Rev 1.5   16 Mar 2001 16:52:22   KOVACSRO
// Added TransNum as a key for persistent Trades.
// 
//    Rev 1.4   06 Mar 2001 14:14:08   KOVACSRO
// creating pending trades now.
// 
//    Rev 1.3   21 Feb 2001 10:32:44   KOVACSRO
// Modified doCreateNewObject
// 
//    Rev 1.2   Feb 16 2001 10:14:58   DINACORN
// Add Revision Control Entries
 * 
 * 
 */