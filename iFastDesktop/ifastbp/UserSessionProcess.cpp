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
//    Copyright 1997 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : UserSessionProcess.cpp
// ^AUTHOR : Jerry Leenerts
// ^DATE   : 12/14/1998
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : UserSessionProcess
//    This class sets the interface for business process subclasses.
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "usersessionprocess.hpp"
#include <ifastdbrkr\dstchost.hpp>
#include <ifastdataimpl\dse_dstcglob_vw.hpp>
#include <ifastdbrkr\dstcsecurity.hpp>
#include <bfproc\genericinterfacecontainer.hpp>
#include <bfsessn\bfcpsession.hpp>
#include "usersessionprocessincludes.h"
#include "etrackheader.h"
#include "persistentusersession.hpp"
#include <ifastcbo\dstcglobalsession.hpp>
#include <ifastawd\DSTCAWDSession.hpp>
#include <ifastcbo\dstcworksession.hpp>
//#include <ifastgui\ConfigurationConstants.h>
#include <configmanager.hpp>

extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_LOGON;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_MANAGEMENT_COMPANY;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_FIRE_FIGHTER_LOGON;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< UserSessionProcess > processCreator( CMD_BPROC_USER_SESSION );

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "UserSessionProcess" );

   // Literals
   const I_CHAR * const ID = I_( "ID" );
   //const I_CHAR * const LANGUAGE = I_( "Language" );

   const int NO_OF_DAYS_PRIOR_TO_CHANGE_PASSWORD = 7;
   const I_CHAR * const IDI_DAYS = I_( "DAYS" );
   const I_CHAR * const SESSIONPTR = I_( "SessionPtr" );

}

namespace USERSESSION
{
   const I_CHAR * const YES = I_( "Y" );
   const I_CHAR * const NO = I_( "N" );
}

namespace CND
{  // Conditions used
   extern CLASS_IMPORT const I_CHAR *IFASTDBRKR_CONDITION;
   extern CLASS_IMPORT const long BP_ERR_NO_FIELD_MATCH;
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
   extern CLASS_IMPORT const long BP_ERR_USER_CHANGE_PASSWORD;
   extern CLASS_IMPORT const long BP_NO_OF_DAYS_PRIOR_TO_CHANGE_PASSWORD;
   extern CLASS_IMPORT const long ERR_AD_TOO_MANY_FAILED_LOGONS;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId ClientName;
}

//******************************************************************************
//              Public Methods
//******************************************************************************

//******************************************************************************
UserSessionProcess::UserSessionProcess() 
: AbstractProcess()
, _dstcUserSession( NULL )
, _language( NULL_STRING )
, _sessionId( NULL_STRING )
, _strXMLConfigFile(NULL_STRING)
{
   initUserSession();
}

UserSessionProcess::UserSessionProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _dstcUserSession( NULL ),
_language( NULL_STRING ),
_sessionId( NULL_STRING ),
_strOldAwdProfile( NULL_STRING ),
_strXMLConfigFile(NULL_STRING)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   initUserSession();
}

//******************************************************************************
void UserSessionProcess::initUserSession()
{
   addFieldDetails( USERID, BF::NullContainerId, SUBCLASS_PROCESS, I_( "UserID" ) );
   addFieldDetails( PASSWORD, BF::NullContainerId, SUBCLASS_PROCESS, I_( "Password" ) );
   addFieldDetails( NEWPASSWORD, BF::NullContainerId, SUBCLASS_PROCESS, I_( "NewPassWord" ) );
   addFieldDetails( SYSTMGMTS, BF::NullContainerId, SUBCLASS_PROCESS, I_( "SystMgmts" ) );
   addFieldDetails( MGMTCONAME, BF::NullContainerId, SUBCLASS_PROCESS, I_( "MgmtCoName" ) );
   addFieldDetails( AWDPROFILE, BF::NullContainerId, SUBCLASS_PROCESS, I_( "AwdProfile" ) );
   addFieldDetails( LANGUAGE, BF::NullContainerId, SUBCLASS_PROCESS, I_( "Language" ) );
   addFieldDetails( SESSIONID, BF::NullContainerId, SUBCLASS_PROCESS, I_( "SessionId" ) );
   addFieldDetails( ACCESSALLSLSREP, BF::NullContainerId, SUBCLASS_PROCESS, I_( "AccessAllSlsRep" ) );
   addFieldDetails( CHANGE_AWDPROFILE, BF::NullContainerId, SUBCLASS_PROCESS, I_( "ChangeAwdProfile" ) );
   addFieldDetails( CHANGE_MGT_COMPANY, BF::NullContainerId, SUBCLASS_PROCESS, I_( "ChangeMgtComp" ) );
   addFieldDetails( CLIENTNAME, BF::NullContainerId, SUBCLASS_PROCESS, I_( "ClientName" ) );
   addFieldDetails( XMLCONFIGFILE, BF::NullContainerId, SUBCLASS_PROCESS, I_( "XMLConfigFileName" ) );

}

