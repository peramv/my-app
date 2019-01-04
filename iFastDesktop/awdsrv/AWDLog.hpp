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
// ^FILE   : AWDLog.hpp
// ^AUTHOR : Yingbao Li
// ^DATE   : Oct. 21, 2005
//
// ^CLASS    :AWDLog
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//********************************************************************************
#pragma once
#include <fstream>

class AwdLobData;
class  AWDLog
{
public:
   AWDLog& OpenFile();
   AWDLog& operator<<( std::string log );
   AWDLog& AWDLog::addLogWithTimeStamp( std::string log );
   AWDLog& AWDLog::logLOBData( AwdLobData& lobdata  );
   static AWDLog& getInstance(  );
   static void killInstance( );

private:
   AWDLog( );
   ~AWDLog();
   bool isSameDay(WORD& day );
   void setDay(WORD day);
   std::string getFileName();
   void closeFile();
   std::string convertIntToString(int iNum);
private:
   static AWDLog* _pInstance;

   WORD _wDay;
   std::ofstream _outfile; 

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/awdsrv/AWDLog.hpp-arc  $
//
//   Rev 1.1   Nov 08 2005 14:15:18   yingbaol
//PET1332,FN09: remove DString and infra structure
//
//   Rev 1.0   Oct 31 2005 14:50:28   yingbaol
//Initial revision.
 * 
 *

 */





