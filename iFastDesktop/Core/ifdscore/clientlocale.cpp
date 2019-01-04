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

#define DICORE_DLL

#include "srcprag.h"
#include "clientlocale.hpp"
#include "CriticalSectionLock.hpp"
#include "Guard.hpp"

const AbstractClientLocaleLookup* ClientLocale::s_pLookup_ = NULL;

void ClientLocale::setLookup( const AbstractClientLocaleLookup* pLookup )
{
   s_pLookup_ = pLookup;
}

static DString getCurrentISOLocale();

static CriticalSectionLock lockInit;

ClientLocale * ClientLocale::s_pDefaultInfraClientLocale = 0;
SingletonRegister * ClientLocale::s_pDefaultsRegister = 0;

void ClientLocale::removeDefaults( void *pObj )
{
   delete s_pDefaultInfraClientLocale;
   delete s_pDefaultsRegister;

   s_pDefaultInfraClientLocale = 0;
   s_pDefaultsRegister = 0;
}


const ClientLocale& ClientLocale::getDefaultInfraClientLocale()
{
   if( s_pDefaultInfraClientLocale )
   {
      return(*s_pDefaultInfraClientLocale);
   }

   Guard crit( &lockInit );

   if( s_pDefaultInfraClientLocale )
   {
      return(*s_pDefaultInfraClientLocale);
   }

   s_pDefaultInfraClientLocale = new ClientLocale( I_( "enUS" ),
                                                   1,
                                                   1 );

   if( 0 == s_pDefaultsRegister )
   {
      s_pDefaultsRegister = new SingletonRegister( removeDefaults, NULL );
   }

   return(*s_pDefaultInfraClientLocale);
}


ClientLocale::ClientLocale()
: m_dstrLocale( getCurrentISOLocale() )
, m_ulMarket( -1 )
, m_ulClient( -1 )
{
   m_dstrMarket = I_( "No Market" );
   m_dstrClient = I_( "No Client" );
   setLCID();
}

ClientLocale::ClientLocale( const DString& dstrLocale,
                            unsigned long ulMarket,
                            unsigned long ulClient )
:m_dstrLocale( dstrLocale ),
m_ulClient( ulClient ),
m_ulMarket( ulMarket )
{
   if( NULL != s_pLookup_ )
   {
      m_dstrMarket = s_pLookup_->getMarketName( m_ulMarket );
      m_dstrClient = s_pLookup_->getClientName( m_ulMarket, m_ulClient );
   }
   else
   {
      m_dstrMarket = I_( "No Market" );
      m_dstrClient = I_( "No Client" );
   }
   setLCID();
}

ClientLocale::ClientLocale( const DString& dstrLocale,
                            const DString& dstrMarket,
                            const DString& dstrClient )
:m_dstrLocale( dstrLocale ),
m_dstrMarket( dstrMarket ),
m_dstrClient( dstrClient )
{
   if( NULL != s_pLookup_ )
   {
      m_ulMarket = s_pLookup_->getMarketIndex( m_dstrMarket );
      m_ulClient = s_pLookup_->getClientIndex( m_ulMarket, m_dstrClient );
   }
   else
   {
      m_ulMarket = 1;
      m_ulClient = 1;
   }
   setLCID();
}


ClientLocale::ClientLocale( const ClientLocale& rhs )
: m_dstrLocale( rhs.m_dstrLocale )
, m_dstrMarket( rhs.m_dstrMarket )
, m_dstrClient( rhs.m_dstrClient )
, m_ulMarket( rhs.m_ulMarket )
, m_ulClient( rhs.m_ulClient )
, lcid_( rhs.lcid_ )
{
   m_dstrLocale.stripTrailing();
}

ClientLocale& ClientLocale::operator=( const ClientLocale& orig )
{
   if( this == &orig )
   {
      return(*this);
   }

   m_dstrLocale = orig.m_dstrLocale;
   m_dstrMarket = orig.m_dstrMarket;
   m_dstrClient = orig.m_dstrClient;
   m_ulMarket = orig.m_ulMarket;
   m_ulClient = orig.m_ulClient;
   lcid_ = orig.lcid_;

   return(*this);
}

bool ClientLocale::operator<(const ClientLocale& compare ) const
{
   if( m_ulMarket < compare.m_ulMarket )
   {
      return(true);
   }

   if( m_ulMarket > compare.m_ulMarket )
   {
      return(false);
   }

   if( m_ulClient < compare.m_ulClient )
   {
      return(true);
   }

   if( m_ulClient > compare.m_ulClient )
   {
      return(false);
   }

   if( m_dstrLocale < compare.m_dstrLocale )
   {
      return(true);
   }

   return(false);
}


bool ClientLocale::operator==( const ClientLocale& orig ) const
{
   if( m_dstrLocale == orig.m_dstrLocale &&
       m_ulMarket == orig.m_ulMarket &&
       m_ulClient == orig.m_ulClient )
   {
      return(true);
   }

   return(false);
}


