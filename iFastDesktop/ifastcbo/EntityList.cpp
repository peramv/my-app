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
// ^FILE   : EntityList.cpp
// ^AUTHOR : 
// ^DATE   : 04/16/97
//
// ^CLASS    : EntityList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "entitylist.hpp"
#include "entity.hpp"
#include "worksessionentitylist.hpp"
#include <ifastdataimpl\dse_dstc0050_req.hpp>
#include <ifastdataimpl\dse_dstc0050_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest ENTITY;
}

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME        = I_ ("EntityList");
   const I_CHAR * const DODELETEOBJECT   = I_ ("doDeleteObject");
}

extern BF_OBJ_TYPE OBJ_TYPE_ENTITY;

//******************************************************************************
EntityList::EntityList (BFAbstractCBO &parent)
: MFCanBFCbo (parent)
{
   TRACE_CONSTRUCTOR (CLASSNAME, NULL_STRING);
   setObjectAsList ();
}

//******************************************************************************
EntityList::~EntityList()
{
   TRACE_DESTRUCTOR (CLASSNAME);
}

//******************************************************************************
SEVERITY EntityList::init (const DString& dstrAccountNum, 
   const DString& dstrTrack, 
   const DString& dstrPageName)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("init(int, DString&)"));

   BFData requestData (ifds::DSTC0050_REQ);

   DString mgmtCoIdOut;

   requestData.setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut));
   requestData.setElementValue (ifds::AccountNum, dstrAccountNum);
   requestData.setElementValue (ifds::Track, dstrTrack);
   requestData.setElementValue (ifds::Activity, dstrPageName);
   ReceiveData(DSTC_REQUEST::ENTITY, requestData, ifds::DSTC0050_VW, 
      DSTCRequestor (getSecurity(), true));
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY EntityList::doCreateObject (const BFData &data, 
   BFCBO *&pObjOut)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doCreateObject"));

   Entity *pEntity;

   getWorkSession().PopulateEntity (BF::HOST, data, pEntity);
   pObjOut = pEntity;

   return GETCURRENTHIGHESTSEVERITY();
}

//********************************************************************************
SEVERITY EntityList::doCreateNewObject (BFCBO *&pBase, 
   DString &strKey, 
   const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("doCreateNewObject"));

   Entity *pEntity;
   DString  strEntityNum = NULL_STRING;

   getWorkSession().getNewEntity (idDataGroup, pEntity);
   pEntity->getEntityId (strEntityNum);
   pBase = pEntity;
   strKey = strEntityNum;
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY EntityList::doDeleteObject (const DString &strKey, 
   const BFDataGroupId& idDataGroup, 
   bool bIsObjectDestroyed)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, DODELETEOBJECT);

   WorkSessionEntityList *pWorkSessionEntityList = NULL;

   if (getWorkSession().getWorkSessionEntityList (
         pWorkSessionEntityList) <= WARNING &&
      pWorkSessionEntityList)
   {
      BFObjIter iter (*pWorkSessionEntityList, idDataGroup, 
         false, BFObjIter::ITERTYPE::NON_DELETED);

      iter.positionByKey (strKey);
      if (!iter.end ())
      {
         iter.removeObjectFromMap (bIsObjectDestroyed);
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
void EntityList::setObjectFlags (const BFObjectKey &objKey, 
   long &lStateFlags, 
   long &lGroupFlags)
{
   lStateFlags = BFCBO::NO_BASE_DELETE;
   lGroupFlags = 0;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/EntityList.cpp-arc  $
 * 
 *    Rev 1.14   Nov 14 2004 14:36:44   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.13   Jan 02 2004 15:12:06   popescu
 * PTS 10025696, NASU flow crash 
 * 
 *    Rev 1.12   Mar 21 2003 18:08:22   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.11   Nov 18 2002 10:54:34   PURDYECH
 * BFObjectKey changes.
 * 
 *    Rev 1.10   Oct 09 2002 23:54:26   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.9   Aug 29 2002 12:55:46   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.8   22 May 2002 18:28:32   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.7   03 May 2001 14:06:26   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.6   30 Mar 2001 16:39:48   BUZILAMI
 * changes in doDeleteObject
 * 
 *    Rev 1.5   Jan 18 2001 16:04:48   YINGBAOL
 * add eTracker
 * 
 *    Rev 1.4   Dec 17 2000 20:23:22   OLTEANCR
 * changed to use a precompiled header
 * 
 *    Rev 1.3   Dec 06 2000 11:08:44   OLTEANCR
 * changed ReceiveData
 * 
 *    Rev 1.2   Nov 02 2000 13:23:18   YINGBAOL
 * use new databroker
 * 
 *    Rev 1.1   Mar 30 2000 09:48:08   BUZILA
 * changes due to introduction of objKey parameter in BFBase:: ::setObjectFlags
 * 
 *    Rev 1.0   Feb 15 2000 10:59:58   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.12   Jan 05 2000 20:10:42   BUZILA
 * adding list flag
 * 
 *    Rev 1.11   Dec 23 1999 14:18:02   VASILEAD
 * Added validation for ids
 * 
 *    Rev 1.10   Dec 12 1999 16:25:20   POPESCUS
 * Xchgdata issue; create and delete the object in the CBO
// 
*/