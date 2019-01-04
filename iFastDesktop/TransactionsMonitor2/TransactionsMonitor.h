#ifndef TRANSACTIONS_MONITOR_H
#define TRANSACTIONS_MONITOR_H

#include <condition.hpp>
#include <string>
#include <dstring.hpp>

int main(int argc, char** argv);

class DSTCUserSession;
class DSTCWorkSession;

SEVERITY Logon(DSTCUserSession** _dstcUserSession, const std::string& username, const std::string& password);
SEVERITY Logoff(DSTCUserSession *_dstcUserSession);
SEVERITY CallView(DSTCWorkSession** _dstrWorkSession, DSTCUserSession* _dstcUserSession, const DString& mgmtCoName);
SEVERITY CallSmartView(DSTCUserSession* _dstcUserSession, DSTCWorkSession* _dstcWorkSession);

BOOL SiteConfigInit( const std::string& t, bool bOverrideRegistry ) ;

bool ParseArgugments(int argc, char** args, std::string& username, std::string& password, std::string& client, std::string& siteXml);

#endif
