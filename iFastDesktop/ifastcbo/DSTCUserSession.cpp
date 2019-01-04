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
// ^FILE   : DSTCUserSession.cpp
// ^AUTHOR : Cristina Oltean
// ^DATE   : Jan, 2001
//
//******************************************************************************

#include "stdafx.h"
#include "dstcusersession.hpp"
#include "dstcglobalsession.hpp"
#include "dstcworksession.hpp"
#include "useraccesslist.hpp"
#include "reportstatuscriteria.hpp"
#include "printerlist.hpp"
#include "MFAccount.hpp"
#include <configmanager.hpp>
#include <ifastdataimpl\dse_dstc0064_vw.hpp>
#include <ifastdataimpl\dse_dstc0004_vw.hpp>
#include <ifastdataimpl\dse_dstcglob_vw.hpp>
#include "FireFighterLogon.hpp"

namespace
{
   const I_CHAR * const CLASSNAME = I_( "DSTCUserSession" );  
   const I_CHAR * const YES		  = I_( "Y" );
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId UpdateStatus;

}

namespace CND
{  // Conditions used
   extern const long ERR_INVALID_FIRE_FIGHTER_LOGON;
}

// we're passing 'this' as an argument in a ctor.  This is not reliable, 
// but will work here.  Disable the warning - Chris Purdye 28Jun2002
#pragma warning( disable: 4355 )
//*****************************************************************
DSTCUserSession::DSTCUserSession()
: BFUserSession( *(new DSTCGlobalSession( *this )), ifds::DSTCGLOB_VW ),
_ownGlobalSession(true),
m_usedCompany(I_(";")),
m_dstrFFID(I_(""))
{
   // verify the market
   verifyMarket( );
   attachSession( &getGlobalSession() );
}
#pragma warning( default: 4355 )

//*****************************************************************
DSTCUserSession::DSTCUserSession( DSTCGlobalSession &globalSession )
: BFUserSession( globalSession, ifds::DSTCGLOB_VW ),
_ownGlobalSession(false),
m_usedCompany(I_(";")),
m_dstrFFID(I_(""))
{
   verifyMarket( );
}

//*****************************************************************
DSTCUserSession::~DSTCUserSession()
{
   if( _ownGlobalSession )
      freeSession( &getGlobalSession() );
}

//******************************************************************************
DSTCGlobalSession &
DSTCUserSession::createGlobalSession()
{
   DSTCGlobalSession *globalSession = new DSTCGlobalSession( *this );
   attachSession(globalSession);
   return(*globalSession);
}

//******************************************************************************
DSTCWorkSession &
DSTCUserSession::createWorkSession( const DString& mgmtCoId )
{
   DSTCWorkSession *workSession = new DSTCWorkSession( mgmtCoId, *this );
   attachSession(workSession);   

   return(*workSession);
}

//******************************************************************************
void DSTCUserSession::verifyMarket()
{
   const ClientLocale& rLocale = getClientLocale();
   // if the MarketIndex is less than or equal to 1 then it was not properly defined in the
   // registry.  In this case we will default to Canada for the market
   if( rLocale.getMarketIndex() <= 1 )
   {
      ClientLocale locale = rLocale;
      locale.setMarket( I_( "Canada" ) );
      // call BFUserSession::setClientLocale()
      // this method will take care of setting the context ClientLocale for us.
      setClientLocale( locale );   
   }
}

//******************************************************************************
void 
DSTCUserSession::establishLogonState( const DSTCHost &host, 
                                      const DString& userID, 
                                      const DString& sessionID, 
                                      const DString& locale )
{
   DSTCSecurity *security = dynamic_cast<DSTCSecurity *>( getSecurity(host) );
   security->establishLogonState( userID, sessionID, locale );

   setLocale( host );
}

//******************************************************************************
const DString& 
DSTCUserSession::getUserId(const DSTCHost &host) const
{
   const DSTCSecurity *security = dynamic_cast<const DSTCSecurity *>( getSecurity(host) );
   return(security->getUserId());
}

