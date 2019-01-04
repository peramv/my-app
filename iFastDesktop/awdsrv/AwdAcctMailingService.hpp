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
// ^FILE   : AwdAcctMailingService.hpp
// ^AUTHOR : Yingbao Li
// ^DATE   : Oct. 26, 2005
//
// ^CLASS    : AwdAcctMailingService
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//********************************************************************************

#pragma once


class ElementAttributeList;
class  AwdAcctMailingService:  public AwdBase
{
public:
   AwdAcctMailingService( );
   ~AwdAcctMailingService(void);   
protected:
   virtual std::string getProcessName(); 
   virtual std::string getProcessParamName();
   virtual std::string getCBOName();
   virtual ElementAttributeList* getProcessAttributeList(ElementAttributeList* eal); 
   virtual ElementAttributeList* getCBOAttributeList(ElementAttributeList* eal);
};
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/awdsrv/AwdAcctMailingService.hpp-arc  $
//
//   Rev 1.1   Nov 08 2005 14:14:46   yingbaol
//PET1332,FN09: remove DString and infra structure
//
//   Rev 1.0   Oct 31 2005 14:43:00   yingbaol
//Initial revision.
 * 
 *

 */




