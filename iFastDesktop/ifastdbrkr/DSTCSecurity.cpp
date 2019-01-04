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
//    Copyright 1999 by DSTCanada, Inc.
//
//
//******************************************************************************
//
// ^FILE   :DSTCSecurity.cpp
// ^AUTHOR :Serban Popescu
// ^DATE   :06/25/99
//
// ----------------------------------------------------------
#pragma warning( disable : 4786)  

#include <botan/botan.h>
#include <SrcPrag.h>
#include "DSTCSecurity.hpp"
#include <bfdbrkr\BFDataBroker.hpp>
#include "DSTCRequestor.hpp"
#include "DSTCRequest.hpp"
#include "DSTCHost.hpp"
#include <conditionmanager.hpp>
#include <dstring.hpp>
#include <idistring.hpp>
#include <bfconmgr\bfconnectionmanager.hpp>
#include <bf/log/log.hpp>

//data dictionary stuff needed for the security
//logon data
#include <ifastdataimpl\dse_DSTC0001_REQ.hpp>
#include <ifastdataimpl\dse_DSTC0001_VW.hpp>
//logoff
#include <ifastdataimpl\dse_DSTC0002_REQ.hpp>
#include <ifastdataimpl\dse_DSTC0002_VW.hpp>
//change password
#include <ifastdataimpl\dse_DSTC0039_REQ.hpp>
#include <ifastdataimpl\dse_DSTC0039_VW.hpp>


#ifndef INCLUDED_DSTRING
#define INCLUDED_DSTRING
#include "dstring.hpp"
#endif

#include "SonicConnectionFactory.hpp"
#include "SonicConnection.hpp"
#include <configmanager.hpp>
#ifndef CONFIGURATION_HPP
   #include "configuration.hpp"
#endif
#include <tinyxml.h>



using namespace Botan;

const DStringA encrypt(const DStringA& in, const DStringA& password)
{
	if(""==in)
		return in;

	// digested password
	Botan::Pipe pipe(new Botan::Hash_Filter("MD5"));
    pipe.process_msg(password.getImp());
	Botan::byte mykey[16];
	memset(mykey,0x00,16);
	pipe.read(mykey, 16);

	// AES/CBC/PKCS7 encrypt
	Botan::SymmetricKey key(mykey, 16);
	const Botan::byte initv[16]={ 0x27, 0x76, 0xa5, 0x5d, 0xf1, 0x92, 0x77, 0x5f, 0x27, 0x76, 0xa5, 0x5d, 0xf1, 0x92, 0x77, 0x5f };
	Botan::InitializationVector iv(initv, 16);
	Botan::Pipe encryptor(get_cipher("AES-128/CBC/PKCS7", key, iv, ENCRYPTION),new Botan::Base64_Encoder);
	try
	{
        encryptor.process_msg(in.getImp());
		return encryptor.read_all_as_string(0);
	}
	catch (Botan::Exception e)
	{
		return "";
	}
}

// base64 decode base64_encoded_in and then use AES/CBC/PKCS7 to decrypt 
// it using MD5 digested password
const DStringA decrypt(const DStringA& base64_encoded_in, const DStringA& password)
{
	if(""==base64_encoded_in)
		return base64_encoded_in;

	// digested password
	Botan::Pipe pipe(new Botan::Hash_Filter("MD5"));
    pipe.process_msg(password.getImp());
	Botan::byte mykey[16];
	memset(mykey,0x00,16);
	pipe.read(mykey, 16);

	// AES/CBC/PKCS7 decrypt
	Botan::SymmetricKey key(mykey, 16);
	const Botan::byte initv[16]={ 0x27, 0x76, 0xa5, 0x5d, 0xf1, 0x92, 0x77, 0x5f, 0x27, 0x76, 0xa5, 0x5d, 0xf1, 0x92, 0x77, 0x5f };
	Botan::InitializationVector iv(initv, 16);
	Botan::Pipe decryptor(new Base64_Decoder,
		get_cipher("AES-128/CBC/PKCS7", key, iv, DECRYPTION),new Botan::Base64_Encoder);
	try
	{
        decryptor.process_msg(base64_encoded_in.getImp());
		return decryptor.read_all_as_string(0);
	}
	catch (Botan::Invalid_Argument e)
	{
        return "";
	}
}

const DStringA getMessageCode(TiXmlDocument &doc)
{
	TiXmlElement* root = doc.FirstChildElement( "AuthResponse" );
    if (0 != root)
    {
    	TiXmlElement* element = root->FirstChildElement( "Message" );

	    if(element!=0){
		    TiXmlAttribute* pAttrib=element->FirstAttribute();
		    return pAttrib->Value();
	    }else{
		    return "";
	    }
    }
    else
    {
        return "";
    }
}

