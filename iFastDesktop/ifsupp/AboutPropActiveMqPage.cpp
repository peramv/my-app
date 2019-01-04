// AboutPropActiveMqPage.cpp : implementation file
//

#include "stdafx.h"

#include "ifsupp.h"

#include <cms/DeliveryMode.h>
#include <typeinfo.h>
#include <bfconmgr/BFConnectionManager.hpp>
#include <bfconmgr/PooledHostConnectionManager.hpp>
#include <configmanager.hpp>
#include <ifastdbrkr/ActiveMQConnectionFactory.hpp>
#include <ifastdbrkr/ActiveMqConnection.hpp>
#include <ifastdbrkr/ifastdbrkr.hpp>
#include "AMQTest.h"
#include "AboutPropActiveMqPage.h"
#include "SonicConnectionTest.h"
#include "resource.h"

// AboutPropActiveMqPage dialog

IMPLEMENT_DYNAMIC(AboutPropActiveMqPage, CPropertyPage)
AboutPropActiveMqPage::AboutPropActiveMqPage() : CPropertyPage(AboutPropActiveMqPage::IDD)
{
  m_bUseSingleConnection = GetConfigValueAsBool(I_("RTSHost"), I_("UseSingleSonicConnection"));

  DString vmHostName =
      GetConfigValueAsString(ConfigManager::getApplication(), I_("RTSHost"), I_("VMHostName"));
  BFConnectionManager* pConMgr = BFConnectionManager::getInstance();
  try
  {
    if (NULL != pConMgr)
    {
      PooledHostConnectionManager* pHostConMgr =
          dynamic_cast<PooledHostConnectionManager*>(pConMgr->getHostConnectionManager(vmHostName));
      if (NULL != pHostConMgr)
      {
        m_iMinConnections = pHostConMgr->getMinConnections();
        m_iMaxConnections = pHostConMgr->getMaxConnections();
        m_iCountConnections = pHostConMgr->getConnectionCount();
        m_iInUseConnections = pHostConMgr->getConnectionsInUse();
        m_iCountFailures = pHostConMgr->getConnectionFailures();

        auto pFactory =
            dynamic_cast<ActiveMQConnectionFactory*>(pHostConMgr->getConnectionFactory());
        if (NULL != pFactory)
        {
          m_BrokerURLs = pFactory->getBrokerURLs().c_str();
          m_User = pFactory->getUser().c_str();
          m_iTimeout = pFactory->getTimeout();
          m_SingleQueue = pFactory->getSingleQueue().c_str();
          m_MultiQueue = pFactory->getMultiQueue().c_str();
          m_LDAPQueue = pFactory->getLDAPQueue().c_str();
          m_AWDQueue = pFactory->getAwdQueue().c_str();
          m_LDAPNS = GetConfigValueAsString(I_("RTSHost"), I_("LDAPUserNS")).c_str();
          m_Password = pFactory->getPassword().c_str();
        }
      }
    }
  }
  catch (std::bad_cast)
  {
  }
}

AboutPropActiveMqPage::~AboutPropActiveMqPage() {}

void AboutPropActiveMqPage::OnOK()
{
  CPropertyPage::OnOK();

  DString vmHostName =
      GetConfigValueAsString(ConfigManager::getApplication(), I_("RTSHost"), I_("VMHostName"));
  BFConnectionManager* pConMgr = BFConnectionManager::getInstance();
  try
  {
    if (NULL != pConMgr)
    {
      PooledHostConnectionManager* pHostConMgr =
          dynamic_cast<PooledHostConnectionManager*>(pConMgr->getHostConnectionManager(vmHostName));
      if (NULL != pHostConMgr)
      {
        auto pFactory =
            dynamic_cast<ActiveMQConnectionFactory*>(pHostConMgr->getConnectionFactory());
        if (NULL != pFactory)
        {
          int iTimeout = pFactory->getTimeout();
          if (iTimeout != m_iTimeout)
          {
            pFactory->setTimeout(m_iTimeout);
            auto v = ActiveMQConnection::getDetails();
            for (auto vIter = v.begin(); vIter != v.end(); ++vIter)
            {
              auto& d = (*vIter);
              auto* p = d.p_;
              if (NULL != p)
              {
                p->setTimeout(m_iTimeout);
                p->makeStale();
              }
            }
          }
        }
      }
    }
  }
  catch (std::bad_cast)
  {
  }
}

