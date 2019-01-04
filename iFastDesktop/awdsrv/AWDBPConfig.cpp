//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2005 by International Financial Data Services
//
//
//******************************************************************************
//******************************************************************************
//
// ^FILE   : AWDBPConfig.cpp
// ^AUTHOR : Yingbao Li
// ^DATE   : Oct. 18, 2005
//
// ^CLASS    : AWDBPConfig
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include <vector>
#include "AWDBPConfig.hpp"
#include <assert.h>
#include "StringHelp.hpp"

namespace
{
   // Trace literals
   const char * const CLASSNAME       = "AWDBPConfig" ;
//section name 
   const char * const UserInfo             = "User Info" ;
   const char * const Company              = "MGMCO" ;
   const char * const AwdFields            = "AWD Fields" ;
   const char * const userID               = "UserId";
   const char * const password             = "Password";
   const char * const language             = "Language";
   const char * const logoff               = "LogOff";
   const char * const portNum              = "PortNum";
   const char * const ipAddress            = "IpAddress";
   const char * const fundGroup            = "FundGroup";
   const char * const accountNum           = "AccountNum";
   const char * const logDirectory         = "LogDirectory";
   const char * const AWD_KEFILE         = "\\AWDKeIntergration.ini";


 }
//*******************************************************************************

AWDBPConfig::AWDBPConfig( )
{
   //TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
 
	
}
//*******************************************************************************
AWDBPConfig::~AWDBPConfig()
{
   deregistSection();
}
//*************************************************************************************************
std::string AWDBPConfig::getUserID()
{
   std::string strID;
   SectionData* pSecData = getSectionData( UserInfo ); 
   if( pSecData )
   {
      strID = pSecData->getValueByKey( userID );
   }
   return strID;
}
//**************************************************************************************************
std::string AWDBPConfig::getPassword()
{
   std::string strPsw = "";
   SectionData* pSecData = getSectionData( UserInfo ); 
   if( pSecData )
   {
      strPsw = pSecData->getValueByKey( password );
   }
   return strPsw;
}
//**************************************************************************************************
std::string AWDBPConfig::getLanguage()
{
   std::string strLang = "";
   SectionData* pSecData = getSectionData( UserInfo ); 
   if( pSecData )
   {
      strLang = pSecData->getValueByKey( language );
   }
   return strLang;
}
//**************************************************************************************************
std::string AWDBPConfig::getLogOff()
{
   std::string strLog = "";
   SectionData* pSecData = getSectionData( UserInfo ); 
   if( pSecData )
   {
      strLog = pSecData->getValueByKey( logoff );
   }
   return strLog;
}
//*************************************************************************************************
std::string AWDBPConfig::getPortNum()
{
   std::string strPort = "";
   SectionData* pSecData = getSectionData( UserInfo ); 
   if( pSecData )
   {
      strPort = pSecData->getValueByKey( portNum );
   }
   return strPort;
}
//***********************************************************************************************
std::string AWDBPConfig::getFundGroup()
{
   std::string strgroup = "";
   SectionData* pSecData = getSectionData( UserInfo ); 
   if( pSecData )
   {
      strgroup = pSecData->getValueByKey( fundGroup );
   }
   return strgroup;
}
//***********************************************************************************************
std::string AWDBPConfig::getAccountName()
{
   std::string strAcctName = "";
   SectionData* pSecData = getSectionData( UserInfo ); 
   if( pSecData )
   {
      strAcctName = pSecData->getValueByKey( accountNum );
   }
   return strAcctName;
}


//***********************************************************************************************
std::string AWDBPConfig::getIPAddress()
{
   std::string address = "";
   SectionData* pSecData = getSectionData( UserInfo ); 
   if( pSecData ) 
   {
      address = pSecData->getValueByKey( ipAddress );
   }
   return address;
}
//********************************************************************************

std::string AWDBPConfig::getLogDirectory()
{
   std::string direct = "";
   SectionData* pSecData = getSectionData( UserInfo ); 
   if( pSecData ) 
   {
      direct = pSecData->getValueByKey( logDirectory );
   }
   return direct;
}




//***********************************************************************************************
std::string AWDBPConfig::getFieldValueInSection( const std::string& section,const std::string& key)
{
   std::string fieldValue = "";
   SectionData* pSecData = getSectionData( section ); 
   if( pSecData )
   {
      fieldValue = pSecData->getValueByKey( key );
   }
   return fieldValue;
}
//**************************************************************************************************
std::string AWDBPConfig::getCompanyIdByLobData(const std::string& lobCmpId  )
{
   std::string cmpID = "";
   SectionData* pSecData = getSectionData( Company ); 
   if( pSecData )
   {
      cmpID = pSecData->getValueByKey( lobCmpId );
   }
   return cmpID;
}

//**************************************************************************************************
std::string AWDBPConfig::getCBOFieldNameByLobField(const std::string& cboName, const std::string& lobField )
{
   std::string fieldName = "";
   SectionData* pAwdSection = getSectionData( AwdFields ); 
   if( pAwdSection )
   {  
        std::string  strLobField; 
        strLobField = pAwdSection->getKeyByValue( lobField );
        //strLobField;
        if( strLobField != "" )
        {
            SectionData* pSecDataCBO = getSectionData( cboName ); 
            if( pSecDataCBO )
            {
               fieldName = pSecDataCBO->getValueByKey( strLobField );
               fieldName = StringHelp::strip( fieldName );             
            }        
        }
   }
   return fieldName;
}

