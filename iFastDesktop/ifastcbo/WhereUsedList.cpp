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
// ^FILE   : WhereUsedListcpp
// ^AUTHOR : Shaobo Huang
// ^DATE   : 09/17/1999
//
// ^CLASS    : WhereUsedList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "whereused.hpp"
#include "whereusedlist.hpp"
#include "Entity.hpp"


#include <ifastdataimpl\dse_dstc0061_req.hpp>
#include <ifastdataimpl\dse_dstc0061_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest WHERE_USED;
}

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME  = I_( "WhereUsedList" );
   
   // Where Use Type (WhereUsed)
   const I_CHAR * const FUNDBROKER				= I_( "01" );
   const I_CHAR * const ACCOUNT					= I_( "02" );
   const I_CHAR * const CLIENT					= I_( "03" );
   const I_CHAR * const FUND					= I_( "04" );
   const I_CHAR * const FUNDSPONSOR				= I_( "05" );
   const I_CHAR * const EXT_PRODUCT_PROVIDER	= I_( "12" );

   // Relationship (EntityType)
   const I_CHAR * const PAYING_AGENT	= I_( "04" );
   const I_CHAR * const NETWORK_SENDER	= I_( "06" );
   const I_CHAR * const PRIMARY_CONTACT	= I_( "02" );
   const I_CHAR * const REG_AGENT		= I_( "14" );
}

namespace CND
{  // Conditions used
	extern const long ERR_AT_LEAST_ONE_OBJECT_MUST_SETUP;
	extern const long ERR_DUPLICATE_RECORD;	
	extern const long ERR_ONE_FS_WHERE_USE;
}

namespace ifds
{   
   extern CLASS_IMPORT const BFNumericFieldId EntityId;
   extern CLASS_IMPORT const BFDateFieldId EffectiveDate;
   extern CLASS_IMPORT const BFDateFieldId StopDate;
}

//******************************************************************************
WhereUsedList::WhereUsedList( BFAbstractCBO &parent )
: MFCanBFCbo( parent ),_requestData(ifds::DSTC0061_REQ)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   setObjectAsList( );
}


//******************************************************************************
WhereUsedList::~WhereUsedList( void )
{
   TRACE_DESTRUCTOR( CLASSNAME );
}


//********************************************************************************
SEVERITY WhereUsedList::init( const DString& dstrEntityId,
                              const DString& dstrTrack,
                              const DString& dstrPageName,
							  const DString& dstrDuplicateCheck,
							  const DString& dstrEntityWhereUseRid,
				              const DString& dstrWhereUse,
				              const DString& dstrWhereUseCode,
				              const DString& dstrEntityType,
							  const DString& dstrEffectiveDate,
							  const DString& dstrStopDate)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("init( int, DString& )"));

   DString mgmtCoIdOut;
   DString entityWhereUseRid( dstrEntityWhereUseRid );

   if (entityWhereUseRid == NULL_STRING)
	   entityWhereUseRid = I_( "0" );

   _requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   _requestData.setElementValue( ifds::EntityId, dstrEntityId ); 
   _requestData.setElementValue( ifds::Track, dstrTrack );
   _requestData.setElementValue( ifds::Activity, dstrPageName );
   _requestData.setElementValue( ifds::DuplicateCheck, dstrDuplicateCheck );
   _requestData.setElementValue( ifds::EntityWhereUseRid, entityWhereUseRid );
   _requestData.setElementValue( ifds::WhereUse, dstrWhereUse );
   _requestData.setElementValue( ifds::WhereUseCode, dstrWhereUseCode );
   _requestData.setElementValue( ifds::EntityType, dstrEntityType );
   _requestData.setElementValue( ifds::OverrideRepeats, I_("0") );
   _requestData.setElementValue( ifds::EffectiveDate, dstrEffectiveDate);
   _requestData.setElementValue( ifds::StopDate, dstrStopDate);
   _requestData.setElementValue( ifds::RetSameCIFAcct, I_("N"));

   _entityID = dstrEntityId;

   bool allRecords = Entity::bUsedByEntityAlone? false:true; 

   ReceiveData( DSTC_REQUEST::WHERE_USED, _requestData, ifds::DSTC0061_VW, DSTCRequestor( getSecurity(),allRecords ) );
   

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************
SEVERITY WhereUsedList::getMore()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getMore" ) );

   if( doMoreRecordsExist() )
   {
      const DSTCSecurity* security = dynamic_cast<const DSTCSecurity *> ( getSecurity() );
      ReceiveData(DSTC_REQUEST::WHERE_USED, _requestData, ifds::DSTC0061_VW, DSTCRequestor(getSecurity(), false) );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************
SEVERITY WhereUsedList::init( const BFData& data )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   attachDataObject( const_cast<BFData&>(data), false, true );

   return(GETCURRENTHIGHESTSEVERITY());
}
//****************************************************************************
void WhereUsedList::initNew( const DString & entityID,  
							 const BFDataGroupId &idDataGroup )
{
   // There is at least one record must be exist.
   _entityID = entityID;
   BFObjectKey objKey(NULL_STRING, idDataGroup);
   getNewListItem( objKey );
}
//******************************************************************************
SEVERITY WhereUsedList::doCreateNewObject(BFCBO *& pBase, DString & strKey, const BFDataGroupId& idDataGroup )
   {
      MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateNewObject" ) );
      pBase = new WhereUsed(*this );
      ((WhereUsed* )pBase)->initNew( _entityID, idDataGroup );
      return(GETCURRENTHIGHESTSEVERITY());

   }