void AboutPropActiveMqPage::DoDataExchange(CDataExchange* pDX)
{
  CPropertyPage::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_SONIC_TIMEOUT, m_wndTimeout);
  DDX_Text(pDX, IDC_SONIC_BROKER_URLS, m_BrokerURLs);
  DDX_Text(pDX, IDC_SONIC_USER, m_User);
  DDX_Text(pDX, IDC_SONIC_TIMEOUT, m_iTimeout);
  DDX_Text(pDX, IDC_SONIC_SINGLE_Q, m_SingleQueue);
  DDX_Text(pDX, IDC_SONIC_MULTI_Q, m_MultiQueue);
  DDX_Text(pDX, IDC_SONIC_LDAP_Q, m_LDAPQueue);
  DDX_Text(pDX, IDC_SONIC_AWD_Q, m_AWDQueue);
  DDX_Text(pDX, IDC_SONIC_LDAP_NS, m_LDAPNS);
  DDX_Text(pDX, IDC_SONIC_MIN_CONNECTIONS, m_iMinConnections);
  DDX_Text(pDX, IDC_SONIC_MAX_CONNECTIONS, m_iMaxConnections);
  DDX_Text(pDX, IDC_SONIC_COUNT_CONNECTIONS, m_iCountConnections);
  DDX_Text(pDX, IDC_SONIC_INUSE_CONNECTIONS, m_iInUseConnections);
  DDX_Text(pDX, IDC_SONIC_FAILED_CONNECTIONS, m_iCountFailures);
  DDX_Check(pDX, IDC_SONIC_REUSE_CONNECTION, m_bUseSingleConnection);

  DDX_Control(pDX, IDC_SONIC_CONNECTION_LIST, m_connectionList);
  DDX_Control(pDX, IDC_SONIC_VIEW_BATCHES, m_viewBatchesList);
  DDX_Control(pDX, IDC_SONIC_CHECK_STATUS, m_wndCheck);
  DDX_Control(pDX, IDC_SONIC_PING_STATUS, m_wndPing);
}

void AboutPropActiveMqPage::generateReport(std::wstringstream& ss)
{
  ss << I_("=====================================================") << std::endl;
  ss << I_("=== Sonic Information ===============================") << std::endl;
  ss << I_("UseSingleConnection: ") << m_bUseSingleConnection << std::endl;
  ss << I_("BrokerURLs: ") << LPCTSTR(m_BrokerURLs) << std::endl;
  ss << I_("Timeout: ") << m_iTimeout << std::endl;
  ss << I_("User: ") << LPCTSTR(m_User) << std::endl;
  ss << I_("SingleQ: ") << LPCTSTR(m_SingleQueue) << std::endl;
  ss << I_("MultiQ: ") << LPCTSTR(m_MultiQueue) << std::endl;
  ss << I_("LDAPQ: ") << LPCTSTR(m_LDAPQueue) << std::endl;
  ss << I_("AWDQ: ") << LPCTSTR(m_AWDQueue) << std::endl;
  ss << I_("LDAPNS: ") << LPCTSTR(m_LDAPNS) << std::endl;
  ss << I_("DeliveryMode: ");
  switch (ActiveMQConnection::getDefaultDeliveryMode())
  {
    case cms::DeliveryMode::PERSISTENT:
      ss << I_("PERSISTENT");
      break;
    case cms::DeliveryMode::NON_PERSISTENT:
      ss << I_("NON_PERSISTENT");
      break;

    default:
      ss << ActiveMQConnection::getDefaultDeliveryMode();
  }
  ss << std::endl;
  ss << I_("MinConnections: ") << m_iMinConnections << std::endl;
  ss << I_("MaxConnections: ") << m_iMaxConnections << std::endl;
  ss << I_("CountConnections: ") << m_iCountConnections << std::endl;
  ss << I_("InUseConnections: ") << m_iInUseConnections << std::endl;
  ss << I_("FailedConnections: ") << m_iCountFailures << std::endl;
  if (m_strSMQTest.GetLength() > 0)
  {
    ss << I_("--- Check Results ---") << std::endl;
    ss << LPCTSTR(m_strSMQTest);
    ss << I_("---------------------") << std::endl;
  }
  DStringA view, size;
  while (ifastdbrkr::getBatchSize(view, size))
  {
    DString dstrView(view);
    DString dstrSize(size);
    ss << I_("View Batch Size for ") << dstrView.c_str() << I_(": ") << dstrSize.c_str()
       << std::endl;
  }
  ss << std::endl;
}

BEGIN_MESSAGE_MAP(AboutPropActiveMqPage, CPropertyPage)
ON_BN_CLICKED(IDC_SONIC_PING, OnPbPing)
ON_BN_CLICKED(IDC_SONIC_CHECK, OnPbCheck)
END_MESSAGE_MAP()

