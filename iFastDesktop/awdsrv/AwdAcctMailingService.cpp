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
// ^FILE   : AwdAcctMailingService.cpp
// ^AUTHOR : Yingbao Li
// ^DATE   : Oct. 26, 2005
//
// ^CLASS    : AwdAcctMailingService
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//********************************************************************************
#include "stdafx.h"
#include "ElementWriter.hpp"
#include "ElementAttribute.hpp"
#include "awdbase.hpp"
#include "AwdAcctMailingService.hpp"
#include "xmltag.hpp"
#include "AwdLobData.hpp"
#include "AWDBPConfig.hpp"
#include "AwdServiceManager.hpp"

namespace
{
    char * const CLASSNAME                    = "AwdAcctMailingService" ;
    char * const PROCESS_PARAM_NAME           = "AccountMailProcessParam" ;
    char * const PROCESS_CBO_NAMES            = "AccountMailProcessCBO" ;
    char * const PROCESS_NAME                 = "AccountMailProcess" ;
}
//*****************************************************************************
AwdAcctMailingService::AwdAcctMailingService( ):AwdBase()
{


}
//******************************************************************************
AwdAcctMailingService::~AwdAcctMailingService( )
{

}
//*********************************************************************************
std::string AwdAcctMailingService::getCBOName()
{
   return PROCESS_CBO_NAMES;
}
//*********************************************************************************
// protect method
//
std::string AwdAcctMailingService::getProcessName()
{
   return PROCESS_NAME;
}
//**********************************************************************************
std::string AwdAcctMailingService::getProcessParamName()
{
   return PROCESS_PARAM_NAME;
}
//*********************************************************************************
//
//
ElementAttributeList* AwdAcctMailingService::getCBOAttributeList(ElementAttributeList* eal)
{
   eal->add(BasicElementAttribute(awdxml::classtag, awdxml::cbo ) );
   eal->add(BasicElementAttribute(awdxml::action, awdxml::update ) );
   return eal;
}

//**********************************************************************************

ElementAttributeList* AwdAcctMailingService::getProcessAttributeList(ElementAttributeList* eal)
{
   eal->add(BasicElementAttribute(awdxml::classtag, awdxml::process ) );
   eal->add(BasicElementAttribute(awdxml::action, awdxml::submit ) );
   return eal;
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/awdsrv/AwdAcctMailingService.cpp-arc  $
// 
//    Rev 1.1   Nov 08 2005 14:14:34   yingbaol
// PET1332,FN09: remove DString and infra structure
// 
//    Rev 1.0   Oct 31 2005 14:42:56   yingbaol
// Initial revision.
 * 
 *

 */




