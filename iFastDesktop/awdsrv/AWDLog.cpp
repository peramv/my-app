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
// ^FILE   : AWDLog.cpp
// ^AUTHOR : Yingbao Li
// ^DATE   : Oct. 21, 2005
//
// ^CLASS    : AWDLog
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//********************************************************************************
#include "stdafx.h"
#include "AWDLog.hpp"
#include "AWDLobData.hpp"
#include <stdio.h>
#include <iostream>
#include "StringHelp.hpp"
#include "AwdServiceManager.hpp"
#include "AwdBPConfig.hpp"


namespace KEBPLog
{   
   const char * const FILEHEADING                    = "AWDBP";
   const char * const DASH                           = "--";
   const char * const EXT                            = ".txt";
   const char * const COL                            = ":";
   const char * const DATE                           = "Date(yy--mm--day)";
   const char * const TIME                           = "time(hh:mm:s:ms)";
   const char * const POND                           = "   ##########   ";
   const char * const TRACEFILE                      = "TraceLobData.ini";
   const char * const EQUAL                          = "  =  ";


}
AWDLog *AWDLog::_pInstance = NULL;



AWDLog::AWDLog( )
{

}
//*******************************************************************************
AWDLog::~AWDLog(void)
{
   closeFile();
}
//******************************************************************************
bool AWDLog::isSameDay(WORD& day )
{
   SYSTEMTIME st;
   GetLocalTime( &st );
   day = st.wDay;
   if( st.wDay == _wDay )
   {
         return true;
   }
   return false;
}
//*******************************************************************************
void AWDLog::setDay(WORD day)
{
   _wDay = day;
}
//********************************************************************************
std::string AWDLog::convertIntToString(int iNum)
{
   std::string str;
   char szValue[32];
//   memset(szValue,'',sizeof (szValue) );
   itoa(iNum, szValue,10 );
   str=szValue;
   return str;
}


//********************************************************************************
std::string AWDLog::getFileName()
{
   std::string fileName =  AwdServiceManager::getInstance()->getConfig()->getLogDirectory();
   fileName += KEBPLog::FILEHEADING;
   fileName += KEBPLog::DASH;
   SYSTEMTIME st;
   GetLocalTime( &st );  
   fileName += convertIntToString( st.wYear );
   fileName += KEBPLog::DASH;
   fileName += convertIntToString( st.wMonth);
   fileName += KEBPLog::DASH;
   fileName += convertIntToString( st.wDay);
   fileName += KEBPLog::EXT;
   return fileName;
}
//*******************************************************************************
AWDLog& AWDLog::OpenFile()
{
   WORD day;
   std::string fileName = getFileName();
   if( !isSameDay( day ) )
   {
      if( _outfile.is_open() )
      {
         _outfile.flush();
         _outfile.close();
      }
      // delete the existing file
	  _outfile.open( fileName.data(), std::ofstream::out | std::ofstream::trunc);
      _outfile.close();
      setDay( day );
   }
   if( !_outfile.is_open() )
   {
      _outfile.open( fileName.data(), std::ofstream::out | std::ofstream::app);   
   }  
   return ( *this );
}
//*******************************************************************************
void AWDLog::closeFile()
{
   if( _outfile.is_open() )
   {
      _outfile.flush();
      _outfile.close();
   }
}
//************************************************************************************
AWDLog& AWDLog::operator<<( std::string log ) 
{ 
      OpenFile();
      _outfile<< log.c_str();
      _outfile.flush();
      return( *this ); 
}
//************************************************************************************
AWDLog& AWDLog::addLogWithTimeStamp( std::string log )
{
   std::string strTemp = KEBPLog::DATE;
   SYSTEMTIME st;
   GetLocalTime( &st );   
   strTemp += convertIntToString( st.wYear);
   strTemp += KEBPLog::DASH;
   strTemp += convertIntToString( st.wMonth);
   strTemp += KEBPLog::DASH;
   strTemp += convertIntToString( st.wDay);
   strTemp += KEBPLog::POND;
   strTemp += KEBPLog::TIME;
   strTemp += convertIntToString( st.wHour);
   strTemp += KEBPLog::COL;
   strTemp += convertIntToString( st.wMinute);
   strTemp += KEBPLog::COL;
   strTemp += convertIntToString( st.wSecond);
   strTemp += KEBPLog::COL;
   strTemp += convertIntToString( st.wMilliseconds);
   OpenFile();
   _outfile<< strTemp.c_str();
   _outfile<< std::endl; 
   _outfile<< log.c_str();
   _outfile<< std::endl; 
   _outfile.flush();
   return ( *this );
}

//************************************************************************************
AWDLog& AWDLog::logLOBData( AwdLobData& lobdata )
{
   std::string strTemp = KEBPLog::DATE;
   SYSTEMTIME st;
   GetLocalTime( &st );   
   strTemp += convertIntToString( st.wYear);
   strTemp += KEBPLog::DASH;
   strTemp += convertIntToString( st.wMonth);
   strTemp += KEBPLog::DASH;
   strTemp += convertIntToString( st.wDay);
   strTemp += KEBPLog::POND;
   strTemp += KEBPLog::TIME;
   strTemp += convertIntToString( st.wHour);
   strTemp += KEBPLog::COL;
   strTemp += convertIntToString( st.wMinute);
   strTemp += KEBPLog::COL;
   strTemp += convertIntToString( st.wSecond);
   strTemp += KEBPLog::COL;
   strTemp += convertIntToString( st.wMilliseconds);
   OpenFile();
   if( _outfile.is_open() )
   {
      _outfile<< strTemp.c_str();
      _outfile<< std::endl; 
      strTemp = "";
      std::string traceini = KEBPLog::TRACEFILE;
      std::ifstream trace( traceini.c_str() ); 
      if( trace.is_open() )
      {
         while( !trace.eof() )
         {
            char ch[5];
            trace.read(ch,5);
            ch[4] = '\0';            
            std::string aStr;
            aStr.append(ch);

            aStr = StringHelp::strip(aStr);
            std::string line(aStr);
            line += KEBPLog::EQUAL; 
            line += lobdata.getLobFieldValue(aStr);            
            _outfile << line.c_str();
            _outfile<< std::endl; 
         } 
         trace.close();
      }
   }
   _outfile.flush();
   return ( *this );
   
}
//*************************************************************************************
AWDLog& AWDLog::getInstance(  )
{
   if( _pInstance == NULL )
   {
      _pInstance = new AWDLog();      
   }      
   return (*_pInstance );
}
//*************************************************************************************
void AWDLog::killInstance(  )
{
   if( _pInstance != NULL )
   {
      delete _pInstance;
      _pInstance = NULL;
   }      
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/awdsrv/AWDLog.cpp-arc  $
// 
//    Rev 1.3   Nov 15 2005 16:08:00   yingbaol
// PET1332,FN09: Logging directory support
// 
//    Rev 1.2   Nov 14 2005 11:39:42   yingbaol
// PET1332,FN09:fix issue
// 
//    Rev 1.1   Nov 08 2005 14:15:16   yingbaol
// PET1332,FN09: remove DString and infra structure
// 
//    Rev 1.0   Oct 31 2005 14:50:20   yingbaol
// Initial revision.
 * 
 *

 */