//******************************************************************************
const DString& 
DSTCUserSession::getSessionId(const DSTCHost &host) const
{
   const DSTCSecurity *security = dynamic_cast<const DSTCSecurity *>( getSecurity(host) );
   return(security->getSessionId());
}

//******************************************************************************
DString 
DSTCUserSession::getUserName(const DSTCHost &host) const
{
   const DSTCSecurity *security = dynamic_cast<const DSTCSecurity *>( getSecurity(host) );
   return(security->getUserName());
}

//******************************************************************************
DString 
DSTCUserSession::getDaysPasswordChange(const DSTCHost &host) const
{
   const DSTCSecurity *security = dynamic_cast<const DSTCSecurity *>( getSecurity(host) );
   return(security->getDaysPasswordChange());
}

//******************************************************************************
long 
DSTCUserSession::getNumberOfCompanies(const DSTCHost &host) const
{
   const DSTCSecurity *security = dynamic_cast<const DSTCSecurity *>( getSecurity(host) );
   return(security->getNumberOfCompanies());
}

//******************************************************************************
void 
DSTCUserSession::getCompanyInfo( const DSTCHost &host,
                                 const unsigned long companyIndex,  
                                 DString &companyId,
                                 DString &companyName ) const
{
   const DSTCSecurity *security = dynamic_cast<const DSTCSecurity *>( getSecurity(host) );
   security->getCompanyInfo( companyIndex, companyId, companyName);
}

bool DSTCUserSession::hasUserAccessList( const DString& dstrCompanyId )
{
   DString strKey;
   buildUserAccessListKey(DSTCHost::getPrimaryHost(), dstrCompanyId, strKey);

   BFObjectKey objKey( strKey, BF::HOST );
   UserAccessList *pUserAccessList = dynamic_cast<UserAccessList *>( findObject( objKey ) );

   return( NULL != pUserAccessList );      
}