// AboutPropActiveMqPage message handlers
BOOL AboutPropActiveMqPage::OnInitDialog()
{
  CPropertyPage::OnInitDialog();
  m_wndTimeout.SetReadOnly(FALSE);
  m_wndCheck.SetWindowText(I_(""));
  m_wndPing.SetWindowText(I_(""));

  m_viewBatchesList.InsertColumn(0, I_("View"), LVCFMT_LEFT, 100);
  m_viewBatchesList.InsertColumn(1, I_("Number of Batches"), LVCFMT_LEFT, 200);
  DStringA view, size;
  int cRows = 0;
  while (ifastdbrkr::getBatchSize(view, size))
  {
    int idx = m_viewBatchesList.InsertItem(cRows++, I_(""));
    DString dstrView(view);
    DString dstrSize(size);
    m_viewBatchesList.SetItemText(idx, 0, dstrView.c_str());
    m_viewBatchesList.SetItemText(idx, 1, dstrSize.c_str());
  }

  m_connectionList.InsertColumn(0, I_("TempQueue"), LVCFMT_LEFT, 100);
  m_connectionList.InsertColumn(1, I_("Used"), LVCFMT_LEFT, 100);
  m_connectionList.InsertColumn(2, I_("Timeout"), LVCFMT_LEFT, 100);
  m_connectionList.InsertColumn(3, I_("Recycles"), LVCFMT_LEFT, 100);

  auto v = ActiveMQConnection::getDetails();

  cRows = 0;
  for (auto vIter = v.begin(); vIter != v.end(); ++vIter)
  {
    int idx = m_connectionList.InsertItem(cRows++, I_(""));
    auto& d = (*vIter);
    m_connectionList.SetItemText(idx, 0, d.tQueue_.c_str());
    I_CHAR sz[33] = {0};
    i_sprintf(sz, I_("%d"), d.cUses_);
    m_connectionList.SetItemText(idx, 1, sz);
    i_sprintf(sz, I_("%d"), d.iTimeout_);
    m_connectionList.SetItemText(idx, 2, sz);
    i_sprintf(sz, I_("%d"), d.cRecycles_);
    m_connectionList.SetItemText(idx, 3, sz);
  }
  return (TRUE);
}

void AboutPropActiveMqPage::OnPbPing() { m_wndPing.SetWindowText(I_("")); }

#include <atlrx.h>
void AboutPropActiveMqPage::OnPbCheck()
{
  m_wndCheck.SetWindowText(I_(""));

  AMQTest smqTest;
  smqTest.setBrokerURL(LPCTSTR(m_BrokerURLs));
  smqTest.setSMQUser(LPCTSTR(m_User));
  smqTest.setSMQPassword(LPCTSTR(m_Password));
  smqTest.setSingleQ(LPCTSTR(m_SingleQueue));
  smqTest.setMultiQ(LPCTSTR(m_MultiQueue));
  smqTest.setAuthQ(LPCTSTR(m_LDAPQueue));
  smqTest.setAwdQ(LPCTSTR(m_AWDQueue));
  CSonicConnectionTest smqTestDlg(smqTest);
  smqTestDlg.DoModal();
}

#include <bf/log/log.hpp>
#include <bfutil/bfhrtimer.hpp>

long AboutPropActiveMqPage::checkPort(const CString& strHost, short nPort, CString& strError)
{
  DStringA dstrHost = DStringA(LPCTSTR(strHost));
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
      bf::log::LogStream ls(bf::log::databroker);
      ls << bf::log::ltrace;
      ls << I_("AboutPropActiveMqPage: ERR_CANNOT_RESOLVE_HOST_FROM_NAME") << bf::log::endl;
      ls << I_("AboutPropActiveMqPage: HostAddress = ") << strHost << bf::log::endlf;
      ls << I_("AboutPropActiveMqPage: WSAGetLastError() = ") << WSAGetLastError()
         << bf::log::endlf;
      strError = I_("Bad Address");
      return (-2);
    }

    hp = gethostbyaddr((char*)&addr, sizeof(addr), AF_INET);
    if (NULL == hp)
    {
      bf::log::LogStream ls(bf::log::databroker);
      ls << bf::log::ltrace;
      ls << I_("AboutPropActiveMqPage: ERR_CANNOT_RESOLVE_HOST_FROM_NAME") << bf::log::endl;
      ls << I_("AboutPropActiveMqPage: HostAddress = ") << strHost << bf::log::endlf;
      ls << I_("AboutPropActiveMqPage: WSAGetLastError() = ") << WSAGetLastError()
         << bf::log::endlf;
      strError = I_("Bad Host");
      return (-3);
    }
  }

  int mySocket = ::socket(AF_INET, SOCK_STREAM, 0);

  if (mySocket < 0)
  {
    bf::log::LogStream ls(bf::log::databroker);
    ls << bf::log::ltrace;
    ls << I_("AboutPropActiveMqPage: ERR_SOCKET_INITIALIZATION_FAILED") << bf::log::endl;
    ls << I_("AboutPropActiveMqPage: WSAGetLastError() = ") << WSAGetLastError() << bf::log::endlf;
    strError = I_("SockError");
    return (-4);
  }

  struct sockaddr_in sin;

  memcpy(&sin.sin_addr.s_addr, hp->h_addr, hp->h_length);
  sin.sin_family = AF_INET;
  sin.sin_port = ::htons((short)nPort); /* Service port number */

  BFHRTimer tConnect;
  if (::connect(mySocket, (struct sockaddr*)&sin, sizeof sin))
  {
    bf::log::LogStream ls(bf::log::databroker);
    ls << bf::log::ltrace;
    ls << I_("AboutPropActiveMqPage: ERR_SOCKET_CONNECT_FAILED") << bf::log::endl;
    ls << I_("AboutPropActiveMqPage: WSAGetLastError() = ") << WSAGetLastError() << bf::log::endlf;
    strError = I_("Timeout");
    return (-5);
  }
  ::closesocket(mySocket);
  // successfully connected in # ms
  I_CHAR szBuf[256];
  i_sprintf(szBuf, I_("%ld ms"), tConnect.elapsed());
  strError = szBuf;
  return (tConnect.elapsed());
}