namespace
{
   const I_CHAR * const LANG_ACL_ENGLISH = I_( "ENG" );
   const I_CHAR * const LANG_ACL_JAPAN   = I_( "JPN" );
   const I_CHAR * const LANG_ACL_JAPAN1  = I_( "JAN" );
   const I_CHAR * const LANG_ACL_FRENCH  = I_( "FRN" );
   const I_CHAR * const LANG_ACL_GERMAN  = I_( "DEU" );
   const I_CHAR * const LANG_ACL_SPANISH = I_( "ESP" );
   const I_CHAR * const LANG_ACL_DUTCH   = I_( "NDL" );
   const I_CHAR * const LANG_ACL_ITALIAN = I_( "ITA" );

   const I_CHAR * const LANG_LDAP_ENGLISH = I_( "en" );
   const I_CHAR * const LANG_LDAP_JAPAN   = I_( "ja" );
   const I_CHAR * const LANG_LDAP_FRENCH  = I_( "fr" );
   const I_CHAR * const LANG_LDAP_GERMAN  = I_( "de" );
   const I_CHAR * const LANG_LDAP_SPANISH = I_( "es" );
   const I_CHAR * const LANG_LDAP_DUTCH   = I_( "nl" );
   const I_CHAR * const LANG_LDAP_ITALIAN = I_( "it" );

   const I_CHAR * const LANG_COUNTRY_ENGLISH = I_( "enUS" );
   const I_CHAR * const LANG_COUNTRY_JAPAN   = I_( "jaJP" );
   const I_CHAR * const LANG_COUNTRY_FRENCH  = I_( "frCA" );
   const I_CHAR * const LANG_COUNTRY_GERMAN  = I_( "deDE" );
   const I_CHAR * const LANG_COUNTRY_SPANISH = I_( "esES" );
   const I_CHAR * const LANG_COUNTRY_DUTCH   = I_( "nlNL" );
   const I_CHAR * const LANG_COUNTRY_ITALIAN = I_( "itIT" );
}

namespace
{
   const I_CHAR* const CLASSNAME                = I_( "DSTCSecurity" );

   const I_CHAR* const DSTCSECURITY             = I_( "DSTCSecurity::DSTCSecurity" );
   const I_CHAR* const LOGON                    = I_( "logon" );
   const I_CHAR* const LOGOFF                   = I_( "logoff" );
   const I_CHAR* const CHANGEPASSWORD           = I_( "changePassword" );
   const I_CHAR* const ESTABLISH_LOGON_STATE    = I_( "establishLogonState" );
   const I_CHAR* const GET_USER_ID              = I_( "getUserId" );
   const I_CHAR* const GET_SESSION_ID           = I_( "getSessionId" );
   const I_CHAR* const GET_LANGUAGE             = I_( "getLanguage" );
   const I_CHAR* const GET_LOCALE               = I_( "getLocale" );
   const I_CHAR* const GET_USER_NAME            = I_( "getUserName" );
   const I_CHAR* const GET_DAYS_PASSWORD_CHANGE = I_( "getDaysPasswordChange" );
   const I_CHAR* const GET_NUMBER_OF_COMPANIES  = I_( "getNumberOfCompanies" );
   const I_CHAR* const GET_COMPANY_INFO         = I_( "getCompanyInfo" );
   const I_CHAR* const COPY_SIGNON_DATA         = I_( "copySignonData" );



   const I_CHAR* const YES = I_( "Y" );
   const I_CHAR * const THRESHOLD = I_( "threshold" );
   const I_CHAR * const FFID_TYPE = I_( "FFID" );
   const I_CHAR * const SSID_TYPE = I_( "S" );
   const I_CHAR * const RRID_TYPE = I_( "RRID" );
}


namespace CND
{
	extern const I_CHAR *IFASTDBRKR_CONDITION;
	extern const long IFASTDBRKR_NOT_LOGGED_ON;

	extern const long ERR_PD_PASSWORD_MUST_BE_AT_LEAST;
	extern const long ERR_PD_PASSWORD_CAN_ONLY_BE;
	extern const long ERR_PD_CANNOT_CHANGE_PASSORD_FOR;
	extern const long ERR_MANAGEMENT_COMPANY_NOT_FOUND;

	extern const long ERR_AUTH_TOKEN_EXP ;
	extern const long ERR_AUTH_INACTIVE ;
	extern const long ERR_AUTH_LOCKED;
	extern const long ERR_AUTH_MAX_LOGONS ;
	extern const long ERR_AUTH_CHPWD_REQD ;
	extern const long ERR_NO_USER ;
	extern const long ERR_PWD_NOT_CHANGE ;
	extern const long PWD_RECENTLY_USED ;
	extern const long ERR_NOT_AUTHENTIC;
	extern const long ERR_RTS_SYSTEM_ISSUE;
}

namespace CORFAX
{
   extern CLASS_EXPORT const DSTCHost HOST;
}

