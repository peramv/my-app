
//******************************************************************************
//
// ^FILE   : DSTCAWDSession.cpp
// ^AUTHOR : Yingbao Li
// ^DATE   : Dec. 18, 2003
//
// ^CLASS    : DSTCAWDSession
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
//#include <ifastcbo\mfcancbo.hpp>
//#include <boost\utility.hpp>
//#include <core\bfsessn\bfcpsession.hpp>

#include "DSTCAWDSession.hpp"
#include <ifastcbo\DSTCWorkSession.hpp>
#include <ifastcbo\mgmtco.hpp>
#include <ifastcbo\errmsgruleslist.hpp>

#include <bfsessn\bfawdsession.hpp>
#include <bfawdi\bfawdinterface.hpp>
#include <bfsessn\bfcpsessiontags.h>
#include "DSTCAWDDataConvert.hpp"
#include <ifastdataimpl\dse_dstc0051_vw.hpp>
#include <ifastdataimpl\dse_dstc0050_vw.hpp>


namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME       = I_( "DSTCAWDSession" );
   const I_CHAR *AWD_PTR				= I_("_AwdInterface_Ptr_");
   const I_CHAR *YES					= I_("Y");
   const I_CHAR *NO					= I_("N");

   const I_CHAR *UPDATE_AWD				= I_( "UPDATE AWD" );
   const I_CHAR *CALL_INQURY			= I_( "CALL INQUIRY" );
   const I_CHAR *OperatorExtension      = I_("OperatorExtension" ) ;
   const I_CHAR *CreateAwdObject		= I_("CreateAwdObject" ) ;
   const I_CHAR *Business_Area			= I_("Business_Area");
   const I_CHAR *LobTag_ObjId			= I_("OBJI");
   const I_CHAR *System					= I_("SYST");
   const I_CHAR *Comment_Flag			= I_("COMF");
   const int  MAX_COMMENT_LEN			= 250;
   const I_CHAR * const WORKSTATION     = I_( "WORKSTATION" );

}



namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId Using_AWD;
   extern CLASS_IMPORT const BFTextFieldId BusinessArea;
   extern CLASS_IMPORT const BFTextFieldId WorkType;
   extern CLASS_IMPORT const BFTextFieldId StatusDesc;
   extern CLASS_IMPORT const BFTextFieldId Batch;
   extern CLASS_IMPORT const BFTextFieldId Remarks;
   extern CLASS_IMPORT const BFTextFieldId AWDComment;
   extern CLASS_IMPORT const BFTextFieldId Option;
   extern CLASS_IMPORT const BFNumericFieldId AccountNum;
   
   extern CLASS_IMPORT const BFTextFieldId CallerName;
   extern CLASS_IMPORT const BFTextFieldId Operator_Extension;
   extern CLASS_IMPORT const BFTextFieldId RelationShip;
   extern CLASS_IMPORT const BFTextFieldId BusinessPhone;
   extern CLASS_IMPORT const BFTextFieldId BusinessExt;
   extern CLASS_IMPORT const BFTextFieldId HomePhone;
   extern CLASS_IMPORT const BFTextFieldId CallStartTime;
   extern CLASS_IMPORT const BFTextFieldId CallEndTime;
   extern CLASS_IMPORT const BFTextFieldId CompanyId;
   extern CLASS_IMPORT const BFTextFieldId User_Id;
   extern CLASS_IMPORT const BFTextFieldId BOTime;
   extern CLASS_IMPORT const BFTextFieldId SegStartTime;
   extern CLASS_IMPORT const BFTextFieldId SegEndTime;
   extern CLASS_IMPORT const BFTextFieldId System;

//   extern CLASS_IMPORT const BFTextFieldId Remark1;  // for Awd remark
}


namespace CND
{  // Conditions used
   extern const I_CHAR *IFASTAWD_CONDITION;
   extern const long ERR_BUSINESS_WORKTYPE_STATUS;
   extern const long ERR_NO_AWD_SOURCE_IMAGE;
   extern const long ERR_AWD_APPLICATION;
   extern const long ERR_NO_AWD_OBJECT_CLONE;
   extern const long ERR_COMMENTS_MANDATORY;
   extern const long ERR_NO_COMMENTS;
}


namespace SessionTags
{
   const I_CHAR *CALL_START_TIME     = I_("STIM");
   const I_CHAR *CALL_END_TIME       = I_("ETIM");

}


namespace DSTCAwdSession
{
   const I_CHAR *FrGetAwdObject      = I_("FrGetAwdObject" ) ;
}


//********************************************************************************
DSTCAWDSession::DSTCAWDSession (BFCPSession* pParent) : BFCPSession(),
m_pParent (pParent),
m_pAwdInterface (NULL),
m_pConvert (NULL),
m_pCaseData (NULL),
m_AwdWorkData (NULL),
m_bOrgUpdated (false),
m_pAwdOriginalWork(NULL)
{
   TRACE_CONSTRUCTOR (CLASSNAME, NULL_STRING);

}
//**********************************************************************************
DSTCAWDSession::~DSTCAWDSession( void )
{
   TRACE_DESTRUCTOR (CLASSNAME);

   if (m_pConvert)
	{
		delete m_pConvert;
		m_pConvert=NULL;
	}
	if (m_pCaseData)
	{
		delete m_pCaseData;
		m_pCaseData = NULL;
	}
	saveOperatorExtension ();
}
//**********************************************************************************
void DSTCAWDSession::setAwdField ( const DString &dstrName, 
                                   const DString &dstrValue)
{
	m_AWDData.setElementValue (dstrName, dstrValue, true);
}

//**********************************************************************************
void DSTCAWDSession::setAwdField ( const BFFieldId &idField,
                                   const DString &dstrValue)
{
	m_AWDData.setElementValue (idField, dstrValue, true);
}	

//**********************************************************************************
void DSTCAWDSession::getAwdField ( const DString &dstrName, 
                                   DString &dstrValue)
{
   if (m_AWDData.exists (dstrName))
   {
      // Found, return it.
      dstrValue = m_AWDData.getElementValue (dstrName);
   }
   else 
   {
      dstrValue = NULL_STRING;  
   }
}

