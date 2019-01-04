#pragma once

/** 
 *    COPYRIGHT:
 *
 *    The computer systems, procedures, data bases and
 *    programs created and maintained by DST Systems, Inc.,
 *    are proprietary in nature and as such are confidential.
 *    Any unauthorized use or disclosure of such information
 *    may result in civil liabilities.
 *
 *    Copyright 1996-2000 by DST Systems, Inc.
 */

//CP20021120/**@pkg BFAWDI */    

#include <commonport.h>
#include <dstring.hpp>

#undef BFAWDI_LINKAGE
#ifdef BFAWDI_DLL
   #define BFAWDI_LINKAGE CLASS_EXPORT
#else
   #define BFAWDI_LINKAGE CLASS_IMPORT
#endif

/**
 * This class is used to return the results of a lookup on the AWD server.
 *
 * A single BFAwdLookupResult object represents either a single AWD work or
 * a single AWD source object.
 *
 * @see CriteriaVector
 */
class BFAWDI_LINKAGE BFAwdLookupResult
{
public:
   /**
    * Default constructor.
    */
   BFAwdLookupResult();

   /**
    * Copy constructor.
    *
    * @param copy - The BFAwdLookupResult object to copy.
    */
   BFAwdLookupResult( const BFAwdLookupResult &copy );

   /**
    * Destructor.
    */
   virtual ~BFAwdLookupResult();

public:
   /**
    * Returns the business area.
    *
    * @return The business area.
    */
   DString getBusinessArea() const;

   /**
    * Returns the work type, if the object is an AWD work (transaction or
    * case) object.
    *
    * @return The work type.
    */
   DString getWorkType() const;

   /**
    * Returns the source type, if the object is an AWD source object.
    *
    * @return The source type.
    */
   DString getSourceType() const;

   /**
    * Returns the status, if the object is an AWD work (transaction or case)
    * object.
    *
    * @return The status.
    */
   DString getStatus() const;

   /**
    * Returns the queue, if the object is an AWD work (transaction or case)
    * object.
    *
    * @return The queue.
    */
   DString getQueue() const;

   /**
    * Returns the creation date and time. This is one of the three elements
    * of a key to an AWD object on an AWD server.  This is needed for an
    * BFAwdKey object.
    *
    * @return The creation date and time.
    */
   DString getCreateDateTime() const;

   /**
    * Returns the record code. This is one of the three elements of a key to
    * an AWD object on an AWD server.  This is needed for an BFAwdKey object.
    *
    * @return The record code.
    */
   DString getRecordCode() const;

   /**
    * Returns the creation node. This is one of the three elements of a key
    * to an AWD object on an AWD server.  This is needed for an BFAwdKey
    * object.
    *
    * @return The creation node.
    */
   DString getCreateNode() const;

   /**
    * Assignment operator.
    *
    * @param copy - The BFAwdLookupResult object to copy.
    *
    * @return Reference to self.
    */
   BFAwdLookupResult &operator=( const BFAwdLookupResult &copy );

protected:
   DString m_unit;
   DString m_wrkt;
   DString m_objt;
   DString m_stat;
   DString m_queu;
   DString m_crda;
   DString m_reco;
   DString m_crno;
};



//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF Core/bfawdi/bfawdlookupresult.hpp-arc  $
//
//   Rev 1.2   Nov 27 2002 14:51:48   PURDYECH
//Documentation Cleanup
//
//   Rev 1.1   Oct 09 2002 17:39:56   PURDYECH
//New PVCS Database
//
//   Rev 1.0   28 May 2002 12:11:20   SMITHDAV
//Initial revision.
// 
//    Rev 1.3   23 Oct 2000 11:44:32   dt14177
// cleanup
// 
//    Rev 1.2   Apr 24 2000 10:38:34   DMUM
//  
//
//    Rev 1.1   Apr 09 1999 13:26:22   DMUM
// Sync up with 1.6.x
//
//    Rev 1.0.2.0   Mar 31 1999 13:14:54   DMUM
// Sync up with Infra 1.6.x
//
//    Rev 1.0.1.1   Feb 19 1999 07:47:32   DMUM
// Added lookupSource() and fixed BFAwdTemplates
//
//    Rev 1.0.1.0   Feb 09 1999 10:23:30   DMUM
// Added documentation
//
//    Rev 1.0   Jan 20 1999 09:08:50   DMUM
//
//
//

