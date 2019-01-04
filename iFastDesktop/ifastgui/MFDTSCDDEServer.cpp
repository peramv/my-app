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
//    Copyright 1997 by International Financial Data Services
//
//
//******************************************************************************
//
// ^FILE   : MFDSTCDDEServer.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : 12/06
//
// ----------------------------------------------------------
//
// ^CLASS    : MFDSTCDDEServer
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  
//
//******************************************************************************
#include "stdafx.h"

#include "mfdstc.h"
#include "dstcview.h"
#include "mainfrm.h"
#include "mfdstcddeserver.h"
#include <ifastawd\dstcawdsession.hpp>
#include <bfproc\genericinterfacecontainer.hpp>


namespace ifds
{  
   extern CLASS_IMPORT const BFTextFieldId BusinessPhone;
   extern CLASS_IMPORT const BFTextFieldId CallStartTime;
   extern CLASS_IMPORT const BFTextFieldId CallerName;
}

//******************************************************************************
MFDSTCDDETopic::MFDSTCDDETopic()
{
}

//******************************************************************************
BOOL MFDSTCDDETopic::Exec (void* pData, DWORD dwSize)
{
   wchar_t buf[128];
   swprintf(buf,
            (wchar_t*)pData);
   m_pServer->Status (L"Exec command is: %s", buf);

//make sure the main view is active
   CDSTCView *pDSTCView = (CDSTCView*)(((CMainFrame*)AfxGetMainWnd())->GetActiveView());
   if (pDSTCView)
   {
      //start the call...
      pDSTCView->startCall ();
      if (pDSTCView->m_rpGIWorkSession)
      {
         DSTCAWDSession* pAwdSession = 
            dynamic_cast< DSTCAWDSession* >(pDSTCView->m_rpGIWorkSession->getSession());
         if (pAwdSession)
         {
//copy fields that do not match
            struct tag_awd_fields
            {
               DString _tag;
               BFFieldId _awdFieldId;
            } 
            a_tags_awd_fields [] = 
            {
               {I_("Number"),       ifds::BusinessPhone},
               {I_("Start"),        ifds::CallStartTime},
               //{I_("Date"),       ifds::NullFieldId},
               //{I_("Name"),       ifds::CallerName},
            };
            int num_fields = sizeof (a_tags_awd_fields) / sizeof (tag_awd_fields);
            I_CHAR *temp = const_cast <I_CHAR*> (buf);
            int i = 0;

            do
            {
               DString value;
               
               temp = parseIdiString (temp, a_tags_awd_fields [i]._tag, value);
               pAwdSession->setAwdField (a_tags_awd_fields [i]._awdFieldId, value);
               ++i;
            } 
            while (temp && temp != NULL_STRING && *temp && i < num_fields);
         }
      }
      ((CDSTCView*)(((CMainFrame*)AfxGetMainWnd())->GetActiveView()))->SendMessage (UM_FUNCTIONKEYPRESSED, 2);
   }

//   AfxMessageBox ((LPCTSTR)buf);   
   return TRUE;
}

//******************************************************************************
void MFDSTCDDEStringItem::OnPoke()
{
   wchar_t buf[128];
   swprintf( buf,
            L"%s is now %s",
            m_strName.GetBuffer (), GetData());
//   m_pServer->Status (L"Poke command is: %s",buf);
//   AfxMessageBox((LPCTSTR)buf);
}

//******************************************************************************
MFDSTCDDEServer::MFDSTCDDEServer(GenericInterface * pGIUserSession) :
m_ddeLogger ( new DbrkrLogger( I_("DDELog"), false) ),
m_rpGIUserSession (pGIUserSession)
{
}

//******************************************************************************
MFDSTCDDEServer::~MFDSTCDDEServer()
{
}

//******************************************************************************
BOOL MFDSTCDDEServer::OnCreate()
{
   m_AwdPhoneTopic.Create("AWDPhone");
   AddTopic (&m_AwdPhoneTopic);

   m_callerInfo.Create ("Caller Info");
   m_AwdPhoneTopic.AddItem (&m_callerInfo);
   return TRUE;
}

//******************************************************************************
void MFDSTCDDEServer::Status (const wchar_t* pszFormat, ...)
{
   wchar_t buf[1024];
   
   va_list arglist;
   va_start (arglist, pszFormat);
   vswprintf (buf, pszFormat, arglist);
   va_end (arglist);
   m_ddeLogger->logData (buf);
}
