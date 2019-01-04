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
// ^FILE   : AwdServiceFactory.hpp
// ^AUTHOR : Yingbao Li
// ^DATE   : Oct. 21, 2005
//
// ^CLASS    :AwdServiceFactory
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//********************************************************************************

#pragma once

#include <map>
class AwdBase;
class AwdServiceManager;
class  AwdServiceFactory
{
public:
   AwdServiceFactory( );
   ~AwdServiceFactory();   

private:
   AwdBase* getService( const std::string serviceName );
   typedef std::map< std::string, AwdBase*  >                          SERVICE_MAP;
   typedef SERVICE_MAP::iterator                                   SERVICE_MAP_ITER;
   typedef SERVICE_MAP::value_type                                 SERVICE_MAP_VALUE_TYPE;
   SERVICE_MAP _service;
   friend class AwdServiceManager;
};
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/awdsrv/AwdServiceFactory.hpp-arc  $
//
//   Rev 1.1   Nov 08 2005 14:16:58   yingbaol
//PET1332,FN09: Remove DString and Infra structure
//
//   Rev 1.0   Oct 31 2005 14:53:28   yingbaol
//Initial revision.
 * 
 *

 */