//******************************************************************************

UserSessionProcess::~UserSessionProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );

   if( !bfutil::isServerContext() && getBFSession()->getUserSession().isLoggedOn( DSTCHost::getPrimaryHost() ) )
   {
      DString logoutMessage;
      getBFSession()->getUserSession().logoff( DSTCHost::getPrimaryHost(), logoutMessage );
   }

   delete _dstcUserSession;

   BFCPSession* rpParentSession = getSession();
   if( NULL != rpParentSession )
   {
      DString dstrSessionPtr = getSession()->getSessionData( SESSIONPTR );
      BFCPSession *rpSession = (BFCPSession *) dstrSessionPtr.asInteger();
      delete rpSession;	
   }

}

//******************************************************************************
//              Protected Methods
//******************************************************************************

void UserSessionProcess::doGetField(
                                   const GenericInterface *rpGICaller,
                                   const BFContainerId& idContainer,
                                   const BFFieldId& idField,
                                   const BFDataGroupId& idDataGroup,
                                   DString &strValueOut,
                                   bool bFormatted
                                   ) const
{
   if( idField == SYSTMGMTS )
   {
      strValueOut = _strSystMgmt;
   }
   else if( idField == LANGUAGE )
   {
      strValueOut = _language;
   }
   else if( idField == SESSIONID )
   {
      strValueOut = _sessionId;
   }
   else if( idField == USERID )
   {
      strValueOut = _strUserID;
   }
   else if( idField == PASSWORD )
   {
      strValueOut = _strPassword;
   }
   else if( idField == NEWPASSWORD )
   {
      strValueOut = _strNewPassword;
   }
   else if( idField == MGMTCONAME )
   {
      strValueOut = _strMgmtCoName;
   }
   else if( idField == AWDPROFILE )
   {
      strValueOut = _strAwdProfile;
   }
   else if( idField == ACCESSALLSLSREP )
   {
      strValueOut = _strAccessAllSlsRep;
   }
   else if( idField == CHANGE_AWDPROFILE)
   {
      strValueOut =  _strAwdProfile == _strOldAwdProfile? USERSESSION::NO:USERSESSION::YES;    
   }
   else if( idField == CHANGE_MGT_COMPANY)
   {
      strValueOut =  _strOldMgmtCoName == _strMgmtCoName? USERSESSION::NO:USERSESSION::YES;  
   }
   else if ( idField == CLIENTNAME )
   {
      // do get mgmco field!
      strValueOut = NULL_STRING;
      DSTCWorkSession* pWorkSession = NULL;

      DString mgmtCoId = _strSystMgmt;
      
      if ( !mgmtCoId.strip().empty() )
      {
         pWorkSession = &_dstcUserSession->createWorkSession( mgmtCoId );

         if ( pWorkSession )
         {
            pWorkSession->getOption2( ifds::ClientName, strValueOut, BF::HOST, false );
            strValueOut.strip();

            pWorkSession->cleanupWorkSession();
            _dstcUserSession->freeSession( pWorkSession );
         }
      }
   }
   else if ( idField == XMLCONFIGFILE )
   {
      strValueOut = _strXMLConfigFile;
   }
   else
   {
      assert( 0 );
      DString strIDI;
      addIDITagValue( strIDI, ID, idField.getId() );
      THROWFROMFILEIDI2( CND::BPBASE_CONDITION, CLASSNAME, DOGETFIELD,
                         CND::BP_ERR_NO_FIELD_MATCH, strIDI );
   }
}

//******************************************************************************