namespace DSTC_REQUEST
{

   extern CLASS_EXPORT const DSTCRequest LOGON;
   extern CLASS_EXPORT const DSTCRequest LOGOFF;
   extern CLASS_EXPORT const DSTCRequest CHANGE_PASSWORD;

}

//******************************************************************************
DSTCSecurity::DSTCSecurity(const BFHost* host) 
:  _host(host)
, _loggedOn( false )
, _userID( NULL_STRING )
, _sessionId( NULL_STRING )
, _language( NULL_STRING )
, _locale( NULL_STRING )
, _signonData( NULL )
, _LDAPloggedOn( false )
{
   TRACE_CONSTRUCTOR( CLASSNAME, DSTCSECURITY );
}

//******************************************************************************
DSTCSecurity::~DSTCSecurity()
{
   TRACE_DESTRUCTOR( CLASSNAME );
   if( _signonData ) delete _signonData;
}

//******************************************************************************
SEVERITY DSTCSecurity::logon( const DString& userID, const DString& password )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTDBRKR_CONDITION, CLASSNAME, LOGON );

	_userID = NULL_STRING;
	setSessionId(NULL_STRING);
	_language = NULL_STRING;
	_locale = NULL_STRING;
	_loggedOn = false;

	
	logonWithLDAP( userID, password );

	_locale = getLocale(_language);

	return(GETCURRENTHIGHESTSEVERITY()); 
}

const DString DSTCSecurity::getLocale(const DString language)
{
   if( language == LANG_LDAP_JAPAN || language == LANG_ACL_JAPAN || language == LANG_ACL_JAPAN )
   {
      return LANG_COUNTRY_JAPAN;
   }
   else if( language == LANG_LDAP_FRENCH || language == LANG_ACL_FRENCH  )
   {
      return LANG_COUNTRY_FRENCH;
   }
   else if( language == LANG_LDAP_GERMAN || language == LANG_ACL_GERMAN )
   {
      return LANG_COUNTRY_GERMAN;
   }
   else if( language == LANG_LDAP_SPANISH || language == LANG_ACL_SPANISH )
   {
      return LANG_COUNTRY_SPANISH;
   }
   else if( language == LANG_LDAP_DUTCH || language == LANG_ACL_DUTCH )
   {
      return LANG_COUNTRY_DUTCH;
   }
   else if( language == LANG_LDAP_ITALIAN || language == LANG_ACL_ITALIAN ) //to be confirmed...
   {
      return LANG_COUNTRY_ITALIAN;
   }
   
   return LANG_COUNTRY_ENGLISH;
}

SEVERITY DSTCSecurity::logonWithLDAP( const DString& userID, 
									 const DString& password )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTDBRKR_CONDITION, 
		CLASSNAME, 
		I_("logonWithLDAP") );

	_userID = userID;

   BFRecordConnection* connection = NULL;

	try
	{
		connection = 
			dynamic_cast< BFRecordConnection* >
			( BFConnectionManager::getInstance()->getConnection( I_("RTSCAN")) );

		const DStringA pass1res = SMQSendReceive(connection, createPassOneDoc(userID, 
			GetConfigValueAsString( I_("RTSHost"), I_("LDAPUserNS"))));

		TiXmlDocument doc;
		doc.Parse( pass1res.c_str() );
		DStringA authToken = getToken(doc, password);

		const DStringA pass2res = SMQSendReceive(connection, createPassTwoDoc(userID, 
			GetConfigValueAsString( I_("RTSHost"), I_("LDAPUserNS")),DString(authToken)));

		TiXmlDocument doc1;
		doc1.Parse( pass2res.c_str() );
		DStringA _sessionToken = getToken(doc1, password);

		DStringA status = getStatus(doc1);

		if(status == "Accepted"){
			_userID = userID;
			setSessionId(DString(_sessionToken));
			createView1Response(doc1);
			_loggedOn = true;
			_LDAPloggedOn = true;
		}
		else{
			const DStringA errCode = getMessageCode(doc1);

			if("AUTH_TOKEN_EXP" == errCode){
				ADDCONDITIONFROMFILE( CND::ERR_AUTH_TOKEN_EXP );
			} else if("AUTH_INACTIVE" == errCode){
				ADDCONDITIONFROMFILE( CND::ERR_AUTH_INACTIVE );
			} else if("AUTH_LOCKED" == errCode){
				ADDCONDITIONFROMFILE( CND::ERR_AUTH_LOCKED );
			} else if("AUTH_MAX_LOGONS" == errCode){
				ADDCONDITIONFROMFILE( CND::ERR_AUTH_MAX_LOGONS );
			} else if("AUTH_CHPWD_REQD" == errCode){
				// just fool the app so that it behave the same as ACL
				_signonData = new BFData( ifds::DSTC0001_VW ); 
				_language = I_("ENG");
				_signonData->setElementValue (ifds::DaysPasswdChange, I_("0"));
				_signonData->setElementValue (ifds::LanguageCode, _language);
				_signonData->setElementValue( ifds::RepeatCount, I_("0") );
				_loggedOn = true;
			} else if("NO_USER" == errCode){
				ADDCONDITIONFROMFILE( CND::ERR_NO_USER );
			} else {
				ADDCONDITIONFROMFILE( CND::ERR_NOT_AUTHENTIC );
			}
		}
	}
    catch (Botan::Invalid_Argument e)
	{
		ADDCONDITIONFROMFILE( CND::ERR_NOT_AUTHENTIC );
	}
    catch(...){
		ADDCONDITIONFROMFILE( CND::ERR_RTS_SYSTEM_ISSUE );
	}
   if( NULL != connection ) {
      BFConnectionManager::getInstance()->freeConnection(connection);
   }

	return(GETCURRENTHIGHESTSEVERITY()); 
}

