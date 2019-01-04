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
// ^FILE   : LSIFRolloverRulesList.cpp
// ^AUTHOR : Serban Popescu 
// ^DATE   : May 2004
//
// ^CLASS    : LSIFRolloverRulesList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "lsifrolloverruleslist.hpp"
#include <ifastdataimpl\dse_dstc0296_req.hpp>
#include <ifastdataimpl\dse_dstc0296_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest LSIF_ROLLOVER_RULES;
}

namespace
{
   //Trace literals
   const I_CHAR * const CLASSNAME = I_("LSIFRolloverRulesList");
}

namespace CND
{
}

//******************************************************************************
LSIFRolloverRulesList::LSIFRolloverRulesList  (BFAbstractCBO &parent) 
: MFCanBFCbo (parent)
{
   TRACE_CONSTRUCTOR  (CLASSNAME , NULL_STRING);
   setObjectAsList ();
   //setVersionable( false );
}

//******************************************************************************
LSIFRolloverRulesList::~LSIFRolloverRulesList ()
{
   TRACE_DESTRUCTOR (CLASSNAME);
}

//******************************************************************************
SEVERITY LSIFRolloverRulesList::init (
   const DString &fromFund, 
   const DString &fromClass,
   const DString &dstrTrack, 
   const DString &dstrPageName)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));

   BFData queryData (ifds::DSTC0296_REQ);

   DString mgmtCoIdOut;
   queryData.setElementValue (ifds::FromFund, fromFund);
   queryData.setElementValue (ifds::FromClass, fromClass);
   queryData.setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut));
   queryData.setElementValue (ifds::Track, dstrTrack);
   queryData.setElementValue (ifds::Activity, dstrPageName);

   ReceiveData (DSTC_REQUEST::LSIF_ROLLOVER_RULES, queryData, 
      ifds::DSTC0296_VW, DSTCRequestor (getSecurity (), true));

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
bool LSIFRolloverRulesList::isRolloverAllowed (
   const DString &toFund, 
   const DString &toClass)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("isRolloverAllowed"));
   DString strKey;
   BFObjIter iter (*this, BF::HOST, false, BFObjIter::ITERTYPE::NON_DELETED);

   buildKey (toFund, toClass, strKey);
   return iter.positionByKey (strKey);
}

//******************************************************************************
void LSIFRolloverRulesList::buildKey (
   const DString &toFund, 
   const DString &toClass, 
   DString &strKey)
{
   strKey = toFund + I_("_") + toClass;
   strKey.stripAll ();
   strKey.upperCase ();
}

//******************************************************************************
void LSIFRolloverRulesList::getStrKey  (DString &strKey, const BFData *data)
{
   TRACE_METHOD (CLASSNAME, I_("getStrKey"));

   if (data)
   {
      buildKey (
         data->getElementValue (ifds::ToFund), 
         data->getElementValue (ifds::ToClass), 
         strKey);
   }
   else
   {
      BFCBO::getStrKey (strKey , NULL);
   }
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/LSIFRolloverRulesList.cpp-arc  $
// 
//    Rev 1.4   Nov 24 2004 10:18:40   yingbaol
// PET1117:temperary take out version features
// 
//    Rev 1.3   Nov 18 2004 13:28:18   YINGBAOL
// PET1117: Perfermance Tunning
// 
//    Rev 1.2   Nov 14 2004 14:49:12   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.1   May 12 2004 09:10:12   popescu
// PET 985, FN 01, LSIF Trade Entry
// 
//    Rev 1.0   May 09 2004 20:17:36   popescu
// Initial revision.
// 
//    Rev 1.0   May 06 2004 18:43:38   popescu
// Initial revision.
*/