//**********************************************************************************
void DSTCAWDSession::getAwdField ( const BFFieldId &idField,
								           DString &dstrValue)
{
   if (m_AWDData.exists (idField ))
   {
      // Found, return it.
      dstrValue = m_AWDData.getElementValue (idField);
   }
   else 
   {
      dstrValue = NULL_STRING;   
   }
}


//************************************************************************************
void DSTCAWDSession::init (DSTCWorkSession *pWorkSession)
{
	associateDSTCWorkSession (pWorkSession);
}	

//************************************************************************************
void DSTCAWDSession::associateDSTCWorkSession (DSTCWorkSession *pWorkSession, bool bIgnoreSessionCheck)
{
	if (pWorkSession && m_pWorkSession != pWorkSession || bIgnoreSessionCheck)
	{
		m_pWorkSession = pWorkSession;
		
      DString dstrMgmtCo,
         dstrBusiness;
		
      m_pWorkSession->getMgmtCo().getField (ifds::CompanyId, dstrMgmtCo, BF::HOST, false);
		getAWDDataConvert()->retrieveAwdBusinessArea (dstrMgmtCo, dstrBusiness);
		setAwdField (ifds::BusinessArea,	dstrBusiness);
		
      DString dstrUserId;
		const DSTCSecurity *pSecurity = 
            dynamic_cast<const DSTCSecurity *> (m_pWorkSession->getSecurity(DSTCHost::getPrimaryHost()));
		
      dstrUserId = pSecurity->getUserId();
		setAwdField (ifds::User_Id, dstrUserId);
// For Transfer Agency - Canadian market
      if (DSTCommonFunctions::getMarket() == MARKET_IDS::CANADA)
      {
         setAwdField (ifds::System, I_("COR"));
      }
      else if (DSTCommonFunctions::getMarket() == MARKET_IDS::LUXEMBOURG)
      {
         setAwdField (ifds::System, I_("MAS"));
      }
      setupWorkArea (UPDATE_AWD);  // set up a defaultone for ID caller
		getOperatorExtension ();                         
		setAwdField (CreateAwdObject,I_("N"));
//Incident# 544677 - correctly record the time when work starts
      setSessionData (SessionTags::BEGIN_TIME, getTimeStamp());
	}
}	
//************************************************************************************
BFAwdInterface* DSTCAWDSession::getAwdInterface()
{
  if (m_pAwdInterface == NULL)
  {
      if (BFCPSession::usingAwd())
	   {
         DString dstrSourcePtr = getSessionData( AWD_PTR );
         m_pAwdInterface = (BFAwdInterface *) dstrSourcePtr.asInteger();		
      }	
  }
  return m_pAwdInterface;
}

//*************************************************************************************
// return dstring contains business area 
string_vector DSTCAWDSession::getAwdBusinessAreaList ()
{
	string_vector vec;
	if (getAwdInterface())
	{
	  vec =  getAwdInterface()->getBusinessAreaList();
	}
	return vec;
}

//***************************************************************************************
string_vector DSTCAWDSession::getAwdStatusList( const DString& dstrBussArea, const DString& dstrWkType )
{
	//we need to filter the status list using the original work object (rather than the previous clone) Linh, Jan 29, 2008
    const BFAwdData *pAwdWork = m_pAwdOriginalWork;
	if( !pAwdWork )
	{
		//OK, no cloning has been done, so get the current work object
		pAwdWork = getAwdSession()->getProcessWork();
	}

	string_vector vec;
	if( getAwdInterface() )
	{
      ConfigManager *pMgr = ConfigManager::getManager( I_( "Session" ) );
      Configuration cfgDefaults = pMgr->retrieveConfig( I_("Defaults")  );	
      DString dstrCrossRef = cfgDefaults.getValueAsString( I_("AWD Queue / Status Cross-reference") ).stripAll( I_CHAR('\t') );
	  DString dstrUnfilteredStatuses = cfgDefaults.getValueAsString( I_("unfilteredStatusList") ).stripAll( I_CHAR('\t') );

		if( pAwdWork )
		{
			if( dstrUnfilteredStatuses == I_("Y") )
			{
			  if( dstrCrossRef == I_("Y") )
			  {
			    vec = getAwdInterface()->getStatusList(pAwdWork->getKey() );
			  }
			  else
			  {
			    vec = getAwdInterface()->getStatusList() ;
			  }// client ask for all the status---March 22,2004; Added Flag July 15, 2005
			}
			//else go with the default implementation of filtering the status list based on queue, business area and workType
			else
			{
				vec = getAwdInterface()->getStatusList(pAwdWork->getKey(), dstrBussArea, dstrWkType );
			}
		}
		else
		{
           vec = getAwdInterface()->getStatusList();
		}
	}
	return vec;
}

