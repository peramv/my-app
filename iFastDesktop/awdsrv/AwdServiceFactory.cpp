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
// ^FILE   : AwdServiceFactory.cpp
// ^AUTHOR : Yingbao Li
// ^DATE   : Oct. 21, 2005
//
// ^CLASS    : 
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//********************************************************************************

#include "stdafx.h"
#include "awdbase.hpp"
#include "AwdServiceFactory.hpp"
#include "AwdAcctMailingService.hpp"
#include "AwdMailingFundGroupService.hpp"
#include "AwdServiceManager.hpp"
#include <string>
#include <iostream>

namespace ServiceName
{
   // Trace literals
   extern char * const MailingService                      =  "MailingService" ;
   extern char * const FundGroupMailingService             = "FundGroupMailingService" ;
 
}
//******************************************************************************
AwdServiceFactory::AwdServiceFactory()
{
  
}
//******************************************************************************
AwdServiceFactory::~AwdServiceFactory()
{
  
}
//******************************************************************************
AwdBase* AwdServiceFactory::getService( const std::string serviceName )
{
  SERVICE_MAP_ITER iter = _service.find(  serviceName );
  AwdBase* pService = NULL;
  if( iter == _service.end() )
  {
     if( serviceName ==  ServiceName::MailingService )
     {
        pService = new AwdAcctMailingService();
     }
     else if ( serviceName ==  ServiceName::FundGroupMailingService )
     {
        pService = new AwdMailingFundGroupService();
     }
     else
     {
         assert( 0 );
     }
     if( pService ) // add service to the map
     {
        _service.insert( SERVICE_MAP_VALUE_TYPE( serviceName,pService ) );      
     }
  }
  else // we find the service
  {
      pService = (*iter ).second;
  
  }
  return pService;
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/awdsrv/AwdServiceFactory.cpp-arc  $
// 
//    Rev 1.1   Nov 08 2005 14:16:44   yingbaol
// PET1332,FN09: Remove DString and Infra structure
// 
//    Rev 1.0   Oct 31 2005 14:53:22   yingbaol
// Initial revision.
 * 
 *

 */