//******************************************************************************
SEVERITY DSTCSecurity::logoff( DString& logoutMessage )
{
    MAKEFRAMEAUTOPROMOTE2( CND::IFASTDBRKR_CONDITION, CLASSNAME, LOGOFF );

    logoffFromLDAP( logoutMessage );

    return(GETCURRENTHIGHESTSEVERITY()); 
}

//******************************************************************************
SEVERITY DSTCSecurity::logoffFromLDAP( DString& logoutMessage )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTDBRKR_CONDITION, CLASSNAME, I_("logoffFromLDAP") );

	if( !_loggedOn )
	{
		ADDCONDITIONFROMFILE( CND::IFASTDBRKR_NOT_LOGGED_ON );
		logoutMessage = NULL_STRING;
	}
	else
	{
		BFRecordConnection* connection = dynamic_cast< BFRecordConnection* >( BFConnectionManager::getInstance()->getConnection(I_("RTSCAN") )  );

		DStringA res = DSTCSecurity::SMQSendReceive(connection, 
			createLogoffDoc(_userID, GetConfigValueAsString( I_("RTSHost"), I_("LDAPUserNS")), getSessionId()));

		// logoff sometimes fail but we still need to clean up user data
		if( _signonData )
		{
			delete _signonData;
			_signonData = NULL;
		}

		_userID = NULL_STRING;
		setSessionId(NULL_STRING);
		_language = NULL_STRING;
		_locale = NULL_STRING;
		_loggedOn = false;
		_LDAPloggedOn = false;
      
      if( NULL != connection ) {
         BFConnectionManager::getInstance()->freeConnection(connection);
      }
	}

	return(GETCURRENTHIGHESTSEVERITY()); 
}

SEVERITY DSTCSecurity::changePassword( const DString& password, const DString& newPassword )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTDBRKR_CONDITION, CLASSNAME, CHANGEPASSWORD );

	if( changePasswordWithLDAP( password, newPassword ) <= WARNING && _LDAPloggedOn == false)
		logonWithLDAP( _userID, newPassword );

	return(GETCURRENTHIGHESTSEVERITY()); 
}

SEVERITY DSTCSecurity::changePasswordWithLDAP( const DString& password, const DString& newPassword )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTDBRKR_CONDITION, CLASSNAME, I_("changePasswordWithLDAP" ));

	BFRecordConnection* connection = dynamic_cast< BFRecordConnection* >( BFConnectionManager::getInstance()->getConnection(I_("RTSCAN") )  );

	DStringA res = DSTCSecurity::SMQSendReceive(connection,
		createChangePasswordDoc(_userID, GetConfigValueAsString( I_("RTSHost"), I_("LDAPUserNS")), password, newPassword));

	TiXmlDocument doc;
	doc.Parse( res.c_str() );

	DStringA status = getStatus(doc);

	if( "Accepted" != status ){
		const DStringA errCode = getMessageCode(doc);

		if("PWD_RECENTLY_USED" == errCode){
			ADDCONDITIONFROMFILE( CND::PWD_RECENTLY_USED );
		} else {
			ADDCONDITIONFROMFILE( CND::ERR_PWD_NOT_CHANGE );
		}
	} 

	if( NULL != connection ) {
		BFConnectionManager::getInstance()->freeConnection(connection);
	}

	return(GETCURRENTHIGHESTSEVERITY()); 
}

//******************************************************************************
bool DSTCSecurity::isLoggedOn() const
{
   return(_loggedOn);
}

//******************************************************************************
const DString& DSTCSecurity::getLanguage() const
{
   if( !_loggedOn )
      THROWFROMFILE2( CND::IFASTDBRKR_CONDITION, CLASSNAME, GET_LANGUAGE, CND::IFASTDBRKR_NOT_LOGGED_ON );

   return(_language);
}

