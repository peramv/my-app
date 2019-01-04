
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
// ^FILE   : WorkSessionEntityList.cpp
// ^AUTHOR : Yingbao Li
// ^DATE   : September 26, 2001
//
//******************************************************************************

#include "stdafx.h"
#include "entity.hpp"
#include "worksessionentitylist.hpp"

#include <bfutil\bfcritsec.hpp>
#include <bfutil\bfguard.hpp>

namespace
{
   const I_CHAR * const CLASSNAME = I_ ("WorkSessionEntityList");
}

extern BF_OBJ_TYPE OBJ_TYPE_ENTITY;

namespace ifds
{
   extern CLASS_IMPORT const BFNumericFieldId EntityId;

}

//****************************************************************************
WorkSessionEntityList::WorkSessionEntityList (BFAbstractCBO &parent) : MFCanBFCbo (parent),
_bFundBroker(false)
{
   TRACE_CONSTRUCTOR (CLASSNAME, NULL_STRING);
   setObjectAsList();
}

//******************************************************************************
WorkSessionEntityList::~WorkSessionEntityList (void)
{
   TRACE_DESTRUCTOR (CLASSNAME);
}

//********************************************************************************************************
SEVERITY WorkSessionEntityList::init (const BFDataGroupId &idDataGroup, 
   const DString &dstrTrack /*= I_("N")*/, 
   const DString &dstrPageName /*= NULL_STRING*/)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("init"));

   return GETCURRENTHIGHESTSEVERITY();
}

//********************************************************************************************************
SEVERITY 
WorkSessionEntityList::getNewEntity (const BFDataGroupId& idDataGroup, Entity *&pEntityOut)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("getNewEntity"));

   DString newEntityId;

   //get the new generated entity id
   getStrKeyForNewItem (newEntityId);
   pEntityOut = new Entity (*this);
   //set the object as being new
   pEntityOut->setObjectNew();
   if (pEntityOut->init (newEntityId, idDataGroup) <= WARNING)
   {

      BFObjectKey objKey (newEntityId, idDataGroup, 
         OBJ_ACTIVITY_ADDED, OBJ_TYPE_ENTITY);

      setObject (objKey, pEntityOut);
   }
   else
   {
      delete pEntityOut;
      pEntityOut = NULL;
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//********************************************************************************************************
SEVERITY 
WorkSessionEntityList::getEntity (const BFDataGroupId &idDataGroup, 
   const DString &strEntityNum, Entity *&pEntityOut)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("getEntity"));

   DString strEntityNumTemp (strEntityNum);

   strEntityNumTemp.strip();
   strEntityNumTemp.stripLeading ('0');

   BFObjectKey objKey (strEntityNumTemp, idDataGroup, 
      OBJ_ACTIVITY_NONE, OBJ_TYPE_ENTITY);
   Entity *pEntity = dynamic_cast<Entity*> (findObject (objKey));

   if (!pEntity)
   {
      pEntityOut = new Entity (*this);
      if (pEntityOut->init (strEntityNumTemp) > WARNING)
      {
         delete pEntityOut;
         pEntityOut = NULL;
      }
      else
      {
         setObject (objKey, pEntityOut);
      }
   }
   else //get the account from the repository
   {
      pEntityOut = pEntity;
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY 
WorkSessionEntityList::PopulateEntity (const BFDataGroupId &idDataGroup, 
   const BFData &entityData, Entity *&pEntityOut)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("PopulateEntity"));

   DString strEntityNum = entityData.getElementValue (ifds::EntityId, 2 /*DataElement::USE_MASK*/);

   strEntityNum.strip().stripLeading (I_CHAR ('0'));

   BFObjectKey objKey (strEntityNum, idDataGroup, 
      OBJ_ACTIVITY_NONE, OBJ_TYPE_ENTITY);

   Entity *pEntity = dynamic_cast<Entity*> (findObject (objKey));

   if (!pEntity)
   {
      pEntityOut = new Entity (*this);
      if (pEntityOut->init (entityData) > WARNING)
      {
         delete pEntityOut;
         pEntityOut = NULL;
      }
      else
      {
         setObject (objKey, pEntityOut);
      }
   }
   else //get the entity from the repository
   {
      pEntityOut = pEntity;
   }
   return GETCURRENTHIGHESTSEVERITY();
}


//******************************************************************************
SEVERITY WorkSessionEntityList::doCreateNewObject(
      BFCBO *&pBase, 
      DString &strKey, 
      const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateNewObject" ) );
   Entity* pEntity = NULL; 
   DString newEntityId;

   newEntityId = strKey;
   pEntity = new Entity (*this);
   pEntity->init (newEntityId, idDataGroup);
      
   pBase = pEntity;
   return GETCURRENTHIGHESTSEVERITY();
}
//********************************************************************************************************
SEVERITY WorkSessionEntityList::refreshEntity (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "refreshEntity" ) );

   Entity *pEntity;

   BFObjIter iter (*this, idDataGroup);
   iter.begin();

   while (!iter.end())
   {
		pEntity = dynamic_cast<Entity*> (iter.getObject());		   

		/*
			needsRefresh() is for update from another cbo and impact to Entity by view update,
			Entity CBO should be invoked view call (refresh).
			Check isUpdatedForDataGroup is for Entity modification, it should
			be invoked view call everytime entity modified to inquire new
			version of data to avoid the version number error. Whenever modification
			entity from another CBO after modify entity itself. View program will
			check version to update entity info, so Entity should be latest information (version) before update.
		*/
		if(pEntity->needsRefresh() || pEntity->isUpdatedForDataGroup (idDataGroup))
		{	
			iter.removeObjectFromMap();
			continue;
		}
		++iter;
   } 

   return GETCURRENTHIGHESTSEVERITY();
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/WorkSessionEntityList.cpp-arc  $
// 
//    Rev 1.9   May 02 2005 11:07:52   yingbaol
// Incident300186: EUSD option is not applicable for FundBroker 
// 
//    Rev 1.8   Mar 01 2005 11:52:40   yingbaol
// PET1137,FN01: EU saving entity update
// 
//    Rev 1.7   Nov 14 2004 14:59:26   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.6   Jan 02 2004 15:12:14   popescu
// PTS 10025696, NASU flow crash 
// 
//    Rev 1.5   Mar 21 2003 18:28:38   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.4   Nov 18 2002 10:54:32   PURDYECH
// BFObjectKey changes.
// 
//    Rev 1.3   Oct 09 2002 23:55:16   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.2   Aug 29 2002 12:57:02   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.1   22 May 2002 18:30:14   PURDYECH
// BFData Implementation
// 
//    Rev 1.0   Oct 02 2001 15:00:06   YINGBAOL
// Initial revision.
// 

  
 *
 */