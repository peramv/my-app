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
//    Copyright 1998 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : ErrMsgRulesList.cpp
// ^AUTHOR : Cornel Dina
// ^DATE   : June 2000
//
// ^CLASS    : ErrMsgRulesList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "errmsgruleslist.hpp"
#include <ifastdataimpl\dse_dstc0142_req.hpp>
#include <ifastdataimpl\dse_dstc0142_vw.hpp>
#include "ConditionObject.h"
namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest ERR_MSG_RULES;
}

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "ErrMsgRulesList" );
}

//******************************************************************************
ErrMsgRulesList::ErrMsgRulesList(BFAbstractCBO &parent)
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList();
   setVersionable( false );
}

//******************************************************************************
ErrMsgRulesList::~ErrMsgRulesList( void )
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY ErrMsgRulesList::init ( const DString& dstrTrack /*=I_("N")*/,
                                 const DString& dstrPageName /*=NULL_STRING*/)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   BFData requestData(ifds::DSTC0142_REQ);

   DString mgmtCoIdOut;
   
   requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   requestData.setElementValue( ifds::Track, dstrTrack );
   requestData.setElementValue( ifds::Activity, dstrPageName );
   AsyncReceiveData (DSTC_REQUEST::ERR_MSG_RULES, requestData, 
                     ifds::DSTC0142_VW, 
                     DSTCRequestor (getSecurity(), true));
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
void ErrMsgRulesList::getStrKey (DString &strKey, const BFData *data)
{
   TRACE_METHOD (CLASSNAME, I_("getStrKey"));

   if (data)
   {
      strKey = data->getElementValue (ifds::ErrNum);
      strKey.strip();
   }
   else
   {
      BFCBO::getStrKey (strKey, NULL);
   }

}

//******************************************************************************
SEVERITY ErrMsgRulesList::getEWI (const DString& strErrNum, 
   long lErrConditionId, 
   long lWarnConditionId, 
   const BFDataGroupId &idDataGroup, 
   const DString &idiStr /*=NULL_STRING*/)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getEWI" ) );

   DString strEwi (NULL_STRING);
   BFObjIter iter (*this, BF::HOST);

   if (iter.positionByKey(strErrNum))
   {
      iter.getObject()->getField (ifds::EWI, strEwi, idDataGroup);

      strEwi.strip().upperCase();

      if (strEwi == I_("I"))
      {
         ;
      }
      else if (strEwi == I_("W"))
      {
         ADDCONDITIONFROMFILEIDI (lWarnConditionId, idiStr); 
      }
      else if (strEwi == I_("E"))
      {
         ADDCONDITIONFROMFILEIDI (lErrConditionId, idiStr); 
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY ErrMsgRulesList::getEWI (const DString& strErrNum, 
                                  CConditionObject& errConditionObj, 
                                  CConditionObject& warnConditionObj, 
                                  const BFDataGroupId &idDataGroup, 
                                  const DString &idiStr /*=NULL_STRING*/)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getEWI" ) );

   DString strEwi (NULL_STRING);
   BFObjIter iter (*this, BF::HOST);

   if (iter.positionByKey(strErrNum))
   {
      iter.getObject()->getField (ifds::EWI, strEwi, idDataGroup);

      strEwi.strip().upperCase();

      if (strEwi == I_("I"))
      {
         ;
      }
      else if (strEwi == I_("W"))
      {
         ADDCONDITIONFROMOBJECTIDI (warnConditionObj, idiStr); 
      }
      else if (strEwi == I_("E"))
      {
         ADDCONDITIONFROMOBJECTIDI (errConditionObj, idiStr); 
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
void ErrMsgRulesList::getEWIValue (const DString &strErrNum, 
   const BFDataGroupId& idDataGroup, 
   DString &strErrValue)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("getEWIValue"));

   BFObjIter iter (*this, BF::HOST);

   if (iter.positionByKey (strErrNum))
   {
      // strErrValue will have one of the following values "I", "W", "E"
      iter.getObject()->getField (ifds::EWI, strErrValue, idDataGroup);
   }
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/ErrMsgRulesList.cpp-arc  $
// 
//    Rev 1.22   24 Jul 2008 12:00:44   popescu
// Incident - 1190617 - set all the data init calls to be asynch
// 
//    Rev 1.21   Dec 10 2004 14:35:10   hernando
// PET1117 - Recovered version feature.
// 
//    Rev 1.20   Nov 24 2004 10:17:52   yingbaol
// PET1117:temperary take out version features
// 
//    Rev 1.19   Nov 18 2004 13:28:02   YINGBAOL
// PET1117: Perfermance Tunning
// 
//    Rev 1.18   Nov 14 2004 14:36:48   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.17   Apr 07 2004 09:55:32   AGUILAAM
// PET965_FN02: change error to uppercase to allow for flexibility in user input  - error levels can be modified by user on iFast
// 
//    Rev 1.16   Oct 30 2003 16:30:36   popescu
// PTS 10023438, RESP SIN legislative requirement
// 
//    Rev 1.15   Apr 09 2003 12:51:52   sanchez
// New function ErrMsgRulesList() tor return of the following string values "I", "W", "E"
// 
//    Rev 1.14   Mar 21 2003 18:08:32   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.13   Oct 09 2002 23:54:28   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.12   Aug 29 2002 12:55:46   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.11   22 May 2002 18:28:32   PURDYECH
// BFData Implementation
// 
//    Rev 1.10   03 May 2001 14:06:26   SMITHDAV
// Session management restructuring.
// 
//    Rev 1.9   Jan 18 2001 16:04:50   YINGBAOL
// add eTracker
// 
//    Rev 1.8   Dec 17 2000 20:23:24   OLTEANCR
// changed to use a precompiled header
// 
//    Rev 1.7   Dec 06 2000 11:16:44   OLTEANCR
// changed ReceiveData
// 
//    Rev 1.6   Dec 05 2000 17:17:16   DINACORN
// Synchronization to C2/C3: Modify getEWI() method
// 
//    Rev 1.5   Nov 16 2000 09:47:30   OLTEANCR
// modif. getEWI
// 
//    Rev 1.4   Nov 15 2000 17:44:50   OLTEANCR
// modified getEWI
// 
//    Rev 1.3   Nov 08 2000 13:13:14   YINGZ
// change get Ewi to getEWI make it compilable
// 
//    Rev 1.2   Nov 06 2000 14:35:50   OLTEANCR
// added new functions: getStrKey, getEWI
// 
//    Rev 1.1   Nov 02 2000 13:23:06   YINGBAOL
// use new databroker
// 
//    Rev 1.0   Jun 23 2000 16:46:50   DINACORN
// Initial revision.
*/


