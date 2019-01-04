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
// ^FILE   : AwdBase.hpp
// ^AUTHOR : Yingbao Li
// ^DATE   : Oct. 21, 2005
//
// ^CLASS    : AwdBase
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//********************************************************************************

#pragma once


class ElementAttributeList;
class BasicDocument;
class BFDocument;
class ElementWriter;
class AwdLobData;
class BPResult;
class YBSocket;
class  AwdBase
{
public:
   AwdBase( );
   ~AwdBase(void);   
   void getXMLData(AwdLobData& lob, std::string& strXml );
   bool  requestService( AwdLobData& lobData, BPResult& result,YBSocket* pSocket );
protected:
   virtual std::string getProcessName() = 0; 
   virtual std::string getProcessParamName() = 0; 
   virtual std::string getCBOName() = 0;
   virtual ElementAttributeList* getProcessAttributeList(ElementAttributeList* eal) = 0;
   virtual ElementAttributeList* getCBOAttributeList(ElementAttributeList* eal) = 0;

   virtual void  addProcessParameter(BasicDocument& doc, AwdLobData& lob) ;
   virtual void  addCBOandFields(BasicDocument& doc, AwdLobData& lob);
   virtual void addCBOKey(const std::string& cboName, 
                          BasicDocument& doc,
                          AwdLobData& lob,
                          const int iNo);
   virtual void addCBOFields(const std::string& cboName, 
                              BasicDocument& doc,
                              AwdLobData& lob,
                              const int iNo);     
private:   
   void buildXMLHeader( BasicDocument& doc,AwdLobData& lob );
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/awdsrv/awdbase.hpp-arc  $
//
//   Rev 1.1   Nov 08 2005 14:14:50   yingbaol
//PET1332,FN09: remove DString and infra structure
//
//   Rev 1.0   Oct 31 2005 14:45:34   yingbaol
//Initial revision.
 * 
 *

 */



