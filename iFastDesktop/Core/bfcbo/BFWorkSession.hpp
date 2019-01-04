#pragma once
#if defined(VERBOSE_INCLUDES)
   #pragma message( "including "__FILE__ )
#endif   

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
//    Copyright 1999 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : BFWorkSession.hpp
// ^AUTHOR : David Smith
// ^DATE   :
//
// ^CLASS    : BFWorkSession
//
// ^CLASS DESCRIPTION :
//
//
//******************************************************************************

#include <srcprag.h>
#include <commonport.h>
#include <bfcbo\bfsession.hpp>
#include <bfcbo\bfcbo.hpp>
#include <clientlocale.hpp>
#include <bfcbo\hosttransactioncontainer.hpp>

class BFUserSession;
class BFGlobalSession;
class BFSecurity;
class BFHost;

// Import/Export resolution
#undef BFBASE_LINKAGE
#ifdef BFBASE_DLL
   #define BFBASE_LINKAGE CLASS_EXPORT
#else
   #define BFBASE_LINKAGE CLASS_IMPORT
#endif

class BFBASE_LINKAGE BFWorkSession : public BFSession, public BFCBO
{
public:
   virtual const BFSession &getSession() const; 
   virtual BFSession &getSession(); 

   virtual bool isSession() const;

   virtual const BFUserSession &getUserSession() const;
   virtual BFUserSession &getUserSession();

   virtual const BFGlobalSession &getGlobalSession() const;
   virtual BFGlobalSession &getGlobalSession();

   virtual const BFSecurity *getSecurity(const BFHost &host) const;
   virtual const ClientLocale &getClientLocale() const;

   virtual bool isBFWorkSession() const;
   virtual bool isBFGlobalSession() const;
   virtual bool isBFUserSession() const;

   virtual SEVERITY buildTransactions() = 0;
   virtual SEVERITY commit() = 0;
   virtual SEVERITY refreshData() = 0;

   virtual bool hasCreatePermission( const DString &functionCode ) const = 0;
   virtual bool hasReadPermission(   const DString &functionCode ) const = 0;
   virtual bool hasUpdatePermission( const DString &functionCode ) const = 0;
   virtual bool hasDeletePermission( const DString &functionCode ) const = 0;

   void clearUncommitedTransactions();
   void cleanupWorkSession();

   HostTransactionContainer& getHostTransactionContainer();
   bool getHadTrxnError() {return _hadTrxnError;};
   void setHadTrxnError(bool hadTrxnError) {_hadTrxnError = hadTrxnError;};
   bool getIsEndSession() {return _endSession;};
   void setIsEndSession(bool endSession) {_endSession = endSession;};

protected:
//   BFWorkSession(BFUserSession &userSession);
   BFWorkSession(BFUserSession &userSession, long workDataSetId );

   void setClient( const DString &client );

private:
   BFWorkSession(); // not implemented
   BFWorkSession(const BFWorkSession& copy); // not implemented

   BFUserSession &_userSession;
   ClientLocale _clientLocale;
   BFData _workData;    // Must be set based on specific data set    work session global
   HostTransactionContainer _hostTransactionContainer;
   bool _hadTrxnError;
   bool _endSession;

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF Core/bfcbo/BFWorkSession.hpp-arc  $
//
//   Rev 1.10   May 14 2004 13:22:18   SMITHDAV
//Add a temporary data area to the session objects. This replaces the InterProcessData globale areas.
//
//   Rev 1.9   May 10 2004 15:09:00   SMITHDAV
//Move work-session level "global data" to the BFWorksession from InterProcessData.
//
//   Rev 1.8   Jan 06 2003 16:41:28   PURDYECH
//BFDataGroupId changeover
//
//   Rev 1.7   Oct 09 2002 17:40:12   PURDYECH
//New PVCS Database
//
//   Rev 1.6   Aug 29 2002 12:51:16   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.5   22 May 2002 18:08:50   PURDYECH
//BFData Implementation
//
//   Rev 1.4   22 Mar 2002 15:11:46   PURDYECH
//Removed compile-time "including..." message
//Use #pragma once as include guard
//Include files with lower-case only names
//
//   Rev 1.3   25 Oct 2001 14:02:42   SMITHDAV
//hasPermission changes...
//
//   Rev 1.2   08 Aug 2001 10:56:50   SMITHDAV
//Made extensive fixes to ClientLocale management.
//
//   Rev 1.1   14 Jun 2001 11:56:30   SMITHDAV
//Re-worked user access list and permission checking code.
//
//   Rev 1.0   03 May 2001 14:44:50   SMITHDAV
//Initial revision.
 * 
 */