//******************************************************************************
SEVERITY  
DSTCUserSession::getUserAccessList( const DSTCHost &host, const DString& companyId, UserAccessList *&pUserAccessListOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getUserAccessList" ) );

   DString strKey;
   buildUserAccessListKey(host, companyId, strKey);

   BFObjectKey objKey( strKey, BF::HOST );
   UserAccessList *pUserAccessList = dynamic_cast<UserAccessList *>( findObject( objKey ) );

   if( !pUserAccessList )
   {
      pUserAccessListOut = new UserAccessList( *this );
      if( pUserAccessListOut->init(companyId) > WARNING )
      {
         delete pUserAccessListOut;
         pUserAccessListOut = NULL;
      }
      else
         setObject( objKey, pUserAccessListOut );
   }
   else //get the account from the repository
   {
      pUserAccessListOut = pUserAccessList;
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY  
DSTCUserSession::getUserAccessList( const DString& companyId, UserAccessList *&pUserAccessListOut )
{
   return(getUserAccessList( DSTCHost::getPrimaryHost(), companyId, pUserAccessListOut ));
}

//******************************************************************************
SEVERITY  
DSTCUserSession::refreshUserAccessList( const DSTCHost &host, const DString& companyId, UserAccessList *&pUserAccessListOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "refreshUserAccessList" ) );

   DString strKey;
   buildUserAccessListKey(host, companyId, strKey);

   BFObjectKey objKey( strKey, BF::HOST );

   UserAccessList *pUserAccessList = new UserAccessList( *this );
   if( pUserAccessList->init(companyId) > WARNING )
   {
      delete pUserAccessList;
      pUserAccessList = NULL;
   }
   else
      setObject( objKey, pUserAccessList );

   pUserAccessListOut = pUserAccessList;

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY  
DSTCUserSession::refreshUserAccessList( const DString& companyId, UserAccessList *&pUserAccessListOut )
{
   return(refreshUserAccessList( DSTCHost::getPrimaryHost(), companyId, pUserAccessListOut ));
}

//******************************************************************************
bool 
DSTCUserSession::hasCreatePermission( const DString& companyId, const DString& functionCode ) const
{
   return(hasPermission( companyId, functionCode, ifds::AddPerm ));
}

//******************************************************************************
bool 
DSTCUserSession::hasReadPermission( const DString& companyId, const DString& functionCode ) const
{
   return(hasPermission( companyId, functionCode, ifds::InqPerm ));
}

//******************************************************************************
bool 
DSTCUserSession::hasUpdatePermission( const DString& companyId, const DString& functionCode ) const
{
   return(hasPermission( companyId, functionCode, ifds::ModPerm ));
}

//******************************************************************************
bool 
DSTCUserSession::hasDeletePermission( const DString& companyId, const DString& functionCode ) const
{
   return(hasPermission( companyId, functionCode, ifds::DelPerm ));
}

//******************************************************************************
bool 
DSTCUserSession::hasPermission( const DString& companyId, const DString& functionCode, const BFFieldId& permissionID ) const
{
   if( GetConfigValueAsBool( I_("Support"), I_("AllPowerfulVaalMode") ) ) {
      return( true );
   }

	bool bHasPermission = false;
	UserAccessList *pUserAccessList;
	if( const_cast<DSTCUserSession *>(this)->getUserAccessList( companyId, pUserAccessList ) > WARNING )
		return(false);

	BFAbstractCBO *pUserAccess = pUserAccessList->getObject( functionCode, BF::HOST );

	if( !pUserAccess )
		return(false);

	DString strActive;
	DString strInqPerm;
	DString strFuncCategory;

	pUserAccess->getField( ifds::F_active, strActive, BF::HOST );
	pUserAccess->getField( ifds::FuncCategory, strFuncCategory, BF::HOST );
	pUserAccess->getField( permissionID, strInqPerm, BF::HOST );

	bHasPermission = strActive == I_("Y") && strInqPerm == I_("Y");   

	if (permissionID == ifds::InqPerm)
		return bHasPermission;

	// check for add, modify and delete on non-finanical data
	if (strFuncCategory == I_("01") && m_StopNFU == I_("Y"))
	{
		bHasPermission = false;
	}
	
	return bHasPermission;

}

//******************************************************************************
void  
DSTCUserSession::buildUserAccessListKey( const DSTCHost &host, const DString& companyId, DString& newKey )
{
   newKey = I_("UserAccessList:") + host.getId() + I_(".") + companyId;
}

SEVERITY DSTCUserSession::getReportStatusCriteria ( ReportStatusCriteria*& pReportStatusCriteria, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getReportStatusCriteria" ) );

   BFObjectKey objKey( I_("ReportStatusCriteria"), idDataGroup );
   pReportStatusCriteria = dynamic_cast<ReportStatusCriteria* >( findObject( objKey ) );

   return(GETCURRENTHIGHESTSEVERITY());
}

SEVERITY DSTCUserSession::createReportStatusCriteria ( ReportStatusCriteria*& pReportStatusCriteria, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "createReportStatusCriteria" ) );

   BFObjectKey objKey( I_("ReportStatusCriteria"), idDataGroup );
   pReportStatusCriteria = new ReportStatusCriteria ( *this );
   pReportStatusCriteria->init( idDataGroup );
   setObject ( objKey, pReportStatusCriteria );

   return(GETCURRENTHIGHESTSEVERITY());
}

SEVERITY DSTCUserSession::getPrinterList ( PrinterList*& pPrinterList, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getPrinterList" ) );

   BFObjectKey objKey( I_("PrinterList"), idDataGroup );   
   pPrinterList = dynamic_cast<PrinterList* >( findObject( objKey ) );

   return(GETCURRENTHIGHESTSEVERITY());
}

SEVERITY DSTCUserSession::createPrinterList ( const DString& dstrCompanyId, PrinterList*& pPrinterList, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "createPrinterList" ) );

   BFObjectKey objKey( I_("PrinterList"), idDataGroup );
   pPrinterList = new PrinterList ( *this );   
   pPrinterList->init( dstrCompanyId );
   setObject ( objKey, pPrinterList );
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
bool
DSTCUserSession::isFFID(const DSTCHost &host) const
{
   const DSTCSecurity *security = dynamic_cast<const DSTCSecurity *>( getSecurity(host) );
   return(security->isFFID());
}

