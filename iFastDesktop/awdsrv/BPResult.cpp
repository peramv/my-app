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
// ^FILE   : BPResult.cpp
// ^AUTHOR : Yingbao Li
// ^DATE   : Oct. 28, 2005
//
// ^CLASS    : BPResult
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//********************************************************************************

#include "stdafx.h"
#include "BPResult.hpp"
#include <string>
#include <iostream>
namespace BPSEVERITY
{
   const char * const NO_SEVERITY                    = "noSeverity" ;
   const char * const NO_CONDITION                   = "noCondition" ;
   const char * const TARCE                          = "traceOnly" ;
   const char * const INFORMATION                    = "information" ;
   const char * const WARNING                        = "warning" ;
   const char * const SEVERE_ERROR                   = "severeError" ;
   const char * const CRITICAL                       = "criticalError" ;

}
//******************************************************************************
BPResult::BPResult()
{
 _accountNum ="";
 _status = ""; 
}
//******************************************************************************
BPResult::~BPResult()
{
   
   CONDITION_VECTOR_ITER iter = _condition.begin();
   while( iter !=  _condition.end()  )
   {
      Condition* con = *iter;
      delete con;
      ++iter;
   }
    _condition.erase( _condition.begin( ), _condition.end( ));

}
//*******************************************************************************
 void BPResult::setAccountNum(  const std::string& account )
{
   _accountNum = account;
}
//********************************************************************************
 std::string BPResult::getAccountNum()
{
   return _accountNum;
}
//********************************************************************************
 void BPResult::setStatus( const std::string& status )
{
   _status = status;
}
//*********************************************************************************
inline std::string BPResult::getStatus( )
{
   return _status;
}
//*********************************************************************************
void BPResult::addErrorMessage( const std::string& severity, 
                                const std::string& errCode,
                                const std::string& message )
{

   Condition* con = new Condition(severity,errCode,message );
   _condition.push_back( con);

}
//*******************************************************************************
int BPResult::getHighestSeverity( )
{
   int iResult = 0;
   CONDITION_VECTOR_ITER iter = _condition.begin();
   while( iter != _condition.end() )
   {
      int severity;
      Condition* con = dynamic_cast<Condition* >(*iter );
      if( con )
      {
         severity = con->getSeverity();
         if( severity > iResult )
         {
            iResult = severity;
         }
      }  

      ++iter;
   }
   return iResult;
}
//*******************************************************************************
// since there are limit in the length of message at AWD side
// we will return 1st highest condition message to AWD Object
//
//
std::string  BPResult::getHighestSeverityMessage( )
{
   std::string message = "";
   int iHighServ = getHighestSeverity();
   CONDITION_VECTOR_ITER iter = _condition.begin();
   while( iter != _condition.end() )
   {
      int severity;
      Condition* con = dynamic_cast<Condition* >(*iter );
      if( con )
      {
         severity = con->getSeverity();
         if( severity == iHighServ )
         {
           message = con->getErrorCode();
           message += "   ";
           message += con->getMessage();
           break;
         }
      }  
      ++iter;
   }
   return message;
}
//******************************************************************************
inline std::string BPResult::Condition::getErrorCode()
{
   return _errCode;
}
//*****************************************************************************
 inline  std::string BPResult::Condition::getMessage()
{
   return _message;
}      
//*****************************************************************************
int inline BPResult::Condition::getSeverity()
{
   int iRet = 0;
   if( isCritical() )
   {
      iRet = 5;  
   }
   else if( isSevere() )
   {
      iRet = 4;
   }
   else if( isWarning() )
   {
      iRet = 3;
   }
   else if( isInformation() )
   {
      iRet = 2;
   }
   else if( isTrace() )
   {
      iRet = 1;
   }
   return iRet;
}
//*******************************************************************************
bool inline BPResult::Condition::isCritical()
{
   bool bResult = false;   
   if( _severity == BPSEVERITY::CRITICAL )
   { 
      bResult = true;
   }
   return bResult;
}
//*******************************************************************************
bool inline BPResult::Condition::isSevere()
{
   bool bResult = false;
   
   if( _severity == BPSEVERITY::SEVERE_ERROR )
   {
      bResult = true;
   }
   return bResult;
}
//*******************************************************************************
bool inline BPResult::Condition::isWarning()
{
   bool bResult = false;
   if( _severity == BPSEVERITY::WARNING )
   {
      bResult = true;
   }
   return bResult;
}
//*******************************************************************************
bool inline BPResult::Condition::isInformation()
{
   bool bResult = false;
   if( _severity == BPSEVERITY::INFORMATION )
   {
      bResult = true;
   }
   return bResult;
}
//*******************************************************************************
bool inline BPResult::Condition::isTrace()
{
   bool bResult = false;
   if( _severity == BPSEVERITY::TARCE )
   {
      bResult = true;
   }
   return bResult;
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/awdsrv/BPResult.cpp-arc  $
// 
//    Rev 1.2   Nov 14 2005 11:02:32   yingbaol
// PET1233,FN09:take out inline
// 
//    Rev 1.1   Nov 08 2005 14:17:22   yingbaol
// PET1332,FN09: Remove DString and Infra structure
// 
//    Rev 1.0   Oct 31 2005 14:55:44   yingbaol
// Initial revision.
 * 
 *

 */