//**************************************************************************************************
std::string AWDBPConfig::getLobFieldNameByCBOField(const std::string& cboName, 
                                       const std::string& cboField )
{
   std::string fieldName = "";
   SectionData* pSecDataCBO = getSectionData( cboName ); 
   if( pSecDataCBO )
   {
      std::string  fieldId;
      fieldId  = pSecDataCBO->getKeyByValue( cboField );
      SectionData* pAwdSection = getSectionData( AwdFields ); 
     
      fieldId = StringHelp::strip( fieldId );             

      if( pAwdSection && fieldId == ""   )
       {  
         fieldName = pAwdSection->getValueByKey( fieldId );
         fieldName = StringHelp::strip( fieldName );  
       }  
   }
   return fieldName;
}

//********************************************************************************************
void AWDBPConfig::init()
{
   std::string name;   
   char cDirectory[64];
   ::GetCurrentDirectory(sizeof(cDirectory) - 1, cDirectory);
   std::string temp = AWD_KEFILE;
   sprintf(_fileName,"%s%s",cDirectory,temp.c_str() );
   char ac_Result[512];
   long lRetValue;
	lRetValue = GetPrivateProfileSectionNames(ac_Result,512,(LPCTSTR)(_fileName ));
   for(int i=0; i< lRetValue; i++)
	{
      if(ac_Result[i] != '\0') 
      {
         name += ac_Result[i];
      }
      else
      {  
         registerSection( name );
         name = "";
      }      
	}   
   SECTION_VECTOR_ITER iter = _section.begin();
   while( iter != _section.end() )
   {         
      readSectionData( **iter );
      ++iter;
   }
}
//*********************************************************************************************
void AWDBPConfig::readSectionData( const std::string& secName  )
{
   char ac_Result[512];
   long lRetValue;
   std::string name,value;
   SectionData* pSectionData = NULL;
   lRetValue = GetPrivateProfileSection((LPCTSTR)(secName.c_str()), ac_Result, 512, (LPCTSTR)_fileName);
   bool bFind = false;  
   if( lRetValue > 4)
   {
      pSectionData =  new SectionData();
      _sectionDetail.insert( SECTION_DETAIL_VALUE_TYPE( secName, pSectionData ) ); 
   }

	for(int i=0; i < lRetValue; i++)
	{  
      
		if(ac_Result[i] != '\0') {
         if( ac_Result[i] != '=' )
         { 
            if( bFind )
            {
               value += ac_Result[i]; 
            }
            else
            {
               name += ac_Result[i];
            }
         }
         else  
         {
            bFind = true;
            continue;
         }
		} 
      else 
      {
         if( pSectionData )
         {         
            pSectionData->addSectionData(name,value );
         }
         bFind = false;
         name = "";
         value = "";
		}
	}
}
//***********************************************************************************************
void AWDBPConfig::registerSection(std::string compName )
{
   std::string* dstr =  new std::string(  compName );
   _section.push_back( dstr);
}

//************************************************************************************************
void  AWDBPConfig::deregistSection()
{
      SECTION_VECTOR_ITER iter = _section.begin();
      while( iter !=  _section.end()  )
      {
         delete *iter;
         ++iter;
      }
      _section.erase( _section.begin( ), _section.end( ) );

}
//********************************************************************************
AWDBPConfig::SectionData::SectionData()
{

}
//********************************************************************************
AWDBPConfig::SectionData::~SectionData()
{
   SEC_DATA_ITER iter1 = _sectionData.begin();
   while( iter1 != _sectionData.end() )
   {
      delete (*iter1).second;
      ++iter1;
   } 
   _sectionData.clear();
}
//********************************************************************************
std::string AWDBPConfig::SectionData::getKeyByValue( const std::string& value )
{
   std::string key = "";
   SEC_DATA_ITER iter = _sectionData.begin();
   while( iter != _sectionData.end() )
   {
      if( value == *(*iter).second )
      {
         key = (*iter).first;
         break;
      }   
   }
   return key;
}
//********************************************************************************
std::string AWDBPConfig::SectionData::getValueByKey( const std::string& key )
{
   std::string value = "";
   SEC_DATA_ITER iter = _sectionData.find( key );
   if( iter != _sectionData.end() )
   {  
      value = *(*iter).second;
   }
   else {
      assert( 0 );
   }
   return value;
}

//***********************************************************************************
void AWDBPConfig::SectionData::addSectionData(const std::string& key,const std::string& value )
{
   _sectionData.insert(SEC_DATA_VALUE_TYPE( key, new std::string(value) ) );
}
//************************************************************************************
SectionDataIter::SectionDataIter(AWDBPConfig::SectionData* pSD)
{
   _pSD = pSD;
   begin();
}
//*************************************************************************************
bool SectionDataIter::begin()
{
  _curIter = _pSD->_sectionData.begin();
  return _curIter != _pSD->_sectionData.end();
}
//*************************************************************************************
bool SectionDataIter::end()
{
  return _curIter == _pSD->_sectionData.end();
}
//*************************************************************************************
bool SectionDataIter::operator++()
{
   if( !end() )
   {
      ++_curIter;   
      return true;
   }
   return false;
}
//***************************************************************************************
std::string SectionDataIter::getSectionKey()
{ 
      return (*_curIter).first;
}
//***************************************************************************************
std::string SectionDataIter::getSectionValue()
{
      std::string value = *(*_curIter).second;
      return value;
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/awdsrv/AWDBPConfig.cpp-arc  $
// 
//    Rev 1.2   Nov 14 2005 11:39:28   yingbaol
// PET1332,FN09:fix issue
// 
//    Rev 1.1   Nov 08 2005 14:14:54   yingbaol
// PET1332,FN09: remove DString and infra structure
// 
//    Rev 1.0   Oct 31 2005 14:47:24   yingbaol
// Initial revision.
 * 
 *

 */