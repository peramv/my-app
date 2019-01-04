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
// ^FILE   : AwdMailingFundGroupService.hpp
// ^AUTHOR : Yingbao Li
// ^DATE   : Oct. 25, 2005
//
// ^CLASS    :AwdMailingFundGroupService
// ^SUBCLASS :AwdBase
//
// ^CLASS DESCRIPTION :
//********************************************************************************

#pragma once


class ElementAttributeList;
class BasicDocument;
class BFDocument;
class ElementWriter;
class  AwdMailingFundGroupService:  public AwdBase
{
public:
   AwdMailingFundGroupService( );
   ~AwdMailingFundGroupService(void);   

protected:
   virtual std::string getProcessName(); 
   virtual std::string getCBOName();
   virtual std::string getProcessParamName();
   virtual ElementAttributeList* getProcessAttributeList(ElementAttributeList* eal); // will be pure
   virtual ElementAttributeList* getCBOAttributeList(ElementAttributeList* eal);
   virtual void addCBOKey(const std::string& cboName, 
                        BasicDocument& doc,
                        AwdLobData& lob,
                        const int iNo);
   virtual void addCBOFields(const std::string& cboName, 
                           BasicDocument& doc,
                           AwdLobData& lob,
                           const int iNo);

};
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/awdsrv/AwdMailingFundGroupService.hpp-arc  $
//
//   Rev 1.1   Nov 08 2005 14:15:22   yingbaol
//PET1332,FN09: remove DString and infra structure
//
//   Rev 1.0   Oct 31 2005 14:51:54   yingbaol
//Initial revision.
 * 
 *

 */




