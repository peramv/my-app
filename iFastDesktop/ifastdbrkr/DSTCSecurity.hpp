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
//    Copyright 1999 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : DSTCSecurity.hpp
// ^AUTHOR : Chris Kennedy, moved to the BFBase level by Serban Popescu(06/25/99)
// ^DATE   : 04/12/1999
//
// ^CLASS  : DSTCSecurity
//
// ^CLASS DESCRIPTION : Security singleton for accessing DSTCanada Corfax system
//

#include <commonport.h>
#include <bfdbrkr\BFSecurity.hpp>
#include <condition.hpp>
#include <bfdata\bfdata.hpp>
#include <bfutil\bfcritsec.hpp>


#undef IFASTDBRKR_LINKAGE
#ifdef IFASTDBRKR_DLL
   #define IFASTDBRKR_LINKAGE CLASS_EXPORT
#else
   #define IFASTDBRKR_LINKAGE CLASS_IMPORT
#endif

class TiXmlDocument;
class BFRecordConnection;

class IFASTDBRKR_LINKAGE DSTCSecurity : public BFSecurity
{
public:
   DSTCSecurity(const BFHost* host);
   ~DSTCSecurity();

   virtual SEVERITY logon( const DString &operatorId, const DString &password );
   virtual SEVERITY logoff( DString& logoutMessage );
   virtual SEVERITY changePassword( const DString &password, const DString &newPassword );

   virtual const DString& getLanguage() const;
   virtual const DString &getLocale() const;

   virtual bool isLoggedOn() const;
   virtual const BFHost *getHost() const;

   void establishLogonState( const DString& userID,
                             const DString& sessionID, 
                             const DString& locale );

   const DString& getUserId() const;
   const DString& getSessionId() const;
   void setSessionId( const DString& sessionId);
    
   DString getUserName() const;
   DString getDaysPasswordChange() const;

   long getNumberOfCompanies() const;

   void getCompanyInfo( const unsigned long companyIndex, DString &companyId, DString &companyName ) const;
   void getClientId (const DString& strCompanyId, DString& clientId, DString& strCompanyName, DString &companyUrl) const;
   void getAllSlSRepFlag( const DString& strCompanyId, DString& strAccessAllSlsRep ) const;

   void copySignonData( BFData*& signonData ) const;
   bool isFFID() const;
   DString getVersionLabel() const;
   DString getAccessID() const;
   DString getSessionToken() const{return _sessionToken;}

private:
   SEVERITY logonWithLDAP( const DString &operatorId, const DString &password );
   SEVERITY logoffFromLDAP( DString& logoutMessage );

   const BFHost* const _host;
   DString _sessionId;
   DString _userID;
   DString _language;
   DString _locale;
   BFData* _signonData;
   bool    _loggedOn;
   DStringA _sessionToken;
   DString _pwdDaysLeft;
   bool		_LDAPloggedOn;
   mutable BFCritSec _csSessionId;

   DSTCSecurity( const DSTCSecurity &copy );
   DSTCSecurity &operator=( const DSTCSecurity &copy );


   const DStringA & SMQSendReceive(BFRecordConnection *connection, const DStringA& request);
   const DStringA getToken(TiXmlDocument &doc, const DStringA& digpwd);
   const DStringA getStatus(TiXmlDocument &doc);
   const DStringA getPackage(TiXmlDocument &doc);
    const DString createPassTwoDoc(const DString& userID, const DString &userNS, const DString &authToken);
    const DString createLogoffDoc(const DString& userID, const DString &userNS, const DString &sessionToken);
    const DString createChangePasswordDoc(const DString& userID, const DString &userNS, const DString &oldPassword, const DString &newPassword);
    const DString createPassOneDoc(const DString& userID, const DString &userNS);
    const DStringA getResponseValue(TiXmlDocument &doc, const DStringA &key);
    void createView1Response(TiXmlDocument &doc);
	const DString getLocale(const DString language);
	SEVERITY changePasswordWithLDAP( const DString& password, const DString& newPassword );
};

///#endif

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastdbrkr/DSTCSecurity.hpp-arc  $
 * 
 *    Rev 1.25   Oct 21 2009 10:24:06   purdyech
 * LDAP Authorization Support
 * 
 *    Rev 1.24   Sep 02 2009 17:35:50   yingz
 * implement handling force password change
 * 
 *    Rev 1.23   Aug 14 2009 16:23:28   yingz
 * LDAP support
 * 
 *    Rev 1.22   Aug 03 2009 23:10:34   purdyech
 * LDAP Integration Pieces
 * 
 *    Rev 1.21   Aug 02 2009 22:26:50   yingz
 * LDAP change
 * 
 *    Rev 1.20   06 Dec 2007 15:20:04   popescu
 * Incident 1088629 - read the ACL set-up for the web pages URL instead of the using the xml configuration file.
 * 
 *    Rev 1.19   Aug 22 2005 10:51:16   ZHANGCEL
 * PET 1235 - FN02 -- Enhancement for Restricted Read Only Unserid 
 * 
 *    Rev 1.18   Feb 21 2005 15:30:32   Fengyong
 * 21193 - BPServer error: "User needs to log on first"
 * 
 *    Rev 1.17   Dec 11 2003 11:48:44   linmay
 * added isFFID( ) and getVersionLabel( )
 * 
 *    Rev 1.16   Oct 09 2002 23:55:24   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.15   Aug 29 2002 12:52:14   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.14   Jul 05 2002 08:55:06   PURDYECH
 * Fixed include files
 * 
 *    Rev 1.13   22 May 2002 18:21:18   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.12   19 Mar 2002 13:16:52   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.11   14 Aug 2001 11:16:06   SMITHDAV
 * Added getClientId() function.
 * 
 *    Rev 1.10   08 Aug 2001 10:56:52   SMITHDAV
 * Made extensive fixes to ClientLocale management.
 * 
 *    Rev 1.9   04 Aug 2001 11:35:02   KOVACSRO
 * Added getAllSlsRep(). Probably it should be a param. in getCompanyInfo.
 * 
 *    Rev 1.8   03 May 2001 14:04:04   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.7   Jan 23 2001 15:18:40   YINGBAOL
 * add eTrack
 * 
*/