//******************************************************************************
const DString& DSTCSecurity::getLocale() const
{
   if( !_loggedOn )
      THROWFROMFILE2( CND::IFASTDBRKR_CONDITION, CLASSNAME, GET_LOCALE, CND::IFASTDBRKR_NOT_LOGGED_ON );

   return(_locale);
}

//******************************************************************************
const BFHost *DSTCSecurity::getHost() const
{
   return(_host);
}

//******************************************************************************
// this function is used the server app to re-create a thin security object 
void DSTCSecurity::establishLogonState( const DString& userID, 
                                        const DString& sessionID, 
                                        const DString& language )
{
   if( _loggedOn )
      // changed error to already logged on
      THROWFROMFILE2( CND::IFASTDBRKR_CONDITION, CLASSNAME, ESTABLISH_LOGON_STATE, CND::IFASTDBRKR_NOT_LOGGED_ON );

   if( _signonData )
   {
      delete _signonData;
      _signonData = NULL;
   }
   _userID = userID;
   setSessionId(sessionID);

   if( language == I_("jp") )
   {
      _locale = I_("jaJP");
   }
   else if( language == I_("fr") )
   {
      _locale = I_("frCA");
   }
   else if( language == I_("de") )
   {
      _locale = I_("deDE");
   }
   else if( language == I_("es") )
   {
      _locale = I_("esES");
   }
   else if( language == I_("nl") )
   {
      _locale = I_("nlNL");
   }
   else if( language == I_("it") )
   {
      _locale = I_("itIT");
   }
   else
   {
      _locale = I_("enUS");
   }
   _loggedOn = true;
}

//******************************************************************************
const DString& DSTCSecurity::getUserId() const
{
   if( !_loggedOn )
      THROWFROMFILE2( CND::IFASTDBRKR_CONDITION, CLASSNAME, GET_USER_ID, CND::IFASTDBRKR_NOT_LOGGED_ON );

   return(_userID);
}

//******************************************************************************
const DString& DSTCSecurity::getSessionId() const
{
   if( !_loggedOn )
      THROWFROMFILE2( CND::IFASTDBRKR_CONDITION, CLASSNAME, GET_SESSION_ID, CND::IFASTDBRKR_NOT_LOGGED_ON );

   BFGuard g( _csSessionId );
   return(_sessionId);
}

void DSTCSecurity::setSessionId(const DString& sessionId)
{
/*
   bf::log::LogStream ls( bf::log::databroker );
   ls << bf::log::information;
   BFGuard g( _csSessionId );
   ls << I_("Resetting SessionId:  From ") << _sessionId << bf::log::endl;
   ls << I_("                        To ") << sessionId << bf::log::endlf;
*/
   _sessionId = sessionId;
}

//******************************************************************************
DString DSTCSecurity::getUserName() const
{
   if( !_loggedOn  || !_signonData )
      THROWFROMFILE2( CND::IFASTDBRKR_CONDITION, CLASSNAME, GET_USER_NAME, CND::IFASTDBRKR_NOT_LOGGED_ON );

   return(_signonData->getElementValue( ifds::Username ).strip());
}

//******************************************************************************
DString DSTCSecurity::getDaysPasswordChange() const
{
   if( !_loggedOn  || !_signonData )
      THROWFROMFILE2( CND::IFASTDBRKR_CONDITION, CLASSNAME, GET_DAYS_PASSWORD_CHANGE, CND::IFASTDBRKR_NOT_LOGGED_ON );

   return (_signonData->getElementValue( ifds::DaysPasswdChange ).stripLeading('0').stripTrailing());

}

//******************************************************************************
long DSTCSecurity::getNumberOfCompanies() const
{
   if( !_loggedOn  || !_signonData )
      THROWFROMFILE2( CND::IFASTDBRKR_CONDITION, CLASSNAME, GET_NUMBER_OF_COMPANIES, CND::IFASTDBRKR_NOT_LOGGED_ON );

   DString numberOfCompanies = _signonData->getElementValue( ifds::RepeatCount );
   return(numberOfCompanies.convertToULong());
}

//******************************************************************************
void DSTCSecurity::getCompanyInfo( const unsigned long companyIndex, 
                                   DString &companyId,
                                   DString &companyName ) const
{
   if( !_loggedOn  || !_signonData )
      THROWFROMFILE2( CND::IFASTDBRKR_CONDITION, CLASSNAME, GET_COMPANY_INFO, CND::IFASTDBRKR_NOT_LOGGED_ON );

   DString numberOfCompanies = _signonData->getElementValue( ifds::RepeatCount );

   const BFData& companyData = _signonData->getRepeat( companyIndex );

   companyId = companyData.getElementValue( ifds::CompanyId ).strip();
   companyName = companyData.getElementValue( ifds::CompanyName ).strip();

}


