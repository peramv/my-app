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
// ^FILE   : DSTCUserSession.hpp
// ^AUTHOR : Cristina Oltean
// ^DATE   : Jan, 2001
//
// ^CLASS    : DSTCWorkSession
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include <bfcbo\BFUserSession.hpp>
#include <boost\utility.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class DSTCGlobalSession;
class DSTCWorkSession;
class UserAccessList;
class MgmtCo;
class DSTCHost;
class ReportStatusCriteria;
class PrinterList;

class IFASTCBO_LINKAGE DSTCUserSession : public BFUserSession, private boost::noncopyable
{
public:
   DSTCUserSession();
   DSTCUserSession(DSTCGlobalSession &globalSession);

   ~DSTCUserSession();

   void establishLogonState( const DSTCHost &host, 
                             const DString& userID, 
                             const DString& sessionID, 
                             const DString& locale );

   const DString& getUserId(const DSTCHost &host) const;
   const DString& getSessionId(const DSTCHost &host) const;

   DString getUserName(const DSTCHost &host) const;
   DString getDaysPasswordChange(const DSTCHost &host) const;

   long getNumberOfCompanies(const DSTCHost &host) const;

   void getCompanyInfo( const DSTCHost &host,
                        const unsigned long companyIndex,  
                        DString &companyId,
                        DString &companyName ) const;


   DSTCGlobalSession &createGlobalSession();
   DSTCWorkSession &createWorkSession( const DString& mgmtCoId );

   // UserAccessList maints
   SEVERITY setStopNFU (const BFDataGroupId& idDataGroup, const DString &lastActiveAccountNumber);

   SEVERITY getUserAccessList( const DSTCHost &host, const DString& companyId, UserAccessList *&pUserAccessListOut );
   SEVERITY getUserAccessList( const DString& companyId, UserAccessList *&pUserAccessListOut );
   bool hasUserAccessList( const DString& companyId );

   SEVERITY refreshUserAccessList( const DSTCHost &host, const DString& companyId, UserAccessList *&pUserAccessListOut );
   SEVERITY refreshUserAccessList( const DString& companyId, UserAccessList *&pUserAccessListOut );

   bool hasCreatePermission( const DString& companyId, const DString& functionCode ) const;
   bool hasReadPermission(   const DString& companyId, const DString& functionCode ) const;
   bool hasUpdatePermission( const DString& companyId, const DString& functionCode ) const;
   bool hasDeletePermission( const DString& companyId, const DString& functionCode ) const;
   SEVERITY getReportStatusCriteria ( ReportStatusCriteria*& pReportStatusCriteria, const BFDataGroupId& idDataGroup );
   SEVERITY createReportStatusCriteria ( ReportStatusCriteria*& pReportStatusCriteria, const BFDataGroupId& idDataGroup );
   SEVERITY getPrinterList ( PrinterList*& pPrinterList, const BFDataGroupId& idDataGroup );
   SEVERITY createPrinterList ( const DString& dstrCompanyId, PrinterList*& pPrinterList, const BFDataGroupId& idDataGroup );
   bool isFFID(const DSTCHost &host) const;
   DSTCWorkSession * FindWorksessionByAccount(const DString &dstrAccountNumber) const;
   int getNumberOfWorksession() const;
   void setFireFighterLogonInfo(const DString& dstrFFID,const DString &dstrPassword,const DString &dstrPTSNum,const DString &dstrDesc1,const DString &dstrDesc2,const DString &dstrDesc3,const DString &dstrDesc4);
   SEVERITY fireFighterLogon(const DString & dstCompanyId);
   bool isFunctionActivated( const DString& companyId, const DString& functionCode ) const;
   void setClientLocale( const ClientLocale& rLocale ){BFUserSession::setClientLocale(rLocale);};

private:
   DSTCUserSession( const DSTCUserSession &copy );// not implemented
   DSTCUserSession& operator=( const DSTCUserSession &copy );// not implemented

   void buildUserAccessListKey( const DSTCHost &host, const DString& companyId, DString& newKey );
   bool hasPermission( const DString& companyId, const DString& functionCode, const BFFieldId& permissionID ) const;

   void verifyMarket();

   bool _ownGlobalSession;
   DString m_lastActiveAccountNumber;
   DString m_StopNFU;
   DString m_dstrFFID,m_dstrPassword,m_dstrPTSNum,m_dstrDesc1,m_dstrDesc2,m_dstrDesc3,m_dstrDesc4;
   DString m_usedCompany;

};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCUserSession.hpp-arc  $
//
//   Rev 1.20   Dec 30 2011 08:36:18   if991250
//set the UserSession locale on language toggle
//
//   Rev 1.19   Oct 04 2011 18:14:14   dchatcha
//P0186477 FN01 - GIA Enhancements, display validate portfolio fields based on environment functionality(UAF).
//
//   Rev 1.18   Jan 08 2010 11:57:20   yingz
//delay view 276 for inc#1936007
//
//   Rev 1.17   Oct 27 2009 23:49:20   purdyech
//Added hasUserAccessList() method.
//
//   Rev 1.16   Nov 06 2008 14:30:08   jankovii
//PET 5517 FN71 Unclaimed Property Phase 2.
//
//   Rev 1.15   Nov 14 2004 14:33:58   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.14   Aug 12 2004 14:31:38   FENGYONG
//PTS 10082387 - limit user open 5 sessions
//
//   Rev 1.13   May 11 2004 14:27:40   FENGYONG
//PET1046 FN1 - transfer-switch -Rel57
//
//   Rev 1.12   Dec 11 2003 11:44:46   linmay
//added isFFID()
//
//   Rev 1.11   Mar 21 2003 18:07:26   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.10   Dec 08 2002 22:03:30   HSUCHIN
//added printerlist and reportstatuscriteria cbo
//
//   Rev 1.9   Oct 09 2002 23:54:24   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.8   Sep 17 2002 16:46:22   PURDYECH
//Added market verification.  If the Config/Market/Market registry value is not set then it effectively defaults to Canada.
//
//   Rev 1.7   Aug 29 2002 12:52:14   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.6   22 May 2002 18:21:12   PURDYECH
//BFData Implementation
//
//   Rev 1.5   19 Mar 2002 13:16:52   PURDYECH
//Use #pragma once as include guard
//Remove compile time "including..." message
//
//   Rev 1.4   25 Oct 2001 14:02:44   SMITHDAV
//hasPermission changes...
//
//   Rev 1.3   08 Aug 2001 11:01:08   SMITHDAV
//Made extensive fixes to ClientLocale management.
//
//   Rev 1.2   09 Jul 2001 15:25:04   SMITHDAV
//Mgmt company refresh related changes.
//
//   Rev 1.1   14 Jun 2001 11:56:30   SMITHDAV
//Re-worked user access list and permission checking code.
//
//   Rev 1.0   03 May 2001 14:50:30   SMITHDAV
//Initial revision.
 *
 */
