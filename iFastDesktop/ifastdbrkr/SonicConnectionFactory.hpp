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
// ^FILE   : SonicConnectionFactory.hpp
// ^AUTHOR : David B. Smith 
// ^DATE   : January 2000
//
// ^CLASS    : SonicConnectionFactory
// ^INHERITS FROM : BFConnectionFactory         
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************
#include <win32\platform.h>
#include <dstring.hpp>
#include <bfconmgr\BFConnectionFactory.hpp>

#include <progress/message/jclient/package.h>

class BFConnection;

// Import/Export resolution
#undef IFASTDBRKR_LINKAGE
#ifdef IFASTDBRKR_DLL
   #define IFASTDBRKR_LINKAGE CLASS_EXPORT
#else
   #define IFASTDBRKR_LINKAGE CLASS_IMPORT
#endif

class IFASTDBRKR_LINKAGE SonicConnectionFactory : public BFConnectionFactory
{
public:
   SonicConnectionFactory( const DString& brokerURLs, 
                           const DString& singleQueue,
                           const DString& multiQueue,
                           const DString& ldapQueue,
                           const DString& awdQueue,
                           const DString& user, 
                           const DString& password,
                           int cMaxUses,
                           int iTimeout,
                           const DString& dstrCswAcl = DString(I_("cswacl"))
                           );
   ~SonicConnectionFactory();

   const DString& getCswAcl() const { return dstrCswAcl_; }

   virtual BFConnection *createConnection(const DStringA &hostId);
   virtual void destroyConnection(BFConnection *connection);

   inline int getTimeout() const { return iTimeout_; }
   void setTimeout( int iTimeout );
   inline const DString& getBrokerURLs() const { return brokerURLs_; }
   inline const DString& getSingleQueue() const { return singleQueue_; }
   inline const DString& getMultiQueue() const { return multiQueue_; }
   inline const DString& getLDAPQueue() const { return ldapQueue_; }
   inline const DString& getAwdQueue() const { return awdQueue_; }
   inline const DString& getUser() const { return user_; }
   inline const DString& getPassword() const { return password_; }
   inline int getMaxUses() const { return cMaxUses_; }

private:
   DString brokerURLs_;
   DString singleQueue_;
   DString multiQueue_;
   DString ldapQueue_;
   DString awdQueue_;
   DString user_;
   DString password_;
   int cMaxUses_;
   int iTimeout_;

   DString dstrCswAcl_;

   progress::message::jclient::QueueConnectionFactoryRef connFactory_;
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastdbrkr/SonicConnectionFactory.hpp-arc  $
//
//   Rev 1.6   Jan 06 2010 13:58:38   purdyech
//Store SMQ password to allow SMQTest to be used from AboutSonicPropPage
//
//   Rev 1.5   Aug 03 2009 23:15:34   purdyech
//LDAP Integration Pieces
//
//   Rev 1.4   Jun 05 2009 08:30:48   purdyech
//Fixed names of SonicSingle and SonicMulti queues in configuration.
//SonicErrorMessages are now handled appropriately.
//
//   Rev 1.3   May 01 2009 09:26:56   purdyech
//Add support to customize CswAcl property value
//
//   Rev 1.2   Feb 27 2009 08:49:54   purdyech
//ZTS Fixes prior to User Experience Test
//
//   Rev 1.1   Feb 06 2009 14:52:50   purdyech
//Interim CheckIn for ZTS Support (Chris is goin' on vacation!)
//
//   Rev 1.0   Jun 17 2008 15:55:32   smithdav
//Initial revision.
// 
//
*/