//******************************************************************************
//this method creates a copy on the heap of the signon data
//the caller is responsible to manage the life of the copy
void DSTCSecurity::copySignonData( BFData*& signonData ) const
{
   if( !_loggedOn  || !_signonData )
      THROWFROMFILE2( CND::IFASTDBRKR_CONDITION, CLASSNAME, COPY_SIGNON_DATA, CND::IFASTDBRKR_NOT_LOGGED_ON );

   signonData = new BFData( *_signonData );
}

//******************************************************************************
void DSTCSecurity::getClientId (const DString& strCompanyId, 
                                DString& clientId, 
                                DString& strCompanyName, 
                                DString &companyUrl) const
{
   if (!_loggedOn  || !_signonData)
      THROWFROMFILE2 (CND::IFASTDBRKR_CONDITION, CLASSNAME, GET_COMPANY_INFO, CND::IFASTDBRKR_NOT_LOGGED_ON);

   clientId = NULL_STRING;
   strCompanyName = NULL_STRING;
   companyUrl = NULL_STRING;

   DString numberOfCompanies = _signonData->getElementValue( ifds::RepeatCount );
   int cCompanies = numberOfCompanies.asInteger();
   int companyIndex = 0;

   while (companyIndex < cCompanies)
   {
      const BFData& companyData = _signonData->getRepeat (companyIndex);
      DString companyId = companyData.getElementValue (ifds::CompanyId).strip();

      if (companyId == strCompanyId)
      {
         clientId = companyData.getElementValue (ifds::ClientID).strip();
         strCompanyName = companyData.getElementValue (ifds::CompanyName).strip();
         companyUrl = companyData.getElementValue(ifds::CompanyUrl).strip();
         break;
      }
      companyIndex++;
   }
}

//******************************************************************************
void DSTCSecurity::getAllSlSRepFlag(const DString& strCompanyId, DString& strAccessAllSlsRep ) const
{
   if( !_loggedOn  || !_signonData )
      THROWFROMFILE2( CND::IFASTDBRKR_CONDITION, CLASSNAME, GET_COMPANY_INFO, CND::IFASTDBRKR_NOT_LOGGED_ON );

   strAccessAllSlsRep = NULL_STRING;

   DString numberOfCompanies = _signonData->getElementValue( ifds::RepeatCount );
   int cCompanies = numberOfCompanies.asInteger();
   int companyIndex = 0;

   while( companyIndex < cCompanies )
   {
      const BFData& companyData = _signonData->getRepeat( companyIndex );
      DString companyId = companyData.getElementValue( ifds::CompanyId ).strip();
      if( companyId == strCompanyId )
      {
         strAccessAllSlsRep = companyData.getElementValue( ifds::AccessAllSlsRep ).strip();
         break;
      }
      companyIndex++;
   }
}

//******************************************************************************
bool DSTCSecurity::isFFID() const
{
   if( !_loggedOn  || !_signonData )
      THROWFROMFILE2( CND::IFASTDBRKR_CONDITION, CLASSNAME, GET_NUMBER_OF_COMPANIES, CND::IFASTDBRKR_NOT_LOGGED_ON );
   DString IdType = _signonData->getElementValue( ifds::IDAccess ).strip();
   return ( IdType.strip() == FFID_TYPE  || IdType.strip() == SSID_TYPE  || IdType.strip() == RRID_TYPE);
}


//******************************************************************************
DString DSTCSecurity::getVersionLabel() const
{
   if( !_loggedOn  || !_signonData )
      THROWFROMFILE2( CND::IFASTDBRKR_CONDITION, CLASSNAME, GET_USER_NAME, CND::IFASTDBRKR_NOT_LOGGED_ON );

   return(_signonData->getElementValue( ifds::VersionLabel ).strip());
}

//******************************************************************************
DString DSTCSecurity::getAccessID() const
{
   if( !_loggedOn  || !_signonData )
      THROWFROMFILE2( CND::IFASTDBRKR_CONDITION, CLASSNAME, GET_USER_NAME, CND::IFASTDBRKR_NOT_LOGGED_ON );

   return(_signonData->getElementValue( ifds::IDAccess ).strip());
}

const DStringA DSTCSecurity::getResponseValue(TiXmlDocument &doc, const DStringA &key)
{
    TiXmlNode* node = 0;
    node = doc.FirstChildElement();
    node = node->FirstChild(key.c_str());
    node = node->FirstChild();
    return node->Value();
}

const DStringA DSTCSecurity::getStatus(TiXmlDocument &doc)
{
    TiXmlNode* node = 0;
    node = doc.FirstChildElement();
    if (0 != node)
        node = node->FirstChild("RequestStatus");
    if (0 != node)
        node = node->FirstChild("status");
    if (0 != node)
        node=node->FirstChild();
    return  (node != 0) ? node->Value() : "";
}


