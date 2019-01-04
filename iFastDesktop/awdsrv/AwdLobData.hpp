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
// ^FILE   : AwdLobData.cpp
// ^AUTHOR : Yingbao Li
// ^DATE   : Oct. 21, 2005
//
// ^CLASS    : AwdLobData
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//********************************************************************************

#pragma once

#include "awdstrct.h"
class  AwdLobData
{
public:
   AwdLobData( PAWDLOBARRAY pAwdLobArray);
   ~AwdLobData();   
   std::string getLobFieldValue( const std::string& name );
   void setLobFieldValue( const std::string& name, const std::string& value );

private:

   PAWDLOBARRAY   _pAwdLobArray;
 };

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/awdsrv/AwdLobData.hpp-arc  $
//
//   Rev 1.1   Nov 08 2005 14:15:14   yingbaol
//PET1332,FN09: remove DString and infra structure
//
//   Rev 1.0   Oct 31 2005 14:49:08   yingbaol
//Initial revision.
 * 
 *

 */



