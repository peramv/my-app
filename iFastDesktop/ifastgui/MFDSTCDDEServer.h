
#ifndef MFDSTCDDESERVER_H
#define MFDSTCDDESERVER_H 

//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 1997 by DST Systems, Inc.
//
//******************************************************************************

#include "stddde.h"
#include <bfdbrkr\dbrkrlogger.hpp>

class GenericInterface;
class MFDSTCDDEStringItem : public CDDEStringItem
{
protected:
    virtual void OnPoke();
};

class MFDSTCDDETopic : public CDDETopic
{
public:
    MFDSTCDDETopic ();
    virtual BOOL Exec (void* pData, DWORD dwSize);
};

class MFDSTCDDEServer : public CDDEServer
{
friend MFDSTCDDETopic;
public:
   MFDSTCDDEServer (GenericInterface *pGIUserSession);
   virtual ~MFDSTCDDEServer();
   virtual void Status (const wchar_t* pszFormat, ...);
   virtual BOOL OnCreate ();

private:
   MFDSTCDDETopic m_AwdPhoneTopic;
   MFDSTCDDEStringItem m_callerInfo;
   GenericInterface *m_rpGIUserSession;
   std::auto_ptr< DbrkrLogger > m_ddeLogger;
};

#endif // MFDSTCDDESERVER_H
