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
// ^FILE   : AwdBase.cpp
// ^AUTHOR : Yingbao Li
// ^DATE   : Oct. 21, 2005
//
// ^CLASS    : AwdBase
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//********************************************************************************

#include "stdafx.h"
#include "ElementWriter.hpp"
#include "ElementAttribute.hpp"
#include "awdbase.hpp"
#include "xmltag.hpp"
#include "AWDLobData.hpp"
#include "AwdServiceManager.hpp"
#include "AwdBPConfig.hpp"
#include "BPResult.hpp"
#include "BPResultParser.hpp"
#include "YBSocket.hpp"
#include "logging.h"
#include "StringHelp.hpp"

namespace
{
    const char * const CLASSNAME                    = "AwdBase" ;
    const char * const BUSINESS_AREA                = "UNIT";
    const char * const REPEAT                       = "Repeat" ;
    const char * const IFAST_PACKAGE                = "iFAST_Package" ;
	 const char * const BP_ERROR_STATUS              = "BPErrStatus"; 
	 const char * const BP_OK_STATUS                 = "BPOkStatus"; 
	 const char * const REJECT								 = "REJECT"; 
}
//*****************************************************************************
AwdBase::AwdBase( )
{
}
//******************************************************************************
AwdBase::~AwdBase( )
{
}
//*********************************************************************************
void AwdBase::getXMLData(AwdLobData& lob, std::string& strXml )
{
   BasicDocument doc(strXml);
   ElementWriter  ewPackage( doc,IFAST_PACKAGE );
   buildXMLHeader( doc,lob );
   ElementAttributeList eal;
   eal.add(BasicElementAttribute(awdxml::id, "A"  ) ); 
   eal.add(BasicElementAttribute(awdxml::ignoreWarnings, awdxml::yes ) );
   ElementWriter  ew( doc,awdxml::batch,eal );  
   ElementAttributeList* ealP = new ElementAttributeList();
   ElementWriter  ewP( doc,getProcessName(),*getProcessAttributeList(ealP) );
   addProcessParameter( doc, lob );
   addCBOandFields( doc, lob ); 
}
//**********************************************************************************
void AwdBase::addProcessParameter(BasicDocument& doc, AwdLobData& lob )
{
   BasicElementAttribute baClass( awdxml::classtag, awdxml::parm );
   std::string processParamName = getProcessParamName();   
   AWDBPConfig::SectionData* pSD = AwdServiceManager::getInstance()->getConfig()->getSectionData(processParamName);
   if( pSD )
   {
      SectionDataIter iter( pSD );
      while( !iter.end() )
      {
         std::string param = iter.getSectionKey();      
         std::string lobName = iter.getSectionValue();      
         std::string lobValue = lob.getLobFieldValue( lobName );
         lobValue = StringHelp::strip(lobValue);
         ElementWriter::write( doc, param, baClass,lobValue );
         ++iter;
      }  
   }
}
//*********************************************************************************
void AwdBase::buildXMLHeader( BasicDocument& doc,AwdLobData& lob )
{
   //ElementWriter  ew( doc,awdxml::package );
   BasicElementAttribute baClass( awdxml::classtag, awdxml::parm );
   std::string temp = AwdServiceManager::getInstance()->getConfig()->getUserID();
   ElementWriter::write( doc, awdxml::userId, baClass,temp );
   temp = AwdServiceManager::getInstance()->getConfig()->getPassword();
   ElementWriter::write( doc, awdxml::userPassword, baClass,temp );
   std::string cmpId = lob.getLobFieldValue(BUSINESS_AREA);
   cmpId = StringHelp::strip(cmpId );
   temp = AwdServiceManager::getInstance()->getConfig()->getCompanyIdByLobData(cmpId);
   ElementWriter::write( doc, awdxml::companyId, baClass,temp );
   temp = AwdServiceManager::getInstance()->getConfig()->getLanguage();
   ElementWriter::write( doc, awdxml::language, baClass,temp );
   temp = AwdServiceManager::getInstance()->getConfig()->getLogOff();
   ElementWriter::write( doc, awdxml::logoff, baClass,temp );

}