SEVERITY UserSessionProcess::doInit()
{
   DString tmp;

   // We have to create our UserSession object.  When this is created we can specify
   // a GlobalSession to use or let the UserSession create its own GlobalSession.  We
   // can determine if we have a handy GlobalSession by querying the PersistentUserSession
   // object.  If there is a PersistentUserSession then we can use its GlobalSession as the 
   // GlobalSession for the new UserSession.  If there is no PersistentUserSession then
   // we must allow the UserSession object to create its own GlobalSession.
   DSTCUserSession* pPUS = PersistentUserSession::getInstance();
   if( NULL != pPUS )
   {
      // there is a PersistentUserSession ... we can use its GlobalSession as the GlobalSession
      // of the new UserSession.
      _dstcUserSession = new DSTCUserSession( dynamic_cast< DSTCGlobalSession& >( pPUS->getGlobalSession() ) );
   }
   else
   {
      _dstcUserSession = new DSTCUserSession;
   }

   setBFSession(_dstcUserSession);

   getParameter( I_( "UserId" ), _strUserID );
   getParameter( I_( "UserPassword" ), _strPassword );
   getParameter( I_( "SessionId" ), _sessionId );
   getParameter( I_( "XML_API" ), tmp );

//CP20030319   if( _sessionId != I_( "" ) || _strUserID != I_( "" ) )
//CP20030319   {
//CP20030319      setServerContext( true );
//CP20030319   }
   if( tmp == I_("Y") )
   {
//CP20030319      setServerContext( true );
      setXMLAPIContext( true );
   }

   getParameter( I_( "Language" ), _language );
   getParameter( I_( "CompanyId" ), _strSystMgmt );

   getParameter( ETRACK::TRACK, _strETrack );
   getParameter( ETRACK::ACTIVITY, _strPageName );
   if( _strETrack == NULL_STRING ) _strETrack = I_("N");

   return(NO_CONDITION);
}

//******************************************************************************

