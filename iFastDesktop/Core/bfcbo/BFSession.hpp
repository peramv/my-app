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
// ^FILE   : BFSession.hpp
// ^AUTHOR : David Smith
// ^DATE   :
//
// ^CLASS    : BFSession
//
// ^CLASS DESCRIPTION :
//
//
//******************************************************************************

#include <commonport.h>
#include <bfdata\bfdata.hpp>

class BFUserSession;
class BFGlobalSession;
class BFSecurity;
class BFHost;
class ClientLocale;

// Import/Export resolution
#undef BFBASE_LINKAGE
#ifdef BFBASE_DLL
   #define BFBASE_LINKAGE CLASS_EXPORT
#else
   #define BFBASE_LINKAGE CLASS_IMPORT
#endif

class BFBASE_LINKAGE BFSessionTempData
{
public:
   BFSessionTempData(long workDataSetId);
   ~BFSessionTempData();

   void getField( const BFFieldId &fieldID, DString &strValueOut) const;
   void clear();
   void setField( const BFFieldId &fieldID, const DString &strValue );

private:
   BFData _tempData;    // Must be set based on specific data set    work session global
};

class BFBASE_LINKAGE BFSession
{
public:
   BFSession(long workDataSetId) : _tempData(workDataSetId) {}
   virtual ~BFSession() {}

   virtual const BFUserSession &getUserSession() const = 0;
   virtual const BFGlobalSession &getGlobalSession() const = 0;
   virtual const BFSecurity *getSecurity(const BFHost &host) const = 0;

   virtual BFUserSession &getUserSession() = 0;
   virtual BFGlobalSession &getGlobalSession() = 0;

   virtual const ClientLocale &getClientLocale() const = 0;
   virtual bool isBFWorkSession() const = 0;
   virtual bool isBFGlobalSession() const = 0;
   virtual bool isBFUserSession() const = 0;

   const BFSessionTempData& getTempData() const {
      return _tempData;
   }

   BFSessionTempData& getTempData() {
      return _tempData;
   }

private:
   BFSessionTempData _tempData;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF Core/bfcbo/BFSession.hpp-arc  $
//
//   Rev 1.5   May 14 2004 13:24:30   SMITHDAV
//Add a temporary data area to the session objects. This replaces the InterProcessData globale areas.
//
//   Rev 1.4   Jan 06 2003 16:41:22   PURDYECH
//BFDataGroupId changeover
//
//   Rev 1.3   Oct 09 2002 17:40:08   PURDYECH
//New PVCS Database
//
//   Rev 1.2   Aug 29 2002 12:51:16   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.1   22 Mar 2002 15:11:44   PURDYECH
//Removed compile-time "including..." message
//Use #pragma once as include guard
//Include files with lower-case only names
//
//   Rev 1.0   03 May 2001 14:51:18   SMITHDAV
//Initial revision.
 * 
 */
