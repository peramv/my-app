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
//    Copyright 1998 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : EntityIdsList.cpp
// ^AUTHOR : Adrian Vasile
// ^DATE   : March 16, 1999
//
// ^CLASS    : EntityIdsList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "entityidslist.hpp"
#include "entityids.hpp"
#include "entity.hpp"
#include "whereused.hpp"
#include "whereusedlist.hpp"
#include "accountentityxref.hpp" //MT535/MT536
#include <ifastdataimpl\dse_dstc0051_vw.hpp>
#include <ifastdataimpl\dse_dstc0051_req.hpp>
#include <ifastdataimpl\dse_dstc0083_vw.hpp>
#include <ifastdataimpl\dse_dstc0003_req.hpp>
#include <ifastdataimpl\dse_dstc0003_vw.hpp>
#include <bfcbo\bfobjiter.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest ENTITY_IDS;
   extern CLASS_IMPORT const DSTCRequest SEARCH;
}

namespace
{
   //Trace literals
   const I_CHAR * const CLASSNAME         = I_( "EntityIdsList" );
   const I_CHAR * const ENTITY_ID         = I_( "ENTITY_ID" );
   const I_CHAR * const ID_VALUE          = I_( "ID_VALUE" );
   const I_CHAR * const INVESTRO          = I_( "02" );
   const I_CHAR * const SWIFT             = I_( "03" );
   const I_CHAR * const KVACCOUNTNUM      = I_( ",09");
   const I_CHAR * const BICCODE           = I_( ",10");

   const I_CHAR * const FUND_CUSTODIAN    = I_( "12" );
   const I_CHAR * const FUND_ACCOUNTANT   = I_( "13" );
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId RoutingType;
   extern CLASS_IMPORT const BFTextFieldId IdType;
   extern CLASS_IMPORT const BFTextFieldId XrefCountryOfIssue;
}

namespace CND
{
   extern const long ERR_ID_TYPE_REQUIRED;
   extern const long ERR_DUPLICATE_CLEARING_PLATFORM_ID_FOR_ENTITY; //MT535/MT536
   extern const long ERR_FUND_ACCOUNTANT_ENTITY_REQUIRE_FUND_ACCOUNTANT_ID;
   extern const long ERR_FUND_CUSTODIAN_ENTITY_REQUIRE_FUND_CUSTODIAN_ID;
   extern const long ERR_DUPLICATE_RECORD;
}

namespace IDS
{
   extern const I_CHAR * const DRIVERS_LICENSE;
   extern const I_CHAR * const PASSPORT;
   extern const I_CHAR * const NATIONAL_ID;
   extern const I_CHAR * const SIN;
   extern const I_CHAR * const BIC_CODE;
   extern const I_CHAR * const ADDITIONAL_ACCT_NUMBER;
   extern const I_CHAR * const CIF;
   extern const I_CHAR * const ACCESS_ID;
   extern const I_CHAR * const CLEARING_PLATFORM; //MT535/MT536
   extern const I_CHAR * const FUND_ACCOUNTANT;
   extern const I_CHAR * const FUND_CUSTODIAN;
   extern const I_CHAR * const CPFB_ACCNUM;
   extern const I_CHAR * const TAX_ID_NUMBER;
   extern const I_CHAR * const EMPLOYER_NUMBER;
   extern const I_CHAR * const BUSINESS_NUMBER;
   extern const I_CHAR * const FATCA_GIIN;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//  Field DD Id,              State Flags,      Group Flags
   {ifds::RoutingType,       BFCBO::CALCULATED_FIELD, 0}, 
};
static const int NUM_FIELDS = sizeof (classFieldInfo) / sizeof (BFCBO::CLASS_FIELD_INFO);

//******************************************************************************
EntityIdsList::EntityIdsList( BFAbstractCBO &parent )
: MFCanBFCbo( parent ),
_entityType (NULL_STRING),
_entityId (NULL_STRING)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   registerMemberData (NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0, NULL);
   setObjectAsList( );
}