void ClientLocale::setLocale( const DString& dstrLocale )
{
   m_dstrLocale = dstrLocale;
   setLCID();
}

void ClientLocale::setMarket( const DString& dstrMarket )
{
   m_dstrMarket = dstrMarket;
   m_ulClient   = 1;
   if( NULL != s_pLookup_ )
   {
      m_ulMarket = s_pLookup_->getMarketIndex( m_dstrMarket );
      m_dstrClient = s_pLookup_->getClientName( m_ulMarket, m_ulClient );
   }
   else
   {
      m_ulMarket = 1;
      m_dstrClient = I_( "No Client" );
   }
}

void ClientLocale::setClient( const DString& dstrClient )
{
   m_dstrClient = dstrClient;
   if( NULL != s_pLookup_ )
   {
      m_ulClient = s_pLookup_->getClientIndex( m_ulMarket, m_dstrClient );
   }
   else
   {
      m_ulClient = 1;
   }
}

void ClientLocale::setMarket( unsigned long ulMarket )
{
   m_ulMarket = ulMarket;
   m_ulClient = 1;
   if( NULL != s_pLookup_ )
   {
      m_dstrMarket = s_pLookup_->getMarketName( m_ulMarket );
      m_dstrClient = s_pLookup_->getClientName( m_ulMarket, m_ulClient );
   }
   else
   {
      m_dstrMarket = I_( "No Market" );
      m_dstrClient = I_( "No Client" );
   }

}

void ClientLocale::setClient( unsigned long ulClient )
{
   m_ulClient = ulClient;
   if( NULL != s_pLookup_ )
   {
      m_dstrClient = s_pLookup_->getClientName( m_ulMarket, m_ulClient );
   }
   else
   {
      m_dstrClient = I_( "No Client" );
   }
}


bool ClientLocale_multimap_compare::operator()
( const ClientLocale& lhs,
  const ClientLocale& rhs ) const
{  // Compare class which only compares locale without extensions
   if( lhs.getLocale() < rhs.getLocale() )
   {
      return(true);
   }

   return(false);
}


// Locale stuff

struct tagISO3166
{
   I_CHAR  szName[64];
   I_CHAR  szCode[3];
};

