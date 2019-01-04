#pragma once

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
//    Copyright 2000 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : DSTCGlobalSession.hpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : DSTCGlobalSession
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <bfcbo\BFGlobalSession.hpp>
#include <boost\utility.hpp>
#include <map>
#include <set>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class DSTCUserSession;
class MgmtCo;

class IFASTCBO_LINKAGE DSTCGlobalSession : public BFGlobalSession, private boost::noncopyable
{
public:
   ~DSTCGlobalSession();

   SEVERITY refreshMgmtCo( const DString& dstMgmtCo );
   /**
   * if dstMgmtCo is already in the map it will reuse it,
   * otherwise it will create it; 
   */
   SEVERITY getMgmtCo( const DString& dstMgmtCo );

   /**
   * if dstMgmtCo is already in the map it returns true,
   * otherwise returns false; 
   */
   bool findMgmtCo( const DString& dstMgmtCo );

    /**
   * it returns a pointer to the MgmCo
   * if dstMgmtCo is already in the map it returns true,
   * otherwise returns false; 
   */
   bool findMgmtCo( const DString& dstMgmtCo, MgmtCo*& pMgmtCo );

   MgmtCo *aquireMgmtCo( const DString& dstMgmtCo );
   void freeMgmtCo( MgmtCo *pMgmtCo );

private:

   // Construct only through DSTCUserSession::createUserSession method (friend)
   DSTCGlobalSession(DSTCUserSession &userSession);

   friend DSTCUserSession;

   typedef std::map< DString, MgmtCo*>   MGMT_CO_MAP;
   typedef MGMT_CO_MAP::iterator         MGMT_CO_MAP_ITER;
   typedef MGMT_CO_MAP::value_type       MGMT_CO_MAP_VALUE_TYPE;

   typedef std::set<MgmtCo*>             MGMT_CO_SET;
   typedef MGMT_CO_SET::iterator         MGMT_CO_SET_ITER;

   MGMT_CO_MAP _currentMgmtCoMap;
   MGMT_CO_SET _retiredMgmtCoSet;

   BFCritSec _mgmtCoLock;

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCGlobalSession.hpp-arc  $
//
//   Rev 1.11   07 Mar 2008 14:06:46   kovacsro
//IN#1172388 - added an overloaded findMgmtCo method to also return the MgmtCo pointer
//
//   Rev 1.10   22 Feb 2008 11:00:44   kovacsro
//IN#1191514 - added findMgmtCo
//
//   Rev 1.9   Nov 14 2004 14:32:46   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.8   Sep 29 2004 15:15:08   SMITHDAV
//Changed DString value parameters to reference parameters.
//
//   Rev 1.7   Oct 09 2002 23:54:20   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.6   Aug 29 2002 12:52:10   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.5   22 May 2002 18:21:22   PURDYECH
//BFData Implementation
//
//   Rev 1.4   19 Mar 2002 13:15:36   PURDYECH
//Use #pragma once as include guard
//Remove compile time "including..." message
//
//   Rev 1.3   10 Jan 2002 12:17:26   KOVACSRO
//Added getMgmtCo method. Supposed to be used only by Desktop.
//
//   Rev 1.2   11 Jul 2001 12:20:44   SMITHDAV
//Fix Global Session cleanup problems.
//
//   Rev 1.1   09 Jul 2001 15:25:02   SMITHDAV
//Mgmt company refresh related changes.
//
//   Rev 1.0   03 May 2001 14:50:30   SMITHDAV
//Initial revision.
 *
 */