SEVERITY UserSessionProcess::ok2( GenericInterface *rpGI )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, OK2 );
   bool bRtn = false;

   // Logon is currently the only dialog initiated from here.  Change this to
   // switch on the command id if need to handle multiple dialogs.
   try
   {  // attempt logon -- return to dialog if logon fails

      if( bfutil::isServerContext() )
      {
         SEVERITY severity = NO_CONDITION;
         if( _sessionId == I_("") )
         {
            severity = _dstcUserSession->logon( DSTCHost::getPrimaryHost(), _strUserID, _strPassword );
            if( severity <= WARNING )
            {
               _language = _dstcUserSession->getLanguage();
               _sessionId = _dstcUserSession->getSessionId( DSTCHost::getPrimaryHost() );
               const DSTCSecurity* pSecurity = dynamic_cast< const DSTCSecurity* >( getBFSession()->getSecurity( DSTCHost::getPrimaryHost() ) );
               (const_cast<DSTCSecurity*>(pSecurity))->getAllSlSRepFlag(_strSystMgmt, _strAccessAllSlsRep);
            }
         }
         else
         {
            _dstcUserSession->establishLogonState( DSTCHost::getPrimaryHost(), _strUserID, _sessionId, _language );
            SEVERITY severity = NO_CONDITION;
         }

      }
      else
      {
         if( _dstcUserSession->logon( DSTCHost::getPrimaryHost(), _strUserID, _strPassword ) <= WARNING )
         {
            _language = _dstcUserSession->getLanguage();
            _sessionId = _dstcUserSession->getSessionId( DSTCHost::getPrimaryHost() );
            bRtn = true;
            //if no new password has been entered check if this is either manadatory
            //or if we have to warn the user about changing the password
            if( _strNewPassword == NULL_STRING )
            {
               DString days = _dstcUserSession->getDaysPasswordChange( DSTCHost::getPrimaryHost() );

               int iDays = days.asInteger();

               if( iDays > 0 && iDays <= NO_OF_DAYS_PRIOR_TO_CHANGE_PASSWORD )
               {
                  DString strTemp;

                  addIDITagValue( strTemp, IDI_DAYS, days );
                  ADDCONDITIONFROMFILEIDI( CND::BP_NO_OF_DAYS_PRIOR_TO_CHANGE_PASSWORD, strTemp );
               }
               else if( iDays == 0 )
               {
                  ADDCONDITIONFROMFILE( CND::BP_ERR_USER_CHANGE_PASSWORD );
                  bRtn = false;
               }
            }
            if( bRtn && _strNewPassword != NULL_STRING )
            {
               if( _dstcUserSession->changePassword( DSTCHost::getPrimaryHost(), _strPassword, _strNewPassword) > WARNING )
               {
                  bRtn = false;
               }
            }
            if( !bRtn )
            {
               DString logoutMessage;
               //Logoff because either changing the password failed or something else happened
               _dstcUserSession->logoff( DSTCHost::getPrimaryHost(), logoutMessage);
               _sessionId = NULL_STRING;
               _language = NULL_STRING;
            }
         }
      }

   }
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOOK,
                      CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(GETCURRENTHIGHESTSEVERITY());
   /*
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, OK2 );
   bool bRtn = false;

   // Logon is currently the only dialog initiated from here.  Change this to
   // switch on the command id if need to handle multiple dialogs.
   try
   {  // attempt logon -- return to dialog if logon fails

      DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
      _pDSTCSecurity = new DSTCSecurity( dstcWorkSession );

      if ( bfutil::isServerContext() )
      {  // Set up to use previous logon info and/or pass company in
         _pDSTCSecurity->setSessionInfo( _strUserID, _sessionId, _language,
            _strSystMgmt);
         if ( _sessionId != I_( "" ) ) 
         {  // must add usersessiondetails prior to each request if not going 
            //  thru logon
            BFSessionManager::getInstance()->addUserSessionDetails(
               getUserSessionID(), _pDSTCSecurity );
         }
      }
      // Note that logon for server would already have syst mgmt set up above.
      if ( _sessionId == I_( "" ) && BFSessionManager::getInstance()->logon(
         getUserSessionID(), _pDSTCSecurity, _strUserID, _strPassword,_strETrack,_strPageName ) <=
         WARNING )
      {  //here we are logged on

         BFSessionManager::getInstance()->getLanguage( getUserSessionID(), _language );
         BFSessionManager::getInstance()->getSessionId( getUserSessionID(), _sessionId );
         
         if ( bfutil::isServerContext() )
         {
            E_COMMANDRETURN rtn = CMD_FAILURE;

            // If process already running, destroy it.
            GenericInterface * rpUserAccess = getGIContainer()->findGI( 0,
               CMD_BPROC_USER_ACCESS );
            if ( rpUserAccess != NULL )
            {
               getGIContainer()->destroy( rpUserAccess );
            }
            
            //We get the UserAccessList here just to find out if the user has been setup in ACL
            //If we are going to need any security in the future regarding the user access control
            //we have to send the right attribute ( for example can user trade ) within every request
            //since we don't have persistence and this list we get it just after logon
            rtn = invokeCommand( this, CMD_BPROC_USER_ACCESS, getProcessType(),
               false, NULL );
            if ( !( CMD_OK != rtn && CMD_MODELESS_INPROCESS != rtn ) )
            {
            }
            else
            {
               DString logoutMessage;
               BFSessionManager::getInstance()->logoff( getUserSessionID(), logoutMessage,false,_strETrack,_strPageName);
            }
         }

         if ( !bfutil::isServerContext() )
         {
            bRtn = true;
            //if no new password has been entered check if this is either manadatory
            //or if we have to warn the user about changing the password
            if ( _strNewPassword == NULL_STRING )
            {
               DString days;

               if ( BFSessionManager::getInstance()->getDaysPasswordChange( 
                                       getUserSessionID(), days ) <= WARNING )
               {
                  int iDays = days.asInteger();

                  if ( iDays > 0 && iDays <= NO_OF_DAYS_PRIOR_TO_CHANGE_PASSWORD )
                  {
                     DString strTemp;

                     addIDITagValue( strTemp, IDI_DAYS, days );
                     ADDCONDITIONFROMFILEIDI( CND::BP_NO_OF_DAYS_PRIOR_TO_CHANGE_PASSWORD, strTemp );
                  }
                  else if ( iDays == 0 )
                  {
                     ADDCONDITIONFROMFILE( CND::BP_ERR_USER_CHANGE_PASSWORD );
                     bRtn = false;
                  }
               }
            }
            if ( bRtn && _strNewPassword != NULL_STRING )
            {
               if ( BFSessionManager::getInstance()->changePassword(
                  getUserSessionID(), _strPassword, _strNewPassword,_strETrack,_strPageName) > WARNING )
               {
                  bRtn = false;
               }
            }
            if ( !bRtn )
            {
               DString logoutMessage;
               //Logoff because either changing the password failed or something else happened
               BFSessionManager::getInstance()->logoff( getUserSessionID(), logoutMessage,false,_strETrack,_strPageName);
               _sessionId = NULL_STRING;
               _language = NULL_STRING;
            }
         }
      }
   }
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOOK,
         CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return GETCURRENTHIGHESTSEVERITY();
   */
}