//******************************************************************************
DSTCWorkSession *
DSTCUserSession::FindWorksessionByAccount(const DString &dstrAccountNumber) const
{
   SESSION_SET_CONST_ITERATOR sessionIterator = getSessionSet().begin();
   while( getSessionSet().end() != sessionIterator ) 
   {
	   //find account in sessionIterator
	   if( (*sessionIterator)->isBFWorkSession())
	   {
		   if( dynamic_cast<DSTCWorkSession *> (*sessionIterator)->haveAccount( dstrAccountNumber ) )
		   {
			   return dynamic_cast<DSTCWorkSession *> (*sessionIterator);
		   }
	   }
	   ++sessionIterator;
   }

   return(NULL);
}

int DSTCUserSession::getNumberOfWorksession() const
{
   int numberOfWS = 0;
   SESSION_SET_CONST_ITERATOR sessionIterator = getSessionSet().begin();
   while( getSessionSet().end() != sessionIterator ) 
   {
	   //find account in sessionIterator
	   if( (*sessionIterator)->isBFWorkSession())
	   {
         numberOfWS ++;
	   }
	   ++sessionIterator;
   }
   return numberOfWS;

};
//******************************************************************************
SEVERITY DSTCUserSession::setStopNFU (const BFDataGroupId& idDataGroup, const DString &lastActiveAccountNumber)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setStopNFU" ) );

	m_lastActiveAccountNumber = lastActiveAccountNumber;

	MFAccount* pMFAccount = NULL; 
	m_StopNFU = NULL_STRING;

	DSTCWorkSession *pWorkSession = FindWorksessionByAccount(lastActiveAccountNumber);

	if (pWorkSession != NULL)
	{
		if (pWorkSession->getMFAccount( idDataGroup, lastActiveAccountNumber, pMFAccount ) <= WARNING &&
			pMFAccount != NULL )
		{
			pMFAccount->getField(ifds::StopNFU, m_StopNFU,idDataGroup, false);
		}
	}

	return(GETCURRENTHIGHESTSEVERITY());
}

void DSTCUserSession::setFireFighterLogonInfo(const DString &dstrFFID,const DString &dstrPassword,const DString &dstrPTSNum,const DString &dstrDesc1,const DString &dstrDesc2,const DString &dstrDesc3,const DString &dstrDesc4) 
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setFireFighterLogonInfo" ) );

	m_dstrFFID = dstrFFID;
	m_dstrPassword = dstrPassword;
	m_dstrPTSNum = dstrPTSNum;
	m_dstrDesc1 = dstrDesc1;
	m_dstrDesc2 = dstrDesc2;
	m_dstrDesc3 = dstrDesc3;
	m_dstrDesc4 = dstrDesc4;
}

SEVERITY DSTCUserSession::fireFighterLogon(const DString & dstCompanyId) 
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "fireFighterLogon" ) );

	// log only the ff info for audit purpose
	if( m_dstrFFID != I_("") && m_usedCompany.find(I_(";")+dstCompanyId+I_(";")) == DString::npos )
	{
		m_usedCompany += (dstCompanyId+I_(";"));
		DString dstrStatusCode;
		FireFighterLogon *pLogon = new FireFighterLogon( *this );
		pLogon->init(dstCompanyId,m_dstrFFID,m_dstrPassword,m_dstrPTSNum,m_dstrDesc1,m_dstrDesc2,m_dstrDesc3,m_dstrDesc4);
		pLogon->getField(ifds::UpdateStatus,dstrStatusCode,BF::HOST,false);
		dstrStatusCode.strip();
		if ( dstrStatusCode != YES )
		{
			ADDCONDITIONFROMFILE( CND::ERR_INVALID_FIRE_FIGHTER_LOGON );
		}
		delete pLogon;
		pLogon = NULL;
	}
	return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