//***************************************************************************************
//*
//
bool DSTCAWDSession::isAWDWorking()
{
   bool bRet = false;
	try
	{
	   if (getAwdSession() != NULL) 
	   {
		  bRet = true;
	   }	
	}
	catch (...)
	{
		assert(0);
	
	}
	return bRet;
}
//***************************************************************************************
DSTCAWDDataConvert* DSTCAWDSession::getAWDDataConvert()
{
	if( !m_pConvert )
	{
	
		m_pConvert =  new DSTCAWDDataConvert( this );
	}
	return m_pConvert;
}
//***************************************************************************************
bool DSTCAWDSession::hasWorkObject()
{
   const BFAwdData *pAwdWork = getAwdSession()->getProcessWork();
	
   return pAwdWork != NULL;
}
//***************************************************************************************
//dstrEventType:SessionTags::CREATE_WORK or SessionTags::UPDATE_WORK
SEVERITY DSTCAWDSession::createAWDObject (const DString& dstrEvent, DString& dstrEventType)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTAWD_CONDITION, CLASSNAME, I_("createAWDObject"));

	if (isAWDWorking ())
	{
      try
      {
         if (getAWDDataConvert() != NULL)
			{				
            BFData d;
   			 
				getAWDDataConvert()->getExportAwdCallerInfo (d ); // ID Caller Information should be always there
				getAWDDataConvert()->getAwdFormatData (dstrEvent, d); //I_( "UPDATE AWD" )
				
            DString dstrComment;

				getAwdField (SessionTags::AWD_COMMENT, dstrComment); 
				dstrComment.stripLeading().stripTrailing();
				if (dstrComment != NULL_STRING)
				{
					d.setElementValue (I_("40000"), YES, true);		//set the comment flag on				
				}
            else
            {
               if (dstrEventType == SessionTags::CREATE_WORK)
               {
                  d.setElementValue (I_("40000"), NO, true);   // set the comment flag to N
               }
            }
				
            BFDataPtrMap dummy;
				
            dummy.insert (BFDataPtrMap::value_type( SessionTags::DEFAULT, &d));
				setSessionData (SessionTags::AWD_EVENT, dstrEventType);
				setSessionData (SessionTags::AWD_PROPAGATE, YES); // do not clean the business area

				DString dstrBusiessArea,
                dstrWorkType,
                dstrStatus;
				
            getAwdField (ifds::BusinessArea,	dstrBusiessArea);
				getAwdField (ifds::WorkType, dstrWorkType);
				getAwdField (ifds::StatusDesc, dstrStatus);
				dstrBusiessArea.strip();
				dstrStatus.strip();
				dstrWorkType.strip();
				setSessionData (I_( "BusinessArea" ), dstrBusiessArea);
				setSessionData (I_("WorkType"), dstrWorkType);
				setSessionData (I_("Status"), dstrStatus);
   //Incident# 544677 - correctly record the time when work ends
            setAWDEndTime();
				setSessionEvent (dstrEvent, dummy);
				if (dstrEventType == SessionTags::CREATE_WORK)
				{
					BFAwdKeyVector keyList;
					// the code here is for the purpose of refreshing m_pAwdWork
					//pointer to point to the object just created
					getAwdInterface()->getAwdWorkObjects (keyList);

					BFAwdKeyVector::reverse_iterator iter;
					BFAwdKey *pKey = NULL;
					if (!keyList.empty())
					{
						iter = keyList.rbegin();
						pKey = *iter;
					}
					
               BFAwdData *pWork = new  BFAwdData (dstrBusiessArea, dstrWorkType, dstrStatus);
					
               if (pKey)
					{
						pWork->setKey (pKey);
					}
					if (getAwdSession()->getProcessWork() != NULL)
					{
						repositionWork (pWork);
					}
					else 
					{
						getAwdSession()->setProcessWork (pWork, true);
					}
					setAwdField (CreateAwdObject, YES);
				}
   //Incident# 544677 - correctly record the time when new work starts
            setAWDBeginTime();
				setAwdField (ifds::WorkType, NULL_STRING);
				setAwdField (ifds::StatusDesc, NULL_STRING);
				setAwdField (SessionTags::AWD_COMMENT, NULL_STRING);        // Clear Comment.  PTS 10028590				
				//setupWorkArea( UPDATE_AWD );  // restore the initial setting;
			 }			
		}
		catch (...)
		{
			assert(0);
		}
	}
	return(GETCURRENTHIGHESTSEVERITY());
}

//**************************************************************************************
//set up business area, work type and status
// if the field has not been set by GUI, get the value from INI file.
//

void DSTCAWDSession::setupWorkArea(const DString& dstrEvent )
{
	DString dstrBusiessArea,
      dstrStatus,
      dstrWorkType;

	// suport 2 layor override	
	DString dstrTable = I_( "WORK TYPE STATUS" );
	retrieveBusinessWorkStatusFromIni( dstrTable );

	ConfigManager *pMgr = ConfigManager::getManager( I_( "Session" ) );
	Configuration cfgTable = pMgr->retrieveConfig( dstrEvent  );	
    dstrTable= cfgTable.getValueAsString( I_("BusinessWorkStatus") ).stripAll( I_CHAR('\t') );
	retrieveBusinessWorkStatusFromIni( dstrTable );

	getAwdField(ifds::BusinessArea,	dstrBusiessArea );
	getAwdField(ifds::WorkType,		dstrWorkType );
	getAwdField(ifds::StatusDesc,		dstrStatus );
	dstrBusiessArea.strip();
	dstrStatus.strip();
	dstrWorkType.strip();
	setSessionData( I_( "BusinessArea" ), dstrBusiessArea );
	setSessionData( I_("WorkType"), dstrWorkType );
	setSessionData( I_("Status"), dstrStatus );
}
//***********************************************************************************
bool DSTCAWDSession::isCallStarted()
{
	DString dstrValue;
	getAwdField(ifds::CallStartTime,	dstrValue );
	dstrValue.stripAll();
	return ( dstrValue == NULL_STRING? false: true );
}
//***********************************************************************************
bool DSTCAWDSession::isBusinessAreaEmpty()
{
	DString dstrValue;
	getAwdField(ifds::BusinessArea,	dstrValue );
	dstrValue.stripAll();
	return ( dstrValue == NULL_STRING? true: false );
}