struct tagISO3166 aISO3166[] =
{
   I_( "AFGHANISTAN" ), I_( "AF" ),
   I_( "ALBANIA" ), I_( "AL" ),
   I_( "ALGERIA" ), I_( "DZ" ),
   I_( "AMERICAN SAMOA" ), I_( "AS" ),
   I_( "ANDORRA" ), I_( "AD" ),
   I_( "ANGOLA" ), I_( "AO" ),
   I_( "ANGUILLA" ), I_( "AI" ),
   I_( "ANTARCTICA" ), I_( "AQ" ),
   I_( "ANTIGUA AND BARBUDA" ), I_( "AG" ),
   I_( "ARGENTINA" ), I_( "AR" ),
   I_( "ARMENIA" ), I_( "AM" ),
   I_( "ARUBA" ), I_( "AW" ),
   I_( "AUSTRALIA" ), I_( "AU" ),
   I_( "AUSTRIA" ), I_( "AT" ),
   I_( "AZERBAIJAN" ), I_( "AZ" ),
   I_( "BAHAMAS" ), I_( "BS" ),
   I_( "BAHRAIN" ), I_( "BH" ),
   I_( "BANGLADESH" ), I_( "BD" ),
   I_( "BARBADOS" ), I_( "BB" ),
   I_( "BELARUS" ), I_( "BY" ),
   I_( "BELGIUM" ), I_( "BE" ),
   I_( "BELIZE" ), I_( "BZ" ),
   I_( "BENIN" ), I_( "BJ" ),
   I_( "BERMUDA" ), I_( "BM" ),
   I_( "BHUTAN" ), I_( "BT" ),
   I_( "BOLIVIA" ), I_( "BO" ),
   I_( "BOSNIA AND HERZEGOVINA" ), I_( "BA" ),
   I_( "BOTSWANA" ), I_( "BW" ),
   I_( "BOUVET ISLAND" ), I_( "BV" ),
   I_( "BRAZIL" ), I_( "BR" ),
   I_( "BRITISH INDIAN OCEAN TERRITORY" ), I_( "IO" ),
   I_( "BRUNEI DARUSSALAM" ), I_( "BN" ),
   I_( "BULGARIA" ), I_( "BG" ),
   I_( "BURKINA FASO" ), I_( "BF" ),
   I_( "BURUNDI" ), I_( "BI" ),
   I_( "CAMBODIA" ), I_( "KH" ),
   I_( "CAMEROON" ), I_( "CM" ),
   I_( "CANADA" ), I_( "CA" ),
   I_( "CAPE VERDE" ), I_( "CV" ),
   I_( "CAYMAN ISLANDS" ), I_( "KY" ),
   I_( "CENTRAL AFRICAN REPUBLIC" ), I_( "CF" ),
   I_( "CHAD" ), I_( "TD" ),
   I_( "CHILE" ), I_( "CL" ),
   I_( "CHINA" ), I_( "CN" ),
   I_( "CHRISTMAS ISLAND" ), I_( "CX" ),
   I_( "COCOS (KEELING) ISLANDS" ), I_( "CC" ),
   I_( "COLOMBIA" ), I_( "CO" ),
   I_( "COMOROS" ), I_( "KM" ),
   I_( "CONGO" ), I_( "CG" ),
   I_( "CONGO, THE DEMOCRATIC REPUBLIC OF THE" ), I_( "CD" ),
   I_( "COOK ISLANDS" ), I_( "CK" ),
   I_( "COSTA RICA" ), I_( "CR" ),
   I_( "CÔTE D'IVOIRE" ), I_( "CI" ),
   I_( "CROATIA" ), I_( "HR" ),
   I_( "CUBA" ), I_( "CU" ),
   I_( "CYPRUS" ), I_( "CY" ),
   I_( "CZECH REPUBLIC" ), I_( "CZ" ),
   I_( "DENMARK" ), I_( "DK" ),
   I_( "DJIBOUTI" ), I_( "DJ" ),
   I_( "DOMINICA" ), I_( "DM" ),
   I_( "DOMINICAN REPUBLIC" ), I_( "DO" ),
   I_( "EAST TIMOR" ), I_( "TP" ),
   I_( "ECUADOR" ), I_( "EC" ),
   I_( "EGYPT" ), I_( "EG" ),
   I_( "EL SALVADOR" ), I_( "SV" ),
   I_( "EQUATORIAL GUINEA" ), I_( "GQ" ),
   I_( "ERITREA" ), I_( "ER" ),
   I_( "ESTONIA" ), I_( "EE" ),
   I_( "ETHIOPIA" ), I_( "ET" ),
   I_( "FALKLAND ISLANDS (MALVINAS)" ), I_( "FK" ),
   I_( "FAROE ISLANDS" ), I_( "FO" ),
   I_( "FIJI" ), I_( "FJ" ),
   I_( "FINLAND" ), I_( "FI" ),
   I_( "FRANCE" ), I_( "FR" ),
   I_( "FRENCH GUIANA" ), I_( "GF" ),
   I_( "FRENCH POLYNESIA" ), I_( "PF" ),
   I_( "FRENCH SOUTHERN TERRITORIES" ), I_( "TF" ),
   I_( "GABON" ), I_( "GA" ),
   I_( "GAMBIA" ), I_( "GM" ),
   I_( "GEORGIA" ), I_( "GE" ),
   I_( "GERMANY" ), I_( "DE" ),
   I_( "GHANA" ), I_( "GH" ),
   I_( "GIBRALTAR" ), I_( "GI" ),
   I_( "GREECE" ), I_( "GR" ),
   I_( "GREENLAND" ), I_( "GL" ),
   I_( "GRENADA" ), I_( "GD" ),
   I_( "GUADELOUPE" ), I_( "GP" ),
   I_( "GUAM" ), I_( "GU" ),
   I_( "GUATEMALA" ), I_( "GT" ),
   I_( "GUINEA" ), I_( "GN" ),
   I_( "GUINEA-BISSAU" ), I_( "GW" ),
   I_( "GUYANA" ), I_( "GY" ),
   I_( "HAITI" ), I_( "HT" ),
   I_( "HEARD ISLAND AND MCDONALD ISLANDS" ), I_( "HM" ),
   I_( "HOLY SEE (VATICAN CITY STATE)" ), I_( "VA" ),
   I_( "HONDURAS" ), I_( "HN" ),
   I_( "HONG KONG" ), I_( "HK" ),
   I_( "HUNGARY" ), I_( "HU" ),
   I_( "ICELAND" ), I_( "IS" ),
   I_( "INDIA" ), I_( "IN" ),
   I_( "INDONESIA" ), I_( "ID" ),
   I_( "IRAN, ISLAMIC REPUBLIC OF" ), I_( "IR" ),
   I_( "IRAQ" ), I_( "IQ" ),
   I_( "IRELAND" ), I_( "IE" ),
   I_( "ISRAEL" ), I_( "IL" ),
   I_( "ITALY" ), I_( "IT" ),
   I_( "JAMAICA" ), I_( "JM" ),
   I_( "JAPAN" ), I_( "JP" ),
   I_( "JORDAN" ), I_( "JO" ),
   I_( "KAZAKSTAN" ), I_( "KZ" ),
   I_( "KENYA" ), I_( "KE" ),
   I_( "KIRIBATI" ), I_( "KI" ),
   I_( "KOREA, DEMOCRATIC PEOPLE'S REPUBLIC OF" ), I_( "KP" ),
   I_( "KOREA, REPUBLIC OF" ), I_( "KR" ),
   I_( "KUWAIT" ), I_( "KW" ),
   I_( "KYRGYZSTAN" ), I_( "KG" ),
   I_( "LAO PEOPLE'S DEMOCRATIC REPUBLIC" ), I_( "LA" ),
   I_( "LATVIA" ), I_( "LV" ),
   I_( "LEBANON" ), I_( "LB" ),
   I_( "LESOTHO" ), I_( "LS" ),
   I_( "LIBERIA" ), I_( "LR" ),
   I_( "LIBYAN ARAB JAMAHIRIYA" ), I_( "LY" ),
   I_( "LIECHTENSTEIN" ), I_( "LI" ),
   I_( "LITHUANIA" ), I_( "LT" ),
   I_( "LUXEMBOURG" ), I_( "LU" ),
   I_( "MACAU" ), I_( "MO" ),
   I_( "MACEDONIA, THE FORMER YUGOSLAV REPUBLIC OF" ), I_( "MK" ),
   I_( "MADAGASCAR" ), I_( "MG" ),
   I_( "MALAWI" ), I_( "MW" ),
   I_( "MALAYSIA" ), I_( "MY" ),
   I_( "MALDIVES" ), I_( "MV" ),
   I_( "MALI" ), I_( "ML" ),
   I_( "MALTA" ), I_( "MT" ),
   I_( "MARSHALL ISLANDS" ), I_( "MH" ),
   I_( "MARTINIQUE" ), I_( "MQ" ),
   I_( "MAURITANIA" ), I_( "MR" ),
   I_( "MAURITIUS" ), I_( "MU" ),
   I_( "MAYOTTE" ), I_( "YT" ),
   I_( "MEXICO" ), I_( "MX" ),
   I_( "MICRONESIA, FEDERATED STATES OF" ), I_( "FM" ),
   I_( "MOLDOVA, REPUBLIC OF" ), I_( "MD" ),
   I_( "MONACO" ), I_( "MC" ),
   I_( "MONGOLIA" ), I_( "MN" ),
   I_( "MONTSERRAT" ), I_( "MS" ),
   I_( "MOROCCO" ), I_( "MA" ),
   I_( "MOZAMBIQUE" ), I_( "MZ" ),
   I_( "MYANMAR" ), I_( "MM" ),
   I_( "NAMIBIA" ), I_( "NA" ),
   I_( "NAURU" ), I_( "NR" ),
   I_( "NEPAL" ), I_( "NP" ),
   I_( "NETHERLANDS" ), I_( "NL" ),
   I_( "NETHERLANDS ANTILLES" ), I_( "AN" ),
   I_( "NEW CALEDONIA" ), I_( "NC" ),
   I_( "NEW ZEALAND" ), I_( "NZ" ),
   I_( "NICARAGUA" ), I_( "NI" ),
   I_( "NIGER" ), I_( "NE" ),
   I_( "NIGERIA" ), I_( "NG" ),
   I_( "NIUE" ), I_( "NU" ),
   I_( "NORFOLK ISLAND" ), I_( "NF" ),
   I_( "NORTHERN MARIANA ISLANDS" ), I_( "MP" ),
   I_( "NORWAY" ), I_( "NO" ),
   I_( "OMAN" ), I_( "OM" ),
   I_( "PAKISTAN" ), I_( "PK" ),
   I_( "PALAU" ), I_( "PW" ),
   I_( "PALESTINIAN TERRITORY, OCCUPIED" ), I_( "PS" ),
   I_( "PANAMA" ), I_( "PA" ),
   I_( "PAPUA NEW GUINEA" ), I_( "PG" ),
   I_( "PARAGUAY" ), I_( "PY" ),
   I_( "PERU" ), I_( "PE" ),
   I_( "PHILIPPINES" ), I_( "PH" ),
   I_( "PITCAIRN" ), I_( "PN" ),
   I_( "POLAND" ), I_( "PL" ),
   I_( "PORTUGAL" ), I_( "PT" ),
   I_( "PUERTO RICO" ), I_( "PR" ),
   I_( "QATAR" ), I_( "QA" ),
   I_( "RÉUNION" ), I_( "RE" ),
   I_( "ROMANIA" ), I_( "RO" ),
   I_( "RUSSIAN FEDERATION" ), I_( "RU" ),
   I_( "RWANDA" ), I_( "RW" ),
   I_( "SAINT HELENA" ), I_( "SH" ),
   I_( "SAINT KITTS AND NEVIS" ), I_( "KN" ),
   I_( "SAINT LUCIA" ), I_( "LC" ),
   I_( "SAINT PIERRE AND MIQUELON" ), I_( "PM" ),
   I_( "SAINT VINCENT AND THE GRENADINES" ), I_( "VC" ),
   I_( "SAMOA" ), I_( "WS" ),
   I_( "SAN MARINO" ), I_( "SM" ),
   I_( "SAO TOME AND PRINCIPE" ), I_( "ST" ),
   I_( "SAUDI ARABIA" ), I_( "SA" ),
   I_( "SENEGAL" ), I_( "SN" ),
   I_( "SEYCHELLES" ), I_( "SC" ),
   I_( "SIERRA LEONE" ), I_( "SL" ),
   I_( "SINGAPORE" ), I_( "SG" ),
   I_( "SLOVAKIA" ), I_( "SK" ),
   I_( "SLOVENIA" ), I_( "SI" ),
   I_( "SOLOMON ISLANDS" ), I_( "SB" ),
   I_( "SOMALIA" ), I_( "SO" ),
   I_( "SOUTH AFRICA" ), I_( "ZA" ),
   I_( "SOUTH GEORGIA AND THE SOUTH SANDWICH ISLANDS" ), I_( "GS" ),
   I_( "SPAIN" ), I_( "ES" ),
   I_( "SRI LANKA" ), I_( "LK" ),
   I_( "SUDAN" ), I_( "SD" ),
   I_( "SURINAME" ), I_( "SR" ),
   I_( "SVALBARD AND JAN MAYEN" ), I_( "SJ" ),
   I_( "SWAZILAND" ), I_( "SZ" ),
   I_( "SWEDEN" ), I_( "SE" ),
   I_( "SWITZERLAND" ), I_( "CH" ),
   I_( "SYRIAN ARAB REPUBLIC" ), I_( "SY" ),
   I_( "TAIWAN, PROVINCE OF CHINA" ), I_( "TW" ),
   I_( "TAJIKISTAN" ), I_( "TJ" ),
   I_( "TANZANIA, UNITED REPUBLIC OF" ), I_( "TZ" ),
   I_( "THAILAND" ), I_( "TH" ),
   I_( "TOGO" ), I_( "TG" ),
   I_( "TOKELAU" ), I_( "TK" ),
   I_( "TONGA" ), I_( "TO" ),
   I_( "TRINIDAD AND TOBAGO" ), I_( "TT" ),
   I_( "TUNISIA" ), I_( "TN" ),
   I_( "TURKEY" ), I_( "TR" ),
   I_( "TURKMENISTAN" ), I_( "TM" ),
   I_( "TURKS AND CAICOS ISLANDS" ), I_( "TC" ),
   I_( "TUVALU" ), I_( "TV" ),
   I_( "UGANDA" ), I_( "UG" ),
   I_( "UKRAINE" ), I_( "UA" ),
   I_( "UNITED ARAB EMIRATES" ), I_( "AE" ),
   I_( "UNITED KINGDOM" ), I_( "US" ),
   I_( "UNITED STATES" ), I_( "US" ),
   I_( "UNITED STATES MINOR OUTLYING ISLANDS" ), I_( "UM" ),
   I_( "URUGUAY" ), I_( "UY" ),
   I_( "UZBEKISTAN" ), I_( "UZ" ),
   I_( "VANUATU" ), I_( "VU" ),
   I_( "VENEZUELA" ), I_( "VE" ),
   I_( "VIET NAM" ), I_( "VN" ),
   I_( "VIRGIN ISLANDS, BRITISH" ), I_( "VG" ),
   I_( "VIRGIN ISLANDS, U.S." ), I_( "VI" ),
   I_( "WALLIS AND FUTUNA" ), I_( "WF" ),
   I_( "WESTERN SAHARA" ), I_( "EH" ),
   I_( "YEMEN" ), I_( "YE" ),
   I_( "YUGOSLAVIA" ), I_( "YU" ),
   I_( "ZAMBIA" ), I_( "ZM" ),
   I_( "ZIMBABWE" ), I_( "ZW" )
};