//******************************************************************************

E_COMMANDRETURN UserSessionProcess::doProcess()
{  
   TRACE_METHOD( CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      assert( !getSession() );  // Session should be NULL, we create our own
      if( !bfutil::isServerContext() )
      {
         while( CMD_OK != rtn && CMD_MODELESS_INPROCESS != rtn )
         {
            // The loop allows us to go back to logon if systmgmt fails or cancels
            clearSignonData();
            rtn = invokeCommand( this, CMD_GUI_LOGON, getProcessType(), true, NULL );
            if( rtn != CMD_OK )
            {  // If we have problem here, we get out
               return(rtn);
            }

         //if the user id logged is FFID then display the FireFighterLogon screen 

            if ( _dstcUserSession->isFFID(DSTCHost::getPrimaryHost() ))
            {
               rtn = invokeCommand( this, CMD_BPROC_FIRE_FIGHTER_LOGON, getProcessType(), true, NULL );
               if ( rtn != CMD_OK && rtn != CMD_MODELESS_INPROCESS )
               {
                  DString logoutMessage;
                  //Here we have to logoff as well
                  _dstcUserSession->logoff( DSTCHost::getPrimaryHost(), logoutMessage );
                  _sessionId = NULL_STRING;
                  _language = NULL_STRING;
                  continue;
               }
            }

            DString dstLanguage, dstCountry;
            getParameter( I_("language" ), dstLanguage );
            getParameter( I_("country" ),  dstCountry );
            const DString dstrLocale = dstLanguage + dstCountry;

            rtn = invokeCommand( this, CMD_BPROC_MANAGEMENT_COMPANY, getProcessType(), true, NULL );
            if( CMD_OK != rtn && CMD_MODELESS_INPROCESS != rtn )
            {
               DString logoutMessage;
               //Here we have to logoff as well
               _dstcUserSession->logoff( DSTCHost::getPrimaryHost(), logoutMessage );
               _sessionId = NULL_STRING;
               _language = NULL_STRING;
            }
         }
         // assert( getSession() ); this should also be processed in run time
         if( !getSession() )
         {
            THROWFROMFILE2( CND::IFASTDBRKR_CONDITION, CLASSNAME, DOPROCESS,
                            CND::ERR_AD_TOO_MANY_FAILED_LOGONS );
         }
      }
   }
   catch( ConditionException & )
   {
      throw;
   }
   catch( ... )
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS,
                      CND::BP_ERR_UNKNOWN_EXCEPTION );
   }

   return(CMD_MODELESS_INPROCESS);  // We are in process.  Only the user can end
                                    //  by closing app.
}

//******************************************************************************

bool UserSessionProcess::doSend(
                               GenericInterface *rpGICaller,
                               const I_CHAR *szMessage
                               )
{
   TRACE_METHOD( CLASSNAME, DOSEND );
   DString str( szMessage );
   DSTCAWDSession *rpSession = NULL; 
   if( str == STARTSESSION )
   {
      if(getSession() )
      {

         DString dstrSessionPtr = getSession()->getSessionData( SESSIONPTR );
         rpSession = (DSTCAWDSession *) dstrSessionPtr.asInteger();	     	
         delete getSession();

      }
      setSession( new BFCPSession(), true );

      if( rpSession ) //there is a child session
      {
         DSTCAWDSession  *pSession = new DSTCAWDSession( getSession() );
         pSession->storeCallerInfo( rpSession );	
         delete rpSession;
         DString dstrSessionPtr = asString( (int) pSession );
         getSession()->setSessionData( SESSIONPTR, dstrSessionPtr);
      }
   }
   return(true);
}

//******************************************************************************

