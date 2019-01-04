#include "TransactionsMonitor.h"

#include <cstdio>
#include <iostream>
#include <codecvt>
#include <string>
#include <ifdscore\condition.hpp>
#include <ifdscore\datapath.h>
#include <ifastcbo\DSTCWorkSession.hpp>
#include <ifastcbo\DSTCUserSession.hpp>
#include <ifastcbo\MgmtCoOptions2.hpp>
#include <ifastcbo\DSTCGlobalSession.hpp>
#include <ifastdbrkr\dstchost.hpp>
#include <ifastbp\PersistentUserSession.hpp>
#include <xercesc\util\PlatformUtils.hpp>
#include <xercesc\dom\DOMException.hpp>
#include <xercesc\sax\saxparseexception.hpp>
#include <ifastdbrkr.hpp>
#include <clientlocale.hpp>
#include <ConfigManager.hpp>
#include "ConfigurationConstants.h"
#include "SiteConfig.h"
#include "MFDSTCSetup.hpp"

#define CLASSNAME I_("TransactionMonitor")

namespace CND
{  // Conditions used
	extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

namespace ifds
{
	extern CLASS_IMPORT const BFTextFieldId CompanyUrl;
}

int main(int argc, char** argv)
{
	std::string username;
	std::string password;
	std::string _strClient;
	std::string siteXml;

	if(!ParseArgugments(argc, argv, username, password, _strClient, siteXml))
	{
		std::cerr<<"Usage: TransactionsMonitor2 -S <config file> -u <user> -p <password> -e <mgmt co>"<<std::endl;
		return -1;
	}

	xercesc::XMLPlatformUtils::Initialize();
	SiteConfigInit( siteXml, true);
	DString error;
	MFDSTCSetup::init ( true, error );

	ConfigManager *pDSTCMgr = ConfigManager::getManager( CONFIGURATION_CONSTANTS::MFDSTC );
	Configuration cfgPath = pDSTCMgr->retrieveConfig( CONFIGURATION_CONSTANTS::DataPath );
	DString sysloadPath = cfgPath.getValueAsString( CONFIGURATION_CONSTANTS::SysloadPath );

	if ( sysloadPath.empty() )
	{
		sysloadPath = cfgPath.getValueAsString( CONFIGURATION_CONSTANTS::Path );
		ConfigValue cvSysloadPath( sysloadPath );
		cfgPath.set( CONFIGURATION_CONSTANTS::SysloadPath, cvSysloadPath );
		pDSTCMgr->storeConfig( cfgPath );

		ConfigManager *pCboMgr = ConfigManager::getManager( CONFIGURATION_CONSTANTS::CBO );
		pCboMgr->storeConfig( cfgPath );
	}

	DSTCUserSession* _dstcUserSession = nullptr;
	DSTCWorkSession* _dstcWorkSession = nullptr;

	int errCode = 0;
	try
	{
		if(Logon(&_dstcUserSession, username, password) > WARNING) 
		{
			errCode = 1;
		}
	}
	catch(...)
	{
		errCode = 1;
	}

	if(errCode == 0)
	{
		try
		{
			if(CallView(&_dstcWorkSession, _dstcUserSession, _strClient) > WARNING)
			{
				errCode = 2;
			}
		}
		catch(...)
		{
			errCode = 2;
		}
	}

	if(errCode == 0)
	{
		try
		{
			if(CallSmartView(_dstcUserSession, _dstcWorkSession) > WARNING)
			{
				errCode = 3;
			}
		}
		catch(...)
		{
			errCode = 3;
		}
	}	

	Logoff(_dstcUserSession);

	return errCode;
}

bool ParseArgugments( int argc, char** argv, std::string& username, std::string& password, std::string& client, std::string& siteXml)
{
	if(argc != 9)
	{
		return false;
	}
	std::map<std::string, std::string> paramMap;
	paramMap.insert(std::make_pair(argv[1], argv[2]));
	paramMap.insert(std::make_pair(argv[3], argv[4]));
	paramMap.insert(std::make_pair(argv[5], argv[6]));
	paramMap.insert(std::make_pair(argv[7], argv[8]));

	siteXml = paramMap["-S"];
	username = paramMap["-u"];
	password = paramMap["-p"];
	client = paramMap["-e"];

	if(siteXml.empty() || username.empty() || password.empty() || client.empty())
	{
		return false;
	}

	return true;
}

SEVERITY Logon(DSTCUserSession** _dstcUserSession, const std::string& username, const std::string& password)
{
	MAKEFRAMEAUTOPROMOTE2(I_( "IFAST_TM" ), CLASSNAME, I_("Logon"));
	SEVERITY severity = NO_CONDITION;

	try
	{
		DSTCUserSession* pPUS = PersistentUserSession::getInstance();
		if( NULL != pPUS )
		{
			// there is a PersistentUserSession ... we can use its GlobalSession as the GlobalSession
			// of the new UserSession.
			*_dstcUserSession = new DSTCUserSession( dynamic_cast< DSTCGlobalSession& >( pPUS->getGlobalSession() ) );
		}
		else
		{
			*_dstcUserSession = new DSTCUserSession;
		}

		DString _strUserName(username), _strPassword(password);

		SEVERITY severity = (*_dstcUserSession)->logon(DSTCHost::getPrimaryHost(), _strUserName, _strPassword);
	}
	catch( ConditionException &ce )
	{
		SETCONDITIONFROMEXCEPTION( ce );
	}
	catch( ... )
	{
		assert( 0 );
		THROWFROMFILE2(I_( "IFAST_TM" ), CLASSNAME, I_("Logon"), CND::BP_ERR_UNKNOWN_EXCEPTION );
	}

	return (GETCURRENTHIGHESTSEVERITY());
}

SEVERITY CallView(DSTCWorkSession** _dstrWorkSession, DSTCUserSession* _dstcUserSession, const DString& mgmtCoName)
{
	MAKEFRAMEAUTOPROMOTE2(I_( "IFAST_TM" ), CLASSNAME, I_("CallView"));
	SEVERITY severity = NO_CONDITION;

	try
	{
		//*_dstrWorkSession = &_dstcUserSession->createWorkSession(mgmtCoName);
		MgmtCoOptions2 *pMgmtCo = new MgmtCoOptions2(*_dstcUserSession);
		severity = pMgmtCo->initSynch(mgmtCoName, NULL_STRING , NULL_STRING);
	}
	catch( ConditionException &ce )
	{
		SETCONDITIONFROMEXCEPTION( ce );
	}
	catch( ... )
	{
		assert( 0 );
		THROWFROMFILE2(I_( "IFAST_TM" ), CLASSNAME, I_("CallView"), CND::BP_ERR_UNKNOWN_EXCEPTION );
	}

	return (GETCURRENTHIGHESTSEVERITY());
}

SEVERITY CallSmartView(DSTCUserSession* _dstcUserSession, DSTCWorkSession* _dstcWorkSession)
{
	MAKEFRAMEAUTOPROMOTE2(I_( "IFAST_TM" ), CLASSNAME, I_("CallSmartView"));
	SEVERITY severity = NO_CONDITION;

	try
	{
		if(_dstcUserSession != NULL && _dstcWorkSession != NULL)
		{
			MgmtCo & mgmtCo = _dstcWorkSession->getMgmtCo();

			DString dWebURL;
			_dstcWorkSession->getOption(ifds::CompanyUrl, dWebURL, BF::HOST, false);

			IStream* pStream = NULL;

			URLOpenBlockingStream(0, dWebURL.c_str(), &pStream, 0, 0);

			if (pStream)
			{
				char data[2000];
				ULONG readBytes = 0;
				HRESULT readResult = pStream->Read(data, sizeof(data), &readBytes);

				pStream->Release();
			}
			else
			{
				throw std::error_code();
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
		THROWFROMFILE2(I_( "IFAST_TM" ), CLASSNAME, I_("CallSmartView"), CND::BP_ERR_UNKNOWN_EXCEPTION );
	}

	return (GETCURRENTHIGHESTSEVERITY());
}

SEVERITY Logoff(DSTCUserSession *_dstcUserSession)
{
	MAKEFRAMEAUTOPROMOTE2(I_( "IFAST_TM" ), CLASSNAME, I_("CallView"));
	SEVERITY severity = NO_CONDITION;

	try
	{
		DString logoutMessage;
		//Logoff because either changing the password failed or something else happened
		if(_dstcUserSession)
		{
			SEVERITY severity = _dstcUserSession->logoff( DSTCHost::getPrimaryHost(), logoutMessage);
		}
	}
	catch( ConditionException &ce )
	{
		SETCONDITIONFROMEXCEPTION( ce );
	}
	catch( ... )
	{
		assert( 0 );
		THROWFROMFILE2(I_( "IFAST_TM" ), CLASSNAME, I_("Logoff"), CND::BP_ERR_UNKNOWN_EXCEPTION );
	}

	return (GETCURRENTHIGHESTSEVERITY());
}

BOOL SiteConfigInit( const std::string& t, bool bOverrideRegistry )
{
	// bOverrideRegistry - values from Site.xml file will override the ones in the user's registry
	std::string dstrSiteXml = t;
	//dstrSiteXml.stripLeading(I_(' '));
	//dstrSiteXml.stripTrailing(I_(' '));
	if ( dstrSiteXml.empty()) {
		return(TRUE);
	}
	ClientLocale clientLocale;
	LCID lcid = clientLocale.getLCID();
	DString dstrLang;

	//if client locale is french load the french resources
	//will be used for configuration slection and logon dialogs
	if(LANG_FRENCH == PRIMARYLANGID(LANGIDFROMLCID(lcid)))
	{
		dstrLang = I_("FR");
	}
	else
	{
		dstrLang = I_("ENG");
	}

	site::SiteConfig* pSC = site::SiteConfig::getInstance();

	ConfigManager *pDSTCMgr = ConfigManager::getManager( CONFIGURATION_CONSTANTS::MFDSTC );

	std::string SiteConfigFileName = dstrSiteXml;

	DString q = GetConfigValueAsString( I_("RTSHost"), I_("SMQInqQueue") );

	bool bSelectedFromDlg = false;
	if ( SiteConfigFileName != "" )
	{
		pSC->init( SiteConfigFileName, pDSTCMgr );
		DString dstrDescription = pSC->getDescription();
		Configuration cfg( I_("SiteXML") );
		if(bSelectedFromDlg)
		{
			DString dstrSiteConfigFileName = SiteConfigFileName;
			cfg.set( DString(I_("file")), dstrSiteConfigFileName );
		}
		else
		{
			cfg.set( DString(I_("file")), DString(dstrSiteXml));
		}
		cfg.set( DString(I_("Description")),dstrDescription);

		cfg.set( DString(I_("override")), bOverrideRegistry ? DString(I_("True")) : DString(I_("False")) );
		pDSTCMgr->storeConfig( cfg );
		pSC->setParm( I_("AwdType"),I_("InterfaceDll"), I_("AwdType"), site::DStringProperty( L"InterfaceDll"), bOverrideRegistry );
		pSC->setParm( I_("AwdType"),I_("AutoLogon"), I_("AwdType"), site::DStringProperty( L"AutoLogon" ), bOverrideRegistry );
		pSC->setParm( I_("DataPath"), I_("FYIfile"), I_("DataPath"), site::DStringProperty( L"FYIfile" ), bOverrideRegistry );
		pSC->setParm( I_("DataPath"), I_("Path"), I_("DataPath"), site::DStringProperty( L"Path" ), bOverrideRegistry );
		ConditionManager::getInstance()->setPath( GetConfigValueAsString( CONFIGURATION_CONSTANTS::MFDSTC, I_("DataPath"), I_("Path") ) );
		SetGlobalDataPath( GetConfigValueAsString( CONFIGURATION_CONSTANTS::MFDSTC, I_("DataPath"), I_("Path") ) );
		SetGlobalIniPath( GetConfigValueAsString( CONFIGURATION_CONSTANTS::MFDSTC, I_("DataPath"), I_("Path") ) );
		pSC->setParm( I_("DataPath"), I_("SysLoadPath"), I_("DataPath"), site::DStringProperty( L"SysLoadPath" ), bOverrideRegistry );
		pSC->setParm( I_("DataPath"), I_("RepositorySource"), I_("DataPath"), site::DStringProperty( L"RepositorySource" ), bOverrideRegistry );
		pSC->setParm( I_("DemoMode"), I_("ProtoDataPath"), I_("DemoMode"), site::DStringProperty( L"ProtoDataPath" ), bOverrideRegistry );

		pSC->setParm( I_("Support"), I_("SpecialPasswordRules"), I_("Support"),
			site::DStringProperty( L"SpecialPasswordRules" ), bOverrideRegistry );

		pSC->setParm( I_("Support"),I_("ViewTimeLog_Enable"), I_("ViewTimeLog"), site::DStringProperty( L"Active"), bOverrideRegistry );
		pSC->setParm( I_("Support"),I_("ViewTimeLog_Path"), I_("ViewTimeLog"), site::DStringProperty( L"Path"), bOverrideRegistry );
		pSC->setParm( I_("Support"),I_("ViewTimeLog_Size"), I_("ViewTimeLog"), site::DStringProperty( L"Size"), bOverrideRegistry );
		pSC->setParm( I_("Support"),I_("ViewTimeLog_Enable"), I_("Support"), site::DStringProperty( L"ViewTimeLog_Enable"), bOverrideRegistry );
		pSC->setParm( I_("Support"),I_("ViewTimeLog_Path"), I_("Support"), site::DStringProperty( L"ViewTimeLog_Path"), bOverrideRegistry );
		pSC->setParm( I_("Support"),I_("ViewTimeLog_Size"), I_("Support"), site::DStringProperty( L"ViewTimeLog_Size"), bOverrideRegistry );

		pSC->setParm( I_("Support"), I_("Log_File"), I_("LoggingOptions"), site::DStringProperty( L"LogFile" ), bOverrideRegistry );
		pSC->setParm( I_("Support"), I_("Log_Path"), I_("LoggingOptions"), site::DStringProperty( L"LogPath" ), bOverrideRegistry );
		pSC->setParm( I_("Support"), I_("Log_File"), I_("Support"), site::DStringProperty( L"Log_File" ), bOverrideRegistry );
		pSC->setParm( I_("Support"), I_("Log_Path"), I_("Support"), site::DStringProperty( L"Log_Path" ), bOverrideRegistry );
		pSC->setParm( I_("Support"), I_("Log_Enable"), I_("Support"), site::DStringProperty( L"Log_Enable" ), bOverrideRegistry );
		pSC->setParm( I_("Support"), I_("Log_Level"), I_("Support"), site::DStringProperty( L"Log_Level" ), bOverrideRegistry );

		pSC->setParm( I_("Support"), I_("ViewLog_Append"), I_("DebugOptions"), site::DStringProperty( L"AppendFile" ), bOverrideRegistry );
		pSC->setParm( I_("Support"), I_("ViewLog_Enable"), I_("DebugOptions"), site::DStringProperty( L"Debug" ), bOverrideRegistry );
		pSC->setParm( I_("Support"), I_("ViewLog_Path"), I_("DebugOptions"), site::DStringProperty( L"DebugPath" ), bOverrideRegistry );
		pSC->setParm( I_("Support"), I_("ViewLog_Complete"), I_("DebugOptions"), site::DStringProperty( L"CompleteLog" ), bOverrideRegistry );
		pSC->setParm( I_("Support"), I_("ViewLog_Append"), I_("Support"), site::DStringProperty( L"ViewLog_Append" ), bOverrideRegistry );
		pSC->setParm( I_("Support"), I_("ViewLog_Enable"), I_("Support"), site::DStringProperty( L"ViewLog_Enable" ), bOverrideRegistry );
		pSC->setParm( I_("Support"), I_("ViewLog_Path"), I_("Support"), site::DStringProperty( L"ViewLog_Path" ), bOverrideRegistry );
		pSC->setParm( I_("Support"), I_("ViewLog_Complete"), I_("Support"), site::DStringProperty( L"ViewLog_Complete" ), bOverrideRegistry );
		pSC->setParm( I_("Support"), I_("ViewLog_InsertDateTime"), I_("Support"), site::DStringProperty( L"ViewLog_InsertDateTime" ), bOverrideRegistry );

		pSC->setParm( I_("Support"), I_("ExceptionReport_Enable"), I_("Support"), site::DStringProperty( L"ExceptionReport_Enable" ), bOverrideRegistry );
		pSC->setParm( I_("Support"), I_("ExceptionReport_Path"), I_("Support"), site::DStringProperty( L"ExceptionReport_Path" ), bOverrideRegistry );

		pSC->setParm( I_("Support"), I_("DisplayConnectionIcon"), I_("Support"), site::DStringProperty( L"DisplayConnectionIcon" ), bOverrideRegistry );
		pSC->setParm( I_("Support"), I_("DisplayConditionName"), I_("Support"), site::DStringProperty( L"DisplayConditionName" ), bOverrideRegistry );
		pSC->setParm( I_("Support"), I_("AllPowerfulVaalMode"), I_("Support"), site::DStringProperty( L"AllPowerfulVaalMode" ), bOverrideRegistry );
		pSC->setParm( I_("Support"), I_("ShowClientNamePane"), I_("Support"), site::DStringProperty( L"ShowClientNamePane" ), bOverrideRegistry );
		pSC->setParm( I_("Support"), I_("ExceptionReport_Enable"), I_("Support"), site::DStringProperty( L"ExceptionReport_Enable" ), bOverrideRegistry );
		pSC->setParm( I_("Support"), I_("ExceptionReport_Path"), I_("Support"), site::DStringProperty( L"ExceptionReport_Path" ), bOverrideRegistry );
		pSC->setParm( I_("Support"), I_("BandInfoByCompanyId"), I_("Support"), site::DStringProperty( L"BandInfoByCompanyId" ), bOverrideRegistry );

#ifdef _DEBUG
		pSC->setParm( I_("Debug"), I_("OverridenDSKURLEnable"), I_("Debug"), site::DStringProperty( L"OverridenDSKURLEnable" ), bOverrideRegistry );
		pSC->setParm( I_("Debug"), I_("OverridenDSKURL"), I_("Debug"), site::DStringProperty( L"OverridenDSKURL" ), bOverrideRegistry );
		pSC->setParm( I_("Debug"), I_("DebugEXT"), I_("Debug"), site::DStringProperty( L"DebugEXT" ), bOverrideRegistry );
		pSC->setParm( I_("Debug"), I_("StubModeOnBrowserScreen"), I_("Debug"), site::DStringProperty( L"StubModeOnBrowserScreen" ), bOverrideRegistry );
		pSC->setParm( I_("Debug"), I_("ShowMGMTOptionsSeparator"), I_("Debug"), site::DStringProperty( L"ShowMGMTOptionsSeparator" ), bOverrideRegistry );
#endif

		pSC->setParm( I_("Support"), I_("ReportEMailAddress"), I_("Support"), site::DStringProperty( L"ReportEMailAddress" ), bOverrideRegistry );
		pSC->setParm( I_("Support"), I_("ControlTextRewriter_Path"),
			I_("Support"), site::DStringProperty( L"ControlTextRewriter_Path" ), bOverrideRegistry );
		pSC->setParm( I_("Support"), I_("KeyPeek_Path"), I_("Support"), site::DStringProperty( L"KeyPeek_Path" ), bOverrideRegistry );

		pSC->setParm( I_("Market"), I_("Market"), I_("Market"), site::DStringProperty( L"Market" ), bOverrideRegistry );

		pSC->setParm( I_("Market"), I_("ValidCompanies"), I_("Market"), site::DStringProperty( L"ValidCompanies" ), bOverrideRegistry );

		pSC->setParm( I_("Csi"), I_("Host"), I_("Csi"), site::DStringProperty( L"Host" ), bOverrideRegistry );
		pSC->setParm( I_("Csi"), I_("Param"), I_("Csi"), site::DStringProperty( L"Param" ), bOverrideRegistry );
		pSC->setParm( I_("Csi"), I_("Type"), I_("Csi"), site::DStringProperty( L"Type" ), bOverrideRegistry );

		pSC->setParm( I_("RTSHost"), I_("RTSHostIP"), I_("RTSHost"), site::DStringProperty( L"RTSHostIP" ), bOverrideRegistry );
		pSC->setParm( I_("RTSHost"), I_("PersistentConnections"), I_("RTSHost"), site::DStringProperty( L"PersistentConnections" ), bOverrideRegistry );
		pSC->setParm( I_("RTSHost"), I_("RecycleInterval"), I_("RTSHost"), site::DStringProperty( L"RecycleInterval" ), bOverrideRegistry );
		pSC->setParm( I_("RTSHost"), I_("SMQBrokerURLs"), I_("RTSHost"), site::DStringProperty( L"SMQBrokerURLs" ), bOverrideRegistry );
		pSC->setParm( I_("RTSHost"), I_("SMQUser"), I_("RTSHost"), site::DStringProperty( L"SMQUser" ), bOverrideRegistry );
		pSC->setParm( I_("RTSHost"), I_("SMQPassword"), I_("RTSHost"), site::DStringProperty( L"SMQPassword" ), bOverrideRegistry );
		pSC->setParm( I_("RTSHost"), I_("SMQMultiQueue"), I_("RTSHost"), site::DStringProperty( L"SMQUpdQueue" ), bOverrideRegistry );
		pSC->setParm( I_("RTSHost"), I_("SMQMultiQueue"), I_("RTSHost"), site::DStringProperty( L"SMQMultiQueue" ), bOverrideRegistry );
		pSC->setParm( I_("RTSHost"), I_("SMQSingleQueue"), I_("RTSHost"), site::DStringProperty( L"SMQInqQueue" ), bOverrideRegistry );
		pSC->setParm( I_("RTSHost"), I_("SMQSingleQueue"), I_("RTSHost"), site::DStringProperty( L"SMQSingleQueue" ), bOverrideRegistry );
		pSC->setParm( I_("RTSHost"), I_("cswacl"), I_("RTSHost"), site::DStringProperty( L"cswacl" ), bOverrideRegistry );
		pSC->setParm( I_("RTSHost"), I_("SMQWaitTimeout"), I_("RTSHost"), site::DStringProperty( L"SMQWaitTimeout" ), bOverrideRegistry );
		pSC->setParm( I_("RTSHost"), I_("SMQRTSDataFormat"), I_("RTSHost"), site::DStringProperty( L"SMQRTSDataFormat" ), bOverrideRegistry );
		pSC->setParm( I_("RTSHost"), I_("UseSonicMQ"), I_("RTSHost"), site::DStringProperty( L"UseSonicMQ" ), bOverrideRegistry );
		pSC->setParm( I_("RTSHost"), I_("UseSCC"), I_("RTSHost"), site::DStringProperty( L"UseSCC" ), bOverrideRegistry );
		pSC->setParm( I_("RTSHost"), I_("LDAPUserNS"), I_("RTSHost"), site::DStringProperty( L"UserNS" ), bOverrideRegistry );
		pSC->setParm( I_("RTSHost"), I_("LDAPUserNS"), I_("RTSHost"), site::DStringProperty( L"LDAPUserNS" ), bOverrideRegistry );
		pSC->setParm( I_("RTSHost"), I_("SMQLDAPQueue"), I_("RTSHost"), site::DStringProperty( L"SMQLDAPQueue" ), bOverrideRegistry );
		pSC->setParm( I_("RTSHost"), I_("SMQAWDQueue"), I_("RTSHost"), site::DStringProperty( L"SMQAWDQueue" ), bOverrideRegistry );
		pSC->setParm( I_("RTSHost"), I_("UseSingleSonicConnection"), I_("RTSHost"), site::DStringProperty( L"UseSingleSonicConnection" ), bOverrideRegistry );
		pSC->setParm( I_("RTSHost"), I_("ViewBatch"), I_("RTSHost"), site::DStringProperty( L"ViewBatch"), bOverrideRegistry );

		pSC->setParm( I_("Session"), I_("NotUse_AWD"), I_("Session"), site::DStringProperty( L"NotUse_AWD" ), bOverrideRegistry );
		pSC->setParm( I_("Session"), I_("NotUse_AWD_File"), I_("Session"), site::DStringProperty( L"NotUse_AWD_File" ), bOverrideRegistry );
		pSC->setParm( I_("Session"), I_("NotUse_AWD_Type"), I_("Session"), site::DStringProperty( L"NotUse_AWD_Type" ), bOverrideRegistry );

		pSC->setParm( I_("Session"), I_("UseIntegration_AWD"), I_("Session"), site::DStringProperty( L"UseIntegration_AWD" ), bOverrideRegistry );
		pSC->setParm( I_("Session"), I_("UseIntegration_AWD_File"), I_("Session"), site::DStringProperty( L"UseIntegration_AWD_File" ), bOverrideRegistry );
		pSC->setParm( I_("Session"), I_("UseIntegration_AWD_Type"), I_("Session"), site::DStringProperty( L"UseIntegration_AWD_Type" ), bOverrideRegistry );

		pSC->setParm( I_("Session"), I_("UsePortalIntegration_AWD"), I_("Session"), site::DStringProperty( L"UsePortalIntegration_AWD" ), bOverrideRegistry );
		pSC->setParm( I_("Session"), I_("UsePortalIntegration_AWD_File"), I_("Session"), site::DStringProperty( L"UsePortalIntegration_AWD_File" ), bOverrideRegistry );
		pSC->setParm( I_("Session"), I_("UsePortalIntegration_AWD_Type"), I_("Session"), site::DStringProperty( L"UsePortalIntegration_AWD_Type" ), bOverrideRegistry );
		pSC->setParm( I_("Session"), I_("UsePortalIntegration_AWD_Topic"), I_("Session"), site::DStringProperty( L"UsePortalIntegration_AWD_Topic" ), bOverrideRegistry );

		pSC->setParm( I_("Session"), I_("CallCentreIntegration"), I_("Session"), site::DStringProperty( L"CallCentreIntegration" ), bOverrideRegistry );
		pSC->setParm( I_("Session"), I_("CallCentreIntegration_File"), I_("Session"), site::DStringProperty( L"CallCentreIntegration_File" ), bOverrideRegistry );
		pSC->setParm( I_("Session"), I_("CallCentreIntegration_Type"), I_("Session"), site::DStringProperty( L"CallCentreIntegration_Type" ), bOverrideRegistry );
		pSC->setParm( I_("Session"), I_("CallCentreIntegration_Topic"), I_("Session"), site::DStringProperty( L"CallCentreIntegration_Topic" ), bOverrideRegistry );
	}

	if(GetConfigValueAsBool(I_("RTSHost"), I_("UseActiveMQ")))
	{
	    ifastdbrkr::setMessageService( ifastdbrkr::MessageService::ActiveMQ );
	}
	else 
	{
		ifastdbrkr::setMessageService( ifastdbrkr::MessageService::SonicMQ );
	}

	return(TRUE);
}