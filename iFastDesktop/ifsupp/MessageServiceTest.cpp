#include "stdafx.h"

#include "./MessageServiceTest.h"

#include <bfutil\bfhrtimer.hpp>
#include <sstream>
#include <Winsock2.h>

bool MessageServiceTest::doTelnetTest(DString& message)
{
  message = I_("BrokerURL not valid");

  DString dstrHostPrimary;
  DString dstrHostBackup;
  int portPrimary;
  int portBackup;
  parseBrokerURL(dstrHostPrimary, portPrimary, dstrHostBackup, portBackup);
  if (dstrHostPrimary != I_("") && portPrimary != 0)
  {
    long rc = checkPort(dstrHostPrimary, portPrimary, message);
    if (rc >= 0)
    {
      return (true);
    }
  }
  if (dstrHostBackup != I_("") && portBackup != 0)
  {
    long rc = checkPort(dstrHostBackup, portBackup, message);
    if (rc >= 0)
    {
      return (true);
    }
  }
  return (false);
}

long MessageServiceTest::checkPort(const DString& strHost, unsigned short nPort, DString& strError)
{
  DStringA dstrHost = DStringA(strHost);
  if (!nPort)
  {
    strError = I_("Bad Port");
    return (-1);
  }
  struct hostent* hp = ::gethostbyname(dstrHost.c_str());
  if (NULL == hp)
  {
    struct in_addr addr;
    addr.s_addr = ::inet_addr(dstrHost.c_str());
    if (addr.s_addr == INADDR_NONE)
    {
      std::wstringstream wss;
      wss << I_("Bad host address: ") << WSAGetLastError();
      strError = wss.str();
      return (-2);
    }

    hp = gethostbyaddr((char*)&addr, sizeof(addr), AF_INET);
    if (NULL == hp)
    {
      std::wstringstream wss;
      wss << I_("Bad host address: ") << WSAGetLastError();
      strError = wss.str();
      return (-3);
    }
  }

  int mySocket = ::socket(AF_INET, SOCK_STREAM, 0);

  if (mySocket < 0)
  {
    std::wstringstream wss;
    wss << I_("Socket initialization failed: ") << WSAGetLastError();
    strError = wss.str();
    return (-4);
  }

  struct sockaddr_in sin;

  memcpy(&sin.sin_addr.s_addr, hp->h_addr, hp->h_length);
  sin.sin_family = AF_INET;
  sin.sin_port = ::htons(nPort); /* Service port number */

  BFHRTimer tConnect;
  if (::connect(mySocket, (struct sockaddr*)&sin, sizeof sin))
  {
    std::wstringstream wss;
    wss << I_("Timeout: ") << WSAGetLastError();
    strError = wss.str();
    return (-5);
  }
  ::closesocket(mySocket);
  // successfully connected in # ms
  I_CHAR szBuf[256];
  i_sprintf(szBuf, I_("%ld ms"), tConnect.elapsed());
  strError = szBuf;
  return (tConnect.elapsed());
}


bool MessageServiceTest::doConnectionTest(DString& message)
{
  if (!createConnectionFactory(message))
  {
    return (false);
  }
  if (!createConnection(message))
  {
    return (false);
  }
  if (!createSession(message))
  {
    return (false);
  }
  message = I_("Successful");
  return (true);
}