//******************************************************************************
EntityIdsList::~EntityIdsList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY EntityIdsList::init ( const DString &entityId, 
                               const DString &entityType,
                               const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init( int... )" ) );

   _entityId = entityId;
   _entityType = entityType;

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY EntityIdsList::init ( const DString &entityId, 
                               const DString &entityType,
                               const DString &dstrTrack, 
                               const DString &dstrPageName)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_( "init( int... )" ) );

   _entityId = entityId;
   _entityType = entityType;

   BFData requestData (ifds::DSTC0051_REQ);

   DString mgmtCoIdOut;
   requestData.setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut));
   requestData.setElementValue (ifds::EntityId, entityId); 

   requestData.setElementValue (ifds::Track, dstrTrack);
   requestData.setElementValue (ifds::Activity, dstrPageName);

   ReceiveData ( DSTC_REQUEST::ENTITY_IDS, 
                 requestData, 
                 ifds::DSTC0051_VW, 
                 DSTCRequestor (getSecurity(), true));
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY EntityIdsList::init (BFData &data, 
                              const DString &entityId, 
                              const DString &entityType) //this is a repeat of view #51
{
   MAKEFRAME2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   _entityId = entityId;
   _entityType = entityType;
   createObjectForEachRepeat( data );
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
void EntityIdsList::getEntityId (DString &entityId) const
{
   entityId = _entityId;
}

//******************************************************************************
void EntityIdsList::setEntityType (const DString &entityType)
{
   _entityType = entityType;
}

//******************************************************************************
SEVERITY EntityIdsList::doCreateObject( const BFData& data, BFCBO*& pObjOut)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

   EntityIds* pEntityIds = new EntityIds( *this );

   pEntityIds->init (data, _entityId, _entityType);
   pObjOut = pEntityIds;

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY EntityIdsList::doCreateNewObject( BFCBO*& pBase, 
                                           DString& strKey, 
                                           const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateNewObject" ) );

   EntityIds* pEntityIds = new EntityIds( *this );

   pEntityIds->init (idDataGroup, _entityId, _entityType);
   pBase = pEntityIds;

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY EntityIdsList::doDeleteObject ( const DString &strKey, 
                                         const BFDataGroupId& idDataGroup, 
                                         bool bIsObjectDestroyed) 
{ 
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("doDeleteObject"));

   updateParentEntitySIN(idDataGroup);

   BFObjIter bfIter( *this, idDataGroup );
   if( bfIter.positionByKey(strKey) )
   {
      DString str;
      bfIter.getObject()->getField(ifds::IdType, str, idDataGroup, false );
      str.strip().upperCase();

      if(str == IDS::TAX_ID_NUMBER || str == IDS::EMPLOYER_NUMBER ||
         str == IDS::BUSINESS_NUMBER )
      {
         Entity* pEntity = dynamic_cast<Entity*>( getParent() );

         if(pEntity)
         {
            pEntity->responseIDRemoved(idDataGroup);
         }
      }

   }
   BFObjIter bfIter1 (*this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED, false);
   bfIter1.begin();
   while (!bfIter1.end())
   {
      DString idType,
         idValue;

      bfIter1.getObject()->getField (ifds::IdType, idType, idDataGroup);
      if ( idType == IDS::NATIONAL_ID || idType == IDS::FATCA_GIIN ||
           idType == IDS::PASSPORT    || idType == IDS::TAX_ID_NUMBER || 
           idType == IDS::EMPLOYER_NUMBER )
      {
         dynamic_cast<BFCBO*>(bfIter1.getObject())->revalidateField( ifds::XrefCountryOfIssue, idDataGroup );
      }
      if (GETCURRENTHIGHESTSEVERITY() > WARNING)
      {
         break;
      }
      ++bfIter1;
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//**************************************************************************************
SEVERITY EntityIdsList::checkForDuplicateClearingPlatform (const DString &clearingPlatformValue, 
                                                           const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("checkForDuplicateClearingPlatform"));

      BFData requestData (ifds::DSTC0003_REQ),
         responseData (ifds::DSTC0003_VW);
      DString mgmtCoIdOut, 
         strCopyOfClearingPlatform (clearingPlatformValue);

      requestData.setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut));
      if(Entity::bUsedByEntityAlone)
      {
        requestData.setElementValue (ifds::NextOrPrevious, N);
        requestData.setElementValue (ifds::AllAccounts, N);
        requestData.setElementValue (ifds::AllEntitys, Y);
      }
      else
      {
         requestData.setElementValue (ifds::AllAccounts, Y);
         requestData.setElementValue (ifds::AllEntitys, Y);
      }
      requestData.setElementValue (ifds::SortBy, I_("LN"));
      strCopyOfClearingPlatform.stripAll ('-');
      requestData.setElementValue (ifds::SrchIdType, IDS::CLEARING_PLATFORM);
      requestData.setElementValue (ifds::SrchIdValue, strCopyOfClearingPlatform);
      if (BFDataBroker::getInstance ()->receive (DSTC_REQUEST::SEARCH, 
            requestData, responseData, DSTCRequestor (getSecurity (), true)) <= WARNING)
      {
         int cRepeats = responseData.getRepeatCount ();
         for (int i = 0; i < cRepeats; i++)
         {
            DString searchEntityId;
            const BFData &data = responseData.getRepeat (i);

            searchEntityId = data.getElementValue (ifds::EntityId);
            if (_entityId.strip () != searchEntityId.strip ())
            {               
               //Only one clearing ID is allowed for Clearing Platform Entity
               ADDCONDITIONFROMFILE (CND::ERR_DUPLICATE_CLEARING_PLATFORM_ID_FOR_ENTITY);
               break;
            }
         }
      }   
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY EntityIdsList::doValidateAll (const BFDataGroupId& idDataGroup, 
                                       long lValidateGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateAll" ));

   if( GETCURRENTHIGHESTSEVERITY() > WARNING )
      return(GETCURRENTHIGHESTSEVERITY());

   //The validation for the required IDS is based on the System Options instead of the static defined ids
   DString mandatoryIds, 
      dstrIdsDesc, 
      dstrRoutingType;

   getWorkSession().getOption (ifds::MandatoryId, mandatoryIds, idDataGroup, false);
   getMandatoryIdsDesc (idDataGroup, mandatoryIds, dstrIdsDesc);
   if (!mandatoryIds.empty())
   {

      bool bValid = false;
      BFObjIter bfIter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED, false );
      bfIter.begin();
      while (!bfIter.end() && !bValid)
      {
         DString idType;
         bfIter.getObject()->getField( ifds::IdType, idType, idDataGroup );
         if (!bfIter.isDummy() && !idType.empty())
         {
            DString::size_type iFindPos = mandatoryIds.find (idType);
            bValid = (iFindPos == DString::npos) ? false : true;
            break;
         }
         ++bfIter;
      }
      if (!bValid)
      {
         DString dstrTemp, dstrEntityid = _entityId;
         dstrEntityid.strip().stripLeading( '0' );

         addIDITagValue( dstrTemp, I_("ENTITY_ID"), dstrEntityid );
         addIDITagValue( dstrTemp, I_("IDS"), dstrIdsDesc );
         ADDCONDITIONFROMFILEIDI (CND::ERR_ID_TYPE_REQUIRED, dstrTemp);
      }
   }
   BFObjIter bfIter1 (*this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED, false);
   bfIter1.begin();
   while (!bfIter1.end())
   {
      DString idType,
         idValue;

      bfIter1.getObject()->getField (ifds::IdType, idType, idDataGroup);
      bfIter1.getObject()->getField (ifds::IdValue, idValue, idDataGroup);
      if (idType == IDS::CLEARING_PLATFORM)
      {
         checkForDuplicateClearingPlatform (idValue, idDataGroup);
      }
      else if ( idType == IDS::NATIONAL_ID || idType == IDS::FATCA_GIIN ||
                idType == IDS::PASSPORT    || idType == IDS::TAX_ID_NUMBER || 
                idType == IDS::EMPLOYER_NUMBER )
      {
         dynamic_cast<BFCBO*>(bfIter1.getObject())->revalidateField( ifds::XrefCountryOfIssue, idDataGroup );
      }
      if (GETCURRENTHIGHESTSEVERITY() > WARNING)
      {
         break;
      }
      ++bfIter1;
   }

   //WhereUsed* pWhereUsed = dynamic_cast<WhereUsed*>( getParent() );
   Entity* pEntity = dynamic_cast<Entity*>( getParent() );

   if ( pEntity && pEntity->isFundSponsorEntity(idDataGroup) )
   {
      validateIDsForFundSponsorEntity( FUND_ACCOUNTANT, idDataGroup );
      validateIDsForFundSponsorEntity( FUND_CUSTODIAN, idDataGroup );
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
void EntityIdsList::getMandatoryIdsDesc( const BFDataGroupId& idDataGroup, 
                                         const DString& dstrMandIds, 
                                         DString& dstrIdsDesc) 
{
   dstrIdsDesc = NULL_STRING;
   if( dstrMandIds == NULL_STRING )
      return;

   DString dstrMandatoryIds = dstrMandIds + I_(",");
   //Get the IdType substitution list
   BFProperties * pBFProperties = getFieldProperties(ifds::IdType, idDataGroup );
   DString dstrSubstr = NULL_STRING;
   if( pBFProperties )
      pBFProperties->getAllSubstituteValues(dstrSubstr);
   if( dstrSubstr.strip() == NULL_STRING )
   {
      dstrIdsDesc = dstrMandatoryIds;
      return;
   }

   //parsing the MandatoryIds

   DString::size_type iCurPos, iNextSep;

   iCurPos =  0;
   iNextSep = dstrMandatoryIds.find( I_(",") );
   while( iNextSep != DString::npos )
   {
      DString dstrId;
      dstrId = dstrMandatoryIds.substr(iCurPos, iNextSep - iCurPos);
      iCurPos = iNextSep + 1;
      iNextSep = dstrMandatoryIds.find(I_(","), iCurPos);

      int idx;
      while( (idx = dstrSubstr.find_first_of(I_("="))) != DString::npos )
      {
         DString dstrCode, dstrDesc;
         dstrCode = dstrSubstr.substr(0, idx);
         dstrDesc = NULL_STRING;
         dstrSubstr.erase(0, idx + 1);                      // Skip to description
         if( (idx = dstrSubstr.find_first_of(I_( ";" ))) == DString::npos )
         {  // Couldn't find end of string
            dstrDesc = dstrCode;
            if( dstrIdsDesc != NULL_STRING )
               dstrIdsDesc += I_(", ");
            dstrIdsDesc += dstrDesc;
            break;
         }
         dstrDesc = dstrSubstr.substr( 0, idx );
         dstrSubstr.erase( 0, idx + 1 );
         if( dstrCode.strip().upperCase() == dstrId.strip().upperCase() )
         {
            if( dstrIdsDesc != NULL_STRING )
               dstrIdsDesc += I_(", ");
            dstrIdsDesc += dstrDesc;
            break;
         }
      }
   }
   if( dstrIdsDesc != NULL_STRING )
   {
      dstrIdsDesc = I_("\n[ ") + dstrIdsDesc;
      dstrIdsDesc += I_(" ]");
   }
}
//******************************************************************************
//MT535/MT536
bool EntityIdsList::isIdTypeExist( const DString& dstrIdType, const BFDataGroupId& idDataGroup )
{
   DString dstrIdTypeIn(dstrIdType);
   dstrIdTypeIn.strip();
   BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
   while( !iter.end() )
   {
      DString dstrIdType;
      iter.getObject()->getField(ifds::IdType, dstrIdType, idDataGroup, false);

      if( dstrIdType.strip() == dstrIdTypeIn)
      {
         return true;
      }
      ++iter; 
   }
   return false;
}

//******************************************************************************
bool EntityIdsList::isIdTypeExistWithValue( const DString& dstrIdType, const BFDataGroupId& idDataGroup )
{
   DString dstrIdTypeIn(dstrIdType);
   dstrIdTypeIn.strip().upperCase();
   BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
   while( !iter.end() )
   {
      DString dstrIdType, dstrIdValue;
      iter.getObject()->getField(ifds::IdType, dstrIdType, idDataGroup, false);
      iter.getObject()->getField(ifds::IdValue, dstrIdValue, idDataGroup, false);
      dstrIdValue.strip().upperCase();

      if( dstrIdType.strip().upperCase() == dstrIdTypeIn && 
          !dstrIdValue.empty())
      {
         return true;
      }
      ++iter; 
   }
   return false;
}

//******************************************************************************
//MT535/MT536
int EntityIdsList::getNumIdTypeRecord( const DString& dstrIdTypeIn, const BFDataGroupId& idDataGroup )
{
   BFObjIter iter( *this, idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED );
   int count = 0;

   while( !iter.end() )
   {
      DString dstrIdType;
      iter.getObject()->getField(ifds::IdType, dstrIdType, idDataGroup, false);

      if( dstrIdType.strip() == dstrIdTypeIn)
      {
         count++;
      }
      ++iter; 
   }
   return(count);
}

//******************************************************************************
bool EntityIdsList::isLinkedWithWhereUsedRelationship(const DString& strRelationship, const BFDataGroupId& idDataGroup)
{
   if (strRelationship.empty())
   {
      return false;
   }

   DString strLocalRelationship(strRelationship);
   strLocalRelationship.strip().upperCase();

   Entity* pEntity = dynamic_cast<Entity*>( getParent() );
   WhereUsedList* pList = NULL;

   bool bIsLinkedWithRelationship = false;
   if( pEntity->getWhereUsedList (pList, idDataGroup, false, false) <= WARNING )
   {
      if( pList )
      {
         BFObjIter iter( *pList, idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED );
         while (!iter.end())
         {
            DString strEntityType;

            iter.getObject()->getField(ifds::EntityType, 
                                       strEntityType, 
                                       idDataGroup,
                                       false);

            if ( strEntityType.strip().upperCase() == strRelationship )
            {
               bIsLinkedWithRelationship = true;
               break;
            }
            ++iter;
         }
      }
   }

   return bIsLinkedWithRelationship;
}

//******************************************************************************
SEVERITY EntityIdsList::validateIDsForFundSponsorEntity(const DString &strRelationship,const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_ ("validateIDsForFundSponsorEntity"));

   if ( isLinkedWithWhereUsedRelationship(strRelationship,idDataGroup) )
   {
      BFObjIter iter( *this, idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED );

      int iNumIDType = 0;

      while (!iter.end())
      {
         DString strEntityIDsType,
                  strEntityIDsValue;

         iter.getObject()->getField(ifds::IdType, 
                                    strEntityIDsType, 
                                    idDataGroup,
                                    false);
                                    
         DString strEntityIDsTypeCompare;
         
         if ( strRelationship == FUND_ACCOUNTANT )
         {
            strEntityIDsTypeCompare = IDS::FUND_ACCOUNTANT;
         }
         else 
         {
            strEntityIDsTypeCompare = IDS::FUND_CUSTODIAN;
         }

         if ( strEntityIDsType == strEntityIDsTypeCompare )
         {
            iNumIDType++;
         }
         ++iter;
      }

      if( iNumIDType == 0 )
      {
         if ( strRelationship == FUND_ACCOUNTANT)
         {
            ADDCONDITIONFROMFILE (CND::ERR_FUND_ACCOUNTANT_ENTITY_REQUIRE_FUND_ACCOUNTANT_ID);
         }
         else
         {
            ADDCONDITIONFROMFILE (CND::ERR_FUND_CUSTODIAN_ENTITY_REQUIRE_FUND_CUSTODIAN_ID);
         }
      }
      else if (iNumIDType > 1)
      {
         ADDCONDITIONFROMFILE ( CND::ERR_DUPLICATE_RECORD );
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY EntityIdsList::updateParentEntitySIN(const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_ ("updateParentEntitySIN"));

   DString dstrSIN = NULL_STRING;

   BFObjIter bfIter(*this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED, false);
   for(bfIter.begin(); !bfIter.end(); ++bfIter)
   {
      DString idType, idValue;

      bfIter.getObject()->getField (ifds::IdType, idType, idDataGroup);
      bfIter.getObject()->getField (ifds::IdValue, idValue, idDataGroup);
      if(idType == IDS::SIN)
      {
         dstrSIN = idValue;
         break;
      }
      if (GETCURRENTHIGHESTSEVERITY() > WARNING)
      {
         break;
      }
   }

   // note, if condition below can be removed when missing entity-searchid record for SIN in entity-identity is fixed
   //if( dstrSIN != NULL_STRING )
   //{
      Entity* pEntity = dynamic_cast<Entity*>( getParent() );
      pEntity->setField(ifds::SIN, dstrSIN, idDataGroup);
   //}

   return GETCURRENTHIGHESTSEVERITY();
}
/**************************************************************************************
Input:IdType to check
Return:bool IDExists return true if a match found
Functionality:Call the function to check if an ID exists in DB using the return value from View
/*******************************************************************************************/
bool EntityIdsList::bCheckIdTypeExistsInDB(DString dstrIdTypeIn )
{
   dstrIdTypeIn.strip();
   BFObjIter iter( *this, BF::HOST);
   while( !iter.end() )
         {
              DString dstrIdType;
              iter.getObject()->getFieldBeforeImage ( ifds::IdType, dstrIdType, false);
              if( dstrIdType.strip() == dstrIdTypeIn )
                  {
                     return true;
                   }
                ++iter; 
           }
            return false;
}
//******************************************************************************
SEVERITY EntityIdsList::getIdByType(const DString& idType, const BFDataGroupId &idDataGroup, DString& id)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("getIdByType"));

   BFObjIter iter (*this, idDataGroup);

   while (!iter.end())
   {
      DString dstrIdType;

      iter.getObject()->getField (ifds::IdType, dstrIdType, idDataGroup);

      if (dstrIdType == idType)
      {
         iter.getObject()->getField (ifds::IdValue, id, idDataGroup);
         break;
      }

      ++iter;
   }

   return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/EntityIdsList.cpp-arc  $
 * 
 *    Rev 1.37   Jul 12 2012 18:47:56   dchatcha
 * P0191601 FN03 - Manual T3/RL 16/NR4 Slip for Taxable Trusts.
 * 
 *    Rev 1.36   Apr 05 2012 10:54:38   wp040039
 * PETP0187485-Entity Maintenance
 * 
 *    Rev 1.35   Jan 19 2012 15:42:00   yingz
 * change code to fix the bad data issue which may cause SIN in entity to be wiped out
 * 
 *    Rev 1.34   Jul 26 2011 00:42:16   wutipong
 * IN#2473119 - ECF Marketing File - revised
 * 
 *    Rev 1.33   Apr 19 2011 10:30:06   wutipong
 * IN#2473119 - Acct Marketing File Issue - revised.
 * 
 *    Rev 1.32   Apr 08 2011 12:04:52   wutipong
 * IN#2473119 - Acct Marketing File Issue
 * 
 *    Rev 1.31   Oct 02 2009 04:54:42   dchatcha
 * P0163546 FN01 TA Automate Fund Transfer, Fix Compile issue.
 * 
 *    Rev 1.30   Oct 01 2009 11:41:08   dchatcha
 * P0163546 FN01 TA Automate Fund Transfer, Code review.
 * 
 *    Rev 1.29   Sep 28 2009 07:56:42   dchatcha
 * P0163546 FN01 TA Automate Fund Transfer.
 * 
 *    Rev 1.28   26 Jan 2009 12:07:52   popescu
 * Incident 1559745 - find clearing platform entities whether they were linked or not to an account - 
 * 
 *    Rev 1.27   23 Jan 2009 16:32:36   popescu
 * Incident 	1548019 - reset button on entitymaintenance dlg, BIC Code can be valid/invalid for entitytype 58
 * 
 *    Rev 1.26   16 Jan 2009 17:23:14   popescu
 * Incident 1544134 - various fixes
 * 
 *    Rev 1.25   Dec 15 2008 01:49:40   phiwponp
 * PET0007773_FN01_MT535-MT536 Enhancement.
 * 
 *    Rev 1.24   16 Aug 2007 12:51:14   popescu
 * Incident# 977474 - access id shhould not be created by the user
 * 
 *    Rev 1.23   17 Jul 2007 15:19:06   popescu
 * GAP 6 CIF - AIM
 * 
 *    Rev 1.22   06 Jul 2007 14:43:20   popescu
 * PET 2363 GAP 6 CIF
 * 
 *    Rev 1.21   Dec 09 2004 15:28:24   Fengyong
 * Move the routing type and idtype validation to fund broker cbo,  removed "entity " for the error message "IDType needed for the specific routing type"
 * 
 *    Rev 1.20   Dec 01 2004 16:02:26   Fengyong
 * PET1117FN54 - minor change
 * 
 *    Rev 1.19   Nov 25 2004 11:52:30   Fengyong
 * base data fix chnaged code for pricetype and routing type
 * 
 *    Rev 1.18   Nov 14 2004 14:36:42   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.17   Nov 04 2004 11:01:04   FENGYONG
 * PET1117 FN54 - Fund broker static temp check in for 59 build
 * 
 *    Rev 1.16   Jan 02 2004 15:12:02   popescu
 * PTS 10025696, NASU flow crash 
 * 
 *    Rev 1.15   Nov 08 2003 21:46:14   popescu
 * PTS 10023438, performance issues fixes, do not call PopulateWhereUsed anymore, data is in memory
 * 
 *    Rev 1.14   Mar 21 2003 18:08:16   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.13   Oct 09 2002 23:54:26   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.12   Aug 29 2002 12:55:44   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.11   22 May 2002 18:28:32   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.10   Jul 29 2001 14:55:42   YINGBAOL
 * add doreset
 * 
 *    Rev 1.9   03 May 2001 14:06:26   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.8   Jan 18 2001 16:04:48   YINGBAOL
 * add eTracker
 * 
 *    Rev 1.7   Dec 17 2000 20:23:18   OLTEANCR
 * changed to use a precompiled header
 * 
 *    Rev 1.6   Dec 06 2000 11:05:02   OLTEANCR
 * changed ReceiveData
 * 
 *    Rev 1.5   Nov 02 2000 13:22:48   YINGBAOL
 * use new databroker
 * 
 *    Rev 1.4   Oct 04 2000 16:38:54   WINNIE
 * do not give error message for dummy record
 * 
 *    Rev 1.3   Aug 01 2000 15:59:14   ZHANGCEL
 * SIN problem
 * 
 *    Rev 1.2   Jul 28 2000 16:56:00   HUANGSHA
 * added back validateAll()
 * 
 *    Rev 1.1   Jul 20 2000 14:39:02   HUANGSHA
 * moved the validateAll handling to AccountEntityXref.cpp
 * 
 *    Rev 1.0   Feb 15 2000 10:59:58   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.18   Feb 01 2000 14:36:26   BUZILA
 * added lValidateGroup parameter to doValidateAll method
 * 
 *    Rev 1.17   Jan 06 2000 16:38:40   VASILEAD
 * Added  setObjectAsList
 * 
 *    Rev 1.16   Jan 06 2000 16:21:12   VASILEAD
 * Business edits for Entity screen
 * 
 *    Rev 1.15   Dec 24 1999 15:18:26   VASILEAD
 * Fixed transactions
 * 
 *    Rev 1.14   Dec 23 1999 15:48:18   VASILEAD
 * Added ids validation
 * 
 *    Rev 1.13   Dec 23 1999 14:18:02   VASILEAD
 * Added validation for ids
 * 
 *    Rev 1.12   Dec 12 1999 16:25:18   POPESCUS
 * Xchgdata issue; create and delete the object in the CBO
// 
*/