struct tagISO639
{
   I_CHAR szName[ 64 ];
   I_CHAR szCode[ 3 ];
};
struct tagISO639 aISO639[] =
{
   I_( "Abkhazian" ), I_( "ab" ),
   I_( "Afan" ), I_( "om" ),
   I_( "Afar" ), I_( "aa" ),
   I_( "Afrikaans" ), I_( "af" ),
   I_( "Albanian" ), I_( "sq" ),
   I_( "Amharic" ), I_( "am" ),
   I_( "Arabic" ), I_( "ar" ),
   I_( "Armenian" ), I_( "hy" ),
   I_( "Assamese" ), I_( "as" ),
   I_( "Aymara" ), I_( "ay" ),
   I_( "Azerbaijani" ), I_( "az" ),
   I_( "Bashkir" ), I_( "ba" ),
   I_( "Basque" ), I_( "eu" ),
   I_( "Bengali" ), I_( "bn" ),
   I_( "Bhutani" ), I_( "dz" ),
   I_( "Bihari" ), I_( "bh" ),
   I_( "Bislama" ), I_( "bi" ),
   I_( "Breton" ), I_( "br" ),
   I_( "Bulgarian" ), I_( "bg" ),
   I_( "Burmese" ), I_( "my" ),
   I_( "Byelorussian" ), I_( "be" ),
   I_( "Cambodian" ), I_( "km" ),
   I_( "Catalan" ), I_( "ca" ),
   I_( "Chinese" ), I_( "zh" ),
   I_( "Corsican" ), I_( "co" ),
   I_( "Croatian" ), I_( "hr" ),
   I_( "Czech" ), I_( "cs" ),
   I_( "Danish" ), I_( "da" ),
   I_( "Dutch" ), I_( "nl" ),
   I_( "English" ), I_( "en" ),
   I_( "Esperanto" ), I_( "eo" ),
   I_( "Estonian" ), I_( "et" ),
   I_( "Faroese" ), I_( "fo" ),
   I_( "Fiji" ), I_( "fj" ),
   I_( "Finnish" ), I_( "fi" ),
   I_( "French" ), I_( "fr" ),
   I_( "Frisian" ), I_( "fy" ),
   I_( "Galician" ), I_( "gl" ),
   I_( "Georgian" ), I_( "ka" ),
   I_( "German" ), I_( "de" ),
   I_( "Greek" ), I_( "el" ),
   I_( "Greenlandic" ), I_( "kl" ),
   I_( "Guarani" ), I_( "gn" ),
   I_( "Gujarati" ), I_( "gu" ),
   I_( "Hausa" ), I_( "ha" ),
   I_( "Hebrew" ), I_( "he" ),
   I_( "Hindi" ), I_( "hi" ),
   I_( "Hungarian" ), I_( "hu" ),
   I_( "Icelandic" ), I_( "is" ),
   I_( "Indonesian" ), I_( "id" ),
   I_( "Interlingua" ), I_( "ia" ),
   I_( "Interlingue" ), I_( "ie" ),
   I_( "Inuktitut" ), I_( "iu" ),
   I_( "Inupiak" ), I_( "ik" ),
   I_( "Irish" ), I_( "ga" ),
   I_( "Italian" ), I_( "it" ),
   I_( "Japanese" ), I_( "ja" ),
   I_( "Javanese" ), I_( "jv" ),
   I_( "Kannada" ), I_( "kn" ),
   I_( "Kashmiri" ), I_( "ks" ),
   I_( "Kazakh" ), I_( "kk" ),
   I_( "Kinyarwanda" ), I_( "rw" ),
   I_( "Kirghiz" ), I_( "ky" ),
   I_( "Korean" ), I_( "ko" ),
   I_( "Kurdish" ), I_( "ku" ),
   I_( "Kurundi" ), I_( "rn" ),
   I_( "Laothian" ), I_( "lo" ),
   I_( "Latin" ), I_( "la" ),
   I_( "Latvian" ), I_( "lv" ),
   I_( "Lingala" ), I_( "ln" ),
   I_( "Lithuanian" ), I_( "lt" ),
   I_( "Macedonian" ), I_( "mk" ),
   I_( "Malagasy" ), I_( "mg" ),
   I_( "Malay" ), I_( "ms" ),
   I_( "Malayalam" ), I_( "ml" ),
   I_( "Maltese" ), I_( "mt" ),
   I_( "Maori" ), I_( "mi" ),
   I_( "Marathi" ), I_( "mr" ),
   I_( "Moldavian" ), I_( "mo" ),
   I_( "Mongolian" ), I_( "mn" ),
   I_( "Nauru" ), I_( "na" ),
   I_( "Nepali" ), I_( "ne" ),
   I_( "Norwegian" ), I_( "no" ),
   I_( "Occitan" ), I_( "oc" ),
   I_( "Oriya" ), I_( "or" ),
   I_( "Pashto" ), I_( "ps" ),
   I_( "Persian" ), I_( "fa" ),
   I_( "Polish" ), I_( "pl" ),
   I_( "Portuguese" ), I_( "pt" ),
   I_( "Punjabi" ), I_( "pa" ),
   I_( "Quechua" ), I_( "qu" ),
   I_( "Rhaeto-Romance" ), I_( "rm" ),
   I_( "Romanian" ), I_( "ro" ),
   I_( "Russian" ), I_( "ru" ),
   I_( "Samoan" ), I_( "sm" ),
   I_( "Sangho" ), I_( "sg" ),
   I_( "Sanskrit" ), I_( "sa" ),
   I_( "Scots Gaelic" ), I_( "gd" ),
   I_( "Serbian" ), I_( "sr" ),
   I_( "Serbo-Croatian" ), I_( "sh" ),
   I_( "Sesotho" ), I_( "st" ),
   I_( "Setswana" ), I_( "tn" ),
   I_( "Shona" ), I_( "sn" ),
   I_( "Sindhi" ), I_( "sd" ),
   I_( "Singhalese" ), I_( "si" ),
   I_( "Siswati" ), I_( "ss" ),
   I_( "Slovak" ), I_( "sk" ),
   I_( "Slovenian" ), I_( "sl" ),
   I_( "Somali" ), I_( "so" ),
   I_( "Spanish" ), I_( "es" ),
   I_( "Sundanese" ), I_( "su" ),
   I_( "Swahili" ), I_( "sw" ),
   I_( "Swedish" ), I_( "sv" ),
   I_( "Tagalog" ), I_( "tl" ),
   I_( "Tajik" ), I_( "tg" ),
   I_( "Tamil" ), I_( "ta" ),
   I_( "Tatar" ), I_( "tt" ),
   I_( "Telugu" ), I_( "te" ),
   I_( "Thai" ), I_( "th" ),
   I_( "Tibetan" ), I_( "bo" ),
   I_( "Tigrinya" ), I_( "ti" ),
   I_( "Tonga" ), I_( "to" ),
   I_( "Tsonga" ), I_( "ts" ),
   I_( "Turkish" ), I_( "tr" ),
   I_( "Turkmen" ), I_( "tk" ),
   I_( "Twi" ), I_( "tw" ),
   I_( "Uigur" ), I_( "ug" ),
   I_( "Ukrainian" ), I_( "uk" ),
   I_( "Urdu" ), I_( "ur" ),
   I_( "Uzbek" ), I_( "uz" ),
   I_( "Vietnamese" ), I_( "vi" ),
   I_( "Volapuk" ), I_( "vo" ),
   I_( "Welsh" ), I_( "cy" ),
   I_( "Wolof" ), I_( "wo" ),
   I_( "Xhosa" ), I_( "xh" ),
   I_( "Yiddish" ), I_( "yi" ),
   I_( "Yoruba" ), I_( "yo" ),
   I_( "Zhuang" ), I_( "za" ),
   I_( "Zulu" ), I_( "zu" )
};