SEVERITY UserSessionProcess::doSetField(
                                       const GenericInterface *rpGICaller,
                                       const BFContainerId& idContainer,
                                       const BFFieldId& idField,
                                       const BFDataGroupId& idDataGroup,
                                       const DString& strValue,
                                       bool bFormatted
                                       )
{
   SEVERITY sevRtn = NO_CONDITION;

   if( idField == USERID )
   {
      _strUserID = strValue;
   }
   else if( idField == PASSWORD )
   {
      _strPassword = strValue;
   }
   else if( idField == NEWPASSWORD )
   {
      _strNewPassword = strValue;
   }
   else if( idField == SYSTMGMTS )
   {
      _strSystMgmt = strValue;
   }
   else if( idField == MGMTCONAME )
   {
      _strOldMgmtCoName = _strMgmtCoName;
      _strMgmtCoName = strValue;     
   }
   else if( idField == AWDPROFILE )
   {
      _strOldAwdProfile = _strAwdProfile; 
      _strAwdProfile = strValue;
   }
   else if( idField == ACCESSALLSLSREP )
   {
      _strAccessAllSlsRep = strValue;
   }
   else if( idField == SESSIONID )
   {
      _sessionId = strValue;
   }
   else if( idField == LANGUAGE )
   {
      _language = strValue;
   }
   else if( idField == XMLCONFIGFILE )
   {
      _strXMLConfigFile = strValue;
   }
   else
   {
// TODO add condition if this code stays
      sevRtn = SEVERE_ERROR;
   }
   return(sevRtn);
}

//******************************************************************************
//              Private Methods
//******************************************************************************