const DStringA DSTCSecurity::getPackage(TiXmlDocument &doc)
{
    TiXmlNode* node = 0;
    node = doc.FirstChild( "AuthResponse" );
    node = node->FirstChild("Package");
    return (node == 0)? DStringA("") : node->FirstChild()->Value();
}

const DStringA DSTCSecurity::getToken(TiXmlDocument &doc, const DStringA& password)
{
	return decrypt(getPackage(doc), password);
}

const DString DSTCSecurity::createPassOneDoc(const DString& userID, const DString &userNS)
{
    return I_("<AuthUser><UserId>")+userID+I_("</UserId><UserNS>")
        + userNS + I_("</UserNS></AuthUser>");
}

const DString DSTCSecurity::createPassTwoDoc(const DString& userID, const DString &userNS, const DString &authToken)
{
    return I_("<AuthUser><UserId>")+userID+I_("</UserId><UserNS>")+
        userNS+I_("</UserNS><AuthToken>")+authToken+I_("</AuthToken></AuthUser>");
}

const DString DSTCSecurity::createLogoffDoc(const DString& userID, const DString &userNS, const DString &sessionToken)
{
    return I_("<AuthLogoff><UserId>")+userID+I_("</UserId><UserNS>")+
        userNS+I_("</UserNS><SessionToken>")+sessionToken+I_("</SessionToken></AuthLogoff>");
}

const DString DSTCSecurity::createChangePasswordDoc(const DString& userID, const DString &userNS, const DString &oldPassword, const DString &newPassword)
{
	const DStringA encrstr = encrypt(DStringA(newPassword),  DStringA(oldPassword) );

	return I_("<AuthChangePwd><UserId>")+userID+I_("</UserId><UserNS>")+
		userNS+I_("</UserNS><Package>")+DString(encrstr)+I_("</Package></AuthChangePwd>");
}

const DStringA &  DSTCSecurity::SMQSendReceive(BFRecordConnection *connection, const DStringA& request)
{
    connection->putRequest( "LDAP", request, TRUE, NULL );
    return connection->getResponse();
}

void DSTCSecurity::createView1Response(TiXmlDocument &doc)
{
   bf::log::LogStream ls( bf::log::databroker );
   ls << bf::log::information;
    _signonData = new BFData( ifds::DSTC0001_VW ); 
    _pwdDaysLeft = DString(getResponseValue(doc, "PwdDaysLeft"));
    _signonData->setElementValue (ifds::DaysPasswdChange, _pwdDaysLeft);
	_language = DString(getResponseValue(doc, "Language"));
    _signonData->setElementValue (ifds::LanguageCode, _language);

	DString userType = DString(getResponseValue(doc, "AccessType"));
	_signonData->setElementValue( ifds::IDAccess, userType );

    TiXmlNode* node = doc.FirstChild( "AuthResponse" );
    TiXmlNode* envnode = node->FirstChild("Environment");

	// do we have a list of allowable companies in our configuration?
	std::set<DString> setAllowed;
	DString strAllowed = GetConfigValueAsString(I_("Market"), I_("ValidCompanies"));
	if( strAllowed != I_("") ) {
		// strAllowed, if not blank, should contain a *SPACE* separated list of allowed company codes
		for(int i=0;i < strAllowed.words(); ++i) {
			DString company = strAllowed.word(i);
            setAllowed.insert(company);
		}
	}
    int cRepeatCount = 0;
    while(envnode != NULL){
        BFData *repeate = new BFData (ifds::DSTC0001_VWRepeat_Record);
        TiXmlNode* tmpnode = envnode->FirstChild("EnvId");
        tmpnode=tmpnode->FirstChild();
		DString candidateCompany = DString(DStringA(tmpnode->Value()));
		if( setAllowed.size() > 0 &&
			setAllowed.find(candidateCompany) == setAllowed.end() ) {
	        envnode = envnode->NextSibling("Environment");
			continue;
		}
	    ++cRepeatCount;
        repeate->setElementValue (ifds::CompanyId, candidateCompany);
        ls << I_("Added company ") << DString(DStringA(tmpnode->Value()));
//      repeate->setElementValue (ifds::ClientID, DString(DStringA(tmpnode->Value())));
      // temp hack to get around lack of ClientID
        repeate->setElementValue (ifds::ClientID, I_("gmx") );
        ls << I_(", clientID=gmx");

        tmpnode = envnode->FirstChild("EnvName");
        tmpnode=tmpnode->FirstChild();
        repeate->setElementValue (ifds::CompanyName, DString(DStringA(tmpnode->Value())));
        ls << I_(", name=") << DString(DStringA(tmpnode->Value()));
        ls << bf::log::endlf;
        _signonData->addRepeat(*repeate);
        envnode = envnode->NextSibling("Environment");
    }
   DString repeatCount;
   repeatCount.appendInt( cRepeatCount );
   ls << I_("RepeatCount=") << repeatCount << bf::log::endlf;
   _signonData->setElementValue( ifds::RepeatCount, repeatCount );
}