//*****************************************************************************************
SEVERITY WhereUsedList::doCreateObject( const BFData& data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );
   pObjOut = new WhereUsed( *this );

   ((WhereUsed* )pObjOut)->init( _entityID, const_cast<BFData&>(data) );

   return(GETCURRENTHIGHESTSEVERITY());
}

SEVERITY WhereUsedList:: doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );
   if( Entity::bUsedByEntityAlone )
   {
      BFObjIter iter( *this, idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED );
      int iNum = iter.getNumberOfItemsInList();
      if( iNum==0 || iNum == 1 && iter.isDummy() )
      {
         ADDCONDITIONFROMFILE (CND::ERR_AT_LEAST_ONE_OBJECT_MUST_SETUP);   
      }
   }  
   return(GETCURRENTHIGHESTSEVERITY());
}
//*********************************************************************************************
void  WhereUsedList:: getFiedByEntityTypeWhereUseCode( 
                          const DString& entityType,
                          const DString& whereUse,    
                          const BFFieldId& idField,
                          DString& strValue,
                          const BFDataGroupId& idDataGroup,
                          bool  lFormatted )
{
     DString strEntity,strWhereUse;
     BFObjIter iter( *this, idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED );
     while( !iter.end() )
     {
        BFAbstractCBO* pObj = iter.getObject();
        if( pObj )
        {
            
            pObj->getField(ifds::EntityType, strEntity,idDataGroup,false );
            pObj->getField(ifds::WhereUse, strWhereUse,idDataGroup,false );
            strEntity.strip();
            strWhereUse.strip();
            if( entityType == strEntity && whereUse == strWhereUse )
            {
                pObj->getField( idField, strValue, idDataGroup, lFormatted );
                break;                 
            }           
        }
        ++iter;
     }  
}