void UserSessionProcess::clearSignonData()
{
   _strSystMgmt = NULL_STRING;
   _strNewPassword = NULL_STRING;
   _strPassword = NULL_STRING;
   _strUserID = NULL_STRING;
   _language = NULL_STRING;
   _sessionId = NULL_STRING;
   _strMgmtCoName = NULL_STRING;
   _strAwdProfile = NULL_STRING;
   _strAccessAllSlsRep = NULL_STRING;
   _strXMLConfigFile = NULL_STRING;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/UserSessionProcess.cpp-arc  $
 * 
 *    Rev 1.41   Sep 19 2011 14:51:08   dchatcha
 * Usability Improvement on iFAST/Desktop
 * 
 *    Rev 1.40   Dec 22 2009 06:16:34   dchatcha
 * IN# 1952546 - Indicator to show that the database DSK is connected to is scrambled.
 * 
 *    Rev 1.39   Aug 27 2009 04:49:12   purdyech
 * Throw of ERR_AD_TOO_MANY_FAILED_LOGONS was specifying wrong Condition file.
 * 
 *    Rev 1.38   May 08 2004 13:28:14   YINGBAOL
 * PTS10029514:AWD Container disappears when Mgmt Co changed
 * 
 *    Rev 1.37   Feb 23 2004 14:57:24   YINGBAOL
 * PTS10027244:Store caller Information to new object
 * 
 *    Rev 1.36   Feb 19 2004 09:28:08   YINGBAOL
 * PTS10027244:When user change profile, AWD session has to be killed.
 * 
 *    Rev 1.35   Jan 19 2004 14:40:08   YINGBAOL
 * PET987:If there is a AWDSession. use it
 * 
 *    Rev 1.34   Jan 12 2004 14:44:02   YINGBAOL
 * PET987: change AWD Session
 * 
 *    Rev 1.32   Dec 11 2003 11:51:38   linmay
 * modified doProcess to add Firfighterlogon
 * 
 *    Rev 1.31   Mar 21 2003 17:49:52   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.30   Oct 09 2002 23:53:42   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.29   Sep 30 2002 11:01:06   PURDYECH
 * BFFieldId no longer has operator long(), so explicit getId() calls are needed in places.
 * 
 *    Rev 1.28   Aug 29 2002 16:45:20   SMITHDAV
 * Condition split.
 * 
 *    Rev 1.27   Aug 29 2002 12:54:46   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.26   May 28 2002 12:18:04   PURDYECH
 * BFData Implementation - Phase II
 * 
 *    Rev 1.25   22 May 2002 18:25:22   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.24   27 Mar 2002 19:56:24   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.23   04 Aug 2001 11:35:54   KOVACSRO
 * set the allSlsRep flag.
 * 
 *    Rev 1.22   17 Jul 2001 11:25:38   PURDYECH
 * Added PersistentUserSession support.
 * 
 *    Rev 1.21   15 May 2001 15:39:00   YINGZ
 * data group id clean up
 * 
 *    Rev 1.20   14 May 2001 13:58:16   YINGZ
 * code sync up
 * 
 *    Rev 1.19   May 11 2001 16:02:10   HUANGSHA
 * set client locale
 * 
 *    Rev 1.18   Feb 21 2001 11:32:28   YINGZ
 * add xmlapi context
 * 
 *    Rev 1.17   Jan 24 2001 17:32:40   YINGBAOL
 * fix
 * 
 *    Rev 1.16   Jan 23 2001 15:18:02   YINGBAOL
 * add eTrack
 * 
 *    Rev 1.15   Dec 22 2000 13:55:00   YINGZ
 * setServerContext for xml api
 * 
 *    Rev 1.14   15 Dec 2000 12:43:56   PURDYECH
 * Use precompiled header stdafx.h.
 * Removed unnecessary header files.
 * 
 *    Rev 1.13   Dec 12 2000 15:47:08   KOVACSRO
 * Bug fixed for changing password.
 * 
 *    Rev 1.12   Nov 29 2000 10:23:14   VASILEAD
 * Created UserAccessList when we do logon in server context
 * 
 *    Rev 1.11   Nov 08 2000 12:24:22   DT24433
 * moved server context flag to GenericInterface
 * 
 *    Rev 1.10   Nov 01 2000 13:02:18   DT24433
 * changes to make logon functionality more consistent between server and gui modes
 * 
 *    Rev 1.9   Oct 26 2000 10:42:32   DT24433
 * changes to work from parms passed in and no longer creating GIC or getting new usersessionid
 * 
 *    Rev 1.8   Sep 19 2000 15:20:40   VASILEAD
 * Cleanup services, UserSeesionProcess and security object
 * 
 *    Rev 1.7   Aug 31 2000 10:14:36   YINGZ
 * change assert( getSession() ) in doProcess to if(...)
 * 
 *    Rev 1.6   Aug 02 2000 15:32:04   BUZILA
 * "locale" changes
 * 
 *    Rev 1.5   Jul 27 2000 17:37:48   BUZILA
 * ClientLocale changes
 * 
 *    Rev 1.4   Jul 26 2000 11:45:52   VASILEAD
 * Added AccessAllSlsRep field in logon transaction
 * 
 *    Rev 1.3   Jul 25 2000 11:53:06   YINGZ
 * take out logon off for the existing user
 * 
 *    Rev 1.2   Apr 04 2000 14:45:08   DT24433
 * set up GIContainer association
 * 
 *    Rev 1.1   Mar 08 2000 11:44:44   DT24433
 * pass in global datasets to use to InterProcessData
 * 
 *    Rev 1.0   Feb 15 2000 10:59:44   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.13   Dec 13 1999 14:21:30   DT24433
 * changed from using refresh to send
 * 
 *    Rev 1.12   13 Dec 1999 09:34:50   HSUCHIN
 * doRefresh now creates a new session only when requested to. 
 * 
 *    Rev 1.11   Dec 09 1999 10:42:36   POPESCUS
 * Checked if the user is logged on before actually logging it off
 * 
 *    Rev 1.10   Dec 07 1999 12:16:58   DT24433
 * added idDataGroup to doGetField/doSetField parms
 * 
 *    Rev 1.9   Nov 29 1999 12:45:52   POPESCUS
 * ok2 should return GetCurrentHighestSeverity because we need to promote conditions that are set into this method
 * 
 *    Rev 1.8   Oct 29 1999 14:50:12   DT24433
 * changed doOk to OK2
 * 
 *    Rev 1.7   Oct 23 1999 15:40:32   HSUCHIN
 * dorefresh now cleans the master session by deleting it and then recreates it.
 * 
 *    Rev 1.6   Oct 18 1999 17:36:46   DT24433
 * temporary get support for two more fields
 * 
 *    Rev 1.5   Aug 30 1999 18:10:36   DT24433
 * changed dosetfield/dogetfield method parms
 * 
 *    Rev 1.4   Aug 20 1999 17:56:50   POPESCUS
 * Added logout message
 * 
 *    Rev 1.3   Aug 04 1999 12:25:54   DT24433
 * Updated for field details changes
 * 
 *    Rev 1.2   Jul 20 1999 11:14:18   VASILEAD
 * New conditions update
 * 
 *    Rev 1.1   Jul 08 1999 10:02:16   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