//***********************************************************************************
bool DSTCAWDSession::isWorkTypeEmpty()
{
	DString dstrValue;
	getAwdField(ifds::WorkType,	dstrValue );
	dstrValue.stripAll();
	return ( dstrValue == NULL_STRING? true: false );
}
//***********************************************************************************
bool DSTCAWDSession::isStatusEmpty()
{
	DString dstrValue;
	getAwdField(ifds::StatusDesc,	dstrValue );
	dstrValue.stripAll();
	return ( dstrValue == NULL_STRING? true: false );
}
//************************************************************************************
void DSTCAWDSession::retrieveBusinessWorkStatusFromIni(DString& dstrTable)
{
	 DString dstrBusiessArea,dstrStatus,dstrWorkType;
	 ConfigManager *pMgr = ConfigManager::getManager( I_( "Session" ) );
	 Configuration cfgTable = pMgr->retrieveConfig( dstrTable );	
	 dstrBusiessArea = cfgTable.getValueAsString( I_("BusinessArea") ).stripAll( I_CHAR('\t') );
	 dstrWorkType = cfgTable.getValueAsString( I_("WorkType") ).stripAll( I_CHAR('\t') );
	 dstrStatus = cfgTable.getValueAsString( I_("Status") ).stripAll( I_CHAR('\t') );	
/*	 if( isBusinessAreaEmpty() )
	 {
		// setAwdField(ifds::BusinessArea,	dstrBusiessArea );
	 }
	 if( isWorkTypeEmpty() )
	 {
	 	setAwdField(ifds::WorkType,	dstrWorkType );

	 }
	 if( isStatusEmpty() )
	 {
	 	setAwdField(ifds::StatusDesc,	dstrStatus );
	 }
	 */
	if(	dstrWorkType!=NULL_STRING)
	{
	 	setAwdField(ifds::WorkType,	dstrWorkType );
	}
	if( dstrStatus  != NULL_STRING )
	{
		setAwdField(ifds::StatusDesc,	dstrStatus );
	}
}
//***********************************************************************************
void  DSTCAWDSession::cleanCallerInfo()
{
	DString dstrValue(NULL_STRING);
	setAwdField(ifds::CallStartTime,dstrValue );
	setAwdField(ifds::CallEndTime,dstrValue );
	setAwdField(ifds::CallerName,dstrValue );
	setAwdField(ifds::HomePhone,dstrValue );
	setAwdField(ifds::BusinessPhone,dstrValue );
	setAwdField(ifds::BusinessExt,dstrValue);
	setAwdField(ifds::RelationShip,dstrValue ); // the field used as relationship
}

//************************************************************************************
void DSTCAWDSession::storeCallerInfo(DSTCAWDSession *pSession)
{
	if( pSession )
	{
		DString dstrValue;
		pSession->getAwdField(ifds::CallStartTime,dstrValue );
		setAwdField(ifds::CallStartTime,dstrValue );
		pSession->getAwdField(ifds::CallEndTime,dstrValue );
		setAwdField(ifds::CallEndTime,dstrValue );
		pSession->getAwdField(ifds::CallerName,dstrValue );
		setAwdField(ifds::CallerName,dstrValue );
		pSession->getAwdField(ifds::HomePhone,dstrValue );
		setAwdField(ifds::HomePhone,dstrValue );
		pSession->getAwdField(ifds::BusinessPhone,dstrValue );
		setAwdField(ifds::BusinessPhone,dstrValue );
		pSession->getAwdField(ifds::BusinessExt,dstrValue );
		setAwdField(ifds::BusinessExt,dstrValue);
		pSession->getAwdField(ifds::RelationShip,dstrValue );
		setAwdField(ifds::RelationShip,dstrValue );
		pSession->getAwdField(ifds::Operator_Extension,dstrValue );
		setAwdField(ifds::Operator_Extension,dstrValue );

		pSession->getAwdField(ifds::SegStartTime,dstrValue );
		setAwdField(ifds::SegStartTime,dstrValue );
		pSession->getAwdField(ifds::SegEndTime,dstrValue );
		setAwdField(ifds::SegEndTime,dstrValue );
	}
}
//************************************************************************************
void DSTCAWDSession::setAWDBeginTime ()
{
	DString dstrTime = getTimeStamp();
   setSessionData (SessionTags::BEGIN_TIME, getTimeStamp());
}

//*************************************************************************************
void DSTCAWDSession::setAWDEndTime ()
{
	DString dstrTime = getTimeStamp();
	setSessionData (SessionTags::END_TIME, dstrTime);
}

//***********************************************************************************
SEVERITY DSTCAWDSession::CallInquiry()
{
    MAKEFRAMEAUTOPROMOTE2( CND::IFASTAWD_CONDITION, CLASSNAME, I_( "CallInquiry" ) );

	DString dstrTime = getTimeStamp();

   setAwdField(ifds::SegEndTime,dstrTime );

   DString event = SessionTags::CREATE_WORK;

   setAwdField(ifds::WorkType, NULL_STRING);    
	setAwdField(ifds::StatusDesc, NULL_STRING);    
	setupWorkArea( CALL_INQURY );  // set up a defaultone for ID caller
	createAWDObject( CALL_INQURY,  event );
	setAwdField(ifds::SegStartTime, dstrTime); // seg end time will become next seg start time    
   return GETCURRENTHIGHESTSEVERITY();
}
//**********************************************************************************
SEVERITY DSTCAWDSession::EndCall()
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTAWD_CONDITION, CLASSNAME, I_( "CallInquryEndCall" ) );
	cleanCallerInfo();
	cleanupAWDObject();
	return(GETCURRENTHIGHESTSEVERITY());
}


//**********************************************************************************

SEVERITY DSTCAWDSession::cleanupAWDObject( )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTAWD_CONDITION, CLASSNAME, I_( "cleanupAWDObject" ) );
	setAwdField( I_("ObjectID"), NULL_STRING );
    setAwdField( I_("CRDA"), NULL_STRING );
	if( getAwdInterface() )
	{

         BFAwdKeyVector keyList;
		 getAwdInterface()->getAwdWorkObjects(keyList);

         BFAwdKeyVector::reverse_iterator iter;

         while( ! keyList.empty() )
         {
            iter = keyList.rbegin();

            BFAwdKey *pKey = *iter;

            try
            {
               getAwdInterface()->lockAwdObject( pKey, false );
            }
            catch( ... )
            {
				//shall we promot error?

            }

            delete pKey;

            keyList.pop_back();
         }
		getAwdInterface()->clearAwdContainer();
	}	

	setAwdField(DSTCAwdSession::FrGetAwdObject, NO);
	m_AwdWorkData = NULL;
	m_pAwdOriginalWork = NULL;
	if( getAwdSession() )
	{
		getAwdSession()->setProcessWork( NULL );
	}
	m_bOrgUpdated =  false;
	return(GETCURRENTHIGHESTSEVERITY());
}
//*************************************************************************************