static DString getCurrentISOLocale()
{
   DString isoLocale;
   I_CHAR szLanguage[ 64 ];
   I_CHAR szCountry[ 64 ];
   ::GetLocaleInfoW( LOCALE_USER_DEFAULT, LOCALE_SENGLANGUAGE, szLanguage, sizeof( szLanguage ) / sizeof( szLanguage[ 0 ] ) );
   ::GetLocaleInfoW( LOCALE_USER_DEFAULT, LOCALE_SENGCOUNTRY, szCountry, sizeof( szCountry ) / sizeof( szCountry[0] ) );

   int cISO639 = sizeof( aISO639 ) / sizeof( aISO639[0] );
   int iISO639;
   for( iISO639 = 0; iISO639 < cISO639; ++iISO639 )
   {
      if( i_stricmp( szLanguage, aISO639[ iISO639 ].szName ) == 0 )
      {
         isoLocale = aISO639[ iISO639 ].szCode;
         break;
      }
   }

   int cISO3166 = sizeof( aISO3166 ) / sizeof( aISO3166[0] );
   int iISO3166;
   for( iISO3166 = 0; iISO3166 < cISO3166; ++iISO3166 )
   {
      if( i_stricmp( szCountry, aISO3166[ iISO3166 ].szName ) == 0 )
      {
         isoLocale += aISO3166[ iISO3166 ].szCode;
         break;
      }
   }
   return( isoLocale );
}

