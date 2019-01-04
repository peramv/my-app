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
// ^FILE   : BPResult.hpp
// ^AUTHOR : Yingbao Li
// ^DATE   : Oct. 30, 2005
//
// ^CLASS    :
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//********************************************************************************

#pragma once


#include <vector> 
#include <string>
class  BPResult
{
public:
   BPResult( );
   ~BPResult();   

   void setAccountNum( const std::string& account );
   std::string getAccountNum();
   void setStatus( const std::string& status );
   std::string getStatus( );
   void addErrorMessage( const std::string& severity, 
                         const std::string& errCode,
                         const std::string& message );
   int getHighestSeverity( );
   std::string  getHighestSeverityMessage();
   
private:
   class Condition
   {
   public:
      Condition(const std::string& severity,
                const std::string& errCode,
                const std::string& message )
      {
         _severity = severity;
         _errCode = errCode;
         _message = message;       
      };
      ~Condition()
      {   
      };
    
      std::string getErrorCode();
      std::string getMessage();
      int getSeverity();
    private:
      bool isCritical();
      bool isSevere();
      bool isWarning();
      bool isInformation();   
      bool isTrace();

      std::string _severity;
      std::string _errCode;
      std::string _message;  
   };

   typedef std::vector<Condition* >         CONDITION_VECTOR;
   typedef CONDITION_VECTOR::iterator       CONDITION_VECTOR_ITER;
   CONDITION_VECTOR _condition;
   std::string _accountNum;
   std::string _status;
 };

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/awdsrv/BPResult.hpp-arc  $
//
//   Rev 1.1   Nov 08 2005 14:17:38   yingbaol
//PET1332,FN09: Remove DString and Infra structure
//
//   Rev 1.0   Oct 31 2005 14:55:52   yingbaol
//Initial revision.
 * 
 *

 */