//*********************************************************************************************
SEVERITY WhereUsedList::checkDuplicate ( const WhereUsed *pWhereUseToCheck, const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_( "checkDuplicate" ) );   	
	
	DString dstrWhereUseToCheck, dstrWhereUsedCodeToCheck, dstrEntityTypeToCheck, dstrDuplicateCheck, dstrRecId;
	DString dstrEffectiveDateToCheck, dstrStopDateToCheck;
	
	pWhereUseToCheck->getField( ifds::WhereUse, dstrWhereUseToCheck, idDataGroup );
	pWhereUseToCheck->getField( ifds::WhereUseCode, dstrWhereUsedCodeToCheck, idDataGroup );
	pWhereUseToCheck->getField( ifds::EntityType, dstrEntityTypeToCheck, idDataGroup );
	pWhereUseToCheck->getField( ifds::DuplicateExist, dstrDuplicateCheck, idDataGroup );
	pWhereUseToCheck->getField( ifds::EntityWhereUseRid, dstrRecId, idDataGroup );
	pWhereUseToCheck->getField( ifds::EffectiveDate, dstrEffectiveDateToCheck, idDataGroup );
	pWhereUseToCheck->getField( ifds::StopDate, dstrStopDateToCheck, idDataGroup );

	dstrWhereUseToCheck.strip ();
	dstrWhereUsedCodeToCheck.strip().upperCase();
	dstrEntityTypeToCheck.strip();

	if ( dstrWhereUseToCheck == CLIENT &&	   
		 dstrWhereUsedCodeToCheck.empty() )		 
	{
		getMgmtCoId( dstrWhereUsedCodeToCheck );
	}
	dstrWhereUsedCodeToCheck.stripAll().upperCase();

	bool bHasDuplicate = false;
	
	//check first whether in the list (in memory) we have a duplicate
	BFObjIter iter( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED );
	iter.begin();
	while (!iter.end())
	{
		WhereUsed *pWhereUsed = dynamic_cast<WhereUsed*>(iter.getObject());
		// Don't check against itself
		if ( pWhereUsed != pWhereUseToCheck )
		{
			DString dstrCurrentWhereUse, dstrCurrentWhereUsedCode, dstrCurrentEntityType;
			DString dstrCurrentEffectiveDate, dstrCurrentStopDate;

			pWhereUsed->getField( ifds::WhereUse, dstrCurrentWhereUse, idDataGroup );
			pWhereUsed->getField( ifds::WhereUseCode, dstrCurrentWhereUsedCode, idDataGroup );
			pWhereUsed->getField( ifds::EntityType, dstrCurrentEntityType, idDataGroup );
			pWhereUsed->getField( ifds::EffectiveDate, dstrCurrentEffectiveDate, idDataGroup );
			pWhereUsed->getField( ifds::StopDate, dstrCurrentStopDate, idDataGroup );

			dstrCurrentWhereUse.strip ();
			dstrCurrentWhereUsedCode.strip().upperCase();
			dstrCurrentEntityType.strip();

			if ( dstrCurrentWhereUse  == dstrWhereUseToCheck &&
				dstrCurrentWhereUsedCode == dstrWhereUsedCodeToCheck &&
				dstrCurrentEntityType == dstrEntityTypeToCheck )
			{
				// check dates
				if( DSTCommonFunctions::dateRangesOverlap (dstrEffectiveDateToCheck, dstrStopDateToCheck,
														   dstrCurrentEffectiveDate, dstrCurrentStopDate))
				{
					bHasDuplicate = true;
					break;
				}
			}
			else if( dstrWhereUseToCheck == REG_AGENT)
			{
				if ( dstrCurrentWhereUse  == dstrWhereUseToCheck &&
					dstrCurrentWhereUsedCode == dstrWhereUsedCodeToCheck)
				{
					if( DSTCommonFunctions::dateRangesOverlap (dstrEffectiveDateToCheck, dstrStopDateToCheck,
						dstrCurrentEffectiveDate, dstrCurrentStopDate))
					{
						bHasDuplicate = true;
						break;
					}
				}
			}
		}
		++iter;
	}

	//finally, if no duplicates in memory, check the back-end
	if ( !bHasDuplicate && !getParent()->isNew() )
	{      	  
		WhereUsedList WhereUsedList((BFAbstractCBO&)(*this));

		if (dstrDuplicateCheck == NULL_STRING)
			dstrDuplicateCheck = I_("N");
		if (dstrRecId== NULL_STRING)
			dstrRecId = I_("0");

		//check duplicate, 
		if ( WhereUsedList.init( _entityID, I_("N"), NULL_STRING, dstrDuplicateCheck, dstrRecId, 
			                     dstrWhereUseToCheck, dstrWhereUsedCodeToCheck,
								 dstrEntityTypeToCheck, dstrEffectiveDateToCheck, dstrStopDateToCheck ) <= WARNING )										   
		{
			//we should get an exact match, so the DuplicateExist flag of the single section is set to Y or N
			DString dstrDuplicateExist;

			WhereUsedList.getField (ifds::DuplicateExist, dstrDuplicateExist, idDataGroup, false);
			bHasDuplicate = dstrDuplicateExist == I_("Y");
			
			//but if we found a duplicate, this might have been already deleted in the memory
			if ( bHasDuplicate )
			{ 
				//check the memory again for possible deleted duplicates
				BFObjIter iterInMemory(*this, idDataGroup);
				iterInMemory.begin();
				while ( !iterInMemory.end() )
				{
					if (iterInMemory.getKey().getActivity() == OBJ_ACTIVITY_DELETED )
					{
						WhereUsed *pDeletedWhereUsed = dynamic_cast<WhereUsed*>(iterInMemory.getObject());
						DString dstrDeletedWhereUse, dstrDeletedWhereUsedCode, dstrDeletedEntityType;
						DString dstrDeletedEffectiveDate, dstrDeletedStopDate;
                          
						pDeletedWhereUsed->getField( ifds::WhereUse, dstrDeletedWhereUse, idDataGroup );
						pDeletedWhereUsed->getField( ifds::WhereUseCode, dstrDeletedWhereUsedCode, idDataGroup );
						pDeletedWhereUsed->getField( ifds::EntityType, dstrDeletedEntityType, idDataGroup );
						pDeletedWhereUsed->getField( ifds::EffectiveDate, dstrDeletedEffectiveDate, idDataGroup );
						pDeletedWhereUsed->getField( ifds::StopDate, dstrDeletedStopDate, idDataGroup );

						dstrDeletedWhereUse.strip ();
						dstrDeletedWhereUsedCode.strip().upperCase();
						dstrDeletedEntityType.strip();
						

						if ( dstrWhereUseToCheck  == dstrDeletedWhereUse &&
							 dstrWhereUsedCodeToCheck == dstrDeletedWhereUsedCode &&
				             dstrEntityTypeToCheck == dstrDeletedEntityType &&
							 dstrEffectiveDateToCheck == dstrDeletedEffectiveDate &&
							 dstrEffectiveDateToCheck == dstrDeletedStopDate)
						{
							bHasDuplicate = false;
							break;
						}
					}
					++iterInMemory;
				}
			}
		}
	}

	if ( bHasDuplicate )
	{
		ADDCONDITIONFROMFILE(CND::ERR_DUPLICATE_RECORD);
	}

	return GETCURRENTHIGHESTSEVERITY();
}
//*********************************************************************************************
void WhereUsedList::getField( const BFFieldId& idField, DString& strFieldValue, const BFDataGroupId& idDataGroup, bool formattedReturn ) const
{
   if( idField == ifds::EntityId )
   {
	   strFieldValue = _entityID;
   }
   else
      BFCBO::getField( idField, strFieldValue, idDataGroup, formattedReturn );

}
//*********************************************************************************************
bool WhereUsedList::isNetworkSender (const BFDataGroupId& idDataGroup)
{
	bool bNetworkSender = false;

	DString strRelationship,strWhereUse;
    BFObjIter iter( *this, idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED );
    
	while( !iter.end() )
    {
		BFAbstractCBO* pObj = iter.getObject();
        if( pObj )
        {
            
            pObj->getField(ifds::EntityType, strRelationship,idDataGroup,false );
            pObj->getField(ifds::WhereUse, strWhereUse,idDataGroup,false );

            strRelationship.strip();
            strWhereUse.strip();

            if( strRelationship == NETWORK_SENDER && strWhereUse == CLIENT )
            {
				bNetworkSender = true;
                break;                 
            }           
        }
		++iter;
	}  

	return bNetworkSender;
}