struct tagLCID_To_Locale
{
   LCID  lcid;
   I_CHAR szLocale[ 5 ];
};
struct tagLCID_To_Locale aLCIDToLocale[] = 
{
   MAKELCID( MAKELANGID( LANG_ENGLISH, SUBLANG_ENGLISH_US ), SORT_DEFAULT ), I_( "enUS" ),
   MAKELCID( MAKELANGID( LANG_JAPANESE, SUBLANG_NEUTRAL ), SORT_JAPANESE_UNICODE ), I_( "jaJP" ),
   MAKELCID( MAKELANGID( LANG_ENGLISH, SUBLANG_ENGLISH_CAN ), SORT_DEFAULT ), I_( "enCA" ),
   MAKELCID( MAKELANGID( LANG_FRENCH, SUBLANG_FRENCH ), SORT_DEFAULT ), I_( "frFR" ),
   MAKELCID( MAKELANGID( LANG_FRENCH, SUBLANG_FRENCH_CANADIAN ), SORT_DEFAULT ), I_( "frCA" ),
   MAKELCID( MAKELANGID( LANG_ENGLISH, SUBLANG_ENGLISH_EIRE ), SORT_DEFAULT ), I_( "enIE" ),
   MAKELCID( MAKELANGID( LANG_ENGLISH, SUBLANG_ENGLISH_UK ), SORT_DEFAULT ), I_( "enGB" ),
   MAKELCID( MAKELANGID( LANG_GERMAN, SUBLANG_GERMAN ), SORT_DEFAULT ), I_( "deDE" ),
   MAKELCID( MAKELANGID( LANG_SPANISH, SUBLANG_SPANISH_MODERN ), SORT_DEFAULT ), I_( "esES" ),  // modern sort
   MAKELCID( MAKELANGID( LANG_SPANISH, SUBLANG_SPANISH ), SORT_DEFAULT ), I_( "esES" ),         // traditional ('castillian') sort
   MAKELCID( MAKELANGID( LANG_DUTCH, SUBLANG_DUTCH ), SORT_DEFAULT ), I_( "nlNL" ),
   MAKELCID( MAKELANGID( LANG_ITALIAN, SUBLANG_ITALIAN ), SORT_DEFAULT ), I_( "itIT" ),
};

