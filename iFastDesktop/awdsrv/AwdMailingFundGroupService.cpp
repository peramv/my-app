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
// ^FILE   : AwdMailingFundGroupService.cpp
// ^AUTHOR : Yingbao Li
// ^DATE   : Oct. 25, 2005
//
// ^CLASS    : AwdMailingFundGroupService
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//********************************************************************************

#include "stdafx.h"
#include "ElementWriter.hpp"
#include "ElementAttribute.hpp"
#include "awdbase.hpp"
#include "AwdMailingFundGroupService.hpp"
#include "xmltag.hpp"
#include "AwdServiceManager.hpp"
#include "AwdBPConfig.hpp"
#include "AwdLobData.hpp"
#include "StringHelp.hpp"
namespace
{
   extern char * const CLASSNAME                    = "AwdMailingFundGroupService";
   extern char * const PROCESS_PARAM_NAME           = "AccountMailProdProcessParam";
   extern char * const PROCESS_CBO_NAMES            = "AccountMailProdProcessCBO";
   extern char * const PROCESS_NAME                 = "AccountMailProdProcess";
   extern char * const DOCUMENT_TYPE                = "DocumentType";
   extern char * const ONHOLD						= "OnHold";

   
}
//*****************************************************************************
AwdMailingFundGroupService::AwdMailingFundGroupService( ):AwdBase()
{


}
//******************************************************************************
AwdMailingFundGroupService::~AwdMailingFundGroupService( )
{

}
//*********************************************************************************
std::string AwdMailingFundGroupService::getCBOName()
{
   return PROCESS_CBO_NAMES;
}
//*********************************************************************************
// protect method
//
std::string AwdMailingFundGroupService::getProcessName()
{
   return PROCESS_NAME;
}
//**********************************************************************************
std::string AwdMailingFundGroupService::getProcessParamName()
{
   return PROCESS_PARAM_NAME;
}
//*********************************************************************************
//
//
ElementAttributeList* AwdMailingFundGroupService::getCBOAttributeList(ElementAttributeList* eal)
{
   eal->add(BasicElementAttribute(awdxml::classtag, awdxml::cbo ) );
   eal->add(BasicElementAttribute(awdxml::action, awdxml::update ) );
   return eal;
}
///**********************************************************************************
// protect method
//
//
ElementAttributeList* AwdMailingFundGroupService::getProcessAttributeList(ElementAttributeList* eal)
{
   eal->add(BasicElementAttribute(awdxml::classtag, awdxml::process ) );
   eal->add(BasicElementAttribute(awdxml::action, awdxml::submit ) );
   return eal;
}

//*************************************************************************************
// protect method
//
//************************************************************************************
void AwdMailingFundGroupService::addCBOKey(const std::string& cboName, 
                        BasicDocument& doc,
                        AwdLobData& lob,
                        const int iNo)
{
   std::string  docType[] = {"10","16","20","21" };
   std::string type = docType[iNo];
      std::string cboKey = cboName +"Key";
      AWDBPConfig::SectionData* pSDKey = 
         AwdServiceManager::getInstance()->getConfig()->getSectionData( cboKey );
      BasicElementAttribute baClassKey( awdxml::classtag, awdxml::key );
      ElementWriter ewKey( doc,cboKey,baClassKey );
      SectionDataIter iter( pSDKey );
      while( !iter.end() )
      {
         std::string lobFieldName,paramValue;
         std::string paramName = iter.getSectionKey();   
         if( paramName == DOCUMENT_TYPE )
         {
            paramValue = docType[iNo];
         }
         else
         {
            lobFieldName = iter.getSectionValue();
            paramValue = lob.getLobFieldValue( lobFieldName );
            paramValue = StringHelp::strip(paramValue);
         }
         ElementWriter::write( doc, paramName,paramValue );            
         ++iter;
      } 
}
//********************************************************************************
void AwdMailingFundGroupService::addCBOFields(const std::string& cboName, 
                           BasicDocument& doc,
                            AwdLobData& lob,
                           const int iNo)
{
   std::string  docType[] = {"10","16","20","21"};
   ElementAttributeList eal;
   eal.add(BasicElementAttribute(awdxml::classtag, awdxml::field ) );
   eal.add(BasicElementAttribute(awdxml::format, awdxml::no ) );
   AWDBPConfig::SectionData* pSDfield = AwdServiceManager::getInstance()->getConfig()->getSectionData( cboName );
   SectionDataIter iter( pSDfield );
   while( !iter.end() )
   {
      std::string paramName = iter.getSectionKey();   
      if( paramName == docType[iNo] )
      {
         std::string lobFieldName = iter.getSectionValue(); 
         std::string paramValue = lob.getLobFieldValue( lobFieldName );
         paramValue = StringHelp::strip(paramValue);
         ElementWriter::write( doc, ONHOLD,eal,paramValue );
         break;
      }
      ++iter;
   }         
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/awdsrv/AwdMailingFundGroupService.cpp-arc  $
// 
//    Rev 1.2   Nov 14 2005 11:39:54   yingbaol
// PET1332,FN09:fix issue
// 
//    Rev 1.1   Nov 08 2005 14:15:20   yingbaol
// PET1332,FN09: remove DString and infra structure
// 
//    Rev 1.0   Oct 31 2005 14:51:46   yingbaol
// Initial revision.
 * 
 *

 */