//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastdbrkr/DSTCSecurity.cpp-arc  $
 * 
 *    Rev 1.45   Dec 29 2011 16:51:00   if991250
 * using constants for languages
 * 
 *    Rev 1.44   Mar 15 2011 17:42:28   purdyech
 * RFC34278 - TA Exclusion List of Companies
 * 
 *    Rev 1.43   Feb 09 2011 14:17:54   jankovii
 * IN 2421716 - destkop password.
 * 
 *    Rev 1.42   Dec 17 2010 06:01:58   purdyech
 * Improved logging for SSBG Performance analysis
 * 
 *    Rev 1.41   Mar 05 2010 15:59:20   yingz
 * change def from R to RRID anf F to FFID to support rr, ff login
 * 
 *    Rev 1.40   Oct 21 2009 10:22:44   purdyech
 * LDAP Authorization Support
 * 
 *    Rev 1.39   Sep 02 2009 17:35:30   yingz
 * implement handling force password change
 * 
 *    Rev 1.38   Aug 25 2009 21:01:48   purdyech
 * Fixed leak of SonicConnection objects in LDAP logon/logoff/changePassword code.
 * 
 *    Rev 1.37   Aug 22 2009 16:07:40   yingz
 * using botan for ldap
 * 
 *    Rev 1.36   Aug 19 2009 13:45:40   yingz
 * fix an encryption issue
 * 
 *    Rev 1.35   Aug 16 2009 08:09:12   yingz
 * add error msg to change password
 * 
 *    Rev 1.34   Aug 14 2009 16:23:16   yingz
 * LDAP support
 * 
 *    Rev 1.33   Aug 04 2009 14:18:48   purdyech
 * Added some logging around ClientID setting
 * 
 *    Rev 1.32   Aug 03 2009 23:09:20   purdyech
 * LDAP Integration Pieces
 * 
 *    Rev 1.31   Aug 02 2009 22:26:18   yingz
 * LDAP change
 * 
 *    Rev 1.30   06 Dec 2007 15:20:04   popescu
 * Incident 1088629 - read the ACL set-up for the web pages URL instead of the using the xml configuration file.
 * 
 *    Rev 1.29   Aug 22 2005 10:50:52   ZHANGCEL
 * PET 1235 - FN02 -- Enhancement for Restricted Read Only Unserid 
 * 
 *    Rev 1.28   Feb 21 2005 15:29:28   Fengyong
 * 21193 - BPServer error: "User needs to log on first"
 * 
 *    Rev 1.27   Sep 03 2004 12:03:46   popescu
 * PET 991, FN02, added support for Dutch/Italian 
 * 
 *    Rev 1.26   Dec 11 2003 11:48:00   linmay
 * added isFFID( ) and GetVersionLabel( )
 * 
 *    Rev 1.25   Oct 03 2003 16:56:48   PURDYECH
 * Another spanish fix.
 * 
 *    Rev 1.24   Oct 02 2003 10:33:04   FENGYONG
 * Make spanish work
 * 
 *    Rev 1.23   Apr 10 2003 15:25:16   PURDYECH
 * Deal with German properly.
 * 
 *    Rev 1.22   Apr 02 2003 14:01:54   PURDYECH
 * Added support for Germany
 * 
 *    Rev 1.21   Oct 09 2002 23:55:24   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.20   Aug 29 2002 12:51:20   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.19   22 May 2002 18:12:58   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.18   Aug 16 2001 17:26:52   HUANGSHA
 * more fix for locale
 * 
 *    Rev 1.17   Aug 15 2001 17:39:28   HUANGSHA
 * blooded bug !!!
 * 
 *    Rev 1.16   14 Aug 2001 11:14:00   SMITHDAV
 * Added getClientId() funcrion.
 * 
 *    Rev 1.15   Aug 08 2001 18:30:46   FENGYONG
 * fix locale
 * 
 *    Rev 1.14   08 Aug 2001 10:56:50   SMITHDAV
 * Made extensive fixes to ClientLocale management.
 * 
 *    Rev 1.13   04 Aug 2001 11:32:04   KOVACSRO
 * Added getAllSlsRep().Probably it should be a param. in getCompanyInfo().
 * 
 *    Rev 1.12   03 May 2001 14:03:32   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.11   Jan 23 2001 15:19:14   YINGBAOL
 * add eTrack
 * 
 *    Rev 1.10   Jan 03 2001 11:54:20   YINGZ
 * add _passedinLanguageCode for api
 * 
 *    Rev 1.9   Dec 05 2000 17:18:04   DINACORN
 * Add "Revision Control Entries" at the end of file
 * 
 */