bool 
DSTCUserSession::isFunctionActivated( const DString& companyId, const DString& functionCode ) const
{
   bool bIsActive = false;
   UserAccessList *pUserAccessList = NULL;
   DSTCUserSession* pUserSession = const_cast<DSTCUserSession *>(this);

   if( pUserSession->getUserAccessList( DSTCHost::getPrimaryHost(), companyId, pUserAccessList ) <= WARNING && 
      pUserAccessList != NULL)
   {
      BFAbstractCBO *pUserAccess = pUserAccessList->getObject( functionCode, BF::HOST );

      if( !pUserAccess )
         return(false);

      DString strActive;
      pUserAccess->getField( ifds::F_active, strActive, BF::HOST );
      bIsActive = (strActive.strip().upperCase()) == I_("Y") ?true:false;
   }

   return bIsActive;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCUserSession.cpp-arc  $
// 
//    Rev 1.24   Oct 07 2011 15:37:24   dchatcha
// P0186477 FN01 - GIA Enhancements, forgot to change it back after testing.
// 
//    Rev 1.23   Oct 04 2011 18:15:22   dchatcha
// P0186477 FN01 - GIA Enhancements, display validate portfolio fields based on environment functionality(UAF).
// 
//    Rev 1.22   Jan 08 2010 11:56:48   yingz
// delay view 276 for inc#1936007
// 
//    Rev 1.21   Oct 27 2009 23:48:20   purdyech
// Added hasUserAccessList() method.
// 
//    Rev 1.20   Mar 26 2009 09:23:46   purdyech
// Sundry tweaks for ZTS - Rel 10
// 
//    Rev 1.19   04 Dec 2008 16:33:00   popescu
// Incident Unclaimed Property -  Smartview - modified 1 to 01
// 
//    Rev 1.18   Nov 06 2008 14:31:00   jankovii
// PET 5517 FN71 Unclaimed Property Phase 2.
// 
//    Rev 1.17   Nov 14 2004 14:33:56   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.16   Aug 12 2004 14:43:14   FENGYONG
// Sync up PTS 10032837 - limit user open 5 sessions
// 
//    Rev 1.15   May 27 2004 16:29:48   SMITHDAV
// Changes to InterProcessData to move "global data" to the session level.
// 
//    Rev 1.14   May 11 2004 14:27:22   FENGYONG
// PET1046 FN1 - transfer-switch -Rel57
// 
//    Rev 1.13   Dec 11 2003 11:45:22   linmay
// added isFFID()
// 
//    Rev 1.12   Mar 21 2003 18:07:24   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.11   Dec 08 2002 22:03:32   HSUCHIN
// added printerlist and reportstatuscriteria cbo
// 
//    Rev 1.10   Oct 09 2002 23:54:24   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.9   Sep 17 2002 16:46:22   PURDYECH
// Added market verification.  If the Config/Market/Market registry value is not set then it effectively defaults to Canada.
// 
//    Rev 1.8   Aug 29 2002 12:55:40   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.7   Jul 05 2002 10:34:16   PURDYECH
// cleanup a compiler warning
// 
//    Rev 1.6   22 May 2002 18:28:02   PURDYECH
// BFData Implementation
// 
//    Rev 1.5   Feb 25 2002 18:55:40   PURDYECH
// Phase 1 of BFData Rollout - Base Component Compatibility
// 
//    Rev 1.4   25 Oct 2001 14:02:48   SMITHDAV
// hasPermission changes...
// 
//    Rev 1.3   08 Aug 2001 10:57:14   SMITHDAV
// Made extensive fixes to ClientLocale management.
// 
//    Rev 1.2   09 Jul 2001 15:25:10   SMITHDAV
// Mgmt company refresh related changes.
// 
//    Rev 1.1   14 Jun 2001 11:56:32   SMITHDAV
// Re-worked user access list and permission checking code.
// 
//    Rev 1.0   03 May 2001 14:48:56   SMITHDAV
// Initial revision.
 *
 */