bool DSTCAWDSession::isContainerEmpty()
{
	bool bEmpty = false;

	if( getAwdInterface() )
	{
         BFAwdKeyVector keyList;
		 getAwdInterface()->getAwdWorkObjects(keyList);
		 bEmpty = keyList.empty();
		
	}
	return bEmpty;
}
//**********************************************************************************
SEVERITY DSTCAWDSession::CallInquiryUpdate ( const DString &eventType,  
                                             DString &event,
                                             bool bUpdateOrg)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTAWD_CONDITION, CLASSNAME, I_("CallInquiryUpdate"));

   if (bUpdateOrg)
	{		
      updateOriginalAwdObject ();
	}
	else
	{
		DString dstrTime = getTimeStamp(),
         dstrRemark;

      setAwdField (ifds::SegEndTime, dstrTime);
		getAwdField (SessionTags::AWD_COMMENT, dstrRemark);
		setSessionData (SessionTags::AWD_COMMENT, dstrRemark);
		createAWDObject (eventType, event);
		setAwdField (ifds::SegStartTime, dstrTime); // seg end time will become next seg start time
	}
	return(GETCURRENTHIGHESTSEVERITY());
}
//**********************************************************************************
SEVERITY DSTCAWDSession::CallInquiryEndCall()
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTAWD_CONDITION, CLASSNAME, I_( "CallInquiryEndCall" ) );

//	createAWDObject( UPDATE_AWD );

//	cleanCallerInfo();
	return(GETCURRENTHIGHESTSEVERITY());
}

//*********************************************************************************
void DSTCAWDSession::getOperatorExtension()
{
   ConfigManager *pMgr = ConfigManager::getManager( I_("Workstation") );
   Configuration cfg = pMgr->retrieveConfig( I_( "Settings" ) );
   DString dstrValue = cfg.getValueAsString( OperatorExtension );
   setAwdField(ifds::Operator_Extension,dstrValue);

}
//*********************************************************************************
void DSTCAWDSession::saveOperatorExtension()
{
   ConfigManager *pMgr = ConfigManager::getManager( I_("Workstation") );
   Configuration cfg = pMgr->retrieveConfig( I_( "Settings" ) );
   DString dstrValue;
   getAwdField(ifds::Operator_Extension,dstrValue);
   cfg.set( OperatorExtension, dstrValue );
   pMgr->storeConfig( cfg );
   pMgr->persist();

}

//****************************************
namespace SessionTags
{
   extern  const I_CHAR *SESSION;
   const I_CHAR *MGMCO = I_("MGMCO");

}
//***********************************************************************************
void DSTCAWDSession::getBusinessAreaByCompanyId( const DString &dstrCompanyId, DString &dstrBusinessArea )
{
   dstrBusinessArea = NULL_STRING;

   // Iterate AWD Business Area list in MGMCO to find matching ID
   bool  bFound = false;
   if( !dstrCompanyId.empty() )
   {
      ConfigManager *pConfigManager = ConfigManager::getManager( SessionTags::SESSION );
      Configuration sysTable = pConfigManager->retrieveConfig( SessionTags::MGMCO);
	  string_vector  bsnArea = getAwdBusinessAreaList();
	  string_vector_const_iterator  iter;
      DString  cmpyDesc = NULL_STRING;
      bsnArea = m_pAwdInterface->getBusinessAreaList();
	  for( iter = bsnArea.begin(); iter != bsnArea.end(); ++iter )
	  {
	      cmpyDesc = *iter;
		  cmpyDesc.strip();
		  if( dstrCompanyId ==	sysTable.getValueAsString( cmpyDesc ).stripAll( I_CHAR('\t') ) )
		  {
			dstrBusinessArea = cmpyDesc;
			break;
		  
		  }
	  }
	  if( dstrBusinessArea.empty() )  // if it has not been defined; use the existing one
	  {								// I doubt the logic here. Maybe we should through error message
	      const BFAwdData *pAwdWork = getAwdSession()->getProcessWork();
		  if( pAwdWork )
		  {
			dstrBusinessArea = pAwdWork->getUnit();
		  
		  }
	  }
   }
}
//************************************************************************
string_vector DSTCAWDSession::getWorkTypeList(const DString& dstrBusinessArea)
{
	string_vector vec;
	if( getAwdInterface() )
	{
		vec = getAwdInterface()->getWorkTypeList( dstrBusinessArea  );

	}
	return vec;
}
//*************************************************************************
DString DSTCAWDSession::getCurrentWork()
{
	DString dstrWork = NULL_STRING;
	const BFAwdData *pAwdWork = getAwdSession()->getProcessWork();
	if( pAwdWork )
	{
		dstrWork =pAwdWork->getWrkt();
	}
	return dstrWork;
}

//*************************************************************************
DString DSTCAWDSession::getCurrentStatus()
{
	DString dstrStatus = NULL_STRING;
	const BFAwdData *pAwdWork = getAwdSession()->getProcessWork();
	if( pAwdWork )
	{
		dstrStatus =pAwdWork->getStat();
	}
	return dstrStatus;
}

//*************************************************************************
SEVERITY DSTCAWDSession::retrieveObjectId()
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTAWD_CONDITION, CLASSNAME, I_( "retrieveObjectId" ) );
	
	const BFAwdData *pAwdWork = getAwdSession()->getProcessWork();
	if( pAwdWork )
	{
		DString dstrObjectId = pAwdWork->getLobValue( LobTag_ObjId);
		BFAwdKey* pSrcKey = NULL;
		if(getAwdInterface()->hasSourceForChild(pAwdWork->getKey(),&pSrcKey) )
		{
		   BFAwdSource* pSource = NULL;

		   if( getAwdInterface()->retrieveSource( pSrcKey,  &pSource ) )
		   {
			    const BFAwdData *pSrcData =  &( pSource->getData() ); 
				dstrObjectId = pSrcData->getLobValue( LobTag_ObjId );
				// save to  a field  ID
                setAwdField( I_("ObjectID"), dstrObjectId );
		   }
		   delete pSrcKey;
		   pSrcKey= NULL;		
		}		
	}	

	return(GETCURRENTHIGHESTSEVERITY());
}