//*********************************************************************************************
bool WhereUsedList::isNEQEntity (const BFDataGroupId& idDataGroup)
{
	bool bExternalProductProvider  = false;

	DString strRelationship,strWhereUse;
    BFObjIter iter( *this, idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED );
    
	while( !iter.end() )
    {
		BFAbstractCBO* pObj = iter.getObject();
        if( pObj )
        {
            
            pObj->getField(ifds::EntityType, strRelationship,idDataGroup,false );
            pObj->getField(ifds::WhereUse, strWhereUse,idDataGroup,false );

            strRelationship.strip();
            strWhereUse.strip();

            if( strRelationship == PRIMARY_CONTACT && strWhereUse == EXT_PRODUCT_PROVIDER)
            {
				bExternalProductProvider  = true;
                break;                 
            }           
        }
		++iter;
	}  

	return bExternalProductProvider;
}
//*********************************************************************************************
bool WhereUsedList::isFundSponsor (const BFDataGroupId& idDataGroup)
{
	bool bFundSponsor = false;

	DString strWhereUse;

    BFObjIter iter( *this, idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED );

	while( !iter.end() )
    {
		BFAbstractCBO* pObj = iter.getObject();
        if( pObj )
        {
            pObj->getField(ifds::WhereUse, strWhereUse,idDataGroup,false );
            strWhereUse.strip();

            if( strWhereUse == FUNDSPONSOR)
            {
				bFundSponsor = true;
                break;                 
            }           
        }
		++iter;
	}  

	return bFundSponsor;
}