LCID ClientLocale::getLCID() const
{
   // temp fix ... we are making enGB turn into enUS for the purposes of the DataDictionary and
   // the Conditions.  However, we still want to return the appropriate enGB LCID value here
   return(lcid_);
}

void ClientLocale::setLCID()
{
   if( m_dstrLocale == I_( "enUS" ) )
   {
      I_CHAR szCountry[ 64 ];
      ::GetLocaleInfoW( LOCALE_USER_DEFAULT, LOCALE_SENGCOUNTRY, szCountry, sizeof( szCountry ) / sizeof( szCountry[0] ) );
      if( szCountry == I_( "UNITED KINGDOM" ) )
      {
         lcid_ = MAKELCID( MAKELANGID( LANG_ENGLISH, SUBLANG_ENGLISH_UK ), SORT_DEFAULT );
         return;
      }
   }

   for( int iLCID = 0; iLCID < ( sizeof( aLCIDToLocale ) / sizeof( aLCIDToLocale[0] ) ); ++iLCID )
   {
      if( m_dstrLocale == aLCIDToLocale[ iLCID ].szLocale )
      {
         lcid_ = aLCIDToLocale[ iLCID ].lcid;
         return;
      }
   }
   lcid_ = MAKELCID( LANG_NEUTRAL, SORT_DEFAULT );
}