//****************************************************************************
SEVERITY DSTCAWDSession::lookupAWDImageByObjectId(const DString& dstrObjId)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTAWD_CONDITION, CLASSNAME, I_( "lookupAWDImageByObjectId" ) );

	DString dstrBusinessArea, dstrBusinessAreaTag;
	getAwdField(ifds::BusinessArea,dstrBusinessArea);
    ConfigManager *pConfigManager = ConfigManager::getManager( SessionTags::SESSION );
    Configuration cfgWorkTable = pConfigManager->retrieveConfig( SessionTags::WORK_TABLE );

	dstrBusinessAreaTag = cfgWorkTable.getValueAsString( Business_Area ).stripAll( I_CHAR('\t')  );
   
    CriteriaVector criteriaList;
/*
   // Add Business_Area (UNIT=) Criteria
    BFAwdLookupCriteria criteriaBusinessArea( dstrBusinessAreaTag, 
	   BFAwdLookupCriteria::EQUAL_TO, dstrBusinessArea );
    criteriaList.push_back( criteriaBusinessArea );
*/  
    BFAwdLookupCriteria CriterialObjId( LobTag_ObjId, BFAwdLookupCriteria::EQUAL_TO, dstrObjId );
    criteriaList.push_back( CriterialObjId );
    if(getAwdInterface() )
	{

	   try
	   {
		  if( !getAwdInterface()->lookupSource( criteriaList ) )
		  {
			 ADDCONDITIONFROMFILE( CND::ERR_NO_AWD_SOURCE_IMAGE );
		  }
	   }
	   catch( ... )
	   {
			 ADDCONDITIONFROMFILE( CND::ERR_AWD_APPLICATION );

		
	   }
	}
	return(GETCURRENTHIGHESTSEVERITY());
}

//****************************************************************************
//before call this method, make sure work status and work type has been stored in the object
//
//****************************************************************************


SEVERITY DSTCAWDSession::validateDirectCommentToAWD(const DString& dstrComment, const BFDataGroupId& idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTAWD_CONDITION, CLASSNAME, I_( "validateDirectCommentToAWD" ) );

   DString dstrBusinessArea, dstrWorkType, dstrStatus;
   getAwdField(ifds::BusinessArea, dstrBusinessArea );
   getAwdField(ifds::WorkType, dstrWorkType );
   getAwdField(ifds::StatusDesc, dstrStatus );
   dstrBusinessArea.strip();
   dstrStatus.strip();
   dstrWorkType.strip();
   if(dstrBusinessArea.empty() || dstrStatus.empty() || dstrWorkType.empty() )
	{
      ADDCONDITIONFROMFILE( CND::ERR_BUSINESS_WORKTYPE_STATUS );
		return( GETCURRENTHIGHESTSEVERITY() );
	}

   // Check length of comment
   DString dstrCommentStripped( dstrComment );
   dstrCommentStripped.stripLeading().stripTrailing();
   if( dstrCommentStripped.size() == 0 )
   {
		ErrMsgRulesList *pErrMsgRulesList = NULL;
		if ( m_pWorkSession && m_pWorkSession->getMgmtCo().getErrMsgRulesList( pErrMsgRulesList ) <= WARNING && pErrMsgRulesList )
      {
         DString dstrErrValue;
         pErrMsgRulesList->getEWIValue( I_( "415" ), idDataGroup, dstrErrValue );
         dstrErrValue.strip().upperCase();
         if( dstrErrValue == I_("E") )
         {
      		ADDCONDITIONFROMFILE( CND::ERR_COMMENTS_MANDATORY );
            return( GETCURRENTHIGHESTSEVERITY() );
         }
         else if( dstrErrValue == I_("W") )
         {
      		ADDCONDITIONFROMFILE( CND::ERR_NO_COMMENTS );
            return( GETCURRENTHIGHESTSEVERITY() );
         }
      }
   }
   return( GETCURRENTHIGHESTSEVERITY() );
}

SEVERITY DSTCAWDSession::addDirectCommentToAWD(const DString& dstrComment, const BFDataGroupId& idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTAWD_CONDITION, CLASSNAME, I_( "addDirectCommentToAWD" ) );

   DString dstrBusinessArea, dstrWorkType, dstrStatus;
   getAwdField(ifds::BusinessArea, dstrBusinessArea );
   getAwdField(ifds::WorkType, dstrWorkType );
   getAwdField(ifds::StatusDesc, dstrStatus );
   dstrBusinessArea.strip();
   dstrStatus.strip();
   dstrWorkType.strip();

	BFAwdData *pAwdWork = const_cast<BFAwdData* >(getAwdSession()->getProcessWork());
	if( pAwdWork )
	{   // there must be an existing work 
		if( getAwdInterface() )
		{
			//BFAwdData  awdData(*pAwdWork);
			pAwdWork->setUnit(dstrBusinessArea);
			pAwdWork->setWrkt(dstrWorkType);
			pAwdWork->setStat(dstrStatus);
			bool bSuccess = false;
			pAwdWork->setLobData( Comment_Flag,YES );
			pAwdWork->setLobData( System,I_("COR") );
			try
			{
				bSuccess = getAwdInterface()->updateAwdObject(*pAwdWork);
				DString Comment(dstrComment);
				int iLenth = dstrComment.size();

				while( iLenth > MAX_COMMENT_LEN )
				{
				   DString dstrSub = Comment.substr( 0, MAX_COMMENT_LEN );
				   Comment.erase( 0, MAX_COMMENT_LEN );
				   getAwdInterface()->addComment( pAwdWork->getKey(), dstrSub );
				   iLenth = Comment.size();
				}
				getAwdInterface()->addComment( pAwdWork->getKey(), Comment );
				if( pAwdWork == m_AwdWorkData )
				{
					m_bOrgUpdated = true;
				}
			}
			catch(...)
			{
				ADDCONDITIONFROMFILE( CND::ERR_AWD_APPLICATION );
			}
		}
	}
	//clear work  type and status
	setAwdField(ifds::WorkType,		NULL_STRING );
	setAwdField(ifds::StatusDesc,   NULL_STRING );

	return(GETCURRENTHIGHESTSEVERITY());  
}

