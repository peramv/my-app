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
// ^FILE   : BFSecurity.hpp
// ^AUTHOR : David B. Smith 
// ^DATE   : January 2000
//
// ^CLASS    : BFSecurity
// ^INHERITS FROM : BaseDBSecurity          
//
// ^CLASS DESCRIPTION : 
//    This class provides an abstract interface for the project specific security 
//    classes.
//
//******************************************************************************

#include <condition.hpp>
#include <basedbsecurity.hpp>

class BFHost;

// Import/Export resolution
#undef BFDBRKR_LINKAGE
#ifdef BFDBRKR_DLL
   #define BFDBRKR_LINKAGE CLASS_EXPORT
#else
   #define BFDBRKR_LINKAGE CLASS_IMPORT
#endif

class BFDBRKR_LINKAGE BFSecurity : public BaseDBSecurity
{
public:
   virtual ~BFSecurity()
   {
   }

   virtual SEVERITY logon( const DString &operatorId, const DString &password ) = 0;
   virtual SEVERITY logoff( DString& logoutMessage ) = 0;
   virtual SEVERITY changePassword( const DString &password, const DString &newPassword ) = 0;

   virtual const DString &getLanguage() const = 0;
   virtual const DString &getLocale() const = 0;
   virtual bool isLoggedOn() const = 0;

   virtual const BFHost *getHost() const = 0;

};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   //db3n5j11/d/scc/ifds/core/archives/bfdbrkr/BFSecurity.hpp-arc  $
 * 
 *    Rev 1.9   Oct 09 2002 17:40:40   PURDYECH
 * New PVCS Database
 * 
 *    Rev 1.8   22 Mar 2002 15:11:44   PURDYECH
 * Removed compile-time "including..." message
 * Use #pragma once as include guard
 * Include files with lower-case only names
 * 
 *    Rev 1.7   08 Aug 2001 10:56:50   SMITHDAV
 * Made extensive fixes to ClientLocale management.
 * 
 *    Rev 1.6   03 May 2001 14:03:26   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.5   Feb 07 2001 10:51:02   MCNABBGL
 * formatted code 
 * 
 *    Rev 1.4   Jan 23 2001 15:20:28   YINGBAOL
 * add eTrack
 * 
 *    Rev 1.3   Sep 28 2000 13:01:42   FENGYONG
 * Add getcurrentCompanyId
 * 
 *    Rev 1.2   Jul 25 2000 11:51:28   YINGZ
 * take out logon off for the existing user
 * 
 *    Rev 1.1   Feb 15 2000 18:54:58   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 10:57:46   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.0   Feb 07 2000 15:17:52   SMITHDAV
 * Initial revision.
*/