/*******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF Core/ifdscore/clientlocale.cpp-arc  $
//
//   Rev 1.8   Aug 30 2004 16:01:08   popescu
//PET 991, FN 02, added support for Dutch and Italian
//
//   Rev 1.7   Aug 14 2003 15:34:18   PURDYECH
//Added support for Castillian Spanish
//
//   Rev 1.6   Aug 12 2003 10:05:54   PURDYECH
//Added Spanish as a valid language.
// 
//    Rev 1.5   Apr 11 2003 17:55:20   PURDYECH
// Added German to  LCID conversion array.
// 
//    Rev 1.4   Oct 09 2002 17:41:44   PURDYECH
// New PVCS Database
// 
//    Rev 1.3   Sep 10 2002 16:20:34   PURDYECH
// ClientLocale aliasing for UK ----> US
// 
//    Rev 1.2   Sep 09 2002 13:36:44   PURDYECH
// Fixed memory overwrite when setting ThreadLocale.
// 
//    Rev 1.1   Sep 02 2002 17:35:16   PURDYECH
// Fixed up ClientLocale stuff for ClientLocaleContext::get()
// 
//    Rev 1.0   Jul 05 2002 10:12:44   SMITHDAV
// Initial revision.
//
//   Rev 1.9   May 18 2001 14:54:18   dt24433
//Switched to Guard\CriticalSectionLock from CriticalSection\MutexSemaphore.
//
//   Rev 1.8   Mar 24 2001 13:51:24   dt24433
//Added method to support compare of locale only for multimaps.  Market and client are not compared.
//
//   Rev 1.7   Feb 21 2001 16:26:10   DT21858
// - Added SingletonRegister
// - Did some cleanup
//
//   Rev 1.6   Sep 05 2000 06:19:02   dt17817
//- Remove Certificate/Authenticator
//- Fix threadsafety of client/market
//- Add "null" property value support
//
//
//   Rev 1.5   Aug 24 2000 07:28:18   dtwk
//Add in more support for clients and markets
//
//   Rev 1.4   Aug 09 2000 08:32:12   dtwk
//Add in support for indexes for markets and clients
//
//   Rev 1.3   Jun 14 2000 12:33:56   dtwk
//Add setter method for default ClientLocale
//
//   Rev 1.2   May 30 2000 14:53:12   dtwk
//Static globals will be created only on demand to work around application startup errors
//
//   Rev 1.1   May 30 2000 09:10:08   dtwk
//Add copy constructor, operator=, operator==
//Add static global instance that is for Infra defaults
//
//   Rev 1.0   May 26 2000 18:01:30   dtwk
//
//
//
*/