//***************************************************************************
// the method will be called after "GetWork"
// so that we can clone the original object
//****************************************************************************
void DSTCAWDSession::saveCurrentObject()
{
	m_AwdWorkData = getAwdSession()->getProcessWork();
	setAwdField(DSTCAwdSession::FrGetAwdObject, YES);
	m_bOrgUpdated = false; // clear update flag

}

//*****************************************************************************
//clone AWD
//
//*****************************************************************************
SEVERITY DSTCAWDSession::cloneAwdObject()
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTAWD_CONDITION, CLASSNAME, I_( "cloneAwdObject" ) );
    if( canClone()  )
	{
		if( getAwdInterface() )
		{
			try
			{
				// make a copy

				BFAwdData* cpAwdWork = new BFAwdData( *m_AwdWorkData);				
				BFAwdData* pPrevWork = NULL;
				bool bLockOrg =  m_AwdWorkData == getAwdSession()->getProcessWork();
				if( bLockOrg )
				{  // the original pointer will be destroyed in BFAwdSession Class;
					// so we make a copy here
					m_pAwdOriginalWork = new BFAwdData( *m_AwdWorkData);
					m_AwdWorkData = m_pAwdOriginalWork;
				}
				cpAwdWork->setKey( NULL );
				cpAwdWork->setLobData( I_("QUEU"),I_("") );
				cpAwdWork->setLobData( I_("CRDA"),I_("") );
            cpAwdWork->setLobData( I_("COMF"),I_("N") );
            cpAwdWork->setStat( I_("CLONED") );

				if( getAwdInterface()->createAwdTransaction( *cpAwdWork,true ) )
				{
					BFAwdKey* pCase = NULL;
					if( getAwdInterface()->hasCaseForParent( m_AwdWorkData->getKey(), &pCase ) )
					{
						//associate cloned object to the same case
					   getAwdInterface()->createRelationship(pCase,cpAwdWork->getKey() );	
					
					}
					BFAwdKey* pSource = NULL;
					if(getAwdInterface()->hasSourceForChild(m_AwdWorkData->getKey(),&pSource) )
					{
					   getAwdInterface()->createRelationship(cpAwdWork->getKey(),pSource  );
					   //expandContainerItemDown causes the AWD container to freeze, so ... better don't call it
					   //getAwdInterface()->expandContainerItemDown( m_AwdWorkData->getKey() );

					}
					delete pSource;
					repositionWork( cpAwdWork );
				}			
			}
			catch(...)
			{
				ADDCONDITIONFROMFILE( CND::ERR_AWD_APPLICATION );
			}
		}
	}
	else
	{
		ADDCONDITIONFROMFILE( CND::ERR_NO_AWD_OBJECT_CLONE );	  
	}

	return(GETCURRENTHIGHESTSEVERITY());
}
//********************************************************************************************
SEVERITY DSTCAWDSession::repositionWork(BFAwdData* pAwdNewWork )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTAWD_CONDITION, CLASSNAME, I_( "repositionWork" ) );
	BFAwdData* pPrevWork =new BFAwdData( *(getAwdSession()->getProcessWork() ) );
	getAwdInterface()->lockAwdObject(  pPrevWork->getKey(), false );
	getAwdSession()->setProcessWork( pAwdNewWork,true );
	getAwdInterface()->lockAwdObject(  pPrevWork->getKey(), true );		
	delete pPrevWork;
	return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************
bool DSTCAWDSession::canClone()
{
	bool bCanClone = false;
	DString dstrFrGetWork;
	getAwdField(DSTCAwdSession::FrGetAwdObject, dstrFrGetWork);
	dstrFrGetWork.strip().upperCase();
	if(m_AwdWorkData && dstrFrGetWork == YES )
	{
	  bCanClone = true;	
	}
    return bCanClone;

}
//*******************************************************************************
SEVERITY DSTCAWDSession::updateOriginalAwdObject()
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTAWD_CONDITION, CLASSNAME, I_( "updateOriginalAwdObject" ) );
	if( canClone() && getAwdInterface() )
	{
		try
		{
         m_bOrgUpdated = true;
			if(m_AwdWorkData == getAwdSession()->getProcessWork() )
			{
					DString dstrUpWork = SessionTags::UPDATE_WORK;
					CallInquiryUpdate(I_("UPDATE AWD" ),dstrUpWork,false );
			}
			else
			{
				BFAwdData* pAwdWork = new BFAwdData (*(getAwdSession()->getProcessWork()) );
				BFAwdData* pOrgWork = new BFAwdData(*m_AwdWorkData);
				if(  pOrgWork && pAwdWork )
				{
					//pointer to original work and update it
					repositionWork(pOrgWork);
					DString dstrUpWork = SessionTags::UPDATE_WORK;
					CallInquiryUpdate(I_("UPDATE AWD" ),dstrUpWork,false );
					m_AwdWorkData = new BFAwdData(*pOrgWork);
					//pointer to the new one again
					repositionWork(pAwdWork);
				}	
			}
		}
		catch(...)
		{
		  ADDCONDITIONFROMFILE( CND::ERR_AWD_APPLICATION );		
		}
	}
	return(GETCURRENTHIGHESTSEVERITY());
}