//*********************************************************************************************
SEVERITY WhereUsedList::validateFundSponsor (const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateFundSponsor" ) );   	

	DString strWhereUse;

    BFObjIter iter( *this, idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED );
    
	int numItems = iter.getNumberOfItemsInList ();
			
    if (numItems == 1)
		return GETCURRENTHIGHESTSEVERITY();

	while( !iter.end() )
    {
		BFAbstractCBO* pObj = iter.getObject();
        if( pObj )
        {
            pObj->getField(ifds::WhereUse, strWhereUse,idDataGroup,false );
            strWhereUse.strip();

            if( strWhereUse == FUNDSPONSOR)
            {
				ADDCONDITIONFROMFILE( CND::ERR_ONE_FS_WHERE_USE );
                break;                 
            }           
        }
		++iter;
	}  

	return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/WhereUsedList.cpp-arc  $
 * 
 *    Rev 1.26   Mar 29 2012 21:15:08   wp040039
 * PETP0187485.FN01- CPF - Agent bank and CPFB 
 * Checking for Duplicate Regsitration agent.
 * 
 *    Rev 1.25   Jan 10 2011 04:27:02   wutipong
 * IN2261419 - Not able to add Clearing Platform Entity 
 * 
 *    Rev 1.24   Apr 30 2010 11:17:16   jankovii
 * Fixed function name change done for QESI.
 * 
 *    Rev 1.23   Apr 08 2010 06:58:10   wutipong
 * IN#2017702 -- CIF Data Fix Validation - CIF searching on Base & Desktop
 * 
 *    Rev 1.22   Apr 07 2010 09:40:22   jankovii
 * PET165541_FN01_QESI - RESP Gap_Dsk_Trading
 * 
 *    Rev 1.21   Aug 10 2007 15:47:28   jankovii
 * CIF stuff .
 * 
 *    Rev 1.20   Nov 20 2006 13:51:18   jankovii
 * PET 2287 FN01 - Grupo Mundial Trade Aggregation.
 * 
 *    Rev 1.19   Jul 21 2006 13:59:26   jankovii
 * PET 2192 FN02 - Dealings-Sender Cut-Off Time.
 * 
 *    Rev 1.18   Nov 28 2005 09:51:18   jankovii
 * PET1228_FN02_ EU Savings Directive Phase Two
 * 
 *    Rev 1.16   Nov 08 2005 16:14:34   jankovii
 * PET1228 - added support for duplicate check.
 * 
 *    Rev 1.15   May 17 2005 17:25:42   Fengyong
 * #Incident 272055 - Add more button to where used screen
 * 
 *    Rev 1.14   Apr 21 2005 13:16:14   yingbaol
 * Incident290503: add new method getFieldbyentitytypewhereuse(....)
 * 
 *    Rev 1.13   Mar 09 2005 16:05:26   yingbaol
 * PET 1171,FN01: EU saving entity update
 * 
 *    Rev 1.12   Mar 01 2005 11:52:34   yingbaol
 * PET1137,FN01: EU saving entity update
 * 
 *    Rev 1.11   Dec 02 2004 14:07:28   georgeet
 * PET1117 FN54 - Fund broker static 
 * 
 *    Rev 1.10   Nov 14 2004 14:59:24   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.9   Mar 21 2003 18:28:34   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.8   Oct 09 2002 23:55:14   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.7   Aug 29 2002 12:57:02   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.6   22 May 2002 18:30:14   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.5   03 May 2001 14:07:16   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.4   Jan 18 2001 16:10:40   YINGBAOL
 * add eTracker
 * 
 *    Rev 1.3   Dec 17 2000 20:24:52   OLTEANCR
 * changed to use a precompiled header
 * 
 *    Rev 1.2   Dec 06 2000 15:21:44   OLTEANCR
 * modif. ReceiveData
 * 
 *    Rev 1.1   Nov 01 2000 10:10:02   OLTEANCR
 * new data brokering system
 * 
 *    Rev 1.0   Feb 15 2000 11:00:08   SMITHDAV
 * Initial revision.
// 
//    Rev 1.5   Jan 05 2000 20:11:06   BUZILA
// adding list flag
// 
//    Rev 1.4   Dec 12 1999 16:26:00   POPESCUS
// Xchgdata issue; create and delete the object in the CBO
// 
//    Rev 1.3   Dec 09 1999 10:43:40   POPESCUS
// Fixed some memory leaks
*/