//*************************************************************************************
// virtual protect method
// cboName: the name of the CBO, for example: mailing
// iNo: the cbo no
// The method provide default behavior, i.e. only one repeat section involved
//   this would be the most cases
//************************************************************************************
void AwdBase::addCBOKey(const std::string& cboName, 
                        BasicDocument& doc,
                        AwdLobData& lob,
                        const int iNo)
{
      std::string cboKey = cboName +"Key";
      AWDBPConfig::SectionData* pSDKey = 
         AwdServiceManager::getInstance()->getConfig()->getSectionData( cboKey );
      BasicElementAttribute baClassKey( awdxml::classtag, awdxml::key );
      ElementWriter ewKey( doc,cboKey,baClassKey );
      SectionDataIter iter( pSDKey );
      while( !iter.end() )
      {
         std::string paramName = iter.getSectionKey();   
         std::string lobFieldName = iter.getSectionValue(); 
         std::string paramValue = lob.getLobFieldValue( lobFieldName );
         paramValue = StringHelp::strip(paramValue);
         ElementWriter::write( doc, paramName,paramValue );            
         ++iter;
      } 
}
//*************************************************************************************
// virtual protect method
// cboName: the name of the CBO, for example: mailing
// iNo: the cbo no
// The method provide default behavior, i.e. only one repeat section involved
//   this would be the most cases
//************************************************************************************
void AwdBase::addCBOFields(const std::string& cboName, 
                           BasicDocument& doc,
                           AwdLobData& lob,
                           const int iNo)
{
   ElementAttributeList eal;
   eal.add(BasicElementAttribute(awdxml::classtag, awdxml::field ) );
   eal.add(BasicElementAttribute(awdxml::format, awdxml::no ) );
   AWDBPConfig::SectionData* pSDfield = AwdServiceManager::getInstance()->getConfig()->getSectionData( cboName );
   SectionDataIter iter( pSDfield );
   while( !iter.end() )
   {
      std::string paramName = iter.getSectionKey();   
      std::string lobFieldName = iter.getSectionValue(); 
      std::string paramValue = lob.getLobFieldValue( lobFieldName );
      paramValue = StringHelp::strip(paramValue);
      ElementWriter::write( doc, paramName,paramValue );            
      ++iter;
   }         
}
//*************************************************************************************
// protect method
//
//
//
void AwdBase::addCBOandFields(BasicDocument& doc, AwdLobData& lob )
{
   std::string cboSection = getCBOName();
   AWDBPConfig::SectionData* pSD = AwdServiceManager::getInstance()->getConfig()->getSectionData( cboSection );
   if( pSD )
   {
      SectionDataIter iter( pSD );
      while( !iter.end() )
      {
         std::string cboName = iter.getSectionValue();      
         std::string repeatSec = cboName + REPEAT;
         std::string look = REPEAT;
         look += "Num";
         std::string dstrNum = AwdServiceManager::getInstance()->getConfig()->getFieldValueInSection( repeatSec,look);
         for ( int i = 0; i < atoi(dstrNum.c_str() ); i++ )
         {
            ElementAttributeList* eal  =  new ElementAttributeList();
            ElementWriter  ew( doc,cboName,*getCBOAttributeList( eal) );
            addCBOKey( cboName, doc,lob,i);
            addCBOFields( cboName, doc,lob,i);
            delete eal;
         }
         ++iter;
      }  
   }
}
//***********************************************************************************
bool AwdBase::requestService( AwdLobData& lob, BPResult& result,YBSocket* pSocket )
{
   bool bRet = false;
   std::string xmlIn;
   std::string xmlOut;
   getXMLData( lob, xmlIn );
   LOGGING("AwdBase::requestService\n");
   LOGGINGWITHTIMESTAMP( xmlIn );    
   xmlIn += '\0';
   if( pSocket )
   {
      bRet = pSocket->readWrite(xmlIn.c_str(),xmlOut,xmlIn.length() );
   }
   BPResultParser  parsor ;
   if( bRet )
   {
      //LOGGINGWITHTIMESTAMP( xmlIn );    
      try
      {
         parsor.parse( xmlOut,result ); 
      }
      catch (xercesc::SAXParseException )
      {
         bRet = false;      
      }
   }
   if( bRet )
   {
       if( result.getHighestSeverity() < 4 )
       {
		    std::string acctNum = result.getAccountNum();
          std::string acctName = AwdServiceManager::getInstance()->getConfig()->getAccountName();
          acctNum = StringHelp::strip( acctNum );
          acctName = StringHelp::strip( acctName );
          lob.setLobFieldValue(acctName,acctNum);       
			 std::string status = AwdServiceManager::getInstance()->getConfig()->getFieldValueInSection("User Info",BP_OK_STATUS);
			 status = StringHelp::strip( status );
			 std::string orgStatus = lob.getLobFieldValue("STAT" );
			 orgStatus = StringHelp::strip(orgStatus);
			 if( orgStatus != REJECT )
			 {
				lob.setLobFieldValue("STAT",status );
			 }
       }
	   else 
	   {
			std::string status = AwdServiceManager::getInstance()->getConfig()->getFieldValueInSection("User Info",BP_ERROR_STATUS);
			status = StringHelp::strip( status );
			lob.setLobFieldValue("STAT",status );
	   }
   }
   return bRet;
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/awdsrv/awdbase.cpp-arc  $
// 
//    Rev 1.7   Nov 29 2005 13:23:16   yingbaol
// PET1332,FN09:don't change status if it is reject.
// 
//    Rev 1.6   Nov 28 2005 10:46:36   yingbaol
// PET1332,update AWD status when everythingis fine.
// 
//    Rev 1.5   Nov 21 2005 09:39:04   yingbaol
// PET1332:FN09,Update AWD status is configurable  if there is a 
// critical error at BP Server side.
// 
//    Rev 1.4   Nov 14 2005 11:39:14   yingbaol
// PET1332,FN09:fix issue
// 
//    Rev 1.3   Nov 08 2005 14:38:06   yingbaol
// PET1332,FN09: Remove Infra
// 
//    Rev 1.1   Nov 01 2005 10:00:30   yingbaol
// take parser exception into consideration. 
// 
//    Rev 1.0   Oct 31 2005 14:45:20   yingbaol
// Initial revision.
 * 
 *

 */




















