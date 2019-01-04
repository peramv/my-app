#pragma once
#include <srvbase/server.hpp>

//Forward declarations

class VisionServer : public Server
{
public:

   virtual ~VisionServer();
   /**
    * These methods register/deregister the data factories with the server,
    * so the way the requests and answers are built can be server independent;
    */

   static VisionServer* getInstance();
   static void killInstance();
   static VisionServer* createInstance( int port, 
                                        int threadCount, 
                                        int queueSize, 
                                        bool bTrace = false,
                                        int iTimeout = 0 );

   virtual bool keyPressed( int c );
   void toggleConsoleTrace();
   bool isConsoleTraceOn() const;
   bool isNoisy() const { return bNoisy_; }

private:
   bool bLogToConsole_;
   bool bNoisy_;

   VisionServer( int port, 
                 int threadCount, 
                 int queueSize, 
                 bool bTrace = false,
                 int iTimeout = 0 );

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbps/VisionServer.hpp-arc  $
//
//   Rev 1.2   Feb 25 2004 11:05:32   PURDYECH
//Server::keyPressed() now returns a bool.
//
//   Rev 1.1   Jan 22 2004 14:46:30   PURDYECH
//PET 910 - Added keyboard handling and trace suppression
//
//   Rev 1.0   Aug 21 2003 11:02:00   PURDYECH
//Initial revision.
//
//   Rev 1.27   Jul 29 2003 10:48:14   FENGYONG
//Add bTrace
//
//   Rev 1.26   Feb 19 2003 15:18:02   SMITHDAV
//Update VisionServer to have a sigleton interface and expected by the core classes.
//
//   Rev 1.25   Oct 09 2002 23:56:30   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.24   22 Mar 2002 15:30:56   PURDYECH
//Removed compile-time "including..." message
//Use #pragma once as include guard
//Include files with lower-case only names
//
//   Rev 1.23   03 Oct 2001 15:10:16   SMITHDAV
//Syncronization changes and Job Queue changes
//
//   Rev 1.22   Dec 11 2000 11:58:44   VASILEAD
//changed shrldnacct name
//
//   Rev 1.21   Dec 06 2000 15:10:26   VASILEAD
//Fixed the name of the logoff service
//
//   Rev 1.20   Dec 04 2000 13:28:28   VASILEAD
//Added FundToListService
//
//   Rev 1.19   Nov 30 2000 10:03:02   FENGYONG
//Add FundToList
//
//   Rev 1.18   Nov 21 2000 10:19:26   VASILEAD
//Added AllFundInfoService
//
//   Rev 1.17   Nov 17 2000 14:42:10   FENGYONG
//change PAGENAME for remove DataEngine
//
//   Rev 1.16   Nov 01 2000 10:36:50   VASILEAD
//Added Purchase service
//
//   Rev 1.15   Oct 27 2000 16:11:10   VASILEAD
//Added Purchase service
//
//   Rev 1.14   Oct 12 2000 14:33:54   YINGZ
//add TradeSrchList
//
//   Rev 1.13   Oct 03 2000 11:19:42   VASILEAD
//Added NASU server support
//
//   Rev 1.12   Sep 27 2000 11:33:04   YINGZ
//add page ACCT_DTL0
//
//   Rev 1.11   Sep 25 2000 15:44:00   YINGZ
//take off internal logon logoff
//
//   Rev 1.10   Sep 18 2000 14:15:34   YINGZ
//move namespace around
//
//   Rev 1.9   Sep 14 2000 11:59:04   YINGZ
//change to create new service for each page request
//
//   Rev 1.8   Sep 07 2000 12:01:34   FENGYONG
//Add new service
//
//   Rev 1.7   Aug 10 2000 19:35:08   FENGYONG
//Add JEntityListProcess
//
//   Rev 1.6   Aug 02 2000 16:20:46   VASILEAD
//Added Maintenance Service
//
//   Rev 1.5   Jul 25 2000 17:33:54   YINGZ
//add internal logon off service
//
//   Rev 1.4   Jul 21 2000 14:57:38   VASILEAD
//Fixed VerificationConf
//
//   Rev 1.3   Jul 20 2000 15:18:32   VASILEAD
//Added VerificationConf service, process and CBO
//
//   Rev 1.2   May 08 2000 17:09:14   YINGZ
//add RedCodeByTaxType service
//
//   Rev 1.1   Apr 25 2000 16:13:28   YINGZ
//add new service
//
//   Rev 1.0   Apr 04 2000 10:25:40   POPESCUS
//Initial revision.
 * 
 * 
 */