//***********************************************************************************
bool DSTCAWDSession::isOrgWorkUpdated()
{
	
     return m_bOrgUpdated;

}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastawd/DSTCAWDSession.cpp-arc  $
// 
//    Rev 1.43   27 Feb 2009 15:03:16   kovacsro
// IN#1469934 - AWD Cloning more than 20 times
// 
//    Rev 1.42   07 Apr 2008 09:37:44   kovacsro
// IN#1166229 - refresh ObjectId & CRDA
// 
//    Rev 1.41   01 Feb 2008 09:03:20   kovacsro
// IN#1118094&1114586 - filtering the status list on the queue, bussArea and workType
// 
//    Rev 1.40   Apr 17 2006 14:29:42   popescu
// Incident# 544677 - subsequent fix when objects are cloned
// 
//    Rev 1.39   Mar 07 2006 15:44:02   popescu
// Incident# 544677 - subsequent fix when objects are cloned
// 
//    Rev 1.38   Feb 21 2006 12:02:58   popescu
// Incindent# 544677 - correctly updates the Begin and End time of a work object.
// 
//    Rev 1.37   Oct 26 2005 12:17:54   popescu
// Incident 437014 - corrected System field value - MAS-COR
// 
//    Rev 1.36   Aug 12 2005 15:30:14   hernando
// Incident 358734 - Uses flag from INI file.
// 
//    Rev 1.35   Jul 13 2005 14:22:40   hernando
// Inc 354559 - Set Comment Flag to N when creating new AWD work objects.
// 
//    Rev 1.34   Jun 24 2005 16:24:46   hernando
// Inc 341591 - Set Comment Flag to N as default after cloning.
// 
//    Rev 1.33   Jan 17 2005 18:23:06   hernando
// PTS10037736 - Removed reference to AWDEVENT.
// 
//    Rev 1.32   Aug 24 2004 16:24:08   YINGBAOL
// PTS10032997:according to Linh, change the cloning object status to "Create", so that they can distinguish between the clone object and the original object.
// 
//    Rev 1.31   Aug 19 2004 16:11:56   HERNANDO
// PTS 10033149 - Changed the way Warning messages are handled by breaking up addDirectComments into validate and add.
// 
//    Rev 1.30   Jul 15 2004 16:26:58   HERNANDO
// PTS 10032002 - Set Original Updated flag to true in updateOriginalAwdObject.
// 
//    Rev 1.29   May 28 2004 17:44:24   YINGBAOL
// PET1017:Add comments should mark the original AWD object as updated
// 
//    Rev 1.28   May 26 2004 15:36:42   HERNANDO
// PET1017 FN01 - Additional enhancement - Display error or warning message based on environment (ErrMsgRuleList #415).
// 
//    Rev 1.27   May 21 2004 17:12:34   HERNANDO
// PET1017 FN02 - Store the ObjectID and remove the Business Area from the lookup.
// 
//    Rev 1.26   May 08 2004 10:10:12   YINGBAOL
// PET1017:Fix locking issue for cloning and max comments for adding comments
// 
//    Rev 1.25   Apr 30 2004 10:43:22   YINGBAOL
// Fix work type status for add comments
// 
//    Rev 1.24   Apr 29 2004 16:43:22   YINGBAOL
// PET1017: more function added for support clone
// 
//    Rev 1.23   Apr 26 2004 16:02:06   YINGBAOL
// PEt 1017: Add clone support
// 
//    Rev 1.22   Apr 20 2004 14:17:14   YINGBAOL
// PET1017 Add comments directly to AWD object
// 
//    Rev 1.21   Apr 20 2004 10:59:44   YINGBAOL
// PET1017:FN2 and FN3:retrieve AWD source image support
// 
//    Rev 1.20   Mar 29 2004 10:34:40   HERNANDO
// PTS10028590 - Clear AWD Comments whenever we finish creating work.  Removed the Clear Comments from the End Call fn.
// 
//    Rev 1.19   Mar 26 2004 17:30:00   HERNANDO
// PTS10028590 - Clear AWD Comments on End Call.
// 
//    Rev 1.18   Mar 25 2004 14:02:12   YINGBAOL
// PTS1008385: move awd pointer to the one just created( the bug in base code)
// 
//    Rev 1.17   Mar 24 2004 17:49:22   HERNANDO
// Update business area.
// 
//    Rev 1.16   Mar 22 2004 17:43:06   YINGBAOL
// PTS10028360:change WorkType,Status
// 
//    Rev 1.15   Mar 12 2004 10:29:38   YINGBAOL
// PTS10027730:fix worktype override logic 
// 
//    Rev 1.14   Feb 27 2004 14:56:46   YINGBAOL
// PTS10027656: In case there isn't AWD installed, assert will cause issue for end work session in debug mode. 
// 
//    Rev 1.13   Feb 23 2004 17:07:28   popescu
// PTS 10027470, revert to old logic of saving the settings into the current user registry location instead of local machine
// 
//    Rev 1.12   Feb 23 2004 14:58:18   YINGBAOL
// PTS10027244:Strore caller information to new object.
// 
//    Rev 1.11   Feb 23 2004 09:40:44   YINGBAOL
// PTS10027246: F11 buton clear AWD Container
// 
//    Rev 1.10   Feb 20 2004 10:53:30   YINGBAOL
// PTS10027247:End call will also clear AWD COntainer 
// 
//    Rev 1.9   Feb 20 2004 10:44:28   YINGBAOL
// PTS10027245:Create AWD objects locked
// 
//    Rev 1.8   Jan 21 2004 17:52:40   YINGBAOL
// PET987: Business Area should not be retrieved from Configuration file
// 
//    Rev 1.7   Jan 21 2004 12:14:16   YINGBAOL
// PET987: Clear Besiness Are and work type for Inquiry Complet
// 
//    Rev 1.6   Jan 21 2004 10:55:44   YINGBAOL
// PET987:GetWorkStatus List based on call started
// 
//    Rev 1.5   Jan 19 2004 17:49:06   YINGBAOL
// PET987: fix isCallStart()
// 
//    Rev 1.4   Jan 19 2004 17:39:54   YINGBAOL
// PET987: implement 2 layor default for Business Area, work Type and status
// 
//    Rev 1.3   Jan 15 2004 11:30:04   YINGBAOL
// PET987:: change SegStartTime logic
// 
//    Rev 1.2   Jan 13 2004 16:34:02   YINGBAOL
// PET987:getAWDField should not gettime automatically
// 
*/

